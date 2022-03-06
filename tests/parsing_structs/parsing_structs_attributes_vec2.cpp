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

TEST_CASE("Parsing/Structs/Attributes/Vec2") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inRangeValueVec2 documentation
        glm::vec2 inRangeValueVec2 [[codegen::inrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // inRangeValueVec2Optional documentation
        std::optional<glm::vec2> inRangeValueVec2Optional
            [[codegen::inrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // inRangeValueVec2Vector documentation
        std::vector<glm::vec2> inRangeValueVec2Vector
            [[codegen::inrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // notInRangeValueVec2 documentation
        glm::vec2 notInRangeValueVec2
            [[codegen::notinrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // notInRangeValueVec2Optional documentation
        std::optional<glm::vec2> notInRangeValueVec2Optional
            [[codegen::notinrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // notInRangeValueVec2Vector documentation
        std::vector<glm::vec2> notInRangeValueVec2Vector
            [[codegen::notinrange(glm::vec2(1.f), glm::vec2(2.f))]];

        // lessValueVec2 documentation
        glm::vec2 lessValueVec2 [[codegen::less(glm::vec2(1.f))]];

        // lessValueVec2Optional documentation
        std::optional<glm::vec2> lessValueVec2Optional [[codegen::less(glm::vec2(1.f))]];

        // lessValueVec2Vector documentation
        std::vector<glm::vec2> lessValueVec2Vector [[codegen::less(glm::vec2(1.f))]];

        // lessEqualValueVec2 documentation
        glm::vec2 lessEqualValueVec2 [[codegen::lessequal(glm::vec2(1.f))]];

        // lessEqualValueVec2Optional documentation
        std::optional<glm::vec2> lessEqualValueVec2Optional
            [[codegen::lessequal(glm::vec2(1.f))]];

        // lessEqualValueVec2Vector documentation
        std::vector<glm::vec2> lessEqualValueVec2Vector
            [[codegen::lessequal(glm::vec2(1.f))]];

        // greaterValueVec2 documentation
        glm::vec2 greaterValueVec2 [[codegen::greater(glm::vec2(1.f))]];

        // greaterValueVec2Optional documentation
        std::optional<glm::vec2> greaterValueVec2Optional
            [[codegen::greater(glm::vec2(1.f))]];

        // greaterValueVec2Vector documentation
        std::vector<glm::vec2> greaterValueVec2Vector
            [[codegen::greater(glm::vec2(1.f))]];

        // greaterEqualValueVec2 documentation
        glm::vec2 greaterEqualValueVec2 [[codegen::greaterequal(glm::vec2(1.f))]];

        // greaterEqualValueVec2Optional documentation
        std::optional<glm::vec2> greaterEqualValueVec2Optional
            [[codegen::greaterequal(glm::vec2(1.f))]];

        // greaterEqualValueVec2Vector documentation
        std::vector<glm::vec2> greaterEqualValueVec2Vector
            [[codegen::greaterequal(glm::vec2(1.f))]];

        // unequalValueVec2 documentation
        glm::vec2 unequalValueVec2 [[codegen::unequal(glm::vec2(1.f))]];

        // unequalValueVec2Optional documentation
        std::optional<glm::vec2> unequalValueVec2Optional
            [[codegen::unequal(glm::vec2(1.f))]];

        // unequalValueVec2Vector documentation
        std::vector<glm::vec2> unequalValueVec2Vector
            [[codegen::unequal(glm::vec2(1.f))]];
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
        CHECK(var->name == "inRangeValueVec2");
        CHECK(var->key == "\"InRangeValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "inRangeValueVec2 documentation");
        CHECK(var->attributes.inrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "inRangeValueVec2Optional");
        CHECK(var->key == "\"InRangeValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "inRangeValueVec2Optional documentation");
        CHECK(var->attributes.inrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "inRangeValueVec2Vector");
        CHECK(var->key == "\"InRangeValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "inRangeValueVec2Vector documentation");
        CHECK(var->attributes.inrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "notInRangeValueVec2");
        CHECK(var->key == "\"NotInRangeValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "notInRangeValueVec2 documentation");
        CHECK(var->attributes.notinrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "notInRangeValueVec2Optional");
        CHECK(var->key == "\"NotInRangeValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "notInRangeValueVec2Optional documentation");
        CHECK(var->attributes.notinrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "notInRangeValueVec2Vector");
        CHECK(var->key == "\"NotInRangeValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "notInRangeValueVec2Vector documentation");
        CHECK(var->attributes.notinrange == "glm::vec2(1.f), glm::vec2(2.f)");

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
        CHECK(var->name == "lessValueVec2");
        CHECK(var->key == "\"LessValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "lessValueVec2 documentation");
        CHECK(var->attributes.less == "glm::vec2(1.f)");

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
        CHECK(var->name == "lessValueVec2Optional");
        CHECK(var->key == "\"LessValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "lessValueVec2Optional documentation");
        CHECK(var->attributes.less == "glm::vec2(1.f)");

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
        CHECK(var->name == "lessValueVec2Vector");
        CHECK(var->key == "\"LessValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "lessValueVec2Vector documentation");
        CHECK(var->attributes.less == "glm::vec2(1.f)");

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
        CHECK(var->name == "lessEqualValueVec2");
        CHECK(var->key == "\"LessEqualValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "lessEqualValueVec2 documentation");
        CHECK(var->attributes.lessequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "lessEqualValueVec2Optional");
        CHECK(var->key == "\"LessEqualValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "lessEqualValueVec2Optional documentation");
        CHECK(var->attributes.lessequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "lessEqualValueVec2Vector");
        CHECK(var->key == "\"LessEqualValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "lessEqualValueVec2Vector documentation");
        CHECK(var->attributes.lessequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterValueVec2");
        CHECK(var->key == "\"GreaterValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "greaterValueVec2 documentation");
        CHECK(var->attributes.greater == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterValueVec2Optional");
        CHECK(var->key == "\"GreaterValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "greaterValueVec2Optional documentation");
        CHECK(var->attributes.greater == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterValueVec2Vector");
        CHECK(var->key == "\"GreaterValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "greaterValueVec2Vector documentation");
        CHECK(var->attributes.greater == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec2");
        CHECK(var->key == "\"GreaterEqualValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "greaterEqualValueVec2 documentation");
        CHECK(var->attributes.greaterequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec2Optional");
        CHECK(var->key == "\"GreaterEqualValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "greaterEqualValueVec2Optional documentation");
        CHECK(var->attributes.greaterequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec2Vector");
        CHECK(var->key == "\"GreaterEqualValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "greaterEqualValueVec2Vector documentation");
        CHECK(var->attributes.greaterequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "unequalValueVec2");
        CHECK(var->key == "\"UnequalValueVec2\"");
        CHECK(generateTypename(var->type) == "glm::vec2");
        CHECK(var->comment == "unequalValueVec2 documentation");
        CHECK(var->attributes.unequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "unequalValueVec2Optional");
        CHECK(var->key == "\"UnequalValueVec2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec2>");
        CHECK(var->comment == "unequalValueVec2Optional documentation");
        CHECK(var->attributes.unequal == "glm::vec2(1.f)");

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
        CHECK(var->name == "unequalValueVec2Vector");
        CHECK(var->key == "\"UnequalValueVec2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec2>");
        CHECK(var->comment == "unequalValueVec2Vector documentation");
        CHECK(var->attributes.unequal == "glm::vec2(1.f)");

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
