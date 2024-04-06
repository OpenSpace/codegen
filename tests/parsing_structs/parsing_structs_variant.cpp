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

TEST_CASE("Parsing/Structs/Variant:  Variant", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::variant<int, float> a;

    // b comment
    std::variant<bool, std::string, glm::ivec2, glm::mat3x4> b;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    CHECK(code.luaWrapperFunctions.empty());
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

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variant:  Optional Variant", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(D)]] P {
    // a comment
    std::optional<std::variant<bool, int>> ov;
})";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
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

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variant:  Multiple instances variant", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(D)]] P {
    std::variant<int, float> a;
    std::variant<float, int> b;
    std::variant<int, float> c;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 3);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "a");
        CHECK(generateTypename(var->type) == "std::variant<int, float>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "b");
        CHECK(generateTypename(var->type) == "std::variant<float, int>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "c");
        CHECK(generateTypename(var->type) == "std::variant<int, float>");
        CHECK(var->comment.empty());
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/Structs/Variant:  Types and vectors", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(D)]] P {
    std::variant<std::string, std::vector<std::string>> string;
    std::variant<std::filesystem::path, std::vector<std::filesystem::path>> path;
    std::variant<int, std::vector<int>> integer;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 3);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "string");
        CHECK(generateTypename(var->type) == "std::variant<std::string, std::vector<std::string>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "path");
        CHECK(generateTypename(var->type) == "std::variant<std::filesystem::path, std::vector<std::filesystem::path>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "integer");
        CHECK(generateTypename(var->type) == "std::variant<int, std::vector<int>>");
        CHECK(var->comment.empty());
    }
}

TEST_CASE("Parsing/Structs/Variant:  Optional types and vectors", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(D)]] P {
    std::optional<std::variant<std::string, std::vector<std::string>>> string;
    std::optional<std::variant<std::filesystem::path, std::vector<std::filesystem::path>>> path;
    std::optional<std::variant<int, std::vector<int>>> integer;

    std::optional<
        std::variant<std::string, std::vector<std::string>>
    > stringWithLineBreak;
    std::optional<
        std::variant<std::filesystem::path, std::vector<std::filesystem::path>>
    > pathWithLineBreak;
    std::optional<
        std::variant<int, std::vector<int>>
    > integerWithLineBreak;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 6);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "string");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<std::string, std::vector<std::string>>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "path");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<std::filesystem::path, std::vector<std::filesystem::path>>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "integer");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<int, std::vector<int>>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "stringWithLineBreak");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<std::string, std::vector<std::string>>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "pathWithLineBreak");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<std::filesystem::path, std::vector<std::filesystem::path>>>");
        CHECK(var->comment.empty());
    }
    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "integerWithLineBreak");
        CHECK(generateTypename(var->type) == "std::optional<std::variant<int, std::vector<int>>>");
        CHECK(var->comment.empty());
    }
}
