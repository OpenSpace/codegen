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

TEST_CASE("Parsing/Enums/Keys:  Keys", "[Parsing][Enums]") {
    constexpr std::string_view Source = R"(
    enum class [[codegen::stringify()]] Enum1 {
        Value1 [[codegen::key("KeyForValue1")]],
        value2,
        Value3 [[codegen::key("KeyForValue3")]]
    };
)";

    Code code = parse(Source);
    CHECK(code.structs.empty());
    REQUIRE(code.enums.size() == 1);
    Enum* e = code.enums.front();
    REQUIRE(e);

    CHECK(e->parent == nullptr);
    CHECK(e->attributes.mappedTo.empty());
    CHECK(e->attributes.stringify);
    CHECK(!e->attributes.arrayify);
    REQUIRE(e->elements.size() == 3);
    {
        EnumElement* ee = e->elements[0];
        REQUIRE(ee);
        CHECK(ee->name == "Value1");
        CHECK(ee->attributes.key == "\"KeyForValue1\"");
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
        CHECK(ee->attributes.key == "\"KeyForValue3\"");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
