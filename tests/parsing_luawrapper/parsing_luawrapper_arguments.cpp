/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2022                                                               *
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

TEST_CASE("Parsing/LuaWrapper/Arguments:  void") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  bool") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(bool arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Bool);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  bool defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(bool arg = true) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Bool);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  bool map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, bool> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Bool);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  bool optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<bool> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Bool);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  bool vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<bool> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Bool);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  int") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(int arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  int defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(int arg = 2) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  int map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, int> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  int optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<int> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  int vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<int> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  double") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(double arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  double defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(double arg = 2.0) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  double map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, double> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  double optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<double> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  double vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<double> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  float") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(float arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Float);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  float defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(float arg = 2.f) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Float);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  float map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, float> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Float);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  float optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<float> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Float);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  float vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<float> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Float);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  string") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::string arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  string defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::string arg = "abc") {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  string map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, std::string> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  string optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<std::string> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  string vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<std::string> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  path") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::filesystem::path arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  path defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::filesystem::path arg = std::filesystem::path()) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  path map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, std::filesystem::path> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  path optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<std::filesystem::path> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  path vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<std::filesystem::path> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec2 arg = glm::ivec2(1, 2)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::ivec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::ivec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::ivec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::ivec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::ivec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::ivec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::ivec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::ivec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  ivec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::ivec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Ivec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec2 arg = glm::dvec2(1.0, 2.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dvec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dvec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dvec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec3 arg = glm::dvec3(1.0, 2.0, 3.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dvec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dvec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dvec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dvec4 arg = glm::dvec4(1.0, 2.0, 3.0, 4.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dvec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dvec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dvec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dvec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dvec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec2 arg = glm::vec2(1.f, 2.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::vec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::vec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::vec2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec3 arg = glm::vec3(1.f, 2.f, 3.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::vec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::vec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::vec3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::vec4 arg = glm::vec4(1.f, 2.f, 3.f, 4.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::vec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::vec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  vec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::vec4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Vec4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x2 arg = glm::mat2x2(1.f, 2.f, 3.f, 4.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  glm::mat2x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x3 arg = glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat2x4 arg = glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat2x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x2 arg = glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x3 arg = glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat3x4 arg = glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat3x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x2 arg = glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x3 arg = glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::mat4x4 arg = glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::mat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::mat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  mat4x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::mat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Mat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x2 arg = glm::dmat2x2(1.0, 2.0, 3.0, 4.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat2x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x3 arg = glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat2x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat2x4 arg = glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat2x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat2x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat2x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x2 arg = glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat3x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x3 arg = glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat3x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat3x4 arg = glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat3x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat3x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat3x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x2") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x2 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x2 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x2 arg = glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat4x2> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x2);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x3") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x3 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x3 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x3 arg = glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat4x3> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x3);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x4") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x4 arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x4 defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(glm::dmat4x4 arg = glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0)) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, glm::dmat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<glm::dmat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dmat4x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<glm::dmat4x4> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::DMat4x4);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dictionary") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(ghoul::Dictionary arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dictionary);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dictionary defaulted") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(ghoul::Dictionary arg = ghoul::Dictionary()) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dictionary);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dictionary map") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::map<std::string, ghoul::Dictionary> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dictionary);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dictionary optional") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::optional<ghoul::Dictionary> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dictionary);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  dictionary vector") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::vector<ghoul::Dictionary> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
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
        CHECK(bt->type == BasicType::Type::Dictionary);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Parsing/LuaWrapper/Arguments:  Variant<bool, int>") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::variant<bool, int> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 1);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg");
        REQUIRE(v->type);
        REQUIRE(v->type->tag == VariableType::Tag::VariantType);
        VariantType* ot = static_cast<VariantType*>(v->type);
        REQUIRE(ot->types.size() == 2);
        {
            VariableType* t = ot->types[0];
            REQUIRE(t->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(t);
            REQUIRE(bt->type == BasicType::Type::Bool);
        }
        {
            VariableType* t = ot->types[1];
            REQUIRE(t->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(t);
            REQUIRE(bt->type == BasicType::Type::Int);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Arguments:  Variant<double, float, string>") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void func(std::variant<double, float, std::string> arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "func");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 1);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg");
        REQUIRE(v->type);
        REQUIRE(v->type->tag == VariableType::Tag::VariantType);
        VariantType* ot = static_cast<VariantType*>(v->type);
        REQUIRE(ot->types.size() == 3);
        {
            VariableType* t = ot->types[0];
            REQUIRE(t->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(t);
            REQUIRE(bt->type == BasicType::Type::Double);
        }
        {
            VariableType* t = ot->types[1];
            REQUIRE(t->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(t);
            REQUIRE(bt->type == BasicType::Type::Float);
        }
        {
            VariableType* t = ot->types[2];
            REQUIRE(t->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(t);
            REQUIRE(bt->type == BasicType::Type::String);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
