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

namespace CM = Catch::Matchers;

TEST_CASE("Unsupported Attributes: double annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector double annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional double annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: double inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector double inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional double inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: double notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector double notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional double notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: double reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: vector double reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: optional double reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: double color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: vector double color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: optional double color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: double directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
double v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: vector double directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<double> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: optional double directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<double> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'double' does not support attribute 'directory'")
    );
}
