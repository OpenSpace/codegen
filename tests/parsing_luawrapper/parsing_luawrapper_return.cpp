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

TEST_CASE("Parsing/LuaWrapper/Return:  void") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  int") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] int foo() {
        return 1;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Int);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  int map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, int> foo() {
        return { "test", 1 };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Int);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  int optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<int> foo() {
        return 1;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Int);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  int vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<int> foo() {
        return { 1 };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Int);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  double") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] double foo() {
        return 1.0;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Double);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  double map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, double> foo() {
        return { "test", 1.0 };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Double);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  double optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<double> foo() {
        return 1.0;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Double);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  double vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<double> foo() {
        return { 1.0 };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Double);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  float") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] float foo() {
        return 1.f;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Float);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  float map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, float> foo() {
        return { "test", 1.f };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Float);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  float optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<float> foo() {
        return 1.f;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Float);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  float vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<float> foo() {
        return { 1.f };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Float);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  string") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::string foo() {
        return "test";
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::String);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  string map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, std::string> foo() {
        return { "test", "string" };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::String);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  string optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<std::string> foo() {
        return "test";
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::String);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  string vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<std::string> foo() {
        return { "test" };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::String);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  path") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::filesystem::path foo() {
        return std::filesystem::path("test");
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Path);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  path map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, std::filesystem::path> foo() {
        return { "test", std::filesystem::path("string") };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Path);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  path optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<std::filesystem::path> foo() {
        return std::filesystem::path("abc");
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Path);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  path vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<std::filesystem::path> foo() {
        return { std::filesystem::path("abc") };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Path);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::ivec2 foo() {
        return glm::ivec2(1, 2);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Ivec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::ivec2> foo() {
        return { "test", glm::ivec2(1, 2) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Ivec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::ivec2> foo() {
        return glm::ivec2(1, 2);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Ivec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::ivec2> foo() {
        return { glm::ivec2(1, 2) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Ivec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::ivec3 foo() {
        return glm::ivec3(1, 2, 3);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Ivec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::ivec3> foo() {
        return { "test", glm::ivec3(1, 2) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Ivec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::ivec3> foo() {
        return glm::ivec3(1, 2, 3);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Ivec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::ivec3> foo() {
        return { glm::ivec3(1, 2, 3) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Ivec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::ivec4 foo() {
        return glm::ivec4(1, 2, 3, 4);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Ivec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::ivec4> foo() {
        return { "test", glm::ivec4(1, 2, 3, 4) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Ivec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::ivec4> foo() {
        return glm::ivec4(1, 2, 3, 4);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Ivec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  ivec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::ivec4> foo() {
        return { glm::ivec4(1, 2, 3, 4) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Ivec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dvec2 foo() {
        return glm::dvec2(1.0, 2.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Dvec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dvec2> foo() {
        return { "test", glm::dvec2(1.0, 2.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Dvec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dvec2> foo() {
        return glm::dvec2(1.0, 2.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Dvec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dvec2> foo() {
        return { glm::dvec2(1.0, 2.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Dvec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dvec3 foo() {
        return glm::dvec3(1.0, 2.0, 3.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Dvec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dvec3> foo() {
        return { "test", glm::dvec3(1.0, 2.0, 3.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Dvec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dvec3> foo() {
        return glm::dvec3(1.0, 2.0, 3.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Dvec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dvec3> foo() {
        return { glm::dvec3(1.0, 2.0, 3.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Dvec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dvec4 foo() {
        return glm::dvec4(1.0, 2.0, 3.0, 4.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Dvec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dvec4> foo() {
        return { "test", glm::dvec4(1.0, 2.0, 3.0, 4.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Dvec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dvec4> foo() {
        return glm::dvec4(1.0, 2.0, 3.0, 4.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Dvec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dvec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dvec4> foo() {
        return { glm::dvec4(1.0, 2.0, 3.0, 4.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Dvec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::vec2 foo() {
        return glm::vec2(1.f, 2.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Vec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::vec2> foo() {
        return { "test", glm::vec2(1.f, 2.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Vec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::vec2> foo() {
        return glm::vec2(1.f, 2.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Vec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::vec2> foo() {
        return { glm::vec2(1.f, 2.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Vec2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::vec3 foo() {
        return glm::vec3(1.f, 2.f, 3.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Vec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::vec3> foo() {
        return { "test", glm::vec3(1.f, 2.f, 3.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Vec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::vec3> foo() {
        return glm::vec3(1.f, 2.f, 3.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Vec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::vec3> foo() {
        return { glm::vec3(1.f, 2.f, 3.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Vec3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::vec4 foo() {
        return glm::vec4(1.f, 2.f, 3.f, 4.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Vec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::vec4> foo() {
        return { "test", glm::vec4(1.f, 2.f, 3.f, 4.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Vec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::vec4> foo() {
        return glm::vec4(1.f, 2.f, 3.f, 4.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Vec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  vec4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::vec4> foo() {
        return { glm::vec4(1.f, 2.f, 3.f, 4.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Vec4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat2x2 foo() {
        return glm::mat2x2(1.f, 2.f, 3.f, 4.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat2x2> foo() {
        return { "test", glm::mat2x2(1.f, 2.f, 3.f, 4.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat2x2> foo() {
        return glm::mat2x2(1.f, 2.f, 3.f, 4.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat2x2> foo() {
        return { glm::mat2x2(1.f, 2.f, 3.f, 4.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat2x3 foo() {
        return glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat2x3> foo() {
        return { "test", glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat2x3> foo() {
        return glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat2x3> foo() {
        return { glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat2x4 foo() {
        return glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat2x4> foo() {
        return { "test", glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat2x4> foo() {
        return glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat2x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat2x4> foo() {
        return { glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat3x2 foo() {
        return glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat3x2> foo() {
        return { "test", glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat3x2> foo() {
        return glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat3x2> foo() {
        return { glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat3x2);

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

    CHECK(f->name == "foo");
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

    CHECK(f->name == "foo");
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

    CHECK(f->name == "foo");
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

    CHECK(f->name == "foo");
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

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat3x4 foo() {
        return glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat3x4> foo() {
        return { "test", glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat3x4> foo() {
        return glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat3x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat3x4> foo() {
        return { glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat4x2 foo() {
        return glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat4x2> foo() {
        return { "test", glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat4x2> foo() {
        return glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat4x2> foo() {
        return { glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat4x3 foo() {
        return glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat4x3> foo() {
        return { "test", glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat4x3> foo() {
        return glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat4x3> foo() {
        return { glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::mat4x4 foo() {
        return glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Mat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::mat4x4> foo() {
        return { "test", glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Mat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::mat4x4> foo() {
        return glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Mat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  mat4x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::mat4x4> foo() {
        return { glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Mat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat2x2 foo() {
        return glm::dmat2x2(1.0, 2.0, 3.0, 4.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat2x2> foo() {
        return { "test", glm::dmat2x2(1.0, 2.0, 3.0, 4.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat2x2> foo() {
        return glm::dmat2x2(1.0, 2.0, 3.0, 4.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat2x2> foo() {
        return { glm::dmat2x2(1.0, 2.0, 3.0, 4.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat2x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat2x3 foo() {
        return glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat2x3> foo() {
        return { "test", glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat2x3> foo() {
        return glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat2x3> foo() {
        return { glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat2x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat2x4 foo() {
        return glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat2x4> foo() {
        return { "test", glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat2x4> foo() {
        return glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat2x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat2x4> foo() {
        return { glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat2x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat3x2 foo() {
        return glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat3x2> foo() {
        return { "test", glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat3x2> foo() {
        return glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat3x2> foo() {
        return { glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat3x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3") {
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

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat3x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 map") {
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

    CHECK(f->name == "foo");
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

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 optional") {
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

    CHECK(f->name == "foo");
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

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x3 vector") {
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

    CHECK(f->name == "foo");
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

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat3x4 foo() {
        return glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat3x4> foo() {
        return { "test", glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat3x4> foo() {
        return glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0. 12.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat3x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat3x4> foo() {
        return { glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0. 12.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat3x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x2") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat4x2 foo() {
        return glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x2 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat4x2> foo() {
        return { "test", glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x2 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat4x2> foo() {
        return glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x2 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat4x2> foo() {
        return { glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat4x2);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x3") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat4x3 foo() {
        return glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x3 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat4x3> foo() {
        return { "test", glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x3 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat4x3> foo() {
        return glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x3 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat4x3> foo() {
        return { glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat4x3);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x4") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] glm::dmat4x4 foo() {
        return glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::DMat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x4 map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, glm::dmat4x4> foo() {
        return { "test", glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::DMat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x4 optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<glm::dmat4x4> foo() {
        return glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::DMat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dmat4x4 vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<glm::dmat4x4> foo() {
        return { glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0) };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::DMat4x4);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dictionary") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] ghoul::Dictionary foo() {
        return ghoul::Dictionary();
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(rt);
    CHECK(bt->type == BasicType::Type::Dictionary);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dictionary map") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::map<std::string, ghoul::Dictionary> foo() {
        return { "test", ghoul::Dictionary() };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::MapType);
    MapType* mt = static_cast<MapType*>(rt);
    REQUIRE(mt->keyType->tag == VariableType::Tag::BasicType);
    CHECK(static_cast<BasicType*>(mt->keyType)->type == BasicType::Type::String);
    CHECK(mt->valueType->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(mt->valueType);
    CHECK(bt->type == BasicType::Type::Dictionary);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dictionary optional") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::optional<ghoul::Dictionary> foo() {
        return ghoul::Dictionary();
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::OptionalType);
    OptionalType* ot = static_cast<OptionalType*>(rt);
    REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(ot->type);
    CHECK(bt->type == BasicType::Type::Dictionary);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  dictionary vector") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::vector<ghoul::Dictionary> foo() {
        return { ghoul::Dictionary() };
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VectorType);
    VectorType* vt = static_cast<VectorType*>(rt);
    REQUIRE(vt->type->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(vt->type);
    CHECK(bt->type == BasicType::Type::Dictionary);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Parsing/LuaWrapper/Return:  variant bool") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::variant<bool> foo() {
        return true;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VariantType);
    VariantType* vt = static_cast<VariantType*>(rt);
    REQUIRE(vt->types.size() == 1);
    VariableType* v = vt->types[0];
    REQUIRE(v);
    REQUIRE(v->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(v);
    CHECK(bt->type == BasicType::Type::Bool);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  variant int double") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::variant<int, double> foo() {
        return 1;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VariantType);
    VariantType* vt = static_cast<VariantType*>(rt);
    REQUIRE(vt->types.size() == 2);
    {
        VariableType* v = vt->types[0];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        VariableType* v = vt->types[1];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  variant float string path") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::variant<float, std::string, std::filesystem::path> foo() {
        return 1.f;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::VariantType);
    VariantType* vt = static_cast<VariantType*>(rt);
    REQUIRE(vt->types.size() == 3);
    {
        VariableType* v = vt->types[0];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Float);
    }
    {
        VariableType* v = vt->types[1];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::String);
    }
    {
        VariableType* v = vt->types[2];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Parsing/LuaWrapper/Return:  tuple bool") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::tuple<bool> foo() {
        return true;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::TupleType);
    TupleType* vt = static_cast<TupleType*>(rt);
    REQUIRE(vt->types.size() == 1);
    VariableType* v = vt->types[0];
    REQUIRE(v);
    REQUIRE(v->tag == VariableType::Tag::BasicType);
    BasicType* bt = static_cast<BasicType*>(v);
    CHECK(bt->type == BasicType::Type::Bool);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  tuple int double") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::tuple<int, double> foo() {
        return 1;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::TupleType);
    TupleType* vt = static_cast<TupleType*>(rt);
    REQUIRE(vt->types.size() == 2);
    {
        VariableType* v = vt->types[0];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        VariableType* v = vt->types[1];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Return:  tuple float string path") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::tuple<float, std::string, std::filesystem::path> foo() {
        return 1.f;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->arguments.size() == 0);
    VariableType* rt = f->returnValue;
    CHECK(rt->tag == VariableType::Tag::TupleType);
    TupleType* vt = static_cast<TupleType*>(rt);
    REQUIRE(vt->types.size() == 3);
    {
        VariableType* v = vt->types[0];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Float);
    }
    {
        VariableType* v = vt->types[1];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::String);
    }
    {
        VariableType* v = vt->types[2];
        REQUIRE(v);
        REQUIRE(v->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v);
        CHECK(bt->type == BasicType::Type::Path);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}
