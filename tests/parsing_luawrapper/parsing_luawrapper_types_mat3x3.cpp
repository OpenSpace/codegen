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

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(glm::mat3x3 arg) {
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
        CHECK(bt->type == BasicType::Type::Mat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(glm::mat3x3 arg = glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)) {
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
        CHECK(bt->type == BasicType::Type::Mat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::map<std::string, glm::mat3x3> arg) {
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
        MapType* ot = static_cast<MapType*>(v->type);
        REQUIRE(ot->keyType->tag == VariableType::Tag::BasicType);
        CHECK(static_cast<BasicType*>(ot->keyType)->type == BasicType::Type::String);
        REQUIRE(ot->valueType->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ot->valueType);
        CHECK(bt->type == BasicType::Type::Mat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::optional<glm::mat3x3> arg) {
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
        CHECK(bt->type == BasicType::Type::Mat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void func(std::vector<glm::mat3x3> arg) {
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
        VectorType* ot = static_cast<VectorType*>(v->type);
        REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::Mat3x3);

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

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat3x3 foo() {
        return glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
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
    CHECK(bt->type == BasicType::Type::Mat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat3x3> foo() {
        return { "test", glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f) };
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
    CHECK(bt->type == BasicType::Type::Mat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat3x3> foo() {
        return glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
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
    CHECK(bt->type == BasicType::Type::Mat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat3x3> foo() {
        return { glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f) };
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
    CHECK(bt->type == BasicType::Type::Mat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
