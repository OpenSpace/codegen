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

TEST_CASE("Parsing/LuaWrapper/No Comments", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void foo() {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);
}


TEST_CASE("Parsing/LuaWrapper/Direct Comments", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    /*
     * Some example documentation
     * that covers a few lines.
     * And another one for good measure
     */
    [[codegen::wraplua]] void foo() {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "Some example documentation that covers a few lines. And another one for good measure");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);
}
