/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2023                                                               *
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
        return 1.1f;
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
        return { 1.1f, 2.2f, 3.3f };
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

    [[codegen::luawrap]] glm::dmat4x4 funcDMat4x4() {
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


    [[codegen::luawrap]] ghoul::Dictionary funcDictionary() {
        using namespace std::string_literals;

        ghoul::Dictionary d;
        d.setValue("a", 1.1);
        d.setValue("b", "abc"s);
        d.setValue("c", glm::dvec3(2.2, 3.3, 4.4));
        return d;
    }

    [[codegen::luawrap]] std::map<std::string, ghoul::Dictionary> funcDictionaryMap() {
        using namespace std::string_literals;

        ghoul::Dictionary d1;
        d1.setValue("a", 1.1);
        d1.setValue("b", "abc"s);
        d1.setValue("c", glm::dvec3(2.2, 3.3, 4.4));

        ghoul::Dictionary d2;
        d2.setValue("a", 5.5);
        d2.setValue("b", "def"s);
        d2.setValue("c", glm::dvec3(6.6, 7.7, 8.8));

        ghoul::Dictionary d3;
        d3.setValue("a", 9.9);
        d3.setValue("b", "ghi"s);
        d3.setValue("c", glm::dvec3(10.10, 11.11, 12.12));

        return {
            { "key1", d1 },
            { "key2", d2 },
            { "key3", d3 }
        };
    }

    [[codegen::luawrap]] std::optional<ghoul::Dictionary> funcDictionaryOptional() {
        using namespace std::string_literals;

        ghoul::Dictionary d;
        d.setValue("a", 1.1);
        d.setValue("b", "abc"s);
        d.setValue("c", glm::dvec3(2.2, 3.3, 4.4));
        return d;
    }

    [[codegen::luawrap]] std::optional<ghoul::Dictionary> funcDictionaryOptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<ghoul::Dictionary> funcDictionaryVector() {
        using namespace std::string_literals;

        ghoul::Dictionary d1;
        d1.setValue("a", 1.1);
        d1.setValue("b", "abc"s);
        d1.setValue("c", glm::dvec3(2.2, 3.3, 4.4));

        ghoul::Dictionary d2;
        d2.setValue("a", 5.5);
        d2.setValue("b", "def"s);
        d2.setValue("c", glm::dvec3(6.6, 7.7, 8.8));

        ghoul::Dictionary d3;
        d3.setValue("a", 9.9);
        d3.setValue("b", "ghi"s);
        d3.setValue("c", glm::dvec3(10.10, 11.11, 12.12));

        return { d1, d2, d3 };
    }

    [[codegen::luawrap]] std::tuple<glm::dvec3> funcTupleVec3() {
        return glm::dvec3(1.1, 2.2, 3.3);
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

    [[codegen::luawrap]] std::variant<double, glm::dvec3, std::string> funcVariantDvec3FloatStringDouble() {
        return 1.1;
    }

    [[codegen::luawrap]] std::variant<double, glm::dvec3, std::string> funcVariantDvec3FloatStringDvec3() {
        return glm::dvec3(1.1, 2.2, 3.3);
    }

    [[codegen::luawrap]] std::variant<double, glm::dvec3, std::string> funcVariantDvec3FloatStringString() {
        return "abc";
    }

#include "execution_luawrapper_return_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Return:  void") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVoid;
    CHECK(func.name == "funcVoid");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBool;
    CHECK(func.name == "funcBool");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    bool val = ghoul::lua::value<bool>(state);
    CHECK(val == true);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolMap;
    CHECK(func.name == "funcBoolMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Boolean");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, bool> val =
        ghoul::lua::value<std::map<std::string, bool>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == true);
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == false);
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == true);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolOptional;
    CHECK(func.name == "funcBoolOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    bool val = ghoul::lua::value<bool>(state);
    CHECK(val == true);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolOptionalNullopt;
    CHECK(func.name == "funcBoolOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  boolVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolVector;
    CHECK(func.name == "funcBoolVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<bool> val = ghoul::lua::value<std::vector<bool>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == false);
    CHECK(val[1] == true);
    CHECK(val[2] == true);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncInt;
    CHECK(func.name == "funcInt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    int val = ghoul::lua::value<int>(state);
    CHECK(val == 1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntMap;
    CHECK(func.name == "funcIntMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, int> val = ghoul::lua::value<std::map<std::string, int>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == 1);
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == 2);
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == 3);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntOptional;
    CHECK(func.name == "funcIntOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Integer?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    int val = ghoul::lua::value<int>(state);
    CHECK(val == 1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntOptionalNullopt;
    CHECK(func.name == "funcIntOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Integer?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  intVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntVector;
    CHECK(func.name == "funcIntVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Integer[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<int> val = ghoul::lua::value<std::vector<int>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == 1);
    CHECK(val[1] == 2);
    CHECK(val[2] == 3);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDouble;
    CHECK(func.name == "funcDouble");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    double val = ghoul::lua::value<double>(state);
    CHECK(val == 1.1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleMap;
    CHECK(func.name == "funcDoubleMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Number");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, double> val =
        ghoul::lua::value<std::map<std::string, double>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == 1.1);
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == 2.2);
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == 3.3);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    double val = ghoul::lua::value<double>(state);
    CHECK(val == 1.1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleOptionalNullopt;
    CHECK(func.name == "funcDoubleOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  doubleVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleVector;
    CHECK(func.name == "funcDoubleVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<double> val = ghoul::lua::value<std::vector<double>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == 1.1);
    CHECK(val[1] == 2.2);
    CHECK(val[2] == 3.3);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  float") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloat;
    CHECK(func.name == "funcFloat");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    float val = ghoul::lua::value<float>(state);
    CHECK(val == 1.1f);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatMap;
    CHECK(func.name == "funcFloatMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Number");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, float> val =
        ghoul::lua::value<std::map<std::string, float>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == 1.1f);
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == 2.2f);
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == 3.3f);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    float val = ghoul::lua::value<float>(state);
    CHECK(val == 1.1f);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatOptionalNullopt;
    CHECK(func.name == "funcFloatOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  floatVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatVector;
    CHECK(func.name == "funcFloatVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<float> val = ghoul::lua::value<std::vector<float>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == 1.1f);
    CHECK(val[1] == 2.2f);
    CHECK(val[2] == 3.3f);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  string") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncString;
    CHECK(func.name == "funcString");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::string val = ghoul::lua::value<std::string>(state);
    CHECK(val == "abc");
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncStringMap;
    CHECK(func.name == "funcStringMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, std::string> val =
        ghoul::lua::value<std::map<std::string, std::string>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == "abc");
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == "def");
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == "ghi");
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncStringOptional;
    CHECK(func.name == "funcStringOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::string val = ghoul::lua::value<std::string>(state);
    CHECK(val == "abc");
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncStringOptionalNullopt;
    CHECK(func.name == "funcStringOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  stringVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncStringVector;
    CHECK(func.name == "funcStringVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<std::string> val = ghoul::lua::value<std::vector<std::string>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == "abc");
    CHECK(val[1] == "def");
    CHECK(val[2] == "ghi");
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  path") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPath;
    CHECK(func.name == "funcPath");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Path");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::filesystem::path val = ghoul::lua::value<std::filesystem::path>(state);
    CHECK(val == std::filesystem::path("abc"));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathMap;
    CHECK(func.name == "funcPathMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Path");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, std::filesystem::path> val =
        ghoul::lua::value<std::map<std::string, std::filesystem::path>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == std::filesystem::path("abc"));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == std::filesystem::path("def"));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == std::filesystem::path("ghi"));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathOptional;
    CHECK(func.name == "funcPathOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Path?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::filesystem::path val = ghoul::lua::value<std::filesystem::path>(state);
    CHECK(val == std::filesystem::path("abc"));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathOptionalNullopt;
    CHECK(func.name == "funcPathOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Path?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  pathVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathVector;
    CHECK(func.name == "funcPathVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Path[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<std::filesystem::path> val =
        ghoul::lua::value<std::vector<std::filesystem::path>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == std::filesystem::path("abc"));
    CHECK(val[1] == std::filesystem::path("def"));
    CHECK(val[2] == std::filesystem::path("ghi"));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2;
    CHECK(func.name == "funcIvec2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec2 val = ghoul::lua::value<glm::ivec2>(state);
    CHECK(val == glm::ivec2(1, 2));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Map;
    CHECK(func.name == "funcIvec2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> ivec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::ivec2> val =
        ghoul::lua::value<std::map<std::string, glm::ivec2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::ivec2(1, 2));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::ivec2(3, 4));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::ivec2(5, 6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec2 val = ghoul::lua::value<glm::ivec2>(state);
    CHECK(val == glm::ivec2(1, 2));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2OptionalNullopt;
    CHECK(func.name == "funcIvec2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Vector;
    CHECK(func.name == "funcIvec2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector val = ghoul::lua::value<std::vector<glm::ivec2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::ivec2(1, 2));
    CHECK(val[1] == glm::ivec2(3, 4));
    CHECK(val[2] == glm::ivec2(5, 6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3;
    CHECK(func.name == "funcIvec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec3 val = ghoul::lua::value<glm::ivec3>(state);
    CHECK(val == glm::ivec3(1, 2, 3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Map;
    CHECK(func.name == "funcIvec3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> ivec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::ivec3> val =
        ghoul::lua::value<std::map<std::string, glm::ivec3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::ivec3(1, 2, 3));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::ivec3(4, 5, 6));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::ivec3(7, 8, 9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec3 val = ghoul::lua::value<glm::ivec3>(state);
    CHECK(val == glm::ivec3(1, 2, 3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3OptionalNullopt;
    CHECK(func.name == "funcIvec3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Vector;
    CHECK(func.name == "funcIvec3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::ivec3> val = ghoul::lua::value<std::vector<glm::ivec3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::ivec3(1, 2, 3));
    CHECK(val[1] == glm::ivec3(4, 5, 6));
    CHECK(val[2] == glm::ivec3(7, 8, 9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4;
    CHECK(func.name == "funcIvec4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec4 val = ghoul::lua::value<glm::ivec4>(state);
    CHECK(val == glm::ivec4(1, 2, 3, 4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Map;
    CHECK(func.name == "funcIvec4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> ivec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::ivec4> val =
        ghoul::lua::value<std::map<std::string, glm::ivec4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::ivec4(1, 2, 3, 4));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::ivec4(5, 6, 7, 8));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::ivec4(9, 10, 11, 12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::ivec4 val = ghoul::lua::value<glm::ivec4>(state);
    CHECK(val == glm::ivec4(1, 2, 3, 4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4OptionalNullopt;
    CHECK(func.name == "funcIvec4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  ivec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Vector;
    CHECK(func.name == "funcIvec4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "ivec4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::ivec4> val = ghoul::lua::value<std::vector<glm::ivec4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::ivec4(1, 2, 3, 4));
    CHECK(val[1] == glm::ivec4(5, 6, 7, 8));
    CHECK(val[2] == glm::ivec4(9, 10, 11, 12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2;
    CHECK(func.name == "funcDvec2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec2 val = ghoul::lua::value<glm::dvec2>(state);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Map;
    CHECK(func.name == "funcDvec2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dvec2> val =
        ghoul::lua::value<std::map<std::string, glm::dvec2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::dvec2(1.1, 2.2));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::dvec2(3.3, 4.4));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::dvec2(5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec2 val = ghoul::lua::value<glm::dvec2>(state);
    CHECK(val == glm::dvec2(1.1, 2.2));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2OptionalNullopt;
    CHECK(func.name == "funcDvec2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Vector;
    CHECK(func.name == "funcDvec2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dvec2> val = ghoul::lua::value<std::vector<glm::dvec2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dvec2(1.1, 2.2));
    CHECK(val[1] == glm::dvec2(3.3, 4.4));
    CHECK(val[2] == glm::dvec2(5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3;
    CHECK(func.name == "funcDvec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec3 val = ghoul::lua::value<glm::dvec3>(state);
    CHECK(val == glm::dvec3(1.1, 2.2, 3.3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Map;
    CHECK(func.name == "funcDvec3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dvec3> val =
        ghoul::lua::value<std::map<std::string, glm::dvec3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::dvec3(4.4, 5.5, 6.6));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::dvec3(7.7, 8.8, 9.9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec3 val = ghoul::lua::value<glm::dvec3>(state);
    CHECK(val == glm::dvec3(1.1, 2.2, 3.3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3OptionalNullopt;
    CHECK(func.name == "funcDvec3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Vector;
    CHECK(func.name == "funcDvec3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dvec3> val = ghoul::lua::value<std::vector<glm::dvec3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dvec3(1.1, 2.2, 3.3));
    CHECK(val[1] == glm::dvec3(4.4, 5.5, 6.6));
    CHECK(val[2] == glm::dvec3(7.7, 8.8, 9.9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4;
    CHECK(func.name == "funcDvec4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec4 val = ghoul::lua::value<glm::dvec4>(state);
    CHECK(val == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Map;
    CHECK(func.name == "funcDvec4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dvec4> val =
        ghoul::lua::value<std::map<std::string, glm::dvec4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::dvec4(5.5, 6.6, 7.7, 8.8));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dvec4 val = ghoul::lua::value<glm::dvec4>(state);
    CHECK(val == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4OptionalNullopt;
    CHECK(func.name == "funcDvec4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dvec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Vector;
    CHECK(func.name == "funcDvec4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dvec4> val = ghoul::lua::value<std::vector<glm::dvec4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    CHECK(val[1] == glm::dvec4(5.5, 6.6, 7.7, 8.8));
    CHECK(val[2] == glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2;
    CHECK(func.name == "funcVec2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec2 val = ghoul::lua::value<glm::vec2>(state);
    CHECK(val == glm::vec2(1.1f, 2.2f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Map;
    CHECK(func.name == "funcVec2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::vec2> val =
        ghoul::lua::value<std::map<std::string, glm::vec2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::vec2(1.1f, 2.2f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::vec2(3.3f, 4.4f));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::vec2(5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec2 val = ghoul::lua::value<glm::vec2>(state);
    CHECK(val == glm::vec2(1.1f, 2.2));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2OptionalNullopt;
    CHECK(func.name == "funcVec2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Vector;
    CHECK(func.name == "funcVec2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::vec2> val = ghoul::lua::value<std::vector<glm::vec2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::vec2(1.1f, 2.2f));
    CHECK(val[1] == glm::vec2(3.3f, 4.4f));
    CHECK(val[2] == glm::vec2(5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3;
    CHECK(func.name == "funcVec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec3 val = ghoul::lua::value<glm::vec3>(state);
    CHECK(val == glm::vec3(1.1f, 2.2f, 3.3f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Map;
    CHECK(func.name == "funcVec3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::vec3> val =
        ghoul::lua::value<std::map<std::string, glm::vec3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::vec3(4.4f, 5.5f, 6.6f));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::vec3(7.7f, 8.8f, 9.9f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec3 val = ghoul::lua::value<glm::vec3>(state);
    CHECK(val == glm::vec3(1.1f, 2.2f, 3.3f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3OptionalNullopt;
    CHECK(func.name == "funcVec3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Vector;
    CHECK(func.name == "funcVec3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::vec3> val = ghoul::lua::value<std::vector<glm::vec3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::vec3(1.1f, 2.2f, 3.3f));
    CHECK(val[1] == glm::vec3(4.4f, 5.5f, 6.6f));
    CHECK(val[2] == glm::vec3(7.7f, 8.8f, 9.9f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4;
    CHECK(func.name == "funcVec4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec4 val = ghoul::lua::value<glm::vec4>(state);
    CHECK(val == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Map;
    CHECK(func.name == "funcVec4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> vec4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::vec4> val =
        ghoul::lua::value<std::map<std::string, glm::vec4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::vec4 val = ghoul::lua::value<glm::vec4>(state);
    CHECK(val == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4OptionalNullopt;
    CHECK(func.name == "funcVec4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  vec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Vector;
    CHECK(func.name == "funcVec4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::vec4> val = ghoul::lua::value<std::vector<glm::vec4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    CHECK(val[1] == glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    CHECK(val[2] == glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2;
    CHECK(func.name == "funcMat2x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x2 val = ghoul::lua::value<glm::mat2x2>(state);
    CHECK(val == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Map;
    CHECK(func.name == "funcMat2x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat2x2> val =
        ghoul::lua::value<std::map<std::string, glm::mat2x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x2 val = ghoul::lua::value<glm::mat2x2>(state);
    CHECK(val == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2OptionalNullopt;
    CHECK(func.name == "funcMat2x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Vector;
    CHECK(func.name == "funcMat2x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat2x2> val = ghoul::lua::value<std::vector<glm::mat2x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    CHECK(val[1] == glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    CHECK(val[2] == glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3;
    CHECK(func.name == "funcMat2x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x3 val = ghoul::lua::value<glm::mat2x3>(state);
    CHECK(val == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Map;
    CHECK(func.name == "funcMat2x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat2x3> val =
        ghoul::lua::value<std::map<std::string, glm::mat2x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second == glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x3 val = ghoul::lua::value<glm::mat2x3>(state);
    CHECK(val == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3OptionalNullopt;
    CHECK(func.name == "funcMat2x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Vector;
    CHECK(func.name == "funcMat2x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat2x3> val = ghoul::lua::value<std::vector<glm::mat2x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    CHECK(val[1] == glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
    CHECK(val[2] == glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4;
    CHECK(func.name == "funcMat2x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x4 val = ghoul::lua::value<glm::mat2x4>(state);
    CHECK(val == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Map;
    CHECK(func.name == "funcMat2x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat2x4> val =
        ghoul::lua::value<std::map<std::string, glm::mat2x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat2x4 val = ghoul::lua::value<glm::mat2x4>(state);
    CHECK(val == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4OptionalNullopt;
    CHECK(func.name == "funcMat2x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Vector;
    CHECK(func.name == "funcMat2x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat2x4> val = ghoul::lua::value<std::vector<glm::mat2x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    CHECK(
        val[1] ==
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    CHECK(
        val[2] ==
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2;
    CHECK(func.name == "funcMat3x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x2 val = ghoul::lua::value<glm::mat3x2>(state);
    CHECK(val == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Map;
    CHECK(func.name == "funcMat3x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat3x2> val =
        ghoul::lua::value<std::map<std::string, glm::mat3x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x2 val = ghoul::lua::value<glm::mat3x2>(state);
    CHECK(val == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2OptionalNullopt;
    CHECK(func.name == "funcMat3x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Vector;
    CHECK(func.name == "funcMat3x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat3x2> val = ghoul::lua::value<std::vector<glm::mat3x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    CHECK(val[1] == glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
    CHECK(val[2] == glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3;
    CHECK(func.name == "funcMat3x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x3 val = ghoul::lua::value<glm::mat3x3>(state);
    CHECK(val == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5, 6.6f, 7.7f, 8.8f, 9.9f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Map;
    CHECK(func.name == "funcMat3x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat3x3> val =
        ghoul::lua::value<std::map<std::string, glm::mat3x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x3 val = ghoul::lua::value<glm::mat3x3>(state);
    CHECK(val == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3OptionalNullopt;
    CHECK(func.name == "funcMat3x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Vector;
    CHECK(func.name == "funcMat3x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat3x3> val = ghoul::lua::value<std::vector<glm::mat3x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f));
    CHECK(
        val[1] == 
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    CHECK(
        val[2] == 
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4;
    CHECK(func.name == "funcMat3x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x4 val = ghoul::lua::value<glm::mat3x4>(state);
    CHECK(
        val ==
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Map;
    CHECK(func.name == "funcMat3x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat3x4> val =
        ghoul::lua::value<std::map<std::string, glm::mat3x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat3x4(
            13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat3x4 val = ghoul::lua::value<glm::mat3x4>(state);
    CHECK(
        val ==
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4OptionalNullopt;
    CHECK(func.name == "funcMat3x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Vector;
    CHECK(func.name == "funcMat3x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat3x4> val = ghoul::lua::value<std::vector<glm::mat3x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] == 
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    CHECK(
        val[1] == 
        glm::mat3x4(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    CHECK(
        val[2] == 
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Return:  mat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2;
    CHECK(func.name == "funcMat4x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x2 val = ghoul::lua::value<glm::mat4x2>(state);
    CHECK(val == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Map;
    CHECK(func.name == "funcMat4x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat4x2> val =
        ghoul::lua::value<std::map<std::string, glm::mat4x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second == 
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second == 
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x2 val = ghoul::lua::value<glm::mat4x2>(state);
    CHECK(val == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2OptionalNullopt;
    CHECK(func.name == "funcMat4x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Vector;
    CHECK(func.name == "funcMat4x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat4x2> val = ghoul::lua::value<std::vector<glm::mat4x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    CHECK(
        val[1] == 
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    CHECK(
        val[2] == 
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3;
    CHECK(func.name == "funcMat4x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x3 val = ghoul::lua::value<glm::mat4x3>(state);
    CHECK(
        val == 
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Map;
    CHECK(func.name == "funcMat4x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat4x3> val =
        ghoul::lua::value<std::map<std::string, glm::mat4x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second == 
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat4x3(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x3 val = ghoul::lua::value<glm::mat4x3>(state);
    CHECK(
        val ==
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3OptionalNullopt;
    CHECK(func.name == "funcMat4x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Vector;
    CHECK(func.name == "funcMat4x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat4x3> val = ghoul::lua::value<std::vector<glm::mat4x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] == 
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    CHECK(
        val[1] == 
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    CHECK(
        val[2] == 
        glm::mat4x3(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4;
    CHECK(func.name == "funcMat4x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x4 val = ghoul::lua::value<glm::mat4x4>(state);
    CHECK(
        val ==
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Map;
    CHECK(func.name == "funcMat4x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::mat4x4> val =
        ghoul::lua::value<std::map<std::string, glm::mat4x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::mat4x4 val = ghoul::lua::value<glm::mat4x4>(state);
    CHECK(
        val == 
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4OptionalNullopt;
    CHECK(func.name == "funcMat4x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  mat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Vector;
    CHECK(func.name == "funcMat4x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::mat4x4> val = ghoul::lua::value<std::vector<glm::mat4x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    CHECK(
        val[1] ==
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    CHECK(
        val[2] ==
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2;
    CHECK(func.name == "funcDMat2x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x2 val = ghoul::lua::value<glm::dmat2x2>(state);
    CHECK(val == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Map;
    CHECK(func.name == "funcDMat2x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat2x2> val =
        ghoul::lua::value<std::map<std::string, glm::dmat2x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    REQUIRE(val.find("key3") != val.end());
    CHECK(val.find("key3")->second == glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x2 val = ghoul::lua::value<glm::dmat2x2>(state);
    CHECK(val == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2OptionalNullopt;
    CHECK(func.name == "funcDMat2x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Vector;
    CHECK(func.name == "funcDMat2x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat2x2> val = ghoul::lua::value<std::vector<glm::dmat2x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    CHECK(val[1] == glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    CHECK(val[2] == glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3;
    CHECK(func.name == "funcDMat2x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x3 val = ghoul::lua::value<glm::dmat2x3>(state);
    CHECK(val == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Map;
    CHECK(func.name == "funcDMat2x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat2x3> val =
        ghoul::lua::value<std::map<std::string, glm::dmat2x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(val.find("key1")->second == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(val.find("key2") != val.end());
    CHECK(val.find("key2")->second == glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x3 val = ghoul::lua::value<glm::dmat2x3>(state);
    CHECK(val == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3OptionalNullopt;
    CHECK(func.name == "funcDMat2x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Vector;
    CHECK(func.name == "funcDMat2x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat2x3> val = ghoul::lua::value<std::vector<glm::dmat2x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    CHECK(val[1] == glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    CHECK(val[2] == glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4;
    CHECK(func.name == "funcDMat2x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x4 val = ghoul::lua::value<glm::dmat2x4>(state);
    CHECK(val == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Map;
    CHECK(func.name == "funcDMat2x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat2x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat2x4> val =
        ghoul::lua::value<std::map<std::string, glm::dmat2x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat2x4 val = ghoul::lua::value<glm::dmat2x4>(state);
    CHECK(val == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4OptionalNullopt;
    CHECK(func.name == "funcDMat2x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Vector;
    CHECK(func.name == "funcDMat2x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat2x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat2x4> val = ghoul::lua::value<std::vector<glm::dmat2x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    CHECK(
        val[1] ==
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    CHECK(
        val[2] ==
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2;
    CHECK(func.name == "funcDMat3x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x2 val = ghoul::lua::value<glm::dmat3x2>(state);
    CHECK(val == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Map;
    CHECK(func.name == "funcDMat3x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat3x2> val =
        ghoul::lua::value<std::map<std::string, glm::dmat3x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x2 val = ghoul::lua::value<glm::dmat3x2>(state);
    CHECK(val == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2OptionalNullopt;
    CHECK(func.name == "funcDMat3x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Vector;
    CHECK(func.name == "funcDMat3x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat3x2> val = ghoul::lua::value<std::vector<glm::dmat3x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    CHECK(val[1] == glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    CHECK(val[2] == glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3;
    CHECK(func.name == "funcDMat3x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x3 val = ghoul::lua::value<glm::dmat3x3>(state);
    CHECK(val == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Map;
    CHECK(func.name == "funcDMat3x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat3x3> val =
        ghoul::lua::value<std::map<std::string, glm::dmat3x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x3 val = ghoul::lua::value<glm::dmat3x3>(state);
    CHECK(val == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3OptionalNullopt;
    CHECK(func.name == "funcDMat3x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Vector;
    CHECK(func.name == "funcDMat3x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat3x3> val = ghoul::lua::value<std::vector<glm::dmat3x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    CHECK(
        val[1] ==
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    CHECK(
        val[2] ==
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4;
    CHECK(func.name == "funcDMat3x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x4 val = ghoul::lua::value<glm::dmat3x4>(state);
    CHECK(
        val ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Map;
    CHECK(func.name == "funcDMat3x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat3x4> val =
        ghoul::lua::value<std::map<std::string, glm::dmat3x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x4 val = ghoul::lua::value<glm::dmat3x4>(state);
    CHECK(
        val ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4OptionalNullopt;
    CHECK(func.name == "funcDMat3x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Vector;
    CHECK(func.name == "funcDMat3x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat3x4> val = ghoul::lua::value<std::vector<glm::dmat3x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    CHECK(
        val[1] ==
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    CHECK(
        val[2] ==
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2;
    CHECK(func.name == "funcDMat4x2");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x2 val = ghoul::lua::value<glm::dmat4x2>(state);
    CHECK(val == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Map;
    CHECK(func.name == "funcDMat4x2Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x2");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat4x2> val =
        ghoul::lua::value<std::map<std::string, glm::dmat4x2>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x2 val = ghoul::lua::value<glm::dmat4x2>(state);
    CHECK(val == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2OptionalNullopt;
    CHECK(func.name == "funcDMat4x2OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Vector;
    CHECK(func.name == "funcDMat4x2Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x2[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat4x2> val = ghoul::lua::value<std::vector<glm::dmat4x2>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0] == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    CHECK(val[1] == glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16));
    CHECK(val[2] == glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3;
    CHECK(func.name == "funcDMat4x3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x3 val = ghoul::lua::value<glm::dmat4x3>(state);
    CHECK(
        val ==
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Map;
    CHECK(func.name == "funcDMat4x3Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat4x3> val =
        ghoul::lua::value<std::map<std::string, glm::dmat4x3>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat4x3(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x3 val = ghoul::lua::value<glm::dmat4x3>(state);
    CHECK(
        val ==
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3OptionalNullopt;
    CHECK(func.name == "funcDMat4x3OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Vector;
    CHECK(func.name == "funcDMat4x3Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x3[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat4x3> val = ghoul::lua::value<std::vector<glm::dmat4x3>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    CHECK(
        val[1] ==
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    CHECK(
        val[2] ==
        glm::dmat4x3(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4;
    CHECK(func.name == "funcDMat4x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x4 val = ghoul::lua::value<glm::dmat4x4>(state);
    CHECK(
        val ==
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Map;
    CHECK(func.name == "funcDMat4x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat4x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat4x4> val =
        ghoul::lua::value<std::map<std::string, glm::dmat4x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat4x4 val = ghoul::lua::value<glm::dmat4x4>(state);
    CHECK(
        val ==
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4OptionalNullopt;
    CHECK(func.name == "funcDMat4x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Vector;
    CHECK(func.name == "funcDMat4x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat4x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat4x4> val = ghoul::lua::value<std::vector<glm::dmat4x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    CHECK(
        val[1] ==
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    CHECK(
        val[2] ==
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dictionary") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionary;
    CHECK(func.name == "funcDictionary");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Table");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    ghoul::Dictionary val = ghoul::lua::value<ghoul::Dictionary>(state);
    REQUIRE(val.hasValue<double>("a"));
    CHECK(val.value<double>("a") == 1.1);
    REQUIRE(val.hasValue<std::string>("b"));
    CHECK(val.value<std::string>("b") == "abc");
    REQUIRE(val.hasValue<glm::dvec3>("c"));
    CHECK(val.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dictionaryMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryMap;
    CHECK(func.name == "funcDictionaryMap");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> Table");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, ghoul::Dictionary> val =
        ghoul::lua::value<std::map<std::string, ghoul::Dictionary>>(state);
    CHECK(val.size() == 3);
    {
        auto it = val.find("key1");
        REQUIRE(it != val.end());
        CHECK(it->second.hasValue<double>("a"));
        CHECK(it->second.value<double>("a") == 1.1);
        REQUIRE(it->second.hasValue<std::string>("b"));
        CHECK(it->second.value<std::string>("b") == "abc");
        REQUIRE(it->second.hasValue<glm::dvec3>("c"));
        CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    }
    {
        auto it = val.find("key2");
        REQUIRE(it != val.end());
        CHECK(it->second.hasValue<double>("a"));
        CHECK(it->second.value<double>("a") == 5.5);
        REQUIRE(it->second.hasValue<std::string>("b"));
        CHECK(it->second.value<std::string>("b") == "def");
        REQUIRE(it->second.hasValue<glm::dvec3>("c"));
        CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(6.6, 7.7, 8.8));
    }
    {
        auto it = val.find("key3");
        REQUIRE(it != val.end());
        CHECK(it->second.hasValue<double>("a"));
        CHECK(it->second.value<double>("a") == 9.9);
        REQUIRE(it->second.hasValue<std::string>("b"));
        CHECK(it->second.value<std::string>("b") == "ghi");
        REQUIRE(it->second.hasValue<glm::dvec3>("c"));
        CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(10.10, 11.11, 12.12));
    }
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dictionaryOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryOptional;
    CHECK(func.name == "funcDictionaryOptional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Table?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    ghoul::Dictionary val = ghoul::lua::value<ghoul::Dictionary>(state);
    REQUIRE(val.hasValue<double>("a"));
    CHECK(val.value<double>("a") == 1.1);
    REQUIRE(val.hasValue<std::string>("b"));
    CHECK(val.value<std::string>("b") == "abc");
    REQUIRE(val.hasValue<glm::dvec3>("c"));
    CHECK(val.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dictionaryOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryOptionalNullopt;
    CHECK(func.name == "funcDictionaryOptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Table?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dictionaryVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryVector;
    CHECK(func.name == "funcDictionaryVector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Table[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<ghoul::Dictionary> val =
        ghoul::lua::value<std::vector<ghoul::Dictionary>>(state);
    REQUIRE(val.size() == 3);
    CHECK(val[0].hasValue<double>("a"));
    CHECK(val[0].value<double>("a") == 1.1);
    REQUIRE(val[0].hasValue<std::string>("b"));
    CHECK(val[0].value<std::string>("b") == "abc");
    REQUIRE(val[0].hasValue<glm::dvec3>("c"));
    CHECK(val[0].value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    CHECK(val[1].hasValue<double>("a"));
    CHECK(val[1].value<double>("a") == 5.5);
    REQUIRE(val[1].hasValue<std::string>("b"));
    CHECK(val[1].value<std::string>("b") == "def");
    REQUIRE(val[1].hasValue<glm::dvec3>("c"));
    CHECK(val[1].value<glm::dvec3>("c") == glm::dvec3(6.6, 7.7, 8.8));
    CHECK(val[2].hasValue<double>("a"));
    CHECK(val[2].value<double>("a") == 9.9);
    REQUIRE(val[2].hasValue<std::string>("b"));
    CHECK(val[2].value<std::string>("b") == "ghi");
    REQUIRE(val[2].hasValue<glm::dvec3>("c"));
    CHECK(val[2].value<glm::dvec3>("c") == glm::dvec3(10.10, 11.11, 12.12));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  tuple(vec3)") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncTupleVec3;
    CHECK(func.name == "funcTupleVec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::tuple<glm::dvec3> val = ghoul::lua::values<glm::dvec3>(state);
    CHECK(std::get<0>(val) == glm::dvec3(1.1, 2.2, 3.3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  tuple(bool,int)") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncTupleBoolInt;
    CHECK(func.name == "funcTupleBoolInt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean, Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 2);
    std::tuple<bool, int> val = ghoul::lua::values<bool, int>(state);
    CHECK(std::get<0>(val) == true);
    CHECK(std::get<1>(val) == 1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  tuple(double,float,string)") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncTupleDoubleFloatStringDouble;
    CHECK(func.name == "funcTupleDoubleFloatStringDouble");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number, Number, String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 3);
    std::tuple<double, float, std::string> val =
        ghoul::lua::values<double, float, std::string>(state);
    CHECK(std::get<0>(val) == 1.1);
    CHECK(std::get<1>(val) == 2.2f);
    CHECK(std::get<2>(val) == "abc");
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(bool,int) / bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantBoolIntBool;
    CHECK(func.name == "funcVariantBoolIntBool");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean | Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::variant<bool, int> val = ghoul::lua::value<std::variant<bool, int>>(state);
    REQUIRE(std::holds_alternative<bool>(val));
    CHECK(std::get<bool>(val) == true);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(bool,int) / int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantBoolIntInt;
    CHECK(func.name == "funcVariantBoolIntInt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean | Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::variant<bool, int> val = ghoul::lua::value<std::variant<bool, int>>(state);
    REQUIRE(std::holds_alternative<int>(val));
    CHECK(std::get<int>(val) == 1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, dvec3, string) / double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantDvec3FloatStringDouble;
    CHECK(func.name == "funcVariantDvec3FloatStringDouble");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number | vec3 | String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::variant<double, glm::dvec3, std::string> val =
        ghoul::lua::value<std::variant<double, glm::dvec3, std::string>>(state);
    REQUIRE(std::holds_alternative<double>(val));
    CHECK(std::get<double>(val) == 1.1);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, dvec3, string) / dvec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantDvec3FloatStringDvec3;
    CHECK(func.name == "funcVariantDvec3FloatStringDvec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number | vec3 | String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::variant<double, glm::dvec3, std::string> val =
        ghoul::lua::value<std::variant<double, glm::dvec3, std::string>>(state);
    REQUIRE(std::holds_alternative<glm::dvec3>(val));
    CHECK(std::get<glm::dvec3>(val) == glm::dvec3(1.1, 2.2, 3.3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  variant(double, dvec3, string) / string") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantDvec3FloatStringString;
    CHECK(func.name == "funcVariantDvec3FloatStringString");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number | vec3 | String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::variant<double, glm::dvec3, std::string> val =
        ghoul::lua::value<std::variant<double, glm::dvec3, std::string>>(state);
    REQUIRE(std::holds_alternative<std::string>(val));
    CHECK(std::get<std::string>(val) == "abc");
    lua_close(state);
}
