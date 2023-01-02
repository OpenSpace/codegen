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

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Error:  Extra \" in root name") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary("Wrong")]] Parameters {
    int dummy;
}
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Root struct name must not be enclosed")
    );
}

TEST_CASE("Parsing/Structs/Error:  Missing description") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    // [[codegen::verbatim]]
    int error;
};
)";
    Code code = parse(Source);
    CHECK_THROWS_MATCHES(
        generateResult(code),
        CodegenError, Catch::Matchers::Contains("Malformed codegen::verbatim")
    );
}

TEST_CASE("Parsing/Structs/Error:  Missing space") {
    constexpr const char Source[] = R"(struct [[codegen::Dictionary(Name)]] Parameters{
};)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Missing space or struct name before")
    );
}

TEST_CASE("Parsing/Structs/Error:  Illegal \" in description") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    // description " with character
    int error;
};
)";
    Code code = parse(Source);
    CHECK_THROWS_MATCHES(
        generateResult(code),
        CodegenError, Catch::Matchers::Contains("Discovered unallowed unescaped")
    );
}

TEST_CASE("Parsing/Structs/Error:  Missing variant closing") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    std::variant<int, float error;
};
)";
    CHECK_THROWS_MATCHES(
        [&](){
            Code code = parse(Source);
            std::string r = generateResult(code);
        }(),
        CodegenError, Catch::Matchers::Contains("Unbalanced number of < > brackets")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unknown type") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    std::list<int> error;
};
)";
    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Type detected that codegen doesn't know how to handle")
    );
}

TEST_CASE("Parsing/Structs/Error:  Missing struct") {
    constexpr const char Source[] = R"(
Type [[codegen::Dictionary(Error)]] Parameters {
    std::string str;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Could not find 'struct' before '[[codegen")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unterminated attribute") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val [[codegen::inrange(1.0, 2.0]];
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unknown attribute (variable)") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val [[codegen::unknown_key(parameter)]];
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Unknown attribute 'unknown_key' in attribute")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unterminated dictionary") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unterminated attribute brackets") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    enum class A {
        Value1 [[codegen::key("KeyA"),
        Value2
    };
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Unterminated attribute brackets")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unknown attribute (struct)") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    struct [[codegen::unknown_key()]] P {
    };
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Unknown attribute 'unknown_key' in struct definition")
    );
}

TEST_CASE("Parsing/Structs/Error:  Unknown attribute (enum)") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    enum class E {
        Value [[codegen::unknown_key()]],
        Value2
    };
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Unrecognized attribute 'unknown_key' found")
    );
}

TEST_CASE("Parsing/Structs/Error:  Empty root name 1") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary()]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("No name specified for root struct")
    );
}

TEST_CASE("Parsing/Structs/Error:  Empty root name 2") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary]] Parameters {
    int val;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Attribute parameter has unterminated parameter list")
    );
}

TEST_CASE("Parsing/Structs/Error:  Missing closing }") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Error)]] Parameters {
    int val;
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Could not find closing } of root struct")
    );
}

TEST_CASE("Parsing/Structs/Error:  Wrong order") {
    constexpr const char Source[] = R"(
struct Parameters [[codegen::Dictionary(abc)]] {
    int value;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Only 'struct' can appear directly before [[codegen::Dictionary")
    );
}

TEST_CASE("Parsing/Structs/Error:  Block comments") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(abc)]] Parameters {
    /* evil block comment */
    int value;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Block comments are not allowed")
    );
}

TEST_CASE("Parsing/Structs/Error:  Duplicate root struct") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(S1)]] Parameters {
    struct [[codegen::Dictionary(S2)]] Sub {
        int value;
    };
    Sub s;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Found nested structs annotated with the Dictionary attribute.")
    );
}

TEST_CASE("Parsing/Structs/Error:  Old-style enum") {
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
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Old-style 'enum' not supported. Use 'enum class' instead")
    );
}

TEST_CASE("Parsing/Structs/Error:  Default argument in variable") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(D)]] P {
   int value1;
   float v2 = 2.f;
};
)";

    CHECK_THROWS_MATCHES(
        parse(Source),
        CodegenError, Catch::Matchers::Contains("Found '=' in variable definition")
    );
}

TEST_CASE("Parsing/Structs/Error:  Misshapen boolean value") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::color(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, Catch::Matchers::Contains("Boolean attribute needs to be")
    );
}
