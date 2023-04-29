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
    [[codegen::luawrap]] void funcDMat3x4(glm::dmat3x4 arg) {
        CHECK(
            arg ==
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat3x4Defaulted(glm::dmat3x4 arg = glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)) {
        CHECK(
            arg ==
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat3x4DefaultedCheck(bool isDefaulted, glm::dmat3x4 arg = glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::dmat3x4(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                    7.7, 8.8, 9.9, 10.10, 11.11, 12.12
                )
            );
        }
        else {
            CHECK(
                arg ==
                glm::dmat3x4(
                    13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                    19.19, 20.20, 21.21, 22.22, 23.23, 24.24
                )
            );
        }
    }

    [[codegen::luawrap]] void funcDMat3x4Map(std::map<std::string, glm::dmat3x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat3x4(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat3x4(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        );
    }

    [[codegen::luawrap]] void funcDMat3x4Optional(std::optional<glm::dmat3x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat3x4OptionalNullopt(std::optional<glm::dmat3x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat3x4Vector(std::vector<glm::dmat3x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
        CHECK(
            arg[1] ==
            glm::dmat3x4(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            )
        );
        CHECK(
            arg[2] ==
            glm::dmat3x4(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        );
    }

    [[codegen::luawrap]] void funcDMat3x4Array1(std::array<glm::dmat3x4, 1> arg) {
        CHECK(arg[0] == glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        ));
    }

    [[codegen::luawrap]] void funcDMat3x4Array2(std::array<glm::dmat3x4, 5> arg) {
        CHECK(arg[0] == glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        ));
        CHECK(arg[1] == glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        ));
        CHECK(arg[2] == glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        ));
        CHECK(arg[3] == glm::dmat3x4(
            37.37, 38.38, 39.39, 40.40, 41.41, 42.42,
            43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        ));
        CHECK(arg[4] == glm::dmat3x4(
            49.49, 50.50, 51.51, 52.52, 53.53, 54.54,
            55.55, 56.56, 57.57, 58.58, 59.59, 60.60
        ));
    }

    [[codegen::luawrap]] void funcDMat3x4Array3(std::array<glm::dmat3x4, 10> arg) {
        CHECK(arg[0] == glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        ));
        CHECK(arg[1] == glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        ));
        CHECK(arg[2] == glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        ));
        CHECK(arg[3] == glm::dmat3x4(
            37.37, 38.38, 39.39, 40.40, 41.41, 42.42,
            43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        ));
        CHECK(arg[4] == glm::dmat3x4(
            49.49, 50.50, 51.51, 52.52, 53.53, 54.54,
            55.55, 56.56, 57.57, 58.58, 59.59, 60.60
        ));
        CHECK(arg[5] == glm::dmat3x4(
            61.61, 62.62, 63.63, 64.64, 65.65, 66.66,
            67.67, 68.68, 69.69, 70.70, 71.71, 72.72
        ));
        CHECK(arg[6] == glm::dmat3x4(
            73.73, 74.74, 75.75, 76.76, 77.77, 78.78,
            79.79, 80.80, 81.81, 82.82, 83.83, 84.84
        ));
        CHECK(arg[7] == glm::dmat3x4(
            85.85, 86.86, 87.87, 88.88, 89.89, 90.90,
            91.91, 92.92, 93.93, 94.94, 95.95, 96.96
        ));
        CHECK(arg[8] == glm::dmat3x4(
            97.97, 98.98, 99.99, 100.100, 101.101, 102.102,
            103.103, 104.104, 105.105, 106.106, 107.107, 108.108
        ));
        CHECK(arg[9] == glm::dmat3x4(
            109.109, 110.110, 111.111, 112.112, 113.113, 114.114,
            115.115, 116.116, 117.117, 118.118, 119.119, 120.120
        ));
    }

    [[codegen::luawrap]] glm::dmat3x4 returnDMat3x4() {
        return glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::map<std::string, glm::dmat3x4> returnDMat3x4Map() {
        return {
            {
                "key1",
                glm::dmat3x4(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                    7.7, 8.8, 9.9, 10.10, 11.11, 12.12
                )
            },
            {
                "key2",
                glm::dmat3x4(
                    13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                    19.19, 20.20, 21.21, 22.22, 23.23, 24.24
                )
            },
            {
                "key3",
                glm::dmat3x4(
                    25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                    31.31, 32.32, 33.33, 34.34, 35.35, 36.36
                )
            }
        };
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x4> returnDMat3x4Optional() {
        return glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        );
    }

    [[codegen::luawrap]] std::optional<glm::dmat3x4> returnDMat3x4OptionalNullopt() {
        return std::nullopt;
    }

    [[codegen::luawrap]] std::vector<glm::dmat3x4> returnDMat3x4Vector() {
        return {
            glm::dmat3x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            ),
            glm::dmat3x4(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            ),
            glm::dmat3x4(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        };
    }
#include "execution_luawrapper_types_dmat3x4_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4;
    CHECK(func.name == "funcDMat3x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  dmat3x4Defaulted with value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::FuncDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(
        func.arguments[0].defaultValue ==
        "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)"
    );
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  dmat3x4Defaulted w/o value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::FuncDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(
        func.arguments[0].defaultValue ==
        "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)"
    );
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  dmat3x4DefaultedCheck with value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::FuncDMat3x4DefaultedCheck;
    CHECK(func.name == "funcDMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(
        func.arguments[1].defaultValue ==
        "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, "
        "10.10, 11.11, 12.12)"
    );
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  dmat3x4DefaultedCheck w/o value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::FuncDMat3x4DefaultedCheck;
    CHECK(func.name == "funcDMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(
        func.arguments[1].defaultValue ==
        "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)"
    );
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Map", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Map;
    CHECK(func.name == "funcDMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Optional", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Arguments:  dmat3x4OptionalNullopt",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::FuncDMat3x4OptionalNullopt;
    CHECK(func.name == "funcDMat3x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Vector", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Vector;
    CHECK(func.name == "funcDMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4[]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Array1", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Array1;
    CHECK(func.name == "funcDMat3x4Array1");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4[1]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Array2", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Array2;
    CHECK(func.name == "funcDMat3x4Array2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4[5]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        4,
        glm::dmat3x4(
            37.37, 38.38, 39.39, 40.40, 41.41, 42.42,
            43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        5,
        glm::dmat3x4(
            49.49, 50.50, 51.51, 52.52, 53.53, 54.54,
            55.55, 56.56, 57.57, 58.58, 59.59, 60.60
        )
    );
    lua_rawset(state, -3);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Array3", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::FuncDMat3x4Array3;
    CHECK(func.name == "funcDMat3x4Array3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4[10]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        4,
        glm::dmat3x4(
            37.37, 38.38, 39.39, 40.40, 41.41, 42.42,
            43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        5,
        glm::dmat3x4(
            49.49, 50.50, 51.51, 52.52, 53.53, 54.54,
            55.55, 56.56, 57.57, 58.58, 59.59, 60.60
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        6,
        glm::dmat3x4(
            61.61, 62.62, 63.63, 64.64, 65.65, 66.66,
            67.67, 68.68, 69.69, 70.70, 71.71, 72.72
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        7,
        glm::dmat3x4(
            73.73, 74.74, 75.75, 76.76, 77.77, 78.78,
            79.79, 80.80, 81.81, 82.82, 83.83, 84.84
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        8,
        glm::dmat3x4(
            85.85, 86.86, 87.87, 88.88, 89.89, 90.90,
            91.91, 92.92, 93.93, 94.94, 95.95, 96.96
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        9,
        glm::dmat3x4(
            97.97, 98.98, 99.99, 100.100, 101.101, 102.102,
            103.103, 104.104, 105.105, 106.106, 107.107, 108.108
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        10,
        glm::dmat3x4(
            109.109, 110.110, 111.111, 112.112, 113.113, 114.114,
            115.115, 116.116, 117.117, 118.118, 119.119, 120.120
        )
    );
    lua_rawset(state, -3);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::ReturnDMat3x4;
    CHECK(func.name == "returnDMat3x4");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x4 val = ghoul::lua::value<glm::dmat3x4>(state);
    CHECK(
        val ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Map", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::ReturnDMat3x4Map;
    CHECK(func.name == "returnDMat3x4Map");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "String -> mat3x4");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::map<std::string, glm::dmat3x4> val =
        ghoul::lua::value<std::map<std::string, glm::dmat3x4>>(state);
    CHECK(val.size() == 3);
    REQUIRE(val.find("key1") != val.end());
    CHECK(
        val.find("key1")->second ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(val.find("key2") != val.end());
    CHECK(
        val.find("key2")->second ==
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    REQUIRE(val.find("key3") != val.end());
    CHECK(
        val.find("key3")->second ==
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Return:  dmat3x4Optional with value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::ReturnDMat3x4Optional;
    CHECK(func.name == "returnDMat3x4Optional");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    glm::dmat3x4 val = ghoul::lua::value<glm::dmat3x4>(state);
    CHECK(
        val ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_close(state);
}

TEST_CASE(
    "Execution/LuaWrapper/Return:  dmat3x4Optional w/o value",
    "[Execution][LuaWrapper]"
)
{
    Function func = codegen::lua::ReturnDMat3x4OptionalNullopt;
    CHECK(func.name == "returnDMat3x4OptionalNullopt");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4?");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Return:  dmat3x4Vector", "[Execution][LuaWrapper]") {
    Function func = codegen::lua::ReturnDMat3x4Vector;
    CHECK(func.name == "returnDMat3x4Vector");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "mat3x4[]");
    CHECK(func.helpText == "");
    REQUIRE(func.function);

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    func.function(state);
    REQUIRE(lua_gettop(state) == 1);
    std::vector<glm::dmat3x4> val = ghoul::lua::value<std::vector<glm::dmat3x4>>(state);
    REQUIRE(val.size() == 3);
    CHECK(
        val[0] ==
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    CHECK(
        val[1] ==
        glm::dmat3x4(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    CHECK(
        val[2] ==
        glm::dmat3x4(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_close(state);
}
