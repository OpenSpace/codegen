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

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing Struct: Minimal", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
};
)";

    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Namespace specified", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name), codegen::namespace(Namespace)]] Parameters {
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier == "Namespace");
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());
    
    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: NoExhaustive no parameter", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name), codegen::noexhaustive]] Parameters {
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: NoExhaustive true parameter", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name), codegen::noexhaustive(true)]] Parameters {
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: NoExhaustive false parameter", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name), codegen::noexhaustive(false)]] Parameters {
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Comment Ignored", "[parsing]") {
    constexpr const char Sources[] = R"(
// Test documentation
struct [[codegen::Dictionary(Name)]] Parameters {
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->comment.empty());
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.empty());

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Substruct", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    struct A {
    };
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());

    REQUIRE(s->children.size() == 1);
    {
        StackElement* e = s->children[0];
        REQUIRE(e->type == StackElement::Type::Struct);
        REQUIRE(e->name == "A");
        Struct* a = static_cast<Struct*>(e);
        REQUIRE(a->comment.empty());
        REQUIRE(a->attributes.dictionary.empty());
        REQUIRE(a->attributes.namespaceSpecifier.empty());
        REQUIRE(a->attributes.noExhaustive);
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Double Substruct", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    struct A {
    };
    struct B {
    };
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());

    REQUIRE(s->children.size() == 2);
    {
        StackElement* e = s->children[0];
        REQUIRE(e->type == StackElement::Type::Struct);
        REQUIRE(e->name == "A");
        Struct* a = static_cast<Struct*>(e);
        REQUIRE(a->comment.empty());
        REQUIRE(a->attributes.dictionary.empty());
        REQUIRE(a->attributes.namespaceSpecifier.empty());
        REQUIRE(a->attributes.noExhaustive);
        REQUIRE(a->children.empty());
        REQUIRE(a->variables.empty());
    }
    {
        StackElement* e = s->children[1];
        REQUIRE(e->type == StackElement::Type::Struct);
        REQUIRE(e->name == "B");
        Struct* b = static_cast<Struct*>(e);
        REQUIRE(b->comment.empty());
        REQUIRE(b->attributes.dictionary.empty());
        REQUIRE(b->attributes.namespaceSpecifier.empty());
        REQUIRE(b->attributes.noExhaustive);
        REQUIRE(b->children.empty());
        REQUIRE(b->variables.empty());
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Variable", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // variable documentation
    int variable;
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.size() == 1);
    {

        Variable* var = s->variables[0];
        REQUIRE(var->name == "variable");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "variable documentation");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Double Variable", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // variable1 documentation
    int variable;

    // variable2 documentation
    float variable2;
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->children.empty());
    REQUIRE(s->variables.size() == 2);
    {
        Variable* var = s->variables[0];
        REQUIRE(var->name == "variable");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "variable1 documentation");
    }
    {
        Variable* var = s->variables[1];
        REQUIRE(var->name == "variable2");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "variable2 documentation");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Empty Enum", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
    };
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    {
        StackElement* e = s->children[0];
        REQUIRE(e->type == StackElement::Type::Enum);
        REQUIRE(e->name == "Name");
        REQUIRE(e->comment == "enum documentation");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Enum", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
        Value,
        Value2
    };
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    {
        StackElement* e = s->children[0];
        REQUIRE(e->type == StackElement::Type::Enum);
        REQUIRE(e->name == "Name");
        REQUIRE(e->comment == "enum documentation");
        Enum* ee = static_cast<Enum*>(e);
        REQUIRE(ee->elements.size() == 2);
        REQUIRE(ee->elements[0]->name == "Value");
        REQUIRE(ee->elements[1]->name == "Value2");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: Enum Key Attribute", "[parsing]") {
    constexpr const char Sources[] = R"(
struct [[codegen::Dictionary(Name)]] Parameters {
    // enum documentation
    enum class Name {
        Value [[codegen::key(VK)]],
        Value2
    };
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Name");
    REQUIRE(s->attributes.namespaceSpecifier.empty());
    //REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.empty());
    REQUIRE(s->children.size() == 1);
    {
        StackElement* e = s->children[0];
        REQUIRE(e->type == StackElement::Type::Enum);
        REQUIRE(e->name == "Name");
        REQUIRE(e->comment == "enum documentation");
        Enum* ee = static_cast<Enum*>(e);
        REQUIRE(ee->elements.size() == 2);
        REQUIRE(ee->elements[0]->name == "Value");
        REQUIRE(ee->elements[0]->attributes.key == "VK");
        REQUIRE(ee->elements[1]->name == "Value2");
        REQUIRE(ee->elements[1]->attributes.key.empty());
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: New lines", "[parsing]") {
 constexpr const char Sources[] = R"(
struct
[[codegen::Dictionary(Dictionary),
codegen::namespace(NS),
codegen::noexhaustive(false)]]
Parameters
{
    int value;
};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Dictionary");
    REQUIRE(s->attributes.namespaceSpecifier == "NS");
    REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    {
        Variable* var = s->variables[0];
        REQUIRE(var->name == "value");
        REQUIRE(var->key == "Value");
        REQUIRE(var->type == "int");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}

TEST_CASE("Parsing Struct: New lines go nuts", "[parsing]") {
    constexpr const char Sources[] = R"(


struct



[[codegen::Dictionary(Dictionary),

codegen::namespace(NS),


codegen::noexhaustive(false)]]

Parameters

{

    int value;



};
)";
    Struct* s = parseRootStruct(Sources);

    REQUIRE(s->name == "Parameters");
    REQUIRE(s->attributes.dictionary == "Dictionary");
    REQUIRE(s->attributes.namespaceSpecifier == "NS");
    REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    {
        Variable* var = s->variables[0];
        REQUIRE(var->name == "value");
        REQUIRE(var->key == "Value");
        REQUIRE(var->type == "int");
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
}
