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

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <openspace/scripting/lualibrary.h>
#include <ghoul/lua/lua_helper.h>
#include <ghoul/misc/dictionary.h>
#include <optional>

namespace {
    bool ranTestFunc = false;
    [[codegen::luawrap]] void testFunc() {
        ranTestFunc = true;
    }

    bool ranTestFunc2 = false;
    int testFunc2Value = -1;
    [[codegen::luawrap]] void testFunc2(int arg) {
        testFunc2Value = arg;
        ranTestFunc2 = true;
    }

    bool ranTestFunc3 = false;
    int testFunc3Value1 = -1;
    std::string testFunc3Value2 = "";
    [[codegen::luawrap]] void testFunc3(int arg1, std::string arg2) {
        testFunc3Value1 = arg1;
        testFunc3Value2 = std::move(arg2);
        ranTestFunc3 = true;
    }

    bool ranTestFunc4 = false;
    int testFunc4Value1 = -1;
    double testFunc4Value2 = -1.0;
    [[codegen::luawrap]] void testFunc4(int arg1, std::optional<double> arg2) {
        testFunc4Value1 = arg1;
        testFunc4Value2 = arg2.value_or(testFunc4Value2);
        ranTestFunc4 = true;
    }

    bool ranTestFunc5 = false;
    [[codegen::luawrap]] int testFunc5() {
        ranTestFunc5 = true;
        return 5;
    }

    bool ranTestFunc6 = false;
    [[codegen::luawrap]] std::tuple<int, double> testFunc6() {
        ranTestFunc6 = true;
        return { 5, 6.0 };
    }

    void resetTestRuns() {
        ranTestFunc = false;

        ranTestFunc2 = false;
        testFunc2Value = -1;

        ranTestFunc3 = false;
        testFunc3Value1 = -1;
        testFunc3Value2.clear();

        ranTestFunc4 = false;
        testFunc4Value1 = -1;
        testFunc4Value2 = -1.0;

        ranTestFunc5 = false;
        ranTestFunc6 = false;
    }

#include "execution_luawrapper_basic_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper:  Basic") {
    using namespace openspace::scripting;
    resetTestRuns();

    SECTION("TestFunc") {
        LuaLibrary::Function func = codegen::lua::testFunc;
        CHECK(func.name == "testFunc");
        CHECK(func.arguments.size() == 0);
        CHECK(func.returnType == "");
        CHECK(func.helpText == "");

        lua_State* state = luaL_newstate();
        REQUIRE(state);
        REQUIRE(func.function);
        func.function(state);
        CHECK(ranTestFunc);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }

    SECTION("TestFunc2") {
        LuaLibrary::Function func = codegen::lua::testFunc2;
        CHECK(func.name == "testFunc2");
        REQUIRE(func.arguments.size() == 1);
        {
            CHECK(func.arguments[0].name == "arg");
            CHECK(func.arguments[0].type == "Integer");
        }
        CHECK(func.returnType == "");
        CHECK(func.helpText == "");

        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2);
        REQUIRE(func.function);
        func.function(state);
        CHECK(ranTestFunc2);
        CHECK(testFunc2Value == 2);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }

    SECTION("TestFunc3") {
        LuaLibrary::Function func = codegen::lua::testFunc3;
        CHECK(func.name == "testFunc3");
        REQUIRE(func.arguments.size() == 2);
        {
            CHECK(func.arguments[0].name == "arg1");
            CHECK(func.arguments[0].type == "Integer");
        }
        {
            CHECK(func.arguments[1].name == "arg2");
            CHECK(func.arguments[1].type == "String");
        }
        CHECK(func.returnType == "");
        CHECK(func.helpText == "");
        
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2, std::string("test"));
        REQUIRE(func.function);
        func.function(state);
        CHECK(ranTestFunc3);
        CHECK(testFunc3Value1 == 2);
        CHECK(testFunc3Value2 == "test");
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }

    SECTION("TestFunc4/All Arguments") {
        LuaLibrary::Function func = codegen::lua::testFunc4;
        CHECK(func.name == "testFunc4");
        REQUIRE(func.arguments.size() == 2);
        {
            CHECK(func.arguments[0].name == "arg1");
            CHECK(func.arguments[0].type == "Integer");
        }
        {
            CHECK(func.arguments[1].name == "arg2");
            CHECK(func.arguments[1].type == "Number?");
        }
        CHECK(func.returnType == "");
        CHECK(func.helpText == "");
        
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2, 3.0);
        REQUIRE(func.function);
        func.function(state);
        CHECK(ranTestFunc4);
        CHECK(testFunc4Value1 == 2);
        CHECK(testFunc4Value2 == 3.0);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }

    SECTION("TestFunc4/No Optional") {
        LuaLibrary::Function func = codegen::lua::testFunc4;
        CHECK(func.name == "testFunc4");
        REQUIRE(func.arguments.size() == 2);
        {
            CHECK(func.arguments[0].name == "arg1");
            CHECK(func.arguments[0].type == "Integer");
        }
        {
            CHECK(func.arguments[1].name == "arg2");
            CHECK(func.arguments[1].type == "Number?");
        }
        CHECK(func.returnType == "");
        CHECK(func.helpText == "");
        
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2);
        REQUIRE(func.function);
        func.function(state);
        CHECK(ranTestFunc4);
        CHECK(testFunc4Value1 == 2);
        CHECK(testFunc4Value2 == -1.0);
        lua_close(state);
    }

    SECTION("Basic/TestFunc5") {
        LuaLibrary::Function func = codegen::lua::testFunc5;
        CHECK(func.name == "testFunc5");
        CHECK(func.arguments.size() == 0);
        CHECK(func.returnType == "Integer");
        CHECK(func.helpText == "");
        
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        REQUIRE(func.function);
        const int nResult = func.function(state);
        CHECK(ranTestFunc5);
        CHECK(lua_gettop(state) == 1);
        REQUIRE(nResult == 1);
        const int value = ghoul::lua::value<int>(state);
        CHECK(value == 5);
        lua_close(state);
    }

    SECTION("Basic/TestFunc6") {
        LuaLibrary::Function func = codegen::lua::testFunc6;
        CHECK(func.name == "testFunc6");
        CHECK(func.arguments.size() == 0);
        CHECK(func.returnType == "Integer, Number");
        CHECK(func.helpText == "");
        
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        REQUIRE(func.function);
        const int nResult = func.function(state);
        CHECK(ranTestFunc6);
        CHECK(lua_gettop(state) == 2);
        REQUIRE(nResult == 2);
        const auto [res1, res2] = ghoul::lua::values<int, double>(state);
        CHECK(res1 == 5);
        CHECK(res2 == 6.0);
        lua_close(state);
    }
}
