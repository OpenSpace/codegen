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
#include <variant>
#include <vector>

namespace {
    struct [[codegen::Dictionary(Variant)]] Parameters {
        // optional variant vector documentation
        std::optional<std::variant<std::string, std::vector<std::string>>> ovv;
    };
#include "execution_optional_variant_vector_codegen.cpp"
} // namespace

TEST_CASE("Optional Variant Vector Bake", "[verifier]") {
    {
        ghoul::Dictionary d;
        const Parameters p = codegen::bake<Parameters>(d);
        CHECK(!p.ovv.has_value());
    }

    {
        ghoul::Dictionary d;
        d.setValue("Ovv", std::string("abc"));
        const Parameters p = codegen::bake<Parameters>(d);
        REQUIRE(p.ovv.has_value());
        REQUIRE(std::holds_alternative<std::string>(*p.ovv));
        CHECK(std::get<std::string>(*p.ovv) == "abc");
    }
    {
        ghoul::Dictionary d;
        ghoul::Dictionary e;
        e.setValue("1", std::string("def"));
        e.setValue("2", std::string("ghi"));
        d.setValue("Ovv", e);
        const Parameters p = codegen::bake<Parameters>(d);
        REQUIRE(p.ovv.has_value());
        REQUIRE(std::holds_alternative<std::vector<std::string>>(*p.ovv));
        CHECK(
            std::get<std::vector<std::string>>(*p.ovv) ==
            std::vector<std::string>{ "def", "ghi" }
        );
    }
}

TEST_CASE("Optional Variant Vector Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 1);
    DocumentationEntry e = doc.entries[0];
    CHECK(e.key == "Ovv");
    CHECK(e.optional);
    CHECK(e.documentation == "optional variant vector documentation");
    CHECK(e.verifier->type() == "String, or Table");
    OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
    REQUIRE(v);
    REQUIRE(v->values.size() == 2);
    CHECK(v->values[0]->type() == "String");
    CHECK(dynamic_cast<StringVerifier*>(v->values[0].get()));
    CHECK(v->values[1]->type() == "Table");
    TableVerifier* w = dynamic_cast<TableVerifier*>(v->values[1].get());
    REQUIRE(w);
    REQUIRE(w->documentations.size() == 1);
    CHECK(w->documentations[0].key == "*");
    CHECK(w->documentations[0].verifier->type() == "String");
    CHECK(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));
}
