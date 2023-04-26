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

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <openspace/scripting/lualibrary.h>
#include <ghoul/lua/lua_helper.h>
#include <ghoul/misc/dictionary.h>
#include <optional>

using Function = openspace::scripting::LuaLibrary::Function;

namespace {
    struct Foo {
        int a;
        float b;
        std::string c;
    };

    [[codegen::luawrap]] void funcVoidArg(void* arg) {
        REQUIRE(arg != nullptr);
        CHECK(arg == reinterpret_cast<void*>(1));
    }

    [[codegen::luawrap]] void funcIntArg(int* arg) {
        REQUIRE(arg != nullptr);
        CHECK(*arg == 1);
    }

    [[codegen::luawrap]] void funcStringArg(std::string* arg) {
        REQUIRE(arg != nullptr);
        CHECK(*arg == "abc");
    }

    [[codegen::luawrap]] void funcStructArg(Foo* arg) {
        REQUIRE(arg != nullptr);
        CHECK(arg->a == 1);
        CHECK(arg->b == 2.f);
        CHECK(arg->c == "abc");
    }

    [[codegen::luawrap]] void funcStruct2Arg(Foo** arg) {
        REQUIRE(arg != nullptr);
        Foo* f1 = arg[0];
        CHECK(f1->a == 1);
        CHECK(f1->b == 2.f);
        CHECK(f1->c == "abc");

        Foo* f2 = arg[1];
        CHECK(f2->a == 3);
        CHECK(f2->b == 4.f);
        CHECK(f2->c == "def");

        Foo* f3 = arg[2];
        CHECK(f3->a == 5);
        CHECK(f3->b == 6.f);
        CHECK(f3->c == "ghi");
    }

    [[codegen::luawrap]] void funcVoidDefaulted(bool isDefaulted, void* arg = nullptr) {
        if (isDefaulted) {
            CHECK(arg == nullptr);
        }
        else {
            CHECK(arg != nullptr);
            CHECK(arg == reinterpret_cast<void*>(1));
        }
    }

    [[codegen::luawrap]] void funcIntDefaulted(bool isDefaulted, int* arg = nullptr) {
        if (isDefaulted) {
            CHECK(arg == nullptr);
        }
        else {
            CHECK(arg != nullptr);
            CHECK(*arg == 1);
        }
    }

    [[codegen::luawrap]] void funcStringDefaulted(bool isDefaulted,
                                                  std::string* arg = nullptr)
    {
        if (isDefaulted) {
            CHECK(arg == nullptr);
        }
        else {
            CHECK(arg != nullptr);
            CHECK(*arg == "abc");
        }
    }

    [[codegen::luawrap]] void funcStructDefaulted(bool isDefaulted, Foo* arg = nullptr) {
        if (isDefaulted) {
            CHECK(arg == nullptr);
        }
        else {
            CHECK(arg != nullptr);
            CHECK(arg->a == 1);
            CHECK(arg->b == 2.f);
            CHECK(arg->c == "abc");
        }
    }

    [[codegen::luawrap]] void funcStruct2Defaulted(bool isDefaulted,
                                                   Foo** arg = nullptr)
    {
        if (isDefaulted) {
            CHECK(arg == nullptr);
        }
        else {
            CHECK(arg != nullptr);
            Foo* f1 = arg[0];
            CHECK(f1->a == 1);
            CHECK(f1->b == 2.f);
            CHECK(f1->c == "abc");

            Foo* f2 = arg[1];
            CHECK(f2->a == 3);
            CHECK(f2->b == 4.f);
            CHECK(f2->c == "def");

            Foo* f3 = arg[2];
            CHECK(f3->a == 5);
            CHECK(f3->b == 6.f);
            CHECK(f3->c == "ghi");
        }
    }

    [[codegen::luawrap]] void funcVoidMap(std::map<std::string, void*> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        REQUIRE(arg.find("key1")->second != nullptr);
        CHECK(arg.find("key1")->second == reinterpret_cast<void*>(1));

        REQUIRE(arg.find("key2") != arg.end());
        REQUIRE(arg.find("key2")->second != nullptr);
        CHECK(arg.find("key2")->second == reinterpret_cast<void*>(2));

        REQUIRE(arg.find("key3") != arg.end());
        REQUIRE(arg.find("key3")->second != nullptr);
        CHECK(arg.find("key3")->second == reinterpret_cast<void*>(3));
    }

    [[codegen::luawrap]] void funcIntMap(std::map<std::string, int*> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        REQUIRE(arg.find("key1")->second != nullptr);
        CHECK(*arg.find("key1")->second == 1);

        REQUIRE(arg.find("key2") != arg.end());
        REQUIRE(arg.find("key2")->second != nullptr);
        CHECK(*arg.find("key2")->second == 2);

        REQUIRE(arg.find("key3") != arg.end());
        REQUIRE(arg.find("key3")->second != nullptr);
        CHECK(*arg.find("key3")->second == 3);
    }

    [[codegen::luawrap]] void funcStringMap(std::map<std::string, std::string*> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        REQUIRE(arg.find("key1")->second != nullptr);
        CHECK(*arg.find("key1")->second == "abc");

        REQUIRE(arg.find("key2") != arg.end());
        REQUIRE(arg.find("key2")->second != nullptr);
        CHECK(*arg.find("key2")->second == "def");

        REQUIRE(arg.find("key3") != arg.end());
        REQUIRE(arg.find("key3")->second != nullptr);
        CHECK(*arg.find("key3")->second == "ghi");
    }

    [[codegen::luawrap]] void funcStructMap(std::map<std::string, Foo*> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        REQUIRE(arg.find("key1")->second != nullptr);
        CHECK(arg.find("key1")->second->a == 1);
        CHECK(arg.find("key1")->second->b == 2.f);
        CHECK(arg.find("key1")->second->c == "abc");

        REQUIRE(arg.find("key2") != arg.end());
        REQUIRE(arg.find("key2")->second != nullptr);
        CHECK(arg.find("key2")->second->a == 3);
        CHECK(arg.find("key2")->second->b == 4.f);
        CHECK(arg.find("key2")->second->c == "def");

        REQUIRE(arg.find("key3") != arg.end());
        REQUIRE(arg.find("key3")->second != nullptr);
        CHECK(arg.find("key3")->second->a == 5);
        CHECK(arg.find("key3")->second->b == 6.f);
        CHECK(arg.find("key3")->second->c == "ghi");
    }

    [[codegen::luawrap]] void funcStruct2Map(std::map<std::string, Foo**> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second != nullptr);
        CHECK(arg.find("key1")->second[0] != nullptr);
        REQUIRE(arg.find("key1")->second[0]->a == 1);
        REQUIRE(arg.find("key1")->second[0]->b == 2.f);
        REQUIRE(arg.find("key1")->second[0]->c == "abc");
        CHECK(arg.find("key1")->second[1] != nullptr);
        REQUIRE(arg.find("key1")->second[1]->a == 3);
        REQUIRE(arg.find("key1")->second[1]->b == 4.f);
        REQUIRE(arg.find("key1")->second[1]->c == "def");
        CHECK(arg.find("key1")->second[2] != nullptr);
        REQUIRE(arg.find("key1")->second[2]->a == 5);
        REQUIRE(arg.find("key1")->second[2]->b == 6.f);
        REQUIRE(arg.find("key1")->second[2]->c == "ghi");

        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second != nullptr);
        CHECK(arg.find("key2")->second[0] != nullptr);
        REQUIRE(arg.find("key2")->second[0]->a == 7);
        REQUIRE(arg.find("key2")->second[0]->b == 8.f);
        REQUIRE(arg.find("key2")->second[0]->c == "jkl");
        CHECK(arg.find("key2")->second[1] != nullptr);
        REQUIRE(arg.find("key2")->second[1]->a == 9);
        REQUIRE(arg.find("key2")->second[1]->b == 10.f);
        REQUIRE(arg.find("key2")->second[1]->c == "mno");
        CHECK(arg.find("key2")->second[2] != nullptr);
        REQUIRE(arg.find("key2")->second[2]->a == 11);
        REQUIRE(arg.find("key2")->second[2]->b == 12.f);
        REQUIRE(arg.find("key2")->second[2]->c == "pqr");

        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second != nullptr);
        CHECK(arg.find("key3")->second[0] != nullptr);
        REQUIRE(arg.find("key3")->second[0]->a == 13);
        REQUIRE(arg.find("key3")->second[0]->b == 14.f);
        REQUIRE(arg.find("key3")->second[0]->c == "stu");
        CHECK(arg.find("key3")->second[1] != nullptr);
        REQUIRE(arg.find("key3")->second[1]->a == 15);
        REQUIRE(arg.find("key3")->second[1]->b == 16.f);
        REQUIRE(arg.find("key3")->second[1]->c == "vwx");
        CHECK(arg.find("key3")->second[2] != nullptr);
        REQUIRE(arg.find("key3")->second[2]->a == 17);
        REQUIRE(arg.find("key3")->second[2]->b == 18.f);
        REQUIRE(arg.find("key3")->second[2]->c == "yzz");
    }

    [[codegen::luawrap]] void funcVoidOptional(std::optional<void*> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(*arg != nullptr);
        CHECK(*arg == reinterpret_cast<void*>(1));
    }

    [[codegen::luawrap]] void funcIntOptional(std::optional<int*> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(*arg != nullptr);
        CHECK(**arg == 1);
    }

    [[codegen::luawrap]] void funcStringOptional(std::optional<std::string*> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(*arg != nullptr);
        CHECK(**arg == "abc");
    }

    [[codegen::luawrap]] void funcStructOptional(std::optional<Foo*> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(*arg != nullptr);
        CHECK((*arg)->a == 1);
        CHECK((*arg)->b == 2.f);
        CHECK((*arg)->c == "abc");
    }

    [[codegen::luawrap]] void funcStruct2Optional(std::optional<Foo**> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(*arg != nullptr);
        Foo* f1 = (*arg)[0];
        CHECK(f1->a == 1);
        CHECK(f1->b == 2.f);
        CHECK(f1->c == "abc");

        Foo* f2 = (*arg)[1];
        CHECK(f2->a == 3);
        CHECK(f2->b == 4.f);
        CHECK(f2->c == "def");

        Foo* f3 = (*arg)[2];
        CHECK(f3->a == 5);
        CHECK(f3->b == 6.f);
        CHECK(f3->c == "ghi");
    }

    [[codegen::luawrap]] void funcVoidVector(std::vector<void*> arg) {
        REQUIRE(arg.size() == 3);
        REQUIRE(arg[0] != nullptr);
        CHECK(arg[0] == reinterpret_cast<void*>(1));

        REQUIRE(arg[1] != nullptr);
        CHECK(arg[1] == reinterpret_cast<void*>(2));

        REQUIRE(arg[2] != nullptr);
        CHECK(arg[2] == reinterpret_cast<void*>(3));
    }

    [[codegen::luawrap]] void funcIntVector(std::vector<int*> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(*arg[0] == 1);
        CHECK(*arg[1] == 2);
        CHECK(*arg[2] == 3);
    }

    [[codegen::luawrap]] void funcStringVector(std::vector<std::string*> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(*arg[0] == "abc");
        CHECK(*arg[1] == "def");
        CHECK(*arg[2] == "ghi");
    }

    [[codegen::luawrap]] void funcStructVector(std::vector<Foo*> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0]->a == 1);
        CHECK(arg[0]->b == 2.f);
        CHECK(arg[0]->c == "abc");

        CHECK(arg[1]->a == 3);
        CHECK(arg[1]->b == 4.f);
        CHECK(arg[1]->c == "def");

        CHECK(arg[2]->a == 5);
        CHECK(arg[2]->b == 6.f);
        CHECK(arg[2]->c == "ghi");
    }

    [[codegen::luawrap]] void funcStruct2Vector(std::vector<Foo**> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0][0]->a == 1);
        CHECK(arg[0][0]->b == 2.f);
        CHECK(arg[0][0]->c == "abc");
        CHECK(arg[0][1]->a == 3);
        CHECK(arg[0][1]->b == 4.f);
        CHECK(arg[0][1]->c == "def");
        CHECK(arg[0][2]->a == 5);
        CHECK(arg[0][2]->b == 6.f);
        CHECK(arg[0][2]->c == "ghi");

        CHECK(arg[1][0]->a == 7);
        CHECK(arg[1][0]->b == 8.f);
        CHECK(arg[1][0]->c == "jkl");
        CHECK(arg[1][1]->a == 9);
        CHECK(arg[1][1]->b == 10.f);
        CHECK(arg[1][1]->c == "mno");
        CHECK(arg[1][2]->a == 11);
        CHECK(arg[1][2]->b == 12.f);
        CHECK(arg[1][2]->c == "pqr");

        CHECK(arg[2][0]->a == 13);
        CHECK(arg[2][0]->b == 14.f);
        CHECK(arg[2][0]->c == "stu");
        CHECK(arg[2][1]->a == 15);
        CHECK(arg[2][1]->b == 16.f);
        CHECK(arg[2][1]->c == "vwx");
        CHECK(arg[2][2]->a == 17);
        CHECK(arg[2][2]->b == 18.f);
        CHECK(arg[2][2]->c == "yzz");
    }

    [[codegen::luawrap]] void* funcVoidReturn() {
        return reinterpret_cast<void*>(1);
    }

    [[codegen::luawrap]] int* funcIntReturn() {
        return new int(1);
    }

    [[codegen::luawrap]] std::string* funcStringReturn() {
        return new std::string("foo");
    }

    [[codegen::luawrap]] Foo* funcStructReturn() {
        return new Foo {
            .a = 1,
            .b = 2.f,
            .c = "abc"
        };
    }

    [[codegen::luawrap]] Foo** funcStruct2Return() {
        Foo** fs = new Foo*[3];

        fs[0] = new Foo {
            .a = 1,
            .b = 2.f,
            .c = "abc"
        };

        fs[1] = new Foo {
            .a = 3,
            .b = 4.f,
            .c = "def"
        };

        fs[2] = new Foo {
            .a = 5,
            .b = 6.f,
            .c = "ghi"
        };

        return fs;
    }

    [[codegen::luawrap]] std::map<std::string, void*> funcVoidReturnMap() {
        return {
            { "key1", reinterpret_cast<void*>(1) },
            { "key2", reinterpret_cast<void*>(2) },
            { "key3", reinterpret_cast<void*>(3) }
        };
    }

    [[codegen::luawrap]] std::map<std::string, int*> funcIntReturnMap() {
        return {
            { "key1", new int(1) },
            { "key2", new int(2) },
            { "key3", new int(3) }
        };
    }

    [[codegen::luawrap]] std::map<std::string, std::string*> funcStringReturnMap() {
        return {
            { "key1", new std::string("abc") },
            { "key2", new std::string("def") },
            { "key3", new std::string("ghi") }
        };
    }

    [[codegen::luawrap]] std::map<std::string, Foo*> funcStructReturnMap() {
        return {
            { "key1", new Foo { .a = 1, .b = 2.f, .c = "abc" } },
            { "key2", new Foo { .a = 3, .b = 4.f, .c = "def" } },
            { "key3", new Foo { .a = 5, .b = 6.f, .c = "ghi" } }
        };
    }

    [[codegen::luawrap]] std::map<std::string, Foo**> funcStruct2ReturnMap() {
        Foo** fs1 = new Foo*[3];
        fs1[0] = new Foo {
            .a = 1,
            .b = 2.f,
            .c = "abc"
        };

        fs1[1] = new Foo {
            .a = 3,
            .b = 4.f,
            .c = "def"
        };

        fs1[2] = new Foo {
            .a = 5,
            .b = 6.f,
            .c = "ghi"
        };

        Foo** fs2 = new Foo*[3];
        fs2[0] = new Foo {
            .a = 7,
            .b = 8.f,
            .c = "jkl"
        };

        fs2[1] = new Foo {
            .a = 9,
            .b = 10.f,
            .c = "mno"
        };

        fs2[2] = new Foo {
            .a = 11,
            .b = 12.f,
            .c = "pqr"
        };

        Foo** fs3 = new Foo*[3];
        fs3[0] = new Foo {
            .a = 13,
            .b = 14.f,
            .c = "stu"
        };

        fs3[1] = new Foo {
            .a = 15,
            .b = 16.f,
            .c = "vwx"
        };

        fs3[2] = new Foo {
            .a = 17,
            .b = 18.f,
            .c = "yzz"
        };

        return {
            { "key1", fs1 },
            { "key2", fs2 },
            { "key3", fs3 }
        };
    }

    [[codegen::luawrap]] std::optional<void*> funcVoidReturnOptional(bool shouldReturn) {
        if (shouldReturn) {
            return reinterpret_cast<void*>(1);
        }
        else {
            return std::nullopt;
        }
    }

    [[codegen::luawrap]] std::optional<int*> funcIntReturnOptional(bool shouldReturn) {
        if (shouldReturn) {
            return new int(1);
        }
        else {
            return std::nullopt;
        }
    }

    [[codegen::luawrap]] std::optional<std::string*> funcStringReturnOptional(
                                                                        bool shouldReturn)
    {
        if (shouldReturn) {
            return new std::string("abc");
        }
        else {
            return std::nullopt;
        }
    }

    [[codegen::luawrap]] std::optional<Foo*> funcStructReturnOptional(bool shouldReturn) {
        if (shouldReturn) {
            return new Foo {
                .a = 1,
                .b = 2.f,
                .c = "abc"
            };
        }
        else {
            return std::nullopt;
        }
    }

    [[codegen::luawrap]] std::optional<Foo**> funcStruct2ReturnOptional(bool shouldReturn)
    {
        if (shouldReturn) {
            Foo** fs = new Foo*[3];

            fs[0] = new Foo {
                .a = 1,
                .b = 2.f,
                .c = "abc"
            };

            fs[1] = new Foo {
                .a = 3,
                .b = 4.f,
                .c = "def"
            };

            fs[2] = new Foo {
                .a = 5,
                .b = 6.f,
                .c = "ghi"
            };

            return fs;
        }
        else {
            return std::nullopt;
        }
    }

    [[codegen::luawrap]] std::vector<void*> funcVoidReturnVector() {
        return {
            reinterpret_cast<void*>(1),
            reinterpret_cast<void*>(2),
            reinterpret_cast<void*>(3)
        };
    }

    [[codegen::luawrap]] std::vector<int*> funcIntReturnVector() {
        return {
            new int(1),
            new int(2),
            new int(3)
        };
    }

    [[codegen::luawrap]] std::vector<std::string*> funcStringReturnVector() {
        return {
            new std::string("abc"),
            new std::string("def"),
            new std::string("ghi")
        };
    }

    [[codegen::luawrap]] std::vector<Foo*> funcStructReturnVector() {
        return {
            new Foo { .a = 1, .b = 2.f, .c = "abc" },
            new Foo { .a = 3, .b = 4.f, .c = "def" },
            new Foo { .a = 5, .b = 6.f, .c = "ghi" }
        };
    }

    [[codegen::luawrap]] std::vector<Foo**> funcStruct2ReturnVector() {
        Foo** fs1 = new Foo*[3];
        fs1[0] = new Foo{
            .a = 1,
            .b = 2.f,
            .c = "abc"
        };

        fs1[1] = new Foo{
            .a = 3,
            .b = 4.f,
            .c = "def"
        };

        fs1[2] = new Foo{
            .a = 5,
            .b = 6.f,
            .c = "ghi"
        };

        Foo** fs2 = new Foo*[3];
        fs2[0] = new Foo{
            .a = 7,
            .b = 8.f,
            .c = "jkl"
        };

        fs2[1] = new Foo{
            .a = 9,
            .b = 10.f,
            .c = "mno"
        };

        fs2[2] = new Foo{
            .a = 11,
            .b = 12.f,
            .c = "pqr"
        };

        Foo** fs3 = new Foo*[3];
        fs3[0] = new Foo{
            .a = 13,
            .b = 14.f,
            .c = "stu"
        };

        fs3[1] = new Foo{
            .a = 15,
            .b = 16.f,
            .c = "vwx"
        };

        fs3[2] = new Foo{
            .a = 17,
            .b = 18.f,
            .c = "yzz"
        };

        return { fs1, fs2, fs3 };
    }

#include "execution_luawrapper_pointer_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Arguments:  void*", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncVoidArg;
    CHECK(func.name == "funcVoidArg");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "void*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, reinterpret_cast<void*>(1));
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  int*", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncIntArg;
    CHECK(func.name == "funcIntArg");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "int*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    int v = 1;
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  std::string*", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncStringArg;
    CHECK(func.name == "funcStringArg");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "std::string*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::string v = "abc";
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  Foo*", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncStructArg;
    CHECK(func.name == "funcStructArg");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v = Foo(1, 2.f, "abc");
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  Foo**", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncStruct2Arg;
    CHECK(func.name == "funcStruct2Arg");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo**");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo** v = new Foo*[3];
    v[0] = new Foo {
        .a = 1,
        .b = 2.f,
        .c = "abc"
    };

    v[1] = new Foo {
        .a = 3,
        .b = 4.f,
        .c = "def"
    };

    v[2] = new Foo {
        .a = 5,
        .b = 6.f,
        .c = "ghi"
    };

    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  void* optional with value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncVoidDefaulted;
    CHECK(func.name == "funcVoidDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "void*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, reinterpret_cast<void*>(1));
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  void* optional w/o value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncVoidDefaulted;
    CHECK(func.name == "funcVoidDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "void*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  int* optional with value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "int*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    int v = 1;
    ghoul::lua::push(state, false, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  int* optional w/o value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "int*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  std::string* optional with value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "std::string*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::string v = "abc";
    ghoul::lua::push(state, false, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  std::string* optional w/o value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "std::string*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo* optional with value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStructDefaulted;
    CHECK(func.name == "funcStructDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Foo*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v = Foo {
        .a = 1,
        .b = 2.f,
        .c = "abc"
    };
    ghoul::lua::push(state, false, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo* optional w/o value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStructDefaulted;
    CHECK(func.name == "funcStructDefaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Foo*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo** optional with value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStruct2Defaulted;
    CHECK(func.name == "funcStruct2Defaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Foo**?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo** v = new Foo*[3];
    v[0] = new Foo{
        .a = 1,
        .b = 2.f,
        .c = "abc"
    };

    v[1] = new Foo{
        .a = 3,
        .b = 4.f,
        .c = "def"
    };

    v[2] = new Foo{
        .a = 5,
        .b = 6.f,
        .c = "ghi"
    };
    ghoul::lua::push(state, false, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo** optional w/o value",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStruct2Defaulted;
    CHECK(func.name == "funcStruct2Defaulted");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Foo**?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  void* map",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncVoidMap;
    CHECK(func.name == "funcVoidMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> void*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::map<std::string, void*> v = {
        { "key1", reinterpret_cast<void*>(1) },
        { "key2", reinterpret_cast<void*>(2) },
        { "key3", reinterpret_cast<void*>(3) }
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  int* map",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncIntMap;
    CHECK(func.name == "funcIntMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> int*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    std::map<std::string, void*> v = {
        { "key1", &v1 },
        { "key2", &v2 },
        { "key3", &v3 }
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  std::string* map",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStringMap;
    CHECK(func.name == "funcStringMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> std::string*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::string v1 = "abc";
    std::string v2 = "def";
    std::string v3 = "ghi";
    std::map<std::string, std::string*> v = {
        { "key1", &v1 },
        { "key2", &v2 },
        { "key3", &v3 }
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo* map",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStructMap;
    CHECK(func.name == "funcStructMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Foo*");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v1 = Foo { .a = 1, .b = 2.f, .c = "abc" };
    Foo v2 = Foo { .a = 3, .b = 4.f, .c = "def" };
    Foo v3 = Foo { .a = 5, .b = 6.f, .c = "ghi" };
    std::map<std::string, Foo*> v = {
        { "key1", &v1 },
        { "key2", &v2 },
        { "key3", &v3 }
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo** map",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStruct2Map;
    CHECK(func.name == "funcStruct2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Foo**");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v11 = Foo { .a = 1, .b = 2.f, .c = "abc" };
    Foo v12 = Foo { .a = 3, .b = 4.f, .c = "def" };
    Foo v13 = Foo { .a = 5, .b = 6.f, .c = "ghi" };
    Foo* v1[3] = { &v11, &v12, &v13 };

    Foo v21 = Foo { .a = 7, .b = 8.f, .c = "jkl" };
    Foo v22 = Foo { .a = 9, .b = 10.f, .c = "mno" };
    Foo v23 = Foo { .a = 11, .b = 12.f, .c = "pqr" };
    Foo* v2[3] = { &v21, &v22, &v23 };

    Foo v31 = Foo { .a = 13, .b = 14.f, .c = "stu" };
    Foo v32 = Foo { .a = 15, .b = 16.f, .c = "vwx" };
    Foo v33 = Foo { .a = 17, .b = 18.f, .c = "yzz" };
    Foo* v3[3] = { &v31, &v32, &v33 };
    std::map<std::string, Foo**> v = {
        { "key1", v1 },
        { "key2", v2 },
        { "key3", v3 }
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  void* optional", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncVoidOptional;
    CHECK(func.name == "funcVoidOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "void*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, reinterpret_cast<void*>(1));
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  int* optional", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "int*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    int v = 1;
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  std::string* optional",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "std::string*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::string v = "abc";
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  Foo* optional", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncStructOptional;
    CHECK(func.name == "funcStructOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo*?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v = Foo(1, 2.f, "abc");
    ghoul::lua::push(state, &v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  Foo** optional", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncStruct2Optional;
    CHECK(func.name == "funcStruct2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo**?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo** v = new Foo*[3];
    v[0] = new Foo {
        .a = 1,
        .b = 2.f,
        .c = "abc"
    };

    v[1] = new Foo {
        .a = 3,
        .b = 4.f,
        .c = "def"
    };

    v[2] = new Foo {
        .a = 5,
        .b = 6.f,
        .c = "ghi"
    };

    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  void* vector",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncVoidVector;
    CHECK(func.name == "funcVoidVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "void*[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::vector<void*> v = {
        reinterpret_cast<void*>(1),
        reinterpret_cast<void*>(2),
        reinterpret_cast<void*>(3)
    };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  int* vector",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncIntVector;
    CHECK(func.name == "funcIntVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "int*[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    std::vector<void*> v = { &v1, &v2, &v3 };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  std::string* vector",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStringVector;
    CHECK(func.name == "funcStringVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "std::string*[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    std::string v1 = "abc";
    std::string v2 = "def";
    std::string v3 = "ghi";
    std::vector<std::string*> v = { &v1, &v2, &v3 };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo* vector",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStructVector;
    CHECK(func.name == "funcStructVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo*[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v1 = Foo { .a = 1, .b = 2.f, .c = "abc" };
    Foo v2 = Foo { .a = 3, .b = 4.f, .c = "def" };
    Foo v3 = Foo { .a = 5, .b = 6.f, .c = "ghi" };
    std::vector<Foo*> v = { &v1, &v2, &v3 };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  Foo** vector",
    "[Execution][LuaWrapper]")
{
    Function func = codegen::lua::FuncStruct2Vector;
    CHECK(func.name == "funcStruct2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Foo**[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    Foo v11 = Foo { .a = 1, .b = 2.f, .c = "abc" };
    Foo v12 = Foo { .a = 3, .b = 4.f, .c = "def" };
    Foo v13 = Foo { .a = 5, .b = 6.f, .c = "ghi" };
    Foo* v1[3] = { &v11, &v12, &v13 };

    Foo v21 = Foo { .a = 7, .b = 8.f, .c = "jkl" };
    Foo v22 = Foo { .a = 9, .b = 10.f, .c = "mno" };
    Foo v23 = Foo { .a = 11, .b = 12.f, .c = "pqr" };
    Foo* v2[3] = { &v21, &v22, &v23 };

    Foo v31 = Foo { .a = 13, .b = 14.f, .c = "stu" };
    Foo v32 = Foo { .a = 15, .b = 16.f, .c = "vwx" };
    Foo v33 = Foo { .a = 17, .b = 18.f, .c = "yzz" };
    Foo* v3[3] = { &v31, &v32, &v33 };
    std::vector<Foo**> v = { v1, v2, v3 };
    ghoul::lua::push(state, v);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}
