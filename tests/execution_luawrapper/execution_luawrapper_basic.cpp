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
    [[codegen::wraplua]] void testFunc() {
        ranTestFunc = true;
    }

    bool ranTestFunc2 = false;
    int testFunc2Value = -1;
    [[codegen::wraplua]] void testFunc2(int arg) {
        testFunc2Value = arg;
        ranTestFunc2 = true;
    }

    bool ranTestFunc3 = false;
    int testFunc3Value1 = -1;
    std::string testFunc3Value2 = "";
    [[codegen::wraplua]] void testFunc3(int arg1, std::string arg2) {
        testFunc3Value1 = arg1;
        testFunc3Value2 = std::move(arg2);
        ranTestFunc3 = true;
    }

    bool ranTestFunc4 = false;
    int testFunc4Value1 = -1;
    double testFunc4Value2 = -1.0;
    [[codegen::wraplua]] void testFunc4(int arg1, std::optional<double> arg2) {
        testFunc4Value1 = arg1;
        testFunc4Value2 = arg2.value_or(testFunc4Value2);
        ranTestFunc4 = true;
    }

    bool ranTestFunc5 = false;
    [[codegen::wraplua]] int testFunc5() {
        ranTestFunc5 = true;
        return 5;
    }

    bool ranTestFunc6 = false;
    [[codegen::wraplua]] std::tuple<int, double> testFunc6() {
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

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc", "[luawrapper][execution]") {
    resetTestRuns();
    
    CHECK(codegen::lua::testFunc.name == "testFunc");
    CHECK(codegen::lua::testFunc.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        codegen::lua::testFunc.function(state);
        CHECK(ranTestFunc);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }

}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc2", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc2.name == "testFunc2");
    CHECK(codegen::lua::testFunc2.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2);
        codegen::lua::testFunc2.function(state);
        CHECK(ranTestFunc2);
        CHECK(testFunc2Value == 2);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }
}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc3", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc3.name == "testFunc3");
    CHECK(codegen::lua::testFunc3.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2, std::string("test"));
        codegen::lua::testFunc3.function(state);
        CHECK(ranTestFunc3);
        CHECK(testFunc3Value1 == 2);
        CHECK(testFunc3Value2 == "test");
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }
}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc4/All Arguments", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc4.name == "testFunc4");
    CHECK(codegen::lua::testFunc4.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2, 3.0);
        codegen::lua::testFunc4.function(state);
        CHECK(ranTestFunc4);
        CHECK(testFunc4Value1 == 2);
        CHECK(testFunc4Value2 == 3.0);
        CHECK(lua_gettop(state) == 0);
        lua_close(state);
    }
}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc4/No Optional", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc4.name == "testFunc4");
    CHECK(codegen::lua::testFunc4.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        ghoul::lua::push(state, 2);
        codegen::lua::testFunc4.function(state);
        CHECK(ranTestFunc4);
        CHECK(testFunc4Value1 == 2);
        CHECK(testFunc4Value2 == -1.0);
        lua_close(state);
    }
}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc5", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc5.name == "testFunc5");
    CHECK(codegen::lua::testFunc5.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        const int nResult = codegen::lua::testFunc5.function(state);
        CHECK(ranTestFunc5);
        CHECK(lua_gettop(state) == 1);
        REQUIRE(nResult == 1);
        const int value = ghoul::lua::value<int>(state);
        CHECK(value == 5);
        lua_close(state);
    }
}

TEST_CASE("Execution/LuaWrapper/Basic/TestFunc6", "[luawrapper][execution]") {
    resetTestRuns();

    CHECK(codegen::lua::testFunc6.name == "testFunc6");
    CHECK(codegen::lua::testFunc6.function);
    {
        lua_State* state = luaL_newstate();
        REQUIRE(state);
        const int nResult = codegen::lua::testFunc6.function(state);
        CHECK(ranTestFunc6);
        CHECK(lua_gettop(state) == 2);
        REQUIRE(nResult == 2);
        const auto [res1, res2] = ghoul::lua::values<int, double>(state);
        CHECK(res1 == 5);
        CHECK(res2 == 6.0);
        lua_close(state);
    }
}
