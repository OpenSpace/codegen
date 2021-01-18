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
#include "storage.h"
#include "types.h"
#include "util.h"
#include "verifier.h"
#include <fmt/format.h>
#include <array>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

namespace {
    std::string_view bakeFunctionForType(std::string_view type) {
        assert(!type.empty());
        static std::unordered_map<std::string_view, std::string_view> BakeFunctions = {
            { "bool",           BakeFunctionBool },
            { "int",            BakeFunctionInt },
            { "double",         BakeFunctionDouble },
            { "float",          BakeFunctionFloat },
            { "std::string",    BakeFunctionString },
            { "glm::ivec2",     BakeFunctionIVec2 },
            { "glm::ivec3",     BakeFunctionIVec3 },
            { "glm::ivec4",     BakeFunctionIVec4 },
            { "glm::dvec2",     BakeFunctionDVec2 },
            { "glm::dvec3",     BakeFunctionDVec3 },
            { "glm::dvec4",     BakeFunctionDVec4 },
            { "glm::vec2",      BakeFunctionVec2 },
            { "glm::vec3",      BakeFunctionVec3 },
            { "glm::vec4",      BakeFunctionVec4 },
            { "glm::mat2x2",    BakeFunctionMat2x2 },
            { "glm::mat2x3",    BakeFunctionMat2x3 },
            { "glm::mat2x4",    BakeFunctionMat2x4 },
            { "glm::mat3x2",    BakeFunctionMat3x2 },
            { "glm::mat3x3",    BakeFunctionMat3x3 },
            { "glm::mat3x4",    BakeFunctionMat3x4 },
            { "glm::mat4x2",    BakeFunctionMat4x2 },
            { "glm::mat4x3",    BakeFunctionMat4x3 },
            { "glm::mat4x4",    BakeFunctionMat4x4 },
            { "glm::dmat2x2",   BakeFunctionDMat2x2 },
            { "glm::dmat2x3",   BakeFunctionDMat2x3 },
            { "glm::dmat2x4",   BakeFunctionDMat2x4 },
            { "glm::dmat3x2",   BakeFunctionDMat3x2 },
            { "glm::dmat3x3",   BakeFunctionDMat3x3 },
            { "glm::dmat3x4",   BakeFunctionDMat3x4 },
            { "glm::dmat4x2",   BakeFunctionDMat4x2 },
            { "glm::dmat4x3",   BakeFunctionDMat4x3 },
            { "glm::dmat4x4",   BakeFunctionDMat4x4 },
            { "std::monostate", BakeFunctionMonostate },
            { "std::optional",  BakeFunctionOptional },
            { "std::vector",    BakeFunctionVector }
        };

        const auto it = BakeFunctions.find(type);
        return it != BakeFunctions.end() ? it->second : std::string_view();
    }

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

    std::vector<std::string> usedTypes(Struct* s) {
        std::vector<std::string> res;
        for (Variable* var : s->variables) {
            std::string_view type = var->type;

            if (startsWith(type, "std::optional<")) {
                res.push_back("std::optional");
                type.remove_prefix(std::string_view("std::optional<").size());
                type.remove_suffix(1);

                if (isBasicType(type)) {
                    res.push_back(std::string(type));
                }
            }

            if (startsWith(type, "std::vector<")) {
                res.push_back("std::vector");
                type.remove_prefix(std::string_view("std::vector<").size());
                type.remove_suffix(1);

                if (isBasicType(type)) {
                    res.push_back(std::string(type));
                }
            }

            if (startsWith(type, "std::variant<")) {
                res.push_back("std::variant");
                std::string_view subtype = type.substr(std::string_view("std::variant<").size());
                std::vector<std::string_view> types = extractTemplateTypeList(subtype);

                for (std::string_view t : types) {
                    if (isBasicType(t)) {
                        res.push_back(std::string(t));
                    }
                }
            }

            if (isBasicType(var->type)) {
                res.push_back(std::string(var->type));
            }
        }

        for (StackElement* e : s->children) {
            if (e->type != StackElement::Type::Struct)  continue;

            Struct* s = static_cast<Struct*>(e);
            std::vector<std::string> t = usedTypes(s);
            res.insert(res.end(), t.begin(), t.end());
        }

        return res;
    }

    std::string resolveComment(std::string comment) {
        if (size_t it = comment.find("codegen::description"); it != std::string::npos) {
            const size_t l = std::string_view("codegen::description").size();
            it += l;
            if (comment[it] != '(') {
                throw std::runtime_error(
                    fmt::format(
                        "Malformed codegen::description. Expected ( after token:\n{}", comment
                    )
                );
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
                throw std::runtime_error(
                    fmt::format(
                        "Discovered unallowed unescaped \" in comment line:\n{}", comment
                    )
                );
            }

            // We add artificial spaces between the multiline comments, which causes there to
            // be a stray space at the end
            if (!comment.empty()) {
                comment.pop_back();
            }
            comment = std::string("\"") + comment + "\"";
        }
        return comment;
    }
} // namespace

std::string verifier(std::string_view type, const Variable& variable, Struct* currentStruct) {
    assert(!type.empty());

    Struct* root = rootStruct(currentStruct);

    std::string v = verifierForType(type, variable.attributes, root->attributes.dictionary);
    
    if (!v.empty()) {
        return std::string("new ") + v;
    }
    else if (startsWith(type, "std::vector<")) {
        std::string_view subtype = type.substr(std::string_view("std::vector<").size());
        subtype.remove_suffix(1);

        const StackElement* e = resolveType(currentStruct, subtype);
        std::string comments;
        if (e) {
            // e is false for subtypes that are not our own structs
            comments = resolveComment(e->comment);
        }

        std::string ver = verifier(subtype, variable, currentStruct);
        char* base = ScratchSpace;

        char* out = fmt::format_to(
            ScratchSpace,
            "new TableVerifier({{{{\"*\",{},Optional::Yes, {}}}}})\n",
            ver, comments
        );
        ScratchSpace = out;

        return std::string(base, ScratchSpace);
    }
    else if (startsWith(type, "std::variant<")) {
        std::string_view subtypes = type.substr(std::string_view("std::variant<").size());
        if (subtypes.find('>') == std::string_view::npos) {
            throw std::runtime_error(fmt::format(
                "Could not find closing > in variant definition:\n{}", type
            ));
        }
        assert(subtypes.back() == '>');

        char* resBase = ScratchSpace;
        ScratchSpace = fmt::format_to(ScratchSpace, "new OrVerifier({{");

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            std::string ver = verifier(subtype, variable, currentStruct);
            ScratchSpace = fmt::format_to(ScratchSpace, "{},", ver);
        }

        ScratchSpace = fmt::format_to(ScratchSpace, "}})");
        return std::string(resBase, ScratchSpace - resBase);
    }
    else {
        const StackElement* e = resolveType(currentStruct, type);
        if (!e) {
            throw std::runtime_error(fmt::format(
                "Unhandled type detected and codegen doesn't know how to handle it: {}",
                type
            ));
        }

        return std::string("codegen_") + fqn(currentStruct, "_") + "_" + std::string(type);
    }
}

char* writeStructDocumentation(char* buffer, Struct* s) {
    std::string name = "codegen_" + fqn(s, "_");
    buffer = fmt::format_to(
        buffer,
        "    TableVerifier* {} = new TableVerifier;\n",
        name
    );

    const bool isRootStruct = s->parent == nullptr;
    if (isRootStruct && !s->attributes.noTypeCheck) {
        buffer = fmt::format_to(
            buffer,
            "    {}->documentations.push_back({{ \"Type\", new StringEqualVerifier(\"{}\"), Optional::No }});\n",
            name, s->attributes.dictionary
        );
    }

    for (StackElement* e : s->children) {
        if (e->type == StackElement::Type::Struct) {
            buffer = writeStructDocumentation(buffer, static_cast<Struct*>(e));
        }
        if (e->type == StackElement::Type::Enum) {
            std::string name = "codegen_" + fqn(e, "_");

            buffer = fmt::format_to(
                buffer,
                "    StringInListVerifier* {} = new StringInListVerifier({{", name
            );


            Enum* en = static_cast<Enum*>(e);
            for (EnumElement* em : en->elements) {
                // If no key attribute is specified, we use the name instead
                std::string_view key;
                if (em->attributes.key.empty()) {
                    key = em->name;
                }
                else {
                    key = em->attributes.key;
                }

                buffer = fmt::format_to(buffer, "\"{}\",", key);
            }
            // The last element has a , at the end that we can overwrite
            buffer -= 1;

            buffer = fmt::format_to(buffer, "}});\n");
        }
    }

    for (Variable* var : s->variables) {
        var->comment = resolveComment(var->comment);

        std::string type = var->type;
        bool isOptional = false;
        if (startsWith(var->type, "std::optional<")) {
            isOptional = true;
            type = var->type.substr(std::string_view("std::optional<").size());
            type = type.substr(0, type.size() - 1);
        }

        std::string ver = std::string("codegen_") + fqn(s, "_");
        std::string v = verifier(type, *var, s);
        buffer = fmt::format_to(
            buffer,
            "    {}->documentations.push_back({{\"{}\",{},{},{}}});\n",
            ver, var->key, v,
            isOptional ? "Optional::Yes" : "Optional::No", var->comment
        );
    }

    return buffer;
}

char* writeStructConverter(char* buffer, Struct* s) {
    for (Variable* var : s->variables) {
        if (startsWith(var->type, "std::variant")) {
            std::string subtypes = var->type.substr(std::string_view("std::variant<").size());

            buffer = fmt::format_to(
                buffer,
                "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n",
                var->type
            );

            std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
            for (std::string_view subtype : ttypes) {
                buffer = fmt::format_to(
                    buffer,
                    "   if (d.hasValue<{0}>(key)) {{ {0} v; bakeTo(d, key, &v); *val = std::move(v); }}\n",
                    subtype
                );
            }

            buffer = fmt::format_to(buffer, "}}");
        }
    }


    for (StackElement* e : s->children) {
        if (e->type == StackElement::Type::Struct) {
            buffer = writeStructConverter(buffer, static_cast<Struct*>(e));
        }

        if (e->type == StackElement::Type::Enum) {
            std::string type = fqn(e, "::");
            buffer = fmt::format_to(
                buffer,
                "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n"
                "    std::string v = d.value<std::string>(key);\n",
                type
            );

            for (EnumElement* elem : static_cast<Enum*>(e)->elements) {
                std::string_view key;
                if (elem->attributes.key.empty()) {
                    key = elem->name;
                }
                else {
                    key = elem->attributes.key;
                }

                std::string type = fqn(e, "::");
                buffer = fmt::format_to(
                    buffer,
                    "    if (v == \"{}\") {{ *val = {}::{}; }}\n",
                    key, type, elem->name
                );
            }

            buffer = fmt::format_to(buffer, "}}\n");

        }
    }

    if (s->parent == nullptr) {
        return buffer;
    }

    std::string name = fqn(s, "::");
    buffer = fmt::format_to(
        buffer,
        "template <> void bakeTo<{0}>(const ghoul::Dictionary& d, std::string_view key, {0}* val) {{\n"
        "    {0}& res = *val;\n"
        "    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);\n",
        name
    );

    for (Variable* var : s->variables) {
        buffer = fmt::format_to(
            buffer,
            "    internal::bakeTo(dict, \"{}\", &res.{});\n", var->key, var->name
        );
    }

    buffer = fmt::format_to(buffer, "}}\n");

    return buffer;
}

std::string_view generateResult(Struct* s, std::filesystem::path path) {
    Result = fmt::format_to(Result, fileHeader, path.filename().string());

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


    Result = fmt::format_to(
        Result,
        R"(
namespace codegen {{
template <typename T> openspace::documentation::Documentation doc() {{
    static_assert(sizeof(T) == 0); // This should never be called
    return openspace::documentation::Documentation();
}}
template <> openspace::documentation::Documentation doc<{}>() {{
    using namespace openspace::documentation;
)",
        name
    );

    Result = writeStructDocumentation(Result, s);
    Result = fmt::format_to(
        Result,
        R"(
    openspace::documentation::Documentation d = {{ "{0}", "{0}", std::move({1}->documentations) }};
    delete {1};
    return d;
}}
}} // namespace codegen

)",
        s->attributes.dictionary,
        fmt::format("codegen_{}", s->name)
    );

    std::string_view preamble = bakeFunctionPreamble;
    std::memcpy(Result, preamble.data(), preamble.size());
    Result += preamble.size();



    // For Linux, we need to delcare the functions in the following order or the overload
    // resolution picks the top fall back implentation and triggers a static_assert:
    // 1. <typename T> bakeTo(..., T*) { static_assert(false); } // fallback
    // 2. bakeTo(..., T*) {...} for T=base types
    // 3. <typename T> bakeTo(..., std::optional<T>*)   declaration only
    // 4. <typename T> bakeTo(..., std::vector<T>*)   declaration only
    // 5. <typename T> bakeTo(..., T*) {...}  for T=custom structs
    // 6. <typename T> bakeTo(..., std::optional<T>*) {...}   definition
    // 7. <typename T> bakeTo(..., std::vector<T>*) {...}   definition
    //
    // Reason:  When going through the custom structs, they need to know that there will
    // be implementatinos for the optional and vector types or otherwise they will trip
    // the fall back.  However, the actual implementation needs to know about the custom
    // struct one or else *they* will trip the fall back in the implementation.
    // For ease of implementation, we are putting 3&4 before 2 instead

    std::vector<std::string> types = usedTypes(s);
    std::sort(types.begin(), types.end());
    types.erase(std::unique(types.begin(), types.end()), types.end());

    if (auto it = std::find(types.begin(), types.end(), "std::optional");
        it != types.end())
    {
        std::string_view decl = BakeFunctionOptionalDeclaration;
        std::memcpy(Result, decl.data(), decl.size());
        Result += decl.size();
    }
    if (auto it = std::find(types.begin(), types.end(), "std::vector");
        it != types.end())
    {
        std::string_view decl = BakeFunctionVectorDeclaration;
        std::memcpy(Result, decl.data(), decl.size());
        Result += decl.size();
    }

    std::vector<std::string> firstPhaseTypes = types;
    auto itOptional = std::find(firstPhaseTypes.begin(), firstPhaseTypes.end(), "std::optional");
    if (itOptional != firstPhaseTypes.end()) {
        firstPhaseTypes.erase(itOptional);
    }
    auto itVector = std::find(firstPhaseTypes.begin(), firstPhaseTypes.end(), "std::vector");
    if (itVector != firstPhaseTypes.end()) {
        firstPhaseTypes.erase(itVector);
    }

    for (const std::string& t : firstPhaseTypes) {
        std::string_view bake = bakeFunctionForType(t);
        if (!bake.empty()) {
            // The return value is empty for types that don't have a
            // preamble-defined bake functions, like all custom structs
            std::memcpy(Result, bake.data(), bake.size());
            Result += bake.size();
        }
    }


    Result = writeStructConverter(Result, s);

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

    for (const std::string& type : types) {
        if (type != "std::vector" && type != "std::optional")  continue;

        std::string_view bake = bakeFunctionForType(type);
        assert(!bake.empty());
        // The return value is empty for types that don't have a
        // preamble-defined bake functions, like all custom structs
        std::memcpy(Result, bake.data(), bake.size());
        Result += bake.size();
    }

    // This is the last struct to be closed, so it is the struct that the user will
    // ask for
    Result = fmt::format_to(
        Result,
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
        Result = fmt::format_to(
            Result,
            "    internal::bakeTo(dict, \"{}\", &res.{});\n", var->key, var->name
        );
    }

    Result = fmt::format_to(Result, "    return res;\n}}\n}} // namespace codegen\n");
    return std::string_view(ResultBase, Result - ResultBase);
}


void handleFile(std::filesystem::path path) {
    std::string res;
    {
        std::ifstream f(path);
        res = std::string(std::istreambuf_iterator<char>{f}, {});
    }
    std::string_view content = strip(validCode(res));
    if (content.empty()) {
        return;
    }
    
    AllFiles++;

    std::filesystem::path destination = path;
    destination.replace_extension();
    destination.replace_filename(destination.filename().string() + "_codegen.cpp");

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

    if (size_t p = res.find(destination.filename().string());
        p == std::string_view::npos)
    {
        //throw std::runtime_error(
        //    "File does not include the generated file. This was probably a mistake"
        //);
    }

    auto it = std::find_if(
        MemoryPool.begin(), MemoryPool.end(),
        [](const Memory& m) { return m.id == std::this_thread::get_id(); }
    );
    if (it == MemoryPool.end()) {
        Memory m;
        m.ScratchSpace = new char[BufferSize];
        m.Result = new char[BufferSize];
        MemoryPool.push_back(m);
        it = MemoryPool.end() - 1;
    }

    ScratchSpaceBase = it->ScratchSpace;
    ResultBase = it->Result;

    ScratchSpace = ScratchSpaceBase;
    Result = ResultBase;
    std::fill(ScratchSpaceBase, ScratchSpaceBase + BufferSize - 1, '\0');
    std::fill(ResultBase, ResultBase + BufferSize - 1, '\0');

    Struct* rootStruct = nullptr;
    std::vector<StackElement*> stack;
    
    std::string variableBuffer;
    std::string commentBuffer;

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (line.empty()) {
            continue;
        }

        // If the variable buffer is filled, then we are in a continuation of a variable
        // definition
        if (variableBuffer.empty()) {
            if (startsWith(line, "//")) {
                std::string_view comment = parseCommentLine(line);
                commentBuffer.append(comment);
                commentBuffer.append(" ");
                continue;
            }

            if (startsWith(line, "struct")) {
                if (!stack.empty() &&
                    stack.back()->type != StackElement::Type::Struct)
                {
                    throw std::runtime_error(fmt::format(
                        "Struct definition found outside a parent struct.\n{}",
                        line
                    ));
                }

                Struct* s = parseStruct(line);
                if (!stack.empty()) {
                    assert(stack.back()->type == StackElement::Type::Struct);
                    s->parent = static_cast<Struct*>(stack.back());
                    s->parent->children.push_back(s);
                }

                stack.push_back(s);
                s->comment = commentBuffer;
                //state.structComments[std::string(s->name)] = commentBuffer;
                commentBuffer.clear();

                if (!s->attributes.dictionary.empty()) {
                    if (rootStruct) {
                        throw std::runtime_error(fmt::format(
                            "Only the root struct can have a [[codegen::Dictionary()]] "
                            "attribute, found a second one here:\n{}",
                            s->name
                        ));
                    }
                    rootStruct = s;
                }
                continue;
            }

            if (startsWith(line, "enum class")) {
                Enum* e = parseEnum(line);
                Struct* parent = static_cast<Struct*>(stack.back());
                assert(parent->type == StackElement::Type::Struct);
                parent->children.push_back(e);
                e->parent = parent;
                stack.push_back(e);
                e->comment = commentBuffer;
                commentBuffer.clear();
                continue;
            }

            if (startsWith(line, "enum")) {
                throw std::runtime_error(
                    "Old-style 'enum' not supported. Use 'enum class' instead"
                );
            }

            if (startsWith(line, "};")) {
                stack.pop_back();
                continue;
            }
        }

        // If we got this far, we must be in a variable definition or an enum defintion
        // if the highest stack element is a struct, we are in a variable definition, if
        // the highest stack element is an enum, we are in an enum definition
        StackElement* e = stack.back();
        switch (e->type) {
            case StackElement::Type::Struct:
                if (line.find(';') == std::string_view::npos) {
                    // No semicolon on this line but we are looking for a variable, so we
                    // are in a definition line that spans multiple lines
                    variableBuffer += std::string(line) + " ";
                    continue;
                }
                if (variableBuffer.empty()) {
                    Variable* var = parseVariable(line);
                    var->comment = commentBuffer;
                    commentBuffer.clear();
                    static_cast<Struct*>(e)->variables.push_back(var);
                }
                else {
                    variableBuffer += std::string(line);
                    Variable* var = parseVariable(variableBuffer);
                    var->comment = commentBuffer;
                    commentBuffer.clear();
                    static_cast<Struct*>(e)->variables.push_back(var);
                    variableBuffer.clear();
                }
                break;
            case StackElement::Type::Enum: {
                EnumElement* el = parseEnumElement(line);
                static_cast<Enum*>(e)->elements.push_back(el);
                break;
            }
        }
    }

    if (!rootStruct || rootStruct->attributes.dictionary.empty()) {
        throw std::runtime_error(
            "Root struct tag [[codegen::Dictionary]] is missing the renderable name"
        );
    }

    std::string_view genContent = generateResult(rootStruct, path);

    if (PrintMemoryUsage) {
        print(
            "Memory usage:   Result(%5lli/%i)    Scratch(%5lli/%i)\n",
            ScratchSpace - ScratchSpaceBase, BufferSize,
            Result - ResultBase, BufferSize
        );
    }

    bool shouldWriteFile;
    if (std::filesystem::exists(destination)) {
        std::ifstream f(destination);
        std::string prev = std::string(std::istreambuf_iterator<char>{f}, {});
        shouldWriteFile = (prev != genContent);
    }
    else {
        shouldWriteFile = true;
    }

    if (shouldWriteFile && PreventFileChange) {
        std::filesystem::path debugDestination = destination;
        debugDestination.replace_extension();
        debugDestination.replace_filename(debugDestination.filename().string() + "_debug.cpp");

        std::ofstream output(debugDestination);
        output.write(genContent.data(), genContent.size());

        throw std::runtime_error(fmt::format(
            "Asked to prevent file change, but file change detected in '{}'",
            path.filename().string()
        ));
    }

    if (shouldWriteFile || AlwaysOutputFiles) {
        print("Processed file '%s'\n", path.filename().string().c_str());
        ChangedFiles++;
    }
}
