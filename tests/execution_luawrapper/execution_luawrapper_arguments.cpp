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
    /*
     * Some example documentation
     * that covers a few lines.
     * And another one for good measure
     */
    [[codegen::wraplua]] double foo(int arg) {
        return arg * 2.0;
    }

    [[codegen::wraplua]] void funcVoid() {
    }

    [[codegen::wraplua]] void funcBool(bool arg) {
    }

    [[codegen::wraplua]] void funcBoolDefaulted1(bool arg = true) {
    }

    [[codegen::wraplua]] void funcBoolDefaulted2(bool arg = { true }) {
    }

    [[codegen::wraplua]] void funcBoolMap(std::map<std::string, bool> arg) {
    }

    [[codegen::wraplua]] void funcBoolOptional(std::optional<bool> arg) {
    }

    [[codegen::wraplua]] void funcBoolVector(std::vector<bool> arg) {
    }

    [[codegen::wraplua]] void funcInt(int arg) {
    }

    [[codegen::wraplua]] void funcIntDefaulted1(int arg = 2) {
    }

    [[codegen::wraplua]] void funcIntDefaulted2(int arg = { 2 }) {
    }

    [[codegen::wraplua]] void funcIntMap(std::map<std::string, int> arg) {
    }

    [[codegen::wraplua]] void funcIntOptional(std::optional<int> arg) {
    }

    [[codegen::wraplua]] void funcIntVector(std::vector<int> arg) {
    }

    [[codegen::wraplua]] void funcDouble(double arg) {
    }

    [[codegen::wraplua]] void funcDoubleDefaulted1(double arg = 2.0) {
    }

    [[codegen::wraplua]] void funcDoubleDefaulted2(double arg = { 2.0 }) {
    }

    [[codegen::wraplua]] void funcDoubleMap(std::map<std::string, double> arg) {
    }

    [[codegen::wraplua]] void funcDoubleOptional(std::optional<double> arg) {
    }

    [[codegen::wraplua]] void funcDoubleVector(std::vector<double> arg) {
    }

    [[codegen::wraplua]] void funcFloat(float arg) {
    }

    [[codegen::wraplua]] void funcFloatDefaulted1(float arg = 2.f) {
    }

    [[codegen::wraplua]] void funcFloatDefaulted2(float arg = { 2.f }) {
    }

    [[codegen::wraplua]] void funcFloatMap(std::map<std::string, float> arg) {
    }

    [[codegen::wraplua]] void funcFloatOptional(std::optional<float> arg) {
    }

    [[codegen::wraplua]] void funcFloatVector(std::vector<float> arg) {
    }

    [[codegen::wraplua]] void funcString(std::string arg) {
    }

    [[codegen::wraplua]] void funcStringDefaulted1(std::string arg = "abc") {
    }

    [[codegen::wraplua]] void funcStringDefaulted2(std::string arg = { "abc" }) {
    }

    [[codegen::wraplua]] void funcStringMap(std::map<std::string, std::string> arg) {
    }

    [[codegen::wraplua]] void funcStringOptional(std::optional<std::string> arg) {
    }

    [[codegen::wraplua]] void funcStringVector(std::vector<std::string> arg) {
    }

    [[codegen::wraplua]] void funcPath(std::filesystem::path arg) {
    }

    [[codegen::wraplua]] void funcPathDefaulted1(std::filesystem::path arg = std::filesystem::path()) {
    }

    [[codegen::wraplua]] void funcPathDefaulted2(std::filesystem::path arg = std::filesystem::path()) {
    }

    [[codegen::wraplua]] void funcPathMap(std::map<std::string, std::filesystem::path> arg) {
    }

    [[codegen::wraplua]] void funcPathOptional(std::optional<std::filesystem::path> arg) {
    }

    [[codegen::wraplua]] void funcPathVector(std::vector<std::filesystem::path> arg) {
    }

    [[codegen::wraplua]] void funcIvec2(glm::ivec2 arg) {
    }

    [[codegen::wraplua]] void funcIvec2Defaulted1(glm::ivec2 arg = glm::ivec2(1, 2)) {
    }

    [[codegen::wraplua]] void funcIvec2Defaulted2(glm::ivec2 arg = { 1, 2 }) {
    }

    [[codegen::wraplua]] void funcIvec2Map(std::map<std::string, glm::ivec2> arg) {
    }

    [[codegen::wraplua]] void funcIvec2Optional(std::optional<glm::ivec2> arg) {
    }

    [[codegen::wraplua]] void funcIvec2Vector(std::vector<glm::ivec2> arg) {
    }

    [[codegen::wraplua]] void funcIvec3(glm::ivec3 arg) {
    }

    [[codegen::wraplua]] void funcIvec3Defaulted1(glm::ivec3 arg = glm::ivec3(1, 2, 3)) {
    }

    [[codegen::wraplua]] void funcIvec3Defaulted2(glm::ivec3 arg = { 1, 2, 3 }) {
    }

    [[codegen::wraplua]] void funcIvec3Map(std::map<std::string, glm::ivec3> arg) {
    }

    [[codegen::wraplua]] void funcIvec3Optional(std::optional<glm::ivec3> arg) {
    }

    [[codegen::wraplua]] void funcIvec3Vector(std::vector<glm::ivec3> arg) {
    }

    [[codegen::wraplua]] void funcIvec4(glm::ivec4 arg) {
    }

    [[codegen::wraplua]] void funcIvec4Defaulted1(glm::ivec4 arg = glm::ivec4(1, 2, 3, 4)) {
    }

    [[codegen::wraplua]] void funcIvec4Defaulted2(glm::ivec4 arg = { 1, 2, 3, 4 }) {
    }

    [[codegen::wraplua]] void funcIvec4Map(std::map<std::string, glm::ivec4> arg) {
    }

    [[codegen::wraplua]] void funcIvec4Optional(std::optional<glm::ivec4> arg) {
    }

    [[codegen::wraplua]] void funcIvec4Vector(std::vector<glm::ivec4> arg) {
    }

    [[codegen::wraplua]] void funcDvec2(glm::dvec2 arg) {
    }

    [[codegen::wraplua]] void funcDvec2Defaulted1(glm::dvec2 arg = glm::dvec2(1.0, 2.0)) {
    }

    [[codegen::wraplua]] void funcDvec2Defaulted2(glm::dvec2 arg = { 1.0, 2.0 }) {
    }

    [[codegen::wraplua]] void funcDvec2Map(std::map<std::string, glm::dvec2> arg) {
    }

    [[codegen::wraplua]] void funcDvec2Optional(std::optional<glm::dvec2> arg) {
    }

    [[codegen::wraplua]] void funcDvec2Vector(std::vector<glm::dvec2> arg) {
    }

    [[codegen::wraplua]] void funcDVec3(glm::dvec3 arg) {
    }

    [[codegen::wraplua]] void funcDVec3Defaulted1(glm::dvec3 arg = glm::dvec3(1.0, 2.0, 3.0)) {
    }

    [[codegen::wraplua]] void funcDVec3Defaulted2(glm::dvec3 arg = { 1.0, 2.0, 3.0 }) {
    }

    [[codegen::wraplua]] void funcDVec3Map(std::map<std::string, glm::dvec3> arg) {
    }

    [[codegen::wraplua]] void funcDVec3Optional(std::optional<glm::dvec3> arg) {
    }

    [[codegen::wraplua]] void funcDVec3Vector(std::vector<glm::dvec3> arg) {
    }

    [[codegen::wraplua]] void funcDVec4(glm::dvec4 arg) {
    }

    [[codegen::wraplua]] void funcDVec4Defaulted1(glm::dvec4 arg = glm::dvec4(1.0, 2.0, 3.0, 4.0)) {
    }

    [[codegen::wraplua]] void funcDVec4Defaulted2(glm::dvec4 arg = { 1.0, 2.0, 3.0, 4.0 }) {
    }

    [[codegen::wraplua]] void funcDVec4Map(std::map<std::string, glm::dvec4> arg) {
    }

    [[codegen::wraplua]] void funcDVec4Optional(std::optional<glm::dvec4> arg) {
    }

    [[codegen::wraplua]] void funcDVec4Vector(std::vector<glm::dvec4> arg) {
    }

    [[codegen::wraplua]] void funcVec2(glm::vec2 arg) {
    }

    [[codegen::wraplua]] void funcVec2Defaulted1(glm::vec2 arg = glm::vec2(1.f, 2.f)) {
    }

    [[codegen::wraplua]] void funcVec2Defaulted2(glm::vec2 arg = { 1.f, 2.f }) {
    }

    [[codegen::wraplua]] void funcVec2Map(std::map<std::string, glm::vec2> arg) {
    }

    [[codegen::wraplua]] void funcVec2Optional(std::optional<glm::vec2> arg) {
    }

    [[codegen::wraplua]] void funcVec2Vector(std::vector<glm::vec2> arg) {
    }

    [[codegen::wraplua]] void funcVec3(glm::vec3 arg) {
    }

    [[codegen::wraplua]] void funcVec3Defaulted1(glm::vec3 arg = glm::vec3(1.f, 2.f, 3.f)) {
    }

    [[codegen::wraplua]] void funcVec3Defaulted2(glm::vec3 arg = { 1.f, 2.f, 3.f }) {
    }

    [[codegen::wraplua]] void funcVec3Map(std::map<std::string, glm::vec3> arg) {
    }

    [[codegen::wraplua]] void funcVec3Optional(std::optional<glm::vec3> arg) {
    }

    [[codegen::wraplua]] void funcVec3Vector(std::vector<glm::vec3> arg) {
    }

    [[codegen::wraplua]] void funcVec4(glm::vec4 arg) {
    }

    [[codegen::wraplua]] void funcVec4Defaulted1(glm::vec4 arg = glm::vec4(1.f, 2.f, 3.f, 4.f)) {
    }

    [[codegen::wraplua]] void funcVec4Defaulted2(glm::vec4 arg = { 1.f, 2.f, 3.f, 4.f }) {
    }

    [[codegen::wraplua]] void funcVec4Map(std::map<std::string, glm::vec4> arg) {
    }

    [[codegen::wraplua]] void funcVec4Optional(std::optional<glm::vec4> arg) {
    }

    [[codegen::wraplua]] void funcVec4Vector(std::vector<glm::vec4> arg) {
    }

    [[codegen::wraplua]] void funcMat2x2(glm::mat2x2 arg) {
    }

    [[codegen::wraplua]] void funcMat2x2Defaulted1(glm::mat2x2 arg = glm::mat2x2(1.f, 2.f, 3.f, 4.f)) {
    }

    [[codegen::wraplua]] void funcMat2x2Defaulted2(glm::mat2x2 arg = { 1.f, 2.f, 3.f, 4.f }) {
    }

    [[codegen::wraplua]] void funcMat2x2Map(std::map<std::string, glm::mat2x2> arg) {
    }

    [[codegen::wraplua]] void funcMat2x2Optional(std::optional<glm::mat2x2> arg) {
    }

    [[codegen::wraplua]] void funcMat2x2Vector(std::vector<glm::mat2x2> arg) {
    }

    [[codegen::wraplua]] void funcMat2x3(glm::mat2x3 arg) {
    }

    [[codegen::wraplua]] void funcMat2x3Defaulted1(glm::mat2x3 arg = glm::mat2x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
    }

    [[codegen::wraplua]] void funcMat2x3Defaulted2(glm::mat2x3 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f }) {
    }

    [[codegen::wraplua]] void funcMat2x3Map(std::map<std::string, glm::mat2x3> arg) {
    }

    [[codegen::wraplua]] void funcMat2x3Optional(std::optional<glm::mat2x3> arg) {
    }

    [[codegen::wraplua]] void funcMat2x3Vector(std::vector<glm::mat2x3> arg) {
    }

    [[codegen::wraplua]] void funcMat2x4(glm::mat2x4 arg) {
    }

    [[codegen::wraplua]] void funcMat2x4Defaulted1(glm::mat2x4 arg = glm::mat2x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
    }

    [[codegen::wraplua]] void funcMat2x4Defaulted2(glm::mat2x4 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f }) {
    }

    [[codegen::wraplua]] void funcMat2x4Map(std::map<std::string, glm::mat2x4> arg) {
    }

    [[codegen::wraplua]] void funcMat2x4Optional(std::optional<glm::mat2x4> arg) {
    }

    [[codegen::wraplua]] void funcMat2x4Vector(std::vector<glm::mat2x4> arg) {
    }

    [[codegen::wraplua]] void funcMat3x2(glm::mat3x2 arg) {
    }

    [[codegen::wraplua]] void funcMat3x2Defaulted1(glm::mat3x2 arg = glm::mat3x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f)) {
    }

    [[codegen::wraplua]] void funcMat3x2Defaulted2(glm::mat3x2 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f }) {
    }

    [[codegen::wraplua]] void funcMat3x2Map(std::map<std::string, glm::mat3x2> arg) {
    }

    [[codegen::wraplua]] void funcMat3x2Optional(std::optional<glm::mat3x2> arg) {
    }

    [[codegen::wraplua]] void funcMat3x2Vector(std::vector<glm::mat3x2> arg) {
    }

    [[codegen::wraplua]] void funcMat3x3(glm::mat3x3 arg) {
    }

    [[codegen::wraplua]] void funcMat3x3Defaulted1(glm::mat3x3 arg = glm::mat3x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)) {
    }

    [[codegen::wraplua]] void funcMat3x3Defaulted2(glm::mat3x3 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f }) {
    }

    [[codegen::wraplua]] void funcMat3x3Map(std::map<std::string, glm::mat3x3> arg) {
    }

    [[codegen::wraplua]] void funcMat3x3Optional(std::optional<glm::mat3x3> arg) {
    }

    [[codegen::wraplua]] void funcMat3x3Vector(std::vector<glm::mat3x3> arg) {
    }

    [[codegen::wraplua]] void funcMat3x4(glm::mat3x4 arg) {
    }

    [[codegen::wraplua]] void funcMat3x4Defaulted1(glm::mat3x4 arg = glm::mat3x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
    }

    [[codegen::wraplua]] void funcMat3x4Defaulted2(glm::mat3x4 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f }) {
    }

    [[codegen::wraplua]] void funcMat3x4Map(std::map<std::string, glm::mat3x4> arg) {
    }

    [[codegen::wraplua]] void funcMat3x4Optional(std::optional<glm::mat3x4> arg) {
    }

    [[codegen::wraplua]] void funcMat3x4Vector(std::vector<glm::mat3x4> arg) {
    }

    [[codegen::wraplua]] void funcMat4x2(glm::mat4x2 arg) {
    }

    [[codegen::wraplua]] void funcMat4x2Defaulted1(glm::mat4x2 arg = glm::mat4x2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f)) {
    }

    [[codegen::wraplua]] void funcMat4x2Defaulted2(glm::mat4x2 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f }) {
    }

    [[codegen::wraplua]] void funcMat4x2Map(std::map<std::string, glm::mat4x2> arg) {
    }

    [[codegen::wraplua]] void funcMat4x2Optional(std::optional<glm::mat4x2> arg) {
    }

    [[codegen::wraplua]] void funcMat4x2Vector(std::vector<glm::mat4x2> arg) {
    }

    [[codegen::wraplua]] void funcMat4x3(glm::mat4x3 arg) {
    }

    [[codegen::wraplua]] void funcMat4x3Defaulted1(glm::mat4x3 arg = glm::mat4x3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f)) {
    }

    [[codegen::wraplua]] void funcMat4x3Defaulted2(glm::mat4x3 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f }) {
    }

    [[codegen::wraplua]] void funcMat4x3Map(std::map<std::string, glm::mat4x3> arg) {
    }

    [[codegen::wraplua]] void funcMat4x3Optional(std::optional<glm::mat4x3> arg) {
    }

    [[codegen::wraplua]] void funcMat4x3Vector(std::vector<glm::mat4x3> arg) {
    }

    [[codegen::wraplua]] void funcMat4x4(glm::mat4x4 arg) {
    }

    [[codegen::wraplua]] void funcMat4x4Defaulted1(glm::mat4x4 arg = glm::mat4x4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f)) {
    }

    [[codegen::wraplua]] void funcMat4x4Defaulted2(glm::mat4x4 arg = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f }) {
    }

    [[codegen::wraplua]] void funcMat4x4Map(std::map<std::string, glm::mat4x4> arg) {
    }

    [[codegen::wraplua]] void funcMat4x4Optional(std::optional<glm::mat4x4> arg) {
    }

    [[codegen::wraplua]] void funcMat4x4Vector(std::vector<glm::mat4x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x2(glm::dmat2x2 arg) {
    }

    [[codegen::wraplua]] void funcDMat2x2Defaulted1(glm::dmat2x2 arg = glm::dmat2x2(1.0, 2.0, 3.0, 4.0)) {
    }

    [[codegen::wraplua]] void funcDMat2x2Defaulted2(glm::dmat2x2 arg = { 1.0, 2.0, 3.0, 4.0 }) {
    }

    [[codegen::wraplua]] void funcDMat2x2Map(std::map<std::string, glm::dmat2x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x2Optional(std::optional<glm::dmat2x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x2Vector(std::vector<glm::dmat2x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x3(glm::dmat2x3 arg) {
    }

    [[codegen::wraplua]] void funcDMat2x3Defaulted1(glm::dmat2x3 arg = glm::dmat2x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
    }

    [[codegen::wraplua]] void funcDMat2x3Defaulted2(glm::dmat2x3 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 }) {
    }

    [[codegen::wraplua]] void funcDMat2x3Map(std::map<std::string, glm::dmat2x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x3Optional(std::optional<glm::dmat2x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x3Vector(std::vector<glm::dmat2x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x4(glm::dmat2x4 arg) {
    }

    [[codegen::wraplua]] void funcDMat2x4Defaulted1(glm::dmat2x4 arg = glm::dmat2x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
    }

    [[codegen::wraplua]] void funcDMat2x4Defaulted2(glm::dmat2x4 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }) {
    }

    [[codegen::wraplua]] void funcDMat2x4Map(std::map<std::string, glm::dmat2x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x4Optional(std::optional<glm::dmat2x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat2x4Vector(std::vector<glm::dmat2x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x2(glm::dmat3x2 arg) {
    }

    [[codegen::wraplua]] void funcDMat3x2Defaulted1(glm::dmat3x2 arg = glm::dmat3x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)) {
    }

    [[codegen::wraplua]] void funcDMat3x2Defaulted2(glm::dmat3x2 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 }) {
    }

    [[codegen::wraplua]] void funcDMat3x2Map(std::map<std::string, glm::dmat3x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x2Optional(std::optional<glm::dmat3x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x2Vector(std::vector<glm::dmat3x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x3(glm::dmat3x3 arg) {
    }

    [[codegen::wraplua]] void funcDMat3x3Defaulted1(glm::dmat3x3 arg = glm::dmat3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)) {
    }

    [[codegen::wraplua]] void funcDMat3x3Defaulted2(glm::dmat3x3 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 }) {
    }

    [[codegen::wraplua]] void funcDMat3x3Map(std::map<std::string, glm::dmat3x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x3Optional(std::optional<glm::dmat3x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x3Vector(std::vector<glm::dmat3x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x4(glm::dmat3x4 arg) {
    }

    [[codegen::wraplua]] void funcDMat3x4Defaulted1(glm::dmat3x4 arg = glm::dmat3x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
    }

    [[codegen::wraplua]] void funcDMat3x4Defaulted2(glm::dmat3x4 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 }) {
    }

    [[codegen::wraplua]] void funcDMat3x4Map(std::map<std::string, glm::dmat3x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x4Optional(std::optional<glm::dmat3x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat3x4Vector(std::vector<glm::dmat3x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x2(glm::dmat4x2 arg) {
    }

    [[codegen::wraplua]] void funcDMat4x2Defaulted1(glm::dmat4x2 arg = glm::dmat4x2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)) {
    }

    [[codegen::wraplua]] void funcDMat4x2Defaulted2(glm::dmat4x2 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }) {
    }

    [[codegen::wraplua]] void funcDMat4x2Map(std::map<std::string, glm::dmat4x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x2Optional(std::optional<glm::dmat4x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x2Vector(std::vector<glm::dmat4x2> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x3(glm::dmat4x3 arg) {
    }

    [[codegen::wraplua]] void funcDMat4x3Defaulted1(glm::dmat4x3 arg = glm::dmat4x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0)) {
    }

    [[codegen::wraplua]] void funcDMat4x3Defaulted2(glm::dmat4x3 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 }) {
    }

    [[codegen::wraplua]] void funcDMat4x3Map(std::map<std::string, glm::dmat4x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x3Optional(std::optional<glm::dmat4x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x3Vector(std::vector<glm::dmat4x3> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x4(glm::dmat4x4 arg) {
    }

    [[codegen::wraplua]] void funcDMat4x4Defaulted1(glm::dmat4x4 arg = glm::dmat4x4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0)) {
    }

    [[codegen::wraplua]] void funcDMat4x4Defaulted2(glm::dmat4x4 arg = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 }) {
    }

    [[codegen::wraplua]] void funcDMat4x4Map(std::map<std::string, glm::dmat4x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x4Optional(std::optional<glm::dmat4x4> arg) {
    }

    [[codegen::wraplua]] void funcDMat4x4Vector(std::vector<glm::dmat4x4> arg) {
    }

    [[codegen::wraplua]] void funcDictionary(ghoul::Dictionary arg) {
    }

    [[codegen::wraplua]] void funcDictionaryDefaulted1(ghoul::Dictionary arg = ghoul::Dictionary()) {
    }

    [[codegen::wraplua]] void funcDictionaryDefaulted2(ghoul::Dictionary arg = {}) {
    }

    [[codegen::wraplua]] void funcDictionaryMap(std::map<std::string, ghoul::Dictionary> arg) {
    }

    [[codegen::wraplua]] void funcDictionaryOptional(std::optional<ghoul::Dictionary> arg) {
    }

    [[codegen::wraplua]] void funcDictionaryVector(std::vector<ghoul::Dictionary> arg) {
    }

    [[codegen::wraplua]] void funcVariant(std::variant<bool, int> arg) {
    }

    [[codegen::wraplua]] void funcVariantDoubleFloatString(std::variant<double, float, std::string> arg) {
    }

#include "execution_luawrapper_arguments_codegen.cpp"
} // namespace

TEST_CASE("Execution/LuaWrapper/Comments:  Simple") {
    CHECK(codegen::lua::foo.name == "foo");
    CHECK(codegen::lua::foo.function);
    CHECK(codegen::lua::foo.argumentText == "arg: Integer -> Number");
    CHECK(
        codegen::lua::foo.helpText ==
        "Some example documentation that covers a few lines. "
        "And another one for good measure"
    );
}
