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

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Attributes/IVec4") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inRangeValueIVec4 documentation
        glm::ivec4 inRangeValueIVec4 [[codegen::inrange(glm::ivec4(1), glm::ivec4(2))]];

        // inRangeValueIVec4Optional documentation
        std::optional<glm::ivec4> inRangeValueIVec4Optional
            [[codegen::inrange(glm::ivec4(1), glm::ivec4(2))]];

        // inRangeValueIVec4Vector documentation
        std::vector<glm::ivec4> inRangeValueIVec4Vector
            [[codegen::inrange(glm::ivec4(1), glm::ivec4(2))]];

        // notInRangeValueIVec4 documentation
        glm::ivec4 notInRangeValueIVec4
            [[codegen::notinrange(glm::ivec4(1), glm::ivec4(2))]];

        // notInRangeValueIVec4Optional documentation
        std::optional<glm::ivec4> notInRangeValueIVec4Optional
            [[codegen::notinrange(glm::ivec4(1), glm::ivec4(2))]];

        // notInRangeValueIVec4Vector documentation
        std::vector<glm::ivec4> notInRangeValueIVec4Vector
            [[codegen::notinrange(glm::ivec4(1), glm::ivec4(2))]];

        // lessValueIVec4 documentation
        glm::ivec4 lessValueIVec4 [[codegen::less(glm::ivec4(1))]];

        // lessValueIVec4Optional documentation
        std::optional<glm::ivec4> lessValueIVec4Optional [[codegen::less(glm::ivec4(1))]];

        // lessValueIVec4Vector documentation
        std::vector<glm::ivec4> lessValueIVec4Vector [[codegen::less(glm::ivec4(1))]];

        // lessEqualValueIVec4 documentation
        glm::ivec4 lessEqualValueIVec4 [[codegen::lessequal(glm::ivec4(1))]];

        // lessEqualValueIVec4Optional documentation
        std::optional<glm::ivec4> lessEqualValueIVec4Optional
            [[codegen::lessequal(glm::ivec4(1))]];

        // lessEqualValueIVec4Vector documentation
        std::vector<glm::ivec4> lessEqualValueIVec4Vector
            [[codegen::lessequal(glm::ivec4(1))]];

        // greaterValueIVec4 documentation
        glm::ivec4 greaterValueIVec4 [[codegen::greater(glm::ivec4(1))]];

        // greaterValueIVec4Optional documentation
        std::optional<glm::ivec4> greaterValueIVec4Optional
            [[codegen::greater(glm::ivec4(1))]];

        // greaterValueIVec4Vector documentation
        std::vector<glm::ivec4> greaterValueIVec4Vector
            [[codegen::greater(glm::ivec4(1))]];

        // greaterEqualValueIVec4 documentation
        glm::ivec4 greaterEqualValueIVec4 [[codegen::greaterequal(glm::ivec4(1))]];

        // greaterEqualValueIVec4Optional documentation
        std::optional<glm::ivec4> greaterEqualValueIVec4Optional
            [[codegen::greaterequal(glm::ivec4(1))]];

        // greaterEqualValueIVec4Vector documentation
        std::vector<glm::ivec4> greaterEqualValueIVec4Vector
            [[codegen::greaterequal(glm::ivec4(1))]];

        // unequalValueIVec4 documentation
        glm::ivec4 unequalValueIVec4 [[codegen::unequal(glm::ivec4(1))]];

        // unequalValueIVec4Optional documentation
        std::optional<glm::ivec4> unequalValueIVec4Optional
            [[codegen::unequal(glm::ivec4(1))]];

        // unequalValueIVec4Vector documentation
        std::vector<glm::ivec4> unequalValueIVec4Vector
            [[codegen::unequal(glm::ivec4(1))]];
})";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 21);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIVec4");
        CHECK(var->key == "\"InRangeValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "inRangeValueIVec4 documentation");
        CHECK(var->attributes.inrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "inRangeValueIVec4Optional");
        CHECK(var->key == "\"InRangeValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "inRangeValueIVec4Optional documentation");
        CHECK(var->attributes.inrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "inRangeValueIVec4Vector");
        CHECK(var->key == "\"InRangeValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "inRangeValueIVec4Vector documentation");
        CHECK(var->attributes.inrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "notInRangeValueIVec4");
        CHECK(var->key == "\"NotInRangeValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "notInRangeValueIVec4 documentation");
        CHECK(var->attributes.notinrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "notInRangeValueIVec4Optional");
        CHECK(var->key == "\"NotInRangeValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "notInRangeValueIVec4Optional documentation");
        CHECK(var->attributes.notinrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "notInRangeValueIVec4Vector");
        CHECK(var->key == "\"NotInRangeValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "notInRangeValueIVec4Vector documentation");
        CHECK(var->attributes.notinrange == "glm::ivec4(1), glm::ivec4(2)");

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
        CHECK(var->name == "lessValueIVec4");
        CHECK(var->key == "\"LessValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "lessValueIVec4 documentation");
        CHECK(var->attributes.less == "glm::ivec4(1)");

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
        CHECK(var->name == "lessValueIVec4Optional");
        CHECK(var->key == "\"LessValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "lessValueIVec4Optional documentation");
        CHECK(var->attributes.less == "glm::ivec4(1)");

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
        CHECK(var->name == "lessValueIVec4Vector");
        CHECK(var->key == "\"LessValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "lessValueIVec4Vector documentation");
        CHECK(var->attributes.less == "glm::ivec4(1)");

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
        CHECK(var->name == "lessEqualValueIVec4");
        CHECK(var->key == "\"LessEqualValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "lessEqualValueIVec4 documentation");
        CHECK(var->attributes.lessequal == "glm::ivec4(1)");

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
        CHECK(var->name == "lessEqualValueIVec4Optional");
        CHECK(var->key == "\"LessEqualValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "lessEqualValueIVec4Optional documentation");
        CHECK(var->attributes.lessequal == "glm::ivec4(1)");

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
        CHECK(var->name == "lessEqualValueIVec4Vector");
        CHECK(var->key == "\"LessEqualValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "lessEqualValueIVec4Vector documentation");
        CHECK(var->attributes.lessequal == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterValueIVec4");
        CHECK(var->key == "\"GreaterValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "greaterValueIVec4 documentation");
        CHECK(var->attributes.greater == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterValueIVec4Optional");
        CHECK(var->key == "\"GreaterValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "greaterValueIVec4Optional documentation");
        CHECK(var->attributes.greater == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterValueIVec4Vector");
        CHECK(var->key == "\"GreaterValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "greaterValueIVec4Vector documentation");
        CHECK(var->attributes.greater == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterEqualValueIVec4");
        CHECK(var->key == "\"GreaterEqualValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "greaterEqualValueIVec4 documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterEqualValueIVec4Optional");
        CHECK(var->key == "\"GreaterEqualValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "greaterEqualValueIVec4Optional documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec4(1)");

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
        CHECK(var->name == "greaterEqualValueIVec4Vector");
        CHECK(var->key == "\"GreaterEqualValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "greaterEqualValueIVec4Vector documentation");
        CHECK(var->attributes.greaterequal == "glm::ivec4(1)");

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
        CHECK(var->name == "unequalValueIVec4");
        CHECK(var->key == "\"UnequalValueIVec4\"");
        CHECK(generateTypename(var->type) == "glm::ivec4");
        CHECK(var->comment == "unequalValueIVec4 documentation");
        CHECK(var->attributes.unequal == "glm::ivec4(1)");

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
        CHECK(var->name == "unequalValueIVec4Optional");
        CHECK(var->key == "\"UnequalValueIVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::ivec4>");
        CHECK(var->comment == "unequalValueIVec4Optional documentation");
        CHECK(var->attributes.unequal == "glm::ivec4(1)");

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
        CHECK(var->name == "unequalValueIVec4Vector");
        CHECK(var->key == "\"UnequalValueIVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::ivec4>");
        CHECK(var->comment == "unequalValueIVec4Vector documentation");
        CHECK(var->attributes.unequal == "glm::ivec4(1)");

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
}
