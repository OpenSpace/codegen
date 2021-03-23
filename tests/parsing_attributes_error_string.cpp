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

TEST_CASE("Unsupported Attributes: std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string inrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string less", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string lessequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string greater", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string greaterequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string notinrange", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string reference", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: std::string color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string color", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: std::string directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: vector std::string directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: optional std::string directory", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError, CM::Contains("'std::string' does not support attribute 'directory'")
    );
}

TEST_CASE("Attribute error: std::string annotation inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::annotation("abc"), codegen::inlist({"abc", "def" })]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string annotation inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::annotation("abc"), codegen::inlist({"abc", "def" })]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string annotation inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::annotation("abc"), codegen::inlist({"abc", "def" })]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string annotation inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::annotation("abc"), codegen::inlist({"abc", "def" })]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string annotation unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::annotation("abc"), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string annotation unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::annotation("abc"), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string annotation unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::annotation("abc"), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string annotation unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::annotation("abc"), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the annotation attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string annotation notempty", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::annotation("abc"), codegen::notempty()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string annotation notempty", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::annotation("abc"), codegen::notempty()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string annotation notempty", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::annotation("abc"), codegen::notempty()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string annotation notempty", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::annotation("abc"), codegen::notempty()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string notempty inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notempty(), codegen::inlist({"abc", "def"})]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string notempty inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::notempty(), codegen::inlist({"abc", "def"})]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string notempty inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::notempty(), codegen::inlist({"abc", "def"})]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string notempty inlist", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::notempty(), codegen::inlist({"abc", "def"})]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string notempty unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notempty(), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string notempty unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::notempty(), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string notempty unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::notempty(), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string notempty unequal", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::notempty(), codegen::unequal("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string notempty annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notempty(), codegen::annotation("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: vector std::string notempty annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<std::string> v [[codegen::notempty(), codegen::annotation("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional std::string notempty annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::string> v [[codegen::notempty(), codegen::annotation("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: optional vector std::string notempty annotation", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<std::vector<std::string>> v [[codegen::notempty(), codegen::annotation("abc")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("With the notempty attribute, no other attribute can be used")
    );
}

TEST_CASE("Attribute error: std::string notempty wrong parameter", "[parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::string v [[codegen::notempty("bla")]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parseRootStruct(S)),
        CodegenError,
        CM::Contains("Boolean attribute needs to be empty, 'true', or 'false'")
    );
}
