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
        size_t nBrackets = 1;
        do {
            cursor++;

            if (types[cursor] == '<') {
                nBrackets += 1;
            }

            if (types[cursor] == '>') {
                nBrackets -= 1;
            }

            if (types[cursor] == ',' || ((types[cursor] == '>') && (nBrackets == 0))) {
                std::string_view subtype = types.substr(base, cursor - base);
                res.push_back(strip(subtype));
                base = cursor + 1;
            }
        } while (nBrackets > 0);

        return res;
    }

    std::vector<std::string_view> usedTypes(const Struct& s) {
        std::vector<std::string_view> res;
        for (const Variable* var : s.variables) {
            std::string_view type = var->typeString;

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
                    if (startsWith(t, "std::vector<")) {
                        res.push_back("std::vector");
                        type.remove_prefix("std::vector<"sv.size());
                        type.remove_suffix(1);
                    }
                    if (isBasicType(t)) {
                        res.push_back(t);
                    }
                }
            }

            if (startsWith(type, "std::map<")) {
                res.push_back("std::map");
                type.remove_prefix("std::map<"sv.size());
                std::vector<std::string_view> types = extractTemplateTypeList(type);
                assert(types.size() == 2);
                assert(types[0] == "std::string");
                assert(types[1] == "std::string");
                res.push_back("std::string");
            }

            if (isBasicType(var->typeString)) {
                res.push_back(var->typeString);
            }
        }

        for (StackElement* e : s.children) {
            if (e->type != StackElement::Type::Struct) {
                continue;
            }

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
        if (size_t it = comment.find("codegen::verbatim"); it != std::string::npos) {
            const size_t l = "codegen::verbatim"sv.size();
            it += l;
            if (comment[it] != '(') {
                throw ParsingError(fmt::format(
                    "Malformed codegen::verbatim. Expected ( after token\n{}", comment
                ));
            }
            it++;
            const size_t end = comment.find(')', it);
            std::string argument = comment.substr(it, end - it);
            comment = argument;
        }
        else {
            if (size_t it = comment.find('"');
                it != std::string::npos && comment[it - 1] != '\\')
            {
                throw ParsingError(fmt::format(
                    "Discovered unallowed unescaped \" in comment line\n{}", comment
                ));
            }

            // We add artificial spaces between the multiline comments, which causes there
            // to be a stray space at the end
            if (!comment.empty() && comment.back() == ' ') {
                comment.pop_back();
            }
            comment = fmt::format("\"{}\"", comment);
        }
        return comment;
    }
} // namespace

std::string verifier(std::string_view type, const Variable& var, Struct* currentStruct) {
    assert(!type.empty());

    const Struct* root = rootStruct(currentStruct);
    std::string v = verifierForType(type, var.attributes, root->attributes.dictionary);
    
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

        std::string ver = verifier(type, var, currentStruct);
        return fmt::format(
            "new TableVerifier({{{{\"*\",{},Optional::Yes, {}}}}})\n", ver, comments
        );
    }
    else if (startsWith(type, "std::variant<")) {
        std::string_view subtypes = type.substr("std::variant<"sv.size());
        if (subtypes.find('>') == std::string_view::npos) {
            // I don't think this can actually fire as it gets tested in the parsing step
            throw ParsingError(fmt::format(
                "Could not find closing > in variant definition: {}", type
            ));
        }
        assert(subtypes.back() == '>');

        std::string result = "new OrVerifier({";

        std::vector<std::string_view> types = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : types) {
            result += verifier(subtype, var, currentStruct) + ',';
        }

        // Remove the final ,
        result.pop_back();

        result += "})";
        return result;
    }
    else if (startsWith(type, "std::map<")) {
        std::string_view subtypes = type.substr("std::map<"sv.size());
        if (subtypes.find('>') == std::string_view::npos) {
            // I don't think this can actually fire as it gets tested in the parsing step
            throw ParsingError(fmt::format(
                "Could not find closing > in map definition: {}", type
            ));
        }
        assert(subtypes.back() == '>');
        std::vector<std::string_view> types = extractTemplateTypeList(subtypes);
        assert(types.size() == 2);
        if (types[0] != "std::string" || types[1] != "std::string") {
            throw SpecificationError(fmt::format(
                "Currently, only 'std::string's are allowed as key and value types for "
                "maps. Found: <{}, {}>", types[0], types[1]
            ));
        }

        return  "new TableVerifier({{\"*\", new StringVerifier, Optional::No }})\n";
    }
    else {
        const StackElement* e = resolveType(currentStruct, type);
        if (!e) {
            throw ParsingError(fmt::format(
                "Type detected that codegen doesn't know how to handle: {}", type
            ));
        }

        return fmt::format("codegen_{}_{}", fqn(currentStruct, "_"), type);
    }
}

std::string writeEnumDocumentation(Enum* e) {
    std::string result = fmt::format(
        "    std::shared_ptr<StringInListVerifier> codegen_{} = std::make_shared<StringInListVerifier>(std::vector<std::string>{{",
        fqn(e, "_")
    );

    Enum* en = static_cast<Enum*>(e);
    for (EnumElement* em : en->elements) {
        // If no key attribute is specified, we use the name instead
        std::string key =
            em->attributes.key.empty() ?
            fmt::format("\"{}\"", em->name) :
            em->attributes.key;
        result += fmt::format("{},", key);
    }
    // The last element has a , at the end that we can overwrite
    result.pop_back();
    result += "});\n";

    return result;
}

std::string writeVariableDocumentation(Struct* s, Variable* var) {
    var->comment = resolveComment(var->comment);

    std::string_view type = var->typeString;
    bool isOptional;
    if (startsWith(var->typeString, "std::optional<")) {
        isOptional = true;
        type.remove_prefix("std::optional<"sv.size());
        type.remove_suffix(1);
    }
    else {
        isOptional = false;
    }

    std::string ver = fqn(s, "_");
    std::string v = verifier(type, *var, s);
    std::string result = fmt::format(
        "    codegen_{}->documentations.push_back({{{},{},{},{}}});\n",
        ver, var->key, v, isOptional ? "Optional::Yes" : "Optional::No", var->comment
    );
    return result;
}

std::string writeStructDocumentation(Struct* s) {
    std::string name = fqn(s, "_");
    std::string result;
    if (s->parent) {
        result = fmt::format(
            "    std::shared_ptr<TableVerifier> codegen_{} = std::make_shared<TableVerifier>();\n", name
        );
    }
    else {
        // root struct
        result = fmt::format(
            "    TableVerifier codegen_{0}_content;\n"
            "    TableVerifier* codegen_{0} = &codegen_{0}_content;\n"
            , name
        );
    }

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

std::string writeVariableConverter(Variable* var, std::vector<std::string>& converters) {
    std::string result;
    if (const size_t p = var->typeString.find("std::variant"); p != std::string::npos) {
        std::string subtypes = var->typeString.substr(p + "std::variant<"sv.size());

        if (std::find(converters.begin(), converters.end(), subtypes) != converters.end())
        {
            return result;
        }

        converters.push_back(subtypes);

        std::string_view fullType = var->typeString;
        if (startsWith(fullType, "std::optional<")) {
            fullType.remove_prefix("std::optional<"sv.size());
            fullType.remove_suffix(">"sv.size());
        }

        result = fmt::format(
            "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n",
            fullType
        );

        int nVectorTypes = 0;
        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            std::string_view originalSubtype = subtype;
            bool isVectorType = false;
            if (startsWith(subtype, "std::vector<")) {
                subtype.remove_prefix("std::vector<"sv.size());
                subtype.remove_suffix(">"sv.size());
                nVectorTypes += 1;
                isVectorType = true;
            }
            if (nVectorTypes > 1) {
                throw SpecificationError(fmt::format(
                    "We can't have a variant containing multiple vector types, try a "
                    "vector of variants instead\n{}", var->typeString
                ));
            }

            std::string_view conv = variantConversionFunctionForType(subtype);

            if (conv.empty()) {
                throw SpecificationError(fmt::format(
                    "Unsupported type '{}' found in variant list\n{}",
                    subtype, var->typeString
                ));
            }

            if (isVectorType) {
                result += vectorBakeFunctionForType(originalSubtype);
            }
            else {
                result += conv;
            }
        }

        result += "    // Any of the previous values should have triggered and returned\n";
        result += "    // If this assert triggers, something in the codegen went wrong\n";
        result += "    assert(false);\n";
        result += "}\n";
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
        // If there is no explicit key, we need to use the name, but surround it with "
        std::string key =
            elem->attributes.key.empty() ?
            fmt::format("\"{}\"", elem->name) :
            elem->attributes.key;

        std::string type = fqn(e, "::");
        result += fmt::format(
            "    if (v == {}) {{ *val = {}::{}; }}\n", key, type, elem->name
        );
    }
    result += "}\n";

    return result;
}

std::string writeStructConverter(Struct* s) {
    std::string result;
    std::vector<std::string> writtenVariantConverters;
    for (Variable* var : s->variables) {
        result += writeVariableConverter(var, writtenVariantConverters);
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
            "    internal::bakeTo(dict, {}, &res.{});\n", var->key, var->name
        );
    }

    result += "}\n";
    return result;
}

std::string emitWarningsForDocumentationLessTypes(Struct* s) {
    std::string res;
    for (Variable* var : s->variables) {
        if (var->comment.empty()) {
#ifdef WIN32
            std::string identifier = var->name;
            Struct* str = s;
            while (str) {
                identifier = str->name + "." + identifier;
                str = str->parent;
            }
            const Struct* root = rootStruct(s);

            res += fmt::format(
                "#pragma message(\"{}: [CODEGEN] {} is not documented\")\n",
                root->sourceFile, identifier
            );
#endif // WIN32
        }
    }
    return res;
}

std::string generateResult(Struct* s) {
    std::string result = fmt::format(FileHeader);

    result += fmt::format(DocumentationPreamble, s->name);

    if (GenerateWarningsForDocumentationLessTypes) {
        result += emitWarningsForDocumentationLessTypes(s);
    }

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
        if (t == "std::map") {
            result += BakeFunctionMapDeclaration;
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

    for (std::string_view type : types) {
        if (type != "std::vector" && type != "std::optional" && type != "std::map") {
            // These types were covered higher up
            continue;
        }

        std::string_view bake = bakeFunctionForType(type);
        assert(!bake.empty());
        result += bake;
    }

    result += fmt::format(
        R"(
}} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) {{ static_assert(sizeof(T) == 0); }}
template <> {0} bake<{0}>(const ghoul::Dictionary& dict) {{
    openspace::documentation::testSpecificationAndThrow(codegen::doc<{0}>(), dict, "{1}");
    {0} res;
)",
        s->name, s->attributes.dictionary
);

    for (Variable* var : s->variables) {
        result += fmt::format(
            "    internal::bakeTo(dict, {}, &res.{});\n", var->key, var->name
        );
    }

    result += "    return res;\n}\n} // namespace codegen\n";
    return result;
}

std::string createClickableFileName(std::string filename) {
    for (size_t i = 0; i < filename.size(); ++i) {
        if (filename[i] == '\\') {
            filename.insert(filename.begin() + i, '\\');
            i += 1;
        }
    }

    return filename;
}

std::string handleCode(std::string_view code, std::string_view path) {
    Struct* rootStruct = parseRootStruct(code);
    if (rootStruct) {
        rootStruct->sourceFile = createClickableFileName(std::string(path));
        std::string genContent = generateResult(rootStruct);
        return genContent;
    }
    else {
        return std::string();
    }
}

Result handleFile(std::filesystem::path path) {
    std::ifstream f(path);
    std::string res = std::string(std::istreambuf_iterator<char>{f}, {});
    f.close();


    std::string p = path.string();
    Struct* rootStruct = parseRootStruct(res);
    if (!rootStruct) {
        return Result::NotProcessed;
    }
    rootStruct->sourceFile = createClickableFileName(path.string());

    std::string content = generateResult(rootStruct);
    if (content.empty()) {
        return Result::NotProcessed;
    }

    std::filesystem::path destination = path;
    destination.replace_extension();
    destination.replace_filename(destination.filename().string() + "_codegen.cpp");

    bool shouldWriteFile;
    if (std::filesystem::exists(destination)) {
        std::ifstream f(destination);
        std::string prev = std::string(std::istreambuf_iterator<char>{f}, {});
        shouldWriteFile = (prev != content);
    }
    else {
        shouldWriteFile = true;
    }

    std::filesystem::path debugDestination = destination;
    debugDestination.replace_extension();
    debugDestination.replace_filename(debugDestination.filename().string() + "_debug.cpp");
    if (shouldWriteFile && PreventFileChange) {
        std::ofstream output(debugDestination);
        output.write(content.data(), content.size());

        throw CodegenError(fmt::format(
            "Asked to prevent file change, but file change detected in '{}'",
            path.filename().string()
        ));
    }

    if (shouldWriteFile || AlwaysOutputFiles) {
        print("Processed file '%s'\n", path.filename().string().c_str());

        std::ofstream r(destination);
        r.write(content.data(), content.size());

        std::filesystem::remove(debugDestination);
        return Result::Processed;
    }
    else {
        std::filesystem::remove(debugDestination);
        return Result::Skipped;
    }
}
