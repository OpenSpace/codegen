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
    }

    [[codegen::luawrap]] void funcIntOptional(std::optional<int> arg) {
    }

    [[codegen::luawrap]] void funcIntVector(std::vector<int> arg) {
    }

    [[codegen::luawrap]] void funcDouble(double arg) {
    }

    [[codegen::luawrap]] void funcDoubleDefaulted(double arg = 2.0) {
        CHECK(arg == 2.0);
    }

    [[codegen::luawrap]] void funcDoubleDefaultedCheck(bool isDefaulted, double arg = 2.0) {
        if (isDefaulted) {
            CHECK(arg == 2.0);
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDoubleMap(std::map<std::string, double> arg) {
    }

    [[codegen::luawrap]] void funcDoubleOptional(std::optional<double> arg) {
    }

    [[codegen::luawrap]] void funcDoubleVector(std::vector<double> arg) {
    }

    [[codegen::luawrap]] void funcFloat(float arg) {
    }

    [[codegen::luawrap]] void funcFloatDefaulted(float arg = 2.f) {
        CHECK(arg == 2.f);
    }

    [[codegen::luawrap]] void funcFloatDefaultedCheck(bool isDefaulted, float arg = 2.f) {
        if (isDefaulted) {
            CHECK(arg == 2.f);
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcFloatMap(std::map<std::string, float> arg) {
    }

    [[codegen::luawrap]] void funcFloatOptional(std::optional<float> arg) {
    }

    [[codegen::luawrap]] void funcFloatVector(std::vector<float> arg) {
    }

    [[codegen::luawrap]] void funcString(std::string arg) {
    }

    [[codegen::luawrap]] void funcStringDefaulted(std::string arg = "abc") {
        CHECK(arg == "abc");
    }

    [[codegen::luawrap]] void funcStringDefaultedCheck(bool isDefaulted, std::string arg = "abc") {
        if (isDefaulted) {
            CHECK(arg == "abc");
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcStringMap(std::map<std::string, std::string> arg) {
    }

    [[codegen::luawrap]] void funcStringOptional(std::optional<std::string> arg) {
    }

    [[codegen::luawrap]] void funcStringVector(std::vector<std::string> arg) {
    }

    [[codegen::luawrap]] void funcPath(std::filesystem::path arg) {
    }

    [[codegen::luawrap]] void funcPathDefaulted(std::filesystem::path arg = std::filesystem::path("abc")) {
        CHECK(arg == std::filesystem::path("abc"));
    }

    [[codegen::luawrap]] void funcPathDefaultedCheck(bool isDefaulted, std::filesystem::path arg = std::filesystem::path("abc")) {
        if (isDefaulted) {
            CHECK(arg == std::filesystem::path("abc"));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcPathMap(std::map<std::string, std::filesystem::path> arg) {
    }

    [[codegen::luawrap]] void funcPathOptional(std::optional<std::filesystem::path> arg) {
    }

    [[codegen::luawrap]] void funcPathVector(std::vector<std::filesystem::path> arg) {
    }

    [[codegen::luawrap]] void funcIvec2(glm::ivec2 arg) {
    }

    [[codegen::luawrap]] void funcIvec2Defaulted(glm::ivec2 arg = glm::ivec2(1, 2)) {
        CHECK(arg == glm::ivec2(1, 2));
    }

    [[codegen::luawrap]] void funcIvec2DefaultedCheck(bool isDefaulted, glm::ivec2 arg = glm::ivec2(1, 2)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec2(1, 2));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcIvec2Map(std::map<std::string, glm::ivec2> arg) {
    }

    [[codegen::luawrap]] void funcIvec2Optional(std::optional<glm::ivec2> arg) {
    }

    [[codegen::luawrap]] void funcIvec2Vector(std::vector<glm::ivec2> arg) {
    }

    [[codegen::luawrap]] void funcIvec3(glm::ivec3 arg) {
    }

    [[codegen::luawrap]] void funcIvec3Defaulted(glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
        CHECK(arg == glm::ivec3(1, 2, 3));
    }

    [[codegen::luawrap]] void funcIvec3DefaultedCheck(bool isDefaulted, glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec3(1, 2, 3));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcIvec3Map(std::map<std::string, glm::ivec3> arg) {
    }

    [[codegen::luawrap]] void funcIvec3Optional(std::optional<glm::ivec3> arg) {
    }

    [[codegen::luawrap]] void funcIvec3Vector(std::vector<glm::ivec3> arg) {
    }

    [[codegen::luawrap]] void funcIvec4(glm::ivec4 arg) {
    }

    [[codegen::luawrap]] void funcIvec4Defaulted(glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
        CHECK(arg == glm::ivec4(1, 2, 3, 4));
    }

    [[codegen::luawrap]] void funcIvec4DefaultedCheck(bool isDefaulted, glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
        if (isDefaulted) {
            CHECK(arg == glm::ivec4(1, 2, 3, 4));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcIvec4Map(std::map<std::string, glm::ivec4> arg) {
    }

    [[codegen::luawrap]] void funcIvec4Optional(std::optional<glm::ivec4> arg) {
    }

    [[codegen::luawrap]] void funcIvec4Vector(std::vector<glm::ivec4> arg) {
    }

    [[codegen::luawrap]] void funcDvec2(glm::dvec2 arg) {
    }

    [[codegen::luawrap]] void funcDvec2Defaulted(glm::dvec2 arg = glm::dvec2(1.0, 2.0)) {
        CHECK(arg == glm::dvec2(1.0, 2.0));
    }

    [[codegen::luawrap]] void funcDvec2DefaultedCheck(bool isDefaulted, glm::dvec2 arg = glm::dvec2(1.0, 2.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec2(1.0, 2.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDvec2Map(std::map<std::string, glm::dvec2> arg) {
    }

    [[codegen::luawrap]] void funcDvec2Optional(std::optional<glm::dvec2> arg) {
    }

    [[codegen::luawrap]] void funcDvec2Vector(std::vector<glm::dvec2> arg) {
    }

    [[codegen::luawrap]] void funcDvec3(glm::dvec3 arg) {
    }

    [[codegen::luawrap]] void funcDvec3Defaulted(glm::dvec3 arg = glm::dvec3(1.0, 2.0, 3.0)) {
        CHECK(arg == glm::dvec3(1.0, 2.0, 3.0));
    }

    [[codegen::luawrap]] void funcDvec3DefaultedCheck(bool isDefaulted, glm::dvec3 arg = glm::dvec3(1.0, 2.0, 3.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec3(1.0, 2.0, 3.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDvec3Map(std::map<std::string, glm::dvec3> arg) {
    }

    [[codegen::luawrap]] void funcDvec3Optional(std::optional<glm::dvec3> arg) {
    }

    [[codegen::luawrap]] void funcDvec3Vector(std::vector<glm::dvec3> arg) {
    }

    [[codegen::luawrap]] void funcDvec4(glm::dvec4 arg) {
    }

    [[codegen::luawrap]] void funcDvec4Defaulted(glm::dvec4 arg = glm::dvec4(1.0, 2.0, 3.0, 4.0)) {
        CHECK(arg == glm::dvec4(1.0, 2.0, 3.0, 4.0));
    }

    [[codegen::luawrap]] void funcDvec4DefaultedCheck(bool isDefaulted, glm::dvec4 arg = glm::dvec4(1.0, 2.0, 3.0, 4.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dvec4(1.0, 2.0, 3.0, 4.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDvec4Map(std::map<std::string, glm::dvec4> arg) {
    }

    [[codegen::luawrap]] void funcDvec4Optional(std::optional<glm::dvec4> arg) {
    }

    [[codegen::luawrap]] void funcDvec4Vector(std::vector<glm::dvec4> arg) {
    }

    [[codegen::luawrap]] void funcVec2(glm::vec2 arg) {
    }

    [[codegen::luawrap]] void funcVec2Defaulted(glm::vec2 arg = glm::vec2(1.f, 2.f)) {
        CHECK(arg == glm::vec2(1.f, 2.f));
    }

    [[codegen::luawrap]] void funcVec2DefaultedCheck(bool isDefaulted, glm::vec2 arg = glm::vec2(1.f, 2.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec2(1.f, 2.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcVec2Map(std::map<std::string, glm::vec2> arg) {
    }

    [[codegen::luawrap]] void funcVec2Optional(std::optional<glm::vec2> arg) {
    }

    [[codegen::luawrap]] void funcVec2Vector(std::vector<glm::vec2> arg) {
    }

    [[codegen::luawrap]] void funcVec3(glm::vec3 arg) {
    }

    [[codegen::luawrap]] void funcVec3Defaulted(glm::vec3 arg = glm::vec3(1.f, 2.f, 3.f)) {
        CHECK(arg == glm::vec3(1.f, 2.f, 3.f));
    }

    [[codegen::luawrap]] void funcVec3DefaultedCheck(bool isDefaulted, glm::vec3 arg = glm::vec3(1.f, 2.f, 3.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec3(1.f, 2.f, 3.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcVec3Map(std::map<std::string, glm::vec3> arg) {
    }

    [[codegen::luawrap]] void funcVec3Optional(std::optional<glm::vec3> arg) {
    }

    [[codegen::luawrap]] void funcVec3Vector(std::vector<glm::vec3> arg) {
    }

    [[codegen::luawrap]] void funcVec4(glm::vec4 arg) {
    }

    [[codegen::luawrap]] void funcVec4Defaulted(glm::vec4 arg = glm::vec4(1.f, 2.f, 3.f, 4.f)) {
        CHECK(arg == glm::vec4(1.f, 2.f, 3.f, 4.f));
    }

    [[codegen::luawrap]] void funcVec4DefaultedCheck(bool isDefaulted, glm::vec4 arg = glm::vec4(1.f, 2.f, 3.f, 4.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::vec4(1.f, 2.f, 3.f, 4.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcVec4Map(std::map<std::string, glm::vec4> arg) {
    }

    [[codegen::luawrap]] void funcVec4Optional(std::optional<glm::vec4> arg) {
    }

    [[codegen::luawrap]] void funcVec4Vector(std::vector<glm::vec4> arg) {
    }

    [[codegen::luawrap]] void funcMat2x2(glm::mat2x2 arg) {
    }

    [[codegen::luawrap]] void funcMat2x2Defaulted(glm::mat2x2 arg = glm::mat2x2(1.f, 2.f, 3.f, 4.f)) {
        CHECK(arg == glm::mat2x2(1.f, 2.f, 3.f, 4.f));
    }

    [[codegen::luawrap]] void funcMat2x2DefaultedCheck(bool isDefaulted, glm::mat2x2 arg = glm::mat2x2(1.f, 2.f, 3.f, 4.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x2(1.f, 2.f, 3.f, 4.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat2x2Map(std::map<std::string, glm::mat2x2> arg) {
    }

    [[codegen::luawrap]] void funcMat2x2Optional(std::optional<glm::mat2x2> arg) {
    }

    [[codegen::luawrap]] void funcMat2x2Vector(std::vector<glm::mat2x2> arg) {
    }

    [[codegen::luawrap]] void funcMat2x3(glm::mat2x3 arg) {
    }

    [[codegen::luawrap]] void funcMat2x3Defaulted(glm::mat2x3 arg = glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
        CHECK(arg == glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f));
    }

    [[codegen::luawrap]] void funcMat2x3DefaultedCheck(bool isDefaulted, glm::mat2x3 arg = glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat2x3Map(std::map<std::string, glm::mat2x3> arg) {
    }

    [[codegen::luawrap]] void funcMat2x3Optional(std::optional<glm::mat2x3> arg) {
    }

    [[codegen::luawrap]] void funcMat2x3Vector(std::vector<glm::mat2x3> arg) {
    }

    [[codegen::luawrap]] void funcMat2x4(glm::mat2x4 arg) {
    }

    [[codegen::luawrap]] void funcMat2x4Defaulted(glm::mat2x4 arg = glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
        CHECK(arg == glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f));
    }

    [[codegen::luawrap]] void funcMat2x4DefaultedCheck(bool isDefaulted, glm::mat2x4 arg = glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat2x4Map(std::map<std::string, glm::mat2x4> arg) {
    }

    [[codegen::luawrap]] void funcMat2x4Optional(std::optional<glm::mat2x4> arg) {
    }

    [[codegen::luawrap]] void funcMat2x4Vector(std::vector<glm::mat2x4> arg) {
    }

    [[codegen::luawrap]] void funcMat3x2(glm::mat3x2 arg) {
    }

    [[codegen::luawrap]] void funcMat3x2Defaulted(glm::mat3x2 arg = glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
        CHECK(arg == glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f));
    }

    [[codegen::luawrap]] void funcMat3x2DefaultedCheck(bool isDefaulted, glm::mat3x2 arg = glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat3x2Map(std::map<std::string, glm::mat3x2> arg) {
    }

    [[codegen::luawrap]] void funcMat3x2Optional(std::optional<glm::mat3x2> arg) {
    }

    [[codegen::luawrap]] void funcMat3x2Vector(std::vector<glm::mat3x2> arg) {
    }

    [[codegen::luawrap]] void funcMat3x3(glm::mat3x3 arg) {
    }

    [[codegen::luawrap]] void funcMat3x3Defaulted(glm::mat3x3 arg = glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)) {
        CHECK(arg == glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
    }

    [[codegen::luawrap]] void funcMat3x3DefaultedCheck(bool isDefaulted, glm::mat3x3 arg = glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat3x3Map(std::map<std::string, glm::mat3x3> arg) {
    }

    [[codegen::luawrap]] void funcMat3x3Optional(std::optional<glm::mat3x3> arg) {
    }

    [[codegen::luawrap]] void funcMat3x3Vector(std::vector<glm::mat3x3> arg) {
    }

    [[codegen::luawrap]] void funcMat3x4(glm::mat3x4 arg) {
    }

    [[codegen::luawrap]] void funcMat3x4Defaulted(glm::mat3x4 arg = glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
        CHECK(arg == glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f));
    }

    [[codegen::luawrap]] void funcMat3x4DefaultedCheck(bool isDefaulted, glm::mat3x4 arg = glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat3x4Map(std::map<std::string, glm::mat3x4> arg) {
    }

    [[codegen::luawrap]] void funcMat3x4Optional(std::optional<glm::mat3x4> arg) {
    }

    [[codegen::luawrap]] void funcMat3x4Vector(std::vector<glm::mat3x4> arg) {
    }

    [[codegen::luawrap]] void funcMat4x2(glm::mat4x2 arg) {
    }

    [[codegen::luawrap]] void funcMat4x2Defaulted(glm::mat4x2 arg = glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
        CHECK(arg == glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f));
    }

    [[codegen::luawrap]] void funcMat4x2DefaultedCheck(bool isDefaulted, glm::mat4x2 arg = glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f));
        }
    }

    [[codegen::luawrap]] void funcMat4x2Map(std::map<std::string, glm::mat4x2> arg) {
    }

    [[codegen::luawrap]] void funcMat4x2Optional(std::optional<glm::mat4x2> arg) {
    }

    [[codegen::luawrap]] void funcMat4x2Vector(std::vector<glm::mat4x2> arg) {
    }

    [[codegen::luawrap]] void funcMat4x3(glm::mat4x3 arg) {
    }

    [[codegen::luawrap]] void funcMat4x3Defaulted(glm::mat4x3 arg = glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
        CHECK(arg == glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f));
    }

    [[codegen::luawrap]] void funcMat4x3DefaultedCheck(bool isDefaulted, glm::mat4x3 arg = glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat4x3Map(std::map<std::string, glm::mat4x3> arg) {
    }

    [[codegen::luawrap]] void funcMat4x3Optional(std::optional<glm::mat4x3> arg) {
    }

    [[codegen::luawrap]] void funcMat4x3Vector(std::vector<glm::mat4x3> arg) {
    }

    [[codegen::luawrap]] void funcMat4x4(glm::mat4x4 arg) {
    }

    [[codegen::luawrap]] void funcMat4x4Defaulted(glm::mat4x4 arg = glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f)) {
        CHECK(arg == glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
    }

    [[codegen::luawrap]] void funcMat4x4DefaultedCheck(bool isDefaulted, glm::mat4x4 arg = glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f)) {
        if (isDefaulted) {
            CHECK(arg == glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcMat4x4Map(std::map<std::string, glm::mat4x4> arg) {
    }

    [[codegen::luawrap]] void funcMat4x4Optional(std::optional<glm::mat4x4> arg) {
    }

    [[codegen::luawrap]] void funcMat4x4Vector(std::vector<glm::mat4x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x2(glm::dmat2x2 arg) {
    }

    [[codegen::luawrap]] void funcDMat2x2Defaulted(glm::dmat2x2 arg = glm::dmat2x2(1.0, 2.0, 3.0, 4.0)) {
        CHECK(arg == glm::dmat2x2(1.0, 2.0, 3.0, 4.0));
    }

    [[codegen::luawrap]] void funcDMat2x2DefaultedCheck(bool isDefaulted, glm::dmat2x2 arg = glm::dmat2x2(1.0, 2.0, 3.0, 4.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x2(1.0, 2.0, 3.0, 4.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat2x2Map(std::map<std::string, glm::dmat2x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x2Optional(std::optional<glm::dmat2x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x2Vector(std::vector<glm::dmat2x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x3(glm::dmat2x3 arg) {
    }

    [[codegen::luawrap]] void funcDMat2x3Defaulted(glm::dmat2x3 arg = glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
        CHECK(arg == glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));
    }

    [[codegen::luawrap]] void funcDMat2x3DefaultedCheck(bool isDefaulted, glm::dmat2x3 arg = glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat2x3Map(std::map<std::string, glm::dmat2x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x3Optional(std::optional<glm::dmat2x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x3Vector(std::vector<glm::dmat2x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x4(glm::dmat2x4 arg) {
    }

    [[codegen::luawrap]] void funcDMat2x4Defaulted(glm::dmat2x4 arg = glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
        CHECK(arg == glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
    }

    [[codegen::luawrap]] void funcDMat2x4DefaultedCheck(bool isDefaulted, glm::dmat2x4 arg = glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat2x4Map(std::map<std::string, glm::dmat2x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x4Optional(std::optional<glm::dmat2x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat2x4Vector(std::vector<glm::dmat2x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x2(glm::dmat3x2 arg) {
    }

    [[codegen::luawrap]] void funcDMat3x2Defaulted(glm::dmat3x2 arg = glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
        CHECK(arg == glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));
    }

    [[codegen::luawrap]] void funcDMat3x2DefaultedCheck(bool isDefaulted, glm::dmat3x2 arg = glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat3x2Map(std::map<std::string, glm::dmat3x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x2Optional(std::optional<glm::dmat3x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x2Vector(std::vector<glm::dmat3x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x3(glm::dmat3x3 arg) {
    }

    [[codegen::luawrap]] void funcDMat3x3Defaulted(glm::dmat3x3 arg = glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)) {
        CHECK(arg == glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0));
    }

    [[codegen::luawrap]] void funcDMat3x3DefaultedCheck(bool isDefaulted, glm::dmat3x3 arg = glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat3x3Map(std::map<std::string, glm::dmat3x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x3Optional(std::optional<glm::dmat3x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x3Vector(std::vector<glm::dmat3x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x4(glm::dmat3x4 arg) {
    }

    [[codegen::luawrap]] void funcDMat3x4Defaulted(glm::dmat3x4 arg = glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
        CHECK(arg == glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0));
    }

    [[codegen::luawrap]] void funcDMat3x4DefaultedCheck(bool isDefaulted, glm::dmat3x4 arg = glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat3x4Map(std::map<std::string, glm::dmat3x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x4Optional(std::optional<glm::dmat3x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat3x4Vector(std::vector<glm::dmat3x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x2(glm::dmat4x2 arg) {
    }

    [[codegen::luawrap]] void funcDMat4x2Defaulted(glm::dmat4x2 arg = glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
        CHECK(arg == glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
    }

    [[codegen::luawrap]] void funcDMat4x2DefaultedCheck(bool isDefaulted, glm::dmat4x2 arg = glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat4x2Map(std::map<std::string, glm::dmat4x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x2Optional(std::optional<glm::dmat4x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x2Vector(std::vector<glm::dmat4x2> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x3(glm::dmat4x3 arg) {
    }

    [[codegen::luawrap]] void funcDMat4x3Defaulted(glm::dmat4x3 arg = glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
        CHECK(arg == glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0));
    }

    [[codegen::luawrap]] void funcDMat4x3DefaultedCheck(bool isDefaulted, glm::dmat4x3 arg = glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat4x3Map(std::map<std::string, glm::dmat4x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x3Optional(std::optional<glm::dmat4x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x3Vector(std::vector<glm::dmat4x3> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x4(glm::dmat4x4 arg) {
    }

    [[codegen::luawrap]] void funcDMat4x4Defaulted(glm::dmat4x4 arg = glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0)) {
        CHECK(arg == glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0));
    }

    [[codegen::luawrap]] void funcDMat4x4DefaultedCheck(bool isDefaulted, glm::dmat4x4 arg = glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0)) {
        if (isDefaulted) {
            CHECK(arg == glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0));
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDMat4x4Map(std::map<std::string, glm::dmat4x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x4Optional(std::optional<glm::dmat4x4> arg) {
    }

    [[codegen::luawrap]] void funcDMat4x4Vector(std::vector<glm::dmat4x4> arg) {
    }

    [[codegen::luawrap]] void funcDictionary(ghoul::Dictionary arg) {
    }

    [[codegen::luawrap]] void funcDictionaryDefaulted(ghoul::Dictionary arg = ghoul::Dictionary()) {
        CHECK(arg == ghoul::Dictionary());
    }

    [[codegen::luawrap]] void funcDictionaryDefaultedCheck(bool isDefaulted, ghoul::Dictionary arg = ghoul::Dictionary()) {
        if (isDefaulted) {
            CHECK(arg == ghoul::Dictionary());
        }
        else {

        }
    }

    [[codegen::luawrap]] void funcDictionaryMap(std::map<std::string, ghoul::Dictionary> arg) {
    }

    [[codegen::luawrap]] void funcDictionaryOptional(std::optional<ghoul::Dictionary> arg) {
    }

    [[codegen::luawrap]] void funcDictionaryVector(std::vector<ghoul::Dictionary> arg) {
    }

    [[codegen::luawrap]] void funcVariant(std::variant<bool, int> arg) {
    }

    [[codegen::luawrap]] void funcVariantDoubleFloatString(std::variant<double, float, std::string> arg) {
    }

#include "execution_luawrapper_arguments_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Arguments:  void") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVoid;
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

    LuaLibrary::Function func = codegen::lua::funcBool;
    CHECK(func.name == "funcBool");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolDefaulted;
    CHECK(func.name == "funcBoolDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolDefaulted;
    CHECK(func.name == "funcBoolDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolDefaultedCheck;
    CHECK(func.name == "funcBoolDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    {
        CHECK(func.arguments[0].name == "isDefaulted");
        CHECK(func.arguments[0].type == "Boolean");
        CHECK(func.arguments[1].name == "arg");
        CHECK(func.arguments[1].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolDefaultedCheck;
    CHECK(func.name == "funcBoolDefaultedCheck");
    REQUIRE(func.arguments.size() == 2);
    {
        CHECK(func.arguments[0].name == "isDefaulted");
        CHECK(func.arguments[0].type == "Boolean");
        CHECK(func.arguments[1].name == "arg");
        CHECK(func.arguments[1].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolMap;
    CHECK(func.name == "funcBoolMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Boolean");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolOptional;
    CHECK(func.name == "funcBoolOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolOptionalNullopt;
    CHECK(func.name == "funcBoolOptionalNullopt");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcBoolVector;
    CHECK(func.name == "funcBoolVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Boolean]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcInt;
    CHECK(func.name == "funcInt");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIntDefaulted;
    CHECK(func.name == "funcIntDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  intMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcIntMap;
    CHECK(func.name == "funcIntMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Integer");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  intOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  intOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIntOptional;
    CHECK(func.name == "funcIntOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Integer?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIntVector;
    CHECK(func.name == "funcIntVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Integer]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDouble;
    CHECK(func.name == "funcDouble");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDoubleDefaulted;
    CHECK(func.name == "funcDoubleDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.1);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleDefaulted;
    CHECK(func.name == "funcDoubleDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleMap;
    CHECK(func.name == "funcDoubleMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Number");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  doubleOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDoubleOptional;
    CHECK(func.name == "funcDoubleOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDoubleVector;
    CHECK(func.name == "funcDoubleVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Number]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcFloat;
    CHECK(func.name == "funcFloat");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number");
    }
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

    LuaLibrary::Function func = codegen::lua::funcFloatDefaulted;
    CHECK(func.name == "funcFloatDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.1f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatDefaulted;
    CHECK(func.name == "funcFloatDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  floatMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatMap;
    CHECK(func.name == "funcFloatMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Number");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  floatOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  floatOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcFloatOptional;
    CHECK(func.name == "funcFloatOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcFloatVector;
    CHECK(func.name == "funcFloatVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Number]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcString;
    CHECK(func.name == "funcString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String");
    }
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

    LuaLibrary::Function func = codegen::lua::funcStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcStringDefaulted;
    CHECK(func.name == "funcStringDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  stringMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringMap;
    CHECK(func.name == "funcStringMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> String");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  stringOptional with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  stringOptional w/o value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcStringOptional;
    CHECK(func.name == "funcStringOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcStringVector;
    CHECK(func.name == "funcStringVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[String]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcPath;
    CHECK(func.name == "funcPath");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path");
    }
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

    LuaLibrary::Function func = codegen::lua::funcPathDefaulted;
    CHECK(func.name == "funcPathDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcPathDefaulted;
    CHECK(func.name == "funcPathDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  pathMap") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathMap;
    CHECK(func.name == "funcPathMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Path");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  pathOptional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathOptional;
    CHECK(func.name == "funcPathOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  pathOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcPathOptional;
    CHECK(func.name == "funcPathOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Path?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcPathVector;
    CHECK(func.name == "funcPathVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Path]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec2;
    CHECK(func.name == "funcIvec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec2Defaulted;
    CHECK(func.name == "funcIvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec2Defaulted;
    CHECK(func.name == "funcIvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Map;
    CHECK(func.name == "funcIvec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec2Optional;
    CHECK(func.name == "funcIvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec2Vector;
    CHECK(func.name == "funcIvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec3;
    CHECK(func.name == "funcIvec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec3Defaulted;
    CHECK(func.name == "funcIvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec3Defaulted;
    CHECK(func.name == "funcIvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Map;
    CHECK(func.name == "funcIvec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec3Optional;
    CHECK(func.name == "funcIvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec3Vector;
    CHECK(func.name == "funcIvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec4;
    CHECK(func.name == "funcIvec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec4Defaulted;
    CHECK(func.name == "funcIvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec4Defaulted;
    CHECK(func.name == "funcIvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Map;
    CHECK(func.name == "funcIvec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> ivec4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  ivec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcIvec4Optional;
    CHECK(func.name == "funcIvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "ivec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcIvec4Vector;
    CHECK(func.name == "funcIvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[ivec4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec2;
    CHECK(func.name == "funcDvec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec2Defaulted;
    CHECK(func.name == "funcDvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec2Defaulted;
    CHECK(func.name == "funcDvec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Map;
    CHECK(func.name == "funcDvec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec2Optional;
    CHECK(func.name == "funcDvec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec2Vector;
    CHECK(func.name == "funcDvec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec3;
    CHECK(func.name == "funcDvec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec3Defaulted;
    CHECK(func.name == "funcDvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec3Defaulted;
    CHECK(func.name == "funcDvec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Map;
    CHECK(func.name == "funcDvec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec3Optional;
    CHECK(func.name == "funcDvec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec3Vector;
    CHECK(func.name == "funcDvec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec4;
    CHECK(func.name == "funcDvec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec4Defaulted;
    CHECK(func.name == "funcDvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec4Defaulted;
    CHECK(func.name == "funcDvec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Map;
    CHECK(func.name == "funcDvec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dvec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDvec4Optional;
    CHECK(func.name == "funcDvec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDvec4Vector;
    CHECK(func.name == "funcDvec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec2;
    CHECK(func.name == "funcVec2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec2Defaulted;
    CHECK(func.name == "funcVec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec2Defaulted;
    CHECK(func.name == "funcVec2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Map;
    CHECK(func.name == "funcVec2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec2Optional;
    CHECK(func.name == "funcVec2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec2Vector;
    CHECK(func.name == "funcVec2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec3;
    CHECK(func.name == "funcVec3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec3Defaulted;
    CHECK(func.name == "funcVec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec3Defaulted;
    CHECK(func.name == "funcVec3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Map;
    CHECK(func.name == "funcVec3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec3Optional;
    CHECK(func.name == "funcVec3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec3Vector;
    CHECK(func.name == "funcVec3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec4;
    CHECK(func.name == "funcVec4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec4Defaulted;
    CHECK(func.name == "funcVec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec4Defaulted;
    CHECK(func.name == "funcVec4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Map;
    CHECK(func.name == "funcVec4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> vec4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  vec4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVec4Optional;
    CHECK(func.name == "funcVec4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "vec4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVec4Vector;
    CHECK(func.name == "funcVec4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[vec4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x2;
    CHECK(func.name == "funcMat2x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x2Defaulted;
    CHECK(func.name == "funcMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x2Defaulted;
    CHECK(func.name == "funcMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Map;
    CHECK(func.name == "funcMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x2Optional;
    CHECK(func.name == "funcMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x2Vector;
    CHECK(func.name == "funcMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x3;
    CHECK(func.name == "funcMat2x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x3Defaulted;
    CHECK(func.name == "funcMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x3Defaulted;
    CHECK(func.name == "funcMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Map;
    CHECK(func.name == "funcMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x3Optional;
    CHECK(func.name == "funcMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x3Vector;
    CHECK(func.name == "funcMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x4;
    CHECK(func.name == "funcMat2x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x4Defaulted;
    CHECK(func.name == "funcMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x4Defaulted;
    CHECK(func.name == "funcMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Map;
    CHECK(func.name == "funcMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat2x4Optional;
    CHECK(func.name == "funcMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat2x4Vector;
    CHECK(func.name == "funcMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x2;
    CHECK(func.name == "funcMat3x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x2Defaulted;
    CHECK(func.name == "funcMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x2Defaulted;
    CHECK(func.name == "funcMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Map;
    CHECK(func.name == "funcMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x2Optional;
    CHECK(func.name == "funcMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x2Vector;
    CHECK(func.name == "funcMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x3;
    CHECK(func.name == "funcMat3x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x3Defaulted;
    CHECK(func.name == "funcMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x3Defaulted;
    CHECK(func.name == "funcMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Map;
    CHECK(func.name == "funcMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x3Optional;
    CHECK(func.name == "funcMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x3Vector;
    CHECK(func.name == "funcMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x4;
    CHECK(func.name == "funcMat3x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x4Defaulted;
    CHECK(func.name == "funcMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x4Defaulted;
    CHECK(func.name == "funcMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Map;
    CHECK(func.name == "funcMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat3x4Optional;
    CHECK(func.name == "funcMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat3x4Vector;
    CHECK(func.name == "funcMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x2;
    CHECK(func.name == "funcMat4x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x2Defaulted;
    CHECK(func.name == "funcMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x2Defaulted;
    CHECK(func.name == "funcMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Map;
    CHECK(func.name == "funcMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x2Optional;
    CHECK(func.name == "funcMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x2Vector;
    CHECK(func.name == "funcMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x3;
    CHECK(func.name == "funcMat4x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x3Defaulted;
    CHECK(func.name == "funcMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x3Defaulted;
    CHECK(func.name == "funcMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Map;
    CHECK(func.name == "funcMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x3");
    }
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
            19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f,
            25.25f, 26.26f, 27.27f, 28.28f, 29.29f, 30.30f)
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x3Optional;
    CHECK(func.name == "funcMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x3Vector;
    CHECK(func.name == "funcMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x4;
    CHECK(func.name == "funcMat4x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x4Defaulted;
    CHECK(func.name == "funcMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x4Defaulted;
    CHECK(func.name == "funcMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Map;
    CHECK(func.name == "funcMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  mat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcMat4x4Optional;
    CHECK(func.name == "funcMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcMat4x4Vector;
    CHECK(func.name == "funcMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x2;
    CHECK(func.name == "funcDMat2x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Defaulted;
    CHECK(func.name == "funcDMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Defaulted;
    CHECK(func.name == "funcDMat2x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Map;
    CHECK(func.name == "funcDMat2x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Optional;
    CHECK(func.name == "funcDMat2x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x2Vector;
    CHECK(func.name == "funcDMat2x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x3;
    CHECK(func.name == "funcDMat2x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Defaulted;
    CHECK(func.name == "funcDMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Defaulted;
    CHECK(func.name == "funcDMat2x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Map;
    CHECK(func.name == "funcDMat2x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x3");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    lua_newtable(state);
    ghoul::lua::push(state, "key1", glm::dmat2x3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key2", glm::dmat2x3(7.7, 8.8, 9.9, 10.10, 11.11, 12.12));
    lua_rawset(state, -3);
    ghoul::lua::push(state, "key3", glm::dmat2x3(13.13, 14.14, 15.15, 16.16, 17.17, 18.18));
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Optional;
    CHECK(func.name == "funcDMat2x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x3Vector;
    CHECK(func.name == "funcDMat2x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x4;
    CHECK(func.name == "funcDMat2x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Defaulted;
    CHECK(func.name == "funcDMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Defaulted;
    CHECK(func.name == "funcDMat2x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Map;
    CHECK(func.name == "funcDMat2x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat2x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat2x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Optional;
    CHECK(func.name == "funcDMat2x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat2x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat2x4Vector;
    CHECK(func.name == "funcDMat2x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat2x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x2;
    CHECK(func.name == "funcDMat3x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Defaulted;
    CHECK(func.name == "funcDMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Defaulted;
    CHECK(func.name == "funcDMat3x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Map;
    CHECK(func.name == "funcDMat3x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Optional;
    CHECK(func.name == "funcDMat3x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x2Vector;
    CHECK(func.name == "funcDMat3x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x3;
    CHECK(func.name == "funcDMat3x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Defaulted;
    CHECK(func.name == "funcDMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Defaulted;
    CHECK(func.name == "funcDMat3x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Map;
    CHECK(func.name == "funcDMat3x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x3");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Optional;
    CHECK(func.name == "funcDMat3x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x3Vector;
    CHECK(func.name == "funcDMat3x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x4;
    CHECK(func.name == "funcDMat3x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(
        state,
        glm::dmat3x4(
            1.1, 2.2, 3.3, 4.4, 5., 6.6,
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Defaulted;
    CHECK(func.name == "funcDMat3x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Map;
    CHECK(func.name == "funcDMat3x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat3x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat3x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Optional;
    CHECK(func.name == "funcDMat3x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat3x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat3x4Vector;
    CHECK(func.name == "funcDMat3x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat3x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x2;
    CHECK(func.name == "funcDMat4x2");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Defaulted;
    CHECK(func.name == "funcDMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Defaulted;
    CHECK(func.name == "funcDMat4x2Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Map;
    CHECK(func.name == "funcDMat4x2Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x2");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x2Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Optional;
    CHECK(func.name == "funcDMat4x2Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x2?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x2Vector;
    CHECK(func.name == "funcDMat4x2Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x2]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x3;
    CHECK(func.name == "funcDMat4x3");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Defaulted;
    CHECK(func.name == "funcDMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Defaulted;
    CHECK(func.name == "funcDMat4x3Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Map;
    CHECK(func.name == "funcDMat4x3Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x3");
    }
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
            19.19, 20.20, 21.21, 22.22, 23.23, 24.24,
            25.25, 26.26, 27.27, 28.28, 29.29, 30.0
        )
    );
    lua_rawset(state, -3);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x3Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Optional;
    CHECK(func.name == "funcDMat4x3Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x3?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x3Vector;
    CHECK(func.name == "funcDMat4x3Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x3]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x4;
    CHECK(func.name == "funcDMat4x4");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Defaulted;
    CHECK(func.name == "funcDMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Defaulted;
    CHECK(func.name == "funcDMat4x4Defaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Map") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Map;
    CHECK(func.name == "funcDMat4x4Map");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> mat4x4");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Optional with value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dmat4x4Optional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Vector;
    CHECK(func.name == "funcDMat4x4Vector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[mat4x4]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDictionary;
    CHECK(func.name == "funcDictionary");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Table");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDictionaryDefaulted;
    CHECK(func.name == "funcDictionaryDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Table?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryDefaulted w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDictionaryDefaulted;
    CHECK(func.name == "funcDictionaryDefaulted");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Table?");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryMap") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcDictionaryMap;
    CHECK(func.name == "funcDictionaryMap");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "String -> Table");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryOptional with value") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcDictionaryOptional;
    CHECK(func.name == "funcDictionaryOptional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Table?");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  dictionaryOptional w/o value") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcDMat4x4Optional;
    CHECK(func.name == "funcDMat4x4Optional");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "mat4x4?");
    }
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

    LuaLibrary::Function func = codegen::lua::funcDictionaryVector;
    CHECK(func.name == "funcDictionaryVector");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "[Table]");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVariant;
    CHECK(func.name == "funcVariant");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
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

    LuaLibrary::Function func = codegen::lua::funcVariant;
    CHECK(func.name == "funcVariant");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Boolean | Integer");
    }
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

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, float, string) / double") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatString;
    CHECK(func.name == "funcVariantDoubleFloatString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.0);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, float, string) / float") {
    using namespace openspace::scripting;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatString;
    CHECK(func.name == "funcVariantDoubleFloatString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
    CHECK(func.returnType == "");
    CHECK(func.helpText == "");

    lua_State* state = luaL_newstate();
    REQUIRE(state);
    ghoul::lua::push(state, 2.f);
    REQUIRE(func.function);
    func.function(state);
    CHECK(lua_gettop(state) == 0);
    lua_close(state);
}

TEST_CASE("Execution/LuaWrapper/Arguments:  variant(double, float, string) / string") {
    using namespace openspace::scripting;
    using namespace std::string_literals;

    LuaLibrary::Function func = codegen::lua::funcVariantDoubleFloatString;
    CHECK(func.name == "funcVariantDoubleFloatString");
    REQUIRE(func.arguments.size() == 1);
    {
        CHECK(func.arguments[0].name == "arg");
        CHECK(func.arguments[0].type == "Number | Number | String");
    }
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
