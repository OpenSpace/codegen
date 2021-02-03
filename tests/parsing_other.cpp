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

TEST_CASE("Parsing: Multiline", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Multiline)]] Parameters {
    // multi
    // line
    // commenting
    int multiLineCommenting;

    // multi line simple variable def
    float
    multiLineSimpleVariableDef;

    // multi
    // line
    // commenting
    // and
    // multi line variable def
    std::string
    multiLineCommentAndDef;

    // misaligned
// commenting
        // all over
    // the place
bool misalignedIndent;

    // multiline
    // comment with
    // attribute
    int multiLineCommentAttribute
    [[codegen::inrange(2, 3)]];

    std::string multilineinlist [[codegen::inlist(A, "Very", Long, "List", Of, Variables,
"And", "String Literals", That, Will, Cover,
    And, Span, Multiple,
Lines, With, Weird,
                Indentations)]];
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    REQUIRE(s->variables.size() == 6);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "multiLineCommenting");
        CHECK(generateTypename(var->type) == "int");
        CHECK(var->comment == "multi line commenting");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "multiLineSimpleVariableDef");
        CHECK(generateTypename(var->type) == "float");
        CHECK(var->comment == "multi line simple variable def");
    }
    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "multiLineCommentAndDef");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "multi line commenting and multi line variable def");
    }
    {
        Variable* var = s->variables[3];
        REQUIRE(var);
        CHECK(var->name == "misalignedIndent");
        CHECK(generateTypename(var->type) == "bool");
        CHECK(var->comment == "misaligned commenting all over the place");
    }
    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "multiLineCommentAttribute");
        CHECK(generateTypename(var->type) == "int");
        CHECK(var->comment == "multiline comment with attribute");
        CHECK(var->attributes.inrange == "2, 3");
    }
    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "multilineinlist");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment.empty());
        CHECK(
            var->attributes.inlist ==
            "A, \"Very\", Long, \"List\", Of, Variables, \"And\", \"String Literals\", "
            "That, Will, Cover, And, Span, Multiple, Lines, With, Weird, Indentations"
        );
    }

    std::string r = generateResult(s);
    CHECK(!r.empty());
}
