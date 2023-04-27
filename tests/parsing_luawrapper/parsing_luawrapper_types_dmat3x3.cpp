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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(glm::dmat3x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->functionName == "func");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 1);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg");
        REQUIRE(v->type);
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 defaulted", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(glm::dmat3x3 arg = glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->functionName == "func");
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
        REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 map", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::map<std::string, glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->functionName == "func");
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
        REQUIRE(mt->valueType->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(mt->valueType);
        CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 optional", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::optional<glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->functionName == "func");
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
        REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 vector", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::vector<glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->functionName == "func");
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
        REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(vt->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 array", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func1(std::array<glm::dmat3x3, 1> arg) {
    }

    [[codegen::luawrap]] void func2(std::array<glm::dmat3x3, 5> arg) {
    }

    [[codegen::luawrap]] void func3(std::array<glm::dmat3x3, 10> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 3);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "func1");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::ArrayType);
            ArrayType* at = static_cast<ArrayType*>(v->type);
            REQUIRE(at->type->tag == VariableType::Tag::BasicType);
            CHECK(at->size == 1);
            BasicType* bt = static_cast<BasicType*>(at->type);
            CHECK(bt->type == BasicType::Type::DMat3x3);

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

        CHECK(f->functionName == "func2");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::ArrayType);
            ArrayType* at = static_cast<ArrayType*>(v->type);
            REQUIRE(at->type->tag == VariableType::Tag::BasicType);
            CHECK(at->size == 5);
            BasicType* bt = static_cast<BasicType*>(at->type);
            CHECK(bt->type == BasicType::Type::DMat3x3);

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

        CHECK(f->functionName == "func3");
        CHECK(f->documentation == "");
        CHECK(f->returnValue == nullptr);
        REQUIRE(f->arguments.size() == 1);
        {
            Variable* v = f->arguments[0];
            REQUIRE(v);
            CHECK(v->name == "arg");
            REQUIRE(v->type);
            REQUIRE(v->type->tag == VariableType::Tag::ArrayType);
            ArrayType* at = static_cast<ArrayType*>(v->type);
            REQUIRE(at->type->tag == VariableType::Tag::BasicType);
            CHECK(at->size == 10);
            BasicType* bt = static_cast<BasicType*>(at->type);
            CHECK(bt->type == BasicType::Type::DMat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat3x3 foo() {
        return glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->functionName == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 map", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat3x3> foo() {
        return { "test", glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->functionName == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 optional", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat3x3> foo() {
        return glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->functionName == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 vector", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat3x3> foo() {
        return { glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->functionName == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 array", "[Parsing][LuaWrapper]") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::array<glm::dmat3x3, 1> foo1() {
        return {};
    }

    [[codegen::luawrap]] std::array<glm::dmat3x3, 5> foo2() {
        return {};
    }

    [[codegen::luawrap]] std::array<glm::dmat3x3, 10> foo3() {
        return {};
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 3);
    {
        Function* f = code.luaWrapperFunctions[0];
        REQUIRE(f);

        CHECK(f->functionName == "foo1");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::ArrayType);
        ArrayType* at = static_cast<ArrayType*>(rt);
        REQUIRE(at->type->tag == VariableType::Tag::BasicType);
        CHECK(at->size == 1);
        BasicType* bt = static_cast<BasicType*>(at->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);
    }
    {
        Function* f = code.luaWrapperFunctions[1];
        REQUIRE(f);

        CHECK(f->functionName == "foo2");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::ArrayType);
        ArrayType* at = static_cast<ArrayType*>(rt);
        REQUIRE(at->type->tag == VariableType::Tag::BasicType);
        CHECK(at->size == 5);
        BasicType* bt = static_cast<BasicType*>(at->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);
    }
    {
        Function* f = code.luaWrapperFunctions[2];
        REQUIRE(f);

        CHECK(f->functionName == "foo3");
        CHECK(f->documentation == "");
        CHECK(f->arguments.size() == 0);
        VariableType* rt = f->returnValue;
        CHECK(rt->tag == VariableType::Tag::ArrayType);
        ArrayType* at = static_cast<ArrayType*>(rt);
        REQUIRE(at->type->tag == VariableType::Tag::BasicType);
        CHECK(at->size == 10);
        BasicType* bt = static_cast<BasicType*>(at->type);
        CHECK(bt->type == BasicType::Type::DMat3x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
