/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2025                                                               *
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

TEST_CASE("Parsing Attribute: Multiple Attributes (success)", "[structs][parsing]") {
    constexpr std::string_view Source = R"(
    struct [[codegen::Dictionary(MultipleAttributes)]] Parameters {
        // keyInRangeValue documentation
        float keyInRangeValue [[codegen::key(KeyKey), codegen::inrange(-2, 2)]];

        // keyInRangeValueOptional documentation
        std::optional<float> keyValueInRangeOptional [[codegen::key(KeyKeyOptional), codegen::inrange(-2, 3)]];
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s->variables.size() == 2);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "keyInRangeValue");
        CHECK(var->key == "KeyKey");
        CHECK(generateTypename(var->type) == "float");
        CHECK(var->comment == "keyInRangeValue documentation");
        CHECK(var->attributes.key == "KeyKey");
        CHECK(var->attributes.inrange == "-2, 2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
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
        CHECK(!var->attributes.isPrivate);
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "keyValueInRangeOptional");
        CHECK(var->key == "KeyKeyOptional");
        CHECK(generateTypename(var->type) == "std::optional<float>");
        CHECK(var->comment == "keyInRangeValueOptional documentation");
        CHECK(var->attributes.key == "KeyKeyOptional");
        CHECK(var->attributes.inrange == "-2, 3");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
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
        CHECK(!var->attributes.isPrivate);
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing Attribute: Struct Attribute empty noexhaustive", "[structs][parsing]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive()]] Parameters {
    int value;
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(generateTypename(s->variables[0]->type) == "int");
    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing Attribute: Struct Attribute true noexhaustive", "[structs][parsing]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive(true)]] Parameters {
    int value;
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(generateTypename(s->variables[0]->type) == "int");
    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing Attribute: Struct Attribute false noexhaustive", "[structs][parsing]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive(false)]] Parameters {
    int value;
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(!s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(generateTypename(s->variables[0]->type) == "int");
    const std::string r = generateResult(code);
    CHECK(!r.empty());
}
