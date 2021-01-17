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

} // namespace

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


std::string verifier(std::string_view type, const Variable& variable, State& state, Struct* rootStruct, Struct* currentStuct) {
    assert(!type.empty());

    std::string v = verifierForType(type, variable.attributes, rootStruct->attributes.dictionary);
    
    if (!v.empty()) {
        state.typeUsage[std::string(type)] = true;
        return std::string("new ") + v;
    }
    else if (startsWith(type, "std::vector<")) {
        state.typeUsage["std::vector"] = true;
        std::string_view subtype = type.substr(std::string_view("std::vector<").size());
        subtype.remove_suffix(1);

        std::string comments;
        if (auto it = state.structComments.find(subtype); it != state.structComments.end()) {
            comments = resolveComment(it->second);
        }

        std::string ver = verifier(subtype, variable, state, rootStruct, currentStuct);
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
        state.typeUsage["std::variant"] = true;

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
            std::string ver = verifier(subtype, variable, state, rootStruct, currentStuct);
            ScratchSpace = fmt::format_to(ScratchSpace, "{},", ver);
        }

        ScratchSpace = fmt::format_to(ScratchSpace, "}})");
        return std::string(resBase, ScratchSpace - resBase);
    }
    else {
        const StackElement* e = resolveType(currentStuct, type);
        if (!e) {
            throw std::runtime_error(fmt::format(
                "Unhandled type detected and codegen doesn't know how to handle it: {}",
                type
            ));
        }

        state.typeUsage[std::string(type)] = true;
        return std::string("codegen_") + fqn(currentStuct, "_") + "_" + std::string(type);
    }
}

void handleStructStart(Struct* s, bool isRootStruct) {
    std::string name = "codegen_" + fqn(s, "_");
    VerifierResult = fmt::format_to(
        VerifierResult,
        "    TableVerifier* {} = new TableVerifier;\n",
        name
    );

    if (isRootStruct && !s->attributes.noTypeCheck) {
        VerifierResult = fmt::format_to(
            VerifierResult,
            "    {}->documentations.push_back({{ \"Type\", new StringEqualVerifier(\"{}\"), Optional::No }});\n",
            name, s->attributes.dictionary
        );
    }
}

void handleStructEnd(State& state, Struct* s, bool isRootStruct) {
    std::string name = fqn(s, "::");
    if (isRootStruct) {
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


        for (const std::pair<const std::string, bool>& kv : state.typeUsage) {
            assert(kv.second);
            if (kv.first != "std::vector" && kv.first != "std::optional") {
                continue;
            }
            if (kv.second) {
                std::string_view bake = bakeFunctionForType(kv.first);
                if (!bake.empty()) {
                    // The return value is empty for types that don't have a
                    // preamble-defined bake functions, like all custom structs
                    std::memcpy(ConverterResult, bake.data(), bake.size());
                    ConverterResult += bake.size();
                }
            }

        }


        // This is the last struct to be closed, so it is the struct that the user will
        // ask for
        ConverterResult = fmt::format_to(
            ConverterResult,
            R"(
}} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) {{ static_assert(sizeof(T) == 0); }}
template <> {0} bake<{0}>(const ghoul::Dictionary& dict) {{
    openspace::documentation::testSpecificationAndThrow(codegen::doc<{1}>(), dict, "{2}");
    {0} res;
)",
            name,
            fqName,
            s->attributes.dictionary
        );
    }
    else {
        ConverterResult = fmt::format_to(
            ConverterResult,
            "template <> void bakeTo<{0}>(const ghoul::Dictionary& d, std::string_view key, {0}* val) {{\n"
            "    {0}& res = *val;\n"
            "    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);\n",
            name
        );
    }


    auto it = state.structConverters.find(name);
    if (it == state.structConverters.end()) {
        throw std::runtime_error(fmt::format("Empty structs are not allowed:\n{}", name));
    }
    assert(state.structVariables.find(name) != state.structVariables.end());
    assert(!state.structVariables[name].empty());

    std::memcpy(ConverterResult, it->second.data(), it->second.size());
    ConverterResult += it->second.size();



    if (!s->attributes.noExhaustive) {
        std::vector<std::string> variableNames = state.structVariables[name];
        if (!s->attributes.noTypeCheck) {
            variableNames.push_back("\"Type\"");
        }


        std::string joined = join(variableNames, ", ");
        ConverterResult = fmt::format_to(
            ConverterResult,
            R"(
    const std::array<std::string_view, {}> AllowedKeys = {{ {} }};
    for (std::string_view k : dict.keys()) {
        if (std::find(AllowedKeys.begin(), AllowedKeys.end(), k) == AllowedKeys.end()) {{
            throw ghoul::RuntimeError(fmt::format("Extra key found: {{}}", k));
        }}
    }}
)",
            variableNames.size(), joined
        );
    }


    if (isRootStruct) {
        ConverterResult = fmt::format_to(ConverterResult, "    return res;\n}}\n");
    }
    else {
        ConverterResult = fmt::format_to(ConverterResult, "}}\n");
    }
}

void handleEnumStart(const std::vector<StackElement*>& stack) {
    std::string name = "codegen_" + fqn(stack.back(), "_");

    VerifierResult = fmt::format_to(
        VerifierResult,
        "    StringInListVerifier* {} = new StringInListVerifier({{", name
    );


    std::string type = fqn(stack.back(), "::");
    ConverterResult = fmt::format_to(
        ConverterResult,
        "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n"
        "    std::string v = d.value<std::string>(key);\n",
        type
    );
}

void handleEnumEnd() {
    // The last element has a , at the end that we can overwrite
    VerifierResult -= 1;

    VerifierResult = fmt::format_to(VerifierResult, "}});\n");


    ConverterResult = fmt::format_to(ConverterResult, "}}\n");
}

void handleEnumValue(EnumElement element, const std::vector<StackElement*>& stack) {
    // If no key attribute is specified, we use the name instead
    if (element.attributes.key.empty()) {
        element.attributes.key = element.name;
    }

    VerifierResult = fmt::format_to(VerifierResult, "\"{}\",", element.attributes.key);

    std::string type = fqn(stack.back(), "::");
    ConverterResult = fmt::format_to(
        ConverterResult,
        "    if (v == \"{}\") {{ *val = {}::{}; }}\n",
        element.attributes.key, type, element.name
    );
}

void handleVariable(Variable var, State& state, Struct* s, Struct* rootStruct) {
    std::string ver = std::string("codegen_") + fqn(s, "_");

    std::string variableName;
    if (auto it = var.attributes.find("key"); it != var.attributes.end()) {
        assert(!it->second.empty());
        variableName = std::string(it->second);
    }
    else {
        variableName = std::string(var.name);
        variableName[0] = static_cast<char>(::toupper(variableName[0]));
    }

    state.commentBuffer = resolveComment(state.commentBuffer);

    bool isOptional = false;
    if (startsWith(var.type, "std::optional<")) {
        isOptional = true;
        state.typeUsage["std::optional"] = true;
        var.type.remove_prefix(std::string_view("std::optional<").size());
        var.type.remove_suffix(1);
    }

    std::string v = verifier(var.type, var, state, rootStruct, s);
    VerifierResult = fmt::format_to(
        VerifierResult,
        "    {}->documentations.push_back({{\"{}\",{},{},{}}});\n",
        ver, variableName, v,
        isOptional ? "Optional::Yes" : "Optional::No", state.commentBuffer
    );
    state.commentBuffer.clear();


    // Converter
    std::string converter;
    std::string name = fqn(s, "::");
    if (auto it = state.structConverters.find(name); it != state.structConverters.end()) {
        converter = it->second;
    }

    char* out = fmt::format_to(
        ScratchSpace,
        "    internal::bakeTo(dict, \"{}\", &res.{});\n",
        variableName, var.name
    );

    converter += std::string(ScratchSpace, out);
    ScratchSpace = out;
    state.structConverters[name] = converter;
    std::vector<std::string> variables = state.structVariables[name];
    variables.push_back("\"" + variableName + "\"");
    state.structVariables[name] = variables;


    if (startsWith(var.type, "std::variant")) {
        std::string_view subtypes = var.type.substr(std::string_view("std::variant<").size());

        ConverterResult = fmt::format_to(
            ConverterResult,
            "void bakeTo(const ghoul::Dictionary& d, std::string_view key, {}* val) {{\n",
            var.type
        );

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            ConverterResult = fmt::format_to(
                ConverterResult,
                "   if (d.hasValue<{0}>(key)) {{ {0} v; bakeTo(d, key, &v); *val = std::move(v); }}\n",
                subtype
            );
        }

        ConverterResult = fmt::format_to(ConverterResult, "}}");
    }
}

void finalizeVerifier(Struct* rootStruct) {
    std::string name;
    if (rootStruct->attributes.namespaceSpecifier.empty()) {
        name = fmt::format("openspace::{}", rootStruct->attributes.dictionary);
    }
    else {
        name = fmt::format(
            "openspace::{}::{}",
            rootStruct->attributes.namespaceSpecifier,
            rootStruct->attributes.dictionary
        );
    }

    std::array<char, 512> Buf;
    std::fill(Buf.begin(), Buf.end(), '\0');
    char* out = fmt::format_to(
        Buf.data(),
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
    int n = static_cast<int>(out - Buf.data());

    std::memmove(
        VerifierResultBase + n,
        VerifierResultBase,
        VerifierResult - VerifierResultBase
    );
    std::memcpy(VerifierResultBase, Buf.data(), n);
    VerifierResult += n;

    VerifierResult = fmt::format_to(
        VerifierResult,
        R"(
    openspace::documentation::Documentation d = {{ "{0}", "{0}", std::move({1}->documentations) }};
    delete {1};
    return d;
}}
}} // namespace codegen

)",
        rootStruct->attributes.dictionary,
        fmt::format("codegen_{}", rootStruct->name)
    );
}

void finalizeConverter(State& state) {
    char* base = ScratchSpace;
    std::string_view preamble = bakeFunctionPreamble;
    std::memcpy(ScratchSpace, preamble.data(), preamble.size());
    ScratchSpace += preamble.size();

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

    if (auto it = state.typeUsage.find("std::optional");
        it != state.typeUsage.end() && it->second)
    {
        std::string_view decl = BakeFunctionOptionalDeclaration;
        std::memcpy(ScratchSpace, decl.data(), decl.size());
        ScratchSpace += decl.size();
    }
    if (auto it = state.typeUsage.find("std::vector");
        it != state.typeUsage.end() && it->second)
    {
        std::string_view decl = BakeFunctionVectorDeclaration;
        std::memcpy(ScratchSpace, decl.data(), decl.size());
        ScratchSpace += decl.size();
    }


    std::map<std::string, bool, std::less<>> firstPhaseType = state.typeUsage;
    firstPhaseType.erase("std::optional");
    firstPhaseType.erase("std::vector");

    std::map<std::string, bool, std::less<>> secondPhaseType;
    if (state.typeUsage.find("std::vector") != state.typeUsage.end()) {
        secondPhaseType["std::vector"] = state.typeUsage["std::vector"];
    }
    if (state.typeUsage.find("std::optional") != state.typeUsage.end()) {
        secondPhaseType["std::optional"] = state.typeUsage["std::optional"];
    }


    for (const std::pair<const std::string, bool>& kv : firstPhaseType) {
        assert(kv.second);
        if (kv.second) {
            std::string_view bake = bakeFunctionForType(kv.first);
            if (!bake.empty()) {
                // The return value is empty for types that don't have a
                // preamble-defined bake functions, like all custom structs
                std::memcpy(ScratchSpace, bake.data(), bake.size());
                ScratchSpace += bake.size();
            }
        }
    }

    long long preambleSize = ScratchSpace - base;

    std::memmove(
        ConverterResultBase + preambleSize,
        ConverterResultBase,
        ConverterResult - ConverterResultBase
    );
    std::memcpy(ConverterResultBase, base, preambleSize);
    ConverterResult += preambleSize;

    ConverterResult = fmt::format_to(ConverterResult, "}} // namespace codegen\n");
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
        throw std::runtime_error(
            "File does not include the generated file. This was probably a mistake"
        );
    }


    State state;
    auto it = std::find_if(
        MemoryPool.begin(), MemoryPool.end(),
        [](const Memory& m) { return m.id == std::this_thread::get_id(); }
    );
    if (it == MemoryPool.end()) {
        Memory m;
        m.ConverterResult = new char[BufferSize];
        m.VerifierResult = new char[BufferSize];
        m.ScratchSpace = new char[BufferSize];
        MemoryPool.push_back(m);
        it = MemoryPool.end() - 1;
    }

    VerifierResultBase = it->VerifierResult;
    ConverterResultBase = it->ConverterResult;
    ScratchSpaceBase = it->ScratchSpace;

    VerifierResult = VerifierResultBase;
    ConverterResult = ConverterResultBase;
    ScratchSpace = ScratchSpaceBase;
    std::fill(VerifierResultBase, VerifierResultBase + BufferSize - 1, '\0');
    std::fill(ConverterResultBase, ConverterResultBase + BufferSize - 1, '\0');
    std::fill(ScratchSpaceBase, ScratchSpaceBase + BufferSize - 1, '\0');

    Struct* rootStruct = nullptr;
    std::vector<StackElement*> stack;

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (line.empty()) {
            continue;
        }

        // If the variable buffer is filled, then we are in a continuation of a variable
        // definition
        if (state.variableBuffer.empty()) {
            if (startsWith(line, "//")) {
                std::string_view comment = parseCommentLine(line);
                state.commentBuffer.append(comment);
                state.commentBuffer.append(" ");
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
                state.structComments[std::string(s->name)] = state.commentBuffer;
                state.commentBuffer.clear();

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

                const bool isRootStruct = (s == rootStruct);
                handleStructStart(s, isRootStruct);
                continue;
            }

            if (startsWith(line, "enum class")) {
                Enum* e = parseEnum(line);
                Struct* parent = static_cast<Struct*>(stack.back());
                assert(parent->type == StackElement::Type::Struct);
                parent->children.push_back(e);
                e->parent = parent;
                stack.push_back(e);
                state.structComments[std::string(e->name)] = state.commentBuffer;
                state.commentBuffer.clear();

                handleEnumStart(stack);
                continue;
            }

            if (startsWith(line, "enum")) {
                throw std::runtime_error(
                    "Old-style 'enum' not supported. Use 'enum class' instead"
                );
            }

            if (startsWith(line, "};")) {
                StackElement* e = stack.back();
                switch (e->type) {
                    case StackElement::Type::Struct:
                        handleStructEnd(
                            state,
                            static_cast<Struct*>(e),
                            e == rootStruct
                        );
                        break;
                    case StackElement::Type::Enum:
                        handleEnumEnd();
                        break;
                    default: throw std::logic_error("Unhandled case label");
                }

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
                    state.variableBuffer += std::string(line) + " ";
                    continue;
                }
                if (state.variableBuffer.empty()) {
                    Variable var = parseVariable(line);
                    handleVariable(var, state, static_cast<Struct*>(e), rootStruct);
                }
                else {
                    state.variableBuffer += std::string(line);
                    Variable var = parseVariable(state.variableBuffer);
                    handleVariable(var, state, static_cast<Struct*>(e), rootStruct);
                    state.variableBuffer.clear();
                }
                break;
            case StackElement::Type::Enum:
                handleEnumValue(parseEnumElement(line), stack);
                break;
        }
    }

    if (!rootStruct || rootStruct->attributes.dictionary.empty()) {
        throw std::runtime_error(
            "Root struct tag [[codegen::Dictionary]] is missing the renderable name"
        );
    }

    char* out = fmt::format_to(ScratchSpace, fileHeader, path.filename().string());
    std::string newContent = std::string(ScratchSpace, out);
    ScratchSpace = out;

    finalizeVerifier(rootStruct);
    finalizeConverter(state);

    newContent += std::string(VerifierResultBase, VerifierResult - VerifierResultBase);
    newContent += std::string(ConverterResultBase, ConverterResult - ConverterResultBase);

    if (PrintMemoryUsage) {
        print(
            "Memory usage:   Converter(%5lli/%i)   Verifier(%5lli/%i)   Scratch(%5lli/%i)\n",
            ConverterResult - ConverterResultBase, BufferSize,
            VerifierResult - VerifierResultBase, BufferSize,
            ScratchSpace - ScratchSpaceBase, BufferSize
        );
    }

    bool shouldWriteFile;
    if (std::filesystem::exists(destination)) {
        std::ifstream f(destination);
        std::string prev = std::string(std::istreambuf_iterator<char>{f}, {});
        shouldWriteFile = (prev != newContent);
    }
    else {
        shouldWriteFile = true;
    }

    if (shouldWriteFile && PreventFileChange) {
        std::filesystem::path debugDestination = destination;
        debugDestination.replace_extension();
        debugDestination.replace_filename(debugDestination.filename().string() + "_debug.cpp");

        std::ofstream output(debugDestination);
        output.write(newContent.c_str(), newContent.size());

        throw std::runtime_error(fmt::format(
            "Asked to prevent file change, but file change detected in '{}'",
            path.filename().string()
        ));
    }

    if (shouldWriteFile || AlwaysOutputFiles) {
        print("Processed file '%s'\n", path.filename().string().c_str());
        std::ofstream output(destination);
        output.write(newContent.c_str(), newContent.size());
        ChangedFiles++;
    }
}
