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
#include <map>
#include <vector>

namespace {
    struct [[codegen::Dictionary(Map)]] Parameters {
        // simpleMap documentation
        std::map<std::string, std::string> simpleMap;

        // optionalMap documentation
        std::optional<std::map<std::string, std::string>> optionalMap;

        // vectorMap documentation
        std::vector<std::map<std::string, std::string>> vectorMap;

        // optionalVectorMap documentation
        std::optional<std::vector<std::map<std::string, std::string>>> optionalVectorMap;
    };
#include "execution_map_codegen.cpp"
} // namespace

TEST_CASE("Map Bake", "[verifier]") {
    using namespace std::literals;
    ghoul::Dictionary d;
    {
        ghoul::Dictionary e;
        e.setValue("a", "1"s);
        e.setValue("b", "2"s);
        e.setValue("c", "3"s);
        d.setValue("SimpleMap", e);
    }
    {
        ghoul::Dictionary e;
        e.setValue("d", "4"s);
        e.setValue("e", "5"s);
        e.setValue("f", "6"s);
        d.setValue("OptionalMap", e);
    }
    {
        ghoul::Dictionary e;
        {
            ghoul::Dictionary f;
            f.setValue("g", "7"s);
            f.setValue("h", "8"s);
            e.setValue("1", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("i", "9"s);
            f.setValue("j", "10"s);
            e.setValue("2", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("k", "11"s);
            f.setValue("l", "12"s);
            e.setValue("3", f);
        }
        d.setValue("VectorMap", e);
    }
    {
        ghoul::Dictionary e;
        {
            ghoul::Dictionary f;
            f.setValue("m", "13"s);
            f.setValue("n", "14"s);
            e.setValue("1", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("o", "15"s);
            f.setValue("p", "16"s);
            e.setValue("2", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("q", "17"s);
            f.setValue("r", "18"s);
            e.setValue("3", f);
        }
        d.setValue("OptionalVectorMap", e);
    }

    const Parameters p = codegen::bake<Parameters>(d);
    {
        REQUIRE(p.simpleMap.size() == 3);
        REQUIRE(p.simpleMap.find("a") != p.simpleMap.end());
        CHECK(p.simpleMap.at("a") == "1");
        REQUIRE(p.simpleMap.find("b") != p.simpleMap.end());
        CHECK(p.simpleMap.at("b") == "2");
        REQUIRE(p.simpleMap.find("c") != p.simpleMap.end());
        CHECK(p.simpleMap.at("c") == "3");
    }

    {
        REQUIRE(p.optionalMap.has_value());
        REQUIRE(p.optionalMap->size() == 3);
        REQUIRE(p.optionalMap->find("d") != p.optionalMap->end());
        CHECK(p.optionalMap->at("d") == "4");
        REQUIRE(p.optionalMap->find("e") != p.optionalMap->end());
        CHECK(p.optionalMap->at("e") == "5");
        REQUIRE(p.optionalMap->find("f") != p.optionalMap->end());
        CHECK(p.optionalMap->at("f") == "6");
    }

    {
        REQUIRE(p.vectorMap.size() == 3);
        REQUIRE(p.vectorMap[0].find("g") != p.vectorMap[0].end());
        CHECK(p.vectorMap[0].at("g") == "7");
        REQUIRE(p.vectorMap[0].find("h") != p.vectorMap[0].end());
        CHECK(p.vectorMap[0].at("h") == "8");

        REQUIRE(p.vectorMap[1].find("i") != p.vectorMap[1].end());
        CHECK(p.vectorMap[1].at("i") == "9");
        REQUIRE(p.vectorMap[1].find("j") != p.vectorMap[1].end());
        CHECK(p.vectorMap[1].at("j") == "10");

        REQUIRE(p.vectorMap[2].find("k") != p.vectorMap[2].end());
        CHECK(p.vectorMap[2].at("k") == "11");
        REQUIRE(p.vectorMap[2].find("l") != p.vectorMap[2].end());
        CHECK(p.vectorMap[2].at("l") == "12");
    }

    {
        REQUIRE(p.optionalVectorMap.has_value());
        REQUIRE(p.optionalVectorMap->size() == 3);
        REQUIRE(p.optionalVectorMap->at(0).find("m") != p.optionalVectorMap->at(0).end());
        CHECK(p.optionalVectorMap->at(0).at("m") == "13");
        REQUIRE(p.optionalVectorMap->at(0).find("n") != p.optionalVectorMap->at(0).end());
        CHECK(p.optionalVectorMap->at(0).at("n") == "14");

        REQUIRE(p.optionalVectorMap->at(1).find("o") != p.optionalVectorMap->at(1).end());
        CHECK(p.optionalVectorMap->at(1).at("o") == "15");
        REQUIRE(p.optionalVectorMap->at(1).find("p") != p.optionalVectorMap->at(1).end());
        CHECK(p.optionalVectorMap->at(1).at("p") == "16");

        REQUIRE(p.optionalVectorMap->at(2).find("q") != p.optionalVectorMap->at(2).end());
        CHECK(p.optionalVectorMap->at(2).at("q") == "17");
        REQUIRE(p.optionalVectorMap->at(2).find("r") != p.optionalVectorMap->at(2).end());
        CHECK(p.optionalVectorMap->at(2).at("r") == "18");
    }
}

TEST_CASE("Map  Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 4);
    {
        DocumentationEntry e = doc.entries[0];
        CHECK(e.key == "SimpleMap");
        CHECK(!e.optional);
        CHECK(e.documentation == "simpleMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(!v->documentations[0].optional);
        CHECK(v->documentations[0].documentation.empty());
        CHECK(v->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        CHECK(e.key == "OptionalMap");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(!v->documentations[0].optional);
        CHECK(v->documentations[0].documentation.empty());
        CHECK(v->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        CHECK(e.key == "VectorMap");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].optional);
        CHECK(v->documentations[0].documentation.empty());
        CHECK(v->documentations[0].verifier->type() == "Table");
        TableVerifier* w =
            dynamic_cast<TableVerifier*>(v->documentations[0].verifier.get());
        REQUIRE(w);

        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(!w->documentations[0].optional);
        CHECK(w->documentations[0].documentation.empty());
        CHECK(w->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[3];
        CHECK(e.key == "OptionalVectorMap");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalVectorMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].optional);
        CHECK(v->documentations[0].documentation.empty());
        CHECK(v->documentations[0].verifier->type() == "Table");
        TableVerifier* w =
            dynamic_cast<TableVerifier*>(v->documentations[0].verifier.get());
        REQUIRE(w);

        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(!w->documentations[0].optional);
        CHECK(w->documentations[0].documentation.empty());
        CHECK(w->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));
    }
}
