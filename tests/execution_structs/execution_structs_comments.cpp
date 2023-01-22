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

#include "catch2/catch.hpp"

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <ghoul/misc/dictionary.h>
#include <optional>
#include <variant>
#include <vector>

namespace {
    std::string A = "A";
    std::string Long = "Long";
    std::string Of = "Of";
    std::string Variables = "Variables";
    std::string That = "That";
    std::string Will = "Will";
    std::string Cover = "Cover";
    std::string And = "And";
    std::string Span = "Span";
    std::string Multiple = "Multiple";
    std::string Lines = "Lines";
    std::string With = "With";
    std::string Weird = "Weird";
    std::string Indentations = "Indentations";

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
#include "execution_structs_comments_codegen.cpp"
} // namespace

TEST_CASE("Execution/Structs/Comments") {
    using namespace openspace::documentation;

    Documentation d = codegen::doc<Parameters>("abc");
    REQUIRE(d.entries.size() == 9);
    CHECK(d.entries[0].documentation == "multi line commenting");
    CHECK(d.entries[1].documentation == "multi line simple variable def");
    CHECK(d.entries[2].documentation == "multi line commenting and multi line variable def");
    CHECK(d.entries[3].documentation == "misaligned commenting all over the place");
    CHECK(d.entries[4].documentation == "multiline comment with attribute");
    CHECK(d.entries[5].documentation.empty());
    CHECK(d.entries[6].documentation.empty());
    CHECK(d.entries[7].documentation == "newLine2Annotation documentation");
    CHECK(d.entries[8].documentation == "This value has a \" in the comment which might cause it to break?");
}
