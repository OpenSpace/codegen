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

TEST_CASE("Unsupported Attributes: glm::dvec4 annotation", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::annotation(ABC)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 annotation", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::annotation(ABC)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 annotation", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::annotation(ABC)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 inlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::inlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 inlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::inlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 inlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::inlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 inrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::inrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 inrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::inrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 inrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::inrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 less", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 less", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 less", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 lessequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 lessequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 lessequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 greater", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 greater", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains("'glm::dvec4' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 greater", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 greaterequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 greaterequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 greaterequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 notinlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::notinlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 notinlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::notinlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 notinlist", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::notinlist(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 notinrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::notinrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 notinrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::notinrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 notinrange", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::notinrange(1, 2)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError,
        CM::Contains("'glm::dvec4' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 reference", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 reference", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 reference", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'reference'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 unequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::unequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'unequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 unequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::unequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'unequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 unequal", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::unequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'unequal'")
    );
}

TEST_CASE("Unsupported Attributes: glm::dvec4 directory", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
glm::dvec4 v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: vector glm::dvec4 directory", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<glm::dvec4> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: optional glm::dvec4 directory", "[structs][parsing_error]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<glm::dvec4> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'glm::dvec4' does not support attribute 'directory'")
    );
}