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

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <ghoul/misc/dictionary.h>
#include <optional>
#include <vector>

namespace openspace { struct Enums; }

namespace {
    struct [[codegen::Dictionary(Enums)]] Parameters {
        // enum A documentation
        enum class A {
            Value1,
            value2,
            Value3
        };
        // variable enumAValue documentation
        A enumAValue;

        // enum B documentation
        enum class B {
            Value1,
            value2,
            Value3
        };
        // variable enumBValue documentation
        std::optional<B> enumBValue;

        // enum C documentation
        enum class C {
            Value1,
            value2,
            Value3
        };
        // variable enumCValue documentation
        std::vector<C> enumCValue;
    };
#include "enums_codegen.cpp"
} // namespace

TEST_CASE("Enum Bake", "[verifier]") {
    ghoul::Dictionary d;
    d.setValue("EnumAValue", std::string("Value1"));
    d.setValue("EnumBValue", std::string("value2"));

    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("Value3"));
        e.setValue("2", std::string("value2"));
        e.setValue("3", std::string("Value1"));
        d.setValue("EnumCValue", e);
    }

    Parameters p = codegen::bake<Parameters>(d);
    REQUIRE(p.enumAValue == Parameters::A::Value1);
    REQUIRE(p.enumBValue.has_value());
    REQUIRE(*p.enumBValue == Parameters::B::value2);
    REQUIRE(p.enumCValue.size() == 3);
    REQUIRE(p.enumCValue[0] == Parameters::C::Value3);
    REQUIRE(p.enumCValue[1] == Parameters::C::value2);
    REQUIRE(p.enumCValue[2] == Parameters::C::Value1);
}

TEST_CASE("Enum Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<openspace::Enums>();

    REQUIRE(doc.entries.size() == 3);
    {
        DocumentationEntry e = doc.entries[0];
        REQUIRE(e.key == "EnumAValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "variable enumAValue documentation");
        REQUIRE(e.verifier->type() == "String");
        REQUIRE(dynamic_cast<StringVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        REQUIRE(e.key == "EnumBValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "variable enumBValue documentation");
        REQUIRE(e.verifier->type() == "String");
        REQUIRE(dynamic_cast<StringVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        REQUIRE(e.key == "EnumCValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "variable enumCValue documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].optional);
        REQUIRE(v->documentations[0].documentation == "enum C documentation");
        REQUIRE(v->documentations[0].verifier->type() == "String");
        REQUIRE(dynamic_cast<StringVerifier*>(v->documentations[0].verifier.get()));
    }
}
