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

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  reference") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'reference'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector reference") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'reference'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional reference") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::reference(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'reference'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
float v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'directory'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  vector directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<float> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'directory'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Float:  optional directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<float> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::Contains("'float' does not support attribute 'directory'")
    );
}