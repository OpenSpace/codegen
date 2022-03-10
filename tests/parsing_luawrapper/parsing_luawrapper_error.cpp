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

namespace CM = Catch::Matchers;

TEST_CASE("Parsing/LuaWrapper/Error:  No variable name provided") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(int) {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("Parameter 0 of function 'foo' has no name")
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Unhandled return type") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] std::chrono::time_point foo() {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains(
            "Illegal type 'std::chrono::time_point' for return value of function 'foo'"
        )
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Unhandled argument type first argument") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(std::list<int> abc) {
    }
)";
    
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains(
            "Illegal type 'std::list<int>' for argument 'abc' value of function 'foo'"
        )
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Unhandled argument type second argument") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(float abc, std::list<int> def) {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains(
            "Illegal type 'std::list<int>' for argument 'def' value of function 'foo'"
        )
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Reference type for argument") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(float& abc) {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains("Illegal reference type found: float&")
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Const reference type for argument") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(const float& abc) {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains("Illegal reference type 'const float&' found in function 'foo'")
    );
}

TEST_CASE("Parsing/LuaWrapper/Error:  Const pointer type for argument") {
    constexpr const char S[] = R"(
    [[codegen::luawrap]] void foo(const float* abc) {
    }
)";

    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains("Illegal pointer type 'const float*' found in function 'foo'")
    );
}
