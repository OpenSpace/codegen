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

TEST_CASE("Parsing/Structs/Variant:  Variant") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::variant<int, float> a;

    // b comment
    std::variant<bool, std::string, glm::ivec2, glm::mat3x4> b;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    CHECK(code.luaWrapperFunctions.size() == 0);
    Struct* s = code.structs.front();
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

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variant:  Optional Variant") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::optional<std::variant<bool, int>> ov;
})";

    Code code = parse(Source);
    CHECK(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 1);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "ov");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<bool, int>>");
        CHECK(var->comment == "a comment");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variant:  Multiple instances variant") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
    std::variant<int, float> a;
    std::variant<float, int> b;
    std::variant<int, float> c;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.structs.front()->variables.size() == 3);
    std::string r = generateResult(code);
    CHECK(!r.empty());
}
