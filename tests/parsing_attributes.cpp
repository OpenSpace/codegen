/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021                                                                    *
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

TEST_CASE("Parsing Attribute: Attributes (success)", "[parsing]") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // keyValue documentation
        float keyValue [[codegen::key("KeyKey")]];

        // keyValueOptional documentation
        std::optional<float> keyValueOptional [[codegen::key("KeyKeyOptional")]];

        // keyValueVector documentation
        std::vector<float> keyValueVector [[codegen::key("KeyKeyVector")]];

        // inRangeValueInt documentation
        int inRangeValueInt [[codegen::inrange(-2, 2)]];

        // inRangeValueIntOptional documentation
        std::optional<int> inRangeValueIntOptional [[codegen::inrange(-2, 2)]];

        // inRangeValueIntVector documentation
        std::vector<int> inRangeValueIntVector [[codegen::inrange(-2, 2)]];

        // inRangeValueFloat documentation
        float inRangeValueFloat [[codegen::inrange(-0.5, 0.75)]];

        // inRangeValueFloatOptional documentation
        std::optional<float> inRangeValueFloatOptional [[codegen::inrange(-0.5, 0.75)]];

        // inRangeValueFloatVector documentation
        std::vector<float> inRangeValueFloatVector [[codegen::inrange(-0.5, 0.75)]];

        // notInRangeValueInt documentation
        int notInRangeValueInt [[codegen::notinrange(5, 7)]];

        // notInRangeValueIntOptional documentation
        std::optional<int> notInRangeValueIntOptional [[codegen::notinrange(5, 7)]];

        // notInRangeValueIntVector documentation
        std::vector<int> notInRangeValueIntVector [[codegen::notinrange(5, 7)]];

        // notInRangeValueFloat documentation
        float notInRangeValueFloat [[codegen::notinrange(-0.5, 0.5)]];

        // notInRangeValueFloatOptional documentation
        std::optional<float> notInRangeValueFloatOptional [[codegen::notinrange(-0.5, 0.5)]];

        // notInRangeValueFloatVector documentation
        std::vector<float> notInRangeValueFloatVector [[codegen::notinrange(-0.5, 0.5)]];

        // lessValueInt documentation
        int lessValueInt [[codegen::less(-5)]];
        
        // lessValueIntOptional documentation
        std::optional<int> lessValueIntOptional [[codegen::less(-5)]];

        // lessValueIntVector documentation
        std::vector<int> lessValueIntVector [[codegen::less(-5)]];

        // lessValueFloat documentation
        float lessValueFloat [[codegen::less(15.0)]];

        // lessValueFloatOptional documentation
        std::optional<float> lessValueFloatOptional [[codegen::less(15.0)]];

        // lessValueFloatVector documentation
        std::vector<float> lessValueFloatVector [[codegen::less(15.0)]];

        // lessEqualValueInt documentation
        int lessEqualValueInt [[codegen::lessequal(25)]];

        // lessEqualValueIntOptional documentation
        std::optional<int> lessEqualValueIntOptional [[codegen::lessequal(25)]];

        // lessEqualValueIntVector documentation
        std::vector<int> lessEqualValueIntVector [[codegen::lessequal(25)]];

        // lessEqualValueFloat documentation
        float lessEqualValueFloat [[codegen::lessequal(12.0)]];

        // lessEqualValueFloatOptional documentation
        std::optional<float> lessEqualValueFloatOptional [[codegen::lessequal(12.0)]];

        // lessEqualValueFloatVector documentation
        std::vector<float> lessEqualValueFloatVector [[codegen::lessequal(12.0)]];

        // greaterValueInt documentation
        int greaterValueInt [[codegen::greater(45)]];

        // greaterValueIntOptional documentation
        std::optional<int> greaterValueIntOptional [[codegen::greater(45)]];

        // greaterValueIntVector documentation
        std::vector<int> greaterValueIntVector [[codegen::greater(45)]];

        // greaterValueFloat documentation
        float greaterValueFloat [[codegen::greater(-5.0)]];

        // greaterValueFloatOptional documentation
        std::optional<float> greaterValueFloatOptional [[codegen::greater(-5.0)]];

        // greaterValueFloatVector documentation
        std::vector<float> greaterValueFloatVector [[codegen::greater(-5.0)]];

        // greaterEqualValueInt documentation
        int greaterEqualValueInt [[codegen::greaterequal(2)]];

        // greaterEqualValueIntOptional documentation
        std::optional<int> greaterEqualValueIntOptional [[codegen::greaterequal(2)]];

        // greaterEqualValueIntVector documentation
        std::vector<int> greaterEqualValueIntVector [[codegen::greaterequal(2)]];

        // greaterEqualValueFloat documentation
        float greaterEqualValueFloat [[codegen::greaterequal(-25.0)]];

        // greaterEqualValueFloatOptional documentation
        std::optional<float> greaterEqualValueFloatOptional [[codegen::greaterequal(-25.0)]];

        // greaterEqualValueFloatVector documentation
        std::vector<float> greaterEqualValueFloatVector [[codegen::greaterequal(-25.0)]];

        // unequalValueInt documentation
        int unequalValueInt [[codegen::unequal(1)]];

        // unequalValueIntOptional documentation
        std::optional<int> unequalValueIntOptional [[codegen::unequal(1)]];

        // unequalValueIntVector documentation
        std::vector<int> unequalValueIntVector [[codegen::unequal(1)]];

        // unequalValueFloat documentation
        float unequalValueFloat [[codegen::unequal(123.0)]];

        // unequalValueFloatOptional documentation
        std::optional<float> unequalValueFloatOptional [[codegen::unequal(123.0)]];

        // unequalValueFloatVector documentation
        std::vector<float> unequalValueFloatVector [[codegen::unequal(123.0)]];

        // [[codegen::verbatim(description)]]
        bool descValue;

        // inListValue1 documentation
        std::string inListValue1 [[codegen::inlist("A", "B", "C")]];

        // inListValue1Optional documentation
        std::optional<std::string> inListValue1Optional [[codegen::inlist("A", "B", "C")]];

        // inListValue1Vector documentation
        std::vector<std::string> inListValue1Vector [[codegen::inlist("A", "B", "C")]];

        // inListValue2 documentation
        std::string inListValue2 [[codegen::inlist(List)]];

        // inListValue2Optional documentation
        std::optional<std::string> inListValue2Optional [[codegen::inlist(List)]];

        // inListValue2Vector documentation
        std::vector<std::string> inListValue2Vector [[codegen::inlist(List)]];

        // unequalValueString documentation
        std::string unequalValueString [[codegen::unequal("abcdef")]];

        // unequalValueStringOptional documentation
        std::optional<std::string> unequalValueStringOptional [[codegen::unequal("abcdef")]];

        // unequalValueStringVector documentation
        std::vector<std::string> unequalValueStringVector [[codegen::unequal("abcdef")]];

        // referenceValue documentation
        std::monostate referenceValue [[codegen::reference("abc")]];

        // referenceValueOptional documentation
        std::optional<std::monostate> referenceValueOptional [[codegen::reference("abc")]];

        // referenceValueVector documentation
        std::vector<std::monostate> referenceValueVector [[codegen::reference("abc")]];
    };
)";
    Struct* s = parseRootStruct(Source);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 58);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "keyValue");
        CHECK(var->key == "\"KeyKey\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "keyValue documentation");
        CHECK(var->attributes.key == "\"KeyKey\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinlist.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "keyValueOptional");
        CHECK(var->key == "\"KeyKeyOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "keyValueOptional documentation");
        CHECK(var->attributes.key == "\"KeyKeyOptional\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinlist.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "keyValueVector");
        CHECK(var->key == "\"KeyKeyVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "keyValueVector documentation");
        CHECK(var->attributes.key == "\"KeyKeyVector\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinlist.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[3];
        CHECK(var->name == "inRangeValueInt");
        CHECK(var->key == "\"InRangeValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "inRangeValueInt documentation");
        CHECK(var->attributes.inrange == "-2, 2");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinlist.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIntOptional");
        CHECK(var->key == "\"InRangeValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "inRangeValueIntOptional documentation");
        CHECK(var->attributes.inrange == "-2, 2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIntVector");
        CHECK(var->key == "\"InRangeValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "inRangeValueIntVector documentation");
        CHECK(var->attributes.inrange == "-2, 2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloat");
        CHECK(var->key == "\"InRangeValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "inRangeValueFloat documentation");
        CHECK(var->attributes.inrange == "-0.5, 0.75");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloatOptional");
        CHECK(var->key == "\"InRangeValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "inRangeValueFloatOptional documentation");
        CHECK(var->attributes.inrange == "-0.5, 0.75");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloatVector");
        CHECK(var->key == "\"InRangeValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "inRangeValueFloatVector documentation");
        CHECK(var->attributes.inrange == "-0.5, 0.75");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueInt");
        CHECK(var->key == "\"NotInRangeValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "notInRangeValueInt documentation");
        CHECK(var->attributes.notinrange == "5, 7");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIntOptional");
        CHECK(var->key == "\"NotInRangeValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "notInRangeValueIntOptional documentation");
        CHECK(var->attributes.notinrange == "5, 7");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIntVector");
        CHECK(var->key == "\"NotInRangeValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "notInRangeValueIntVector documentation");
        CHECK(var->attributes.notinrange == "5, 7");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloat");
        CHECK(var->key == "\"NotInRangeValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "notInRangeValueFloat documentation");
        CHECK(var->attributes.notinrange == "-0.5, 0.5");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloatOptional");
        CHECK(var->key == "\"NotInRangeValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "notInRangeValueFloatOptional documentation");
        CHECK(var->attributes.notinrange == "-0.5, 0.5");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloatVector");
        CHECK(var->key == "\"NotInRangeValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "notInRangeValueFloatVector documentation");
        CHECK(var->attributes.notinrange == "-0.5, 0.5");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "lessValueInt");
        CHECK(var->key == "\"LessValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "lessValueInt documentation");
        CHECK(var->attributes.less == "-5");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "lessValueIntOptional");
        CHECK(var->key == "\"LessValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "lessValueIntOptional documentation");
        CHECK(var->attributes.less == "-5");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "lessValueIntVector");
        CHECK(var->key == "\"LessValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "lessValueIntVector documentation");
        CHECK(var->attributes.less == "-5");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloat");
        CHECK(var->key == "\"LessValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "lessValueFloat documentation");
        CHECK(var->attributes.less == "15.0");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloatOptional");
        CHECK(var->key == "\"LessValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "lessValueFloatOptional documentation");
        CHECK(var->attributes.less == "15.0");
        
        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloatVector");
        CHECK(var->key == "\"LessValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "lessValueFloatVector documentation");
        CHECK(var->attributes.less == "15.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueInt");
        CHECK(var->key == "\"LessEqualValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "lessEqualValueInt documentation");
        CHECK(var->attributes.lessequal == "25");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIntOptional");
        CHECK(var->key == "\"LessEqualValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "lessEqualValueIntOptional documentation");
        CHECK(var->attributes.lessequal == "25");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIntVector");
        CHECK(var->key == "\"LessEqualValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "lessEqualValueIntVector documentation");
        CHECK(var->attributes.lessequal == "25");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloat");
        CHECK(var->key == "\"LessEqualValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "lessEqualValueFloat documentation");
        CHECK(var->attributes.lessequal == "12.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloatOptional");
        CHECK(var->key == "\"LessEqualValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "lessEqualValueFloatOptional documentation");
        CHECK(var->attributes.lessequal == "12.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloatVector");
        CHECK(var->key == "\"LessEqualValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "lessEqualValueFloatVector documentation");
        CHECK(var->attributes.lessequal == "12.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "greaterValueInt");
        CHECK(var->key == "\"GreaterValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "greaterValueInt documentation");
        CHECK(var->attributes.greater == "45");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIntOptional");
        CHECK(var->key == "\"GreaterValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "greaterValueIntOptional documentation");
        CHECK(var->attributes.greater == "45");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIntVector");
        CHECK(var->key == "\"GreaterValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "greaterValueIntVector documentation");
        CHECK(var->attributes.greater == "45");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloat");
        CHECK(var->key == "\"GreaterValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "greaterValueFloat documentation");
        CHECK(var->attributes.greater == "-5.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloatOptional");
        CHECK(var->key == "\"GreaterValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "greaterValueFloatOptional documentation");
        CHECK(var->attributes.greater == "-5.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloatVector");
        CHECK(var->key == "\"GreaterValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "greaterValueFloatVector documentation");
        CHECK(var->attributes.greater == "-5.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[33];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueInt");
        CHECK(var->key == "\"GreaterEqualValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "greaterEqualValueInt documentation");
        CHECK(var->attributes.greaterequal == "2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[34];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIntOptional");
        CHECK(var->key == "\"GreaterEqualValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "greaterEqualValueIntOptional documentation");
        CHECK(var->attributes.greaterequal == "2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[35];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIntVector");
        CHECK(var->key == "\"GreaterEqualValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "greaterEqualValueIntVector documentation");
        CHECK(var->attributes.greaterequal == "2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[36];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloat");
        CHECK(var->key == "\"GreaterEqualValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "greaterEqualValueFloat documentation");
        CHECK(var->attributes.greaterequal == "-25.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[37];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloatOptional");
        CHECK(var->key == "\"GreaterEqualValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "greaterEqualValueFloatOptional documentation");
        CHECK(var->attributes.greaterequal == "-25.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[38];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloatVector");
        CHECK(var->key == "\"GreaterEqualValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "greaterEqualValueFloatVector documentation");
        CHECK(var->attributes.greaterequal == "-25.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[39];
        REQUIRE(var);
        CHECK(var->name == "unequalValueInt");
        CHECK(var->key == "\"UnequalValueInt\"");
        CHECK(var->typeString == "int");
        CHECK(var->comment == "unequalValueInt documentation");
        CHECK(var->attributes.unequal == "1");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[40];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIntOptional");
        CHECK(var->key == "\"UnequalValueIntOptional\"");
        CHECK(var->typeString == "std::optional<int>");
        CHECK(var->comment == "unequalValueIntOptional documentation");
        CHECK(var->attributes.unequal == "1");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[41];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIntVector");
        CHECK(var->key == "\"UnequalValueIntVector\"");
        CHECK(var->typeString == "std::vector<int>");
        CHECK(var->comment == "unequalValueIntVector documentation");
        CHECK(var->attributes.unequal == "1");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[42];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloat");
        CHECK(var->key == "\"UnequalValueFloat\"");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "unequalValueFloat documentation");
        CHECK(var->attributes.unequal == "123.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[43];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloatOptional");
        CHECK(var->key == "\"UnequalValueFloatOptional\"");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "unequalValueFloatOptional documentation");
        CHECK(var->attributes.unequal == "123.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[44];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloatVector");
        CHECK(var->key == "\"UnequalValueFloatVector\"");
        CHECK(var->typeString == "std::vector<float>");
        CHECK(var->comment == "unequalValueFloatVector documentation");
        CHECK(var->attributes.unequal == "123.0");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[45];
        REQUIRE(var);
        CHECK(var->name == "descValue");
        CHECK(var->key == "\"DescValue\"");
        CHECK(var->typeString == "bool");
        CHECK(var->comment == "[[codegen::verbatim(description)]]");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[46];
        REQUIRE(var);
        CHECK(var->name == "inListValue1");
        CHECK(var->key == "\"InListValue1\"");
        CHECK(var->typeString == "std::string");
        CHECK(var->comment == "inListValue1 documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[47];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Optional");
        CHECK(var->key == "\"InListValue1Optional\"");
        CHECK(var->typeString == "std::optional<std::string>");
        CHECK(var->comment == "inListValue1Optional documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[48];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Vector");
        CHECK(var->key == "\"InListValue1Vector\"");
        CHECK(var->typeString == "std::vector<std::string>");
        CHECK(var->comment == "inListValue1Vector documentation");
        CHECK(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[49];
        REQUIRE(var);
        CHECK(var->name == "inListValue2");
        CHECK(var->key == "\"InListValue2\"");
        CHECK(var->typeString == "std::string");
        CHECK(var->comment == "inListValue2 documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[50];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Optional");
        CHECK(var->key == "\"InListValue2Optional\"");
        CHECK(var->typeString == "std::optional<std::string>");
        CHECK(var->comment == "inListValue2Optional documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[51];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Vector");
        CHECK(var->key == "\"InListValue2Vector\"");
        CHECK(var->typeString == "std::vector<std::string>");
        CHECK(var->comment == "inListValue2Vector documentation");
        CHECK(var->attributes.inlist == "List");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[52];
        REQUIRE(var);
        CHECK(var->name == "unequalValueString");
        CHECK(var->key == "\"UnequalValueString\"");
        CHECK(var->typeString == "std::string");
        CHECK(var->comment == "unequalValueString documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[53];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringOptional");
        CHECK(var->key == "\"UnequalValueStringOptional\"");
        CHECK(var->typeString == "std::optional<std::string>");
        CHECK(var->comment == "unequalValueStringOptional documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[54];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringVector");
        CHECK(var->key == "\"UnequalValueStringVector\"");
        CHECK(var->typeString == "std::vector<std::string>");
        CHECK(var->comment == "unequalValueStringVector documentation");
        CHECK(var->attributes.unequal == "\"abcdef\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[55];
        REQUIRE(var);
        CHECK(var->name == "referenceValue");
        CHECK(var->key == "\"ReferenceValue\"");
        CHECK(var->typeString == "std::monostate");
        CHECK(var->comment == "referenceValue documentation");
        CHECK(var->attributes.reference == "\"abc\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[56];
        REQUIRE(var);
        CHECK(var->name == "referenceValueOptional");
        CHECK(var->key == "\"ReferenceValueOptional\"");
        CHECK(var->typeString == "std::optional<std::monostate>");
        CHECK(var->comment == "referenceValueOptional documentation");
        CHECK(var->attributes.reference == "\"abc\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[57];
        REQUIRE(var);
        CHECK(var->name == "referenceValueVector");
        CHECK(var->key == "\"ReferenceValueVector\"");
        CHECK(var->typeString == "std::vector<std::monostate>");
        CHECK(var->comment == "referenceValueVector documentation");
        CHECK(var->attributes.reference == "\"abc\"");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.inrange.empty());
        CHECK(var->attributes.key.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.unequal.empty());
    }

    std::string r = generateResult(s);
    CHECK(!r.empty());
}

TEST_CASE("Parsing Attribute: Multiple Attributes (success)", "[parsing]") {
    constexpr const char Source[] = R"(
    struct [[codegen::Dictionary(MultipleAttributes)]] Parameters {
        // keyInRangeValue documentation
        float keyInRangeValue [[codegen::key(KeyKey), codegen::inrange(-2, 2)]];

        // keyInRangeValueOptional documentation
        std::optional<float> keyValueInRangeOptional [[codegen::key(KeyKeyOptional), codegen::inrange(-2, 3)]];
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s->variables.size() == 2);
    
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "keyInRangeValue");
        CHECK(var->key == "KeyKey");
        CHECK(var->typeString == "float");
        CHECK(var->comment == "keyInRangeValue documentation");
        CHECK(var->attributes.key == "KeyKey");
        CHECK(var->attributes.inrange == "-2, 2");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "keyValueInRangeOptional");
        CHECK(var->key == "KeyKeyOptional");
        CHECK(var->typeString == "std::optional<float>");
        CHECK(var->comment == "keyInRangeValueOptional documentation");
        CHECK(var->attributes.key == "KeyKeyOptional");
        CHECK(var->attributes.inrange == "-2, 3");

        CHECK(var->attributes.annotation.empty());
        CHECK(var->attributes.greater.empty());
        CHECK(var->attributes.greaterequal.empty());
        CHECK(var->attributes.inlist.empty());
        CHECK(var->attributes.less.empty());
        CHECK(var->attributes.lessequal.empty());
        CHECK(var->attributes.notinrange.empty());
        CHECK(var->attributes.reference.empty());
        CHECK(var->attributes.unequal.empty());
    }
}

TEST_CASE("Parsing Attribute: Struct Attribute empty noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive()]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(s->variables[0]->typeString == "int");
}

TEST_CASE("Parsing Attribute: Struct Attribute true noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive(true)]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(s->variables[0]->typeString == "int");
}

TEST_CASE("Parsing Attribute: Struct Attribute false noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::noexhaustive(false)]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s);
    CHECK(s->attributes.dictionary == "Par");
    CHECK(!s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]);
    CHECK(s->variables[0]->name == "value");
    CHECK(s->variables[0]->key == "\"Value\"");
    CHECK(s->variables[0]->typeString == "int");
}
