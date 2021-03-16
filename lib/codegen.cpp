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
#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

namespace {
    std::vector<const VariableType*> usedTypes(const VariableType* var) {
        assert(var);
        std::vector<const VariableType*> res;
        res.push_back(var);

        switch (var->tag) {
            case VariableType::Tag::BasicType:
            case VariableType::Tag::CustomType:
                break;
            case VariableType::Tag::MapType: {
                const MapType* mt = static_cast<const MapType*>(var);
                std::vector<const VariableType*> v1 = usedTypes(mt->keyType);
                std::vector<const VariableType*> v2 = usedTypes(mt->valueType);

                res.insert(res.end(), v1.begin(), v1.end());
                res.insert(res.end(), v2.begin(), v2.end());
                break;
            }
            case VariableType::Tag::OptionalType: {
                const OptionalType* pt = static_cast<const OptionalType*>(var);
                std::vector<const VariableType*> v1 = usedTypes(pt->type);
                res.insert(res.end(), v1.begin(), v1.end());
                break;
            }
            case VariableType::Tag::VariantType: {
                const VariantType* vt = static_cast<const VariantType*>(var);
                for (VariableType* v : vt->types) {
                    assert(v);
                    std::vector<const VariableType*> v1 = usedTypes(v);
                    res.insert(res.end(), v1.begin(), v1.end());
                }
                break;
            }
            case VariableType::Tag::VectorType: {
                const VectorType* vt = static_cast<const VectorType*>(var);
                std::vector<const VariableType*> v1 = usedTypes(vt->type);
                res.insert(res.end(), v1.begin(), v1.end());
                break;
            }
        }

        assert(
            std::none_of(
                res.begin(), res.end(),
                [](const VariableType* v) { return v == nullptr; }
            )
        );
        return res;
    }

    std::vector<const VariableType*> usedTypes(const Struct& s) {
        std::vector<const VariableType*> res;
        for (const Variable* var : s.variables) {
            assert(var);
            std::vector<const VariableType*> v = usedTypes(var->type);
            res.insert(res.end(), v.begin(), v.end());
        }

        for (StackElement* e : s.children) {
            assert(e);
            if (e->type != StackElement::Type::Struct) {
                continue;
            }

            const Struct& s = static_cast<const Struct&>(*e);
            std::vector<const VariableType*> t = usedTypes(s);
            res.insert(res.end(), t.begin(), t.end());
        }

        // Remove duplicates
        for (int i = 0; i < static_cast<int>(res.size()); ++i) {
            for (int j = i + 1; j < static_cast<int>(res.size()); ++j) {
                if (*res[i] == *res[j]) {
                    res.erase(res.begin() + j);
                    i--;
                    break;
                }
            }
        }

        return res;
    }

    std::string resolveComment(std::string comment) {
        if (size_t it = comment.find("codegen::verbatim"); it != std::string::npos) {
            const size_t l = "codegen::verbatim"sv.size();
            it += l;
            if (comment[it] != '(') {
                throw CodegenError(fmt::format(
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
                throw CodegenError(fmt::format(
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

std::string verifier(VariableType* type, const Variable& var, Struct* currentStruct) {
    assert(type);
    assert(currentStruct);

    if (type->tag == VariableType::Tag::BasicType) {
        BasicType* bt = static_cast<BasicType*>(type);
        const Struct* root = rootStruct(currentStruct);
        std::string v = verifierForType(bt->type, var.attributes);
        return "new " + v;
    }
    else if (type->tag == VariableType::Tag::OptionalType) {
        OptionalType* ot = static_cast<OptionalType*>(type);
        return verifier(ot->type, var, currentStruct);
    }
    else if (type->tag == VariableType::Tag::VectorType) {
        VectorType* vt = static_cast<VectorType*>(type);
        const StackElement* e = resolveType(currentStruct, generateTypename(vt->type));
        std::string comments;
        if (e) {
            // e is false for subtypes that are not our own structs
            comments = resolveComment(e->comment);
        }

        std::string ver = verifier(vt->type, var, currentStruct);
        return fmt::format(
            "new TableVerifier({{{{\"*\",{},Optional::Yes, {}}}}})\n", ver, comments
        );
    }
    else if (type->tag == VariableType::Tag::VariantType) {
        VariantType* vt = static_cast<VariantType*>(type);

        std::string result = "new OrVerifier({";

        for (VariableType* v : vt->types) {
            result += verifier(v, var, currentStruct) + ',';
        }

        // Remove the final ,
        result.pop_back();

        result += "})";
        return result;
    }
    else if (type->tag == VariableType::Tag::MapType) {
        MapType* mt = static_cast<MapType*>(type);
        assert(mt->valueType->tag == VariableType::Tag::BasicType);
        BasicType* valueType = static_cast<BasicType*>(mt->valueType);
        const Struct* root = rootStruct(currentStruct);
        std::string valueVerifier = verifierForType(valueType->type, var.attributes);
        return fmt::format(
            "new TableVerifier({{{{\"*\", new {}, Optional::No }}}})\n", valueVerifier
        );
    }
    else if (type->tag == VariableType::Tag::CustomType) {
        CustomType* ct = static_cast<CustomType*>(type);
        assert(ct->type);
        return fmt::format("codegen_{}_{}", fqn(currentStruct, "_"), ct->type->name);
    }
    else {
        throw std::logic_error("Missing case label");
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

    const bool isOptional = var->type->tag == VariableType::Tag::OptionalType;

    std::string ver = fqn(s, "_");
    std::string v = verifier(var->type, *var, s);
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
    // @TODO (abock, 2021-02-03) This function is really ugly and should really be
    // overhauled.  This would include not generating the typename as a string and then
    // reparsing it.  Instead, we can walk the type tree and take out the types directly
    // instead.

    std::string typeString = generateTypename(var->type);
    std::string result;
    if (const size_t p = typeString.find("std::variant"); p != std::string::npos) {
        std::string subtypes = typeString.substr(p + "std::variant<"sv.size());

        if (std::find(converters.begin(), converters.end(), subtypes) != converters.end())
        {
            return result;
        }

        converters.push_back(subtypes);

        std::string_view fullType = typeString;
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
                throw CodegenError(fmt::format(
                    "We can't have a variant containing multiple vector types, try a "
                    "vector of variants instead\n{}", typeString
                ));
            }

            std::string_view conv = variantConversionFunctionForType(subtype);

            if (conv.empty()) {
                throw CodegenError(fmt::format(
                    "Unsupported type '{}' found in variant list\n{}",
                    subtype, typeString
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
        assert(elem);
        std::string type = fqn(e, "::");
        assert(!elem->attributes.key.empty());
        result += fmt::format(
            "    if (v == {}) {{ *val = {}::{}; }}\n",
            elem->attributes.key, type, elem->name
        );
    }
    result += "}\n";

    return result;
}

std::string writeStructConverter(Struct* s) {
    assert(s);
    std::string result;
    std::vector<std::string> writtenVariantConverters;
    for (Variable* var : s->variables) {
        assert(var);
        result += writeVariableConverter(var, writtenVariantConverters);
    }

    for (StackElement* e : s->children) {
        assert(e);
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
    assert(s);

    std::string res;
    const Struct* root = rootStruct(s);
    for (Variable* var : s->variables) {
        assert(var);
        if (var->comment.empty()) {
            std::string identifier = fmt::format("{}.{}", fqn(s, "."), var->name);
            std::string message = fmt::format(
                "\"{}: [CODEGEN] {} is not documented\"", root->sourceFile, identifier
            );
#ifdef WIN32
            res += fmt::format("#pragma message({})\n", message);
#else
            res += fmt::format("#warning {}\n", message);
#endif // WIN32
        }
    }
    return res;
}

std::string generateResult(Struct* s) {
    assert(s);

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

    std::vector<const VariableType*> types = usedTypes(*s);
    bool hasOptionalType = false;
    bool hasVectorType = false;
    bool hasMapType = false;
    for (const VariableType* t : types) {
        assert(t);
        hasOptionalType |= (t->tag == VariableType::Tag::OptionalType);
        hasVectorType |= (t->tag == VariableType::Tag::VectorType);
        hasMapType |= (t->tag == VariableType::Tag::MapType);
    }

    if (hasOptionalType) {
        result += BakeFunctionOptionalDeclaration;
    }
    if (hasVectorType) {
        result += BakeFunctionVectorDeclaration;
    }
    if (hasMapType) {
        result += BakeFunctionMapDeclaration;
    }
    for (const VariableType* t : types) {
        if (t->tag == VariableType::Tag::BasicType) {
            const BasicType* bt = static_cast<const BasicType*>(t);
            result += bakeFunctionForType(bt->type);
        }
    }


    result += writeStructConverter(s);


    if (hasOptionalType) {
        result += BakeFunctionOptional;
    }
    if (hasVectorType) {
        result += BakeFunctionVector;
    }
    if (hasMapType) {
        result += BakeFunctionMap;
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

    std::filesystem::path debugDest = destination;
    debugDest.replace_extension();
    debugDest.replace_filename(debugDest.filename().string() + "_debug.cpp");

    if (shouldWriteFile || ShouldAlwaysWriteFiles) {
        std::cout << fmt::format("Processed file '{}'\n", path.filename().string());

        std::ofstream r(destination);
        r.write(content.data(), content.size());

        std::filesystem::remove(debugDest);
        return Result::Processed;
    }
    else {
        std::filesystem::remove(debugDest);
        return Result::Skipped;
    }
}
