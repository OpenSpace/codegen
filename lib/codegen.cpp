/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2024                                                               *
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
#include <numeric>
#include <string>
#include <vector>

using namespace std::literals;

// Set this value to true if you want to prevent changes to files during code refactoring
constexpr bool PreventFileChange = false;

namespace {
    std::vector<const VariableType*> usedTypes(const VariableType* var) {
        assert(var);
        std::vector<const VariableType*> res;
        res.push_back(var);

        switch (var->tag) {
            case VariableType::Tag::BasicType:
            case VariableType::Tag::PointerType:
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
            case VariableType::Tag::ArrayType: {
                const ArrayType* vt = static_cast<const ArrayType*>(var);
                std::vector<const VariableType*> v1 = usedTypes(vt->type);
                res.insert(res.end(), v1.begin(), v1.end());
                break;
            }
            case VariableType::Tag::VectorType: {
                const VectorType* vt = static_cast<const VectorType*>(var);
                std::vector<const VariableType*> v1 = usedTypes(vt->type);
                res.insert(res.end(), v1.begin(), v1.end());
                break;
            }
            case VariableType::Tag::TupleType: {
                const TupleType* vt = static_cast<const TupleType*>(var);
                for (VariableType* v : vt->types) {
                    assert(v);
                    std::vector<const VariableType*> v1 = usedTypes(v);
                    res.insert(res.end(), v1.begin(), v1.end());
                }
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

            const Struct& str = static_cast<const Struct&>(*e);
            std::vector<const VariableType*> t = usedTypes(str);
            res.insert(res.end(), t.begin(), t.end());
        }


        return res;
    }

    std::vector<const VariableType*> usedTypes(const std::vector<Struct*>& structs) {
        std::vector<const VariableType*> res;

        for (Struct* s : structs) {
            std::vector<const VariableType*> r = usedTypes(*s);
            res.insert(res.end(), r.begin(), r.end());
        }

        // Remove duplicates
        for (int i = 0; i < static_cast<int>(res.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(res.size()); j++) {
                if (*res[i] == *res[j]) {
                    res.erase(res.begin() + j);
                    i--;
                    break;
                }
            }
        }

        return res;
    }

    std::vector<Enum*> mappedEnums(const Struct& s) {
        std::vector<Enum*> res;
        for (StackElement* se : s.children) {
            if (se->type == StackElement::Type::Enum) {
                Enum* e = static_cast<Enum*>(se);
                if (!e->attributes.mappedTo.empty()) {
                    res.push_back(e);
                }
            }

            if (se->type == StackElement::Type::Struct) {
                Struct* str = static_cast<Struct*>(se);
                std::vector<Enum*> subRes = mappedEnums(*str);
                res.insert(res.end(), subRes.begin(), subRes.end());
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
            const std::string argument = comment.substr(it, end - it);
            comment = argument;
        }
        else {
            if (const size_t jt = comment.find('"');
                jt != std::string::npos && comment[jt - 1] != '\\')
            {
                comment.insert(jt, "\\");
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

    std::vector<Enum*> collectEnums(Struct* s) {
        std::vector<Enum*> res;
        for (StackElement* se : s->children) {
            switch (se->type) {
            case StackElement::Type::Struct:
            {
                std::vector<Enum*> e = collectEnums(static_cast<Struct*>(se));
                res.insert(res.end(), e.begin(), e.end());
                break;
            }
            case StackElement::Type::Enum:
                res.push_back(static_cast<Enum*>(se));
                break;
            }
        }
        return res;
    }

    std::vector<Enum*> collectEnums(const Code& code) {
        std::vector<Enum*> res = code.enums;

        for (Struct* s : code.structs) {
            std::vector<Enum*> e = collectEnums(s);
            res.insert(res.end(), e.begin(), e.end());
        }

        return res;
    }
} // namespace

std::string verifier(VariableType* type, const Variable& var, Struct* currentStruct) {
    assert(type);
    assert(currentStruct);

    if (type->tag == VariableType::Tag::BasicType) {
        BasicType* bt = static_cast<BasicType*>(type);
        const std::string v = verifierForType(bt->type, var.attributes);
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

    for (EnumElement* em : e->elements) {
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

std::string writeVariantConverter(Variable* var, std::vector<std::string>& converters) {
    VariableType* type = var->type;
    if (var->type->tag == VariableType::Tag::OptionalType) {
        // For this case, we don't care about whether the variant is wrapped in an
        // optional.  The converter code generated for the optional<T> will call the code
        // generated here.  So we basically just unwrap the optional type here
        OptionalType* ot = static_cast<OptionalType*>(var->type);
        type = ot->type;
    }

    if (type->tag != VariableType::Tag::VariantType) {
        // No need to even look at non-variant types here
        return "";
    }
    VariantType* variantType = static_cast<VariantType*>(type);

    std::string typeString = generateTypename(type, true);
    if (std::find(converters.begin(), converters.end(), typeString) != converters.end()) {
        // This check will trigger if we are using the same type of variant for multiple
        // variables in the same struct.  If that is the case, we only want to emit the
        // conversion code once, or else we would get a multiply defined function
        // definition compile error
        return "";
    }
    converters.push_back(typeString);

    std::string result = fmt::format(
        "[[maybe_unused]] "
        "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n",
        typeString
    );

    for (VariableType* t : variantType->types) {
        const std::string typeName = generateTypename(t);

        const bool isEnumType =
            t->isCustomType() &&
            static_cast<CustomType*>(t)->type->type == StackElement::Type::Enum;
        if (t->isVectorType()) {
            const std::string bakeFunction = vectorBakeFunctionForType(typeName);
            result += bakeFunction;
        }
        else if (isEnumType) {
            const std::string fqnType = fqn(static_cast<CustomType*>(t)->type, "::");
            const std::string bakeFunction = enumBakeFunctionForType(fqnType);
            result += bakeFunction;
        }
        else {
            const std::string_view convFunc = variantConversionFunctionForType(typeName);
            assert(!convFunc.empty());
            result += convFunc;
        }
    }

    result += "    // Any of the previous values should have triggered and returned\n";
    result += "    // If this assert triggers, something in the codegen went wrong\n";
    result += "    assert(false);\n";
    result += "}\n";
    return result;
}

std::string writeInnerEnumConverter(Enum* e) {
    std::string type = fqn(e, "::");
    std::string result = fmt::format(
        "[[maybe_unused]] "
        "void bakeTo(const ghoul::Dictionary & d, std::string_view key, {}*val) {{\n"
        "    std::string v = d.value<std::string>(key);\n",
        type
    );

    for (EnumElement* elem : e->elements) {
        assert(elem);
        std::string typeStr = fqn(e, "::");
        assert(!elem->attributes.key.empty());
        result += fmt::format(
            "    if (v == {}) {{ *val = {}::{}; }}\n",
            elem->attributes.key, typeStr, elem->name
        );
    }
    result += "}\n";

    return result;
}

std::string writeStructConverter(Struct* s) {
    assert(s);
    std::string result;
    std::vector<std::string> writtenVariantConverters;

    for (StackElement* e : s->children) {
        assert(e);
        if (e->type == StackElement::Type::Struct) {
            result += writeStructConverter(static_cast<Struct*>(e));
        }

        if (e->type == StackElement::Type::Enum) {
            result += writeInnerEnumConverter(static_cast<Enum*>(e));
        }
    }

    for (Variable* var : s->variables) {
        assert(var);
        result += writeVariantConverter(var, writtenVariantConverters);
    }

    if (s->parent == nullptr) {
        return result;
    }

    std::string name = fqn(s, "::");
    result += fmt::format(R"(template <> [[maybe_unused]] void bakeTo<{0}>(const ghoul::Dictionary& d, std::string_view key, {0}* val) {{
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

std::string emitWarningsForDocumentationLessTypes(Struct* s, std::string_view sourceFile)
{
    assert(s);

    std::string res;
    for (Variable* var : s->variables) {
        assert(var);
        if (var->comment.empty()) {
            std::string identifier = fmt::format("{}.{}", fqn(s, "."), var->name);
            std::string message = fmt::format(
                "\"{}: [CODEGEN] {} is not documented\"", sourceFile, identifier
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

std::string writeRootEnumConverter(Enum* e) {
    assert(e);

    std::string res;

    // toString
    res += fmt::format(R"(
template <> [[maybe_unused]] std::string_view toString<{0}>({0} t) {{
    switch (t) {{
)",
        fqn(e, "::")
    );
    for (EnumElement* elem : e->elements) {
        res += fmt::format(
            "        case {0}::{1}: return {2};\n",
            fqn(e, "::"), elem->name, elem->attributes.key
        );
    }
    res += R"(        default: throw "This default label is not necessary since the case labels are "
                       "exhaustive, but not having it makes Visual Studio cranky";)";
    res += "\n    }\n}\n";

    // fromString
    res += fmt::format(
        "template <> [[maybe_unused]] {0} fromString<{0}>(std::string_view sv) {{\n",
        fqn(e, "::")
    );
    for (EnumElement* elem : e->elements) {
        res += fmt::format("    if (sv == {0}) {{ return {1}::{2}; }}\n",
            elem->attributes.key, fqn(e, "::"), elem->name
        );
    }
    res += "    throw std::runtime_error(\"Could not find value in enum\");\n";
    res += "}\n";

    res += fmt::format(BakeEnum, fqn(e, "::"));

    return res;
}

std::string generateStructsResult(const Code& code, bool& hasWrittenMappingFallback) {
    // For Linux, we need to declare the functions in the following order or the overload
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

    std::string result;
    result += "namespace codegen {\n\n";
    result += DocumentationFallback;

    for (Struct* s : code.structs) {
        result += fmt::format(DocumentationPreamble, s->name);

        if (GenerateWarningsForDocumentationLessTypes) {
            result += emitWarningsForDocumentationLessTypes(s, code.sourceFile);
        }

        result += writeStructDocumentation(s);
        result += fmt::format(
            DocumentationEpilog,
            s->attributes.dictionary, s->name, s->comment
        );
    }

    result += "namespace internal {\n\n";
    result += BakeToFunctionFallback;
    result += "\n\n";

    const std::vector<const VariableType*> types = usedTypes(code.structs);
    bool hasOptionalType = false;
    bool hasVectorType = false;
    bool hasMapType = false;
    for (const VariableType* t : types) {
        assert(t);
        hasOptionalType |= t->isOptionalType();
        hasVectorType |= t->isVectorType();
        hasMapType |= t->isMapType();
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
        if (t->isBasicType()) {
            const BasicType* bt = static_cast<const BasicType*>(t);
            result += bakeFunctionForType(bt->type);
        }
    }

    for (Struct* s : code.structs) {
        result += writeStructConverter(s);
    }

    if (hasOptionalType) {
        result += BakeFunctionOptional;
    }
    if (hasVectorType) {
        result += BakeFunctionVector;
    }
    if (hasMapType) {
        result += BakeFunctionMap;
    }

    result += "\n} // namespace internal\n\n";
    result += BackFunctionFallback;
    result += '\n';

    for (Struct* s : code.structs) {
        result += fmt::format(BakeStructPreamble, s->name, s->attributes.dictionary);

        for (Variable* var : s->variables) {
            result += fmt::format(
                "    internal::bakeTo(dict, {}, &res.{});\n", var->key, var->name
            );
        }

        result += "    return res;\n}\n";

        const std::vector<Enum*> enums = mappedEnums(*s);
        if (!enums.empty() && !hasWrittenMappingFallback) {
            result += MapFunctionFallback;
            result += '\n';
            hasWrittenMappingFallback = true;
        }

        for (Enum* e : enums) {
            result += enumToEnumMapping(e);
        }
    }

    result += "\n} // namespace codegen\n\n";
    return result;
}

std::string generateEnumResult(const Code& code, bool& hasWrittenMappingFallback,
                               bool& hasWrittenArrayFallback)
{
    const std::vector<Enum*> enums = collectEnums(code);

    // If there are no enums, we can bail out
    if (enums.empty()) {
        return "";
    }

    std::string result;
    result += "namespace codegen {\n";
    result += BakeEnumFallback;
    result += '\n';
    result += ToStringFallback;
    result += '\n';
    result += FromStringFallback;
    result += '\n';


    for (Enum* e : code.enums) {
        result += writeRootEnumConverter(e);

        if (!e->attributes.mappedTo.empty()) {
            if (!hasWrittenMappingFallback) {
                result += MapFunctionFallback;
                result += '\n';
                hasWrittenMappingFallback = true;
            }
            result += enumToEnumMapping(e);
        }

        if (e->attributes.arrayify) {
            if (!hasWrittenArrayFallback) {
                result += ArrayifyFallback;
                result += '\n';
                hasWrittenArrayFallback = true;
            }
            result += enumArrayify(e);
        }
    }

    result += "\n } // namespace codegen\n\n";
    return result;
}

std::string generateLuaFunction(Function* f) {
    assert(f);
    std::string result;
    // Open the Function object declaration
    std::string capitalizedName = f->functionName;
    capitalizedName[0] = static_cast<char>(::toupper(capitalizedName[0]));

    result += fmt::format(LuaWrapperPreamble, capitalizedName);
    result += fmt::format("    \"{}\",\n", f->luaName);

    // The lambda that is executed
    result += "    [](lua_State* L) -> int {\n";

    int nRequiredArguments = 0;
    for (Variable* var : f->arguments) {
        if (!var->type->isOptionalType()) {
            nRequiredArguments += 1;
        }
    }

    // Adding the check for number of variables
    int nTotalArguments = static_cast<int>(f->arguments.size());
    if (nRequiredArguments == nTotalArguments) {
        result += fmt::format(
            "        ghoul::lua::checkArgumentsAndThrow(L, {}, \"{}\");\n",
            nTotalArguments, f->luaName
        );
    }
    else {
        result += fmt::format(
            "        ghoul::lua::checkArgumentsAndThrow(L, {{ {}, {} }}, \"{}\");\n",
            nRequiredArguments, nTotalArguments, f->luaName
        );
    }

    std::vector<Variable*> arguments = f->arguments;
    // If we only have optional arguments, we don't want them to be peeled off from the
    // front, but handle them as a bunch instead
    bool hasOnlyOptional = true;
    for (Variable* var : arguments) {
        if (!var->type->isOptionalType()) {
            hasOnlyOptional = false;
            break;
        }
    }

    // Need to handle optional arguments separately from the regular ones as they have to
    // have an extra check to see if the value exists
    while (!hasOnlyOptional &&
           !arguments.empty() && arguments.front()->type->isOptionalType())
    {
        Variable* var = arguments.front();
        OptionalType* ot = static_cast<OptionalType*>(var->type);

        result += fmt::format(
            LuaWrapperOptionalTypeExtraction,
            generateTypename(ot), var->name, generateLuaExtractionTypename(ot->type)
        );

        // Peel off the argument that we just handled
        arguments.erase(arguments.begin());
    }

    if (!arguments.empty()) {
        std::string names;
        std::string types;
        for (Variable* var : arguments) {
            names += var->name + ", ";
            types += generateLuaExtractionTypename(var->type) + ", ";
        }
        names = names.substr(0, names.size() - 2);
        types = types.substr(0, types.size() - 2);

        result += fmt::format(
            "        auto [{}] = ghoul::lua::values<{}>(L);\n", names, types
        );
    }

    result += "        try {\n";

    // Depending on if we have a return value, we want to be able to capture that value
    result += "            ";
    if (f->returnValue) {
        result += fmt::format("{} res = ", generateTypename(f->returnValue));
    }

    if (f->arguments.empty()) {
        // If there are no arguments to the function, it's pretty simple to just
        // call it
        result += fmt::format("{}();\n", f->functionName);
    }
    else {
        // If there are arguments it might get a bit more complicated since we
        // want to support default initialized arguments.
        result += fmt::format("{}(\n", f->functionName);

        for (size_t i = 0; i < f->arguments.size(); i += 1) {
            Variable* var = f->arguments[i];

            result += "                ";
            if (var->type->isOptionalType() &&
                static_cast<OptionalType*>(var->type)->defaultArgument.has_value())
            {
                OptionalType* ot = static_cast<OptionalType*>(var->type);
                // If there is a default argument, the function actually wants the
                // underlying value, not the std::optional type. We basically check if the
                // original optional value was set; if it was, we derefence it and use it.
                // Otherwise we paste in the stored default value instead.
                //
                // An alternative way would be to not provide the optional argument at
                // all, but that turned out to be much more code and more complicated than
                // just storing the default value
                result += fmt::format(
                    "{0}.has_value() ? std::move(*{0}) : {1}",
                    var->name, *ot->defaultArgument
                );
            }
            else if (var->type->containsCustomType()) {
                // We have extracted this type as a ghoul::Dictionary previously, and need
                // to bake it into the correct type here instead
                result += fmt::format(
                    "codegen::bake<{0}>({1})",
                    generateTypename(var->type), var->name
                );
            }
            else {
                result += fmt::format("std::move({})", var->name);
            }

            if (i != f->arguments.size() - 1) {
                result += ',';
            }
            result += '\n';
        }
        result += "            );\n";
    }

    if (f->returnValue) {
        if (f->returnValue->isTupleType()) {
            result += "            int nArguments = 0;\n";
            TupleType* tt = static_cast<TupleType*>(f->returnValue);
            assert(!tt->types.empty());
            for (size_t i = 0; i < tt->types.size(); i += 1) {
                if (tt->types[i]->isOptionalType()) {
                    result += fmt::format(LuaWrapperPushTupleOptional, i);
                }
                else {
                    result += fmt::format(LuaWrapperPushTupleRegular, i);
                }
            }
            result += "            return nArguments;\n";
        }
        else if (f->returnValue->isOptionalType()) {
            result += LuaWrapperPushOptional;
        }
        else if (f->returnValue->isVariantType()) {
            VariantType* vt = static_cast<VariantType*>(f->returnValue);
            for (VariableType* v : vt->types) {
                result += fmt::format(LuaWrapperPushVariant, generateTypename(v));
            }
            result += "            return 1;\n";
        }
        else if (f->returnValue->isCustomType()) {
            CustomType* vt = static_cast<CustomType*>(f->returnValue);

            switch (vt->type->type) {
                case StackElement::Type::Struct: {
                    const Struct* s = static_cast<const Struct*>(vt->type);

                    result += "            lua_newtable(L);\n";
                    for (Variable* var : s->variables) {
                        result += fmt::format(
                            "            ghoul::lua::push(L, \"{0}\", std::move(res.{0}));\n",
                            var->name
                        );
                        result += "            lua_settable(L, -3);\n";
                    }
                    result += '\n';
                    result += "            return 1;\n";
                    break;
                }
                case StackElement::Type::Enum: {
                    result += "            ghoul::lua::push(L, codegen::toString(res));\n";
                    result += "            return 1;\n";
                    break;
                }
            }
        }
        else {
            result += "            ghoul::lua::push(L, std::move(res));\n";
            result += "            return 1;\n";
        }
    }
    else {
        result += "            return 0;\n";
    }

    result += "        }\n";
    result += "        catch (const ghoul::lua::LuaError& e) {\n";
    result += "            return ghoul::lua::luaError(L, e.message);\n";
    result += "        }\n";

    result += "    },\n";


    // Argument description
    std::string argumentsDesc = "{\n";
    for (Variable* var : f->arguments) {
        argumentsDesc += fmt::format(
            R"(        {{ "{}", "{}")", var->name, generateDescriptiveTypename(var->type)
        );

        if (var->type->isOptionalType() &&
            static_cast<OptionalType*>(var->type)->defaultArgument.has_value())
        {
            OptionalType* ot = static_cast<OptionalType*>(var->type);
            std::string defaultArgument = *ot->defaultArgument;
            for (size_t i = 0; i < defaultArgument.size(); i += 1) {
                if (defaultArgument[i] == '\\' || defaultArgument[i] == '"') {
                    defaultArgument.insert(defaultArgument.begin() + i, '\\');
                    i += 1;
                }
                if (defaultArgument[i] == '\n') {
                    defaultArgument.erase(defaultArgument.begin() + i);
                    i -= 1;
                }
            }
            argumentsDesc += fmt::format(", \"{}\"", defaultArgument);
        }

        argumentsDesc += " },\n";

    }
    if (!f->arguments.empty()) {
        // Remove the closing ", "
        argumentsDesc = argumentsDesc.substr(0, argumentsDesc.size() - 1);
    }

    result += "    " + argumentsDesc + "\n    },\n";

    result += fmt::format(
        "    \"{}\",\n", f->returnValue ? generateDescriptiveTypename(f->returnValue) : ""
    );

    // Documentation
    result += fmt::format(R"(    R"[({})[")", f->documentation) + ",\n";

    // Source location
    if (f->sourceLocation.file.empty()) {
        // The `sourceLocation.file` is empty for all of the unit tests where we call the
        // `parse` function manually, so that not filename exists
        result += fmt::format("    {{ \"<null>\", {} }}\n", f->sourceLocation.line);
    }
    else {
        // `sourceLocation.file` is the full path to the file, but we only want to store
        // the path relative to the working directory
        result += fmt::format(
            "    {{ \"{}\", {} }}\n",
            f->sourceLocation.file,
            f->sourceLocation.line
        );
    }

    result += "};\n\n";

    return result;
}

std::string generateLuaWrapperResult(const Code& code) {
    std::string result;

    result += "namespace codegen {\n";
    // The Lua wrapping functions require a bit more of the conversions, like being
    // able to return them wrapped in an optional, vector, etc, so we need to enhance
    // the `bake` function to be able to take care of those types if they arise
    bool hasCustomInMap = false;
    bool hasCustomInOptional = false;
    bool hasCustomInVector = false;

    auto updateState = [&](VariableType* var) {
        if (!var) {
            return;
        }
        hasCustomInMap |= var->isMapType() && var->containsCustomType();
        hasCustomInOptional |= var->isOptionalType() && var->containsCustomType();
        hasCustomInVector |= var->isVectorType() && var->containsCustomType();
    };

    for (Function* f : code.luaWrapperFunctions) {
        updateState(f->returnValue);

        for (Variable* var : f->arguments) {
            updateState(var->type);
        }
    }

    // First, we need to define the declarations to handle all of the cases
    result += hasCustomInMap ? BakeCustomMapDeclaration : "";
    result += hasCustomInOptional ? BakeCustomOptionalDeclaration : "";
    result += hasCustomInVector ? BakeCustomVectorDeclaration : "";

    // Then we can define them properly
    result += hasCustomInMap ? BakeCustomMap : "";
    result += hasCustomInOptional ? BakeCustomOptional : "";
    result += hasCustomInVector ? BakeCustomVector : "";

    result += "} // namespace codegen\n\n";

    result += "namespace codegen::lua {\n\n";

    for (Function* f : code.luaWrapperFunctions) {
        result += generateLuaFunction(f);
    }

    result += "} // namespace codegen::lua\n";
    return result;
}

std::string generateResult(const Code& code) {
    assert(
        !code.structs.empty() ||
        !code.enums.empty() ||
        !code.luaWrapperFunctions.empty()
    );

    std::string result = std::string(FileHeader);

    bool hasWrittenMappingFallback = false;
    bool hasWrittenArrayifyFallback = false;
    if (!code.structs.empty()) {
        result += generateStructsResult(code, hasWrittenMappingFallback);
    }

    // We can't just check on empty code.enum since there might be enums hiding in structs
    result += generateEnumResult(
        code,
        hasWrittenMappingFallback,
        hasWrittenArrayifyFallback
    );

    if (!code.luaWrapperFunctions.empty()) {
        result += generateLuaWrapperResult(code);
    }

    return result;
}

std::string createClickableFileName(std::string filename) {
    for (size_t i = 0; i < filename.size(); i++) {
        if (filename[i] == '\\') {
            filename.insert(filename.begin() + i, '\\');
            i += 1;
        }
    }
    return filename;
}

Result handleFile(std::filesystem::path path) {
    std::ifstream file(path);
    std::string res = std::string(std::istreambuf_iterator<char>(file), {});
    file.close();


    const std::string p = path.string();
    Code code = parse(std::move(res), p);
    if (code.structs.empty() && code.enums.empty() && code.luaWrapperFunctions.empty()) {
        return Result::NotProcessed;
    }
    code.sourceFile = createClickableFileName(path.string());

    std::string content = generateResult(code);
    if (content.empty()) {
        return Result::NotProcessed;
    }

    std::filesystem::path destination = path;
    destination.replace_extension();
    destination.replace_filename(destination.filename().string() + "_codegen.cpp");

    bool shouldWriteFile = true;
    if (std::filesystem::exists(destination)) {
        std::ifstream f = std::ifstream(destination);
        const std::string prev = std::string(std::istreambuf_iterator<char>{f}, {});
        shouldWriteFile = (prev != content);
    }

    if (PreventFileChange && shouldWriteFile) {
        throw CodegenError(fmt::format("File '{}' changed", path.filename().string()));
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
