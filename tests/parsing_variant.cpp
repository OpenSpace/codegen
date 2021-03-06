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

TEST_CASE("Parsing: Variant", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::variant<int, float> a;

    // b comment
    std::variant<bool, std::string, glm::ivec2, glm::mat3x4> b;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    REQUIRE(s->variables.size() == 2);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "a");
        CHECK(generateTypename(var->type) == "std::variant<int, float>");
        CHECK(var->comment == "a comment");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "b");
        CHECK(
            generateTypename(var->type) ==
            "std::variant<bool, std::string, glm::ivec2, glm::mat3x4>"
        );
        CHECK(var->comment == "b comment");
    }
}

TEST_CASE("Parsing: Optional Variant", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::optional<std::variant<bool, int>> ov;
})";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    REQUIRE(s->variables.size() == 1);

    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "ov");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<bool, int>>");
        CHECK(var->comment == "a comment");
    }
}

TEST_CASE("Parsing: Multiple instances variant", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    std::variant<int, float> a;
    std::variant<float, int> b;
    std::variant<int, float> c;
};
)";

    Struct* s = parseRootStruct(Source);
    [[maybe_unused]] std::string res = generateResult(s);
}
