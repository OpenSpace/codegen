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

TEST_CASE("Unsupported Attributes: std::string annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::annotation(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::inrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::less(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::lessequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::greater(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::greaterequal(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::notinrange(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::reference(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::reference(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::reference(1)]];
};)";
    REQUIRE_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        SpecificationError,
        CM::Contains("'std::string' does not support attribute 'reference'")
    );
}