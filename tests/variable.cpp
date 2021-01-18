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

#include "catch2/catch.hpp"

#include "parsing.h"
#include "types.h"

TEST_CASE("Basic Types", "[variables]") {
    Struct* s = parseRootStruct(R"(
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
    glm::mat2x3 mat2x3Value;
    glm::mat2x4 mat2x4Value;
    glm::mat3x2 mat3x2Value;
    glm::mat3x3 mat3x3Value;
    glm::mat3x4 mat3x4Value;
    glm::mat4x2 mat4x2Value;
    glm::mat4x3 mat4x3Value;
    glm::mat4x4 mat4x4Value;
    glm::dmat2x2 dmat2x2Value;
    glm::dmat2x3 dmat2x3Value;
    glm::dmat2x4 dmat2x4Value;
    glm::dmat3x2 dmat3x2Value;
    glm::dmat3x3 dmat3x3Value;
    glm::dmat3x4 dmat3x4Value;
    glm::dmat4x2 dmat4x2Value;
    glm::dmat4x3 dmat4x3Value;
    glm::dmat4x4 dmat4x4Value;
};
)");

    REQUIRE(s->variables.size() == 32);
    REQUIRE(s->variables[0]->name == "boolVariable");
    REQUIRE(s->variables[0]->type == "bool");
    REQUIRE(s->variables[1]->name == "intVariable");
    REQUIRE(s->variables[1]->type == "int");
    REQUIRE(s->variables[2]->name == "doubleValue");
    REQUIRE(s->variables[2]->type == "double");
    REQUIRE(s->variables[3]->name == "floatValue");
    REQUIRE(s->variables[3]->type == "float");
    REQUIRE(s->variables[4]->name == "stringValue");
    REQUIRE(s->variables[4]->type == "std::string");
    REQUIRE(s->variables[5]->name == "ivec2Value");
    REQUIRE(s->variables[5]->type == "glm::ivec2");
    REQUIRE(s->variables[6]->name == "ivec3Value");
    REQUIRE(s->variables[6]->type == "glm::ivec3");
    REQUIRE(s->variables[7]->name == "ivec4Value");
    REQUIRE(s->variables[7]->type == "glm::ivec4");
    REQUIRE(s->variables[8]->name == "dvec2Value");
    REQUIRE(s->variables[8]->type == "glm::dvec2");
    REQUIRE(s->variables[9]->name == "dvec3Value");
    REQUIRE(s->variables[9]->type == "glm::dvec3");
    REQUIRE(s->variables[10]->name == "dvec4Value");
    REQUIRE(s->variables[10]->type == "glm::dvec4");
    REQUIRE(s->variables[11]->name == "vec2Value");
    REQUIRE(s->variables[11]->type == "glm::vec2");
    REQUIRE(s->variables[12]->name == "vec3Value");
    REQUIRE(s->variables[12]->type == "glm::vec3");
    REQUIRE(s->variables[13]->name == "vec4Value");
    REQUIRE(s->variables[13]->type == "glm::vec4");
    REQUIRE(s->variables[14]->name == "mat2x2Value");
    REQUIRE(s->variables[14]->type == "glm::mat2x2");
    REQUIRE(s->variables[15]->name == "mat2x3Value");
    REQUIRE(s->variables[15]->type == "glm::mat2x3");
    REQUIRE(s->variables[16]->name == "mat2x4Value");
    REQUIRE(s->variables[16]->type == "glm::mat2x4");
    REQUIRE(s->variables[17]->name == "mat3x2Value");
    REQUIRE(s->variables[17]->type == "glm::mat3x2");
    REQUIRE(s->variables[18]->name == "mat3x3Value");
    REQUIRE(s->variables[18]->type == "glm::mat3x3");
    REQUIRE(s->variables[19]->name == "mat3x4Value");
    REQUIRE(s->variables[19]->type == "glm::mat3x4");
    REQUIRE(s->variables[20]->name == "mat4x2Value");
    REQUIRE(s->variables[20]->type == "glm::mat4x2");
    REQUIRE(s->variables[21]->name == "mat4x3Value");
    REQUIRE(s->variables[21]->type == "glm::mat4x3");
    REQUIRE(s->variables[22]->name == "mat4x4Value");
    REQUIRE(s->variables[22]->type == "glm::mat4x4");
    REQUIRE(s->variables[23]->name == "dmat2x2Value");
    REQUIRE(s->variables[23]->type == "glm::dmat2x2");
    REQUIRE(s->variables[24]->name == "dmat2x3Value");
    REQUIRE(s->variables[24]->type == "glm::dmat2x3");
    REQUIRE(s->variables[25]->name == "dmat2x4Value");
    REQUIRE(s->variables[25]->type == "glm::dmat2x4");
    REQUIRE(s->variables[26]->name == "dmat3x2Value");
    REQUIRE(s->variables[26]->type == "glm::dmat3x2");
    REQUIRE(s->variables[27]->name == "dmat3x3Value");
    REQUIRE(s->variables[27]->type == "glm::dmat3x3");
    REQUIRE(s->variables[28]->name == "dmat3x4Value");
    REQUIRE(s->variables[28]->type == "glm::dmat3x4");
    REQUIRE(s->variables[29]->name == "dmat4x2Value");
    REQUIRE(s->variables[29]->type == "glm::dmat4x2");
    REQUIRE(s->variables[30]->name == "dmat4x3Value");
    REQUIRE(s->variables[30]->type == "glm::dmat4x3");
    REQUIRE(s->variables[31]->name == "dmat4x4Value");
    REQUIRE(s->variables[31]->type == "glm::dmat4x4");
}

TEST_CASE("Vector Base Types", "[variables]") {
    Struct* s = parseRootStruct(R"(
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
    std::vector<glm::mat2x3> mat2x3Value;
    std::vector<glm::mat2x4> mat2x4Value;
    std::vector<glm::mat3x2> mat3x2Value;
    std::vector<glm::mat3x3> mat3x3Value;
    std::vector<glm::mat3x4> mat3x4Value;
    std::vector<glm::mat4x2> mat4x2Value;
    std::vector<glm::mat4x3> mat4x3Value;
    std::vector<glm::mat4x4> mat4x4Value;
    std::vector<glm::dmat2x2> dmat2x2Value;
    std::vector<glm::dmat2x3> dmat2x3Value;
    std::vector<glm::dmat2x4> dmat2x4Value;
    std::vector<glm::dmat3x2> dmat3x2Value;
    std::vector<glm::dmat3x3> dmat3x3Value;
    std::vector<glm::dmat3x4> dmat3x4Value;
    std::vector<glm::dmat4x2> dmat4x2Value;
    std::vector<glm::dmat4x3> dmat4x3Value;
    std::vector<glm::dmat4x4> dmat4x4Value;
};
)");

    REQUIRE(s->variables.size() == 32);
    REQUIRE(s->variables[0]->name == "boolVariable");
    REQUIRE(s->variables[0]->type == "std::vector<bool>");
    REQUIRE(s->variables[1]->name == "intVariable");
    REQUIRE(s->variables[1]->type == "std::vector<int>");
    REQUIRE(s->variables[2]->name == "doubleValue");
    REQUIRE(s->variables[2]->type == "std::vector<double>");
    REQUIRE(s->variables[3]->name == "floatValue");
    REQUIRE(s->variables[3]->type == "std::vector<float>");
    REQUIRE(s->variables[4]->name == "stringValue");
    REQUIRE(s->variables[4]->type == "std::vector<std::string>");
    REQUIRE(s->variables[5]->name == "ivec2Value");
    REQUIRE(s->variables[5]->type == "std::vector<glm::ivec2>");
    REQUIRE(s->variables[6]->name == "ivec3Value");
    REQUIRE(s->variables[6]->type == "std::vector<glm::ivec3>");
    REQUIRE(s->variables[7]->name == "ivec4Value");
    REQUIRE(s->variables[7]->type == "std::vector<glm::ivec4>");
    REQUIRE(s->variables[8]->name == "dvec2Value");
    REQUIRE(s->variables[8]->type == "std::vector<glm::dvec2>");
    REQUIRE(s->variables[9]->name == "dvec3Value");
    REQUIRE(s->variables[9]->type == "std::vector<glm::dvec3>");
    REQUIRE(s->variables[10]->name == "dvec4Value");
    REQUIRE(s->variables[10]->type == "std::vector<glm::dvec4>");
    REQUIRE(s->variables[11]->name == "vec2Value");
    REQUIRE(s->variables[11]->type == "std::vector<glm::vec2>");
    REQUIRE(s->variables[12]->name == "vec3Value");
    REQUIRE(s->variables[12]->type == "std::vector<glm::vec3>");
    REQUIRE(s->variables[13]->name == "vec4Value");
    REQUIRE(s->variables[13]->type == "std::vector<glm::vec4>");
    REQUIRE(s->variables[14]->name == "mat2x2Value");
    REQUIRE(s->variables[14]->type == "std::vector<glm::mat2x2>");
    REQUIRE(s->variables[15]->name == "mat2x3Value");
    REQUIRE(s->variables[15]->type == "std::vector<glm::mat2x3>");
    REQUIRE(s->variables[16]->name == "mat2x4Value");
    REQUIRE(s->variables[16]->type == "std::vector<glm::mat2x4>");
    REQUIRE(s->variables[17]->name == "mat3x2Value");
    REQUIRE(s->variables[17]->type == "std::vector<glm::mat3x2>");
    REQUIRE(s->variables[18]->name == "mat3x3Value");
    REQUIRE(s->variables[18]->type == "std::vector<glm::mat3x3>");
    REQUIRE(s->variables[19]->name == "mat3x4Value");
    REQUIRE(s->variables[19]->type == "std::vector<glm::mat3x4>");
    REQUIRE(s->variables[20]->name == "mat4x2Value");
    REQUIRE(s->variables[20]->type == "std::vector<glm::mat4x2>");
    REQUIRE(s->variables[21]->name == "mat4x3Value");
    REQUIRE(s->variables[21]->type == "std::vector<glm::mat4x3>");
    REQUIRE(s->variables[22]->name == "mat4x4Value");
    REQUIRE(s->variables[22]->type == "std::vector<glm::mat4x4>");
    REQUIRE(s->variables[23]->name == "dmat2x2Value");
    REQUIRE(s->variables[23]->type == "std::vector<glm::dmat2x2>");
    REQUIRE(s->variables[24]->name == "dmat2x3Value");
    REQUIRE(s->variables[24]->type == "std::vector<glm::dmat2x3>");
    REQUIRE(s->variables[25]->name == "dmat2x4Value");
    REQUIRE(s->variables[25]->type == "std::vector<glm::dmat2x4>");
    REQUIRE(s->variables[26]->name == "dmat3x2Value");
    REQUIRE(s->variables[26]->type == "std::vector<glm::dmat3x2>");
    REQUIRE(s->variables[27]->name == "dmat3x3Value");
    REQUIRE(s->variables[27]->type == "std::vector<glm::dmat3x3>");
    REQUIRE(s->variables[28]->name == "dmat3x4Value");
    REQUIRE(s->variables[28]->type == "std::vector<glm::dmat3x4>");
    REQUIRE(s->variables[29]->name == "dmat4x2Value");
    REQUIRE(s->variables[29]->type == "std::vector<glm::dmat4x2>");
    REQUIRE(s->variables[30]->name == "dmat4x3Value");
    REQUIRE(s->variables[30]->type == "std::vector<glm::dmat4x3>");
    REQUIRE(s->variables[31]->name == "dmat4x4Value");
    REQUIRE(s->variables[31]->type == "std::vector<glm::dmat4x4>");
}

TEST_CASE("Optional Base Types", "[variables]") {
    Struct* s = parseRootStruct(R"(
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
    std::optional<glm::mat2x3> mat2x3Value;
    std::optional<glm::mat2x4> mat2x4Value;
    std::optional<glm::mat3x2> mat3x2Value;
    std::optional<glm::mat3x3> mat3x3Value;
    std::optional<glm::mat3x4> mat3x4Value;
    std::optional<glm::mat4x2> mat4x2Value;
    std::optional<glm::mat4x3> mat4x3Value;
    std::optional<glm::mat4x4> mat4x4Value;
    std::optional<glm::dmat2x2> dmat2x2Value;
    std::optional<glm::dmat2x3> dmat2x3Value;
    std::optional<glm::dmat2x4> dmat2x4Value;
    std::optional<glm::dmat3x2> dmat3x2Value;
    std::optional<glm::dmat3x3> dmat3x3Value;
    std::optional<glm::dmat3x4> dmat3x4Value;
    std::optional<glm::dmat4x2> dmat4x2Value;
    std::optional<glm::dmat4x3> dmat4x3Value;
    std::optional<glm::dmat4x4> dmat4x4Value;
};
)");

    REQUIRE(s->variables.size() == 32);
    REQUIRE(s->variables[0]->name == "boolVariable");
    REQUIRE(s->variables[0]->type == "std::optional<bool>");
    REQUIRE(s->variables[1]->name == "intVariable");
    REQUIRE(s->variables[1]->type == "std::optional<int>");
    REQUIRE(s->variables[2]->name == "doubleValue");
    REQUIRE(s->variables[2]->type == "std::optional<double>");
    REQUIRE(s->variables[3]->name == "floatValue");
    REQUIRE(s->variables[3]->type == "std::optional<float>");
    REQUIRE(s->variables[4]->name == "stringValue");
    REQUIRE(s->variables[4]->type == "std::optional<std::string>");
    REQUIRE(s->variables[5]->name == "ivec2Value");
    REQUIRE(s->variables[5]->type == "std::optional<glm::ivec2>");
    REQUIRE(s->variables[6]->name == "ivec3Value");
    REQUIRE(s->variables[6]->type == "std::optional<glm::ivec3>");
    REQUIRE(s->variables[7]->name == "ivec4Value");
    REQUIRE(s->variables[7]->type == "std::optional<glm::ivec4>");
    REQUIRE(s->variables[8]->name == "dvec2Value");
    REQUIRE(s->variables[8]->type == "std::optional<glm::dvec2>");
    REQUIRE(s->variables[9]->name == "dvec3Value");
    REQUIRE(s->variables[9]->type == "std::optional<glm::dvec3>");
    REQUIRE(s->variables[10]->name == "dvec4Value");
    REQUIRE(s->variables[10]->type == "std::optional<glm::dvec4>");
    REQUIRE(s->variables[11]->name == "vec2Value");
    REQUIRE(s->variables[11]->type == "std::optional<glm::vec2>");
    REQUIRE(s->variables[12]->name == "vec3Value");
    REQUIRE(s->variables[12]->type == "std::optional<glm::vec3>");
    REQUIRE(s->variables[13]->name == "vec4Value");
    REQUIRE(s->variables[13]->type == "std::optional<glm::vec4>");
    REQUIRE(s->variables[14]->name == "mat2x2Value");
    REQUIRE(s->variables[14]->type == "std::optional<glm::mat2x2>");
    REQUIRE(s->variables[15]->name == "mat2x3Value");
    REQUIRE(s->variables[15]->type == "std::optional<glm::mat2x3>");
    REQUIRE(s->variables[16]->name == "mat2x4Value");
    REQUIRE(s->variables[16]->type == "std::optional<glm::mat2x4>");
    REQUIRE(s->variables[17]->name == "mat3x2Value");
    REQUIRE(s->variables[17]->type == "std::optional<glm::mat3x2>");
    REQUIRE(s->variables[18]->name == "mat3x3Value");
    REQUIRE(s->variables[18]->type == "std::optional<glm::mat3x3>");
    REQUIRE(s->variables[19]->name == "mat3x4Value");
    REQUIRE(s->variables[19]->type == "std::optional<glm::mat3x4>");
    REQUIRE(s->variables[20]->name == "mat4x2Value");
    REQUIRE(s->variables[20]->type == "std::optional<glm::mat4x2>");
    REQUIRE(s->variables[21]->name == "mat4x3Value");
    REQUIRE(s->variables[21]->type == "std::optional<glm::mat4x3>");
    REQUIRE(s->variables[22]->name == "mat4x4Value");
    REQUIRE(s->variables[22]->type == "std::optional<glm::mat4x4>");
    REQUIRE(s->variables[23]->name == "dmat2x2Value");
    REQUIRE(s->variables[23]->type == "std::optional<glm::dmat2x2>");
    REQUIRE(s->variables[24]->name == "dmat2x3Value");
    REQUIRE(s->variables[24]->type == "std::optional<glm::dmat2x3>");
    REQUIRE(s->variables[25]->name == "dmat2x4Value");
    REQUIRE(s->variables[25]->type == "std::optional<glm::dmat2x4>");
    REQUIRE(s->variables[26]->name == "dmat3x2Value");
    REQUIRE(s->variables[26]->type == "std::optional<glm::dmat3x2>");
    REQUIRE(s->variables[27]->name == "dmat3x3Value");
    REQUIRE(s->variables[27]->type == "std::optional<glm::dmat3x3>");
    REQUIRE(s->variables[28]->name == "dmat3x4Value");
    REQUIRE(s->variables[28]->type == "std::optional<glm::dmat3x4>");
    REQUIRE(s->variables[29]->name == "dmat4x2Value");
    REQUIRE(s->variables[29]->type == "std::optional<glm::dmat4x2>");
    REQUIRE(s->variables[30]->name == "dmat4x3Value");
    REQUIRE(s->variables[30]->type == "std::optional<glm::dmat4x3>");
    REQUIRE(s->variables[31]->name == "dmat4x4Value");
    REQUIRE(s->variables[31]->type == "std::optional<glm::dmat4x4>");
}

