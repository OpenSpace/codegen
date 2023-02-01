/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2023                                                               *
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

TEST_CASE("Parsing: Comments") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Comments)]] Parameters {
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

    std::string newLineAnnotation
        [[codegen::annotation(
            "some-annotation-that-is-very-long"
        )]];

    // newLine2Annotation documentation
    std::string newLine2Annotation [[codegen::annotation("A long string that starts here"
        "and covers"
        "multiple lines breaks, because someone really has a"
        "lot to say"
    )]];

    // This value has a " in the comment which might cause it to break?
    std::vector<std::string> quoteInComment;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.size() == 0);
    CHECK(code.luaWrapperFunctions.size() == 0);
    Struct* s = code.structs.front();
    REQUIRE(s);

    REQUIRE(s->variables.size() == 9);
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
    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "newLineAnnotation");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment.empty());
        CHECK(var->attributes.annotation == "\"some-annotation-that-is-very-long\"");
    }
    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "newLine2Annotation");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "newLine2Annotation documentation");
        CHECK(var->attributes.annotation == "\"A long string that starts here and covers multiple lines breaks, because someone really has a lot to say\"");
    }
    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "quoteInComment");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "This value has a \" in the comment which might cause it to break?");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing: Multiple") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(P1)]] Param1 {
    int abc;
};
struct [[codegen::Dictionary(P2)]] Param2 {
    std::string def;
};
struct [[codegen::Dictionary(P3)]] Param3 {
    double ghi;
};
struct [[codegen::Dictionary(P4)]] Param4 {
    ghoul::Dictionary jkl;
};
)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 4);
    REQUIRE(code.enums.size() == 0);

    {
        Struct* s = code.structs[0];
        REQUIRE(s);
        REQUIRE(s->variables.size() == 1);
        CHECK(s->variables[0]->name == "abc");
    }

    {
        Struct* s = code.structs[1];
        REQUIRE(s);
        REQUIRE(s->variables.size() == 1);
        CHECK(s->variables[0]->name == "def");
    }

    {
        Struct* s = code.structs[2];
        REQUIRE(s);
        REQUIRE(s->variables.size() == 1);
        CHECK(s->variables[0]->name == "ghi");
    }

    {
        Struct* s = code.structs[3];
        REQUIRE(s);
        REQUIRE(s->variables.size() == 1);
        CHECK(s->variables[0]->name == "jkl");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
