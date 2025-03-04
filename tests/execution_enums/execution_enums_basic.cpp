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

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <ghoul/misc/dictionary.h>
#include <optional>
#include <variant>
#include <vector>

namespace {
    enum class [[codegen::stringify()]] Enum1 {
        Value1,
        value2,
        Value3
    };
#include "execution_enums_basic_codegen.cpp"
} // namespace

TEST_CASE("Execution/Enums/Basic:  From String", "[Execution][Enums]") {
    Enum1 v1 = codegen::fromString<Enum1>("Value1");
    CHECK(v1 == Enum1::Value1);
    Enum1 v2 = codegen::fromString<Enum1>("value2");
    CHECK(v2 == Enum1::value2);
    Enum1 v3 = codegen::fromString<Enum1>("Value3");
    CHECK(v3 == Enum1::Value3);
}

TEST_CASE("Execution/Enums/Basic:  To String", "[Execution][Enums]") {
    std::string_view sv1 = codegen::toString(Enum1::Value1);
    CHECK(sv1 == "Value1");
    std::string_view sv2 = codegen::toString(Enum1::value2);
    CHECK(sv2 == "value2");
    std::string_view sv3 = codegen::toString(Enum1::Value3);
    CHECK(sv3 == "Value3");
}
