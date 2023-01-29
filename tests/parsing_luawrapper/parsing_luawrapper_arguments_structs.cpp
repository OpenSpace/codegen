/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2023                                                               *
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

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  void") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func() {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        CHECK(f->arguments.size() == 0);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as single parameter") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(Parameter p) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        CHECK(f->arguments[0]->name == "p");
        REQUIRE(f->arguments[0]->type->isCustomType());
        CustomType* t = static_cast<CustomType*>(f->arguments[0]->type);
        REQUIRE(t);
        REQUIRE(t->type);
        CHECK(t->type->name == "Parameter");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as optional single parameter") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(std::optional<Parameter> p) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        CHECK(f->arguments[0]->name == "p");
        REQUIRE(f->arguments[0]->type->isOptionalType());
        OptionalType* t = static_cast<OptionalType*>(f->arguments[0]->type);
        REQUIRE(t);

        REQUIRE(t->type->isCustomType());
        CustomType* tt = static_cast<CustomType*>(t->type);
        REQUIRE(tt);
        REQUIRE(tt->type);
        CHECK(tt->type->name == "Parameter");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as multiple parameter") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(Parameter p, Parameter q) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 2);

        {
            CHECK(f->arguments[0]->name == "p");
            REQUIRE(f->arguments[0]->type->isCustomType());
            CustomType* t = static_cast<CustomType*>(f->arguments[0]->type);
            REQUIRE(t);
            REQUIRE(t->type);
            CHECK(t->type->name == "Parameter");
        }
        {
            CHECK(f->arguments[1]->name == "q");
            REQUIRE(f->arguments[1]->type->isCustomType());
            CustomType* t = static_cast<CustomType*>(f->arguments[1]->type);
            REQUIRE(t);
            REQUIRE(t->type);
            CHECK(t->type->name == "Parameter");

        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as multiple parameter w/ optional") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(Parameter p, std::optional<Parameter> q) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 2);

        {
            CHECK(f->arguments[0]->name == "p");
            REQUIRE(f->arguments[0]->type->isCustomType());
            CustomType* t = static_cast<CustomType*>(f->arguments[0]->type);
            REQUIRE(t);
            REQUIRE(t->type);
            CHECK(t->type->name == "Parameter");
        }
        {
            CHECK(f->arguments[1]->name == "q");
            REQUIRE(f->arguments[1]->type->isOptionalType());
            OptionalType* t = static_cast<OptionalType*>(f->arguments[1]->type);
            REQUIRE(t);

            REQUIRE(t->type->isCustomType());
            CustomType* tt = static_cast<CustomType*>(t->type);
            REQUIRE(tt);
            REQUIRE(tt->type);
            CHECK(tt->type->name == "Parameter");

        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as parameter vector") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(std::vector<Parameter> p) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        CHECK(f->arguments[0]->name == "p");
        REQUIRE(f->arguments[0]->type->isVectorType());
        VectorType* t = static_cast<VectorType*>(f->arguments[0]->type);
        REQUIRE(t->type->isCustomType());
        CustomType* tt = static_cast<CustomType*>(t->type);
        REQUIRE(tt);
        REQUIRE(tt->type);
        CHECK(tt->type->name == "Parameter");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as optional parameter vector") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(std::optional<std::vector<Parameter>> p) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        CHECK(f->arguments[0]->name == "p");
        REQUIRE(f->arguments[0]->type->isOptionalType());
        OptionalType* t = static_cast<OptionalType*>(f->arguments[0]->type);
        REQUIRE(t->type->isVectorType());
        VectorType* tt = static_cast<VectorType*>(t->type);
        REQUIRE(tt->type->isCustomType());
        CustomType* ttt = static_cast<CustomType*>(tt->type);
        REQUIRE(ttt);
        REQUIRE(ttt->type);
        CHECK(ttt->type->name == "Parameter");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as map") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void func(std::map<std::string, Parameter> p) {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        CHECK(f->arguments[0]->name == "p");
        REQUIRE(f->arguments[0]->type->isMapType());
        MapType* t = static_cast<MapType*>(f->arguments[0]->type);
        CHECK(generateTypename(t->keyType) == "std::string");
        REQUIRE(t->valueType->isCustomType());
        CustomType* tt = static_cast<CustomType*>(t->valueType);
        REQUIRE(tt);
        REQUIRE(tt->type);
        CHECK(tt->type->name == "Parameter");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Struct:  as return value") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(P)]] Parameter {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] Parameter func() {
    }
)";

    Code code = parse(Source);
    CHECK(code.enums.size() == 0);

    {
        REQUIRE(code.structs.size() == 1);
        Struct* s = code.structs[0];
        REQUIRE(s);

        CHECK(s->name == "Parameter");
        REQUIRE(s->variables.size() == 3);
        CHECK(s->variables[0]->name == "a");
        CHECK(generateTypename(s->variables[0]->type) == "int");

        CHECK(s->variables[1]->name == "b");
        CHECK(generateTypename(s->variables[1]->type) == "float");

        CHECK(s->variables[2]->name == "c");
        CHECK(generateTypename(s->variables[2]->type) == "std::string");
    }
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");

        REQUIRE(f->returnValue->isCustomType());
        CustomType* t = static_cast<CustomType*>(f->returnValue);
        REQUIRE(t);
        REQUIRE(t->type);
        CHECK(t->type->name == "Parameter");

        REQUIRE(f->arguments.size() == 0);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
