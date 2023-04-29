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
#include <array>
#include <optional>

using Function = openspace::scripting::LuaLibrary::Function;

namespace {
    [[codegen::luawrap]] std::tuple<glm::dvec3> returnTupleVec3() {
        return glm::dvec3(1.1, 2.2, 3.3);
    }

    [[codegen::luawrap]] std::tuple<bool, int> returnTupleBoolInt() {
        return { true, 1 };
    }

    [[codegen::luawrap]] std::tuple<double, float, std::string> returnTupleDoubleFloatStringDouble() {
        return { 1.1, 2.2f, "abc" };
    }
#include "execution_luawrapper_types_tuple_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Return:  tuple(vec3)", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::ReturnTupleVec3;
    CHECK(func.name == "returnTupleVec3");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "vec3");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::tuple<glm::dvec3> val = ghoul::lua::values<glm::dvec3>(state);
    CHECK(std::get<0>(val) == glm::dvec3(1.1, 2.2, 3.3));
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  tuple(bool,int)", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::ReturnTupleBoolInt;
    CHECK(func.name == "returnTupleBoolInt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Boolean, Integer");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 2);
    std::tuple<bool, int> val = ghoul::lua::values<bool, int>(state);
    CHECK(std::get<0>(val) == true);
    CHECK(std::get<1>(val) == 1);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Return:  tuple(double,float,string)",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::ReturnTupleDoubleFloatStringDouble;
    CHECK(func.name == "returnTupleDoubleFloatStringDouble");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "Number, Number, String");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 3);
    std::tuple<double, float, std::string> val =
        ghoul::lua::values<double, float, std::string>(state);
    CHECK(std::get<0>(val) == 1.1);
    CHECK(std::get<1>(val) == 2.2f);
    CHECK(std::get<2>(val) == "abc");
    lua_close(state);
}
