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

        // string not empty value documentation
        std::string notEmptyString [[codegen::notempty()]];

        // string not empty optional value documentation
        std::optional<std::string> notEmptyStringOptional [[codegen::notempty()]];

        // string not empty vector value documentation
        std::vector<std::string> notEmptyStringVector [[codegen::notempty()]];

        // string not empty optional vector value documentation
        std::optional<std::vector<std::string>> notEmptyStringOptionalVector [[codegen::notempty()]];

        // string not not empty value documentation
        std::string notNotEmptyString [[codegen::notempty(false)]];

        // string not not empty optional value documentation
        std::optional<std::string> notNotEmptyStringOptional [[codegen::notempty(false)]];

        // string not not empty vector value documentation
        std::vector<std::string> notNotEmptyStringVector [[codegen::notempty(false)]];

        // string not not empty optional vector value documentation
        std::optional<std::vector<std::string>> notNotEmptyStringOptionalVector [[codegen::notempty(false)]];

        // string yes not empty value documentation
        std::string yesNotEmptyString [[codegen::notempty(true)]];

        // string yes not empty optional value documentation
        std::optional<std::string> yesNotEmptyStringOptional [[codegen::notempty(true)]];

        // string yes not empty vector value documentation
        std::vector<std::string> yesNotEmptyStringVector [[codegen::notempty(true)]];

        // string yes not empty optional vector value documentation
        std::optional<std::vector<std::string>> yesNotEmptyStringOptionalVector [[codegen::notempty(true)]];

        // referenceValue documentation
        ghoul::Dictionary referenceValue [[codegen::reference("abc")]];

        // referenceValueOptional documentation
        std::optional<ghoul::Dictionary> referenceValueOptional [[codegen::reference("abc")]];

        // referenceValueVector documentation
        std::vector<ghoul::Dictionary> referenceValueVector [[codegen::reference("abc")]];

        // referenceValueOptionalVector documentation
        std::optional<std::vector<ghoul::Dictionary>> referenceValueOptionalVector [[codegen::reference("abc")]];

        // dcolor3Value documentation
        glm::dvec3 dcolor3Value [[codegen::color()]];

        // optionalDcolor3Value documentation
        std::optional<glm::dvec3> optionalDcolor3Value [[codegen::color()]];

        // vectorDcolor3Value documentation
        std::vector<glm::dvec3> vectorDcolor3Value [[codegen::color()]];

        // optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> optionalVectorDcolor3Value [[codegen::color()]];

        // not dcolor3Value documentation
        glm::dvec3 notDcolor3Value [[codegen::color(false)]];

        // not optionalDcolor3Value documentation
        std::optional<glm::dvec3> notOptionalDcolor3Value [[codegen::color(false)]];

        // not vectorDcolor3Value documentation
        std::vector<glm::dvec3> notVectorDcolor3Value [[codegen::color(false)]];

        // not optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> notOptionalVectorDcolor3Value [[codegen::color(false)]];

        // yes dcolor3Value documentation
        glm::dvec3 yesDcolor3Value [[codegen::color(true)]];

        // yes optionalDcolor3Value documentation
        std::optional<glm::dvec3> yesOptionalDcolor3Value [[codegen::color(true)]];

        // yes vectorDcolor3Value documentation
        std::vector<glm::dvec3> yesVectorDcolor3Value [[codegen::color(true)]];

        // yes optionalVectorDcolor3Value documentation
        std::optional<std::vector<glm::dvec3>> yesOptionalVectorDcolor3Value [[codegen::color(true)]];

        // file value documentation
        std::filesystem::path fileValue;

        // optional file value documentation
        std::optional<std::filesystem::path> optionalFileValue;

        // vector file value documentation
        std::vector<std::filesystem::path> vectorFileValue;

        // optional vector file value documentation
        std::optional<std::vector<std::filesystem::path>> optionalVectorFileValue;

        // directory value documentation
        std::filesystem::path directoryValue [[codegen::directory()]];

        // optional directory value documentation
        std::optional<std::filesystem::path> optionalDirectoryValue [[codegen::directory()]];

        // vector directory value documentation
        std::vector<std::filesystem::path> vectorDirectoryValue [[codegen::directory()]];

        // optional vector directory value documentation
        std::optional<std::vector<std::filesystem::path>> optionalVectorDirectoryValue [[codegen::directory()]];

        // not directory value documentation
        std::filesystem::path notDirectoryValue [[codegen::directory(false)]];

        // not optional directory value documentation
        std::optional<std::filesystem::path> notOptionalDirectoryValue [[codegen::directory(false)]];

        // not vector directory value documentation
        std::vector<std::filesystem::path> notVectorDirectoryValue [[codegen::directory(false)]];

        // not optional vector directory value documentation
        std::optional<std::vector<std::filesystem::path>> notOptionalVectorDirectoryValue [[codegen::directory(false)]];

        // yes directory value documentation
        std::filesystem::path yesDirectoryValue [[codegen::directory(true)]];

        // yes optional directory value documentation
        std::optional<std::filesystem::path> yesOptionalDirectoryValue [[codegen::directory(true)]];

        // yes vector directory value documentation
        std::vector<std::filesystem::path> yesVectorDirectoryValue [[codegen::directory(true)]];

        // yes optional vector directory value documentation
        std::optional<std::vector<std::filesystem::path>> yesOptionalVectorDirectoryValue [[codegen::directory(true)]];
        
        // dateTime value documentation
        std::string dateTimeValue [[codegen::datetime()]];

        // optional dateTime value documentation
        std::optional<std::string> optionalDateTimeValue [[codegen::datetime()]];

        // vector dateTime value documentation
        std::vector<std::string> vectorDateTimeValue [[codegen::datetime()]];

        // optional vector dateTime value documentation
        std::optional<std::vector<std::string>> optionalVectorDateTimeValue [[codegen::datetime()]];
    
    };
)";
    Struct* s = parseRootStruct(Source);

    CHECK(s->children.empty());
    REQUIRE(s->variables.size() == 103);
    {
        Variable* var = s->variables[0];
        REQUIRE(var);
        CHECK(var->name == "keyValue");
        CHECK(var->key == "\"KeyKey\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[1];
        REQUIRE(var);
        CHECK(var->name == "keyValueOptional");
        CHECK(var->key == "\"KeyKeyOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[2];
        REQUIRE(var);
        CHECK(var->name == "keyValueVector");
        CHECK(var->key == "\"KeyKeyVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[3];
        CHECK(var->name == "inRangeValueInt");
        CHECK(var->key == "\"InRangeValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[4];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIntOptional");
        CHECK(var->key == "\"InRangeValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[5];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueIntVector");
        CHECK(var->key == "\"InRangeValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[6];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloat");
        CHECK(var->key == "\"InRangeValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[7];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloatOptional");
        CHECK(var->key == "\"InRangeValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[8];
        REQUIRE(var);
        CHECK(var->name == "inRangeValueFloatVector");
        CHECK(var->key == "\"InRangeValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[9];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueInt");
        CHECK(var->key == "\"NotInRangeValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[10];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIntOptional");
        CHECK(var->key == "\"NotInRangeValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[11];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueIntVector");
        CHECK(var->key == "\"NotInRangeValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[12];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloat");
        CHECK(var->key == "\"NotInRangeValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[13];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloatOptional");
        CHECK(var->key == "\"NotInRangeValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[14];
        REQUIRE(var);
        CHECK(var->name == "notInRangeValueFloatVector");
        CHECK(var->key == "\"NotInRangeValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[15];
        REQUIRE(var);
        CHECK(var->name == "lessValueInt");
        CHECK(var->key == "\"LessValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[16];
        REQUIRE(var);
        CHECK(var->name == "lessValueIntOptional");
        CHECK(var->key == "\"LessValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[17];
        REQUIRE(var);
        CHECK(var->name == "lessValueIntVector");
        CHECK(var->key == "\"LessValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[18];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloat");
        CHECK(var->key == "\"LessValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[19];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloatOptional");
        CHECK(var->key == "\"LessValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[20];
        REQUIRE(var);
        CHECK(var->name == "lessValueFloatVector");
        CHECK(var->key == "\"LessValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[21];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueInt");
        CHECK(var->key == "\"LessEqualValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[22];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIntOptional");
        CHECK(var->key == "\"LessEqualValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[23];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueIntVector");
        CHECK(var->key == "\"LessEqualValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[24];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloat");
        CHECK(var->key == "\"LessEqualValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[25];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloatOptional");
        CHECK(var->key == "\"LessEqualValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[26];
        REQUIRE(var);
        CHECK(var->name == "lessEqualValueFloatVector");
        CHECK(var->key == "\"LessEqualValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[27];
        REQUIRE(var);
        CHECK(var->name == "greaterValueInt");
        CHECK(var->key == "\"GreaterValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[28];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIntOptional");
        CHECK(var->key == "\"GreaterValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[29];
        REQUIRE(var);
        CHECK(var->name == "greaterValueIntVector");
        CHECK(var->key == "\"GreaterValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[30];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloat");
        CHECK(var->key == "\"GreaterValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[31];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloatOptional");
        CHECK(var->key == "\"GreaterValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[32];
        REQUIRE(var);
        CHECK(var->name == "greaterValueFloatVector");
        CHECK(var->key == "\"GreaterValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[33];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueInt");
        CHECK(var->key == "\"GreaterEqualValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[34];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIntOptional");
        CHECK(var->key == "\"GreaterEqualValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[35];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueIntVector");
        CHECK(var->key == "\"GreaterEqualValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[36];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloat");
        CHECK(var->key == "\"GreaterEqualValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[37];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloatOptional");
        CHECK(var->key == "\"GreaterEqualValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[38];
        REQUIRE(var);
        CHECK(var->name == "greaterEqualValueFloatVector");
        CHECK(var->key == "\"GreaterEqualValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[39];
        REQUIRE(var);
        CHECK(var->name == "unequalValueInt");
        CHECK(var->key == "\"UnequalValueInt\"");
        CHECK(generateTypename(var->type) == "int");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[40];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIntOptional");
        CHECK(var->key == "\"UnequalValueIntOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[41];
        REQUIRE(var);
        CHECK(var->name == "unequalValueIntVector");
        CHECK(var->key == "\"UnequalValueIntVector\"");
        CHECK(generateTypename(var->type) == "std::vector<int>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[42];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloat");
        CHECK(var->key == "\"UnequalValueFloat\"");
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[43];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloatOptional");
        CHECK(var->key == "\"UnequalValueFloatOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[44];
        REQUIRE(var);
        CHECK(var->name == "unequalValueFloatVector");
        CHECK(var->key == "\"UnequalValueFloatVector\"");
        CHECK(generateTypename(var->type) == "std::vector<float>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[45];
        REQUIRE(var);
        CHECK(var->name == "descValue");
        CHECK(var->key == "\"DescValue\"");
        CHECK(generateTypename(var->type) == "bool");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[46];
        REQUIRE(var);
        CHECK(var->name == "inListValue1");
        CHECK(var->key == "\"InListValue1\"");
        CHECK(generateTypename(var->type) == "std::string");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[47];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Optional");
        CHECK(var->key == "\"InListValue1Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[48];
        REQUIRE(var);
        CHECK(var->name == "inListValue1Vector");
        CHECK(var->key == "\"InListValue1Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[49];
        REQUIRE(var);
        CHECK(var->name == "inListValue2");
        CHECK(var->key == "\"InListValue2\"");
        CHECK(generateTypename(var->type) == "std::string");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[50];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Optional");
        CHECK(var->key == "\"InListValue2Optional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[51];
        REQUIRE(var);
        CHECK(var->name == "inListValue2Vector");
        CHECK(var->key == "\"InListValue2Vector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[52];
        REQUIRE(var);
        CHECK(var->name == "unequalValueString");
        CHECK(var->key == "\"UnequalValueString\"");
        CHECK(generateTypename(var->type) == "std::string");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[53];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringOptional");
        CHECK(var->key == "\"UnequalValueStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[54];
        REQUIRE(var);
        CHECK(var->name == "unequalValueStringVector");
        CHECK(var->key == "\"UnequalValueStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[55];
        REQUIRE(var);
        CHECK(var->name == "notEmptyString");
        CHECK(var->key == "\"NotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string not empty value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[56];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringOptional");
        CHECK(var->key == "\"NotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string not empty optional value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[57];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringVector");
        CHECK(var->key == "\"NotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string not empty vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }
    
    {
        Variable* var = s->variables[58];
        REQUIRE(var);
        CHECK(var->name == "notEmptyStringOptionalVector");
        CHECK(var->key == "\"NotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string not empty optional vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty == true);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[59];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyString");
        CHECK(var->key == "\"NotNotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string not not empty value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[60];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringOptional");
        CHECK(var->key == "\"NotNotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string not not empty optional value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[61];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringVector");
        CHECK(var->key == "\"NotNotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string not not empty vector value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[62];
        REQUIRE(var);
        CHECK(var->name == "notNotEmptyStringOptionalVector");
        CHECK(var->key == "\"NotNotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string not not empty optional vector value documentation");
        CHECK(!var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[63];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyString");
        CHECK(var->key == "\"YesNotEmptyString\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "string yes not empty value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
    }

    {
        Variable* var = s->variables[64];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringOptional");
        CHECK(var->key == "\"YesNotEmptyStringOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "string yes not empty optional value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[65];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringVector");
        CHECK(var->key == "\"YesNotEmptyStringVector\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "string yes not empty vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[66];
        REQUIRE(var);
        CHECK(var->name == "yesNotEmptyStringOptionalVector");
        CHECK(var->key == "\"YesNotEmptyStringOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "string yes not empty optional vector value documentation");
        CHECK(var->attributes.mustBeNotEmpty);

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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.isDirectory);
    }

    {
        Variable* var = s->variables[67];
        REQUIRE(var);
        CHECK(var->name == "referenceValue");
        CHECK(var->key == "\"ReferenceValue\"");
        CHECK(generateTypename(var->type) == "ghoul::Dictionary");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[68];
        REQUIRE(var);
        CHECK(var->name == "referenceValueOptional");
        CHECK(var->key == "\"ReferenceValueOptional\"");
        CHECK(generateTypename(var->type) == "std::optional<ghoul::Dictionary>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[69];
        REQUIRE(var);
        CHECK(var->name == "referenceValueVector");
        CHECK(var->key == "\"ReferenceValueVector\"");
        CHECK(generateTypename(var->type) == "std::vector<ghoul::Dictionary>");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[70];
        REQUIRE(var);
        CHECK(var->name == "referenceValueOptionalVector");
        CHECK(var->key == "\"ReferenceValueOptionalVector\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<ghoul::Dictionary>>");
        CHECK(var->comment == "referenceValueOptionalVector documentation");
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
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[71];
        REQUIRE(var);
        CHECK(var->name == "dcolor3Value");
        CHECK(var->key == "\"Dcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "dcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[72];
        REQUIRE(var);
        CHECK(var->name == "optionalDcolor3Value");
        CHECK(var->key == "\"OptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "optionalDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[73];
        REQUIRE(var);
        CHECK(var->name == "vectorDcolor3Value");
        CHECK(var->key == "\"VectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "vectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[74];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorDcolor3Value");
        CHECK(var->key == "\"OptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "optionalVectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[75];
        REQUIRE(var);
        CHECK(var->name == "notDcolor3Value");
        CHECK(var->key == "\"NotDcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "not dcolor3Value documentation");
        CHECK(!var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[76];
        REQUIRE(var);
        CHECK(var->name == "notOptionalDcolor3Value");
        CHECK(var->key == "\"NotOptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "not optionalDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[77];
        REQUIRE(var);
        CHECK(var->name == "notVectorDcolor3Value");
        CHECK(var->key == "\"NotVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "not vectorDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[78];
        REQUIRE(var);
        CHECK(var->name == "notOptionalVectorDcolor3Value");
        CHECK(var->key == "\"NotOptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "not optionalVectorDcolor3Value documentation");
        CHECK(!var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }


    {
        Variable* var = s->variables[79];
        REQUIRE(var);
        CHECK(var->name == "yesDcolor3Value");
        CHECK(var->key == "\"YesDcolor3Value\"");
        CHECK(generateTypename(var->type) == "glm::dvec3");
        CHECK(var->comment == "yes dcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[80];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalDcolor3Value");
        CHECK(var->key == "\"YesOptionalDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<glm::dvec3>");
        CHECK(var->comment == "yes optionalDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[81];
        REQUIRE(var);
        CHECK(var->name == "yesVectorDcolor3Value");
        CHECK(var->key == "\"YesVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::vector<glm::dvec3>");
        CHECK(var->comment == "yes vectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[82];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalVectorDcolor3Value");
        CHECK(var->key == "\"YesOptionalVectorDcolor3Value\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<glm::dvec3>>");
        CHECK(var->comment == "yes optionalVectorDcolor3Value documentation");
        CHECK(var->attributes.isColor);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[83];
        REQUIRE(var);
        CHECK(var->name == "fileValue");
        CHECK(var->key == "\"FileValue\"");
        CHECK(generateTypename(var->type) == "std::filesystem::path");
        CHECK(var->comment == "file value documentation");

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[84];
        REQUIRE(var);
        CHECK(var->name == "optionalFileValue");
        CHECK(var->key == "\"OptionalFileValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::filesystem::path>");
        CHECK(var->comment == "optional file value documentation");

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[85];
        REQUIRE(var);
        CHECK(var->name == "vectorFileValue");
        CHECK(var->key == "\"VectorFileValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::filesystem::path>");
        CHECK(var->comment == "vector file value documentation");

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[86];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorFileValue");
        CHECK(var->key == "\"OptionalVectorFileValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::filesystem::path>>");
        CHECK(var->comment == "optional vector file value documentation");

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[87];
        REQUIRE(var);
        CHECK(var->name == "directoryValue");
        CHECK(var->key == "\"DirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::filesystem::path");
        CHECK(var->comment == "directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[88];
        REQUIRE(var);
        CHECK(var->name == "optionalDirectoryValue");
        CHECK(var->key == "\"OptionalDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::filesystem::path>");
        CHECK(var->comment == "optional directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[89];
        REQUIRE(var);
        CHECK(var->name == "vectorDirectoryValue");
        CHECK(var->key == "\"VectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::filesystem::path>");
        CHECK(var->comment == "vector directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[90];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorDirectoryValue");
        CHECK(var->key == "\"OptionalVectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::filesystem::path>>");
        CHECK(var->comment == "optional vector directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[91];
        REQUIRE(var);
        CHECK(var->name == "notDirectoryValue");
        CHECK(var->key == "\"NotDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::filesystem::path");
        CHECK(var->comment == "not directory value documentation");
        CHECK(!var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[92];
        REQUIRE(var);
        CHECK(var->name == "notOptionalDirectoryValue");
        CHECK(var->key == "\"NotOptionalDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::filesystem::path>");
        CHECK(var->comment == "not optional directory value documentation");
        CHECK(!var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[93];
        REQUIRE(var);
        CHECK(var->name == "notVectorDirectoryValue");
        CHECK(var->key == "\"NotVectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::filesystem::path>");
        CHECK(var->comment == "not vector directory value documentation");
        CHECK(!var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[94];
        REQUIRE(var);
        CHECK(var->name == "notOptionalVectorDirectoryValue");
        CHECK(var->key == "\"NotOptionalVectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::filesystem::path>>");
        CHECK(var->comment == "not optional vector directory value documentation");
        CHECK(!var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[95];
        REQUIRE(var);
        CHECK(var->name == "yesDirectoryValue");
        CHECK(var->key == "\"YesDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::filesystem::path");
        CHECK(var->comment == "yes directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[96];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalDirectoryValue");
        CHECK(var->key == "\"YesOptionalDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::filesystem::path>");
        CHECK(var->comment == "yes optional directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[97];
        REQUIRE(var);
        CHECK(var->name == "yesVectorDirectoryValue");
        CHECK(var->key == "\"YesVectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::filesystem::path>");
        CHECK(var->comment == "yes vector directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[98];
        REQUIRE(var);
        CHECK(var->name == "yesOptionalVectorDirectoryValue");
        CHECK(var->key == "\"YesOptionalVectorDirectoryValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::filesystem::path>>");
        CHECK(var->comment == "yes optional vector directory value documentation");
        CHECK(var->attributes.isDirectory);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDateTime);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[99];
        REQUIRE(var);
        CHECK(var->name == "dateTimeValue");
        CHECK(var->key == "\"DateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::string");
        CHECK(var->comment == "dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[100];
        REQUIRE(var);
        CHECK(var->name == "optionalDateTimeValue");
        CHECK(var->key == "\"OptionalDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::string>");
        CHECK(var->comment == "optional dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[101];
        REQUIRE(var);
        CHECK(var->name == "vectorDateTimeValue");
        CHECK(var->key == "\"VectorDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::vector<std::string>");
        CHECK(var->comment == "vector dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
    }

    {
        Variable* var = s->variables[102];
        REQUIRE(var);
        CHECK(var->name == "optionalVectorDateTimeValue");
        CHECK(var->key == "\"OptionalVectorDateTimeValue\"");
        CHECK(generateTypename(var->type) == "std::optional<std::vector<std::string>>");
        CHECK(var->comment == "optional vector dateTime value documentation");
        CHECK(var->attributes.isDateTime);

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
        CHECK(var->attributes.reference.empty());
        CHECK(!var->attributes.isColor);
        CHECK(!var->attributes.isDirectory);
        CHECK(!var->attributes.mustBeNotEmpty);
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
        CHECK(generateTypename(var->type) == "float");
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
        CHECK(generateTypename(var->type) == "std::optional<float>");
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
    CHECK(generateTypename(s->variables[0]->type) == "int");
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
    CHECK(generateTypename(s->variables[0]->type) == "int");
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
    CHECK(generateTypename(s->variables[0]->type) == "int");
}
