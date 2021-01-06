/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2021                                                               *
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

#include <array>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <string_view>
#include <unordered_map>

#ifdef WIN32
#pragma warning (disable : 4996)
#endif // WIN32

//#define PRINT_MEMORY_USAGE

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary";
    constexpr const int ErrorContext = 50;

    template <typename... Ts>
    [[noreturn]] void Fail(const char buf[], Ts... params) {
        printf(buf, params...);
        exit(EXIT_FAILURE);
    }
} // namespace

struct State {
    std::string_view line;
    std::string commentBuffer;
    std::vector<std::string_view> structs;

    std::map<std::string, std::string, std::less<>> structComments;
    std::pair<std::string, std::string> rootStruct;

    char* resultVerifierBase = nullptr;
    char* resultVerifier = nullptr;

    std::map<std::string, std::string, std::less<>> structConverters;
    char* resultConverterBase = nullptr;
    char* resultConverter = nullptr;

    char* scratchSpace = nullptr;
};

struct Struct {
    std::string_view name;

    std::string_view attributeRenderable;
};

struct Variable {
    std::string_view type;
    std::string_view name;

    struct Attributes {
        std::string_view key;
        std::string_view inRange;
    };
    Attributes attributes;
};

//
// Helper functions
//
std::string_view strip(std::string_view sv) {
    const size_t strBegin = sv.find_first_not_of(' ');
    if (strBegin == std::string::npos) {
        return sv;
    }

    const size_t strEnd = sv.find_last_not_of(' ');
    const size_t strRange = strEnd - strBegin + 1;
    return sv.substr(strBegin, strRange);
}

bool startsWith(std::string_view lhs, std::string_view rhs) {
    return lhs.size() >= rhs.size() && lhs.substr(0, rhs.size()) == rhs;
}

std::string join(const std::vector<std::string_view>& list, std::string_view sep) {
    size_t size = 0;
    for (std::string_view l : list) {
        size += l.size();
    }
    // this allocates space for one sep more than needed, but it simplifies the for loop
    size += sep.size() * (list.size() - 1);

    std::string res;
    res.reserve(size);
    for (std::string_view l : list) {
        res.append(l.data(), l.size());
        res.append(sep.data(), sep.size());
    }
    // Remove the last separator
    for (size_t i = 0; i < sep.size(); ++i) {
        res.pop_back();
    }
    return res;
}

std::string_view extractLine(std::string_view sv, size_t* cursor) {
    assert(cursor);
    assert(*cursor == 0 || sv[*cursor - 1] == '\n');
    const size_t p = sv.find('\n', *cursor);

    if (p != std::string_view::npos) {
        std::string_view line = sv.substr(*cursor, p - *cursor);
        *cursor = p + 1;
        return strip(line);
    }
    else {
        std::string_view line = sv.substr(*cursor);
        *cursor = std::string_view::npos;
        return strip(line);
    }
}

void handleCommentLine(State& state) {
    // Remove the starting // characters
    std::string_view comment = strip(state.line.substr(2));
    state.commentBuffer.append(comment);
}

std::string_view parseAttribute(std::string_view block, std::string_view name) {
    std::string key = std::string("codegen::" + std::string(name));
    const size_t p = block.find(key);
    if (p == std::string_view::npos) {
        return std::string_view();
    }
    const size_t beg = block.find('(', p) + 1;
    const size_t end = block.find(')', beg);

    std::string_view content = block.substr(beg, end - beg);
    return content;
}

Struct parseStruct(std::string_view line) {
    Struct s;

    size_t cursor = line.find(' ');
    assert(line.substr(0, cursor) == "struct");
    cursor++;

    const size_t beginAttribute = line.find("[[", cursor);
    if (beginAttribute != std::string_view::npos) {
        const size_t endAttribute = line.find("]]", beginAttribute) + 2;
        if (endAttribute == std::string_view::npos) {
            Fail(
                "Could not find closing bracket for attribute in struct:\n%s",
                std::string(line).c_str()
            );
        }

        size_t beginName = line.find('(', beginAttribute);
        if (beginName == std::string_view::npos) {
            Fail("No name specified for root struct:\n%s", std::string(line).c_str());
        }

        beginName++;
        const size_t endName = line.find(')', beginName);
        if (beginName == endName) {
            Fail("No name specified for root struct:\n%s", std::string(line).c_str());
        }

        s.attributeRenderable = line.substr(beginName, endName - beginName);
        cursor = endAttribute + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        Fail(
            "Missing space before the closing { of a struct:\n%s",
            std::string(line).c_str()
        );
    }
    s.name = line.substr(cursor, endStruct - cursor);
    return s;
}

Variable parseVariable(std::string_view line) {
    if (line.back() != ';') {
        Fail(
            "Variable definitions over multiple lines not supported:\n%s",
            std::string(line).c_str()
        );
    }
    // Remove the trailing ;
    line.remove_suffix(1);

    const size_t p1 = line.find(' ');
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        Fail("Too few spaces in variable definition:\n%s", std::string(line).c_str());
    }

    Variable res;
    res.type = line.substr(0, p1);
    res.name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        res.attributes.inRange = parseAttribute(attributes, "inrange");
        res.attributes.key = parseAttribute(attributes, "key");
    }

    return res;
}

std::string resolveComment(std::string comment) {
    if (size_t it = comment.find("codegen::description"); it != std::string::npos) {
        const size_t l = std::string_view("codegen::description").size();
        it += l;
        if (comment[it] != '(') {
            Fail(
                "Malformed codegen::description. Expected ( after token:\n%s",
                comment.c_str()
            );
        }
        it++;
        size_t end = comment.find(')', it);
        std::string identifier = comment.substr(it, end - it);
        comment = identifier + ".description";
    }
    else {
        comment = std::string("\"") + comment + "\"";
    }
    return comment;
}

void reportUnsupportedAttribute(std::string_view type, std::string_view name,
                                std::string_view value)
{
    if (!value.empty()) {
        Fail(
            "Attribute '%s' not supported for type '%s'",
            std::string(name).c_str(), std::string(type).c_str()
        );
    }
}

std::string addQualifier(std::string verifier, std::string qualifier,
                                 std::string parameters)
{
    return qualifier + "<" + verifier + ">(" + parameters + ")";
}

std::string verifierForType(std::string_view type, Variable::Attributes attributes) {
    if (type == "bool") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "BoolVerifier";
    }
    else if (type == "int") {
        std::string res = "IntVerifier";
        if (!attributes.inRange.empty()) {
            res = addQualifier(res, "InRangeVerifier", std::string(attributes.inRange));
        }
        return res;
    }
    else if (type == "double" || type == "float") {
        std::string res = "DoubleVerifier";
        if (!attributes.inRange.empty()) {
            res = addQualifier(res, "InRangeVerifier", std::string(attributes.inRange));
        }
        return res;
    }
    else if (type == "std::string") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "StringVerifier";
    }
    else if (type == "glm::ivec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "IntVector2Verifier";
    }
    else if (type == "glm::ivec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "IntVector3Verifier";
    }
    else if (type == "glm::ivec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "IntVector4Verifier";
    }
    else if (type == "glm::dvec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector2Verifier";
    }
    else if (type == "glm::dvec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector3Verifier";
    }
    else if (type == "glm::dvec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector4Verifier";
    }
    else if (type == "glm::vec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector2Verifier";
    }
    else if (type == "glm::vec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector3Verifier";
    }
    else if (type == "glm::vec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleVector4Verifier";
    }
    else if (type == "glm::dmat2x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x2Verifier";
    }
    else if (type == "glm::dmat2x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x3Verifier";
    }
    else if (type == "glm::dmat2x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x4Verifier";
    }
    else if (type == "glm::dmat3x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x2Verifier";
    }
    else if (type == "glm::dmat3x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x3Verifier";
    }
    else if (type == "glm::dmat3x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x4Verifier";
    }
    else if (type == "glm::dmat4x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x2Verifier";
    }
    else if (type == "glm::dmat4x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x3Verifier";
    }
    else if (type == "glm::dmat4x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x4Verifier";
    }
    else if (type == "glm::mat2x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x2Verifier";
    }
    else if (type == "glm::mat2x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x3Verifier";
    }
    else if (type == "glm::mat2x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix2x4Verifier";
    }
    else if (type == "glm::mat3x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x2Verifier";
    }
    else if (type == "glm::mat3x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x3Verifier";
    }
    else if (type == "glm::mat3x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix3x4Verifier";
    }
    else if (type == "glm::mat4x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x2Verifier";
    }
    else if (type == "glm::mat4x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x3Verifier";
    }
    else if (type == "glm::mat4x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        return "DoubleMatrix4x4Verifier";
    }
    else {
        return std::string();
    }
}

std::string verifier(std::string_view type, Variable::Attributes attributes, State& state)
{
    std::string_view v = verifierForType(type, attributes);
    
    if (!v.empty()) {
        return std::string("new ") + std::string(v);
    }
    else if (startsWith(type, "std::vector<")) {
        std::string_view subtype = type.substr(12);
        subtype.remove_suffix(1);

        std::string comments;
        if (auto it = state.structComments.find(subtype); it != state.structComments.end()) {
            comments = resolveComment(it->second);
        }

        std::string ver = verifier(subtype, attributes, state);
        std::array<char, 256> Buf;
        std::fill(Buf.begin(), Buf.end(), '\0');
        int n = sprintf(
            Buf.data(),
            "new TableVerifier({{\"*\",%s,Optional::Yes, %s}})\n",
            ver.c_str(),
            comments.c_str()
        );
        return std::string(Buf.data(), Buf.data() + n);
    }
    else {
        return std::string("codegen_") + join(state.structs, "_") + "_" + std::string(type);
    }
}

void handleStructStart(State& state) {
    std::string name = "codegen_" + join(state.structs, "_");
    int n = sprintf(
        state.resultVerifier,
        "    TableVerifier* %s = new TableVerifier;\n", name.c_str()
    );
    state.resultVerifier += n;
}

void handleStructEnd(State& state) {
    const bool isRootStruct = state.structs.size() == 1;

    std::string name = join(state.structs, "::");
    if (isRootStruct) {
        // This is the last struct to be closed, so it is the struct that the user will
        // ask for
        int n = sprintf(
            state.resultConverter,
            R"(
} // namespace internal

template <typename T> T bake(const ghoul::Dictionary& dict) { static_assert(sizeof(T) == 0); };
template <> %s bake<%s>(const ghoul::Dictionary& dict) {
    documentation::testSpecificationAndThrow(codegen::doc<%s>(), dict, "%s");
    %s res;
)",
            name.c_str(), name.c_str(),
            state.rootStruct.second.c_str(), state.rootStruct.second.c_str(),
            name.c_str()
        );
        state.resultConverter += n;
    }
    else {
        int n = sprintf(
            state.resultConverter,
            "template <> void bakeTo<%s>(const ghoul::Dictionary& d, std::string_view key, %s* val) {\n"
            "    %s& res = *val;\n"
            "    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);\n",
            name.c_str(), name.c_str(), name.c_str()
        );
        state.resultConverter += n;
    }


    auto it = state.structConverters.find(name);
    if (it == state.structConverters.end()) {
        Fail("Empty structs are not allowed:\n%s", name.c_str());
    }

    std::memcpy(state.resultConverter, it->second.data(), it->second.size());
    state.resultConverter += it->second.size();

    if (isRootStruct) {
        int n = sprintf(state.resultConverter, "    return res;\n}\n");
        state.resultConverter += n;
    }
    else {
        int n = sprintf(state.resultConverter, "}\n");
        state.resultConverter += n;
    }
}

void handleVariable(Variable var, State& state) {
    std::string ver = std::string("codegen_") + join(state.structs, "_");
    std::string variableName;

    if (var.attributes.key.empty()) {
        variableName = std::string(var.name);
        variableName[0] = static_cast<char>(::toupper(variableName[0]));
    }
    else {
        variableName = std::string(var.attributes.key);
    }

    state.commentBuffer = resolveComment(state.commentBuffer);

    bool isOptional = false;
    if (startsWith(var.type, "std::optional<")) {
        isOptional = true;
        var.type.remove_prefix(std::string_view("std::optional<").size());
        var.type.remove_suffix(1);
    }

    std::string v = verifier(var.type, var.attributes, state);
    int n = sprintf(
        state.resultVerifier,
        "    %s->documentations.push_back({\"%s\",%s,%s,%s});\n",
        ver.c_str(), variableName.c_str(), v.c_str(),
        isOptional ? "Optional::Yes" : "Optional::No", state.commentBuffer.c_str()
    );
    state.resultVerifier += n;
    state.commentBuffer.clear();


    // Converter
    std::string converter;
    std::string name = join(state.structs, "::");
    if (auto it = state.structConverters.find(name); it != state.structConverters.end()) {
        converter = it->second;
    }

    n = sprintf(
        state.scratchSpace,
        "    internal::bakeTo(dict, \"%s\", &res.%s);\n",
        variableName.c_str(),
        std::string(var.name).c_str()
    );
    
    converter += std::string(state.scratchSpace, state.scratchSpace + n);
    state.scratchSpace += n;
    state.structConverters[name] = converter;
}

std::string finalizeVerifier(State& state) {
    std::array<char, 512> Buf;
    std::fill(Buf.begin(), Buf.end(), '\0');
    int n = sprintf(
        Buf.data(),
        R"(
namespace codegen {
template <typename T> documentation::Documentation doc() {
    static_assert(sizeof(T) == 0); // This should never be called
}
template <> documentation::Documentation doc<%s>() {
    using namespace documentation;
)",
        state.rootStruct.second.c_str()
    );

    std::memmove(
        state.resultVerifierBase + n,
        state.resultVerifierBase,
        state.resultVerifier - state.resultVerifierBase
    );
    std::memcpy(state.resultVerifierBase, Buf.data(), n);
    state.resultVerifier += n;

    std::string rootStruct = std::string("codegen_") + state.rootStruct.first;
    n = sprintf(
        state.resultVerifier,
        R"(
    documentation::Documentation d = {
        "%s",
        "%s",
        std::move(%s->documentations)
    };
    delete %s;
    return d;
}
} // namespace codegen

)",
        state.rootStruct.second.c_str(),
        state.rootStruct.second.c_str(),
        rootStruct.c_str(),
        rootStruct.c_str()
    );
    state.resultVerifier += n;
    return std::string(state.resultVerifierBase, state.resultVerifier);
}

std::string finalizeConverter(State& state) {
    constexpr const char Preamble[] = R"(
namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); } // This should never be called
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { *val = static_cast<int>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) { *val = d.value<double>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
    if (d.hasKey(key)) {
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }
    else *val = std::nullopt;
}
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    std::vector<std::string_view> keys = dict.keys();
    val->reserve(keys.size());
    for (size_t i = 0; i < dict.size(); ++i) {
        T v;
        bakeTo(dict, keys[i], &v);
        val->push_back(std::move(v));
    }
}
)";

    // preamble contains \0 at the end
    std::memmove(
        state.resultConverterBase + sizeof(Preamble) - 1,
        state.resultConverterBase,
        state.resultConverter - state.resultConverterBase
    );
    std::memcpy(state.resultConverterBase, Preamble, sizeof(Preamble) - 1);
    state.resultConverter += sizeof(Preamble) - 1;

    int n = sprintf(state.resultConverter, "} // namespace codegen\n");
    state.resultConverter += n;
    return std::string(state.resultConverterBase, state.resultConverter);
}

std::string_view validCode(std::string_view code) {
    const size_t mainLocation = code.find(AttributeDictionary);
    if (mainLocation == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLocation + 1) != std::string_view::npos) {
        Fail("We currently only support one struct per file annotated with %s, "
            "including commented out ones", AttributeDictionary
        );
    }

    const size_t lastNewLine = code.rfind('\n', mainLocation) + 1;
    size_t cursor = code.find('{', lastNewLine) + 1;
    
    for (int counter = 1; counter > 0; cursor++) {
        if (code[cursor] == '{') {
            counter++;
        }
        if (code[cursor] == '}') {
            counter--;
        }
    }

    return code.substr(lastNewLine, cursor - lastNewLine + 1);
}

void handleFile(std::filesystem::path path) {
    std::string str;
    {
        std::ifstream f(path);
        str = std::string(std::istreambuf_iterator<char>{f}, {});
    }
    std::string_view content = strip(validCode(str));
    if (content.empty()) {
        return;
    }

    printf("Processing file '%s'\n", path.filename().string().c_str());

    std::filesystem::path destination = path;
    destination.replace_extension();
    destination.replace_filename(destination.filename().string() + "_codegen.cpp");

    // Some initial sanity checks
    if (std::string_view s = content.substr(0, 6); s != "struct") {
        Fail(
            "[[codegen::Dictionary]] needs a 'struct' declaration immediately before on "
            "the same line. Found %s", std::string(s).c_str()
        );
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        Fail(
            "Block comments are not allowed:\n%s",
            std::string(content.substr(p, ErrorContext)).c_str()
        );
    }

    if (size_t p = str.find(destination.filename().string());
        p == std::string_view::npos)
    {
        Fail("File does not include the generated file. This was probably a mistake");
    }


    State state;
    // The fivefold increase is a tunable parameter
    const size_t bufferSize = content.size() * 5;
    state.resultVerifierBase = new char[bufferSize];
    state.resultVerifier = state.resultVerifierBase;
    std::fill(state.resultVerifier, state.resultVerifier + bufferSize, '\0');

    state.resultConverterBase = new char[bufferSize];
    state.resultConverter = state.resultConverterBase;
    std::fill(state.resultConverter, state.resultConverter + bufferSize, '\0');

    char* scratchSpaceBase = new char[bufferSize];
    state.scratchSpace = scratchSpaceBase;
    std::fill(state.scratchSpace, state.scratchSpace + bufferSize, '\0');

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        state.line = extractLine(content, &cursor);
        if (state.line.empty()) {
            continue;
        }

        if (startsWith(state.line, "//")) {
            handleCommentLine(state);
            continue;
        }

        if (startsWith(state.line, "struct")) {
            Struct s = parseStruct(state.line);
            state.structs.push_back(s.name);
            state.structComments[std::string(s.name)] = state.commentBuffer;
            state.commentBuffer.clear();
            
            if (!s.attributeRenderable.empty()) {
                assert(state.rootStruct.first.empty() && state.rootStruct.second.empty());
                state.rootStruct.first = s.name;
                state.rootStruct.second = s.attributeRenderable;
            }

            handleStructStart(state);
            continue;
        }

        if (startsWith(state.line, "};")) {
            if (!state.commentBuffer.empty()) {
                Fail("Unaccounted for comments at the end of a struct definition");
            }

            handleStructEnd(state);
            state.structs.pop_back();
            continue;
        }

        // If we got this far, we must be in a variable definition
        Variable var = parseVariable(state.line);
        handleVariable(var, state);
    }

    if (state.rootStruct.first.empty() || state.rootStruct.second.empty()) {
        Fail("Root struct tag [[codegen::Dictionary]] is missing the renderable name");
    }


    std::ofstream output(destination);
    int n = sprintf(
        state.scratchSpace,
        R"(
// This file has been auto-generated by the codegen tool by running
// codegen either directly or indirectly on:  %s
// Do not change this file manually
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.
)",
        path.string().c_str()
    );

    output.write(state.scratchSpace, n);
    state.scratchSpace += n;

    std::string resultVerifier = finalizeVerifier(state);
    output.write(resultVerifier.c_str(), resultVerifier.size());
    std::string resultConverter = finalizeConverter(state);
    output.write(resultConverter.c_str(), resultConverter.size());


#ifdef PRINT_MEMORY_USAGE
    printf("Memory usage (Buffer: %zi)\n", bufferSize);
    printf("Converter: %lli\n", state.resultConverter - resultConverterBase);
    printf("Verifier: %lli\n", state.resultVerifier - resultVerifierBase);
    printf("Scratch: %lli\n", state.scratchSpace - scratchSpaceBase);
#endif // PRINT_MEMORY_USAGE
}

int main(int argc, char** argv) {
    if (argc != 3) {
        Fail(
            "Wrong number of parameters. Expected 3.\n"
            "Usage: codegen --file <file>\n"
            "       codegen --folder <folder>"
        );
    }

    std::string_view type = argv[1];
    std::string_view src = argv[2];
    if (type == "--file") {
        handleFile(src);
    }
    else if (type == "--folder") {
        namespace fs = std::filesystem;
        if (!fs::is_directory(src)) {
            Fail("When using --folder, the second parameter has to name a folder");
        }

        auto beg = std::chrono::high_resolution_clock::now();
        for (const fs::directory_entry& p : fs::recursive_directory_iterator(src)) {
            if (p.path().extension() == ".cpp") {
                handleFile(p.path());
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        printf("Time: %i\n", static_cast<int>((end - beg).count()/ 1000));
    }
    else {
        Fail(
            "Unrecognized argument '%s'. Expected '--file' or '--folder'\n",
            std::string(type).c_str()
        );
    }
}
