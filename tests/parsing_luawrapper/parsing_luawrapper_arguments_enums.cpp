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

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  void") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] void func() {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
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

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  as single parameter") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] void func(Enum e) {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        Variable* v = f->arguments[0];
        CHECK(v->name == "e");
        REQUIRE(v->type->isCustomType());
        CustomType* t = static_cast<CustomType*>(v->type);
        CHECK(t->name == "Enum");
        REQUIRE(t->type->type == StackElement::Type::Enum);

        CHECK(v->attributes.annotation.empty());
        CHECK(v->attributes.key.empty());
        CHECK(v->attributes.inlist.empty());
        CHECK(v->attributes.inrange.empty());
        CHECK(v->attributes.less.empty());
        CHECK(v->attributes.lessequal.empty());
        CHECK(v->attributes.greater.empty());
        CHECK(v->attributes.greaterequal.empty());
        CHECK(v->attributes.notinlist.empty());
        CHECK(v->attributes.reference.empty());
        CHECK(v->attributes.unequal.empty());
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  as double parameter") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] void func(Enum e, Enum f) {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 2);
        {
            Variable* v = f->arguments[0];
            CHECK(v->name == "e");
            REQUIRE(v->type->isCustomType());
            CustomType* t = static_cast<CustomType*>(v->type);
            CHECK(t->name == "Enum");
            REQUIRE(t->type->type == StackElement::Type::Enum);

            CHECK(v->attributes.annotation.empty());
            CHECK(v->attributes.key.empty());
            CHECK(v->attributes.inlist.empty());
            CHECK(v->attributes.inrange.empty());
            CHECK(v->attributes.less.empty());
            CHECK(v->attributes.lessequal.empty());
            CHECK(v->attributes.greater.empty());
            CHECK(v->attributes.greaterequal.empty());
            CHECK(v->attributes.notinlist.empty());
            CHECK(v->attributes.reference.empty());
            CHECK(v->attributes.unequal.empty());
        }
        {
            Variable* v = f->arguments[1];
            CHECK(v->name == "f");
            REQUIRE(v->type->isCustomType());
            CustomType* t = static_cast<CustomType*>(v->type);
            CHECK(t->name == "Enum");
            REQUIRE(t->type->type == StackElement::Type::Enum);

            CHECK(v->attributes.annotation.empty());
            CHECK(v->attributes.key.empty());
            CHECK(v->attributes.inlist.empty());
            CHECK(v->attributes.inrange.empty());
            CHECK(v->attributes.less.empty());
            CHECK(v->attributes.lessequal.empty());
            CHECK(v->attributes.greater.empty());
            CHECK(v->attributes.greaterequal.empty());
            CHECK(v->attributes.notinlist.empty());
            CHECK(v->attributes.reference.empty());
            CHECK(v->attributes.unequal.empty());
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  as optional parameter") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] void func(std::optional<Enum> e) {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        Variable* v = f->arguments[0];
        CHECK(v->name == "e");
        REQUIRE(v->type->isOptionalType());
        OptionalType* t = static_cast<OptionalType*>(v->type);
        REQUIRE(t->type->isCustomType());
        CustomType* tt = static_cast<CustomType*>(t->type);
        CHECK(tt->name == "Enum");
        REQUIRE(tt->type->type == StackElement::Type::Enum);

        CHECK(v->attributes.annotation.empty());
        CHECK(v->attributes.key.empty());
        CHECK(v->attributes.inlist.empty());
        CHECK(v->attributes.inrange.empty());
        CHECK(v->attributes.less.empty());
        CHECK(v->attributes.lessequal.empty());
        CHECK(v->attributes.greater.empty());
        CHECK(v->attributes.greaterequal.empty());
        CHECK(v->attributes.notinlist.empty());
        CHECK(v->attributes.reference.empty());
        CHECK(v->attributes.unequal.empty());
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  as vector parameter") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] void func(std::vector<Enum> e) {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        Variable* v = f->arguments[0];
        CHECK(v->name == "e");
        REQUIRE(v->type->isVectorType());
        VectorType* t = static_cast<VectorType*>(v->type);
        REQUIRE(t->type->isCustomType());
        CustomType* tt = static_cast<CustomType*>(t->type);
        CHECK(tt->name == "Enum");
        REQUIRE(tt->type->type == StackElement::Type::Enum);

        CHECK(v->attributes.annotation.empty());
        CHECK(v->attributes.key.empty());
        CHECK(v->attributes.inlist.empty());
        CHECK(v->attributes.inrange.empty());
        CHECK(v->attributes.less.empty());
        CHECK(v->attributes.lessequal.empty());
        CHECK(v->attributes.greater.empty());
        CHECK(v->attributes.greaterequal.empty());
        CHECK(v->attributes.notinlist.empty());
        CHECK(v->attributes.reference.empty());
        CHECK(v->attributes.unequal.empty());
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments-Enums:  as return value") {
    constexpr const char Source[] = R"(
    enum class [[codegen::enum]] Enum {
        A,
        B,
        C
    };

    [[codegen::luawrap]] Enum func() {
    }
)";

    Code code = parse(Source);
    {
        REQUIRE(code.enums.size() == 1);
        Enum* e = code.enums[0];
        REQUIRE(e);
        REQUIRE(e->elements.size() == 3);
        CHECK(e->elements[0]->name == "A");
        CHECK(e->elements[1]->name == "B");
        CHECK(e->elements[2]->name == "C");
    }
    CHECK(code.structs.size() == 0);
    {
        REQUIRE(code.luaWrapperFunctions.size() == 1);
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func");
        CHECK(f->documentation == "");
        CHECK(f->returnValue->isCustomType());
        CustomType* t = static_cast<CustomType*>(f->returnValue);
        CHECK(t->name == "Enum");
        REQUIRE(t->type->type == StackElement::Type::Enum);
        CHECK(f->arguments.size() == 0);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
