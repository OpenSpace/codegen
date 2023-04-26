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

#include <catch2/catch_test_macros.hpp>

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing/LuaWrapper/Arguments:  Pointer", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void funcVoid(void* arg) {
    }

    [[codegen::luawrap]] void funcInt(int* arg) {
    }

    [[codegen::luawrap]] void funcString(std::string* arg) {
    }

    [[codegen::luawrap]] void funcStruct(Foo* arg) {
    }

    [[codegen::luawrap]] void funcStruct2(Foo** arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(v->type);
            CHECK(generateTypename(pt) == "void*");

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
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(v->type);
            CHECK(generateTypename(pt) == "int*");

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
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(v->type);
            CHECK(generateTypename(pt) == "std::string*");

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
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(v->type);
            CHECK(generateTypename(pt) == "Foo*");

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
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(v->type);
            CHECK(generateTypename(pt) == "Foo**");

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  Pointer defaulted", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void funcVoid(void* arg = nullptr) {
    }

    [[codegen::luawrap]] void funcInt(int* arg = nullptr) {
    }

    [[codegen::luawrap]] void funcString(std::string* arg = nullptr) {
    }

    [[codegen::luawrap]] void funcStruct(Foo* arg = nullptr) {
    }

    [[codegen::luawrap]] void funcStruct2(Foo** arg = nullptr) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "void*");

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
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "int*");

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
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "std::string*");

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
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "Foo*");

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
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "Foo**");

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  Pointer map", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void funcVoid(std::map<std::string, void*> arg) {
    }

    [[codegen::luawrap]] void funcInt(std::map<std::string, int*> arg) {
    }

    [[codegen::luawrap]] void funcString(std::map<std::string, std::string*> arg) {
    }

    [[codegen::luawrap]] void funcStruct(std::map<std::string, Foo*> arg) {
    }

    [[codegen::luawrap]] void funcStruct2(std::map<std::string, Foo**> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::MapType);
            MapType* mt = static_cast<MapType*>(v->type);
            REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
            CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
            REQUIRE(mt->valueType->isPointerType());
            PointerType* pt = static_cast<PointerType*>(mt->valueType);
            CHECK(generateTypename(pt) == "void*");

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
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::MapType);
            MapType* mt = static_cast<MapType*>(v->type);
            REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
            CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
            REQUIRE(mt->valueType->isPointerType());
            PointerType* pt = static_cast<PointerType*>(mt->valueType);
            CHECK(generateTypename(pt) == "int*");

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
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::MapType);
            MapType* mt = static_cast<MapType*>(v->type);
            REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
            CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
            REQUIRE(mt->valueType->isPointerType());
            PointerType* pt = static_cast<PointerType*>(mt->valueType);
            CHECK(generateTypename(pt) == "std::string*");

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
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::MapType);
            MapType* mt = static_cast<MapType*>(v->type);
            REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
            CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
            REQUIRE(mt->valueType->isPointerType());
            PointerType* pt = static_cast<PointerType*>(mt->valueType);
            CHECK(generateTypename(pt) == "Foo*");

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
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::MapType);
            MapType* mt = static_cast<MapType*>(v->type);
            REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
            CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
            REQUIRE(mt->valueType->isPointerType());
            PointerType* pt = static_cast<PointerType*>(mt->valueType);
            CHECK(generateTypename(pt) == "Foo**");

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  Pointer optional", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void funcVoid(std::optional<void*> arg) {
    }

    [[codegen::luawrap]] void funcInt(std::optional<int*> arg) {
    }

    [[codegen::luawrap]] void funcString(std::optional<std::string*> arg) {
    }

    [[codegen::luawrap]] void funcStruct(std::optional<Foo*> arg) {
    }

    [[codegen::luawrap]] void funcStruct2(std::optional<Foo**> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "void*");

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
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "int*");

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
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "std::string*");

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
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "Foo*");

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
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
            OptionalType* ot = static_cast<OptionalType*>(v->type);
            REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(ot->type);
            CHECK(generateTypename(pt) == "Foo**");

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  Pointer vector", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void funcVoid(std::vector<void*> arg) {
    }

    [[codegen::luawrap]] void funcInt(std::vector<int*> arg) {
    }

    [[codegen::luawrap]] void funcString(std::vector<std::string*> arg) {
    }

    [[codegen::luawrap]] void funcStruct(std::vector<Foo*> arg) {
    }

    [[codegen::luawrap]] void funcStruct2(std::vector<Foo**> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::VectorType);
            VectorType* vt = static_cast<VectorType*>(v->type);
            REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(vt->type);
            CHECK(generateTypename(pt) == "void*");

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
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::VectorType);
            VectorType* vt = static_cast<VectorType*>(v->type);
            REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(vt->type);
            CHECK(generateTypename(pt) == "int*");

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
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::VectorType);
            VectorType* vt = static_cast<VectorType*>(v->type);
            REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(vt->type);
            CHECK(generateTypename(pt) == "std::string*");

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
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::VectorType);
            VectorType* vt = static_cast<VectorType*>(v->type);
            REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(vt->type);
            CHECK(generateTypename(pt) == "Foo*");

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
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::VectorType);
            VectorType* vt = static_cast<VectorType*>(v->type);
            REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
            PointerType* pt = static_cast<PointerType*>(vt->type);
            CHECK(generateTypename(pt) == "Foo**");

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

TEST_CASE("Parsing/LuaWrapper/Return:  pointer", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] void* funcVoid() {
    }

    [[codegen::luawrap]] int* funcInt() {
    }

    [[codegen::luawrap]] std::string* funcString() {
    }

    [[codegen::luawrap]] Foo* funcStruct() {
    }

    [[codegen::luawrap]] Foo** funcStruct2() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(rt);
        CHECK(generateTypename(pt) == "void*");
    }
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(rt);
        CHECK(generateTypename(pt) == "int*");
    }
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(rt);
        CHECK(generateTypename(pt) == "std::string*");
    }
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(rt);
        CHECK(generateTypename(pt) == "Foo*");
    }
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(rt);
        CHECK(generateTypename(pt) == "Foo**");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  pointer map", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] std::map<std::string, void*> funcVoid() {
    }

    [[codegen::luawrap]] std::map<std::string, int*> funcInt() {
    }

    [[codegen::luawrap]] std::map<std::string, std::string*> funcString() {
    }

    [[codegen::luawrap]] std::map<std::string, Foo*> funcStruct() {
    }

    [[codegen::luawrap]] std::map<std::string, Foo**> funcStruct2() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::MapType);
        MapType* mt = static_cast<MapType*>(rt);
        REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
        CHECK(mt->valueType->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(mt->valueType);
        CHECK(generateTypename(pt) == "void*");
    }
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::MapType);
        MapType* mt = static_cast<MapType*>(rt);
        REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
        CHECK(mt->valueType->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(mt->valueType);
        CHECK(generateTypename(pt) == "int*");
    }
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::MapType);
        MapType* mt = static_cast<MapType*>(rt);
        REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
        CHECK(mt->valueType->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(mt->valueType);
        CHECK(generateTypename(pt) == "std::string*");
    }
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::MapType);
        MapType* mt = static_cast<MapType*>(rt);
        REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
        CHECK(mt->valueType->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(mt->valueType);
        CHECK(generateTypename(pt) == "Foo*");
    }
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::MapType);
        MapType* mt = static_cast<MapType*>(rt);
        REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
        CHECK(mt->valueType->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(mt->valueType);
        CHECK(generateTypename(pt) == "Foo**");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  pointer optional", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] std::optional<void*> funcVoid() {
    }

    [[codegen::luawrap]] std::optional<int*> funcInt() {
    }

    [[codegen::luawrap]] std::optional<std::string*> funcString() {
    }

    [[codegen::luawrap]] std::optional<Foo*> funcStruct() {
    }

    [[codegen::luawrap]] std::optional<Foo**> funcStruct2() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(rt);
        REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(ot->type);
        CHECK(generateTypename(pt) == "void*");
    }
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(rt);
        REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(ot->type);
        CHECK(generateTypename(pt) == "int*");
    }
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(rt);
        REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(ot->type);
        CHECK(generateTypename(pt) == "std::string*");
    }
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(rt);
        REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(ot->type);
        CHECK(generateTypename(pt) == "Foo*");
    }
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(rt);
        REQUIRE(ot->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(ot->type);
        CHECK(generateTypename(pt) == "Foo**");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  pointer vector", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    struct Foo {};

    [[codegen::luawrap]] std::vector<void*> funcVoid() {
    }

    [[codegen::luawrap]] std::vector<int*> funcInt() {
    }

    [[codegen::luawrap]] std::vector<std::string*> funcString() {
    }

    [[codegen::luawrap]] std::vector<Foo*> funcStruct() {
    }

    [[codegen::luawrap]] std::vector<Foo**> funcStruct2() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 5);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "funcVoid");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::VectorType);
        VectorType* vt = static_cast<VectorType*>(rt);
        REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(vt->type);
        CHECK(generateTypename(pt) == "void*");
    }
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "funcInt");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::VectorType);
        VectorType* vt = static_cast<VectorType*>(rt);
        REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(vt->type);
        CHECK(generateTypename(pt) == "int*");
    }
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "funcString");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::VectorType);
        VectorType* vt = static_cast<VectorType*>(rt);
        REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(vt->type);
        CHECK(generateTypename(pt) == "std::string*");
    }
    {
        Function* f = code.luaWrapperFunctions[3];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::VectorType);
        VectorType* vt = static_cast<VectorType*>(rt);
        REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(vt->type);
        CHECK(generateTypename(pt) == "Foo*");
    }
    {
        Function* f = code.luaWrapperFunctions[4];
        REQUIRE(f);

        CHECK(f->functionName == "funcStruct2");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        REQUIRE(rt->tag == VariableType::Tag::VectorType);
        VectorType* vt = static_cast<VectorType*>(rt);
        REQUIRE(vt->type->tag == VariableType::Tag::PointerType);
        PointerType* pt = static_cast<PointerType*>(vt->type);
        CHECK(generateTypename(pt) == "Foo**");
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
