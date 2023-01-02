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

TEST_CASE("Parsing/Structs/Attributes/Vec4") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inRangeValueVec4 documentation
        glm::vec4 inRangeValueVec4 [[codegen::inrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // inRangeValueVec4Optional documentation
        std::optional<glm::vec4> inRangeValueVec4Optional
            [[codegen::inrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // inRangeValueVec4Vector documentation
        std::vector<glm::vec4> inRangeValueVec4Vector
            [[codegen::inrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // notInRangeValueVec4 documentation
        glm::vec4 notInRangeValueVec4
            [[codegen::notinrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // notInRangeValueVec4Optional documentation
        std::optional<glm::vec4> notInRangeValueVec4Optional
            [[codegen::notinrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // notInRangeValueVec4Vector documentation
        std::vector<glm::vec4> notInRangeValueVec4Vector
            [[codegen::notinrange(glm::vec4(1.f), glm::vec4(2.f))]];

        // lessValueVec4 documentation
        glm::vec4 lessValueVec4 [[codegen::less(glm::vec4(1.f))]];

        // lessValueVec4Optional documentation
        std::optional<glm::vec4> lessValueVec4Optional [[codegen::less(glm::vec4(1.f))]];

        // lessValueVec4Vector documentation
        std::vector<glm::vec4> lessValueVec4Vector [[codegen::less(glm::vec4(1.f))]];

        // lessEqualValueVec4 documentation
        glm::vec4 lessEqualValueVec4 [[codegen::lessequal(glm::vec4(1.f))]];

        // lessEqualValueVec4Optional documentation
        std::optional<glm::vec4> lessEqualValueVec4Optional
            [[codegen::lessequal(glm::vec4(1.f))]];

        // lessEqualValueVec4Vector documentation
        std::vector<glm::vec4> lessEqualValueVec4Vector
            [[codegen::lessequal(glm::vec4(1.f))]];

        // greaterValueVec4 documentation
        glm::vec4 greaterValueVec4 [[codegen::greater(glm::vec4(1.f))]];

        // greaterValueVec4Optional documentation
        std::optional<glm::vec4> greaterValueVec4Optional
            [[codegen::greater(glm::vec4(1.f))]];

        // greaterValueVec4Vector documentation
        std::vector<glm::vec4> greaterValueVec4Vector
            [[codegen::greater(glm::vec4(1.f))]];

        // greaterEqualValueVec4 documentation
        glm::vec4 greaterEqualValueVec4 [[codegen::greaterequal(glm::vec4(1.f))]];

        // greaterEqualValueVec4Optional documentation
        std::optional<glm::vec4> greaterEqualValueVec4Optional
            [[codegen::greaterequal(glm::vec4(1.f))]];

        // greaterEqualValueVec4Vector documentation
        std::vector<glm::vec4> greaterEqualValueVec4Vector
            [[codegen::greaterequal(glm::vec4(1.f))]];

        // unequalValueVec4 documentation
        glm::vec4 unequalValueVec4 [[codegen::unequal(glm::vec4(1.f))]];

        // unequalValueVec4Optional documentation
        std::optional<glm::vec4> unequalValueVec4Optional
            [[codegen::unequal(glm::vec4(1.f))]];

        // unequalValueVec4Vector documentation
        std::vector<glm::vec4> unequalValueVec4Vector
            [[codegen::unequal(glm::vec4(1.f))]];
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
        CHECK(var->name == "inRangeValueVec4");
        CHECK(var->key == "\"InRangeValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "inRangeValueVec4 documentation");
        CHECK(var->attributes.inrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "inRangeValueVec4Optional");
        CHECK(var->key == "\"InRangeValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "inRangeValueVec4Optional documentation");
        CHECK(var->attributes.inrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "inRangeValueVec4Vector");
        CHECK(var->key == "\"InRangeValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "inRangeValueVec4Vector documentation");
        CHECK(var->attributes.inrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "notInRangeValueVec4");
        CHECK(var->key == "\"NotInRangeValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "notInRangeValueVec4 documentation");
        CHECK(var->attributes.notinrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "notInRangeValueVec4Optional");
        CHECK(var->key == "\"NotInRangeValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "notInRangeValueVec4Optional documentation");
        CHECK(var->attributes.notinrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "notInRangeValueVec4Vector");
        CHECK(var->key == "\"NotInRangeValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "notInRangeValueVec4Vector documentation");
        CHECK(var->attributes.notinrange == "glm::vec4(1.f), glm::vec4(2.f)");

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
        CHECK(var->name == "lessValueVec4");
        CHECK(var->key == "\"LessValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "lessValueVec4 documentation");
        CHECK(var->attributes.less == "glm::vec4(1.f)");

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
        CHECK(var->name == "lessValueVec4Optional");
        CHECK(var->key == "\"LessValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "lessValueVec4Optional documentation");
        CHECK(var->attributes.less == "glm::vec4(1.f)");

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
        CHECK(var->name == "lessValueVec4Vector");
        CHECK(var->key == "\"LessValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "lessValueVec4Vector documentation");
        CHECK(var->attributes.less == "glm::vec4(1.f)");

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
        CHECK(var->name == "lessEqualValueVec4");
        CHECK(var->key == "\"LessEqualValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "lessEqualValueVec4 documentation");
        CHECK(var->attributes.lessequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "lessEqualValueVec4Optional");
        CHECK(var->key == "\"LessEqualValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "lessEqualValueVec4Optional documentation");
        CHECK(var->attributes.lessequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "lessEqualValueVec4Vector");
        CHECK(var->key == "\"LessEqualValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "lessEqualValueVec4Vector documentation");
        CHECK(var->attributes.lessequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterValueVec4");
        CHECK(var->key == "\"GreaterValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "greaterValueVec4 documentation");
        CHECK(var->attributes.greater == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterValueVec4Optional");
        CHECK(var->key == "\"GreaterValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "greaterValueVec4Optional documentation");
        CHECK(var->attributes.greater == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterValueVec4Vector");
        CHECK(var->key == "\"GreaterValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "greaterValueVec4Vector documentation");
        CHECK(var->attributes.greater == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec4");
        CHECK(var->key == "\"GreaterEqualValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "greaterEqualValueVec4 documentation");
        CHECK(var->attributes.greaterequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec4Optional");
        CHECK(var->key == "\"GreaterEqualValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "greaterEqualValueVec4Optional documentation");
        CHECK(var->attributes.greaterequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "greaterEqualValueVec4Vector");
        CHECK(var->key == "\"GreaterEqualValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "greaterEqualValueVec4Vector documentation");
        CHECK(var->attributes.greaterequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "unequalValueVec4");
        CHECK(var->key == "\"UnequalValueVec4\"");
        CHECK(generateTypename(var->type) == "glm::vec4");
        CHECK(var->comment == "unequalValueVec4 documentation");
        CHECK(var->attributes.unequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "unequalValueVec4Optional");
        CHECK(var->key == "\"UnequalValueVec4Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::vec4>");
        CHECK(var->comment == "unequalValueVec4Optional documentation");
        CHECK(var->attributes.unequal == "glm::vec4(1.f)");

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
        CHECK(var->name == "unequalValueVec4Vector");
        CHECK(var->key == "\"UnequalValueVec4Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::vec4>");
        CHECK(var->comment == "unequalValueVec4Vector documentation");
        CHECK(var->attributes.unequal == "glm::vec4(1.f)");

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
