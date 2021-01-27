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
        float keyValue [[codegen::key(KeyKey)]];

        // keyValueOptional documentation
        std::optional<float> keyValueOptional [[codegen::key(KeyKeyOptional)]];

        // inRangeValueInt documentation
        int inRangeValueInt [[codegen::inrange(-2, 2)]];

        // inRangeValueIntOptional documentation
        std::optional<int> inRangeValueIntOptional [[codegen::inrange(-2, 2)]];

        // inRangeValueFloat documentation
        float inRangeValueFloat [[codegen::inrange(-0.5, 0.75)]];

        // inRangeValueFloatOptional documentation
        std::optional<float> inRangeValueFloatOptional [[codegen::inrange(-0.5, 0.75)]];

        // notInRangeValueInt documentation
        int notInRangeValueInt [[codegen::notinrange(5, 7)]];

        // notInRangeValueIntOptional documentation
        std::optional<int> notInRangeValueIntOptional [[codegen::notinrange(5, 7)]];

        // notInRangeValueFloat documentation
        float notInRangeValueFloat [[codegen::notinrange(-0.5, 0.5)]];

        // notInRangeValueFloatOptional documentation
        std::optional<float> notInRangeValueFloatOptional [[codegen::notinrange(-0.5, 0.5)]];

        // lessValueInt documentation
        int lessValueInt [[codegen::less(-5)]];
        
        // lessValueIntOptional documentation
        std::optional<int> lessValueIntOptional [[codegen::less(-5)]];

        // lessValueFloat documentation
        float lessValueFloat [[codegen::less(15.0)]];

        // lessValueFloatOptional documentation
        std::optional<float> lessValueFloatOptional [[codegen::less(15.0)]];

        // lessEqualValueInt documentation
        int lessEqualValueInt [[codegen::lessequal(25)]];

        // lessEqualValueIntOptional documentation
        std::optional<int> lessEqualValueIntOptional [[codegen::lessequal(25)]];

        // lessEqualValueFloat documentation
        float lessEqualValueFloat [[codegen::lessequal(12.0)]];

        // lessEqualValueFloatOptional documentation
        std::optional<float> lessEqualValueFloatOptional [[codegen::lessequal(12.0)]];

        // greaterValueInt documentation
        int greaterValueInt [[codegen::greater(45)]];

        // greaterValueIntOptional documentation
        std::optional<int> greaterValueIntOptional [[codegen::greater(45)]];

        // greaterValueFloat documentation
        float greaterValueFloat [[codegen::greater(-5.0)]];

        // greaterValueFloatOptional documentation
        std::optional<float> greaterValueFloatOptional [[codegen::greater(-5.0)]];

        // greaterEqualValueInt documentation
        int greaterEqualValueInt [[codegen::greaterequal(2)]];

        // greaterEqualValueIntOptional documentation
        std::optional<int> greaterEqualValueIntOptional [[codegen::greaterequal(2)]];

        // greaterEqualValueFloat documentation
        float greaterEqualValueFloat [[codegen::greaterequal(-25.0)]];

        // greaterEqualValueFloatOptional documentation
        std::optional<float> greaterEqualValueFloatOptional [[codegen::greaterequal(-25.0)]];

        // unequalValueInt documentation
        int unequalValueInt [[codegen::unequal(1)]];

        // unequalValueIntOptional documentation
        std::optional<int> unequalValueIntOptional [[codegen::unequal(1)]];

        // unequalValueFloat documentation
        float unequalValueFloat [[codegen::unequal(123.0)]];

        // unequalValueFloatOptional documentation
        std::optional<float> unequalValueFloatOptional [[codegen::unequal(123.0)]];

        // [[codegen::description(desc)]]
        bool descValue;

        // inListValue1 documentation
        std::string inListValue1 [[codegen::inlist("A", "B", "C")]];

        // inListValue1Optional documentation
        std::optional<std::string> inListValue1Optional [[codegen::inlist("A", "B", "C")]];

        // inListValue2 documentation
        std::string inListValue2 [[codegen::inlist(List)]];

        // inListValue2Optional documentation
        std::optional<std::string> inListValue2Optional [[codegen::inlist(List)]];

        // unequalValueString documentation
        std::string unequalValueString [[codegen::unequal("abcdef")]];

        // unequalValueStringOptional documentation
        std::optional<std::string> unequalValueStringOptional [[codegen::unequal("abcdef")]];

        // referenceValue documentation
        std::optional<std::monostate> referenceValue [[codegen::reference("abc")]];
    };
)";
    Struct* s = parseRootStruct(Source);

    REQUIRE(s->children.empty());
    REQUIRE(s->variables.size() == 38);
    {
        Variable* var = s->variables[0];
        REQUIRE(var->name == "keyValue");
        REQUIRE(var->key == "KeyKey");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "keyValue documentation");
        REQUIRE(var->attributes.key == "KeyKey");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinlist.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var->name == "keyValueOptional");
        REQUIRE(var->key == "KeyKeyOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "keyValueOptional documentation");
        REQUIRE(var->attributes.key == "KeyKeyOptional");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinlist.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var->name == "inRangeValueInt");
        REQUIRE(var->key == "InRangeValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "inRangeValueInt documentation");
        REQUIRE(var->attributes.inrange == "-2, 2");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinlist.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[3];
        REQUIRE(var->name == "inRangeValueIntOptional");
        REQUIRE(var->key == "InRangeValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "inRangeValueIntOptional documentation");
        REQUIRE(var->attributes.inrange == "-2, 2");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var->name == "inRangeValueFloat");
        REQUIRE(var->key == "InRangeValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "inRangeValueFloat documentation");
        REQUIRE(var->attributes.inrange == "-0.5, 0.75");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[5];
        REQUIRE(var->name == "inRangeValueFloatOptional");
        REQUIRE(var->key == "InRangeValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "inRangeValueFloatOptional documentation");
        REQUIRE(var->attributes.inrange == "-0.5, 0.75");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[6];
        REQUIRE(var->name == "notInRangeValueInt");
        REQUIRE(var->key == "NotInRangeValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "notInRangeValueInt documentation");
        REQUIRE(var->attributes.notinrange == "5, 7");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[7];
        REQUIRE(var->name == "notInRangeValueIntOptional");
        REQUIRE(var->key == "NotInRangeValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "notInRangeValueIntOptional documentation");
        REQUIRE(var->attributes.notinrange == "5, 7");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[8];
        REQUIRE(var->name == "notInRangeValueFloat");
        REQUIRE(var->key == "NotInRangeValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "notInRangeValueFloat documentation");
        REQUIRE(var->attributes.notinrange == "-0.5, 0.5");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[9];
        REQUIRE(var->name == "notInRangeValueFloatOptional");
        REQUIRE(var->key == "NotInRangeValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "notInRangeValueFloatOptional documentation");
        REQUIRE(var->attributes.notinrange == "-0.5, 0.5");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var->name == "lessValueInt");
        REQUIRE(var->key == "LessValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "lessValueInt documentation");
        REQUIRE(var->attributes.less == "-5");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var->name == "lessValueIntOptional");
        REQUIRE(var->key == "LessValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "lessValueIntOptional documentation");
        REQUIRE(var->attributes.less == "-5");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var->name == "lessValueFloat");
        REQUIRE(var->key == "LessValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "lessValueFloat documentation");
        REQUIRE(var->attributes.less == "15.0");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var->name == "lessValueFloatOptional");
        REQUIRE(var->key == "LessValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "lessValueFloatOptional documentation");
        REQUIRE(var->attributes.less == "15.0");
        
        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var->name == "lessEqualValueInt");
        REQUIRE(var->key == "LessEqualValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "lessEqualValueInt documentation");
        REQUIRE(var->attributes.lessequal == "25");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var->name == "lessEqualValueIntOptional");
        REQUIRE(var->key == "LessEqualValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "lessEqualValueIntOptional documentation");
        REQUIRE(var->attributes.lessequal == "25");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var->name == "lessEqualValueFloat");
        REQUIRE(var->key == "LessEqualValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "lessEqualValueFloat documentation");
        REQUIRE(var->attributes.lessequal == "12.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var->name == "lessEqualValueFloatOptional");
        REQUIRE(var->key == "LessEqualValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "lessEqualValueFloatOptional documentation");
        REQUIRE(var->attributes.lessequal == "12.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var->name == "greaterValueInt");
        REQUIRE(var->key == "GreaterValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "greaterValueInt documentation");
        REQUIRE(var->attributes.greater == "45");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var->name == "greaterValueIntOptional");
        REQUIRE(var->key == "GreaterValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "greaterValueIntOptional documentation");
        REQUIRE(var->attributes.greater == "45");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var->name == "greaterValueFloat");
        REQUIRE(var->key == "GreaterValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "greaterValueFloat documentation");
        REQUIRE(var->attributes.greater == "-5.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[21];
        REQUIRE(var->name == "greaterValueFloatOptional");
        REQUIRE(var->key == "GreaterValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "greaterValueFloatOptional documentation");
        REQUIRE(var->attributes.greater == "-5.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[22];
        REQUIRE(var->name == "greaterEqualValueInt");
        REQUIRE(var->key == "GreaterEqualValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "greaterEqualValueInt documentation");
        REQUIRE(var->attributes.greaterequal == "2");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[23];
        REQUIRE(var->name == "greaterEqualValueIntOptional");
        REQUIRE(var->key == "GreaterEqualValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "greaterEqualValueIntOptional documentation");
        REQUIRE(var->attributes.greaterequal == "2");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[24];
        REQUIRE(var->name == "greaterEqualValueFloat");
        REQUIRE(var->key == "GreaterEqualValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "greaterEqualValueFloat documentation");
        REQUIRE(var->attributes.greaterequal == "-25.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[25];
        REQUIRE(var->name == "greaterEqualValueFloatOptional");
        REQUIRE(var->key == "GreaterEqualValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "greaterEqualValueFloatOptional documentation");
        REQUIRE(var->attributes.greaterequal == "-25.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[26];
        REQUIRE(var->name == "unequalValueInt");
        REQUIRE(var->key == "UnequalValueInt");
        REQUIRE(var->type == "int");
        REQUIRE(var->comment == "unequalValueInt documentation");
        REQUIRE(var->attributes.unequal == "1");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[27];
        REQUIRE(var->name == "unequalValueIntOptional");
        REQUIRE(var->key == "UnequalValueIntOptional");
        REQUIRE(var->type == "std::optional<int>");
        REQUIRE(var->comment == "unequalValueIntOptional documentation");
        REQUIRE(var->attributes.unequal == "1");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[28];
        REQUIRE(var->name == "unequalValueFloat");
        REQUIRE(var->key == "UnequalValueFloat");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "unequalValueFloat documentation");
        REQUIRE(var->attributes.unequal == "123.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[29];
        REQUIRE(var->name == "unequalValueFloatOptional");
        REQUIRE(var->key == "UnequalValueFloatOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "unequalValueFloatOptional documentation");
        REQUIRE(var->attributes.unequal == "123.0");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[30];
        REQUIRE(var->name == "descValue");
        REQUIRE(var->key == "DescValue");
        REQUIRE(var->type == "bool");
        REQUIRE(var->comment == "[[codegen::description(desc)]]");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[31];
        REQUIRE(var->name == "inListValue1");
        REQUIRE(var->key == "InListValue1");
        REQUIRE(var->type == "std::string");
        REQUIRE(var->comment == "inListValue1 documentation");
        REQUIRE(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[32];
        REQUIRE(var->name == "inListValue1Optional");
        REQUIRE(var->key == "InListValue1Optional");
        REQUIRE(var->type == "std::optional<std::string>");
        REQUIRE(var->comment == "inListValue1Optional documentation");
        REQUIRE(var->attributes.inlist == "\"A\", \"B\", \"C\"");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[33];
        REQUIRE(var->name == "inListValue2");
        REQUIRE(var->key == "InListValue2");
        REQUIRE(var->type == "std::string");
        REQUIRE(var->comment == "inListValue2 documentation");
        REQUIRE(var->attributes.inlist == "List");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[34];
        REQUIRE(var->name == "inListValue2Optional");
        REQUIRE(var->key == "InListValue2Optional");
        REQUIRE(var->type == "std::optional<std::string>");
        REQUIRE(var->comment == "inListValue2Optional documentation");
        REQUIRE(var->attributes.inlist == "List");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[35];
        REQUIRE(var->name == "unequalValueString");
        REQUIRE(var->key == "UnequalValueString");
        REQUIRE(var->type == "std::string");
        REQUIRE(var->comment == "unequalValueString documentation");
        REQUIRE(var->attributes.unequal == "\"abcdef\"");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[36];
        REQUIRE(var->name == "unequalValueStringOptional");
        REQUIRE(var->key == "UnequalValueStringOptional");
        REQUIRE(var->type == "std::optional<std::string>");
        REQUIRE(var->comment == "unequalValueStringOptional documentation");
        REQUIRE(var->attributes.unequal == "\"abcdef\"");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
    }

    {
        Variable* var = s->variables[37];
        REQUIRE(var->name == "referenceValue");
        REQUIRE(var->key == "ReferenceValue");
        REQUIRE(var->type == "std::optional<std::monostate>");
        REQUIRE(var->comment == "referenceValue documentation");
        REQUIRE(var->attributes.reference == "\"abc\"");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.inrange.empty());
        REQUIRE(var->attributes.key.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    std::string r = generateResult(s);
    REQUIRE(!r.empty());
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
        REQUIRE(var->name == "keyInRangeValue");
        REQUIRE(var->key == "KeyKey");
        REQUIRE(var->type == "float");
        REQUIRE(var->comment == "keyInRangeValue documentation");
        REQUIRE(var->attributes.key == "KeyKey");
        REQUIRE(var->attributes.inrange == "-2, 2");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var->name == "keyValueInRangeOptional");
        REQUIRE(var->key == "KeyKeyOptional");
        REQUIRE(var->type == "std::optional<float>");
        REQUIRE(var->comment == "keyInRangeValueOptional documentation");
        REQUIRE(var->attributes.key == "KeyKeyOptional");
        REQUIRE(var->attributes.inrange == "-2, 3");

        REQUIRE(var->attributes.annotation.empty());
        REQUIRE(var->attributes.greater.empty());
        REQUIRE(var->attributes.greaterequal.empty());
        REQUIRE(var->attributes.inlist.empty());
        REQUIRE(var->attributes.less.empty());
        REQUIRE(var->attributes.lessequal.empty());
        REQUIRE(var->attributes.notinrange.empty());
        REQUIRE(var->attributes.reference.empty());
        REQUIRE(var->attributes.unequal.empty());
    }
}

TEST_CASE("Parsing Attribute: Struct Attribute empty noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::namespace(Namespace), codegen::noexhaustive()]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s->attributes.dictionary == "Par");
    REQUIRE(s->attributes.namespaceName == "Namespace");
    REQUIRE(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]->name == "value");
    REQUIRE(s->variables[0]->key == "Value");
    REQUIRE(s->variables[0]->type == "int");
}

TEST_CASE("Parsing Attribute: Struct Attribute true noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::namespace(Namespace), codegen::noexhaustive(true)]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s->attributes.dictionary == "Par");
    REQUIRE(s->attributes.namespaceName == "Namespace");
    REQUIRE(s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]->name == "value");
    REQUIRE(s->variables[0]->key == "Value");
    REQUIRE(s->variables[0]->type == "int");
}

TEST_CASE("Parsing Attribute: Struct Attribute false noexhaustive", "[parsing]") {
    constexpr const char Source[] = R"(
struct [[codegen::Dictionary(Par), codegen::namespace(Namespace), codegen::noexhaustive(false)]] Parameters {
    int value;
};
)";

    Struct* s = parseRootStruct(Source);
    REQUIRE(s->attributes.dictionary == "Par");
    REQUIRE(s->attributes.namespaceName == "Namespace");
    REQUIRE(!s->attributes.noExhaustive);
    REQUIRE(s->variables.size() == 1);
    REQUIRE(s->variables[0]->name == "value");
    REQUIRE(s->variables[0]->key == "Value");
    REQUIRE(s->variables[0]->type == "int");
}
