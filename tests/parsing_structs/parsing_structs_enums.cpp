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

TEST_CASE("Parsing: Enums", "[structs][parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Multiline)]] Parameters {
    // enum A documentation
    enum class A {
        Value1,
        value2,
        Value3
    };
    // variable enumAValue documentation
    A enumAValue;

    // enum B documentation
    enum class B {
        Value1,
        value2,
        Value3
    };
    // variable enumBValue documentation
    std::optional<B> enumBValue;

    // enum C documentation
    enum class C {
        Value1,
        value2,
        Value3
    };
    // variable enumCValue documentation
    std::vector<C> enumCValue;

    enum class D {
        VeryLongValueThatIsSoLongWithAnEvenLongerKeyWhichNeedsToBe
            [[codegen::key("On a second line or else one line would be too long")]],
        ValueB,
        SecondVeryLongValueThatWillCheckIfWeDetectPropertyThatWeHave
            [[codegen::key("a continuation line as the last element of the enum")]]
    };
    // variable enumDValue documentation
    D enumDValue;
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    Struct* s = code.structs.front();

    REQUIRE(s->children.size() == 4);
    {
        StackElement* se = s->children[0];
        REQUIRE(se);
        REQUIRE(se->type == StackElement::Type::Enum);
        Enum* e = static_cast<Enum*>(se);
        CHECK(e->name == "A");
        CHECK(e->mappedTo.empty());
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "Value1");
        CHECK(e->elements[1]->name == "value2");
        CHECK(e->elements[2]->name == "Value3");
    }

    {
        StackElement* se = s->children[1];
        REQUIRE(se);
        REQUIRE(se->type == StackElement::Type::Enum);
        Enum* e = static_cast<Enum*>(se);
        CHECK(e->name == "B");
        CHECK(e->mappedTo.empty());
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "Value1");
        CHECK(e->elements[1]->name == "value2");
        CHECK(e->elements[2]->name == "Value3");
    }

    {
        StackElement* se = s->children[2];
        REQUIRE(se);
        REQUIRE(se->type == StackElement::Type::Enum);
        Enum* e = static_cast<Enum*>(se);
        CHECK(e->name == "C");
        CHECK(e->mappedTo.empty());
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "Value1");
        CHECK(e->elements[1]->name == "value2");
        CHECK(e->elements[2]->name == "Value3");
    }

    {
        StackElement* se = s->children[3];
        REQUIRE(se);
        REQUIRE(se->type == StackElement::Type::Enum);
        Enum* e = static_cast<Enum*>(se);
        CHECK(e->name == "D");
        CHECK(e->mappedTo.empty());
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "VeryLongValueThatIsSoLongWithAnEvenLongerKeyWhichNeedsToBe");
        CHECK(e->elements[1]->name == "ValueB");
        CHECK(e->elements[2]->name == "SecondVeryLongValueThatWillCheckIfWeDetectPropertyThatWeHave");
    }

}
