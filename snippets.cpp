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

#include "snippets.h"

#include <cassert>
#include <unordered_map>

namespace {
    constexpr const char BakeFunctionBool[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) {{ *val = d.value<bool>(key); }}\n";
    constexpr const char BakeFunctionInt[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) {{ *val = static_cast<int>(d.value<double>(key)); }}\n";
    constexpr const char BakeFunctionDouble[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) {{ *val = d.value<double>(key); }}\n";
    constexpr const char BakeFunctionFloat[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) {{ *val = static_cast<float>(d.value<double>(key)); }}\n";
    constexpr const char BakeFunctionString[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) {{ *val = d.value<std::string>(key); }}\n";
    constexpr const char BakeFunctionIVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) {{ *val = d.value<glm::dvec2>(key); }}\n";
    constexpr const char BakeFunctionIVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) {{ *val = d.value<glm::dvec3>(key); }}\n";
    constexpr const char BakeFunctionIVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) {{ *val = d.value<glm::dvec4>(key); }}\n";
    constexpr const char BakeFunctionDVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) {{ *val = d.value<glm::dvec2>(key); }}\n";
    constexpr const char BakeFunctionDVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) {{ *val = d.value<glm::dvec3>(key); }}\n";
    constexpr const char BakeFunctionDVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) {{ *val = d.value<glm::dvec4>(key); }}\n";
    constexpr const char BakeFunctionVec2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) {{ *val = d.value<glm::dvec2>(key); }}\n";
    constexpr const char BakeFunctionVec3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) {{ *val = d.value<glm::dvec3>(key); }}\n";
    constexpr const char BakeFunctionVec4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) {{ *val = d.value<glm::dvec4>(key); }}\n";
    constexpr const char BakeFunctionMat2x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) {{ *val = d.value<glm::dmat2x2>(key); }}\n";
    constexpr const char BakeFunctionMat2x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) {{ *val = d.value<glm::dmat2x3>(key); }}\n";
    constexpr const char BakeFunctionMat2x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) {{ *val = d.value<glm::dmat2x4>(key); }}\n";
    constexpr const char BakeFunctionMat3x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x2* val) {{ *val = d.value<glm::dmat3x2>(key); }}\n";
    constexpr const char BakeFunctionMat3x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) {{ *val = d.value<glm::dmat3x3>(key); }}\n";
    constexpr const char BakeFunctionMat3x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) {{ *val = d.value<glm::dmat3x4>(key); }}\n";
    constexpr const char BakeFunctionMat4x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) {{ *val = d.value<glm::dmat4x2>(key); }}\n";
    constexpr const char BakeFunctionMat4x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x3* val) {{ *val = d.value<glm::dmat4x3>(key); }}\n";
    constexpr const char BakeFunctionMat4x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) {{ *val = d.value<glm::dmat4x4>(key); }}\n";
    constexpr const char BakeFunctionDMat2x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x2* val) {{ *val = d.value<glm::dmat2x2>(key); }}\n";
    constexpr const char BakeFunctionDMat2x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x3* val) {{ *val = d.value<glm::dmat2x3>(key); }}\n";
    constexpr const char BakeFunctionDMat2x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x4* val) {{ *val = d.value<glm::dmat2x4>(key); }}\n";
    constexpr const char BakeFunctionDMat3x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x2* val) {{ *val = d.value<glm::dmat3x2>(key); }}\n";
    constexpr const char BakeFunctionDMat3x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) {{ *val = d.value<glm::dmat3x3>(key); }}\n";
    constexpr const char BakeFunctionDMat3x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x4* val) {{ *val = d.value<glm::dmat3x4>(key); }}\n";
    constexpr const char BakeFunctionDMat4x2[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x2* val) {{ *val = d.value<glm::dmat4x2>(key); }}\n";
    constexpr const char BakeFunctionDMat4x3[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x3* val) {{ *val = d.value<glm::dmat4x3>(key); }}\n";
    constexpr const char BakeFunctionDMat4x4[] = "void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) {{ *val = d.value<glm::dmat4x4>(key); }}\n";
    constexpr const char BakeFunctionMonostate[] = "void bakeTo(const ghoul::Dictionary&, std::string_view, std::monostate* val) {{ *val = std::monostate(); }}\n";
    constexpr const char BakeFunctionOptional[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {{
    if (d.hasKey(key)) {{
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }}
    else *val = std::nullopt;
}}
)";

    constexpr const char BakeFunctionVector[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {{
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    std::vector<std::string_view> keys = dict.keys();
    val->reserve(keys.size());
    for (size_t i = 0; i < dict.size(); ++i) {{
        T v;
        bakeTo(dict, keys[i], &v);
        val->push_back(std::move(v));
    }}
}}
)";

} // namespace

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