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

TEST_CASE("Unsupported Attributes: int annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector int annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional int annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: int inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector int inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional int inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: int notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int notinlist [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector int notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional int notinlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: int reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: vector int reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: optional int reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::reference(1)]];
};)";
CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: int color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: vector int color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: optional int color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: int directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
int v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: vector int directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<int> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: optional int directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<int> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'int' does not support attribute 'directory'")
    );
}
