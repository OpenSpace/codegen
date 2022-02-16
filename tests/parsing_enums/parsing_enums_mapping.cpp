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

TEST_CASE("Parsing: Enum Mapping", "[enums][parsing]") {
    constexpr const char Source[] = R"(
    enum class [[codegen::stringify()]] Enum1 {
        Value1,
        value2,
        Value3
    };

    enum class [[codegen::stringify(), codegen::map(Mapped2)]] Enum2 {
        Val4,
        Val5
    };

    enum class [[codegen::map(Mapped3)]] Enum3 {
        Val6
    };
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    REQUIRE(code.enums.size() == 3);

    {
        Enum* e = code.enums[0];
        CHECK(e->parent == nullptr);
        CHECK(e->mappedTo.empty());
        REQUIRE(e->elements.size() == 3);
        {
            EnumElement* ee = e->elements[0];
            REQUIRE(ee);
            CHECK(ee->name == "Value1");
        }
        {
            EnumElement* ee = e->elements[1];
            REQUIRE(ee);
            CHECK(ee->name == "value2");
        }
        {
            EnumElement* ee = e->elements[2];
            REQUIRE(ee);
            CHECK(ee->name == "Value3");
        }
    }

    {
        Enum* e = code.enums[1];
        CHECK(e->parent == nullptr);
        CHECK(e->mappedTo == "Mapped2");
        REQUIRE(e->elements.size() == 2);
        {
            EnumElement* ee = e->elements[0];
            REQUIRE(ee);
            CHECK(ee->name == "Val4");
        }
        {
            EnumElement* ee = e->elements[1];
            REQUIRE(ee);
            CHECK(ee->name == "Val5");
        }
    }

    {
        Enum* e = code.enums[2];
        CHECK(e->parent == nullptr);
        CHECK(e->mappedTo == "Mapped3");
        REQUIRE(e->elements.size() == 1);
        {
            EnumElement* ee = e->elements[0];
            REQUIRE(ee);
            CHECK(ee->name == "Val6");
        }
    }
}