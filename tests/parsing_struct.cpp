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

#include "parsing.h"
#include "types.h"

TEST_CASE("Minimal", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());
}

TEST_CASE("Namespace specified", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name), codegen::namespace(Namespace)]] Parameters {
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier == "Namespace");
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());
}

TEST_CASE("NoExhaustive", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name), codegen::noexhaustive]] Parameters {
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());
}

TEST_CASE("Comment", "[parsing]") {
    Struct* s = parseRootStruct(R"(
// Test documentation
struct [[codegen::Dictionary(Name)]] Parameters {
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->comment == "Test documentation");
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());
}

TEST_CASE("Substruct", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    struct A {
    };
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());

    REQUIRE(s->children.size() == 1);
    REQUIRE(s->children[0]->type == StackElement::Type::Struct);
    REQUIRE(s->children[0]->name == "A");
    Struct* a = static_cast<Struct*>(s->children[0]);
    REQUIRE(a->comment.empty());
    REQUIRE(a->attributes.dictionary.empty());
    REQUIRE(a->attributes.namespaceSpecifier.empty());
    REQUIRE(a->attributes.noExhaustive);
}

TEST_CASE("Double Substruct", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    struct A {
    };
    struct B {
    };
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());

    REQUIRE(s->children.size() == 2);
    REQUIRE(s->children[0]->type == StackElement::Type::Struct);
    REQUIRE(s->children[0]->name == "A");
    Struct* a = static_cast<Struct*>(s->children[0]);
    REQUIRE(a->comment.empty());
    REQUIRE(a->attributes.dictionary.empty());
    REQUIRE(a->attributes.namespaceSpecifier.empty());
    REQUIRE(a->attributes.noExhaustive);
    REQUIRE(a->children.empty());
    REQUIRE(a->variables.empty());

    REQUIRE(s->children[1]->type == StackElement::Type::Struct);
    REQUIRE(s->children[1]->name == "B");
    Struct* b = static_cast<Struct*>(s->children[1]);
    REQUIRE(b->comment.empty());
    REQUIRE(b->attributes.dictionary.empty());
    REQUIRE(b->attributes.namespaceSpecifier.empty());
    REQUIRE(b->attributes.noExhaustive);
    REQUIRE(b->children.empty());
    REQUIRE(b->variables.empty());
}

TEST_CASE("Variable", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // variable documentation
    int variable;
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]->name == "variable");
    REQUIRE(s->variables[0]->type == "int");
    REQUIRE(s->variables[0]->comment == "variable documentation");
}

TEST_CASE("Double Variable", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // variable1 documentation
    int variable;

    // variable2 documentation
    float variable2;
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.size() == 2);
    REQUIRE(s->variables[0]->name == "variable");
    REQUIRE(s->variables[0]->type == "int");
    REQUIRE(s->variables[0]->comment == "variable1 documentation");
    REQUIRE(s->variables[1]->name == "variable2");
    REQUIRE(s->variables[1]->type == "float");
    REQUIRE(s->variables[1]->comment == "variable2 documentation");
}

TEST_CASE("Empty Enum", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
    };
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    REQUIRE(s->children[0]->type == StackElement::Type::Enum);
    REQUIRE(s->children[0]->name == "Name");
    REQUIRE(s->children[0]->comment == "enum documentation");
}

TEST_CASE("Enum", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
        Value,
        Value2
    };
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    REQUIRE(s->children[0]->type == StackElement::Type::Enum);
    REQUIRE(s->children[0]->name == "Name");
    REQUIRE(s->children[0]->comment == "enum documentation");
    Enum* e = static_cast<Enum*>(s->children[0]);
    REQUIRE(e->elements.size() == 2);
    REQUIRE(e->elements[0]->name == "Value");
    REQUIRE(e->elements[1]->name == "Value2");
}

TEST_CASE("Enum Key Attribute", "[parsing]") {
    Struct* s = parseRootStruct(R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
        Value [[codegen::key(VK)]],
        Value2
    };
};
)");

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    REQUIRE(s->children[0]->type == StackElement::Type::Enum);
    REQUIRE(s->children[0]->name == "Name");
    REQUIRE(s->children[0]->comment == "enum documentation");
    Enum* e = static_cast<Enum*>(s->children[0]);
    REQUIRE(e->elements.size() == 2);
    REQUIRE(e->elements[0]->name == "Value");
    REQUIRE(e->elements[0]->attributes.key == "VK");
    REQUIRE(e->elements[1]->name == "Value2");
    REQUIRE(e->elements[1]->attributes.key.empty());
}
