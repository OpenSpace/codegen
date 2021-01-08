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

#include <fmt/format.h>
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

/* TODO
 - Check for extra keys in the bake function to protect against misspellings
 - Check for unknown codegen::attributes and throw error
 - Check for mixing of different attributes (inrange + greater, for example)
 - Need support for a std::map?
 - Add ability to include an external parameter (in replacement for the ReferencingVerifier
 - Name used for ReferencingVerifier has to be generated in a better way (including some more information to disambiguate)
 - std::variant<glm::vec3, glm::vec4> type detection stops at space after , not at the end
*/

#ifdef WIN32
#pragma warning (disable : 4996)
#endif // WIN32

#define PRINT_MEMORY_USAGE

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary";
    constexpr const int ErrorContext = 50;


    constexpr int BufferSize = 32768;
    char* VerifierResultBase = nullptr;
    char* VerifierResult = nullptr;

    char* ConverterResultBase = nullptr;
    char* ConverterResult = nullptr;

    char* ScratchSpaceBase = nullptr;
    char* ScratchSpace = nullptr;
} // namespace


struct StackElement {
    enum class Type { Struct, Enum };
    Type type;
    std::string_view name;
};

struct Struct {
    std::string_view name;

    struct Attributes {
        std::string_view dictionary;
        std::string_view namespaceSpecifier;
    };
    Attributes attributes;
};

struct Enum {
    std::string_view name;
};

struct EnumElement {
    std::string_view name;
    
    struct Attributes {
        std::string_view key;
    };
    Attributes attributes;
};

struct Variable {
    std::string_view type;
    std::string_view name;

    struct Attributes {
        std::string_view key;
        std::string_view reference;

        std::string_view inRange;
        std::string_view notInRange;
        std::string_view less;
        std::string_view lessEqual;
        std::string_view greater;
        std::string_view greaterEqual;
        std::string_view unequal;
        std::string_view inList;
        std::string_view notInList;
    };
    Attributes attributes;
};


struct State {
    std::string commentBuffer;
    std::string variableBuffer;
    std::vector<StackElement> stack;

    std::map<std::string, std::string, std::less<>> structComments;
    Struct rootStruct;
    std::map<std::string, std::string, std::less<>> structConverters;

    std::map<std::string, bool, std::less<>> typeUsage;

    std::vector<std::string> structList;
    std::vector<std::string> enumList;
};


namespace {
    constexpr const char BakeFunctionBool[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }\n";
    constexpr const char BakeFunctionInt[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { *val = static_cast<int>(d.value<double>(key)); }\n";
    constexpr const char BakeFunctionDouble[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) { *val = d.value<double>(key); }\n";
    constexpr const char BakeFunctionFloat[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }\n";
    constexpr const char BakeFunctionString[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }\n";
    constexpr const char BakeFunctionIVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) { *val = d.value<glm::dvec2>(key); }\n";
    constexpr const char BakeFunctionIVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) { *val = d.value<glm::dvec3>(key); }\n";
    constexpr const char BakeFunctionIVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) { *val = d.value<glm::dvec4>(key); }\n";
    constexpr const char BakeFunctionDVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) { *val = d.value<glm::dvec2>(key); }\n";
    constexpr const char BakeFunctionDVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) { *val = d.value<glm::dvec3>(key); }\n";
    constexpr const char BakeFunctionDVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) { *val = d.value<glm::dvec4>(key); }\n";
    constexpr const char BakeFunctionVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) { *val = d.value<glm::dvec2>(key); }\n";
    constexpr const char BakeFunctionVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) { *val = d.value<glm::dvec3>(key); }\n";
    constexpr const char BakeFunctionVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) { *val = d.value<glm::dvec4>(key); }\n";
    constexpr const char BakeFunctionMat2x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) { *val = d.value<glm::dmat2x2>(key); }\n";
    constexpr const char BakeFunctionMat2x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) { *val = d.value<glm::dmat2x3>(key); }\n";
    constexpr const char BakeFunctionMat2x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) { *val = d.value<glm::dmat2x4>(key); }\n";
    constexpr const char BakeFunctionMat3x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x2* val) { *val = d.value<glm::dmat3x2>(key); }\n";
    constexpr const char BakeFunctionMat3x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) { *val = d.value<glm::dmat3x3>(key); }\n";
    constexpr const char BakeFunctionMat3x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) { *val = d.value<glm::dmat3x4>(key); }\n";
    constexpr const char BakeFunctionMat4x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) { *val = d.value<glm::dmat4x2>(key); }\n";
    constexpr const char BakeFunctionMat4x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x3* val) { *val = d.value<glm::dmat4x3>(key); }\n";
    constexpr const char BakeFunctionMat4x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) { *val = d.value<glm::dmat4x4>(key); }\n";
    constexpr const char BakeFunctionDMat2x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x2* val) { *val = d.value<glm::dmat2x2>(key); }\n";
    constexpr const char BakeFunctionDMat2x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x3* val) { *val = d.value<glm::dmat2x3>(key); }\n";
    constexpr const char BakeFunctionDMat2x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x4* val) { *val = d.value<glm::dmat2x4>(key); }\n";
    constexpr const char BakeFunctionDMat3x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x2* val) { *val = d.value<glm::dmat3x2>(key); }\n";
    constexpr const char BakeFunctionDMat3x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) { *val = d.value<glm::dmat3x3>(key); }\n";
    constexpr const char BakeFunctionDMat3x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x4* val) { *val = d.value<glm::dmat3x4>(key); }\n";
    constexpr const char BakeFunctionDMat4x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x2* val) { *val = d.value<glm::dmat4x2>(key); }\n";
    constexpr const char BakeFunctionDMat4x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x3* val) { *val = d.value<glm::dmat4x3>(key); }\n";
    constexpr const char BakeFunctionDMat4x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) { *val = d.value<glm::dmat4x4>(key); }\n";
    constexpr const char BakeFunctionOptional[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
    if (d.hasKey(key)) {
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }
    else *val = std::nullopt;
}
)";
    constexpr const char BakeFunctionVector[] = R"(
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
    constexpr const char BakeFunctionMonostate[] = "void bakeTo(const ghoul::Dictionary&, std::string_view, std::monostate* val) { *val = std::monostate(); }\n";

    void reportUnsupportedAttribute(std::string_view type, std::string_view name,
        std::string_view value)
    {
        if (!value.empty()) {
            throw std::runtime_error(fmt::format(
                "Attribute '{}' not supported for type '{}'", name, type
            ));
        }
    }

    std::string addQualifier(std::string verifier, std::string qualifier,
        std::string parameters)
    {
        return fmt::format(
            "{}<{}>({})", std::move(qualifier), std::move(verifier), std::move(parameters)
        );
    }

} // namespace

std::string_view fileHeader() {
    return R"(
// This file has been auto-generated by the codegen tool by running codegen either
// directly or indirectly on:  %s
//
// Do not change this file manually as any change will be automatically overwritten,
// instead change the struct tagged with "codegen::Dictionary" in the main file from which
// the code in this file was generated.
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.
)";
}

std::string_view bakeFunctionPreamble() {
    return R"(
namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); } // This should never be called
)";
}

std::string_view bakeFunctionForType(std::string_view type) {
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
        { "std::optional",  BakeFunctionOptional },
        { "std::vector",    BakeFunctionVector },
        { "std::monostate", BakeFunctionMonostate }
    };

    const auto it = BakeFunctions.find(type);
    return it != BakeFunctions.end() ? it->second : std::string_view();
}

std::string verifierForType(std::string_view type, Variable::Attributes attributes, const State& state) {
    if (type == "bool") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "BoolVerifier";
    }
    else if (type == "int") {
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);

        std::string res = "IntVerifier";
        if (!attributes.inRange.empty()) {
            res = addQualifier(res, "InRangeVerifier", std::string(attributes.inRange));
        }
        if (!attributes.notInRange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", std::string(attributes.notInRange));
        }
        if (!attributes.less.empty()) {
            res = addQualifier(res, "LessVerifier", std::string(attributes.less));
        }
        if (!attributes.lessEqual.empty()) {
            res = addQualifier(res, "LessEqualVerifier", std::string(attributes.lessEqual));
        }
        if (!attributes.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", std::string(attributes.greater));
        }
        if (!attributes.greaterEqual.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", std::string(attributes.greaterEqual));
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", std::string(attributes.unequal));
        }
        return res;
    }
    else if (type == "double" || type == "float") {
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);

        std::string res = "DoubleVerifier";
        if (!attributes.inRange.empty()) {
            res = addQualifier(res, "InRangeVerifier", std::string(attributes.inRange));
        }
        if (!attributes.notInRange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", std::string(attributes.notInRange));
        }
        if (!attributes.less.empty()) {
            res = addQualifier(res, "LessVerifier", std::string(attributes.less));
        }
        if (!attributes.lessEqual.empty()) {
            res = addQualifier(res, "LessEqualVerifier", std::string(attributes.lessEqual));
        }
        if (!attributes.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", std::string(attributes.greater));
        }
        if (!attributes.greaterEqual.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", std::string(attributes.greaterEqual));
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", std::string(attributes.unequal));
        }
        return res;
    }
    else if (type == "std::string") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        
        std::string res = "StringVerifier";
        if (!attributes.inList.empty()) {
            std::string attr = std::string(attributes.inList);
            res = addQualifier(res, "InListVerifier", "{" + attr + "}");
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", std::string(attributes.unequal));
        }
        return res;
    }
    else if (type == "glm::ivec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "IntVector2Verifier";
    }
    else if (type == "glm::ivec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "IntVector3Verifier";
    }
    else if (type == "glm::ivec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "IntVector4Verifier";
    }
    else if (type == "glm::dvec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector2Verifier";
    }
    else if (type == "glm::dvec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector3Verifier";
    }
    else if (type == "glm::dvec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector4Verifier";
    }
    else if (type == "glm::vec2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector2Verifier";
    }
    else if (type == "glm::vec3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector3Verifier";
    }
    else if (type == "glm::vec4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleVector4Verifier";
    }
    else if (type == "glm::dmat2x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x2Verifier";
    }
    else if (type == "glm::dmat2x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x3Verifier";
    }
    else if (type == "glm::dmat2x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x4Verifier";
    }
    else if (type == "glm::dmat3x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x2Verifier";
    }
    else if (type == "glm::dmat3x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x3Verifier";
    }
    else if (type == "glm::dmat3x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x4Verifier";
    }
    else if (type == "glm::dmat4x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x2Verifier";
    }
    else if (type == "glm::dmat4x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x3Verifier";
    }
    else if (type == "glm::dmat4x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x4Verifier";
    }
    else if (type == "glm::mat2x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x2Verifier";
    }
    else if (type == "glm::mat2x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x3Verifier";
    }
    else if (type == "glm::mat2x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix2x4Verifier";
    }
    else if (type == "glm::mat3x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x2Verifier";
    }
    else if (type == "glm::mat3x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x3Verifier";
    }
    else if (type == "glm::mat3x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix3x4Verifier";
    }
    else if (type == "glm::mat4x2") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x2Verifier";
    }
    else if (type == "glm::mat4x3") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x3Verifier";
    }
    else if (type == "glm::mat4x4") {
        reportUnsupportedAttribute(type, "inrange", attributes.inRange);
        reportUnsupportedAttribute(type, "notinrange", attributes.notInRange);
        reportUnsupportedAttribute(type, "less", attributes.less);
        reportUnsupportedAttribute(type, "lessequal", attributes.lessEqual);
        reportUnsupportedAttribute(type, "greater", attributes.greater);
        reportUnsupportedAttribute(type, "greaterequal", attributes.greaterEqual);
        reportUnsupportedAttribute(type, "unequal", attributes.unequal);
        reportUnsupportedAttribute(type, "inlist", attributes.inList);
        reportUnsupportedAttribute(type, "notinlist", attributes.notInList);
        return "DoubleMatrix4x4Verifier";
    }
    else if (type == "std::monostate") {
        if (attributes.reference.empty()) {
            throw std::runtime_error(
                "Using a monostate needs to have an attribute 'reference'"
            );
        }

        return fmt::format(
            "ReferencingVerifier({})",
            attributes.reference == "this" ?
                fmt::format("\"{}\"", state.rootStruct.attributes.dictionary) :
                std::string(attributes.reference)
        );
    }
    else {
        return std::string();
    }
}



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

std::string join(const std::vector<StackElement>& list, std::string_view sep) {
    std::vector<std::string_view> names;
    names.reserve(list.size());
    for (const StackElement& e : list) {
        names.push_back(e.name);
    }
    return join(names, sep);
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

void handleCommentLine(std::string_view line, State& state) {
    // Remove the starting // characters
    std::string_view comment = strip(line.substr(2));
    state.commentBuffer.append(comment);
    state.commentBuffer.append(" ");
}

std::string_view parseAttribute(std::string_view block, std::string_view name) {
    std::string key = std::string("codegen::" + std::string(name));
    const size_t p = block.find(key);
    if (p == std::string_view::npos) {
        return std::string_view();
    }
    const size_t beg = block.find('(', p) + 1;
    
    if (const size_t end = block.find(')', beg); end == std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "Attribute parameter has unterminated parameter list:\n{}", block
        ));
    }

    size_t cursor = beg;
    int paranthesisCount = 1;
    while (cursor < block.size() && paranthesisCount > 0) {
        if (block[cursor] == '(') {
            paranthesisCount++;
        }
        if (block[cursor] == ')') {
            paranthesisCount--;
        }

        cursor++;
    }
    cursor--;

    std::string_view content = block.substr(beg, cursor - beg);
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
        std::string_view block = line.substr(
            beginAttribute,
            endAttribute - beginAttribute
        );
        s.attributes.dictionary = parseAttribute(block, "Dictionary");
        if (s.attributes.dictionary.empty()) {
            throw std::runtime_error(
                fmt::format("No name specified for root struct:\n{}", line)
            );
        }

        s.attributes.namespaceSpecifier = parseAttribute(block, "namespace");
        cursor = endAttribute + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Missing space before the closing {{ of a struct:\n{}", line)
        );
    }
    s.name = line.substr(cursor, endStruct - cursor);
    return s;
}

Enum parseEnum(std::string_view line) {
    Enum e;

    size_t cursor = line.find(' ', line.find(' ') + 1);
    assert(line.substr(0, cursor) == "enum class");
    cursor++;

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Missing space before the closing {{ of a struct:\n{}", line)
        );
    }
    e.name = line.substr(cursor, endStruct - cursor);
    return e;
}

EnumElement parseEnumElement(std::string_view line) {
    if (line.back() == ',') {
        line.remove_suffix(1);
    }

    size_t i = line.find(' ');
    EnumElement e;
    e.name = line.substr(0, i);
    if (i != std::string_view::npos) {
        std::string_view attributes = line.substr(i + 1);
        e.attributes.key = parseAttribute(attributes, "key");
    }
    return e;
}

Variable parseVariable(std::string_view line) {
    // Remove the trailing ;
    line.remove_suffix(1);

    const size_t p1 = line.find(' ');
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Too few spaces in variable definition:\n{}", line)
        );
    }

    Variable res;
    res.type = line.substr(0, p1);
    res.name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        res.attributes.key = parseAttribute(attributes, "key");
        res.attributes.reference = parseAttribute(attributes, "reference");

        res.attributes.inRange = parseAttribute(attributes, "inrange");
        res.attributes.notInRange = parseAttribute(attributes, "notinrange");
        res.attributes.less = parseAttribute(attributes, "less");
        res.attributes.lessEqual = parseAttribute(attributes, "lessequal");
        res.attributes.greater = parseAttribute(attributes, "greater");
        res.attributes.greaterEqual = parseAttribute(attributes, "greaterequal");
        res.attributes.unequal = parseAttribute(attributes, "unequal");
        res.attributes.inList = parseAttribute(attributes, "inlist");
        res.attributes.notInList = parseAttribute(attributes, "notinlist");
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



std::string verifier(std::string_view type, Variable::Attributes attributes, State& state)
{
    std::string v = verifierForType(type, attributes, state);
    
    if (!v.empty()) {
        return std::string("new ") + v;
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
        std::vector<StackElement> stack = state.stack;
        stack.push_back({ StackElement::Type::Struct, type });
        std::string structCandidate = join(stack, "::");

        stack.pop_back();
        stack.push_back({ StackElement::Type::Enum, type });
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

        return std::string("codegen_") + join(state.stack, "_") + "_" + std::string(type);
    }
}

void handleStructStart(State& state) {
    std::string name = "codegen_" + join(state.stack, "_");
    int n = sprintf(
        VerifierResult,
        "    TableVerifier* %s = new TableVerifier;\n", name.c_str()
    );
    VerifierResult += n;
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

        // This is the last struct to be closed, so it is the struct that the user will
        // ask for
        int n = sprintf(
            ConverterResult,
            R"(
} // namespace internal

template <typename T> T bake(const ghoul::Dictionary& dict) { static_assert(sizeof(T) == 0); };
template <> %s bake<%s>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<%s>(), dict, "%s");
    %s res;
)",
            name.c_str(), name.c_str(),
            fqName.c_str(),
            //fqName.c_str(),
            std::string(state.rootStruct.attributes.dictionary).c_str(),
            //std::string(state.rootStruct.attributes.dictionary).c_str(),
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

    std::memcpy(ConverterResult, it->second.data(), it->second.size());
    ConverterResult += it->second.size();

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
        state.typeUsage["std::optional"] = true;
        var.type.remove_prefix(std::string_view("std::optional<").size());
        var.type.remove_suffix(1);
    }
    if (startsWith(var.type, "std::vector<")) {
        state.typeUsage["std::vector"] = true;
    }

    state.typeUsage[std::string(var.type)] = true;
    std::string v = verifier(var.type, var.attributes, state);
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
    openspace::documentation::Documentation d = {
        "%s",
        "%s",
        std::move(%s->documentations)
    };
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
    std::string_view preamble = bakeFunctionPreamble();
    std::memcpy(ScratchSpace, preamble.data(), preamble.size());
    ScratchSpace += preamble.size();


    for (const std::pair<const std::string, bool>& kv : state.typeUsage) {
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

std::string_view validCode(std::string_view code) {
    const size_t mainLocation = code.find(AttributeDictionary);
    if (mainLocation == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLocation + 1) != std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "We currently only support one struct per file annotated with {}, "
            "including commented out ones",
            AttributeDictionary
        ));
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
        throw std::runtime_error(fmt::format(
            "[[codegen::Dictionary]] needs a 'struct' declaration immediately before on "
            "the same line. Found {}", s
        ));
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "Block comments are not allowed:\n{}", content.substr(p, ErrorContext)
        ));
    }

    if (size_t p = str.find(destination.filename().string());
        p == std::string_view::npos)
    {
        throw std::runtime_error(
            "File does not include the generated file. This was probably a mistake"
        );
    }


    State state;
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
                handleCommentLine(line, state);
                continue;
            }

            if (startsWith(line, "struct")) {
                Struct s = parseStruct(line);
                state.stack.push_back({ StackElement::Type::Struct, s.name });
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

                handleStructStart(state);
                continue;
            }

            if (startsWith(line, "enum class")) {
                Enum e = parseEnum(line);
                state.stack.push_back({ StackElement::Type::Enum, e.name });
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


    std::ofstream output(destination);
    int n = sprintf(
        ScratchSpace,
        R"(
// This file has been auto-generated by the codegen tool by running codegen either
// directly or indirectly on:  %s
//
// Do not change this file manually as any change will be automatically overwritten,
// instead change the struct tagged with "codegen::Dictionary" in the main file from which
// the code in this file was generated.
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.
)",
        path.filename().string().c_str()
    );

    output.write(ScratchSpace, n);
    ScratchSpace += n;

    finalizeVerifier(state);
    output.write(VerifierResultBase, VerifierResult - VerifierResultBase);

    finalizeConverter(state);
    output.write(ConverterResultBase, ConverterResult - ConverterResultBase);

#ifdef PRINT_MEMORY_USAGE
    printf("Memory usage (Buffer: %i)\n", BufferSize);
    printf("Converter: %lli\n", ConverterResult - ConverterResultBase);
    printf("Verifier: %lli\n", VerifierResult - VerifierResultBase);
    printf("Scratch: %lli\n", ScratchSpace - ScratchSpaceBase);
#endif // PRINT_MEMORY_USAGE
}

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::runtime_error(
            "Wrong number of parameters. Expected 3.\n"
            "Usage: codegen --file <file>\n"
            "       codegen --folder <folder>"
        );
    }

    VerifierResultBase = new char[BufferSize];
    ConverterResultBase = new char[BufferSize];
    ScratchSpaceBase = new char[BufferSize];

    std::string_view type = argv[1];
    std::string_view src = argv[2];
    if (type == "--file") {
        handleFile(src);
    }
    else if (type == "--folder") {
        namespace fs = std::filesystem;
        if (!fs::is_directory(src)) {
            throw std::runtime_error(
                "When using --folder, the second parameter has to name a folder"
            );
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
        throw std::runtime_error(fmt::format(
            "Unrecognized argument '{}'. Expected '--file' or '--folder'\n", type
        ));
    }
}
