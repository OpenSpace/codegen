/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2022                                                               *
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


        return res;
    }
    
    std::vector<const VariableType*> usedTypes(const std::vector<Struct*> structs) {
        std::vector<const VariableType*> res;

        for (Struct* s : structs) {
            std::vector<const VariableType*> r = usedTypes(*s);
            res.insert(res.end(), r.begin(), r.end());
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

    std::vector<Enum*> mappedEnums(const Struct& s) {
        std::vector<Enum*> res;
        for (StackElement* se : s.children) {
            if (se->type == StackElement::Type::Enum) {
                Enum* e = static_cast<Enum*>(se);
                if (!e->mappedTo.empty()) {
                    res.push_back(e);
                }
            }

            if (se->type == StackElement::Type::Struct) {
                Struct* s = static_cast<Struct*>(se);
                std::vector<Enum*> subRes = mappedEnums(*s);
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
        std::string type = generateTypename(t);
        
        const bool isVectorType = t->tag == VariableType::Tag::VectorType;
        const bool isEnumType =
            t->tag == VariableType::Tag::CustomType &&
            static_cast<CustomType*>(t)->type->type == StackElement::Type::Enum;
        if (isVectorType) {
            std::string bakeFunction = vectorBakeFunctionForType(type);
            result += bakeFunction;
        }
        else if (isEnumType) {
            std::string fqnType = fqn(static_cast<CustomType*>(t)->type, "::");
            std::string bakeFunction = enumBakeFunctionForType(fqnType);
            result += bakeFunction;
        }
        else {
            std::string_view conversionFunction = variantConversionFunctionForType(type);
            assert(!conversionFunction.empty());
            result += conversionFunction;
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
    const Struct* root = rootStruct(s);
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
    assert(e->parent == nullptr);

    std::string res;

    // toString
    res += fmt::format(R"(
template <> [[maybe_unused]] std::string_view toString<{0}>({0} t) {{
    switch (t) {{ 
)",
        e->name
    );
    for (EnumElement* elem : e->elements) {
        res += fmt::format(
            "        case {0}::{1}: return {2};\n", e->name, elem->name, elem->attributes.key
        );
    }
    res += R"(        default: throw "This default label is not necessary since the case labels are "
                       "exhaustive, but not having it makes Visual Studio cranky";)";
    res += "\n    }\n}\n";

    // fromString
    res += fmt::format(
        "template <> [[maybe_unused]] {0} fromString<{0}>(std::string_view sv) {{\n",
        e->name
    );
    for (EnumElement* elem : e->elements) {
        res += fmt::format("    if (sv == {0}) {{ return {1}::{2}; }}\n",
            elem->attributes.key, e->name, elem->name
        );
    }
    res += "    throw std::runtime_error(\"Could not find value in enum\");\n";
    res += "}\n";

    return res;
}

std::string generateResult(const Code& code) {
    assert(
        !code.structs.empty() ||
        !code.enums.empty() ||
        !code.luaWrapperFunctions.empty()
    );

    std::string result = FileHeader;


    if (!code.structs.empty()) {
        result += "namespace codegen {\n";
        result += DocumentationFallback;

        for (Struct* s : code.structs) {
            result += fmt::format(DocumentationPreamble, s->name);

            if (GenerateWarningsForDocumentationLessTypes) {
                result += emitWarningsForDocumentationLessTypes(s, code.sourceFile);
            }

            result += writeStructDocumentation(s);
            result += fmt::format(DocumentationEpilog, s->attributes.dictionary, s->name);
        }
        result += "} // namespace codegen\n";
    }

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

    result += "\nnamespace codegen {\n";

    bool hasWrittenMappingFallback = false;
    
    if (!code.structs.empty()) {
        result += "namespace internal { \n";
        result += BakeFunctionFallback;
        result += '\n';

        std::vector<const VariableType*> types = usedTypes(code.structs);
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

        result += R"(
} // namespace internal

template <typename T> [[maybe_unused]] T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }
)";

        for (Struct* s : code.structs) {
            result += fmt::format(
                R"(
template <> [[maybe_unused]] {0} bake<{0}>(const ghoul::Dictionary& dict) {{
    openspace::documentation::testSpecificationAndThrow(codegen::doc<{0}>("{0}"), dict, "{1}");
    {0} res;
)",
s->name, s->attributes.dictionary
);

            for (Variable* var : s->variables) {
                result += fmt::format(
                    "    internal::bakeTo(dict, {}, &res.{});\n", var->key, var->name
                );
            }

            result += "    return res;\n}\n";

            std::vector<Enum*> enums = mappedEnums(*s);
            if (!enums.empty() && !hasWrittenMappingFallback) {
                result += MapFunctionFallback;
                result += '\n';
                hasWrittenMappingFallback = true;
            }

            for (Enum* e : enums) {
                result += enumToEnumMapping(e);
            }
        }

        result += '\n';
    }

    if (!code.enums.empty()) {
        result += ToStringFallback;
        result += '\n';
        result += FromStringFallback;
        result += '\n';

        for (Enum* e : code.enums) {
            result += writeRootEnumConverter(e);

            if (!e->mappedTo.empty()) {
                if (!hasWrittenMappingFallback) {
                    result += MapFunctionFallback;
                    result += '\n';
                    hasWrittenMappingFallback = true;
                }
                result += enumToEnumMapping(e);
            }
        }
    }

    if (!code.luaWrapperFunctions.empty()) {
        result += "namespace lua {\n\n";

        for (Function* f : code.luaWrapperFunctions) {
            // Open the Function object declaration
            result += fmt::format(
                "static const openspace::scripting::LuaLibrary::Function {} = {{\n",
                f->name
            );

            // Name of the function
            result += fmt::format("    \"{}\",\n", f->name);

            // The lambda that is executed
            result += "    [](lua_State* L) -> int {\n";

            int nRequiredArguments = 0;
            for (Variable* var : f->arguments) {
                if (var->type->tag == VariableType::Tag::OptionalType) {
                    // We passed into the optional phase
                    break;
                }
                nRequiredArguments += 1;
            }

            // Adding the check for number of variables
            int nTotalArguments = static_cast<int>(f->arguments.size());
            if (nRequiredArguments == nTotalArguments) {
                result += fmt::format(
                    "        ghoul::lua::checkArgumentsAndThrow(L, {}, \"{}\");\n",
                    nTotalArguments, f->name
                );
            }
            else {
                result += fmt::format(
                    "        ghoul::lua::checkArgumentsAndThrow(L, {{ {}, {} }}, \"{}\");\n",
                    nRequiredArguments, nTotalArguments, f->name
                );
            }

            std::string names;
            std::string types;
            for (Variable* var : f->arguments) {
                names += var->name + ", ";
                types += generateTypename(var->type) + ", ";
            }

            // Remove the final ", " from both strings if we have added anything
            if (!f->arguments.empty()) {
                names.pop_back();
                names.pop_back();
                types.pop_back();
                types.pop_back();

                result += fmt::format(
                    "        const auto [{}] = ghoul::lua::values<{}>(L);\n", names, types
                );
            }

            // Depending on if we have a return value at all, we want to be able to
            // capture that value or not
            if (f->returnValue) {
                result += fmt::format(
                    "        const {} res = ", generateTypename(f->returnValue)
                );
            }
            else {
                result += "        ";
            }

            if (f->arguments.empty()) {
                // If there are no arguments to the function, it's pretty simple to just
                // call it
                result += fmt::format("::{}();\n", f->name);
            }
            else {
                // If there are arguments it might get a bit more complicated since we
                // want to support default initialized arguments.
                result += fmt::format("::{}(\n", f->name);
                for (size_t i = 0; i < f->arguments.size(); i += 1) {
                    Variable* var = f->arguments[i];

                    result += "            ";
                    bool hasWrittenValue = false;
                    if (var->type->tag == VariableType::Tag::OptionalType) {
                        OptionalType* ot = static_cast<OptionalType*>(var->type);
                        if (ot->defaultArgument.has_value()) {
                            // If there is a default argument, the function actually wants
                            // the underlying value, not the std::optional type. We
                            // basically check if the original optional value was set; if
                            // it was, we derefence it and use it. Otherwise we paste in
                            // the stored default value instead.
                            //
                            // An alternative way would be to not provide the optional
                            // argument at all, but that turned out to be much more code
                            // and more complicated than just storing the default value

                            result += fmt::format(
                                "{0}.has_value() ? *{0} : {1}",
                                var->name, *ot->defaultArgument
                            );
                            hasWrittenValue = true;
                        }
                    }

                    if (!hasWrittenValue) {
                        result += var->name;
                    }

                    if (i != f->arguments.size() - 1) {
                        result += ',';
                    }
                    result += '\n';
                }
                result += "        );\n";
            }

            if (f->returnValue) {
                int nArguments = 0;
                if (f->returnValue->tag == VariableType::Tag::TupleType) {
                    TupleType* tt = static_cast<TupleType*>(f->returnValue);
                    assert(!tt->types.empty());
                    for (size_t i = 0; i < tt->types.size(); i += 1) {
                        result += fmt::format(
                            "        ghoul::lua::push(L, std::get<{}>(res));\n", i
                        );
                    }
                    nArguments = static_cast<int>(tt->types.size());
                }
                else {
                    result += "        ghoul::lua::push(L, res);\n";
                    nArguments = 1;
                }

                result += fmt::format("        return {};\n", nArguments);
            }
            else {
                result += "        return 0;\n";
            }

            result += "    },\n";


            // Argument description
            std::string arguments;
            for (Variable* var : f->arguments) {
                arguments += fmt::format(
                    "{}: {}, ",
                    var->name, generateDescriptiveTypename(var->type)
                );
            }
            if (!f->arguments.empty()) {
                // Remove the closing ", "
                arguments = arguments.substr(0, arguments.size() - 2);
            }

            if (f->returnValue) {
                arguments += " -> " + generateDescriptiveTypename(f->returnValue);
            }

            result += "    \"" + arguments + "\",\n";

            // Documentation
            result += "    \"" + f->documentation + "\"\n";

            result += "};\n\n";
        }

        result += "} // namespace lua\n";
    }


    result += "} // namespace codegen\n";
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

Result handleFile(std::filesystem::path path) {
    std::ifstream f(path);
    std::string res = std::string(std::istreambuf_iterator<char>{f}, {});
    f.close();


    std::string p = path.string();
    Code code = parse(res);
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
