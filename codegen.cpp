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
#include "util.h"
#include "verifier.h"
#include <fmt/format.h>
#include <array>
#include <cassert>
#include <fstream>

#ifdef WIN32
#pragma warning (disable : 4996)
#endif // WIN32
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


std::string verifier(std::string_view type, const Variable& variable, State& state) {
    assert(!type.empty());

    std::string v = verifierForType(type, variable.attributes, state.rootStruct.attributes.dictionary);
    
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

        std::string ver = verifier(subtype, variable, state);
        char* base = ScratchSpace;
        int n = sprintf(
            ScratchSpace,
            "new TableVerifier({{\"*\",%s,Optional::Yes, %s}})\n",
            ver.c_str(),
            comments.c_str()
        );
        ScratchSpace += n;

        return std::string(base, base + n);
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
        int n = sprintf(ScratchSpace, "new OrVerifier({");
        ScratchSpace += n;

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            std::string ver = verifier(subtype, variable, state);
            n = sprintf(ScratchSpace, "%s,", ver.c_str());
            ScratchSpace += n;
        }

        n = sprintf(ScratchSpace, "})");
        ScratchSpace += n;
        return std::string(resBase, ScratchSpace - resBase);
    }
    else {
        std::vector<StackElement> stack = state.stack;
        stack.push_back({ StackElement::Type::Struct, Struct { type } });
        std::string structCandidate = join(stack, "::");

        stack.pop_back();
        stack.push_back({ StackElement::Type::Enum, Enum { type } });
        std::string enumCandidate = join(stack, "::");

        auto itStruct = std::find(
            state.structList.begin(), state.structList.end(),
            structCandidate
        );
        auto itEnum = std::find(
            state.enumList.begin(), state.enumList.end(),
            enumCandidate
        );
        if (itStruct == state.structList.end() && itEnum == state.enumList.end()) {
            throw std::runtime_error(fmt::format(
                "Unhandled type detected and codegen doesn't know how to handle it: {}",
                type
            ));
        }

        state.typeUsage[std::string(type)] = true;
        return std::string("codegen_") + join(state.stack, "_") + "_" + std::string(type);
    }
}

void handleStructStart(const Struct& s, State& state) {
    std::string name = "codegen_" + join(state.stack, "_");
    int n = sprintf(
        VerifierResult,
        "    TableVerifier* %s = new TableVerifier;\n", name.c_str()
    );
    VerifierResult += n;

    const bool isRootStruct = state.stack.size() == 1;
    if (isRootStruct && !s.attributes.noTypeCheck) {
        n = sprintf(
            VerifierResult,
            "    %s->documentations.push_back({ \"Type\", new StringEqualVerifier(\"%s\"), Optional::No });\n",
            name.c_str(),
            std::string(s.attributes.dictionary).c_str()
        );
        VerifierResult += n;
    }
}

void handleStructEnd(State& state) {
    const bool isRootStruct = state.stack.size() == 1;

    std::string name = join(state.stack, "::");
    if (isRootStruct) {
        std::string fqName;
        if (state.rootStruct.attributes.namespaceSpecifier.empty()) {
            fqName = fmt::format("openspace::{}", state.rootStruct.attributes.dictionary);
        }
        else {
            fqName = fmt::format(
                "openspace::{}::{}",
                state.rootStruct.attributes.namespaceSpecifier,
                state.rootStruct.attributes.dictionary
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
        int n = sprintf(
            ConverterResult,
            R"(
} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }
template <> %s bake<%s>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<%s>(), dict, "%s");
    %s res;
)",
            name.c_str(), name.c_str(),
            fqName.c_str(),
            std::string(state.rootStruct.attributes.dictionary).c_str(),
            name.c_str()
        );
        ConverterResult += n;
    }
    else {
        int n = sprintf(
            ConverterResult,
            "template <> void bakeTo<%s>(const ghoul::Dictionary& d, std::string_view key, %s* val) {\n"
            "    %s& res = *val;\n"
            "    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);\n",
            name.c_str(), name.c_str(), name.c_str()
        );
        ConverterResult += n;
    }


    auto it = state.structConverters.find(name);
    if (it == state.structConverters.end()) {
        throw std::runtime_error(fmt::format("Empty structs are not allowed:\n{}", name));
    }
    assert(state.structVariables.find(name) != state.structVariables.end());
    assert(!state.structVariables[name].empty());

    std::memcpy(ConverterResult, it->second.data(), it->second.size());
    ConverterResult += it->second.size();



    const StackElement& elem = state.stack.back();
    assert(elem.type == StackElement::Type::Struct);
    const Struct& s = std::get<Struct>(elem.payload);
    if (!s.attributes.noExhaustive) {
        std::vector<std::string> variableNames = state.structVariables[name];
        if (!s.attributes.noTypeCheck) {
            variableNames.push_back("\"Type\"");
        }


        std::string joined = join(variableNames, ", ");
        int n = sprintf(
            ConverterResult,
            R"(
    const std::array<std::string_view, %i> AllowedKeys = { %s };
    for (std::string_view k : dict.keys()) {
        if (std::find(AllowedKeys.begin(), AllowedKeys.end(), k) == AllowedKeys.end()) {
            throw ghoul::RuntimeError(fmt::format("Extra key found: {}", k));
        }
    }
)",
            static_cast<int>(variableNames.size()),
            joined.c_str()
        );
        ConverterResult += n;
    }


    if (isRootStruct) {
        int n = sprintf(ConverterResult, "    return res;\n}\n");
        ConverterResult += n;
    }
    else {
        int n = sprintf(ConverterResult, "}\n");
        ConverterResult += n;
    }
}

void handleEnumStart(State& state) {
    std::string name = "codegen_" + join(state.stack, "_");

    int n = sprintf(
        VerifierResult,
        "    StringInListVerifier* %s = new StringInListVerifier({", name.c_str()
    );
    VerifierResult += n;


    std::string type = join(state.stack, "::");
    n = sprintf(
        ConverterResult,
        "void bakeTo(const ghoul::Dictionary& d, std::string_view key, %s* val) {\n"
        "    std::string v = d.value<std::string>(key);\n",
        std::string(type).c_str()
    );
    ConverterResult += n;
}

void handleEnumEnd(State& state) {
    // The last element has a , at the end that we can overwrite
    VerifierResult -= 1;

    int n = sprintf(VerifierResult, "});\n");
    VerifierResult += n;


    n = sprintf(ConverterResult, "}\n");
    ConverterResult += n;
}

void handleEnumValue(EnumElement element, State& state) {
    // If no key attribute is specified, we use the name instead
    if (element.attributes.key.empty()) {
        element.attributes.key = element.name;
    }

    int n = sprintf(VerifierResult, "\"%s\",", std::string(element.attributes.key).c_str());
    VerifierResult += n;

    std::string type = join(state.stack, "::");
    n = sprintf(
        ConverterResult,
        "    if (v == \"%s\") { *val = %s::%s; }\n",
        std::string(element.attributes.key).c_str(), type.c_str(),
        std::string(element.name).c_str()
    );
    ConverterResult += n;
}

void handleVariable(Variable var, State& state) {
    std::string ver = std::string("codegen_") + join(state.stack, "_");

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

    std::string v = verifier(var.type, var, state);
    int n = sprintf(
        VerifierResult,
        "    %s->documentations.push_back({\"%s\",%s,%s,%s});\n",
        ver.c_str(), variableName.c_str(), v.c_str(),
        isOptional ? "Optional::Yes" : "Optional::No", state.commentBuffer.c_str()
    );
    VerifierResult += n;
    state.commentBuffer.clear();


    // Converter
    std::string converter;
    std::string name = join(state.stack, "::");
    if (auto it = state.structConverters.find(name); it != state.structConverters.end()) {
        converter = it->second;
    }

    n = sprintf(
        ScratchSpace,
        "    internal::bakeTo(dict, \"%s\", &res.%s);\n",
        variableName.c_str(),
        std::string(var.name).c_str()
    );

    converter += std::string(ScratchSpace, ScratchSpace + n);
    ScratchSpace += n;
    state.structConverters[name] = converter;
    std::vector<std::string> variables = state.structVariables[name];
    variables.push_back("\"" + variableName + "\"");
    state.structVariables[name] = variables;


    if (startsWith(var.type, "std::variant")) {
        std::string_view subtypes = var.type.substr(std::string_view("std::variant<").size());

        n = sprintf(
            ConverterResult,
            "void bakeTo(const ghoul::Dictionary& d, std::string_view key, %s* val) {\n",
            std::string(var.type).c_str()
        );
        ConverterResult += n;

        std::vector<std::string_view> ttypes = extractTemplateTypeList(subtypes);
        for (std::string_view subtype : ttypes) {
            n = sprintf(
                ConverterResult,
                "   if (d.hasValue<%s>(key)) { %s v; bakeTo(d, key, &v); *val = std::move(v); }\n",
                std::string(subtype).c_str(),
                std::string(subtype).c_str()
            );
            ConverterResult += n;
        }

        n = sprintf(ConverterResult, "}");
        ConverterResult += n;
    }
}

void finalizeVerifier(State& state) {
    std::string name;
    if (state.rootStruct.attributes.namespaceSpecifier.empty()) {
        name = fmt::format("openspace::{}", state.rootStruct.attributes.dictionary);
    }
    else {
        name = fmt::format(
            "openspace::{}::{}",
            state.rootStruct.attributes.namespaceSpecifier,
            state.rootStruct.attributes.dictionary
        );
    }

    std::array<char, 512> Buf;
    std::fill(Buf.begin(), Buf.end(), '\0');
    int n = sprintf(
        Buf.data(),
        R"(
namespace codegen {
template <typename T> openspace::documentation::Documentation doc() {
    static_assert(sizeof(T) == 0); // This should never be called
    return openspace::documentation::Documentation();
}
template <> openspace::documentation::Documentation doc<%s>() {
    using namespace openspace::documentation;
)",
        name.c_str()
    );

    std::memmove(
        VerifierResultBase + n,
        VerifierResultBase,
        VerifierResult - VerifierResultBase
    );
    std::memcpy(VerifierResultBase, Buf.data(), n);
    VerifierResult += n;

    std::string rootStruct = fmt::format("codegen_{}", state.rootStruct.name);
    n = sprintf(
        VerifierResult,
        R"(
    openspace::documentation::Documentation d = { "%s", "%s", std::move(%s->documentations) };
    delete %s;
    return d;
}
} // namespace codegen

)",
        std::string(state.rootStruct.attributes.dictionary).c_str(),
        std::string(state.rootStruct.attributes.dictionary).c_str(),
        rootStruct.c_str(),
        rootStruct.c_str()
    );
    VerifierResult += n;
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

    int n = sprintf(ConverterResult, "} // namespace codegen\n");
    ConverterResult += n;
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
                Struct s = parseStruct(line);
                state.stack.push_back({ StackElement::Type::Struct, s });
                state.structList.push_back(join(state.stack, "::"));
                state.structComments[std::string(s.name)] = state.commentBuffer;
                state.commentBuffer.clear();

                if (!s.attributes.dictionary.empty()) {
                    if (!state.rootStruct.name.empty() ||
                        !state.rootStruct.attributes.dictionary.empty())
                    {
                        throw std::runtime_error(fmt::format(
                            "Only the root struct can have a [[codegen::Dictionary()]] "
                            "attribute, found a second one here:\n{}",
                            s.name
                        ));
                    }
                    state.rootStruct = s;
                }

                handleStructStart(s, state);
                continue;
            }

            if (startsWith(line, "enum class")) {
                Enum e = parseEnum(line);
                state.stack.push_back({ StackElement::Type::Enum, e });
                state.enumList.push_back(join(state.stack, "::"));
                state.structComments[std::string(e.name)] = state.commentBuffer;
                state.commentBuffer.clear();

                handleEnumStart(state);
                continue;
            }

            if (startsWith(line, "enum")) {
                throw std::runtime_error(
                    "Old-style 'enum' not supported. Use 'enum class' instead"
                );
            }

            if (startsWith(line, "};")) {
                StackElement e = state.stack.back();
                switch (e.type) {
                    case StackElement::Type::Struct:
                        handleStructEnd(state);
                        break;
                    case StackElement::Type::Enum:
                        handleEnumEnd(state);
                        break;
                    default: throw std::logic_error("Unhandled case label");
                }

                state.stack.pop_back();
                continue;
            }
        }

        // If we got this far, we must be in a variable definition or an enum defintion
        // if the highest stack element is a struct, we are in a variable definition, if
        // the highest stack element is an enum, we are in an enum definition
        const StackElement& e = state.stack.back();
        switch (e.type) {
            case StackElement::Type::Struct:
                if (line.find(';') == std::string_view::npos) {
                    // No semicolon on this line but we are looking for a variable, so we
                    // are in a definition line that spans multiple lines
                    state.variableBuffer += std::string(line) + " ";
                    continue;
                }
                if (state.variableBuffer.empty()) {
                    Variable var = parseVariable(line);
                    handleVariable(var, state);
                }
                else {
                    state.variableBuffer += std::string(line);
                    Variable var = parseVariable(state.variableBuffer);
                    handleVariable(var, state);
                    state.variableBuffer.clear();
                }
                break;
            case StackElement::Type::Enum:
                handleEnumValue(parseEnumElement(line), state);
                break;
        }
    }

    if (state.rootStruct.name.empty() || state.rootStruct.attributes.dictionary.empty()) {
        throw std::runtime_error(
            "Root struct tag [[codegen::Dictionary]] is missing the renderable name"
        );
    }


    int n = sprintf(
        ScratchSpace,
        fileHeader,
        path.filename().string().c_str()
    );
    std::string newContent = std::string(ScratchSpace, ScratchSpace + n);
    ScratchSpace += n;

    finalizeVerifier(state);
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
