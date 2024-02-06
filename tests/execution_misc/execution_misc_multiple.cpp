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

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <ghoul/misc/dictionary.h>

namespace {
    struct [[codegen::Dictionary(StructA)]] StructA {
        float test;
    };

    struct [[codegen::Dictionary(StructB)]] StructB {
        int test;
    };

#include "execution_misc_multiple_codegen.cpp"
} // namespace

TEST_CASE("Execution/Misc:  Multiple", "[Execution][Misc]") {
    using namespace openspace::documentation;

    Documentation a = codegen::doc<StructA>("abc");
    REQUIRE(a.entries.size() == 1);
    CHECK(a.entries[0].key == "Test");
    CHECK(a.entries[0].verifier->type() == "Double");

    Documentation b = codegen::doc<StructB>("abc");
    REQUIRE(b.entries.size() == 1);
    CHECK(b.entries[0].key == "Test");
    CHECK(b.entries[0].verifier->type() == "Integer");
}
