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

TEST_CASE("Parsing/Structs/Attributes/Vec3") {
    constexpr std::string_view Source = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inRangeValueVec3 documentation
        glm::vec3 inRangeValueVec3 [[codegen::inrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // inRangeValueVec3Optional documentation
        std::optional<glm::vec3> inRangeValueVec3Optional
            [[codegen::inrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // inRangeValueVec3Vector documentation
        std::vector<glm::vec3> inRangeValueVec3Vector
            [[codegen::inrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // notInRangeValueVec3 documentation
        glm::vec3 notInRangeValueVec3
            [[codegen::notinrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // notInRangeValueVec3Optional documentation
        std::optional<glm::vec3> notInRangeValueVec3Optional
            [[codegen::notinrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // notInRangeValueVec3Vector documentation
        std::vector<glm::vec3> notInRangeValueVec3Vector
            [[codegen::notinrange(glm::vec3(1.f), glm::vec3(2.f))]];

        // lessValueVec3 documentation
        glm::vec3 lessValueVec3 [[codegen::less(glm::vec3(1.f))]];

        // lessValueVec3Optional documentation
        std::optional<glm::vec3> lessValueVec3Optional [[codegen::less(glm::vec3(1.f))]];

        // lessValueVec3Vector documentation
        std::vector<glm::vec3> lessValueVec3Vector [[codegen::less(glm::vec3(1.f))]];

        // lessEqualValueVec3 documentation
        glm::vec3 lessEqualValueVec3 [[codegen::lessequal(glm::vec3(1.f))]];

        // lessEqualValueVec3Optional documentation
        std::optional<glm::vec3> lessEqualValueVec3Optional
            [[codegen::lessequal(glm::vec3(1.f))]];

        // lessEqualValueVec3Vector documentation
        std::vector<glm::vec3> lessEqualValueVec3Vector
            [[codegen::lessequal(glm::vec3(1.f))]];

        // greaterValueVec3 documentation
        glm::vec3 greaterValueVec3 [[codegen::greater(glm::vec3(1.f))]];

        // greaterValueVec3Optional documentation
        std::optional<glm::vec3> greaterValueVec3Optional
            [[codegen::greater(glm::vec3(1.f))]];

        // greaterValueVec3Vector documentation
        std::vector<glm::vec3> greaterValueVec3Vector
            [[codegen::greater(glm::vec3(1.f))]];

        // greaterEqualValueVec3 documentation
        glm::vec3 greaterEqualValueVec3 [[codegen::greaterequal(glm::vec3(1.f))]];

        // greaterEqualValueVec3Optional documentation
        std::optional<glm::vec3> greaterEqualValueVec3Optional
            [[codegen::greaterequal(glm::vec3(1.f))]];

        // greaterEqualValueVec3Vector documentation
        std::vector<glm::vec3> greaterEqualValueVec3Vector
            [[codegen::greaterequal(glm::vec3(1.f))]];

        // unequalValueVec3 documentation
        glm::vec3 unequalValueVec3 [[codegen::unequal(glm::vec3(1.f))]];

        // unequalValueVec3Optional documentation
        std::optional<glm::vec3> unequalValueVec3Optional
            [[codegen::unequal(glm::vec3(1.f))]];

        // unequalValueVec3Vector documentation
        std::vector<glm::vec3> unequalValueVec3Vector
            [[codegen::unequal(glm::vec3(1.f))]];

        // dcolor3Value documentation
        glm::dvec3 dcolor3Value [[codegen::color()]];

        // optionalDcolor3Value documentation
        std::optional<glm::dvec3> optionalDcolor3Value [[codegen::color()]];

        // vectorDcolor3Value documentation
        std::vector<glm::dvec3> vectorDcolor3Value [[codegen::color()]];

        // optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> optionalVectorDcolor3Value
            [[codegen::color()]];

        // not dcolor3Value documentation
        glm::dvec3 notDcolor3Value [[codegen::color(false)]];

        // not optionalDcolor3Value documentation
        std::optional<glm::dvec3> notOptionalDcolor3Value [[codegen::color(false)]];

        // not vectorDcolor3Value documentation
        std::vector<glm::dvec3> notVectorDcolor3Value [[codegen::color(false)]];

        // not optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> notOptionalVectorDcolor3Value
            [[codegen::color(false)]];

        // yes dcolor3Value documentation
        glm::dvec3 yesDcolor3Value [[codegen::color(true)]];

        // yes optionalDcolor3Value documentation
        std::optional<glm::dvec3> yesOptionalDcolor3Value [[codegen::color(true)]];

        // yes vectorDcolor3Value documentation
        std::vector<glm::dvec3> yesVectorDcolor3Value [[codegen::color(true)]];

        // yes optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> yesOptionalVectorDcolor3Value
            [[codegen::color(true)]];

})";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    CHECK(code.luaWrapperFunctions.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 33);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueVec3");
        CHECK(var->key == "\"InRangeValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "inRangeValueVec3 documentation");
        CHECK(var->attributes.inrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueVec3Optional");
        CHECK(var->key == "\"InRangeValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "inRangeValueVec3Optional documentation");
        CHECK(var->attributes.inrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueVec3Vector");
        CHECK(var->key == "\"InRangeValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "inRangeValueVec3Vector documentation");
        CHECK(var->attributes.inrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueVec3");
        CHECK(var->key == "\"NotInRangeValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "notInRangeValueVec3 documentation");
        CHECK(var->attributes.notinrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueVec3Optional");
        CHECK(var->key == "\"NotInRangeValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "notInRangeValueVec3Optional documentation");
        CHECK(var->attributes.notinrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueVec3Vector");
        CHECK(var->key == "\"NotInRangeValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "notInRangeValueVec3Vector documentation");
        CHECK(var->attributes.notinrange == "glm::vec3(1.f), glm::vec3(2.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "lessValueVec3");
        CHECK(var->key == "\"LessValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "lessValueVec3 documentation");
        CHECK(var->attributes.less == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "lessValueVec3Optional");
        CHECK(var->key == "\"LessValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "lessValueVec3Optional documentation");
        CHECK(var->attributes.less == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "lessValueVec3Vector");
        CHECK(var->key == "\"LessValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "lessValueVec3Vector documentation");
        CHECK(var->attributes.less == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueVec3");
        CHECK(var->key == "\"LessEqualValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "lessEqualValueVec3 documentation");
        CHECK(var->attributes.lessequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueVec3Optional");
        CHECK(var->key == "\"LessEqualValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "lessEqualValueVec3Optional documentation");
        CHECK(var->attributes.lessequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueVec3Vector");
        CHECK(var->key == "\"LessEqualValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "lessEqualValueVec3Vector documentation");
        CHECK(var->attributes.lessequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "greaterValueVec3");
        CHECK(var->key == "\"GreaterValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "greaterValueVec3 documentation");
        CHECK(var->attributes.greater == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "greaterValueVec3Optional");
        CHECK(var->key == "\"GreaterValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "greaterValueVec3Optional documentation");
        CHECK(var->attributes.greater == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "greaterValueVec3Vector");
        CHECK(var->key == "\"GreaterValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "greaterValueVec3Vector documentation");
        CHECK(var->attributes.greater == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueVec3");
        CHECK(var->key == "\"GreaterEqualValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "greaterEqualValueVec3 documentation");
        CHECK(var->attributes.greaterequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueVec3Optional");
        CHECK(var->key == "\"GreaterEqualValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "greaterEqualValueVec3Optional documentation");
        CHECK(var->attributes.greaterequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueVec3Vector");
        CHECK(var->key == "\"GreaterEqualValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "greaterEqualValueVec3Vector documentation");
        CHECK(var->attributes.greaterequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "unequalValueVec3");
        CHECK(var->key == "\"UnequalValueVec3\"");
        CHECK(generateTypename(var->type) == "glm::vec3");
        CHECK(var->comment == "unequalValueVec3 documentation");
        CHECK(var->attributes.unequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "unequalValueVec3Optional");
        CHECK(var->key == "\"UnequalValueVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec3>");
        CHECK(var->comment == "unequalValueVec3Optional documentation");
        CHECK(var->attributes.unequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "unequalValueVec3Vector");
        CHECK(var->key == "\"UnequalValueVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec3>");
        CHECK(var->comment == "unequalValueVec3Vector documentation");
        CHECK(var->attributes.unequal == "glm::vec3(1.f)");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "dcolor3Value");
        CHECK(var->key == "\"Dcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "dcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "optionalDcolor3Value");
        CHECK(var->key == "\"OptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "optionalDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "vectorDcolor3Value");
        CHECK(var->key == "\"VectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "vectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorDcolor3Value");
        CHECK(var->key == "\"OptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "optionalVectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "notDcolor3Value");
        CHECK(var->key == "\"NotDcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "not dcolor3Value documentation");
        CHECK(!var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "notOptionalDcolor3Value");
        CHECK(var->key == "\"NotOptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "not optionalDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "notVectorDcolor3Value");
        CHECK(var->key == "\"NotVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "not vectorDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "notOptionalVectorDcolor3Value");
        CHECK(var->key == "\"NotOptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "not optionalVectorDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "yesDcolor3Value");
        CHECK(var->key == "\"YesDcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "yes dcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalDcolor3Value");
        CHECK(var->key == "\"YesOptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "yes optionalDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "yesVectorDcolor3Value");
        CHECK(var->key == "\"YesVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "yes vectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalVectorDcolor3Value");
        CHECK(var->key == "\"YesOptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "yes optionalVectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
