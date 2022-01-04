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

TEST_CASE("Unsupported Attributes: ghoul::Dictionary annotation", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary annotation", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary annotation", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary inlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary inlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary inlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary inrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary inrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary inrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary less", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary less", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary less", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary lessequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary lessequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary lessequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary greater", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary greater", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary greater", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary greaterequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary greaterequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary greaterequal", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary notinlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary notinlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary notinlist", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary notinrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary notinrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary notinrange", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary color", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary color", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary color", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Unsupported Attributes: ghoul::Dictionary directory", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: vector ghoul::Dictionary directory", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'directory'")
    );
}

TEST_CASE("Unsupported Attributes: optional ghoul::Dictionary directory", "[structs][parsing]") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'ghoul::Dictionary' does not support attribute 'directory'")
    );
}
