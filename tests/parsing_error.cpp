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

TEST_CASE("Parsing Error: Missing description", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    // [[codegen::verbatim]]
    int error;
};
)";
    Struct* s = parseRootStruct(Source);
    CHECK_THROWS_MATCHES(
        generateResult(s),
        ParsingError,
        Catch::Matchers::Contains("Malformed codegen::verbatim")
    );
}

TEST_CASE("Parsing Error: Illegal \" in description", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    // description " with character
    int error;
};
)";
    Struct* s = parseRootStruct(Source);
    CHECK_THROWS_MATCHES(
        generateResult(s),
        ParsingError,
        Catch::Matchers::Contains("Discovered unallowed unescaped")
    );
}

TEST_CASE("Parsing Error: Missing variant closing", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    std::variant<int, float error;
};
)";
    CHECK_THROWS_MATCHES(
        [&](){
            Struct* s = parseRootStruct(Source);
            std::string r = generateResult(s);
        }(),
        ParsingError,
        Catch::Matchers::Contains("Unbalanced number of < > brackets")
    );
}

TEST_CASE("Parsing Error: Unknown type", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    std::list<int> error;
};
)";
    Struct* s = parseRootStruct(Source);
    CHECK_THROWS_MATCHES(
        generateResult(s),
        ParsingError,
        Catch::Matchers::Contains("Type detected that codegen doesn't know how to handle")
    );
}

TEST_CASE("Parsing Error: Missing struct", "[parsing_error]") {
    constexpr const char Source[] = R"(
Type [[codegen::Dictionary(Error)]] Parameters {
    std::string str;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Could not find 'struct' before '[[codegen")
    );
}

TEST_CASE("Parsing Error: Unterminated attribute", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val [[codegen::inrange(1.0, 2.0]];
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing Error: Unknown attribute (variable)", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val [[codegen::unknown_key(parameter)]];
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        SpecificationError,
        Catch::Matchers::Contains("Unknown attribute 'unknown_key' in attribute")
    );
}

TEST_CASE("Parsing Error: Unterminated dictionary", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing Error: Unknown attribute (struct)", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    struct [[codegen::unknown_key()]] P {
    };
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        SpecificationError,
        Catch::Matchers::Contains("Unknown attribute 'unknown_key' in struct definition")
    );
}

TEST_CASE("Parsing Error: Unknown attribute (enum)", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    enum class E {
        Value [[codegen::unknown_key()]],
        Value2
    };
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        SpecificationError,
        Catch::Matchers::Contains("Unrecognized attribute 'unknown_key' found")
    );
}

TEST_CASE("Parsing Error: Empty root name 1", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary()]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        SpecificationError,
        Catch::Matchers::Contains("No name specified for root struct")
    );
}

TEST_CASE("Parsing Error: Empty root name 2", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing Error: Missing closing }", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val;
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Could not find closing } of root struct")
    );
}

TEST_CASE("Parsing Error: Wrong order", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct Parameters [[codegen::Dictionary(abc)]] {
    int value;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        SpecificationError,
        Catch::Matchers::Contains(
            "Only 'struct' can appear directly before [[codegen::Dictionary"
        )
    );
}

TEST_CASE("Parsing Error: Block comments", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(abc)]] Parameters {
    /* evil block comment */
    int value;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains("Block comments are not allowed")
    );
}

// Let's see if we can live without this exception
//TEST_CASE("Parsing Error: Illegal characters", "[parsing_error]") {
//    constexpr const char Source[] = R"(
//struct [[codegen::Dictionary(abc)]] Parameters {
//    // smörgåstårta
//    int value;
//};
//)";
//
//    CHECK_THROWS_MATCHES(
//        parseRootStruct(Source),
//        ParsingError,
//        Catch::Matchers::Contains("Illegal character")
//    );
//}

TEST_CASE("Parsing Error: Duplicate root struct", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(S1)]] Parameters {
    struct [[codegen::Dictionary(S2)]] Sub {
        int value;
    };
    Sub s;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains(
            "We currently only support one struct per file annotated"
        )
    );
}

TEST_CASE("Parsing Error: Old-style enum", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(abc)]] Parameters {
    enum ABC {
        value1,
        value2
    };
    ABC abc;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains(
            "Old-style 'enum' not supported. Use 'enum class' instead"
        )
    );
}

TEST_CASE("Parsing Error: Multiple structs", "[parsing_error]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(abc)]] Parameters1 {
    int value1;
};

struct [[codegen::Dictionary(def)]] Parameters2 {
    int value2;
};
)";

    CHECK_THROWS_MATCHES(
        parseRootStruct(Source),
        ParsingError,
        Catch::Matchers::Contains(
            "We currently only support one struct per file annotated"
        )
    );
}
