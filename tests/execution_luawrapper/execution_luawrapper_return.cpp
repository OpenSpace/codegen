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

#include "catch2/catch.hpp"

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <openspace/scripting/lualibrary.h>
#include <ghoul/lua/lua_helper.h>
#include <ghoul/misc/dictionary.h>
#include <optional>

namespace {
    [[codegen::luawrap]] void funcVoid() {
    }

    [[codegen::luawrap]] bool funcBool() {
        return true;
    }

    [[codegen::luawrap]] std::map<std::string, bool> funcBoolMap() {
        return {
            { "key1", true },
            { "key2", false },
            { "key3", true },
        };
    }

    [[codegen::luawrap]] std::optional<bool> funcBoolOptional() {
        return true;
    }

    [[codegen::luawrap]] std::optional<bool> funcBoolOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<bool> funcBoolVector() {
        return { false, true, true };
    }

    [[codegen::luawrap]] int funcInt() {
        return 1;
    }

    [[codegen::luawrap]] std::map<std::string, int> funcIntMap() {
        return {
            { "key1", 1 },
            { "key2", 2 },
            { "key3", 3 }
        };
    }

    [[codegen::luawrap]] std::optional<int> funcIntOptional() {
        return 1;
    }

    [[codegen::luawrap]] std::optional<int> funcIntOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<int> funcIntVector() {
        return { 1, 2, 3 };
    }

    [[codegen::luawrap]] double funcDouble() {
        return 1.1;
    }

    [[codegen::luawrap]] std::map<std::string, double> funcDoubleMap() {
        return {
            { "key1", 1.1 },
            { "key2", 2.2 },
            { "key3", 3.3 }
        };
    }

    [[codegen::luawrap]] std::optional<double> funcDoubleOptional() {
        return 1.1;
    }

    [[codegen::luawrap]] std::optional<double> funcDoubleOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<double> funcDoubleVector() {
        return { 1.1, 2.2, 3.3 };
    }

    [[codegen::luawrap]] float funcFloat() {
        return 1.f;
    }

    [[codegen::luawrap]] std::map<std::string, float> funcFloatMap() {
        return {
            { "key1", 1.1f },
            { "key2", 2.2f },
            { "key3", 3.3f }
        };
    }

    [[codegen::luawrap]] std::optional<float> funcFloatOptional() {
        return 1.1f;
    }

    [[codegen::luawrap]] std::optional<float> funcFloatOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<float> funcFloatVector() {
        return { 1.f, 2.f, 3.f };
    }

    [[codegen::luawrap]] std::string funcString() {
        return "abc";
    }

    [[codegen::luawrap]] std::map<std::string, std::string> funcStringMap() {
        return {
            { "key1", "abc" },
            { "key2", "def" },
            { "key3", "ghi" }
        };
    }

    [[codegen::luawrap]] std::optional<std::string> funcStringOptional() {
        return "abc";
    }

    [[codegen::luawrap]] std::optional<std::string> funcStringOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<std::string> funcStringVector() {
        return { "abc", "def", "ghi" };
    }

    [[codegen::luawrap]] std::filesystem::path funcPath() {
        return std::filesystem::path("abc");
    }

    [[codegen::luawrap]] std::map<std::string, std::filesystem::path> funcPathMap() {
        return {
            { "key1", std::filesystem::path("abc") },
            { "key2", std::filesystem::path("def") },
            { "key3", std::filesystem::path("ghi") }
        };
    }

    [[codegen::luawrap]] std::optional<std::filesystem::path> funcPathOptional() {
        return std::filesystem::path("abc");
    }

    [[codegen::luawrap]] std::optional<std::filesystem::path> funcPathOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<std::filesystem::path> funcPathVector() {
        return {
            std::filesystem::path("abc"),
            std::filesystem::path("def"),
            std::filesystem::path("ghi")
        };
    }

    [[codegen::luawrap]] glm::ivec2 funcIvec2() {
        return glm::ivec2(1, 2);
    }

    [[codegen::luawrap]] std::map<std::string, glm::ivec2> funcIvec2Map() {
        return {
            { "key1", glm::ivec2(1, 2) },
            { "key2", glm::ivec2(3, 4) },
            { "key3", glm::ivec2(5, 6) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::ivec2> funcIvec2Optional() {
        return glm::ivec2(1, 2);
    }

    [[codegen::luawrap]] std::optional<glm::ivec2> funcIvec2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::ivec2> funcIvec2Vector() {
        return { glm::ivec2(1, 2), glm::ivec2(3, 4), glm::ivec2(5, 6) };
    }

    [[codegen::luawrap]] glm::ivec3 funcIvec3() {
        return glm::ivec3(1, 2, 3);
    }

    [[codegen::luawrap]] std::map<std::string, glm::ivec3> funcIvec3Map() {
        return {
            { "key1", glm::ivec3(1, 2, 3) },
            { "key2", glm::ivec3(4, 5, 6) },
            { "key3", glm::ivec3(7, 8, 9) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::ivec3> funcIvec3Optional() {
        return glm::ivec3(1, 2, 3);
    }

    [[codegen::luawrap]] std::optional<glm::ivec3> funcIvec3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::ivec3> funcIvec3Vector() {
        return {
            glm::ivec3(1, 2, 3),
            glm::ivec3(4, 5, 6),
            glm::ivec3(7, 8, 9)
        };
    }

    [[codegen::luawrap]] glm::ivec4 funcIvec4() {
        return glm::ivec4(1, 2, 3, 4);
    }

    [[codegen::luawrap]] std::map<std::string, glm::ivec4> funcIvec4Map() {
        return {
            { "key1", glm::ivec4(1, 2, 3, 4) },
            { "key2", glm::ivec4(5, 6, 7, 8) },
            { "key3", glm::ivec4(9, 10, 11, 12) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::ivec4> funcIvec4Optional() {
        return glm::ivec4(1, 2, 3, 4);
    }

    [[codegen::luawrap]] std::optional<glm::ivec4> funcIvec4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::ivec4> funcIvec4Vector() {
        return {
            glm::ivec4(1, 2, 3, 4),
            glm::ivec4(5, 6, 7, 8),
            glm::ivec4(9, 10, 11, 12)
        };
    }

    [[codegen::luawrap]] glm::dvec2 funcDvec2() {
        return glm::dvec2(1.1, 2.2);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dvec2> funcDvec2Map() {
        return {
            { "key1", glm::dvec2(1.1, 2.2) },
            { "key2", glm::dvec2(3.3, 4.4) },
            { "key3", glm::dvec2(5.5, 6.6) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dvec2> funcDvec2Optional() {
        return glm::dvec2(1.1, 2.2);
    }

    [[codegen::luawrap]] std::optional<glm::dvec2> funcDvec2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dvec2> funcDvec2Vector() {
        return {
            glm::dvec2(1.1, 2.2),
            glm::dvec2(3.3, 4.4),
            glm::dvec2(5.5, 6.6)
        };
    }

    [[codegen::luawrap]] glm::dvec3 funcDvec3() {
        return glm::dvec3(1.1, 2.2, 3.3);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dvec3> funcDvec3Map() {
        return {
            { "key1", glm::dvec3(1.1, 2.2, 3.3) },
            { "key2", glm::dvec3(4.4, 5.5, 6.6) },
            { "key3", glm::dvec3(7.7, 8.8, 9.9) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dvec3> funcDvec3Optional() {
        return glm::dvec3(1.1, 2.2, 3.3);
    }

    [[codegen::luawrap]] std::optional<glm::dvec3> funcDvec3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dvec3> funcDvec3Vector() {
        return {
            glm::dvec3(1.1, 2.2, 3.3),
            glm::dvec3(4.4, 5.5, 6.6),
            glm::dvec3(7.7, 8.8, 9.9)
        };
    }

    [[codegen::luawrap]] glm::dvec4 funcDvec4() {
        return glm::dvec4(1.1, 2.2, 3.3, 4.4);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dvec4> funcDvec4Map() {
        return {
            { "key1", glm::dvec4(1.1, 2.2, 3.3, 4.4) },
            { "key2", glm::dvec4(5.5, 6.6, 7.7, 8.8) },
            { "key3", glm::dvec4(9.9, 10.10, 11.11, 12.12) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dvec4> funcDvec4Optional() {
        return glm::dvec4(1.1, 2.2, 3.3, 4.4);
    }

    [[codegen::luawrap]] std::optional<glm::dvec4> funcDvec4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dvec4> funcDvec4Vector() {
        return {
            glm::dvec4(1.1, 2.2, 3.3, 4.4),
            glm::dvec4(5.5, 6.6, 7.7, 8.8),
            glm::dvec4(9.9, 10.10, 11.11, 12.12)
        };
    }

    [[codegen::luawrap]] glm::vec2 funcVec2() {
        return glm::vec2(1.1f, 2.2f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::vec2> funcVec2Map() {
        return {
            { "key1", glm::vec2(1.1f, 2.2f) },
            { "key2", glm::vec2(3.3f, 4.4f) },
            { "key3", glm::vec2(5.5f, 6.6f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::vec2> funcVec2Optional() {
        return glm::vec2(1.1f, 2.2f);
    }

    [[codegen::luawrap]] std::optional<glm::vec2> funcVec2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::vec2> funcVec2Vector() {
        return {
            glm::vec2(1.1f, 2.2f),
            glm::vec2(3.3f, 4.4f),
            glm::vec2(5.5f, 6.6f)
        };
    }

    [[codegen::luawrap]] glm::vec3 funcVec3() {
        return glm::vec3(1.1f, 2.2f, 3.3f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::vec3> funcVec3Map() {
        return {
            { "key1", glm::vec3(1.1f, 2.2f, 3.3f) },
            { "key2", glm::vec3(4.4f, 5.5f, 6.6f) },
            { "key3", glm::vec3(7.7f, 8.8f, 9.9f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::vec3> funcVec3Optional() {
        return glm::vec3(1.1f, 2.2f, 3.3f);
    }

    [[codegen::luawrap]] std::optional<glm::vec3> funcVec3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::vec3> funcVec3Vector() {
        return {
            glm::vec3(1.1f, 2.2f, 3.3f),
            glm::vec3(4.4f, 5.5f, 6.6f),
            glm::vec3(7.7f, 8.8f, 9.9f)
        };
    }

    [[codegen::luawrap]] glm::vec4 funcVec4() {
        return glm::vec4(1.1f, 2.2f, 3.3f, 4.4f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::vec4> funcVec4Map() {
        return {
            { "key1", glm::vec4(1.1f, 2.2f, 3.3f, 4.4f) },
            { "key2", glm::vec4(5.5f, 6.6f, 7.7f, 8.8f) },
            { "key3", glm::vec4(9.9f, 10.10f, 11.11f, 12.12f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::vec4> funcVec4Optional() {
        return glm::vec4(1.1f, 2.2f, 3.3f, 4.4f);
    }

    [[codegen::luawrap]] std::optional<glm::vec4> funcVec4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::vec4> funcVec4Vector() {
        return {
            glm::vec4(1.1f, 2.2f, 3.3f, 4.4f),
            glm::vec4(5.5f, 6.6f, 7.7f, 8.8f),
            glm::vec4(9.9f, 10.10f, 11.11f, 12.12f)
        };
    }

    [[codegen::luawrap]] glm::mat2x2 funcMat2x2() {
        return glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat2x2> funcMat2x2Map() {
        return {
            { "key1", glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f) },
            { "key2", glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f) },
            { "key3", glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat2x2> funcMat2x2Optional() {
        return glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f);
    }

    [[codegen::luawrap]] std::optional<glm::mat2x2> funcMat2x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat2x2> funcMat2x2Vector() {
        return {
            glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f),
            glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f),
            glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f)
        };
    }

    [[codegen::luawrap]] glm::mat2x3 funcMat2x3() {
        return glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat2x3> funcMat2x3Map() {
        return {
            { "key1", glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f) },
            { "key2", glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f) },
            { "key3", glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat2x3> funcMat2x3Optional() {
        return glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
    }

    [[codegen::luawrap]] std::optional<glm::mat2x3> funcMat2x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat2x3> funcMat2x3Vector() {
        return {
            glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f),
            glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f),
            glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
        };
    }

    [[codegen::luawrap]] glm::mat2x4 funcMat2x4() {
        return glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat2x4> funcMat2x4Map() {
        return {
            {
                "key1",
                glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
            },
            {
                "key2",
                glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
            },
            {
                "key3",
                glm::mat2x4(
                    17.17f, 18.18f, 19.19f, 20.20f,
                    21.21f, 22.22f, 23.23f, 24.24f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat2x4> funcMat2x4Optional() {
        return glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);
    }

    [[codegen::luawrap]] std::optional<glm::mat2x4> funcMat2x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat2x4> funcMat2x4Vector() {
        return {
            glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f),
            glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f),
            glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
        };
    }

    [[codegen::luawrap]] glm::mat3x2 funcMat3x2() {
        return glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat3x2> funcMat3x2Map() {
        return {
            { "key1", glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f) },
            { "key2", glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f) },
            { "key3", glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat3x2> funcMat3x2Optional() {
        return glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
    }

    [[codegen::luawrap]] std::optional<glm::mat3x2> funcMat3x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat3x2> funcMat3x2Vector() {
        return {
            glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f),
            glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f),
            glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
        };
    }

    [[codegen::luawrap]] glm::mat3x3 funcMat3x3() {
        return glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat3x3> funcMat3x3Map() {
        return {
            {
                "key1",
                glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
            },
            {
                "key2",
                glm::mat3x3(
                    10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
                    15.15f, 16.16f, 17.17f, 18.18f
                )
            },
            {
                "key3",
                glm::mat3x3(
                    19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
                    24.24f, 25.25f, 26.26f, 27.27f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat3x3> funcMat3x3Optional() {
        return glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
    }

    [[codegen::luawrap]] std::optional<glm::mat3x3> funcMat3x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat3x3> funcMat3x3Vector() {
        return {
            glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f),
            glm::mat3x3(
                10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
                15.15f, 16.16f, 17.17f, 18.18f
            ),
            glm::mat3x3(
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
                24.24f, 25.25f, 26.26f, 27.27f
            )
        };
    }

    [[codegen::luawrap]] glm::mat3x4 funcMat3x4() {
        return glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat3x4> funcMat3x4Map() {
        return {
            {
                "key1",
                glm::mat3x4(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                    7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
                )
            },
            {
                "key2",
                glm::mat3x4(
                    13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                    19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
                )
            },
            {
                "key3",
                glm::mat3x4(
                    25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                    31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat3x4> funcMat3x4Optional() {
        return glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        );
    }

    [[codegen::luawrap]] std::optional<glm::mat3x4> funcMat3x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat3x4> funcMat3x4Vector() {
        return {
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            ),
            glm::mat3x4(
                13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            ),
            glm::mat3x4(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        };
    }

    [[codegen::luawrap]] glm::mat4x2 funcMat4x2() {
        return glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat4x2> funcMat4x2Map() {
        return {
            {
                "key1",
                glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
            },
            {
                "key2",
                glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
            },
            {
                "key3",
                glm::mat4x2(
                    17.17f, 18.18f, 19.19f, 20.20f,
                    21.21f, 22.22f, 23.23f, 24.24f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat4x2> funcMat4x2Optional() {
        return glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f);
    }

    [[codegen::luawrap]] std::optional<glm::mat4x2> funcMat4x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat4x2> funcMat4x2Vector() {
        return {
            glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f),
            glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f),
            glm::mat4x2(
                17.17f, 18.18f, 19.19f, 20.20f,
                21.21f, 22.22f, 23.23f, 24.24f
            )
        };
    }

    [[codegen::luawrap]] glm::mat4x3 funcMat4x3() {
        return glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat4x3> funcMat4x3Map() {
        return {
            {
                "key1",
                glm::mat4x3(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                    7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
                )
            },
            {
                "key2",
                glm::mat4x3(
                    13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                    19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
                )
            },
            {
                "key3",
                glm::mat4x3(
                    25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                    31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat4x3> funcMat4x3Optional() {
        return glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        );
    }

    [[codegen::luawrap]] std::optional<glm::mat4x3> funcMat4x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat4x3> funcMat4x3Vector() {
        return {
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            ),
            glm::mat4x3(
                13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            ),
            glm::mat4x3(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        };
    }

    [[codegen::luawrap]] glm::mat4x4 funcMat4x4() {
        return glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::mat4x4> funcMat4x4Map() {
        return {
            {
                "key1",
                glm::mat4x4(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                    9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
                )
            },
            {
                "key2",
                glm::mat4x4(
                    17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
                    25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
                )
            },
            {
                "key3",
                glm::mat4x4(
                    33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
                    41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::mat4x4> funcMat4x4Optional() {
        return glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        );
    }

    [[codegen::luawrap]] std::optional<glm::mat4x4> funcMat4x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::mat4x4> funcMat4x4Vector() {
        return {
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            ),
            glm::mat4x4(
                17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
            ),
            glm::mat4x4(
                33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
                41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
            )
        };
    }

    [[codegen::luawrap]] glm::dmat2x2 funcDMat2x2() {
        return glm::dmat2x2(1.1, 2.2, 3.3, 4.4);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat2x2> funcDMat2x2Map() {
        return {
            { "key1", glm::dmat2x2(1.1, 2.2, 3.3, 4.4) },
            { "key2", glm::dmat2x2(5.5, 6.6, 7.7, 8.8) },
            { "key3", glm::dmat2x2(9.9, 10.10, 11.11, 12.12) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x2> funcDMat2x2Optional() {
        return glm::dmat2x2(1.1, 2.2, 3.3, 4.4);
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x2> funcDMat2x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat2x2> funcDMat2x2Vector() {
        return {
            glm::dmat2x2(1.1, 2.2, 3.3, 4.4),
            glm::dmat2x2(5.5, 6.6, 7.7, 8.8),
            glm::dmat2x2(9.9, 10.10, 11.11, 12.12)
        };
    }

    [[codegen::luawrap]] glm::dmat2x3 funcDMat2x3() {
        return glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat2x3> funcDMat2x3Map() {
        return {
            { "key1", glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6) },
            { "key2", glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12) },
            { "key3", glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x3> funcDMat2x3Optional() {
        return glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x3> funcDMat2x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat2x3> funcDMat2x3Vector() {
        return {
            glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6),
            glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12),
            glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        };
    }

    [[codegen::luawrap]] glm::dmat2x4 funcDMat2x4() {
        return glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat2x4> funcDMat2x4Map() {
        return {
            {
                "key1",
                glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
            },
            {
                "key2",
                glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
            },
            {
                "key3",
                glm::dmat2x4(
                    17.17, 18.18, 19.19, 20.20,
                    21.21, 22.22, 23.23, 24.24
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x4> funcDMat2x4Optional() {
        return glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8);
    }

    [[codegen::luawrap]] std::optional<glm::dmat2x4> funcDMat2x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat2x4> funcDMat2x4Vector() {
        return {
            glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8),
            glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16),
            glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
        };
    }

    [[codegen::luawrap]] glm::dmat3x2 funcDMat3x2() {
        return glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat3x2> funcDMat3x2Map() {
        return {
            { "key1", glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6) },
            { "key2", glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12) },
            { "key3", glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18) }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x2> funcDMat3x2Optional() {
        return glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x2> funcDMat3x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat3x2> funcDMat3x2Vector() {
        return {
            glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6),
            glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12),
            glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        };
    }

    [[codegen::luawrap]] glm::dmat3x3 funcDMat3x3() {
        return glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat3x3> funcDMat3x3Map() {
        return {
            {
                "key1",
                glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
            },
            {
                "key2",
                glm::dmat3x3(
                    10.10, 11.11, 12.12, 13.13, 14.14,
                    15.15, 16.16, 17.17, 18.18
                )
            },
            {
                "key3",
                glm::dmat3x3(
                    19.19, 20.20, 21.21, 22.22, 23.23,
                    24.24, 25.25, 26.26, 27.27
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x3> funcDMat3x3Optional() {
        return glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9);
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x3> funcDMat3x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat3x3> funcDMat3x3Vector() {
        return {
            glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9),
            glm::dmat3x3(
                10.10, 11.11, 12.12, 13.13, 14.14,
                15.15, 16.16, 17.17, 18.18
            ),
            glm::dmat3x3(
                19.19, 20.20, 21.21, 22.22, 23.23,
                24.24, 25.25, 26.26, 27.27
            )
        };
    }

    [[codegen::luawrap]] glm::dmat3x4 funcDMat3x4() {
        return glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat3x4> funcDMat3x4Map() {
        return {
            {
                "key1",
                glm::dmat3x4(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                    7.7, 8.8, 9.9, 10.10, 11.11, 12.12
                )
            },
            {
                "key2",
                glm::dmat3x4(
                    13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                    19.19, 20.20, 21.21, 22.22, 23.23, 24.24
                )
            },
            {
                "key3",
                glm::dmat3x4(
                    25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                    31.31, 32.32, 33.33, 34.34, 35.35, 36.36
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x4> funcDMat3x4Optional() {
        return glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x4> funcDMat3x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat3x4> funcDMat3x4Vector() {
        return {
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            ),
            glm::dmat3x4(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            ),
            glm::dmat3x4(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        };
    }

    [[codegen::luawrap]] glm::dmat4x2 funcDMat4x2() {
        return glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8);
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat4x2> funcDMat4x2Map() {
        return {
            {
                "key1",
                glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
            },
            {
                "key2",
                glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
            },
            {
                "key3",
                glm::dmat4x2(
                    17.17, 18.18, 19.19, 20.20,
                    21.21, 22.22, 23.23, 24.24
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x2> funcDMat4x2Optional() {
        return glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8);
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x2> funcDMat4x2OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat4x2> funcDMat4x2Vector() {
        return {
            glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8),
            glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16),
            glm::dmat4x2(
                17.17, 18.18, 19.19, 20.20,
                21.21, 22.22, 23.23, 24.24
            )
        };
    }

    [[codegen::luawrap]] glm::dmat4x3 funcDMat4x3() {
        return glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat4x3> funcDMat4x3Map() {
        return {
            {
                "key1",
                glm::dmat4x3(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                    7.7, 8.8, 9.9, 10.10, 11.11, 12.12
                )
            },
            {
                "key2",
                glm::dmat4x3(
                    13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                    19.19, 20.20, 21.21, 22.22, 23.23, 24.24
                )
            },
            {
                "key3",
                glm::dmat4x3(
                    25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                    31.31, 32.32, 33.33, 34.34, 35.35, 36.36
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x3> funcDMat4x3Optional() {
        return glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x3> funcDMat4x3OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat4x3> funcDMat4x3Vector() {
        return {
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            ),
            glm::dmat4x3(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            ),
            glm::dmat4x3(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        };
    }

    [[codegen::luawrap]] glm::mat4x4 funcDMat4x4() {
        return glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat4x4> funcDMat4x4Map() {
        return {
            {
                "key1",
                glm::dmat4x4(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                    9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
                )
            },
            {
                "key2",
                glm::dmat4x4(
                    17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
                    25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
                )
            },
            {
                "key3",
                glm::dmat4x4(
                    33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
                    41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x4> funcDMat4x4Optional() {
        return glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        );
    }

    [[codegen::luawrap]] std::optional<glm::dmat4x4> funcDMat4x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat4x4> funcDMat4x4Vector() {
        return {
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            ),
            glm::dmat4x4(
                17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
            ),
            glm::dmat4x4(
                33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
                41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
            )
        };
    }

    [[codegen::luawrap]] std::tuple<bool, int> funcTupleBoolInt() {
        return { true, 1 };
    }

    [[codegen::luawrap]] std::tuple<double, float, std::string> funcTupleDoubleFloatStringDouble() {
        return { 1.1, 2.2f, "abc" };
    }

    [[codegen::luawrap]] std::variant<bool, int> funcVariantBoolIntBool() {
        return true;
    }

    [[codegen::luawrap]] std::variant<bool, int> funcVariantBoolIntInt() {
        return 1;
    }

    [[codegen::luawrap]] std::variant<double, float, std::string> funcVariantDoubleFloatStringDouble() {
        return 1.1;
    }

    [[codegen::luawrap]] std::variant<double, float, std::string> funcVariantDoubleFloatStringFloat() {
        return 1.f;
    }

    [[codegen::luawrap]] std::variant<double, float, std::string> funcVariantDoubleFloatStringString() {
        return "abc";
    }

#include "execution_luawrapper_return_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Return:  void") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVoid;
    CHECK(func.name == "funcVoid");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcBool;
    CHECK(func.name == "funcBool");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcBoolMap;
    CHECK(func.name == "funcBoolMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Boolean");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", true);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", false);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", false);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcBoolOptional;
    CHECK(func.name == "funcBoolOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcBoolOptional;
    CHECK(func.name == "funcBoolOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcBoolVector;
    CHECK(func.name == "funcBoolVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Boolean]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, true);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, false);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, false);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcInt;
    CHECK(func.name == "funcInt");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcIntMap;
    CHECK(func.name == "funcIntMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIntVector;
    CHECK(func.name == "funcIntVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Integer]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDouble;
    CHECK(func.name == "funcDouble");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleMap;
    CHECK(func.name == "funcDoubleMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Number");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2.2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3.3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleVector;
    CHECK(func.name == "funcDoubleVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Number]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2.2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3.3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  float") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloat;
    CHECK(func.name == "funcFloat");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatMap;
    CHECK(func.name == "funcFloatMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Number");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1.1f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2.2f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3.3f);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatVector;
    CHECK(func.name == "funcFloatVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Number]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1.1f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2.2f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3.3f);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  string") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcString;
    CHECK(func.name == "funcString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringMap;
    CHECK(func.name == "funcStringMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", "def"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", "ghi"s);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringOptional with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringOptional w/o value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringVector") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringVector;
    CHECK(func.name == "funcStringVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[String]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, "def"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, "ghi"s);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  path") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPath;
    CHECK(func.name == "funcPath");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, std::filesystem::path("abc"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathMap;
    CHECK(func.name == "funcPathMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Path");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", std::filesystem::path("abc"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", std::filesystem::path("def"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", std::filesystem::path("ghi"));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathOptional;
    CHECK(func.name == "funcPathOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, std::filesystem::path("abc"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathOptional;
    CHECK(func.name == "funcPathOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathVector;
    CHECK(func.name == "funcPathVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Path]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, std::filesystem::path("abc"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, std::filesystem::path("def"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, std::filesystem::path("ghi"));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2;
    CHECK(func.name == "funcIvec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec2(1, 2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Map;
    CHECK(func.name == "funcIvec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec2(1, 2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec2(3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec2(5, 6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec2(1, 2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Vector;
    CHECK(func.name == "funcIvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec2(1, 2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec2(3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec2(5, 6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3;
    CHECK(func.name == "funcIvec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec3(1, 2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Map;
    CHECK(func.name == "funcIvec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec3(1, 2, 3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec3(4, 5, 6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec3(7, 8, 9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec3(1, 2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Vector;
    CHECK(func.name == "funcIvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec3(1, 2, 3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec3(4, 5, 6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec3(7, 8, 9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4;
    CHECK(func.name == "funcIvec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec4(1, 2, 3, 4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Map;
    CHECK(func.name == "funcIvec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec4(1, 2, 3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec4(5, 6, 7, 8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec4(9, 10, 11, 12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec4(1, 2, 3, 4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Vector;
    CHECK(func.name == "funcIvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec4(1, 2, 3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec4(5, 6, 7, 8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec4(9, 10, 11, 12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2;
    CHECK(func.name == "funcDvec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec2(1.1, 2.2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Map;
    CHECK(func.name == "funcDvec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec2(1.1, 2.2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec2(3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec2(5.5, 6.6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec2(1.1, 2.2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Vector;
    CHECK(func.name == "funcDvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec2(1.1, 2.2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec2(3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec2(5.5, 6.6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3;
    CHECK(func.name == "funcDvec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Map;
    CHECK(func.name == "funcDvec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec3(1.1, 2.2, 3.3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec3(4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec3(7.7, 8.8, 9.9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Vector;
    CHECK(func.name == "funcDvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec3(1.1, 2.2, 3.3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec3(4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec3(7.7, 8.8, 9.9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4;
    CHECK(func.name == "funcDvec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Map;
    CHECK(func.name == "funcDvec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec4(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Vector;
    CHECK(func.name == "funcDvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec4(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2;
    CHECK(func.name == "funcVec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec2(1.1f, 2.2f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Map;
    CHECK(func.name == "funcVec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec2(1.1f, 2.2f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec2(3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec2(5.5f, 6.6f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec2(1.1f, 2.2f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Vector;
    CHECK(func.name == "funcVec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec2(1.1f, 2.2f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec2(3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec2(5.5f, 6.6f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3;
    CHECK(func.name == "funcVec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Map;
    CHECK(func.name == "funcVec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec3(1.1f, 2.2f, 3.3f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec3(4.4f, 5.5f, 6.6f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec3(7.7f, 8.8f, 9.9f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Vector;
    CHECK(func.name == "funcVec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec3(1.1f, 2.2f, 3.3f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec3(4.4f, 5.5f, 6.6f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec3(7.7f, 8.8f, 9.9f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4;
    CHECK(func.name == "funcVec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Map;
    CHECK(func.name == "funcVec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Vector;
    CHECK(func.name == "funcVec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2;
    CHECK(func.name == "funcMat2x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Map;
    CHECK(func.name == "funcMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Vector;
    CHECK(func.name == "funcMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3;
    CHECK(func.name == "funcMat2x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Map;
    CHECK(func.name == "funcMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Vector;
    CHECK(func.name == "funcMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4;
    CHECK(func.name == "funcMat2x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Map;
    CHECK(func.name == "funcMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Vector;
    CHECK(func.name == "funcMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2;
    CHECK(func.name == "funcMat3x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Map;
    CHECK(func.name == "funcMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Vector;
    CHECK(func.name == "funcMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3;
    CHECK(func.name == "funcMat3x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Map;
    CHECK(func.name == "funcMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Vector;
    CHECK(func.name == "funcMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4;
    CHECK(func.name == "funcMat3x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Map;
    CHECK(func.name == "funcMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x4(
            13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Vector;
    CHECK(func.name == "funcMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x4(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  mat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2;
    CHECK(func.name == "funcMat4x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Map;
    CHECK(func.name == "funcMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Vector;
    CHECK(func.name == "funcMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3;
    CHECK(func.name == "funcMat4x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Map;
    CHECK(func.name == "funcMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Vector;
    CHECK(func.name == "funcMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x3(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4;
    CHECK(func.name == "funcMat4x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Map;
    CHECK(func.name == "funcMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Vector;
    CHECK(func.name == "funcMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2;
    CHECK(func.name == "funcDMat2x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Map;
    CHECK(func.name == "funcDMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Vector;
    CHECK(func.name == "funcDMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3;
    CHECK(func.name == "funcDMat2x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Map;
    CHECK(func.name == "funcDMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Vector;
    CHECK(func.name == "funcDMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4;
    CHECK(func.name == "funcDMat2x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Map;
    CHECK(func.name == "funcDMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Vector;
    CHECK(func.name == "funcDMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2;
    CHECK(func.name == "funcDMat3x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Map;
    CHECK(func.name == "funcDMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Vector;
    CHECK(func.name == "funcDMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3;
    CHECK(func.name == "funcDMat3x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Map;
    CHECK(func.name == "funcDMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Vector;
    CHECK(func.name == "funcDMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4;
    CHECK(func.name == "funcDMat3x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5., 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Map;
    CHECK(func.name == "funcDMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Vector;
    CHECK(func.name == "funcDMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2;
    CHECK(func.name == "funcDMat4x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Map;
    CHECK(func.name == "funcDMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x2");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Vector;
    CHECK(func.name == "funcDMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x2]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3;
    CHECK(func.name == "funcDMat4x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Map;
    CHECK(func.name == "funcDMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x3(
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.0
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Vector;
    CHECK(func.name == "funcDMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x3]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x3(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4;
    CHECK(func.name == "funcDMat4x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Map;
    CHECK(func.name == "funcDMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Vector;
    CHECK(func.name == "funcDMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x4]");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  tuple(bool,int)") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcTupleBoolInt;
    CHECK(func.name == "funcTupleBoolInt");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  tuple(double,float,string)") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcTupleDoubleFloatStringDouble;
    CHECK(func.name == "funcTupleDoubleFloatStringDouble");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(bool,int) / bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantBoolIntBool;
    CHECK(func.name == "funcVariantBoolIntBool");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(bool,int) / int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantBoolIntInt;
    CHECK(func.name == "funcVariantBoolIntInt");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, float, string) / double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatStringDouble;
    CHECK(func.name == "funcVariantDoubleFloatStringDouble");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.0);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, float, string) / float") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatStringFloat;
    CHECK(func.name == "funcVariantDoubleFloatStringFloat");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, float, string) / string") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatStringString;
    CHECK(func.name == "funcVariantDoubleFloatStringString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}
