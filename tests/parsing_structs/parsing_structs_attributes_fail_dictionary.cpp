/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2024                                                               *
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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "codegen.h"
#include "parsing.h"
#include "types.h"

namespace CM = Catch::Matchers;

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional annotation") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::annotation(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'annotation'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional inlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::inlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  inrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector inrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional inrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::inrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'inrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  less") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector less") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional less") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::less(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'less'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  lessequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector lessequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional lessequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::lessequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'lessequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  greater") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector greater") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional greater") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::greater(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greater'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  greaterequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector greaterequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional greaterequal") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::greaterequal(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'greaterequal'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional notinlist") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::notinlist(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinlist'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  notinrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector notinrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional notinrange") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::notinrange(1)]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'notinrange'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional color") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::color()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'color'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
ghoul::Dictionary v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'directory'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  vector directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::vector<ghoul::Dictionary> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'directory'")
    );
}

TEST_CASE("Parsing/Structs/Attributes/Error/Dictionary:  optional directory") {
    constexpr const char S[] = R"(struct [[codegen::Dictionary(D)]] P {
std::optional<ghoul::Dictionary> v [[codegen::directory()]];
};)";
    CHECK_THROWS_MATCHES(
        generateResult(parse(S)),
        CodegenError, CM::StartsWith("Type 'ghoul::Dictionary' does not support attribute 'directory'")
    );
}
