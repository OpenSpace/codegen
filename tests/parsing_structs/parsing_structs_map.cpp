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

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/Structs/Map: Minimal", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    std::map<std::string, std::string> p;
};)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    CHECK(code.enums.empty());
    CHECK(code.luaWrapperFunctions.empty());
    Struct* s = code.structs.front();

    REQUIRE(s);
    CHECK(s->name == "Parameters");
    CHECK(s->attributes.dictionary == "Name");
    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 1);
    CHECK(s->variables[0]->name == "p");
    CHECK(s->variables[0]->key == "\"P\"");

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}

//TEST_CASE("Parsing/Structs/Map: Enum Key (Outer)", "[Parsing][Structs]") {
//    constexpr std::string_view Source = R"(
//    enum class [[codegen::stringify()]] KeyType {
//        Key1,
//        Key2,
//        Key3
//    };
//
//    struct [[codegen::Dictionary(Name)]] Parameters {
//        std::map<KeyType, std::string> p;
//    };
//)";
//
//    Code code = parse(Source);
//    REQUIRE(code.structs.size() == 1);
//    REQUIRE(code.enums.size() == 1);
//    CHECK(code.luaWrapperFunctions.empty());
//
//    {
//        Enum* e = code.enums.front();
//        REQUIRE(e);
//
//        CHECK(e->parent == nullptr);
//        CHECK(e->attributes.mappedTo.empty());
//        CHECK(e->attributes.stringify);
//        CHECK(!e->attributes.arrayify);
//        REQUIRE(e->elements.size() == 3);
//        {
//            EnumElement* ee = e->elements[0];
//            REQUIRE(ee);
//            CHECK(ee->name == "Key1");
//        }
//        {
//            EnumElement* ee = e->elements[1];
//            REQUIRE(ee);
//            CHECK(ee->name == "Key2");
//        }
//        {
//            EnumElement* ee = e->elements[2];
//            REQUIRE(ee);
//            CHECK(ee->name == "Key3");
//        }
//    }
//
//    {
//        Struct* s = code.structs.front();
//        REQUIRE(s);
//
//        CHECK(s->name == "Parameters");
//        CHECK(s->attributes.dictionary == "Name");
//        CHECK(s->children.empty());
//        REQUIRE(s->variables.size() == 1);
//        CHECK(s->variables[0]->name == "p");
//        CHECK(s->variables[0]->key == "\"P\"");
//
//        CHECK(s->variables[0]->attributes.annotation.empty());
//        CHECK(s->variables[0]->attributes.greater.empty());
//        CHECK(s->variables[0]->attributes.greaterequal.empty());
//        CHECK(s->variables[0]->attributes.inlist.empty());
//        CHECK(s->variables[0]->attributes.less.empty());
//        CHECK(s->variables[0]->attributes.lessequal.empty());
//        CHECK(s->variables[0]->attributes.notinrange.empty());
//        CHECK(s->variables[0]->attributes.reference.empty());
//        CHECK(s->variables[0]->attributes.unequal.empty());
//        CHECK(!s->variables[0]->attributes.isColor);
//        CHECK(!s->variables[0]->attributes.isDirectory);
//        CHECK(!s->variables[0]->attributes.isDateTime);
//        CHECK(!s->variables[0]->attributes.isIdentifier);
//        CHECK(!s->variables[0]->attributes.mustBeNotEmpty);
//        //CHECK(!s->variables[0]->attributes.isPrivate);
//    }
//
//    const std::string r = generateResult(code);
//    CHECK(!r.empty());
//}

TEST_CASE("Parsing/Structs/Map: Enum Key (Inner)", "[Parsing][Structs]") {
    constexpr std::string_view Source = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    enum class KeyType {
        Key1,
        Key2,
        Key3
    };

    std::map<KeyType, std::string> p;
};)";

    Code code = parse(Source);
    REQUIRE(code.structs.size() == 1);
    REQUIRE(code.enums.empty());
    CHECK(code.luaWrapperFunctions.empty());

    {
        Struct* s = code.structs.front();
        REQUIRE(s);

        {
            REQUIRE(s->children.size() == 1);
            REQUIRE(s->children.front()->type == StackElement::Type::Enum);
            Enum* e = static_cast<Enum*>(s->children.front());
            REQUIRE(e);

            CHECK(e->attributes.mappedTo.empty());
            CHECK(!e->attributes.stringify);
            CHECK(!e->attributes.arrayify);
            REQUIRE(e->elements.size() == 3);
            {
                EnumElement* ee = e->elements[0];
                REQUIRE(ee);
                CHECK(ee->name == "Key1");
            }
            {
                EnumElement* ee = e->elements[1];
                REQUIRE(ee);
                CHECK(ee->name == "Key2");
            }
            {
                EnumElement* ee = e->elements[2];
                REQUIRE(ee);
                CHECK(ee->name == "Key3");
            }
        }


        CHECK(s->name == "Parameters");
        CHECK(s->attributes.dictionary == "Name");
        REQUIRE(s->variables.size() == 1);
        CHECK(s->variables[0]->name == "p");
        CHECK(s->variables[0]->key == "\"P\"");

        CHECK(s->variables[0]->attributes.annotation.empty());
        CHECK(s->variables[0]->attributes.greater.empty());
        CHECK(s->variables[0]->attributes.greaterequal.empty());
        CHECK(s->variables[0]->attributes.inlist.empty());
        CHECK(s->variables[0]->attributes.less.empty());
        CHECK(s->variables[0]->attributes.lessequal.empty());
        CHECK(s->variables[0]->attributes.notinrange.empty());
        CHECK(s->variables[0]->attributes.reference.empty());
        CHECK(s->variables[0]->attributes.unequal.empty());
        CHECK(!s->variables[0]->attributes.isColor);
        CHECK(!s->variables[0]->attributes.isDirectory);
        CHECK(!s->variables[0]->attributes.isDateTime);
        CHECK(!s->variables[0]->attributes.isIdentifier);
        CHECK(!s->variables[0]->attributes.mustBeNotEmpty);
        //CHECK(!s->variables[0]->attributes.isPrivate);
    }

    const std::string r = generateResult(code);
    CHECK(!r.empty());
}
