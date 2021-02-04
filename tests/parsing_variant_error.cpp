/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021                                                                    *
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

TEST_CASE("Variant Error: Multiple Vectors", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::variant<std::vector<int>, std::vector<float>> a;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    REQUIRE(s->variables.size() == 1);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "a");
        CHECK(
            generateTypename(var->type) ==
            "std::variant<std::vector<int>, std::vector<float>>"
        );
        CHECK(var->comment == "a comment");
    }

    CHECK_THROWS_MATCHES(
        generateResult(s),
        CodegenError, Catch::Matchers::Contains("can't have a variant containing multiple vector types")
    );
}
