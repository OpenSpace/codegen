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

#include <catch2/catch_test_macros.hpp>

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Variable:  Basic Types", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    bool boolVariable;
    int intVariable;
    double doubleValue;
    float floatValue;
    std::string stringValue;
    glm::ivec2 ivec2Value;
    glm::ivec3 ivec3Value;
    glm::ivec4 ivec4Value;
    glm::dvec2 dvec2Value;
    glm::dvec3 dvec3Value;
    glm::dvec4 dvec4Value;
    glm::vec2 vec2Value;
    glm::vec3 vec3Value;
    glm::vec4 vec4Value;
    glm::mat2x2 mat2x2Value;
    glm::mat2 mat2Value;
    glm::mat2x3 mat2x3Value;
    glm::mat2x4 mat2x4Value;
    glm::mat3x2 mat3x2Value;
    glm::mat3x3 mat3x3Value;
    glm::mat3 mat3Value;
    glm::mat3x4 mat3x4Value;
    glm::mat4x2 mat4x2Value;
    glm::mat4x3 mat4x3Value;
    glm::mat4x4 mat4x4Value;
    glm::mat4 mat4Value;
    glm::dmat2x2 dmat2x2Value;
    glm::dmat2 dmat2Value;
    glm::dmat2x3 dmat2x3Value;
    glm::dmat2x4 dmat2x4Value;
    glm::dmat3x2 dmat3x2Value;
    glm::dmat3x3 dmat3x3Value;
    glm::dmat3 dmat3Value;
    glm::dmat3x4 dmat3x4Value;
    glm::dmat4x2 dmat4x2Value;
    glm::dmat4x3 dmat4x3Value;
    glm::dmat4x4 dmat4x4Value;
    glm::dmat4 dmat4Value;
};
)";
    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    CHECK(code.luaWrapperFunctions.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 38);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "boolVariable");
        CHECK(var->key == "\"BoolVariable\"");
        CHECK(generateTypename(var->type) == "bool");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "intVariable");
        CHECK(var->key == "\"IntVariable\"");
        CHECK(generateTypename(var->type) == "int");
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "doubleValue");
        CHECK(var->key == "\"DoubleValue\"");
        CHECK(generateTypename(var->type) == "double");
    }
    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "floatValue");
        CHECK(var->key == "\"FloatValue\"");
        CHECK(generateTypename(var->type) == "float");
    }
    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "stringValue");
        CHECK(var->key == "\"StringValue\"");
        CHECK(generateTypename(var->type) == "std::string");
    }
    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "ivec2Value");
        CHECK(var->key == "\"Ivec2Value\"");
        CHECK(generateTypename(var->type) == "glm::ivec2");
    }
    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "ivec3Value");
        CHECK(var->key == "\"Ivec3Value\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
    }
    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "ivec4Value");
        CHECK(var->key == "\"Ivec4Value\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
    }
    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "dvec2Value");
        CHECK(var->key == "\"Dvec2Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec2");
    }
    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "dvec3Value");
        CHECK(var->key == "\"Dvec3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
    }
    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "dvec4Value");
        CHECK(var->key == "\"Dvec4Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec4");
    }
    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "vec2Value");
        CHECK(var->key == "\"Vec2Value\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
    }
    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "vec3Value");
        CHECK(var->key == "\"Vec3Value\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
    }
    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "vec4Value");
        CHECK(var->key == "\"Vec4Value\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
    }
    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "mat2x2Value");
        CHECK(var->key == "\"Mat2x2Value\"");
        CHECK(generateTypename(var->type) == "glm::mat2x2");
    }
    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "mat2Value");
        CHECK(var->key == "\"Mat2Value\"");
        CHECK(generateTypename(var->type) == "glm::mat2x2");
    }
    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "mat2x3Value");
        CHECK(var->key == "\"Mat2x3Value\"");
        CHECK(generateTypename(var->type) == "glm::mat2x3");
    }
    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "mat2x4Value");
        CHECK(var->key == "\"Mat2x4Value\"");
        CHECK(generateTypename(var->type) == "glm::mat2x4");
    }
    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "mat3x2Value");
        CHECK(var->key == "\"Mat3x2Value\"");
        CHECK(generateTypename(var->type) == "glm::mat3x2");
    }
    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "mat3x3Value");
        CHECK(var->key == "\"Mat3x3Value\"");
        CHECK(generateTypename(var->type) == "glm::mat3x3");
    }
    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "mat3Value");
        CHECK(var->key == "\"Mat3Value\"");
        CHECK(generateTypename(var->type) == "glm::mat3x3");
    }
    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "mat3x4Value");
        CHECK(var->key == "\"Mat3x4Value\"");
        CHECK(generateTypename(var->type) == "glm::mat3x4");
    }
    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "mat4x2Value");
        CHECK(var->key == "\"Mat4x2Value\"");
        CHECK(generateTypename(var->type) == "glm::mat4x2");
    }
    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "mat4x3Value");
        CHECK(var->key == "\"Mat4x3Value\"");
        CHECK(generateTypename(var->type) == "glm::mat4x3");
    }
    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "mat4x4Value");
        CHECK(var->key == "\"Mat4x4Value\"");
        CHECK(generateTypename(var->type) == "glm::mat4x4");
    }
    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "mat4Value");
        CHECK(var->key == "\"Mat4Value\"");
        CHECK(generateTypename(var->type) == "glm::mat4x4");
    }
    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "dmat2x2Value");
        CHECK(var->key == "\"Dmat2x2Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat2x2");
    }
    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "dmat2Value");
        CHECK(var->key == "\"Dmat2Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat2x2");
    }
    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "dmat2x3Value");
        CHECK(var->key == "\"Dmat2x3Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat2x3");
    }
    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "dmat2x4Value");
        CHECK(var->key == "\"Dmat2x4Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat2x4");
    }
    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "dmat3x2Value");
        CHECK(var->key == "\"Dmat3x2Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat3x2");
    }
    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "dmat3x3Value");
        CHECK(var->key == "\"Dmat3x3Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat3x3");
    }
    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "dmat3Value");
        CHECK(var->key == "\"Dmat3Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat3x3");
    }
    {
        Variable* var = s->variables[33];
        REQUIRE(var);
        CHECK(var->name == "dmat3x4Value");
        CHECK(var->key == "\"Dmat3x4Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat3x4");
    }
    {
        Variable* var = s->variables[34];
        REQUIRE(var);
        CHECK(var->name == "dmat4x2Value");
        CHECK(var->key == "\"Dmat4x2Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat4x2");
    }
    {
        Variable* var = s->variables[35];
        REQUIRE(var);
        CHECK(var->name == "dmat4x3Value");
        CHECK(var->key == "\"Dmat4x3Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat4x3");
    }
    {
        Variable* var = s->variables[36];
        REQUIRE(var);
        CHECK(var->name == "dmat4x4Value");
        CHECK(var->key == "\"Dmat4x4Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat4x4");
    }
    {
        Variable* var = s->variables[37];
        REQUIRE(var);
        CHECK(var->name == "dmat4Value");
        CHECK(var->key == "\"Dmat4Value\"");
        CHECK(generateTypename(var->type) == "glm::dmat4x4");
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing Variable: Vector Base Types", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    std::vector<bool> boolVariable;
    std::vector<int> intVariable;
    std::vector<double> doubleValue;
    std::vector<float> floatValue;
    std::vector<std::string> stringValue;
    std::vector<glm::ivec2> ivec2Value;
    std::vector<glm::ivec3> ivec3Value;
    std::vector<glm::ivec4> ivec4Value;
    std::vector<glm::dvec2> dvec2Value;
    std::vector<glm::dvec3> dvec3Value;
    std::vector<glm::dvec4> dvec4Value;
    std::vector<glm::vec2> vec2Value;
    std::vector<glm::vec3> vec3Value;
    std::vector<glm::vec4> vec4Value;
    std::vector<glm::mat2x2> mat2x2Value;
    std::vector<glm::mat2> mat2Value;
    std::vector<glm::mat2x3> mat2x3Value;
    std::vector<glm::mat2x4> mat2x4Value;
    std::vector<glm::mat3x2> mat3x2Value;
    std::vector<glm::mat3x3> mat3x3Value;
    std::vector<glm::mat3> mat3Value;
    std::vector<glm::mat3x4> mat3x4Value;
    std::vector<glm::mat4x2> mat4x2Value;
    std::vector<glm::mat4x3> mat4x3Value;
    std::vector<glm::mat4x4> mat4x4Value;
    std::vector<glm::mat4> mat4Value;
    std::vector<glm::dmat2x2> dmat2x2Value;
    std::vector<glm::dmat2> dmat2Value;
    std::vector<glm::dmat2x3> dmat2x3Value;
    std::vector<glm::dmat2x4> dmat2x4Value;
    std::vector<glm::dmat3x2> dmat3x2Value;
    std::vector<glm::dmat3x3> dmat3x3Value;
    std::vector<glm::dmat3> dmat3Value;
    std::vector<glm::dmat3x4> dmat3x4Value;
    std::vector<glm::dmat4x2> dmat4x2Value;
    std::vector<glm::dmat4x3> dmat4x3Value;
    std::vector<glm::dmat4x4> dmat4x4Value;
    std::vector<glm::dmat4> dmat4Value;
};
)";
    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 38);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "boolVariable");
        CHECK(var->key == "\"BoolVariable\"");
        CHECK(generateTypename(var->type) == "std::vector<bool>");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "intVariable");
        CHECK(var->key == "\"IntVariable\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "doubleValue");
        CHECK(var->key == "\"DoubleValue\"");
        CHECK(generateTypename(var->type) == "std::vector<double>");
    }
    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "floatValue");
        CHECK(var->key == "\"FloatValue\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
    }
    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "stringValue");
        CHECK(var->key == "\"StringValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
    }
    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "ivec2Value");
        CHECK(var->key == "\"Ivec2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec2>");
    }
    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "ivec3Value");
        CHECK(var->key == "\"Ivec3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
    }
    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "ivec4Value");
        CHECK(var->key == "\"Ivec4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
    }
    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "dvec2Value");
        CHECK(var->key == "\"Dvec2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec2>");
    }
    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "dvec3Value");
        CHECK(var->key == "\"Dvec3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
    }
    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "dvec4Value");
        CHECK(var->key == "\"Dvec4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec4>");
    }
    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "vec2Value");
        CHECK(var->key == "\"Vec2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
    }
    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "vec3Value");
        CHECK(var->key == "\"Vec3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
    }
    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "vec4Value");
        CHECK(var->key == "\"Vec4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
    }
    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "mat2x2Value");
        CHECK(var->key == "\"Mat2x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat2x2>");
    }
    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "mat2Value");
        CHECK(var->key == "\"Mat2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat2x2>");
    }
    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "mat2x3Value");
        CHECK(var->key == "\"Mat2x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat2x3>");
    }
    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "mat2x4Value");
        CHECK(var->key == "\"Mat2x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat2x4>");
    }
    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "mat3x2Value");
        CHECK(var->key == "\"Mat3x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat3x2>");
    }
    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "mat3x3Value");
        CHECK(var->key == "\"Mat3x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat3x3>");
    }
    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "mat3Value");
        CHECK(var->key == "\"Mat3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat3x3>");
    }
    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "mat3x4Value");
        CHECK(var->key == "\"Mat3x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat3x4>");
    }
    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "mat4x2Value");
        CHECK(var->key == "\"Mat4x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat4x2>");
    }
    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "mat4x3Value");
        CHECK(var->key == "\"Mat4x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat4x3>");
    }
    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "mat4x4Value");
        CHECK(var->key == "\"Mat4x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat4x4>");
    }
    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "mat4Value");
        CHECK(var->key == "\"Mat4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::mat4x4>");
    }
    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "dmat2x2Value");
        CHECK(var->key == "\"Dmat2x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat2x2>");
    }
    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "dmat2Value");
        CHECK(var->key == "\"Dmat2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat2x2>");
    }
    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "dmat2x3Value");
        CHECK(var->key == "\"Dmat2x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat2x3>");
    }
    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "dmat2x4Value");
        CHECK(var->key == "\"Dmat2x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat2x4>");
    }
    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "dmat3x2Value");
        CHECK(var->key == "\"Dmat3x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat3x2>");
    }
    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "dmat3x3Value");
        CHECK(var->key == "\"Dmat3x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat3x3>");
    }
    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "dmat3Value");
        CHECK(var->key == "\"Dmat3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat3x3>");
    }
    {
        Variable* var = s->variables[33];
        REQUIRE(var);
        CHECK(var->name == "dmat3x4Value");
        CHECK(var->key == "\"Dmat3x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat3x4>");
    }
    {
        Variable* var = s->variables[34];
        REQUIRE(var);
        CHECK(var->name == "dmat4x2Value");
        CHECK(var->key == "\"Dmat4x2Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat4x2>");
    }
    {
        Variable* var = s->variables[35];
        REQUIRE(var);
        CHECK(var->name == "dmat4x3Value");
        CHECK(var->key == "\"Dmat4x3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat4x3>");
    }
    {
        Variable* var = s->variables[36];
        REQUIRE(var);
        CHECK(var->name == "dmat4x4Value");
        CHECK(var->key == "\"Dmat4x4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat4x4>");
    }
    {
        Variable* var = s->variables[37];
        REQUIRE(var);
        CHECK(var->name == "dmat4Value");
        CHECK(var->key == "\"Dmat4Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dmat4x4>");
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variable:  Optional Base Types", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    std::optional<bool> boolVariable;
    std::optional<int> intVariable;
    std::optional<double> doubleValue;
    std::optional<float> floatValue;
    std::optional<std::string> stringValue;
    std::optional<glm::ivec2> ivec2Value;
    std::optional<glm::ivec3> ivec3Value;
    std::optional<glm::ivec4> ivec4Value;
    std::optional<glm::dvec2> dvec2Value;
    std::optional<glm::dvec3> dvec3Value;
    std::optional<glm::dvec4> dvec4Value;
    std::optional<glm::vec2> vec2Value;
    std::optional<glm::vec3> vec3Value;
    std::optional<glm::vec4> vec4Value;
    std::optional<glm::mat2x2> mat2x2Value;
    std::optional<glm::mat2> mat2Value;
    std::optional<glm::mat2x3> mat2x3Value;
    std::optional<glm::mat2x4> mat2x4Value;
    std::optional<glm::mat3x2> mat3x2Value;
    std::optional<glm::mat3x3> mat3x3Value;
    std::optional<glm::mat3> mat3Value;
    std::optional<glm::mat3x4> mat3x4Value;
    std::optional<glm::mat4x2> mat4x2Value;
    std::optional<glm::mat4x3> mat4x3Value;
    std::optional<glm::mat4x4> mat4x4Value;
    std::optional<glm::mat4> mat4Value;
    std::optional<glm::dmat2x2> dmat2x2Value;
    std::optional<glm::dmat2> dmat2Value;
    std::optional<glm::dmat2x3> dmat2x3Value;
    std::optional<glm::dmat2x4> dmat2x4Value;
    std::optional<glm::dmat3x2> dmat3x2Value;
    std::optional<glm::dmat3x3> dmat3x3Value;
    std::optional<glm::dmat3> dmat3Value;
    std::optional<glm::dmat3x4> dmat3x4Value;
    std::optional<glm::dmat4x2> dmat4x2Value;
    std::optional<glm::dmat4x3> dmat4x3Value;
    std::optional<glm::dmat4x4> dmat4x4Value;
    std::optional<glm::dmat4> dmat4Value;
};
)";
    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 38);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "boolVariable");
        CHECK(var->key == "\"BoolVariable\"");
        CHECK(generateTypename(var->type) == "std::optional<bool>");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "intVariable");
        CHECK(var->key == "\"IntVariable\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "doubleValue");
        CHECK(var->key == "\"DoubleValue\"");
        CHECK(generateTypename(var->type) == "std::optional<double>");
    }
    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "floatValue");
        CHECK(var->key == "\"FloatValue\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
    }
    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "stringValue");
        CHECK(var->key == "\"StringValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
    }
    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "ivec2Value");
        CHECK(var->key == "\"Ivec2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec2>");
    }
    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "ivec3Value");
        CHECK(var->key == "\"Ivec3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
    }
    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "ivec4Value");
        CHECK(var->key == "\"Ivec4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
    }
    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "dvec2Value");
        CHECK(var->key == "\"Dvec2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec2>");
    }
    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "dvec3Value");
        CHECK(var->key == "\"Dvec3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
    }
    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "dvec4Value");
        CHECK(var->key == "\"Dvec4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec4>");
    }
    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "vec2Value");
        CHECK(var->key == "\"Vec2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
    }
    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "vec3Value");
        CHECK(var->key == "\"Vec3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
    }
    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "vec4Value");
        CHECK(var->key == "\"Vec4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
    }
    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "mat2x2Value");
        CHECK(var->key == "\"Mat2x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat2x2>");
    }
    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "mat2Value");
        CHECK(var->key == "\"Mat2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat2x2>");
    }
    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "mat2x3Value");
        CHECK(var->key == "\"Mat2x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat2x3>");
    }
    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "mat2x4Value");
        CHECK(var->key == "\"Mat2x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat2x4>");
    }
    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "mat3x2Value");
        CHECK(var->key == "\"Mat3x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat3x2>");
    }
    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "mat3x3Value");
        CHECK(var->key == "\"Mat3x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat3x3>");
    }
    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "mat3Value");
        CHECK(var->key == "\"Mat3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat3x3>");
    }
    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "mat3x4Value");
        CHECK(var->key == "\"Mat3x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat3x4>");
    }
    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "mat4x2Value");
        CHECK(var->key == "\"Mat4x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat4x2>");
    }
    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "mat4x3Value");
        CHECK(var->key == "\"Mat4x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat4x3>");
    }
    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "mat4x4Value");
        CHECK(var->key == "\"Mat4x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat4x4>");
    }
    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "mat4Value");
        CHECK(var->key == "\"Mat4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::mat4x4>");
    }
    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "dmat2x2Value");
        CHECK(var->key == "\"Dmat2x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat2x2>");
    }
    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "dmat2Value");
        CHECK(var->key == "\"Dmat2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat2x2>");
    }
    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "dmat2x3Value");
        CHECK(var->key == "\"Dmat2x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat2x3>");
    }
    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "dmat2x4Value");
        CHECK(var->key == "\"Dmat2x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat2x4>");
    }
    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "dmat3x2Value");
        CHECK(var->key == "\"Dmat3x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat3x2>");
    }
    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "dmat3x3Value");
        CHECK(var->key == "\"Dmat3x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat3x3>");
    }
    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "dmat3Value");
        CHECK(var->key == "\"Dmat3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat3x3>");
    }
    {
        Variable* var = s->variables[33];
        REQUIRE(var);
        CHECK(var->name == "dmat3x4Value");
        CHECK(var->key == "\"Dmat3x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat3x4>");
    }
    {
        Variable* var = s->variables[34];
        REQUIRE(var);
        CHECK(var->name == "dmat4x2Value");
        CHECK(var->key == "\"Dmat4x2Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat4x2>");
    }
    {
        Variable* var = s->variables[35];
        REQUIRE(var);
        CHECK(var->name == "dmat4x3Value");
        CHECK(var->key == "\"Dmat4x3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat4x3>");
    }
    {
        Variable* var = s->variables[36];
        REQUIRE(var);
        CHECK(var->name == "dmat4x4Value");
        CHECK(var->key == "\"Dmat4x4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat4x4>");
    }
    {
        Variable* var = s->variables[37];
        REQUIRE(var);
        CHECK(var->name == "dmat4Value");
        CHECK(var->key == "\"Dmat4Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dmat4x4>");
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variable:  Variable attributes", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    int variable1 [[codegen::key(Var)]];

};
)";
    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->key == "Var");

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}
