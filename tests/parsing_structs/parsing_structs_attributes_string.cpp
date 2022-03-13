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

TEST_CASE("Parsing/Structs/Attributes/String") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // inListValue1 documentation
        std::string inListValue1 [[codegen::inlist("A", "B", "C")]];

        // inListValue1Optional documentation
        std::optional<std::string> inListValue1Optional
            [[codegen::inlist("A", "B", "C")]];

        // inListValue1Vector documentation
        std::vector<std::string> inListValue1Vector [[codegen::inlist("A", "B", "C")]];

        // inListValue2 documentation
        std::string inListValue2 [[codegen::inlist(List)]];

        // inListValue2Optional documentation
        std::optional<std::string> inListValue2Optional [[codegen::inlist(List)]];

        // inListValue2Vector documentation
        std::vector<std::string> inListValue2Vector [[codegen::inlist(List)]];

        // unequalValueString documentation
        std::string unequalValueString [[codegen::unequal("abcdef")]];

        // unequalValueStringOptional documentation
        std::optional<std::string> unequalValueStringOptional
            [[codegen::unequal("abcdef")]];

        // unequalValueStringVector documentation
        std::vector<std::string> unequalValueStringVector [[codegen::unequal("abcdef")]];

        // string not empty value documentation
        std::string notEmptyString [[codegen::notempty()]];

        // string not empty optional value documentation
        std::optional<std::string> notEmptyStringOptional [[codegen::notempty()]];

        // string not empty vector value documentation
        std::vector<std::string> notEmptyStringVector [[codegen::notempty()]];

        // string not empty optional vector value documentation
        std::optional<std::vector<std::string>> notEmptyStringOptionalVector
            [[codegen::notempty()]];

        // string not not empty value documentation
        std::string notNotEmptyString [[codegen::notempty(false)]];

        // string not not empty optional value documentation
        std::optional<std::string> notNotEmptyStringOptional [[codegen::notempty(false)]];

        // string not not empty vector value documentation
        std::vector<std::string> notNotEmptyStringVector [[codegen::notempty(false)]];

        // string not not empty optional vector value documentation
        std::optional<std::vector<std::string>> notNotEmptyStringOptionalVector
            [[codegen::notempty(false)]];

        // string yes not empty value documentation
        std::string yesNotEmptyString [[codegen::notempty(true)]];

        // string yes not empty optional value documentation
        std::optional<std::string> yesNotEmptyStringOptional [[codegen::notempty(true)]];

        // string yes not empty vector value documentation
        std::vector<std::string> yesNotEmptyStringVector [[codegen::notempty(true)]];

        // string yes not empty optional vector value documentation
        std::optional<std::vector<std::string>> yesNotEmptyStringOptionalVector
            [[codegen::notempty(true)]];

        // dateTime value documentation
        std::string dateTimeValue [[codegen::datetime()]];

        // optional dateTime value documentation
        std::optional<std::string> optionalDateTimeValue [[codegen::datetime()]];

        // vector dateTime value documentation
        std::vector<std::string> vectorDateTimeValue [[codegen::datetime()]];

        // optional vector dateTime value documentation
        std::optional<std::vector<std::string>> optionalVectorDateTimeValue
            [[codegen::datetime()]];
})";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    CHECK(code.luaWrapperFunctions.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 25);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "inListValue1");
        CHECK(var->key == "\"InListValue1\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "inListValue1 documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Optional");
        CHECK(var->key == "\"InListValue1Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "inListValue1Optional documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Vector");
        CHECK(var->key == "\"InListValue1Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "inListValue1Vector documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "inListValue2");
        CHECK(var->key == "\"InListValue2\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "inListValue2 documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Optional");
        CHECK(var->key == "\"InListValue2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "inListValue2Optional documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Vector");
        CHECK(var->key == "\"InListValue2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "inListValue2Vector documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
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
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "unequalValueString");
        CHECK(var->key == "\"UnequalValueString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "unequalValueString documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

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
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringOptional");
        CHECK(var->key == "\"UnequalValueStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "unequalValueStringOptional documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

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
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringVector");
        CHECK(var->key == "\"UnequalValueStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "unequalValueStringVector documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

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
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "notEmptyString");
        CHECK(var->key == "\"NotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string not empty value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringOptional");
        CHECK(var->key == "\"NotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string not empty optional value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringVector");
        CHECK(var->key == "\"NotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string not empty vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringOptionalVector");
        CHECK(var->key == "\"NotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string not empty optional vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyString");
        CHECK(var->key == "\"NotNotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string not not empty value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringOptional");
        CHECK(var->key == "\"NotNotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string not not empty optional value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringVector");
        CHECK(var->key == "\"NotNotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string not not empty vector value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringOptionalVector");
        CHECK(var->key == "\"NotNotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string not not empty optional vector value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyString");
        CHECK(var->key == "\"YesNotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string yes not empty value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringOptional");
        CHECK(var->key == "\"YesNotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string yes not empty optional value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringVector");
        CHECK(var->key == "\"YesNotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string yes not empty vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringOptionalVector");
        CHECK(var->key == "\"YesNotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string yes not empty optional vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(var->attributes.unequal.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "dateTimeValue");
        CHECK(var->key == "\"DateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "optionalDateTimeValue");
        CHECK(var->key == "\"OptionalDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "optional dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "vectorDateTimeValue");
        CHECK(var->key == "\"VectorDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "vector dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorDateTimeValue");
        CHECK(var->key == "\"OptionalVectorDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "optional vector dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
