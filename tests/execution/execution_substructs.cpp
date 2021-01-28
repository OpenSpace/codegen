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

namespace {
    struct [[codegen::Dictionary(Substructs)]] Parameters {
        // struct A documentation
        struct A {
            // A::value documentation
            int value;
        };
        // variable structAValue documentation
        A structAValue;

        // struct B documentation
        struct B {
            // B::valval documentation
            float valval;
        };
        // variable structBValue documentation
        std::optional<B> structBValue;

        // struct C documentation
        struct C {
            // C::eulav documentation
            std::string eulav;

            // C::lavlav documentation
            bool lavlav;
        };
        // variable structCValue documentation
        std::vector<C> structCValue;
    };
#include "execution_substructs_codegen.cpp"
} // namespace

TEST_CASE("Substruct Bake", "[verifier]") {
    ghoul::Dictionary d;
    {
        ghoul::Dictionary e;
        e.setValue("Value", 5.0);
        d.setValue("StructAValue", e);
    }
    {
        ghoul::Dictionary e;
        e.setValue("Valval", 2.1);
        d.setValue("StructBValue", e);
    }
    {
        ghoul::Dictionary e;
        {
            ghoul::Dictionary f;
            f.setValue("Eulav", std::string("text"));
            f.setValue("Lavlav", true);
            e.setValue("1", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("Eulav", std::string("text2"));
            f.setValue("Lavlav", false);
            e.setValue("2", f);
        }
        d.setValue("StructCValue", e);
    }

    Parameters p = codegen::bake<Parameters>(d);
    REQUIRE(p.structAValue.value == 5);
    REQUIRE(p.structBValue.has_value());
    REQUIRE(p.structBValue->valval == 2.1f);
    REQUIRE(p.structCValue.size() == 2);
    REQUIRE(p.structCValue[0].eulav == "text");
    REQUIRE(p.structCValue[0].lavlav == true);
    REQUIRE(p.structCValue[1].eulav == "text2");
    REQUIRE(p.structCValue[1].lavlav == false);
}

TEST_CASE("Substruct Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 3);
    {
        DocumentationEntry e = doc.entries[0];
        REQUIRE(e.key == "StructAValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "variable structAValue documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "Value");
        REQUIRE(!v->documentations[0].optional);
        REQUIRE(v->documentations[0].documentation == "A::value documentation");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        REQUIRE(dynamic_cast<IntVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        REQUIRE(e.key == "StructBValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "variable structBValue documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "Valval");
        REQUIRE(!v->documentations[0].optional);
        REQUIRE(v->documentations[0].documentation == "B::valval documentation");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        REQUIRE(e.key == "StructCValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "variable structCValue documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].optional);
        REQUIRE(v->documentations[0].documentation == "struct C documentation");
        REQUIRE(v->documentations[0].verifier->type() == "Table");
        TableVerifier* w = dynamic_cast<TableVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->documentations.size() == 2);
        REQUIRE(w->documentations[0].key == "Eulav");
        REQUIRE(!w->documentations[0].optional);
        REQUIRE(w->documentations[0].documentation == "C::eulav documentation");
        REQUIRE(w->documentations[0].verifier->type() == "String");
        REQUIRE(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));

        REQUIRE(w->documentations[1].key == "Lavlav");
        REQUIRE(!w->documentations[1].optional);
        REQUIRE(w->documentations[1].documentation == "C::lavlav documentation");
        REQUIRE(w->documentations[1].verifier->type() == "Boolean");
        REQUIRE(dynamic_cast<BoolVerifier*>(w->documentations[1].verifier.get()));

    }
}
