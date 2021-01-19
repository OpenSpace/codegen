/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021                                                                    *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include "codegen.h"

#include "parsing.h"
#include "settings.h"
#include "snippets.h"
#include "types.h"
#include "util.h"
#include "verifier.h"
#include <fmt/format.h>
#include <array>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

using namespace std::literals;

namespace {
    bool isBasicType(std::string_view type) {
        // Stand-in for a list of basic types that are supported
        std::string_view bake = bakeFunctionForType(type);
        return !bake.empty();
    }

    std::vector<std::string_view> extractTemplateTypeList(std::string_view types) {
        assert(!types.empty());

        std::vector<std::string_view> res;

        size_t base = 0;
        size_t cursor = 0;
        do {
            cursor++;
            if (types[cursor] == ',' || types[cursor] == '>') {
                std::string_view subtype = types.substr(base, cursor - base);
                res.push_back(strip(subtype));
                base = cursor + 1;
            }
        } while (types[cursor] != '>');

        return res;
    }

    std::vector<std::string_view> usedTypes(const Struct& s) {
        std::vector<std::string_view> res;
        for (const Variable* var : s.variables) {
            std::string_view type = var->type;

            if (startsWith(type, "std::optional<")) {
                res.push_back("std::optional");
                type.remove_prefix("std::optional<"sv.size());
                type.remove_suffix(1);

                if (isBasicType(type)) {
                    res.push_back(type);
                }
            }

            if (startsWith(type, "std::vector<")) {
                res.push_back("std::vector");
                type.remove_prefix("std::vector<"sv.size());
                type.remove_suffix(1);

                if (isBasicType(type)) {
                    res.push_back(type);
                }
            }

            if (startsWith(type, "std::variant<")) {
                res.push_back("std::variant");
                type.remove_prefix("std::variant<"sv.size());
                std::vector<std::string_view> types = extractTemplateTypeList(type);

                for (std::string_view t : types) {
                    if (isBasicType(t)) {
                        res.push_back(t);
                    }
                }
            }

            if (isBasicType(var->type)) {
                res.push_back(var->type);
            }
        }

        for (StackElement* e : s.children) {
            if (e->type != StackElement::Type::Struct)  continue;

            const Struct& s = static_cast<const Struct&>(*e);
            std::vector<std::string_view> t = usedTypes(s);
            res.insert(res.end(), t.begin(), t.end());
        }

        // Remove duplicates
        std::sort(res.begin(), res.end());
        res.erase(std::unique(res.begin(), res.end()), res.end());

        return res;
    }

    std::string resolveComment(std::string comment) {
        if (size_t it = comment.find("codegen::description"); it != std::string::npos) {
            const size_t l = "codegen::description"sv.size();
            it += l;
            if (comment[it] != '(') {
                throw std::runtime_error(fmt::format(
                    "Malformed codegen::description. Expected ( after token:\n{}", comment
                ));
            }
            it++;
            size_t end = comment.find(')', it);
            std::string identifier = comment.substr(it, end - it);
            comment = identifier + ".description";
        }
        else {
            if (size_t it = comment.find('"');
                it != std::string::npos && comment[it - 1] != '\\')
            {
                throw std::runtime_error(fmt::format(
                    "Discovered unallowed unescaped \" in comment line:\n{}", comment
                ));
            }

            // We add artificial spaces between the multiline comments, which causes there to
            // be a stray space at the end
            if (!comment.empty() && comment.back() == ' ') {
                comment.pop_back();
            }
            comment = fmt::format("\"{}\"", comment);
        }
        return comment;
    }
} // namespace

std::string verifier(std::string_view type, const Variable& variable, Struct* currentStruct) {
    assert(!type.empty());

    const Struct* root = rootStruct(currentStruct);
    std::string v = verifierForType(type, variable.attributes, root->attributes.dictionary);
    
    if (!v.empty()) {
        return std::string("new ") + v;
    }
    else if (startsWith(type, "std::vector<")) {
        type.remove_prefix("std::vector<"sv.size());
        type.remove_suffix(1);

        const StackElement* e = resolveType(currentStruct, type);
        std::string comments;
        if (e) {
            // e is false for subtypes that are not our own structs
            comments = resolveComment(e->comment);
        }

        std::string ver = verifier(type, variable, currentStruct);
        return fmt::format(
            "new TableVerifier({{{{\"*\",{},Optional::Yes, {}}}}})\n",
            ver, comments
        );
    }
    else if (startsWith(type, "std::variant<")) {
        std::string_view subtypes = type.substr("std::variant<"sv.size());
        if (subtypes.find('>') == std::string_view::npos) {
            throw std::runtime_error(fmt::format(
                "Could not find closing > in variant definition:\n{}", type
            ));
        }
        assert(subtypes.back() == '>');

        std::string result = "new OrVerifier({";

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            std::string ver = verifier(subtype, variable, currentStruct);
            result += ver + ",";
        }

        // Remove the final ,
        result.pop_back();

        result += "})";
        return result;
    }
    else {
        const StackElement* e = resolveType(currentStruct, type);
        if (!e) {
            throw std::runtime_error(fmt::format(
                "Type detected that codegen doesn't know how to handle: {}", type
            ));
        }

        return fmt::format("codegen_{}_{}", fqn(currentStruct, "_"), type);
    }
}

std::string writeEnumDocumentation(Enum* e) {
    std::string result = fmt::format(
        "    StringInListVerifier* codegen_{} = new StringInListVerifier({{",
        fqn(e, "_")
    );


    Enum* en = static_cast<Enum*>(e);
    for (EnumElement* em : en->elements) {
        // If no key attribute is specified, we use the name instead
        std::string_view key =
            em->attributes.key.empty() ?
            em->name :
            em->attributes.key;

        result += fmt::format("\"{}\",", key);
    }
    // The last element has a , at the end that we can overwrite
    result.pop_back();

    result += "});\n";
    return result;
}

std::string writeVariableDocumentation(Struct* s, Variable* var) {
    var->comment = resolveComment(var->comment);

    std::string_view type = var->type;
    bool isOptional = false;
    if (startsWith(var->type, "std::optional<")) {
        isOptional = true;
        type.remove_prefix("std::optional<"sv.size());
        type.remove_suffix(1);
    }

    std::string ver = fqn(s, "_");
    std::string v = verifier(type, *var, s);
    std::string result = fmt::format(
        "    codegen_{}->documentations.push_back({{\"{}\",{},{},{}}});\n",
        ver, var->key, v, isOptional ? "Optional::Yes" : "Optional::No", var->comment
    );
    return result;
}

std::string writeStructDocumentation(Struct* s) {
    std::string name = fqn(s, "_");
    std::string result = fmt::format(
        "    TableVerifier* codegen_{} = new TableVerifier;\n", name
    );

    for (StackElement* e : s->children) {
        if (e->type == StackElement::Type::Struct) {
            result += writeStructDocumentation(static_cast<Struct*>(e));
        }
        if (e->type == StackElement::Type::Enum) {
            result += writeEnumDocumentation(static_cast<Enum*>(e));
        }
    }

    for (Variable* var : s->variables) {
        result += writeVariableDocumentation(s, var);
    }

    return result;
}

std::string writeVariableConverter(Variable* var) {
    std::string result;
    if (startsWith(var->type, "std::variant")) {
        std::string subtypes = var->type.substr("std::variant<"sv.size());

        result = fmt::format(
            "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n",
            var->type
        );

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            result += fmt::format(
                "   if (d.hasValue<{0}>(key)) {{ {0} v; bakeTo(d, key, &v); *val = std::move(v); }}\n",
                subtype
            );
        }

        result += "}";
    }
    return result;
}

std::string writeEnumConverter(Enum* e) {
    std::string type = fqn(e, "::");
    std::string result = fmt::format(
        "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n"
        "    std::string v = d.value<std::string>(key);\n",
        type
    );

    for (EnumElement* elem : e->elements) {
        std::string_view key;
        if (elem->attributes.key.empty()) {
            key = elem->name;
        }
        else {
            key = elem->attributes.key;
        }

        std::string type = fqn(e, "::");
        result += fmt::format(
            "    if (v == \"{}\") {{ *val = {}::{}; }}\n",
            key, type, elem->name
        );
    }

    result += "}\n";
    return result;
}

std::string writeStructConverter(Struct* s) {
    std::string result;
    for (Variable* var : s->variables) {
        result += writeVariableConverter(var);
    }

    for (StackElement* e : s->children) {
        if (e->type == StackElement::Type::Struct) {
            result += writeStructConverter(static_cast<Struct*>(e));
        }

        if (e->type == StackElement::Type::Enum) {
            result += writeEnumConverter(static_cast<Enum*>(e));
        }
    }

    if (s->parent == nullptr) {
        return result;
    }

    std::string name = fqn(s, "::");
    result += fmt::format(R"(template <> void bakeTo<{0}>(const ghoul::Dictionary& d, std::string_view key, {0}* val) {{
    {0}& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
)",
        name
    );

    for (Variable* var : s->variables) {
        result += fmt::format(
            "    internal::bakeTo(dict, \"{}\", &res.{});\n", var->key, var->name
        );
    }

    result += "}\n";
    return result;
}

std::string generateResult(Struct* s) {
    std::string result = fmt::format(FileHeader);

    std::string name;
    if (s->attributes.namespaceSpecifier.empty()) {
        name = fmt::format("openspace::{}", s->attributes.dictionary);
    }
    else {
        name = fmt::format(
            "openspace::{}::{}",
            s->attributes.namespaceSpecifier,
            s->attributes.dictionary
        );
    }

    result += fmt::format(DocumentationPreamble, name);
    result += writeStructDocumentation(s);
    result += fmt::format(DocumentationEpilog, s->attributes.dictionary, s->name);



    // For Linux, we need to delcare the functions in the following order or the overload
    // resolution picks the top fall back implentation and triggers a static_assert:
    // 1. <typename T> bakeTo(..., T*) { static_assert(false); } // fallback
    // 2. <typename T> bakeTo(..., std::optional<T>*)   declaration only
    // 3. <typename T> bakeTo(..., std::vector<T>*)   declaration only
    // 4. bakeTo(..., T*) {...} for T=base types
    // 5. <typename T> bakeTo(..., T*) {...}  for T=custom structs
    // 6. <typename T> bakeTo(..., std::optional<T>*) {...}   definition
    // 7. <typename T> bakeTo(..., std::vector<T>*) {...}   definition
    //
    // Reason:  When going through the custom structs, they need to know that there will
    // be implementatinos for the optional and vector types or otherwise they will trip
    // the fall back.  However, the actual implementation needs to know about the custom
    // struct one or else *they* will trip the fall back in the implementation.
    // For ease of implementation, we are putting 3&4 before 2 instead

    result += BakeFunctionPreamble;

    std::vector<std::string_view> types = usedTypes(*s);
    for (std::string_view t : types) {
        if (t == "std::optional") {
            result += BakeFunctionOptionalDeclaration;
            continue;
        }
        if (t == "std::vector") {
            result += BakeFunctionVectorDeclaration;
            continue;
        }

        std::string_view bake = bakeFunctionForType(t);
        if (!bake.empty()) {
            // The return value is empty for types that don't have a
            // preamble-defined bake functions, like all custom structs
            result += bake;
        }
    }


    result += writeStructConverter(s);

    std::string fqName;
    if (s->attributes.namespaceSpecifier.empty()) {
        fqName = fmt::format("openspace::{}", s->attributes.dictionary);
    }
    else {
        fqName = fmt::format(
            "openspace::{}::{}",
            s->attributes.namespaceSpecifier,
            s->attributes.dictionary
        );
    }

    for (std::string_view type : types) {
        if (type != "std::vector" && type != "std::optional")  continue;

        std::string_view bake = bakeFunctionForType(type);
        assert(!bake.empty());
        result += bake;
    }

    result += fmt::format(
        R"(
}} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) {{ static_assert(sizeof(T) == 0); }}
template <> {0} bake<{0}>(const ghoul::Dictionary& dict) {{
    openspace::documentation::testSpecificationAndThrow(codegen::doc<{1}>(), dict, "{2}");
    {0} res;
)",
        s->name,
        fqName,
        s->attributes.dictionary
);

    for (Variable* var : s->variables) {
        result += fmt::format(
            "    internal::bakeTo(dict, \"{}\", &res.{});\n", var->key, var->name
        );
    }

    result += fmt::format("    return res;\n}}\n}} // namespace codegen\n");
    return result;
}

std::string handleCode(std::string_view code, std::string_view path) {
    std::string_view content = strip(validCode(code));
    if (content.empty()) {
        return std::string();
    }

    // Some initial sanity checks
    if (std::string_view s = content.substr(0, 6); s != "struct") {
        throw std::runtime_error(fmt::format(
            "[[codegen::Dictionary]] needs a 'struct' declaration immediately before on "
            "the same line. Found {}", s
        ));
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        constexpr const int ErrorContext = 50;
        throw std::runtime_error(fmt::format(
            "Block comments are not allowed:\n{}", content.substr(p, ErrorContext)
        ));
    }

    Struct* rootStruct = parseRootStruct(content);
    std::string genContent = generateResult(rootStruct);

    return genContent;
}

Result handleFile(std::filesystem::path path) {
    std::ifstream f(path);
    std::string res = std::string(std::istreambuf_iterator<char>{f}, {});
    f.close();


    std::string p = path.string();
    std::string genContent = handleCode(res, p);

    if (genContent.empty()) {
        return Result::NotProcessed;
    }

    std::filesystem::path destination = path;
    destination.replace_extension();
    destination.replace_filename(destination.filename().string() + "_codegen.cpp");

    bool shouldWriteFile;
    if (std::filesystem::exists(destination)) {
        std::ifstream f(destination);
        std::string prev = std::string(std::istreambuf_iterator<char>{f}, {});
        shouldWriteFile = (prev != genContent);
    }
    else {
        shouldWriteFile = true;
    }

    std::filesystem::path debugDestination = destination;
    debugDestination.replace_extension();
    debugDestination.replace_filename(debugDestination.filename().string() + "_debug.cpp");
    if (shouldWriteFile && PreventFileChange) {
        std::ofstream output(debugDestination);
        output.write(genContent.data(), genContent.size());

        throw std::runtime_error(fmt::format(
            "Asked to prevent file change, but file change detected in '{}'",
            path.filename().string()
        ));
    }

    if (shouldWriteFile || AlwaysOutputFiles) {
        print("Processed file '%s'\n", path.filename().string().c_str());

        std::ofstream r(destination);
        r.write(genContent.data(), genContent.size());

        std::filesystem::remove(debugDestination);
        return Result::Processed;
    }
    else {
        std::filesystem::remove(debugDestination);
        return Result::Skipped;
    }
}
