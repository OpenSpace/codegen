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

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Attributes/IVec3") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inRangeValueIVec3 documentation
        glm::ivec3 inRangeValueIVec3 [[codegen::inrange(glm::ivec3(1), glm::ivec3(2))]];

        // inRangeValueIVec3Optional documentation
        std::optional<glm::ivec3> inRangeValueIVec3Optional
            [[codegen::inrange(glm::ivec3(1), glm::ivec3(2))]];

        // inRangeValueIVec3Vector documentation
        std::vector<glm::ivec3> inRangeValueIVec3Vector
            [[codegen::inrange(glm::ivec3(1), glm::ivec3(2))]];

        // notInRangeValueIVec3 documentation
        glm::ivec3 notInRangeValueIVec3
            [[codegen::notinrange(glm::ivec3(1), glm::ivec3(2))]];

        // notInRangeValueIVec3Optional documentation
        std::optional<glm::ivec3> notInRangeValueIVec3Optional
            [[codegen::notinrange(glm::ivec3(1), glm::ivec3(2))]];

        // notInRangeValueIVec3Vector documentation
        std::vector<glm::ivec3> notInRangeValueIVec3Vector
            [[codegen::notinrange(glm::ivec3(1), glm::ivec3(2))]];

        // lessValueIVec3 documentation
        glm::ivec3 lessValueIVec3 [[codegen::less(glm::ivec3(1))]];

        // lessValueIVec3Optional documentation
        std::optional<glm::ivec3> lessValueIVec3Optional [[codegen::less(glm::ivec3(1))]];

        // lessValueIVec3Vector documentation
        std::vector<glm::ivec3> lessValueIVec3Vector [[codegen::less(glm::ivec3(1))]];

        // lessEqualValueIVec3 documentation
        glm::ivec3 lessEqualValueIVec3 [[codegen::lessequal(glm::ivec3(1))]];

        // lessEqualValueIVec3Optional documentation
        std::optional<glm::ivec3> lessEqualValueIVec3Optional
            [[codegen::lessequal(glm::ivec3(1))]];

        // lessEqualValueIVec3Vector documentation
        std::vector<glm::ivec3> lessEqualValueIVec3Vector
            [[codegen::lessequal(glm::ivec3(1))]];

        // greaterValueIVec3 documentation
        glm::ivec3 greaterValueIVec3 [[codegen::greater(glm::ivec3(1))]];

        // greaterValueIVec3Optional documentation
        std::optional<glm::ivec3> greaterValueIVec3Optional
            [[codegen::greater(glm::ivec3(1))]];

        // greaterValueIVec3Vector documentation
        std::vector<glm::ivec3> greaterValueIVec3Vector
            [[codegen::greater(glm::ivec3(1))]];

        // greaterEqualValueIVec3 documentation
        glm::ivec3 greaterEqualValueIVec3 [[codegen::greaterequal(glm::ivec3(1))]];

        // greaterEqualValueIVec3Optional documentation
        std::optional<glm::ivec3> greaterEqualValueIVec3Optional
            [[codegen::greaterequal(glm::ivec3(1))]];

        // greaterEqualValueIVec3Vector documentation
        std::vector<glm::ivec3> greaterEqualValueIVec3Vector
            [[codegen::greaterequal(glm::ivec3(1))]];

        // unequalValueIVec3 documentation
        glm::ivec3 unequalValueIVec3 [[codegen::unequal(glm::ivec3(1))]];

        // unequalValueIVec3Optional documentation
        std::optional<glm::ivec3> unequalValueIVec3Optional
            [[codegen::unequal(glm::ivec3(1))]];

        // unequalValueIVec3Vector documentation
        std::vector<glm::ivec3> unequalValueIVec3Vector
            [[codegen::unequal(glm::ivec3(1))]];
})";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    CHECK(code.luaWrapperFunctions.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 21);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIVec3");
        CHECK(var->key == "\"InRangeValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "inRangeValueIVec3 documentation");
        CHECK(var->attributes.inrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIVec3Optional");
        CHECK(var->key == "\"InRangeValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "inRangeValueIVec3Optional documentation");
        CHECK(var->attributes.inrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIVec3Vector");
        CHECK(var->key == "\"InRangeValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "inRangeValueIVec3Vector documentation");
        CHECK(var->attributes.inrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIVec3");
        CHECK(var->key == "\"NotInRangeValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "notInRangeValueIVec3 documentation");
        CHECK(var->attributes.notinrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIVec3Optional");
        CHECK(var->key == "\"NotInRangeValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "notInRangeValueIVec3Optional documentation");
        CHECK(var->attributes.notinrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIVec3Vector");
        CHECK(var->key == "\"NotInRangeValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "notInRangeValueIVec3Vector documentation");
        CHECK(var->attributes.notinrange == "glm::ivec3(1), glm::ivec3(2)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "lessValueIVec3");
        CHECK(var->key == "\"LessValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "lessValueIVec3 documentation");
        CHECK(var->attributes.less == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "lessValueIVec3Optional");
        CHECK(var->key == "\"LessValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "lessValueIVec3Optional documentation");
        CHECK(var->attributes.less == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "lessValueIVec3Vector");
        CHECK(var->key == "\"LessValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "lessValueIVec3Vector documentation");
        CHECK(var->attributes.less == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIVec3");
        CHECK(var->key == "\"LessEqualValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "lessEqualValueIVec3 documentation");
        CHECK(var->attributes.lessequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIVec3Optional");
        CHECK(var->key == "\"LessEqualValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "lessEqualValueIVec3Optional documentation");
        CHECK(var->attributes.lessequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIVec3Vector");
        CHECK(var->key == "\"LessEqualValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "lessEqualValueIVec3Vector documentation");
        CHECK(var->attributes.lessequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIVec3");
        CHECK(var->key == "\"GreaterValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "greaterValueIVec3 documentation");
        CHECK(var->attributes.greater == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIVec3Optional");
        CHECK(var->key == "\"GreaterValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "greaterValueIVec3Optional documentation");
        CHECK(var->attributes.greater == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIVec3Vector");
        CHECK(var->key == "\"GreaterValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "greaterValueIVec3Vector documentation");
        CHECK(var->attributes.greater == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIVec3");
        CHECK(var->key == "\"GreaterEqualValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "greaterEqualValueIVec3 documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIVec3Optional");
        CHECK(var->key == "\"GreaterEqualValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "greaterEqualValueIVec3Optional documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIVec3Vector");
        CHECK(var->key == "\"GreaterEqualValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "greaterEqualValueIVec3Vector documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIVec3");
        CHECK(var->key == "\"UnequalValueIVec3\"");
        CHECK(generateTypename(var->type) == "glm::ivec3");
        CHECK(var->comment == "unequalValueIVec3 documentation");
        CHECK(var->attributes.unequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIVec3Optional");
        CHECK(var->key == "\"UnequalValueIVec3Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec3>");
        CHECK(var->comment == "unequalValueIVec3Optional documentation");
        CHECK(var->attributes.unequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIVec3Vector");
        CHECK(var->key == "\"UnequalValueIVec3Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec3>");
        CHECK(var->comment == "unequalValueIVec3Vector documentation");
        CHECK(var->attributes.unequal == "glm::ivec3(1)");

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
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
