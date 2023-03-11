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

#include <catch2/catch_test_macros.hpp>

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Attribute/Dictionary") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // referenceValue documentation
        ghoul::Dictionary referenceValue [[codegen::reference("abc")]];

        // referenceValueOptional documentation
        std::optional<ghoul::Dictionary> referenceValueOptional
            [[codegen::reference("abc")]];

        // referenceValueVector documentation
        std::vector<ghoul::Dictionary> referenceValueVector [[codegen::reference("abc")]];

        // referenceValueOptionalVector documentation
        std::optional<std::vector<ghoul::Dictionary>> referenceValueOptionalVector
            [[codegen::reference("abc")]];

        // referenceValueMap documentation
        std::map<std::string, ghoul::Dictionary> referenceValueMap
            [[codegen::reference("abc")]];

})";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    CHECK(code.luaWrapperFunctions.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 5);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "referenceValue");
        CHECK(var->key == "\"ReferenceValue\"");
        CHECK(generateTypename(var->type) == "ghoul::Dictionary");
        CHECK(var->comment == "referenceValue documentation");
        CHECK(var->attributes.reference == "\"abc\"");

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "referenceValueOptional");
        CHECK(var->key == "\"ReferenceValueOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<ghoul::Dictionary>");
        CHECK(var->comment == "referenceValueOptional documentation");
        CHECK(var->attributes.reference == "\"abc\"");

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "referenceValueVector");
        CHECK(var->key == "\"ReferenceValueVector\"");
        CHECK(generateTypename(var->type) == "std::vector<ghoul::Dictionary>");
        CHECK(var->comment == "referenceValueVector documentation");
        CHECK(var->attributes.reference == "\"abc\"");

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "referenceValueOptionalVector");
        CHECK(var->key == "\"ReferenceValueOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<ghoul::Dictionary>>");
        CHECK(var->comment == "referenceValueOptionalVector documentation");
        CHECK(var->attributes.reference == "\"abc\"");

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "referenceValueMap");
        CHECK(var->key == "\"ReferenceValueMap\"");
        CHECK(generateTypename(var->type) == "std::map<std::string, ghoul::Dictionary>");
        CHECK(var->comment == "referenceValueMap documentation");
        CHECK(var->attributes.reference == "\"abc\"");

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
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isIdentifier);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
