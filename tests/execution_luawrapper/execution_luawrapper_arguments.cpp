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
    [[codegen::luawrap]] void funcVoid() {
    }

    [[codegen::luawrap]] void funcBool(bool arg) {
        CHECK(arg == true);
    }

    [[codegen::luawrap]] void funcBoolDefaulted(bool arg = true) {
        CHECK(arg == true);
    }

    [[codegen::luawrap]] void funcBoolDefaultedCheck(bool isDefaulted, bool arg = true) {
        if (isDefaulted) {
            CHECK(arg == true);
        }
        else {
            CHECK(arg == false);
        }
    }

    [[codegen::luawrap]] void funcBoolMap(std::map<std::string, bool> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == true);
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == false);
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == false);
    }

    [[codegen::luawrap]] void funcBoolOptional(std::optional<bool> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == true);
    }

    [[codegen::luawrap]] void funcBoolOptionalNullopt(std::optional<bool> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcBoolVector(std::vector<bool> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == true);
        CHECK(arg[1] == false);
        CHECK(arg[2] == false);
    }

    [[codegen::luawrap]] void funcInt(int arg) {
        CHECK(arg == 1);
    }

    [[codegen::luawrap]] void funcIntDefaulted(int arg = 2) {
        CHECK(arg == 2);
    }

    [[codegen::luawrap]] void funcIntDefaultedCheck(bool isDefaulted, int arg = 2) {
        if (isDefaulted) {
            CHECK(arg == 2);
        }
        else {
            CHECK(arg == 3);
        }
    }

    [[codegen::luawrap]] void funcIntMap(std::map<std::string, int> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == 1);
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == 2);
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == 3);
    }

    [[codegen::luawrap]] void funcIntOptional(std::optional<int> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == 1);
    }

    [[codegen::luawrap]] void funcIntOptionalNullopt(std::optional<int> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcIntVector(std::vector<int> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == 1);
        CHECK(arg[1] == 2);
        CHECK(arg[2] == 3);
    }

    [[codegen::luawrap]] void funcDouble(double arg) {
        CHECK(arg == 1.1);
    }

    [[codegen::luawrap]] void funcDoubleDefaulted(double arg = 2.2) {
        CHECK(arg == 2.2);
    }

    [[codegen::luawrap]] void funcDoubleDefaultedCheck(bool isDefaulted, double arg = 2.2) {
        if (isDefaulted) {
            CHECK(arg == 2.2);
        }
        else {
            CHECK(arg == 3.3);
        }
    }

    [[codegen::luawrap]] void funcDoubleMap(std::map<std::string, double> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == 1.1);
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == 2.2);
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == 3.3);
    }

    [[codegen::luawrap]] void funcDoubleOptional(std::optional<double> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == 1.1);
    }

    [[codegen::luawrap]] void funcDoubleOptionalNullopt(std::optional<double> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDoubleVector(std::vector<double> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == 1.1);
        CHECK(arg[1] == 2.2);
        CHECK(arg[2] == 3.3);
    }

    [[codegen::luawrap]] void funcFloat(float arg) {
        CHECK(arg == 1.1f);
    }

    [[codegen::luawrap]] void funcFloatDefaulted(float arg = 1.1f) {
        CHECK(arg == 1.1f);
    }

    [[codegen::luawrap]] void funcFloatDefaultedCheck(bool isDefaulted, float arg = 2.2f) {
        if (isDefaulted) {
            CHECK(arg == 2.2f);
        }
        else {
            CHECK(arg == 3.3f);
        }
    }

    [[codegen::luawrap]] void funcFloatMap(std::map<std::string, float> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == 1.1f);
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == 2.2f);
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == 3.3f);
    }

    [[codegen::luawrap]] void funcFloatOptional(std::optional<float> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == 1.1f);
    }

    [[codegen::luawrap]] void funcFloatOptionalNullopt(std::optional<float> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcFloatVector(std::vector<float> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == 1.1f);
        CHECK(arg[1] == 2.2f);
        CHECK(arg[2] == 3.3f);
    }

    [[codegen::luawrap]] void funcString(std::string arg) {
        CHECK(arg == "abc");
    }

    [[codegen::luawrap]] void funcStringDefaulted(std::string arg = "abc") {
        CHECK(arg == "abc");
    }

    [[codegen::luawrap]] void funcStringDefaultedCheck(bool isDefaulted, std::string arg = "abc") {
        if (isDefaulted) {
            CHECK(arg == "abc");
        }
        else {
            CHECK(arg == "def");
        }
    }

    [[codegen::luawrap]] void funcStringMap(std::map<std::string, std::string> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == "abc");
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == "def");
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == "ghi");
    }

    [[codegen::luawrap]] void funcStringOptional(std::optional<std::string> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == "abc");
    }

    [[codegen::luawrap]] void funcStringOptionalNullopt(std::optional<std::string> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcStringVector(std::vector<std::string> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == "abc");
        CHECK(arg[1] == "def");
        CHECK(arg[2] == "ghi");
    }

    [[codegen::luawrap]] void funcPath(std::filesystem::path arg) {
        CHECK(arg == std::filesystem::path("abc"));
    }

    [[codegen::luawrap]] void funcPathDefaulted(std::filesystem::path arg = std::filesystem::path("abc")) {
        CHECK(arg == std::filesystem::path("abc"));
    }

    [[codegen::luawrap]] void funcPathDefaultedCheck(bool isDefaulted, std::filesystem::path arg = std::filesystem::path("abc")) {
        if (isDefaulted) {
            CHECK(arg == std::filesystem::path("abc"));
        }
        else {
            CHECK(arg == std::filesystem::path("def"));
        }
    }

    [[codegen::luawrap]] void funcPathMap(std::map<std::string, std::filesystem::path> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == std::filesystem::path("abc"));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == std::filesystem::path("def"));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == std::filesystem::path("ghi"));
    }

    [[codegen::luawrap]] void funcPathOptional(std::optional<std::filesystem::path> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == "abc");
    }

    [[codegen::luawrap]] void funcPathOptionalNullopt(std::optional<std::filesystem::path> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcPathVector(std::vector<std::filesystem::path> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == std::filesystem::path("abc"));
        CHECK(arg[1] == std::filesystem::path("def"));
        CHECK(arg[2] == std::filesystem::path("ghi"));
    }

    [[codegen::luawrap]] void funcIvec2(glm::ivec2 arg) {
        CHECK(arg == glm::ivec2(1, 2));
    }

    [[codegen::luawrap]] void funcIvec2Defaulted(glm::ivec2 arg = glm::ivec2(1, 2)) {
        CHECK(arg == glm::ivec2(1, 2));
    }

    [[codegen::luawrap]] void funcIvec2DefaultedCheck(bool isDefaulted, glm::ivec2 arg = glm::ivec2(1, 2)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec2(1, 2));
        }
        else {
            CHECK(arg == glm::ivec2(2, 3));
        }
    }

    [[codegen::luawrap]] void funcIvec2Map(std::map<std::string, glm::ivec2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::ivec2(1, 2));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::ivec2(3, 4));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::ivec2(5, 6));
    }

    [[codegen::luawrap]] void funcIvec2Optional(std::optional<glm::ivec2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::ivec2(1, 2));
    }

    [[codegen::luawrap]] void funcIvec2OptionalNullopt(std::optional<glm::ivec2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcIvec2Vector(std::vector<glm::ivec2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::ivec2(1, 2));
        CHECK(arg[1] == glm::ivec2(3, 4));
        CHECK(arg[2] == glm::ivec2(5, 6));
    }

    [[codegen::luawrap]] void funcIvec3(glm::ivec3 arg) {
        CHECK(arg == glm::ivec3(1, 2, 3));
    }

    [[codegen::luawrap]] void funcIvec3Defaulted(glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
        CHECK(arg == glm::ivec3(1, 2, 3));
    }

    [[codegen::luawrap]] void funcIvec3DefaultedCheck(bool isDefaulted, glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec3(1, 2, 3));
        }
        else {
            CHECK(arg == glm::ivec3(4, 5, 6));
        }
    }

    [[codegen::luawrap]] void funcIvec3Map(std::map<std::string, glm::ivec3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::ivec3(1, 2, 3));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::ivec3(4, 5, 6));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::ivec3(7, 8, 9));
    }

    [[codegen::luawrap]] void funcIvec3Optional(std::optional<glm::ivec3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::ivec3(1, 2, 3));
    }

    [[codegen::luawrap]] void funcIvec3OptionalNullopt(std::optional<glm::ivec3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcIvec3Vector(std::vector<glm::ivec3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::ivec3(1, 2, 3));
        CHECK(arg[1] == glm::ivec3(4, 5, 6));
        CHECK(arg[2] == glm::ivec3(7, 8, 9));
    }

    [[codegen::luawrap]] void funcIvec4(glm::ivec4 arg) {
        CHECK(arg == glm::ivec4(1, 2, 3, 4));
    }

    [[codegen::luawrap]] void funcIvec4Defaulted(glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
        CHECK(arg == glm::ivec4(1, 2, 3, 4));
    }

    [[codegen::luawrap]] void funcIvec4DefaultedCheck(bool isDefaulted, glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec4(1, 2, 3, 4));
        }
        else {
            CHECK(arg == glm::ivec4(5, 6, 7, 8));
        }
    }

    [[codegen::luawrap]] void funcIvec4Map(std::map<std::string, glm::ivec4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::ivec4(1, 2, 3, 4));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::ivec4(5, 6, 7, 8));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::ivec4(9, 10, 11, 12));
    }

    [[codegen::luawrap]] void funcIvec4Optional(std::optional<glm::ivec4> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::ivec4(1, 2, 3, 4));
    }

    [[codegen::luawrap]] void funcIvec4OptionalNullopt(std::optional<glm::ivec4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcIvec4Vector(std::vector<glm::ivec4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::ivec4(1, 2, 3, 4));
        CHECK(arg[1] == glm::ivec4(5, 6, 7, 8));
        CHECK(arg[2] == glm::ivec4(9, 10, 11, 12));
    }

    [[codegen::luawrap]] void funcDvec2(glm::dvec2 arg) {
        CHECK(arg == glm::dvec2(1.1, 2.2));
    }

    [[codegen::luawrap]] void funcDvec2Defaulted(glm::dvec2 arg = glm::dvec2(1.1, 2.2)) {
        CHECK(arg == glm::dvec2(1.1, 2.2));
    }

    [[codegen::luawrap]] void funcDvec2DefaultedCheck(bool isDefaulted, glm::dvec2 arg = glm::dvec2(1.1, 2.2)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec2(1.1, 2.2));
        }
        else {
            CHECK(arg == glm::dvec2(3.3, 4.4));
        }
    }

    [[codegen::luawrap]] void funcDvec2Map(std::map<std::string, glm::dvec2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::dvec2(1.1, 2.2));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::dvec2(3.3, 4.4));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::dvec2(5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDvec2Optional(std::optional<glm::dvec2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dvec2(1.1, 2.2));
    }

    [[codegen::luawrap]] void funcDvec2OptionalNullopt(std::optional<glm::dvec2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDvec2Vector(std::vector<glm::dvec2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dvec2(1.1, 2.2));
        CHECK(arg[1] == glm::dvec2(3.3, 4.4));
        CHECK(arg[2] == glm::dvec2(5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDvec3(glm::dvec3 arg) {
        CHECK(arg == glm::dvec3(1.1, 2.2, 3.3));
    }

    [[codegen::luawrap]] void funcDvec3Defaulted(glm::dvec3 arg = glm::dvec3(1.1, 2.2, 3.3)) {
        CHECK(arg == glm::dvec3(1.1, 2.2, 3.3));
    }

    [[codegen::luawrap]] void funcDvec3DefaultedCheck(bool isDefaulted, glm::dvec3 arg = glm::dvec3(1.1, 2.2, 3.3)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec3(1.1, 2.2, 3.3));
        }
        else {
            CHECK(arg == glm::dvec3(4.4, 5.5, 6.6));

        }
    }

    [[codegen::luawrap]] void funcDvec3Map(std::map<std::string, glm::dvec3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::dvec3(1.1, 2.2, 3.3));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::dvec3(4.4, 5.5, 6.6));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::dvec3(7.7, 8.8, 9.9));
    }

    [[codegen::luawrap]] void funcDvec3Optional(std::optional<glm::dvec3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dvec3(1.1, 2.2, 3.3));
    }

    [[codegen::luawrap]] void funcDvec3OptionalNullopt(std::optional<glm::dvec3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDvec3Vector(std::vector<glm::dvec3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dvec3(1.1, 2.2, 3.3));
        CHECK(arg[1] == glm::dvec3(4.4, 5.5, 6.6));
        CHECK(arg[2] == glm::dvec3(7.7, 8.8, 9.9));
    }

    [[codegen::luawrap]] void funcDvec4(glm::dvec4 arg) {
        CHECK(arg == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDvec4Defaulted(glm::dvec4 arg = glm::dvec4(1.1, 2.2, 3.3, 4.4)) {
        CHECK(arg == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDvec4DefaultedCheck(bool isDefaulted, glm::dvec4 arg = glm::dvec4(1.1, 2.2, 3.3, 4.4)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec4(1.1, 2.2, 3.3, 4.4));
        }
        else {
            CHECK(arg == glm::dvec4(5.5, 6.6, 7.7, 8.8));

        }
    }

    [[codegen::luawrap]] void funcDvec4Map(std::map<std::string, glm::dvec4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::dvec4(1.1, 2.2, 3.3, 4.4));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::dvec4(5.5, 6.6, 7.7, 8.8));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::dvec4(9.9, 10.10, 11.11, 12.12));
    }

    [[codegen::luawrap]] void funcDvec4Optional(std::optional<glm::dvec4> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dvec4(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDvec4OptionalNullopt(std::optional<glm::dvec4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDvec4Vector(std::vector<glm::dvec4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dvec4(1.1, 2.2, 3.3, 4.4));
        CHECK(arg[1] == glm::dvec4(5.5, 6.6, 7.7, 8.8));
        CHECK(arg[2] == glm::dvec4(9.9, 10.10, 11.11, 12.12));
    }

    [[codegen::luawrap]] void funcVec2(glm::vec2 arg) {
        CHECK(arg == glm::vec2(1.1f, 2.2f));
    }

    [[codegen::luawrap]] void funcVec2Defaulted(glm::vec2 arg = glm::vec2(1.1f, 2.2f)) {
        CHECK(arg == glm::vec2(1.1f, 2.2f));
    }

    [[codegen::luawrap]] void funcVec2DefaultedCheck(bool isDefaulted, glm::vec2 arg = glm::vec2(1.1f, 2.2f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec2(1.1f, 2.2f));
        }
        else {
            CHECK(arg == glm::vec2(3.3f, 4.4f));
        }
    }

    [[codegen::luawrap]] void funcVec2Map(std::map<std::string, glm::vec2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::vec2(1.1f, 2.2f));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::vec2(3.3f, 4.4f));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::vec2(5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcVec2Optional(std::optional<glm::vec2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::vec2(1.1f, 2.2f));
    }

    [[codegen::luawrap]] void funcVec2OptionalNullopt(std::optional<glm::vec2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcVec2Vector(std::vector<glm::vec2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::vec2(1.1f, 2.2f));
        CHECK(arg[1] == glm::vec2(3.3f, 4.4f));
        CHECK(arg[2] == glm::vec2(5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcVec3(glm::vec3 arg) {
        CHECK(arg == glm::vec3(1.1f, 2.2f, 3.3f));
    }

    [[codegen::luawrap]] void funcVec3Defaulted(glm::vec3 arg = glm::vec3(1.1f, 2.2f, 3.3f)) {
        CHECK(arg == glm::vec3(1.1f, 2.2f, 3.3f));
    }

    [[codegen::luawrap]] void funcVec3DefaultedCheck(bool isDefaulted, glm::vec3 arg = glm::vec3(1.1f, 2.2f, 3.3f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec3(1.1f, 2.2f, 3.3f));
        }
        else {
            CHECK(arg == glm::vec3(4.4f, 5.5f, 6.6f));
        }
    }

    [[codegen::luawrap]] void funcVec3Map(std::map<std::string, glm::vec3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::vec3(1.1f, 2.2f, 3.3f));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::vec3(4.4f, 5.5f, 6.6f));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::vec3(7.7f, 8.8f, 9.9f));
    }

    [[codegen::luawrap]] void funcVec3Optional(std::optional<glm::vec3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::vec3(1.1f, 2.2f, 3.3f));
    }

    [[codegen::luawrap]] void funcVec3OptionalNullopt(std::optional<glm::vec3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcVec3Vector(std::vector<glm::vec3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::vec3(1.1f, 2.2f, 3.3f));
        CHECK(arg[1] == glm::vec3(4.4f, 5.5f, 6.6f));
        CHECK(arg[2] == glm::vec3(7.7f, 8.8f, 9.9f));
    }

    [[codegen::luawrap]] void funcVec4(glm::vec4 arg) {
        CHECK(arg == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcVec4Defaulted(glm::vec4 arg = glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)) {
        CHECK(arg == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcVec4DefaultedCheck(bool isDefaulted, glm::vec4 arg = glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
        }
        else {
            CHECK(arg == glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
        }
    }

    [[codegen::luawrap]] void funcVec4Map(std::map<std::string, glm::vec4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    }

    [[codegen::luawrap]] void funcVec4Optional(std::optional<glm::vec4> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcVec4OptionalNullopt(std::optional<glm::vec4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcVec4Vector(std::vector<glm::vec4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
        CHECK(arg[1] == glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
        CHECK(arg[2] == glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    }

    [[codegen::luawrap]] void funcMat2x2(glm::mat2x2 arg) {
        CHECK(arg == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcMat2x2Defaulted(glm::mat2x2 arg = glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)) {
        CHECK(arg == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcMat2x2DefaultedCheck(bool isDefaulted, glm::mat2x2 arg = glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
        }
        else {
            CHECK(arg == glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
        }
    }

    [[codegen::luawrap]] void funcMat2x2Map(std::map<std::string, glm::mat2x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    }

    [[codegen::luawrap]] void funcMat2x2Optional(std::optional<glm::mat2x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    }

    [[codegen::luawrap]] void funcMat2x2OptionalNullopt(std::optional<glm::mat2x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat2x2Vector(std::vector<glm::mat2x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
        CHECK(arg[1] == glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
        CHECK(arg[2] == glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    }

    [[codegen::luawrap]] void funcMat2x3(glm::mat2x3 arg) {
        CHECK(arg == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat2x3Defaulted(glm::mat2x3 arg = glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)) {
        CHECK(arg == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat2x3DefaultedCheck(bool isDefaulted, glm::mat2x3 arg = glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
        }
        else {
            CHECK(arg == glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
        }
    }

    [[codegen::luawrap]] void funcMat2x3Map(std::map<std::string, glm::mat2x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
        );
    }

    [[codegen::luawrap]] void funcMat2x3Optional(std::optional<glm::mat2x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat2x3OptionalNullopt(std::optional<glm::mat2x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat2x3Vector(std::vector<glm::mat2x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
        CHECK(arg[1] == glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
        CHECK(arg[2] == glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f));
    }

    [[codegen::luawrap]] void funcMat2x4(glm::mat2x4 arg) {
        CHECK(arg == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    }

    [[codegen::luawrap]] void funcMat2x4Defaulted(glm::mat2x4 arg = glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)) {
        CHECK(arg == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    }

    [[codegen::luawrap]] void funcMat2x4DefaultedCheck(bool isDefaulted, glm::mat2x4 arg = glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
        }
        else {
            CHECK(
                arg ==
                glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
            );
        }
    }

    [[codegen::luawrap]] void funcMat2x4Map(std::map<std::string, glm::mat2x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
        );
    }

    [[codegen::luawrap]] void funcMat2x4Optional(std::optional<glm::mat2x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    }

    [[codegen::luawrap]] void funcMat2x4OptionalNullopt(std::optional<glm::mat2x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat2x4Vector(std::vector<glm::mat2x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
        CHECK(
            arg[1] ==
            glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
        );
        CHECK(
            arg[2] ==
            glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
        );
    }

    [[codegen::luawrap]] void funcMat3x2(glm::mat3x2 arg) {
        CHECK(arg == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat3x2Defaulted(glm::mat3x2 arg = glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)) {
        CHECK(arg == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat3x2DefaultedCheck(bool isDefaulted, glm::mat3x2 arg = glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
        }
        else {
            CHECK(arg == glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
        }
    }

    [[codegen::luawrap]] void funcMat3x2Map(std::map<std::string, glm::mat3x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
        );
    }

    [[codegen::luawrap]] void funcMat3x2Optional(std::optional<glm::mat3x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    }

    [[codegen::luawrap]] void funcMat3x2OptionalNullopt(std::optional<glm::mat3x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat3x2Vector(std::vector<glm::mat3x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
        CHECK(arg[1] == glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
        CHECK(arg[2] == glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f));
    }

    [[codegen::luawrap]] void funcMat3x3(glm::mat3x3 arg) {
        CHECK(arg == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5, 6.6f, 7.7f, 8.8f, 9.9f));
    }

    [[codegen::luawrap]] void funcMat3x3Defaulted(glm::mat3x3 arg = glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)) {
        CHECK(arg == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f));
    }

    [[codegen::luawrap]] void funcMat3x3DefaultedCheck(bool isDefaulted, glm::mat3x3 arg = glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
            );
        }
        else {
            CHECK(
                arg ==
                glm::mat3x3(
                    10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
                    15.15f, 16.16f, 17.17f, 18.18f
                )
            );
        }
    }

    [[codegen::luawrap]] void funcMat3x3Map(std::map<std::string, glm::mat3x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat3x3(
                10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
                15.15f, 16.16f, 17.17f, 18.18f
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat3x3(
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
                24.24f, 25.25f, 26.26f, 27.27f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x3Optional(std::optional<glm::mat3x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f));
    }

    [[codegen::luawrap]] void funcMat3x3OptionalNullopt(std::optional<glm::mat3x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat3x3Vector(std::vector<glm::mat3x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
        );
        CHECK(
            arg[1] ==
            glm::mat3x3(
                10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
                15.15f, 16.16f, 17.17f, 18.18f
            )
        );
        CHECK(
            arg[2] ==
            glm::mat3x3(
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
                24.24f, 25.25f, 26.26f, 27.27f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x4(glm::mat3x4 arg) {
        CHECK(
            arg ==
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x4Defaulted(glm::mat3x4 arg = glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)) {
        CHECK(
            arg ==
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x4DefaultedCheck(bool isDefaulted, glm::mat3x4 arg = glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::mat3x4(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                    7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
        }
        else {
            CHECK(
                arg ==
                glm::mat3x4(
                    13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
                    19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
                )
            );
        }
    }

    [[codegen::luawrap]] void funcMat3x4Map(std::map<std::string, glm::mat3x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat3x4(
                13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat3x4(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x4Optional(std::optional<glm::mat3x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat3x4OptionalNullopt(std::optional<glm::mat3x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat3x4Vector(std::vector<glm::mat3x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::mat3x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
        CHECK(
            arg[1] ==
            glm::mat3x4(
                13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            )
        );
        CHECK(
            arg[2] ==
            glm::mat3x4(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x2(glm::mat4x2 arg) {
        CHECK(arg == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    }

    [[codegen::luawrap]] void funcMat4x2Defaulted(glm::mat4x2 arg = glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)) {
        CHECK(arg == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    }

    [[codegen::luawrap]] void funcMat4x2DefaultedCheck(bool isDefaulted, glm::mat4x2 arg = glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
        }
        else {
            CHECK(
                arg ==
                glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
            );
        }
    }

    [[codegen::luawrap]] void funcMat4x2Map(std::map<std::string, glm::mat4x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
        );
    }

    [[codegen::luawrap]] void funcMat4x2Optional(std::optional<glm::mat4x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
        );
    }

    [[codegen::luawrap]] void funcMat4x2OptionalNullopt(std::optional<glm::mat4x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat4x2Vector(std::vector<glm::mat4x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
        CHECK(
            arg[1] ==
            glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
        );
        CHECK(
            arg[2] ==
            glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
        );
    }

    [[codegen::luawrap]] void funcMat4x3(glm::mat4x3 arg) {
        CHECK(
            arg ==
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x3Defaulted(glm::mat4x3 arg = glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)) {
        CHECK(
            arg ==
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x3DefaultedCheck(bool isDefaulted, glm::mat4x3 arg = glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::mat4x3(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                    7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
                )
            );
        }
        else {
            CHECK(
                arg ==
                glm::mat4x3(
                    13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                    19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
                )
            );
        }
    }

    [[codegen::luawrap]] void funcMat4x3Map(std::map<std::string, glm::mat4x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat4x3(
                13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat4x3(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x3Optional(std::optional<glm::mat4x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x3OptionalNullopt(std::optional<glm::mat4x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat4x3Vector(std::vector<glm::mat4x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::mat4x3(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
                7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
            )
        );
        CHECK(
            arg[1] ==
            glm::mat4x3(
                13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
                19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
            )
        );
        CHECK(
            arg[2] ==
            glm::mat4x3(
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
                31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x4(glm::mat4x4 arg) {
        CHECK(
            arg ==
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x4Defaulted(glm::mat4x4 arg = glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)) {
        CHECK(
            arg ==
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x4DefaultedCheck(bool isDefaulted, glm::mat4x4 arg = glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::mat4x4(
                    1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                    9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
                )
            );
        }
        else {
            CHECK(
                arg ==
                glm::mat4x4(
                    17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
                    25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
                )
            );
        }
    }

    [[codegen::luawrap]] void funcMat4x4Map(std::map<std::string, glm::mat4x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::mat4x4(
                17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::mat4x4(
                33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38, 39.39f, 40.40f,
                41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x4Optional(std::optional<glm::mat4x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            )
        );
    }

    [[codegen::luawrap]] void funcMat4x4OptionalNullopt(std::optional<glm::mat4x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcMat4x4Vector(std::vector<glm::mat4x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::mat4x4(
                1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
                9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
            )
        );
        CHECK(
            arg[1] ==
            glm::mat4x4(
                17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
                25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
            )
        );
        CHECK(
            arg[2] ==
            glm::mat4x4(
                33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
                41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
            )
        );
    }

    [[codegen::luawrap]] void funcDMat2x2(glm::dmat2x2 arg) {
        CHECK(arg == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDMat2x2Defaulted(glm::dmat2x2 arg = glm::dmat2x2(1.1, 2.2, 3.3, 4.4)) {
        CHECK(arg == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDMat2x2DefaultedCheck(bool isDefaulted, glm::dmat2x2 arg = glm::dmat2x2(1.1, 2.2, 3.3, 4.4)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
        }
        else {
            CHECK(arg == glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
        }
    }

    [[codegen::luawrap]] void funcDMat2x2Map(std::map<std::string, glm::dmat2x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(arg.find("key2")->second == glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(arg.find("key3")->second == glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    }

    [[codegen::luawrap]] void funcDMat2x2Optional(std::optional<glm::dmat2x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDMat2x2OptionalNullopt(std::optional<glm::dmat2x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat2x2Vector(std::vector<glm::dmat2x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
        CHECK(arg[1] == glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
        CHECK(arg[2] == glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    }

    [[codegen::luawrap]] void funcDMat2x3(glm::dmat2x3 arg) {
        CHECK(arg == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat2x3Defaulted(glm::dmat2x3 arg = glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)) {
        CHECK(arg == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat2x3DefaultedCheck(bool isDefaulted, glm::dmat2x3 arg = glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
        }
        else {
            CHECK(arg == glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
        }
    }

    [[codegen::luawrap]] void funcDMat2x3Map(std::map<std::string, glm::dmat2x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(arg.find("key1")->second == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        );
    }

    [[codegen::luawrap]] void funcDMat2x3Optional(std::optional<glm::dmat2x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat2x3OptionalNullopt(std::optional<glm::dmat2x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat2x3Vector(std::vector<glm::dmat2x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(arg[1] == glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
        CHECK(arg[2] == glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    }

    [[codegen::luawrap]] void funcDMat2x4(glm::dmat2x4 arg) {
        CHECK(arg == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    }

    [[codegen::luawrap]] void funcDMat2x4Defaulted(glm::dmat2x4 arg = glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)) {
        CHECK(arg == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    }

    [[codegen::luawrap]] void funcDMat2x4DefaultedCheck(bool isDefaulted, glm::dmat2x4 arg = glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
        }
        else {
            CHECK(
                arg ==
                glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
            );
        }
    }

    [[codegen::luawrap]] void funcDMat2x4Map(std::map<std::string, glm::dmat2x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
        );
    }

    [[codegen::luawrap]] void funcDMat2x4Optional(std::optional<glm::dmat2x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    }

    [[codegen::luawrap]] void funcDMat2x4OptionalNullopt(std::optional<glm::dmat2x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat2x4Vector(std::vector<glm::dmat2x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
        );
        CHECK(
            arg[1] ==
            glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
        );
        CHECK(
            arg[2] ==
            glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
        );
    }

    [[codegen::luawrap]] void funcDMat3x2(glm::dmat3x2 arg) {
        CHECK(arg == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat3x2Defaulted(glm::dmat3x2 arg = glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)) {
        CHECK(arg == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat3x2DefaultedCheck(bool isDefaulted, glm::dmat3x2 arg = glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
        }
        else {
            CHECK(arg == glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
        }
    }

    [[codegen::luawrap]] void funcDMat3x2Map(std::map<std::string, glm::dmat3x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        );
    }

    [[codegen::luawrap]] void funcDMat3x2Optional(std::optional<glm::dmat3x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    }

    [[codegen::luawrap]] void funcDMat3x2OptionalNullopt(std::optional<glm::dmat3x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat3x2Vector(std::vector<glm::dmat3x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
        CHECK(arg[1] == glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
        CHECK(arg[2] == glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    }

    [[codegen::luawrap]] void funcDMat3x3(glm::dmat3x3 arg) {
        CHECK(arg == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
    }

    [[codegen::luawrap]] void funcDMat3x3Defaulted(glm::dmat3x3 arg = glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)) {
        CHECK(arg == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
    }

    [[codegen::luawrap]] void funcDMat3x3DefaultedCheck(bool isDefaulted, glm::dmat3x3 arg = glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
        }
        else {
            CHECK(
                arg ==
                glm::dmat3x3(
                    10.10, 11.11, 12.12, 13.13, 14.14,
                    15.15, 16.16, 17.17, 18.18
                )
            );
        }
    }

    [[codegen::luawrap]] void funcDMat3x3Map(std::map<std::string, glm::dmat3x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
        );
    }

    [[codegen::luawrap]] void funcDMat3x3Optional(std::optional<glm::dmat3x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(*arg == glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9));
    }

    [[codegen::luawrap]] void funcDMat3x3OptionalNullopt(std::optional<glm::dmat3x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat3x3Vector(std::vector<glm::dmat3x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
        );
        CHECK(
            arg[1] ==
            glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
        );
        CHECK(
            arg[2] ==
            glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
        );
    }

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

    [[codegen::luawrap]] void funcDMat4x2(glm::dmat4x2 arg) {
        CHECK(arg == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    }

    [[codegen::luawrap]] void funcDMat4x2Defaulted(glm::dmat4x2 arg = glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)) {
        CHECK(arg == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    }

    [[codegen::luawrap]] void funcDMat4x2DefaultedCheck(bool isDefaulted, glm::dmat4x2 arg = glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
        }
        else {
            CHECK(
                arg ==
                glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
            );
        }
    }

    [[codegen::luawrap]] void funcDMat4x2Map(std::map<std::string, glm::dmat4x2> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
        );
    }

    [[codegen::luawrap]] void funcDMat4x2Optional(std::optional<glm::dmat4x2> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
        );
    }

    [[codegen::luawrap]] void funcDMat4x2OptionalNullopt(std::optional<glm::dmat4x2> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat4x2Vector(std::vector<glm::dmat4x2> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0] == glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
        CHECK(
            arg[1] ==
            glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
        );
        CHECK(
            arg[2] ==
            glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
        );
    }

    [[codegen::luawrap]] void funcDMat4x3(glm::dmat4x3 arg) {
        CHECK(
            arg ==
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x3Defaulted(glm::dmat4x3 arg = glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)) {
        CHECK(
            arg ==
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x3DefaultedCheck(bool isDefaulted, glm::dmat4x3 arg = glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::dmat4x3(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                    7.7, 8.8, 9.9, 10.10, 11.11, 12.12
                )
            );
        }
        else {
            CHECK(
                arg ==
                glm::dmat4x3(
                    13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                    19.19, 20.20, 21.21, 22.22, 23.23, 24.24
                )
            );
        }
    }

    [[codegen::luawrap]] void funcDMat4x3Map(std::map<std::string, glm::dmat4x3> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat4x3(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat4x3(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x3Optional(std::optional<glm::dmat4x3> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x3OptionalNullopt(std::optional<glm::dmat4x3> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat4x3Vector(std::vector<glm::dmat4x3> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::dmat4x3(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
                7.7, 8.8, 9.9, 10.10, 11.11, 12.12
            )
        );
        CHECK(
            arg[1] ==
            glm::dmat4x3(
                13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
                19.19, 20.20, 21.21, 22.22, 23.23, 24.24
            )
        );
        CHECK(
            arg[2] ==
            glm::dmat4x3(
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
                31.31, 32.32, 33.33, 34.34, 35.35, 36.36
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x4(glm::dmat4x4 arg) {
        CHECK(
            arg ==
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x4Defaulted(glm::dmat4x4 arg = glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)) {
        CHECK(
            arg ==
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x4DefaultedCheck(bool isDefaulted, glm::dmat4x4 arg = glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)) {
        if (isDefaulted) {
            CHECK(
                arg ==
                glm::dmat4x4(
                    1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                    9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
                )
            );
        }
        else {
            CHECK(
                arg ==
                glm::dmat4x4(
                    17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
                    25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
                )
            );
        }
    }

    [[codegen::luawrap]] void funcDMat4x4Map(std::map<std::string, glm::dmat4x4> arg) {
        CHECK(arg.size() == 3);
        REQUIRE(arg.find("key1") != arg.end());
        CHECK(
            arg.find("key1")->second ==
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            )
        );
        REQUIRE(arg.find("key2") != arg.end());
        CHECK(
            arg.find("key2")->second ==
            glm::dmat4x4(
                17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
            )
        );
        REQUIRE(arg.find("key3") != arg.end());
        CHECK(
            arg.find("key3")->second ==
            glm::dmat4x4(
                33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
                41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x4Optional(std::optional<glm::dmat4x4> arg) {
        REQUIRE(arg.has_value());
        CHECK(
            *arg ==
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            )
        );
    }

    [[codegen::luawrap]] void funcDMat4x4OptionalNullopt(std::optional<glm::dmat4x4> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDMat4x4Vector(std::vector<glm::dmat4x4> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(
            arg[0] ==
            glm::dmat4x4(
                1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
            )
        );
        CHECK(
            arg[1] ==
            glm::dmat4x4(
                17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
                25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
            )
        );
        CHECK(
            arg[2] ==
            glm::dmat4x4(
                33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
                41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
            )
        );
    }

    [[codegen::luawrap]] void funcDictionary(ghoul::Dictionary arg) {
        REQUIRE(arg.hasValue<double>("a"));
        CHECK(arg.value<double>("a") == 1.1);
        REQUIRE(arg.hasValue<std::string>("b"));
        CHECK(arg.value<std::string>("b") == "abc");
        REQUIRE(arg.hasValue<glm::dvec3>("c"));
        CHECK(arg.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDictionaryDefaulted(ghoul::Dictionary arg = ghoul::Dictionary()) {
        CHECK(arg == ghoul::Dictionary());
    }

    [[codegen::luawrap]] void funcDictionaryDefaultedCheck(bool isDefaulted, ghoul::Dictionary arg = ghoul::Dictionary()) {
        if (isDefaulted) {
            CHECK(arg == ghoul::Dictionary());
        }
        else {
            REQUIRE(arg.hasValue<double>("a"));
            CHECK(arg.value<double>("a") == 1.1);
            REQUIRE(arg.hasValue<std::string>("b"));
            CHECK(arg.value<std::string>("b") == "abc");
            REQUIRE(arg.hasValue<glm::dvec3>("c"));
            CHECK(arg.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
        }
    }

    [[codegen::luawrap]] void funcDictionaryMap(std::map<std::string, ghoul::Dictionary> arg) {
        CHECK(arg.size() == 3);
        {
            auto it = arg.find("key1");
            REQUIRE(it != arg.end());
            CHECK(it->second.hasValue<double>("a"));
            CHECK(it->second.value<double>("a") == 1.1);
            REQUIRE(it->second.hasValue<std::string>("b"));
            CHECK(it->second.value<std::string>("b") == "abc");
            REQUIRE(it->second.hasValue<glm::dvec3>("c"));
            CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
        }
        {
            auto it = arg.find("key2");
            REQUIRE(it != arg.end());
            CHECK(it->second.hasValue<double>("a"));
            CHECK(it->second.value<double>("a") == 5.5);
            REQUIRE(it->second.hasValue<std::string>("b"));
            CHECK(it->second.value<std::string>("b") == "def");
            REQUIRE(it->second.hasValue<glm::dvec3>("c"));
            CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(6.6, 7.7, 8.8));
        }
        {
            auto it = arg.find("key3");
            REQUIRE(it != arg.end());
            CHECK(it->second.hasValue<double>("a"));
            CHECK(it->second.value<double>("a") == 9.9);
            REQUIRE(it->second.hasValue<std::string>("b"));
            CHECK(it->second.value<std::string>("b") == "ghi");
            REQUIRE(it->second.hasValue<glm::dvec3>("c"));
            CHECK(it->second.value<glm::dvec3>("c") == glm::dvec3(10.10, 11.11, 12.12));
        }
    }

    [[codegen::luawrap]] void funcDictionaryOptional(std::optional<ghoul::Dictionary> arg) {
        REQUIRE(arg.has_value());
        REQUIRE(arg->hasValue<double>("a"));
        CHECK(arg->value<double>("a") == 1.1);
        REQUIRE(arg->hasValue<std::string>("b"));
        CHECK(arg->value<std::string>("b") == "abc");
        REQUIRE(arg->hasValue<glm::dvec3>("c"));
        CHECK(arg->value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
    }

    [[codegen::luawrap]] void funcDictionaryOptionalNullopt(std::optional<ghoul::Dictionary> arg) {
        CHECK(!arg.has_value());
    }

    [[codegen::luawrap]] void funcDictionaryVector(std::vector<ghoul::Dictionary> arg) {
        REQUIRE(arg.size() == 3);
        CHECK(arg[0].hasValue<double>("a"));
        CHECK(arg[0].value<double>("a") == 1.1);
        REQUIRE(arg[0].hasValue<std::string>("b"));
        CHECK(arg[0].value<std::string>("b") == "abc");
        REQUIRE(arg[0].hasValue<glm::dvec3>("c"));
        CHECK(arg[0].value<glm::dvec3>("c") == glm::dvec3(2.2, 3.3, 4.4));
        CHECK(arg[1].hasValue<double>("a"));
        CHECK(arg[1].value<double>("a") == 5.5);
        REQUIRE(arg[1].hasValue<std::string>("b"));
        CHECK(arg[1].value<std::string>("b") == "def");
        REQUIRE(arg[1].hasValue<glm::dvec3>("c"));
        CHECK(arg[1].value<glm::dvec3>("c") == glm::dvec3(6.6, 7.7, 8.8));
        CHECK(arg[2].hasValue<double>("a"));
        CHECK(arg[2].value<double>("a") == 9.9);
        REQUIRE(arg[2].hasValue<std::string>("b"));
        CHECK(arg[2].value<std::string>("b") == "ghi");
        REQUIRE(arg[2].hasValue<glm::dvec3>("c"));
        CHECK(arg[2].value<glm::dvec3>("c") == glm::dvec3(10.10, 11.11, 12.12));
    }

    [[codegen::luawrap]] void funcVariantBool(std::variant<bool, int> arg) {
        REQUIRE(std::holds_alternative<bool>(arg));
        CHECK(std::get<bool>(arg) == true);
    }

    [[codegen::luawrap]] void funcVariantInt(std::variant<bool, int> arg) {
        REQUIRE(std::holds_alternative<int>(arg));
        CHECK(std::get<int>(arg) == 2);
    }

    [[codegen::luawrap]] void funcVariantDoubleDvec3StringDouble(std::variant<double, glm::dvec3, std::string> arg) {
        REQUIRE(std::holds_alternative<double>(arg));
        CHECK(std::get<double>(arg) == 2.2);
    }

    [[codegen::luawrap]] void funcVariantDoubleDvec3StringDvec3(std::variant<double, glm::dvec3, std::string> arg) {
        REQUIRE(std::holds_alternative<glm::dvec3>(arg));
        CHECK(std::get<glm::dvec3>(arg) == glm::dvec3(1.1, 2.2, 3.3));
    }

    [[codegen::luawrap]] void funcVariantDoubleDvec3StringString(std::variant<double, glm::dvec3, std::string> arg) {
        REQUIRE(std::holds_alternative<std::string>(arg));
        CHECK(std::get<std::string>(arg) == "abc");
    }

#include "execution_luawrapper_arguments_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Arguments:  void") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVoid;
    CHECK(func.name == "funcVoid");
    CHECK(func.arguments.size() == 0);
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBool;
    CHECK(func.name == "funcBool");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolDefaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolDefaulted;
    CHECK(func.name == "funcBoolDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean?");
    CHECK(func.arguments[0].defaultValue == "true");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolDefaulted;
    CHECK(func.name == "funcBoolDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean?");
    CHECK(func.arguments[0].defaultValue == "true");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolDefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolDefaultedCheck;
    CHECK(func.name == "funcBoolDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Boolean?");
    CHECK(func.arguments[1].defaultValue == "true");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, false);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolDefaultedCheck;
    CHECK(func.name == "funcBoolDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Boolean?");
    CHECK(func.arguments[1].defaultValue == "true");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolMap;
    CHECK(func.name == "funcBoolMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Boolean");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", true);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", false);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", false);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolOptional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolOptional;
    CHECK(func.name == "funcBoolOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  funcBoolOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolOptionalNullopt;
    CHECK(func.name == "funcBoolOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  boolVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncBoolVector;
    CHECK(func.name == "funcBoolVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Boolean]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, true);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, false);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, false);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncInt;
    CHECK(func.name == "funcInt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Integer");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intDefaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Integer?");
    CHECK(func.arguments[0].defaultValue == "2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Integer?");
    CHECK(func.arguments[0].defaultValue == "2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intDefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntDefaultedCheck;
    CHECK(func.name == "funcIntDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Integer?");
    CHECK(func.arguments[1].defaultValue == "2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, 3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntDefaultedCheck;
    CHECK(func.name == "funcIntDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Integer?");
    CHECK(func.arguments[1].defaultValue == "2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncIntMap;
    CHECK(func.name == "funcIntMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Integer");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intOptional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Integer?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntOptionalNullopt;
    CHECK(func.name == "funcIntOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Integer?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIntVector;
    CHECK(func.name == "funcIntVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Integer]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDouble;
    CHECK(func.name == "funcDouble");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleDefaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleDefaulted;
    CHECK(func.name == "funcDoubleDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.arguments[0].defaultValue == "2.2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleDefaulted;
    CHECK(func.name == "funcDoubleDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.arguments[0].defaultValue == "2.2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleDefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleDefaultedCheck;
    CHECK(func.name == "funcDoubleDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Number?");
    CHECK(func.arguments[1].defaultValue == "2.2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, 3.3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleDefaultedCheck;
    CHECK(func.name == "funcDoubleDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Number?");
    CHECK(func.arguments[1].defaultValue == "2.2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleMap;
    CHECK(func.name == "funcDoubleMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Number");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2.2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3.3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleOptional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleOptionalNullopt;
    CHECK(func.name == "funcDoubleOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDoubleVector;
    CHECK(func.name == "funcDoubleVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Number]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2.2);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3.3);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  float") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloat;
    CHECK(func.name == "funcFloat");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatDefaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatDefaulted;
    CHECK(func.name == "funcFloatDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.arguments[0].defaultValue == "1.1f");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatDefaulted;
    CHECK(func.name == "funcFloatDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.arguments[0].defaultValue == "1.1f");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatDefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatDefaultedCheck;
    CHECK(func.name == "funcFloatDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Number?");
    CHECK(func.arguments[1].defaultValue == "2.2f");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, 3.3f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatDefaultedCheck;
    CHECK(func.name == "funcFloatDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Number?");
    CHECK(func.arguments[1].defaultValue == "2.2f");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatMap;
    CHECK(func.name == "funcFloatMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Number");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", 1.1f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", 2.2f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", 3.3f);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatOptional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 1.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatOptionalNullopt;
    CHECK(func.name == "funcFloatOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncFloatVector;
    CHECK(func.name == "funcFloatVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Number]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, 1.1f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, 2.2f);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, 3.3f);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Arguments:  string") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncString;
    CHECK(func.name == "funcString");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringDefaulted with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String?");
    CHECK(func.arguments[0].defaultValue == "\"abc\"");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringDefaulted w/o value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String?");
    CHECK(func.arguments[0].defaultValue == "\"abc\"");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringDefaultedCheck with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringDefaultedCheck;
    CHECK(func.name == "funcStringDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "String?");
    CHECK(func.arguments[1].defaultValue == "\"abc\"");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, "def"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringDefaultedCheck w/o value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringDefaultedCheck;
    CHECK(func.name == "funcStringDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "String?");
    CHECK(func.arguments[1].defaultValue == "\"abc\"");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringMap;
    CHECK(func.name == "funcStringMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> String");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", "def"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", "ghi"s);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringOptional") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringOptionalNullopt") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringOptionalNullopt;
    CHECK(func.name == "funcStringOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringVector") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncStringVector;
    CHECK(func.name == "funcStringVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[String]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, "def"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, "ghi"s);
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  path") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPath;
    CHECK(func.name == "funcPath");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Path");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, std::filesystem::path("abc"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathDefaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathDefaulted;
    CHECK(func.name == "funcPathDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Path?");
    CHECK(func.arguments[0].defaultValue == "std::filesystem::path(\"abc\")");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, std::filesystem::path("abc"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathDefaulted;
    CHECK(func.name == "funcPathDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Path?");
    CHECK(func.arguments[0].defaultValue == "std::filesystem::path(\"abc\")");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathDefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathDefaultedCheck;
    CHECK(func.name == "funcPathDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Path?");
    CHECK(func.arguments[1].defaultValue == "std::filesystem::path(\"abc\")");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, std::filesystem::path("def"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathDefaultedCheck;
    CHECK(func.name == "funcPathDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Path?");
    CHECK(func.arguments[1].defaultValue == "std::filesystem::path(\"abc\")");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathMap;
    CHECK(func.name == "funcPathMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Path");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", std::filesystem::path("abc"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", std::filesystem::path("def"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", std::filesystem::path("ghi"));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathOptional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathOptional;
    CHECK(func.name == "funcPathOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Path?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, std::filesystem::path("abc"));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathOptionalNullopt;
    CHECK(func.name == "funcPathOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Path?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathVector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncPathVector;
    CHECK(func.name == "funcPathVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Path]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, std::filesystem::path("abc"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, std::filesystem::path("def"));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, std::filesystem::path("ghi"));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2;
    CHECK(func.name == "funcIvec2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec2(1, 2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Defaulted;
    CHECK(func.name == "funcIvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec2?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec2(1, 2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec2(1, 2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Defaulted;
    CHECK(func.name == "funcIvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec2?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec2(1, 2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2DefaultedCheck;
    CHECK(func.name == "funcIvec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec2?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec2(1, 2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::ivec2(2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2DefaultedCheck;
    CHECK(func.name == "funcIvec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec2?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec2(1, 2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Map;
    CHECK(func.name == "funcIvec2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> ivec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec2(1, 2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec2(3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec2(5, 6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec2(1, 2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2OptionalNullopt;
    CHECK(func.name == "funcIvec2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec2Vector;
    CHECK(func.name == "funcIvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[ivec2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec2(1, 2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec2(3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec2(5, 6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3;
    CHECK(func.name == "funcIvec3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec3(1, 2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Defaulted;
    CHECK(func.name == "funcIvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec3?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec3(1, 2, 3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec3(1, 2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Defaulted;
    CHECK(func.name == "funcIvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec3?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec3(1, 2, 3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3DefaultedCheck;
    CHECK(func.name == "funcIvec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec3?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec3(1, 2, 3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::ivec3(4, 5, 6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3DefaultedCheck;
    CHECK(func.name == "funcIvec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec3?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec3(1, 2, 3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Map;
    CHECK(func.name == "funcIvec3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> ivec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec3(1, 2, 3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec3(4, 5, 6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec3(7, 8, 9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec3(1, 2, 3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3OptionalNullopt;
    CHECK(func.name == "funcIvec3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec3Vector;
    CHECK(func.name == "funcIvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[ivec3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec3(1, 2, 3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec3(4, 5, 6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec3(7, 8, 9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4;
    CHECK(func.name == "funcIvec4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec4(1, 2, 3, 4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Defaulted;
    CHECK(func.name == "funcIvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec4?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec4(1, 2, 3, 4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec4(1, 2, 3, 4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Defaulted;
    CHECK(func.name == "funcIvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec4?");
    CHECK(func.arguments[0].defaultValue == "glm::ivec4(1, 2, 3, 4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4DefaultedCheck;
    CHECK(func.name == "funcIvec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec4?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec4(1, 2, 3, 4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::ivec4(5, 6, 7, 8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4DefaultedCheck;
    CHECK(func.name == "funcIvec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "ivec4?");
    CHECK(func.arguments[1].defaultValue == "glm::ivec4(1, 2, 3, 4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Map;
    CHECK(func.name == "funcIvec4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> ivec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::ivec4(1, 2, 3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::ivec4(5, 6, 7, 8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::ivec4(9, 10, 11, 12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::ivec4(1, 2, 3, 4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4OptionalNullopt;
    CHECK(func.name == "funcIvec4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "ivec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncIvec4Vector;
    CHECK(func.name == "funcIvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[ivec4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::ivec4(1, 2, 3, 4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::ivec4(5, 6, 7, 8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::ivec4(9, 10, 11, 12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2;
    CHECK(func.name == "funcDvec2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec2(1.1, 2.2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Defaulted;
    CHECK(func.name == "funcDvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec2(1.1, 2.2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec2(1.1, 2.2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Defaulted;
    CHECK(func.name == "funcDvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec2(1.1, 2.2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2DefaultedCheck;
    CHECK(func.name == "funcDvec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec2?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec2(1.1, 2.2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dvec2(3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2DefaultedCheck;
    CHECK(func.name == "funcDvec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec2?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec2(1.1, 2.2)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Map;
    CHECK(func.name == "funcDvec2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec2(1.1, 2.2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec2(3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec2(5.5, 6.6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec2(1.1, 2.2));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2OptionalNullopt;
    CHECK(func.name == "funcDvec2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec2Vector;
    CHECK(func.name == "funcDvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec2(1.1, 2.2));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec2(3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec2(5.5, 6.6));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3;
    CHECK(func.name == "funcDvec3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Defaulted;
    CHECK(func.name == "funcDvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec3(1.1, 2.2, 3.3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Defaulted;
    CHECK(func.name == "funcDvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec3(1.1, 2.2, 3.3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3DefaultedCheck;
    CHECK(func.name == "funcDvec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec3?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec3(1.1, 2.2, 3.3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dvec3(4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3DefaultedCheck;
    CHECK(func.name == "funcDvec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec3?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec3(1.1, 2.2, 3.3)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Map;
    CHECK(func.name == "funcDvec3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec3(1.1, 2.2, 3.3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec3(4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec3(7.7, 8.8, 9.9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3OptionalNullopt;
    CHECK(func.name == "funcDvec3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec3Vector;
    CHECK(func.name == "funcDvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec3(1.1, 2.2, 3.3));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec3(4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec3(7.7, 8.8, 9.9));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4;
    CHECK(func.name == "funcDvec4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Defaulted;
    CHECK(func.name == "funcDvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec4(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Defaulted;
    CHECK(func.name == "funcDvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.arguments[0].defaultValue == "glm::dvec4(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4DefaultedCheck;
    CHECK(func.name == "funcDvec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec4?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec4(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dvec4(5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4DefaultedCheck;
    CHECK(func.name == "funcDvec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec4?");
    CHECK(func.arguments[1].defaultValue == "glm::dvec4(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Map;
    CHECK(func.name == "funcDvec4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dvec4(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4OptionalNullopt;
    CHECK(func.name == "funcDvec4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDvec4Vector;
    CHECK(func.name == "funcDvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dvec4(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dvec4(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dvec4(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2;
    CHECK(func.name == "funcVec2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec2(1.1f, 2.2f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Defaulted;
    CHECK(func.name == "funcVec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.arguments[0].defaultValue == "glm::vec2(1.1f, 2.2f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec2(1.1f, 2.2f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Defaulted;
    CHECK(func.name == "funcVec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.arguments[0].defaultValue == "glm::vec2(1.1f, 2.2f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2DefaultedCheck;
    CHECK(func.name == "funcVec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec2?");
    CHECK(func.arguments[1].defaultValue == "glm::vec2(1.1f, 2.2f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::vec2(3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2DefaultedCheck;
    CHECK(func.name == "funcVec2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec2?");
    CHECK(func.arguments[1].defaultValue == "glm::vec2(1.1f, 2.2f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Map;
    CHECK(func.name == "funcVec2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec2(1.1f, 2.2f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec2(3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec2(5.5f, 6.6f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec2(1.1f, 2.2f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2OptionalNullopt;
    CHECK(func.name == "funcVec2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec2Vector;
    CHECK(func.name == "funcVec2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec2(1.1f, 2.2f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec2(3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec2(5.5f, 6.6f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3;
    CHECK(func.name == "funcVec3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Defaulted;
    CHECK(func.name == "funcVec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.arguments[0].defaultValue == "glm::vec3(1.1f, 2.2f, 3.3f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Defaulted;
    CHECK(func.name == "funcVec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.arguments[0].defaultValue == "glm::vec3(1.1f, 2.2f, 3.3f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3DefaultedCheck;
    CHECK(func.name == "funcVec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec3?");
    CHECK(func.arguments[1].defaultValue == "glm::vec3(1.1f, 2.2f, 3.3f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::vec3(4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3DefaultedCheck;
    CHECK(func.name == "funcVec3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec3?");
    CHECK(func.arguments[1].defaultValue == "glm::vec3(1.1f, 2.2f, 3.3f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Map;
    CHECK(func.name == "funcVec3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec3(1.1f, 2.2f, 3.3f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec3(4.4f, 5.5f, 6.6f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec3(7.7f, 8.8f, 9.9f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec3(1.1f, 2.2f, 3.3f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3OptionalNullopt;
    CHECK(func.name == "funcVec3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec3Vector;
    CHECK(func.name == "funcVec3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec3(1.1f, 2.2f, 3.3f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec3(4.4f, 5.5f, 6.6f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec3(7.7f, 8.8f, 9.9f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4;
    CHECK(func.name == "funcVec4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Defaulted;
    CHECK(func.name == "funcVec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.arguments[0].defaultValue == "glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Defaulted;
    CHECK(func.name == "funcVec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.arguments[0].defaultValue == "glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4DefaultedCheck;
    CHECK(func.name == "funcVec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec4?");
    CHECK(func.arguments[1].defaultValue == "glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4DefaultedCheck;
    CHECK(func.name == "funcVec4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "vec4?");
    CHECK(func.arguments[1].defaultValue == "glm::vec4(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Map;
    CHECK(func.name == "funcVec4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> vec4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4OptionalNullopt;
    CHECK(func.name == "funcVec4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "vec4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVec4Vector;
    CHECK(func.name == "funcVec4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[vec4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::vec4(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::vec4(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::vec4(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2;
    CHECK(func.name == "funcMat2x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Defaulted;
    CHECK(func.name == "funcMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Defaulted;
    CHECK(func.name == "funcMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2DefaultedCheck;
    CHECK(func.name == "funcMat2x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2DefaultedCheck;
    CHECK(func.name == "funcMat2x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Map;
    CHECK(func.name == "funcMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2OptionalNullopt;
    CHECK(func.name == "funcMat2x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x2Vector;
    CHECK(func.name == "funcMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::mat2x2(1.1f, 2.2f, 3.3f, 4.4f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::mat2x2(5.5f, 6.6f, 7.7f, 8.8f));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::mat2x2(9.9f, 10.10f, 11.11f, 12.12f));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3;
    CHECK(func.name == "funcMat2x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Defaulted;
    CHECK(func.name == "funcMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Defaulted;
    CHECK(func.name == "funcMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3DefaultedCheck;
    CHECK(func.name == "funcMat2x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3DefaultedCheck;
    CHECK(func.name == "funcMat2x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Map;
    CHECK(func.name == "funcMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3OptionalNullopt;
    CHECK(func.name == "funcMat2x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x3Vector;
    CHECK(func.name == "funcMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat2x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat2x3(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat2x3(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4;
    CHECK(func.name == "funcMat2x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Defaulted;
    CHECK(func.name == "funcMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Defaulted;
    CHECK(func.name == "funcMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4DefaultedCheck;
    CHECK(func.name == "funcMat2x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4DefaultedCheck;
    CHECK(func.name == "funcMat2x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Map;
    CHECK(func.name == "funcMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4OptionalNullopt;
    CHECK(func.name == "funcMat2x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat2x4Vector;
    CHECK(func.name == "funcMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat2x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat2x4(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat2x4(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2;
    CHECK(func.name == "funcMat3x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Defaulted;
    CHECK(func.name == "funcMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Defaulted;
    CHECK(func.name == "funcMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2DefaultedCheck;
    CHECK(func.name == "funcMat3x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2DefaultedCheck;
    CHECK(func.name == "funcMat3x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Map;
    CHECK(func.name == "funcMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2OptionalNullopt;
    CHECK(func.name == "funcMat3x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x2Vector;
    CHECK(func.name == "funcMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x2(7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x2(13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3;
    CHECK(func.name == "funcMat3x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Defaulted;
    CHECK(func.name == "funcMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Defaulted;
    CHECK(func.name == "funcMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3DefaultedCheck;
    CHECK(func.name == "funcMat3x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3DefaultedCheck;
    CHECK(func.name == "funcMat3x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Map;
    CHECK(func.name == "funcMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3OptionalNullopt;
    CHECK(func.name == "funcMat3x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x3Vector;
    CHECK(func.name == "funcMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x3(
            10.10f, 11.11f, 12.12f, 13.13f, 14.14f,
            15.15f, 16.16f, 17.17f, 18.18f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x3(
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f,
            24.24f, 25.25f, 26.26f, 27.27f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4;
    CHECK(func.name == "funcMat3x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Defaulted;
    CHECK(func.name == "funcMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Defaulted;
    CHECK(func.name == "funcMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4DefaultedCheck;
    CHECK(func.name == "funcMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat3x4(
            13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4DefaultedCheck;
    CHECK(func.name == "funcMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat3x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Map;
    CHECK(func.name == "funcMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat3x4(
            13.13f, 14.14f, 15.15, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4OptionalNullopt;
    CHECK(func.name == "funcMat3x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat3x4Vector;
    CHECK(func.name == "funcMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat3x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat3x4(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat3x4(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2;
    CHECK(func.name == "funcMat4x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Defaulted;
    CHECK(func.name == "funcMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Defaulted;
    CHECK(func.name == "funcMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2DefaultedCheck;
    CHECK(func.name == "funcMat4x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2DefaultedCheck;
    CHECK(func.name == "funcMat4x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x2?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Map;
    CHECK(func.name == "funcMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2OptionalNullopt;
    CHECK(func.name == "funcMat4x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x2Vector;
    CHECK(func.name == "funcMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x2(9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x2(17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3;
    CHECK(func.name == "funcMat4x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Defaulted;
    CHECK(func.name == "funcMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Defaulted;
    CHECK(func.name == "funcMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3DefaultedCheck;
    CHECK(func.name == "funcMat4x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3DefaultedCheck;
    CHECK(func.name == "funcMat4x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x3?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Map;
    CHECK(func.name == "funcMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x3(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3OptionalNullopt;
    CHECK(func.name == "funcMat4x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x3Vector;
    CHECK(func.name == "funcMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x3(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f,
            7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x3(
            13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f,
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x3(
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f,
            31.31f, 32.32f, 33.33f, 34.34f, 35.35f, 36.36f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4;
    CHECK(func.name == "funcMat4x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Defaulted;
    CHECK(func.name == "funcMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Defaulted;
    CHECK(func.name == "funcMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.arguments[0].defaultValue == "glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4DefaultedCheck;
    CHECK(func.name == "funcMat4x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4DefaultedCheck;
    CHECK(func.name == "funcMat4x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x4?");
    CHECK(func.arguments[1].defaultValue == "glm::mat4x4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Map;
    CHECK(func.name == "funcMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4OptionalNullopt;
    CHECK(func.name == "funcMat4x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncMat4x4Vector;
    CHECK(func.name == "funcMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::mat4x4(
            1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f,
            9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::mat4x4(
            17.17f, 18.18f, 19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f, 31.31f, 32.32f
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::mat4x4(
            33.33f, 34.34f, 35.35f, 36.36f, 37.37f, 38.38f, 39.39f, 40.40f,
            41.41f, 42.42f, 43.43f, 44.44f, 45.45f, 46.46f, 47.47f, 48.48f
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2;
    CHECK(func.name == "funcDMat2x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Defaulted;
    CHECK(func.name == "funcDMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x2(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Defaulted;
    CHECK(func.name == "funcDMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x2(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2DefaultedCheck;
    CHECK(func.name == "funcDMat2x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x2(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2DefaultedCheck;
    CHECK(func.name == "funcDMat2x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x2(1.1, 2.2, 3.3, 4.4)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Map;
    CHECK(func.name == "funcDMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2OptionalNullopt;
    CHECK(func.name == "funcDMat2x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x2Vector;
    CHECK(func.name == "funcDMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dmat2x2(1.1, 2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dmat2x2(5.5, 6.6, 7.7, 8.8));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dmat2x2(9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3;
    CHECK(func.name == "funcDMat2x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Defaulted;
    CHECK(func.name == "funcDMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Defaulted;
    CHECK(func.name == "funcDMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3DefaultedCheck;
    CHECK(func.name == "funcDMat2x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3DefaultedCheck;
    CHECK(func.name == "funcDMat2x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Map;
    CHECK(func.name == "funcDMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3OptionalNullopt;
    CHECK(func.name == "funcDMat2x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x3Vector;
    CHECK(func.name == "funcDMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, 1, glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 2, glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    ghoul::lua::push(state, 3, glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4;
    CHECK(func.name == "funcDMat2x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Defaulted;
    CHECK(func.name == "funcDMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Defaulted;
    CHECK(func.name == "funcDMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4DefaultedCheck;
    CHECK(func.name == "funcDMat2x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4DefaultedCheck;
    CHECK(func.name == "funcDMat2x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat2x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Map;
    CHECK(func.name == "funcDMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat2x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4OptionalNullopt;
    CHECK(func.name == "funcDMat2x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat2x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat2x4Vector;
    CHECK(func.name == "funcDMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat2x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat2x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat2x4(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat2x4(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2;
    CHECK(func.name == "funcDMat3x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Defaulted;
    CHECK(func.name == "funcDMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Defaulted;
    CHECK(func.name == "funcDMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2DefaultedCheck;
    CHECK(func.name == "funcDMat3x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false, glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2DefaultedCheck;
    CHECK(func.name == "funcDMat3x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Map;
    CHECK(func.name == "funcDMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2OptionalNullopt;
    CHECK(func.name == "funcDMat3x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x2Vector;
    CHECK(func.name == "funcDMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x2(7.7, 8.8, 9.9, 10.10, 11.11, 12.12)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x2(13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3;
    CHECK(func.name == "funcDMat3x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Defaulted;
    CHECK(func.name == "funcDMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Defaulted;
    CHECK(func.name == "funcDMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3DefaultedCheck;
    CHECK(func.name == "funcDMat3x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3DefaultedCheck;
    CHECK(func.name == "funcDMat3x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Map;
    CHECK(func.name == "funcDMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3OptionalNullopt;
    CHECK(func.name == "funcDMat3x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x3Vector;
    CHECK(func.name == "funcDMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat3x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat3x3(10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat3x3(19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26, 27.27)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4;
    CHECK(func.name == "funcDMat3x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4DefaultedCheck;
    CHECK(func.name == "funcDMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

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
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4DefaultedCheck;
    CHECK(func.name == "funcDMat3x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat3x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat3x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Map;
    CHECK(func.name == "funcDMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat3x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

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
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4OptionalNullopt;
    CHECK(func.name == "funcDMat3x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat3x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat3x4Vector;
    CHECK(func.name == "funcDMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat3x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

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
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}


TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2;
    CHECK(func.name == "funcDMat4x2");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Defaulted;
    CHECK(func.name == "funcDMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Defaulted;
    CHECK(func.name == "funcDMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2DefaultedCheck;
    CHECK(func.name == "funcDMat4x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2DefaultedCheck;
    CHECK(func.name == "funcDMat4x2DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x2?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Map;
    CHECK(func.name == "funcDMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x2");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2OptionalNullopt;
    CHECK(func.name == "funcDMat4x2OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x2?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x2Vector;
    CHECK(func.name == "funcDMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x2]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x2(9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x2(17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3;
    CHECK(func.name == "funcDMat4x3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Defaulted;
    CHECK(func.name == "funcDMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Defaulted;
    CHECK(func.name == "funcDMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3DefaultedCheck;
    CHECK(func.name == "funcDMat4x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3DefaultedCheck;
    CHECK(func.name == "funcDMat4x3DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x3?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Map;
    CHECK(func.name == "funcDMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x3");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x3(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3OptionalNullopt;
    CHECK(func.name == "funcDMat4x3OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x3?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x3Vector;
    CHECK(func.name == "funcDMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x3]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x3(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6,
            7.7, 8.8, 9.9, 10.10, 11.11, 12.12
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x3(
            13.13, 14.14, 15.15, 16.16, 17.17, 18.18,
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x3(
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30,
            31.31, 32.32, 33.33, 34.34, 35.35, 36.36
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4;
    CHECK(func.name == "funcDMat4x4");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Defaulted with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Defaulted;
    CHECK(func.name == "funcDMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Defaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Defaulted;
    CHECK(func.name == "funcDMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.arguments[0].defaultValue == "glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4DefaultedCheck with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4DefaultedCheck;
    CHECK(func.name == "funcDMat4x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        false,
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4DefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4DefaultedCheck;
    CHECK(func.name == "funcDMat4x4DefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "mat4x4?");
    CHECK(func.arguments[1].defaultValue == "glm::dmat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Map;
    CHECK(func.name == "funcDMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> mat4x4");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        "key1",
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key2",
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        "key3",
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Optional") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4OptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4OptionalNullopt;
    CHECK(func.name == "funcDMat4x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Vector") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4Vector;
    CHECK(func.name == "funcDMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[mat4x4]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(
        state,
        1,
        glm::dmat4x4(
            1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
            9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        2,
        glm::dmat4x4(
            17.17, 18.18, 19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
        )
    );
    lua_rawset(state, -3);
    ghoul::lua::push(
        state,
        3,
        glm::dmat4x4(
            33.33, 34.34, 35.35, 36.36, 37.37, 38.38, 39.39, 40.40,
            41.41, 42.42, 43.43, 44.44, 45.45, 46.46, 47.47, 48.48
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionary") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionary;
    CHECK(func.name == "funcDictionary");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Table");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "a"s, 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "b"s, "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "c"s, glm::dvec3(2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryDefaulted with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryDefaulted;
    CHECK(func.name == "funcDictionaryDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Table?");
    CHECK(func.arguments[0].defaultValue == "ghoul::Dictionary()");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryDefaulted;
    CHECK(func.name == "funcDictionaryDefaulted");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Table?");
    CHECK(func.arguments[0].defaultValue == "ghoul::Dictionary()");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryDefaultedCheck with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryDefaultedCheck;
    CHECK(func.name == "funcDictionaryDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Table?");
    CHECK(func.arguments[1].defaultValue == "ghoul::Dictionary()");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, false);
    lua_newtable(state);
    ghoul::lua::push(state, "a"s, 1.1);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "b"s, "abc"s);
    lua_rawset(state, -3);
    ghoul::lua::push(state, "c"s, glm::dvec3(2.2, 3.3, 4.4));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryDefaultedCheck w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryDefaultedCheck;
    CHECK(func.name == "funcDictionaryDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    CHECK(func.arguments[0].name == "isDefaulted");
    CHECK(func.arguments[0].type == "Boolean");
    CHECK(func.arguments[1].name == "arg");
    CHECK(func.arguments[1].type == "Table?");
    CHECK(func.arguments[1].defaultValue == "ghoul::Dictionary()");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryMap;
    CHECK(func.name == "funcDictionaryMap");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "String -> Table");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    {
        ghoul::lua::push(state, "key1");
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 1.1);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "abc"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(2.2, 3.3, 4.4));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    {
        ghoul::lua::push(state, "key2");
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 5.5);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "def"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(6.6, 7.7, 8.8));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    {
        ghoul::lua::push(state, "key3");
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 9.9);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "ghi"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(10.10, 11.11, 12.12));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryOptional") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryOptional;
    CHECK(func.name == "funcDictionaryOptional");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Table?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    {
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 1.1);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "abc"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(2.2, 3.3, 4.4));
        lua_rawset(state, -3);
    }
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryOptionalNullopt") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncDMat4x4OptionalNullopt;
    CHECK(func.name == "funcDMat4x4OptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "mat4x4?");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryVector") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncDictionaryVector;
    CHECK(func.name == "funcDictionaryVector");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "[Table]");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    {
        ghoul::lua::push(state, 1);
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 1.1);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "abc"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(2.2, 3.3, 4.4));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    {
        ghoul::lua::push(state, 2);
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 5.5);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "def"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(6.6, 7.7, 8.8));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    {
        ghoul::lua::push(state, 3);
        lua_newtable(state);
        ghoul::lua::push(state, "a"s, 9.9);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "b"s, "ghi"s);
        lua_rawset(state, -3);
        ghoul::lua::push(state, "c"s, glm::dvec3(10.10, 11.11, 12.12));
        lua_rawset(state, -3);
    }
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(bool,int) / bool") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantBool;
    CHECK(func.name == "funcVariantBool");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean | Integer");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, true);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(bool,int) / int") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantInt;
    CHECK(func.name == "funcVariantInt");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Boolean | Integer");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, vec3, string) / double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantDoubleDvec3StringDouble;
    CHECK(func.name == "funcVariantDoubleDvec3StringDouble");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number | vec3 | String");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.2);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, vec3, string) / vec3") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::FuncVariantDoubleDvec3StringDvec3;
    CHECK(func.name == "funcVariantDoubleDvec3StringDvec3");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number | vec3 | String");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, glm::dvec3(1.1, 2.2, 3.3));
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, vec3, string) / string") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::FuncVariantDoubleDvec3StringString;
    CHECK(func.name == "funcVariantDoubleDvec3StringString");
    REQUIRE(func.arguments.size() == 1);
    CHECK(func.arguments[0].name == "arg");
    CHECK(func.arguments[0].type == "Number | vec3 | String");
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, "abc"s);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}
