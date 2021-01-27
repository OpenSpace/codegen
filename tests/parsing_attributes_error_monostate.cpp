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

namespace CM = Catch::Matchers;

TEST_CASE("Unsupported Attributes: std::monostate annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::inlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::inlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::inlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::notinlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::notinlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::notinlist(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: std::monostate notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::monostate notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::monostate> v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::monostate notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::monostate> v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::monostate' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Missing Attribute: monostate reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::monostate v;
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("A monostate must have a 'reference' attribute")
    );
}
