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
#include <openspace/documentation/documentationengine.h>
#include <openspace/documentation/verifier.h>
#include <ghoul/misc/dictionary.h>
#include <optional>
#include <variant>
#include <vector>

namespace {
    std::string description = "Description";

    std::vector<std::string> List = { "F", "G", "H", "I", "J" };

    struct [[codegen::Dictionary(Attributes)]] Parameters {
        // keyValue documentation
        float keyValue [[codegen::key("KeyKey")]];

        // keyValueOptional documentation
        std::optional<float> keyValueOptional [[codegen::key("KeyKeyOptional")]];

        // keyValueVector documentation
        std::vector<float> keyValueVector [[codegen::key("KeyKeyVector")]];

        // inRangeValueInt documentation
        int inRangeValueInt [[codegen::inrange(-2, 8)]];

        // inRangeValueIntOptional documentation
        std::optional<int> inRangeValueIntOptional [[codegen::inrange(-2, 8)]];

        // inRangeValueIntVector documentation
        std::vector<int> inRangeValueIntVector [[codegen::inrange(-2, 8)]];

        // inRangeValueFloat documentation
        float inRangeValueFloat [[codegen::inrange(8.0, 9.0)]];

        // inRangeValueFloatOptional documentation
        std::optional<float> inRangeValueFloatOptional [[codegen::inrange(8.0, 9.0)]];

        // inRangeValueFloatVector documentation
        std::vector<float> inRangeValueFloatVector [[codegen::inrange(8.0, 9.0)]];

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
        int lessValueInt [[codegen::less(20)]];
        
        // lessValueIntOptional documentation
        std::optional<int> lessValueIntOptional [[codegen::less(20)]];

        // lessValueIntVector documentation
        std::vector<int> lessValueIntVector [[codegen::less(20)]];

        // lessValueFloat documentation
        float lessValueFloat [[codegen::less(21.0)]];

        // lessValueFloatOptional documentation
        std::optional<float> lessValueFloatOptional [[codegen::less(22.0)]];

        // lessValueFloatVector documentation
        std::vector<float> lessValueFloatVector [[codegen::less(23.0)]];

        // lessEqualValueInt documentation
        int lessEqualValueInt [[codegen::lessequal(25)]];

        // lessEqualValueIntOptional documentation
        std::optional<int> lessEqualValueIntOptional [[codegen::lessequal(25)]];

        // lessEqualValueIntVector documentation
        std::vector<int> lessEqualValueIntVector [[codegen::lessequal(25)]];

        // lessEqualValueFloat documentation
        float lessEqualValueFloat [[codegen::lessequal(27.0)]];

        // lessEqualValueFloatOptional documentation
        std::optional<float> lessEqualValueFloatOptional [[codegen::lessequal(27.0)]];

        // lessEqualValueFloatVector documentation
        std::vector<float> lessEqualValueFloatVector [[codegen::lessequal(27.0)]];

        // greaterValueInt documentation
        int greaterValueInt [[codegen::greater(25)]];

        // greaterValueIntOptional documentation
        std::optional<int> greaterValueIntOptional [[codegen::greater(25)]];

        // greaterValueIntVector documentation
        std::vector<int> greaterValueIntVector [[codegen::greater(25)]];

        // greaterValueFloat documentation
        float greaterValueFloat [[codegen::greater(-5.0)]];

        // greaterValueFloatOptional documentation
        std::optional<float> greaterValueFloatOptional [[codegen::greater(-5.0)]];

        // greaterValueFloatVector documentation
        std::vector<float> greaterValueFloatVector [[codegen::greater(-5.0)]];

        // greaterEqualValueInt documentation
        int greaterEqualValueInt [[codegen::greaterequal(33)]];

        // greaterEqualValueIntOptional documentation
        std::optional<int> greaterEqualValueIntOptional [[codegen::greaterequal(33)]];

        // greaterEqualValueIntVector documentation
        std::vector<int> greaterEqualValueIntVector [[codegen::greaterequal(33)]];

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
        std::string inListValue1 [[codegen::inlist("A", "B", "C", "D", "E")]];

        // inListValue1Optional documentation
        std::optional<std::string> inListValue1Optional [[codegen::inlist("A", "B", "C", "D", "E")]];

        // inListValue1Vector documentation
        std::vector<std::string> inListValue1Vector [[codegen::inlist("A", "B", "C", "D", "E")]];

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

        // referenceValueOptional documentation
        std::optional<ghoul::Dictionary> referenceValueOptional [[codegen::reference("abc")]];

        // referenceValueVector documentation
        std::optional<std::vector<ghoul::Dictionary>> referenceValueVector [[codegen::reference("abc")]];

        // dictValue documentation
        ghoul::Dictionary dictValue [[codegen::reference("abc")]];

        // dictValueVector documentation
        std::vector<ghoul::Dictionary> dictValueVector [[codegen::reference("abc")]];

        // dictValueOptional documentation
        std::optional<ghoul::Dictionary> dictValueOptional [[codegen::reference("abc")]];

        // dictValueMap documentation
        std::map<std::string, ghoul::Dictionary> dictValueMap [[codegen::reference("abc")]];

        // vectorDictValueMap documentation
        std::vector<std::map<std::string, ghoul::Dictionary>> vectorDictValueMap [[codegen::reference("abc")]];

        // optionalDictValueMap documentation
        std::optional<std::map<std::string, ghoul::Dictionary>> optionalDictValueMap [[codegen::reference("abc")]];

        // optionalVectorDictValueMap documentation
        std::optional<std::vector<std::map<std::string, ghoul::Dictionary>>> optionalVectorDictValueMap [[codegen::reference("abc")]];

        // annotation documentation
        std::string annotation [[codegen::annotation("abc")]];

        // annotationOptional documentation
        std::optional<std::string> annotationOptional [[codegen::annotation("def")]];

        // annotationVector documentation
        std::vector<std::string> annotationVector [[codegen::annotation("ghi")]];

        // dcolor3Value documentation
        glm::dvec3 dcolor3Value [[codegen::color()]];

        // optionalDcolor3Value documentation
        std::optional<glm::dvec3> optionalDcolor3Value [[codegen::color()]];

        // vectorDcolor3Value documentation
        std::vector<glm::dvec3> vectorDcolor3Value [[codegen::color()]];

        // color3Value documentation
        glm::vec3 color3Value [[codegen::color()]];

        // optionalColor3Value documentation
        std::optional<glm::vec3> optionalColor3Value [[codegen::color()]];

        // vectorColor3Value documentation
        std::vector<glm::vec3> vectorColor3Value [[codegen::color()]];

        // dcolor4Value documentation
        glm::dvec4 dcolor4Value [[codegen::color()]];

        // optionalDcolor4Value documentation
        std::optional<glm::dvec4> optionalDcolor4Value [[codegen::color()]];

        // vectorDcolor4Value documentation
        std::vector<glm::dvec4> vectorDcolor4Value [[codegen::color()]];

        // color4Value documentation
        glm::vec4 color4Value [[codegen::color()]];

        // optionalColor4Value documentation
        std::optional<glm::vec4> optionalColor4Value [[codegen::color()]];

        // vectorColor4Value documentation
        std::vector<glm::vec4> vectorColor4Value [[codegen::color()]];

        // dateTime value documentation
        std::string dateTimeValue [[codegen::datetime()]];

        // optional dateTime value documentation
        std::optional<std::string> optionalDateTimeValue [[codegen::datetime()]];

        // vector dateTime value documentation
        std::vector<std::string> vectorDateTimeValue [[codegen::datetime()]];

        // optional vector dateTime value documentation
        std::optional<std::vector<std::string>> optionalVectorDateTimeValue [[codegen::datetime()]];
    };
#include "execution_structs_attributes_codegen.cpp"
} // namespace

TEST_CASE("Attributes Bake", "[structs][execution]") {
    openspace::documentation::Documentation doc;
    doc.id = "abc";
    DocEng.addDocumentation(doc);

    ghoul::Dictionary d;
    d.setValue("KeyKey", 2.1);
    d.setValue("KeyKeyOptional", 2.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 2.3);
        e.setValue("2", 2.4);
        e.setValue("3", 2.5);
        d.setValue("KeyKeyVector", e);
    }
    d.setValue("InRangeValueInt", 3.0);
    d.setValue("InRangeValueIntOptional", 4.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 5.0);
        e.setValue("2", 6.0);
        e.setValue("3", 7.0);
        d.setValue("InRangeValueIntVector", e);
    }
    d.setValue("InRangeValueFloat", 8.1);
    d.setValue("InRangeValueFloatOptional", 8.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 8.3);
        e.setValue("2", 8.4);
        e.setValue("3", 8.5);
        d.setValue("InRangeValueFloatVector", e);
    }
    d.setValue("NotInRangeValueInt", 9.0);
    d.setValue("NotInRangeValueIntOptional", 10.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 11.0);
        e.setValue("2", 12.0);
        e.setValue("3", 13.0);
        d.setValue("NotInRangeValueIntVector", e);
    }
    d.setValue("NotInRangeValueFloat", 14.1);
    d.setValue("NotInRangeValueFloatOptional", 14.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 14.3);
        e.setValue("2", 14.4);
        e.setValue("3", 14.5);
        d.setValue("NotInRangeValueFloatVector", e);
    }
    d.setValue("LessValueInt", 15.0);
    d.setValue("LessValueIntOptional", 16.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 17.0);
        e.setValue("2", 18.0);
        e.setValue("3", 19.0);
        d.setValue("LessValueIntVector", e);
    }
    d.setValue("LessValueFloat", 20.1);
    d.setValue("LessValueFloatOptional", 20.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 20.3);
        e.setValue("2", 20.4);
        e.setValue("3", 20.5);
        d.setValue("LessValueFloatVector", e);
    }
    d.setValue("LessEqualValueInt", 21.0);
    d.setValue("LessEqualValueIntOptional", 22.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 23.0);
        e.setValue("2", 24.0);
        e.setValue("3", 25.0);
        d.setValue("LessEqualValueIntVector", e);
    }
    d.setValue("LessEqualValueFloat", 26.1);
    d.setValue("LessEqualValueFloatOptional", 26.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 26.3);
        e.setValue("2", 26.4);
        e.setValue("3", 26.5);
        d.setValue("LessEqualValueFloatVector", e);
    }
    d.setValue("GreaterValueInt", 27.0);
    d.setValue("GreaterValueIntOptional", 28.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 29.0);
        e.setValue("2", 30.0);
        e.setValue("3", 31.0);
        d.setValue("GreaterValueIntVector", e);
    }
    d.setValue("GreaterValueFloat", 32.1);
    d.setValue("GreaterValueFloatOptional", 32.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 32.3);
        e.setValue("2", 32.4);
        e.setValue("3", 32.5);
        d.setValue("GreaterValueFloatVector", e);
    }
    d.setValue("GreaterEqualValueInt", 33.0);
    d.setValue("GreaterEqualValueIntOptional", 34.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 35.0);
        e.setValue("2", 36.0);
        e.setValue("3", 37.0);
        d.setValue("GreaterEqualValueIntVector", e);
    }
    d.setValue("GreaterEqualValueFloat", 38.1);
    d.setValue("GreaterEqualValueFloatOptional", 38.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 38.3);
        e.setValue("2", 38.4);
        e.setValue("3", 38.5);
        d.setValue("GreaterEqualValueFloatVector", e);
    }
    d.setValue("UnequalValueInt", 39.0);
    d.setValue("UnequalValueIntOptional", 40.0);
    {
        ghoul::Dictionary e;
        e.setValue("1", 41.0);
        e.setValue("2", 42.0);
        e.setValue("3", 43.0);
        d.setValue("UnequalValueIntVector", e);
    }
    d.setValue("UnequalValueFloat", 44.1);
    d.setValue("UnequalValueFloatOptional", 44.2);
    {
        ghoul::Dictionary e;
        e.setValue("1", 44.3);
        e.setValue("2", 44.4);
        e.setValue("3", 44.5);
        d.setValue("UnequalValueFloatVector", e);
    }
    d.setValue("DescValue", true);
    d.setValue("InListValue1", std::string("A"));
    d.setValue("InListValue1Optional", std::string("B"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("C"));
        e.setValue("2", std::string("D"));
        e.setValue("3", std::string("E"));
        d.setValue("InListValue1Vector", e);
    }
    d.setValue("InListValue2", std::string("F"));
    d.setValue("InListValue2Optional", std::string("G"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("H"));
        e.setValue("2", std::string("I"));
        e.setValue("3", std::string("J"));
        d.setValue("InListValue2Vector", e);
    }
    d.setValue("UnequalValueString", std::string("zyxwv"));
    d.setValue("UnequalValueStringOptional", std::string("zyxwv"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("zyxwv1"));
        e.setValue("2", std::string("zyxwv2"));
        e.setValue("3", std::string("zyxwv3"));
        d.setValue("UnequalValueStringVector", e);
    }
    d.setValue("NotEmptyString", std::string("def"));
    d.setValue("NotEmptyStringOptional", std::string("def"));
    {
        ghoul::Dictionary v;
        v.setValue("1", std::string("jkl"));
        v.setValue("2", std::string("mno"));
        v.setValue("3", std::string("pqr"));
        d.setValue("NotEmptyStringVector", v);
    }
    {
        ghoul::Dictionary v;
        v.setValue("1", std::string("jkl"));
        v.setValue("2", std::string("mno"));
        v.setValue("3", std::string("pqr"));
        d.setValue("NotEmptyStringOptionalVector", v);
    }
    d.setValue("DictValue", ghoul::Dictionary());
    {
        ghoul::Dictionary e;
        e.setValue("1", ghoul::Dictionary());
        e.setValue("2", ghoul::Dictionary());
        e.setValue("3", ghoul::Dictionary());
        d.setValue("DictValueVector", e);
    }
    d.setValue("DictValueOptional", ghoul::Dictionary());
    {
        ghoul::Dictionary e;
        e.setValue("a", ghoul::Dictionary());
        e.setValue("b", ghoul::Dictionary());
        e.setValue("c", ghoul::Dictionary());
        d.setValue("DictValueMap", e);
    }
    {
        ghoul::Dictionary e;
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("1", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("2", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("3", f);
        }
        d.setValue("VectorDictValueMap", e);
    }
    {
        ghoul::Dictionary e;
        e.setValue("a", ghoul::Dictionary());
        e.setValue("b", ghoul::Dictionary());
        e.setValue("c", ghoul::Dictionary());
        d.setValue("OptionalDictValueMap", e);
    }
    {
        ghoul::Dictionary e;
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("1", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("2", f);
        }
        {
            ghoul::Dictionary f;
            f.setValue("a", ghoul::Dictionary());
            f.setValue("b", ghoul::Dictionary());
            f.setValue("c", ghoul::Dictionary());
            e.setValue("3", f);
        }
        d.setValue("OptionalVectorDictValueMap", e);
    }

    d.setValue("Annotation", std::string("annotation_abc"));
    d.setValue("AnnotationOptional", std::string("annotation_def"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("annotation_ghi"));
        e.setValue("2", std::string("annotation_jkl"));
        e.setValue("3", std::string("annotation_mno"));
        d.setValue("AnnotationVector", e);
    }
    d.setValue("Dcolor3Value", glm::dvec3(0.0, 0.1, 0.2));
    d.setValue("OptionalDcolor3Value", glm::dvec3(0.3, 0.4, 0.5));
    {
        ghoul::Dictionary e;
        e.setValue("1", glm::dvec3(0.60, 0.61, 0.62));
        e.setValue("2", glm::dvec3(0.63, 0.64, 0.65));
        e.setValue("3", glm::dvec3(0.66, 0.67, 0.68));
        d.setValue("VectorDcolor3Value", e);
    }
    d.setValue("Color3Value", glm::dvec3(0.70, 0.71, 0.72));
    d.setValue("OptionalColor3Value", glm::dvec3(0.73, 0.74, 0.75));
    {
        ghoul::Dictionary e;
        e.setValue("1", glm::dvec3(0.80, 0.81, 0.82));
        e.setValue("2", glm::dvec3(0.83, 0.84, 0.85));
        e.setValue("3", glm::dvec3(0.86, 0.87, 0.88));
        d.setValue("VectorColor3Value", e);
    }
    d.setValue("Dcolor4Value", glm::dvec4(0.0, 0.1, 0.2, 0.3));
    d.setValue("OptionalDcolor4Value", glm::dvec4(0.4, 0.5, 0.6, 0.7));
    {
        ghoul::Dictionary e;
        e.setValue("1", glm::dvec4(0.60, 0.61, 0.62, 0.63));
        e.setValue("2", glm::dvec4(0.64, 0.65, 0.66, 0.67));
        e.setValue("3", glm::dvec4(0.68, 0.69, 0.70, 0.71));
        d.setValue("VectorDcolor4Value", e);
    }
    d.setValue("Color4Value", glm::dvec4(0.80, 0.81, 0.82, 0.83));
    d.setValue("OptionalColor4Value", glm::dvec4(0.84, 0.85, 0.86, 0.87));
    {
        ghoul::Dictionary e;
        e.setValue("1", glm::dvec4(0.90, 0.91, 0.92, 0.93));
        e.setValue("2", glm::dvec4(0.94, 0.95, 0.96, 0.97));
        e.setValue("3", glm::dvec4(0.98, 0.99, 0.991, 0.992));
        d.setValue("VectorColor4Value", e);
    }

    d.setValue("DateTimeValue", std::string("1990 03 11 12:40:53"));
    d.setValue("OptionalDateTimeValue", std::string("1991 03 11 12:40:53"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("1992 03 11 12:40:53"));
        e.setValue("2", std::string("1993 03 11 12:40:53"));
        e.setValue("3", std::string("1994 03 11 12:40:53"));
        d.setValue("VectorDateTimeValue", e);
    }
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("1995 03 11 12:40:53"));
        e.setValue("2", std::string("1996 03 11 12:40:53"));
        e.setValue("3", std::string("1997 03 11 12:40:53"));
        d.setValue("OptionalVectorDateTimeValue", e);
    }

    const Parameters p = codegen::bake<Parameters>(d);

    CHECK(p.keyValue == 2.1f);
    REQUIRE(p.keyValueOptional.has_value());
    CHECK(p.keyValueOptional == 2.2f);
    CHECK(p.keyValueVector == std::vector{ 2.3f, 2.4f, 2.5f });

    CHECK(p.inRangeValueInt == 3);
    REQUIRE(p.inRangeValueIntOptional.has_value());
    CHECK(p.inRangeValueIntOptional == 4);
    CHECK(p.inRangeValueIntVector == std::vector{ 5, 6, 7 });

    CHECK(p.inRangeValueFloat == 8.1f);
    REQUIRE(p.inRangeValueFloatOptional.has_value());
    CHECK(p.inRangeValueFloatOptional == 8.2f);
    CHECK(p.inRangeValueFloatVector == std::vector{ 8.3f, 8.4f, 8.5f });

    CHECK(p.notInRangeValueInt == 9);
    REQUIRE(p.notInRangeValueIntOptional.has_value());
    CHECK(p.notInRangeValueIntOptional == 10);
    CHECK(p.notInRangeValueIntVector == std::vector{ 11, 12, 13 });

    CHECK(p.notInRangeValueFloat == 14.1f);
    REQUIRE(p.notInRangeValueFloatOptional.has_value());
    CHECK(p.notInRangeValueFloatOptional == 14.2f);
    CHECK(p.notInRangeValueFloatVector == std::vector{ 14.3f, 14.4f, 14.5f });

    CHECK(p.lessValueInt == 15);
    REQUIRE(p.lessValueIntOptional.has_value());
    CHECK(p.lessValueIntOptional == 16);
    CHECK(p.lessValueIntVector == std::vector{ 17, 18, 19 });

    CHECK(p.lessValueFloat == 20.1f);
    REQUIRE(p.lessValueFloatOptional.has_value());
    CHECK(p.lessValueFloatOptional == 20.2f);
    CHECK(p.lessValueFloatVector == std::vector{ 20.3f, 20.4f, 20.5f });

    CHECK(p.lessEqualValueInt == 21);
    REQUIRE(p.lessEqualValueIntOptional.has_value());
    CHECK(p.lessEqualValueIntOptional == 22);
    CHECK(p.lessEqualValueIntVector == std::vector{ 23, 24, 25 });

    CHECK(p.lessEqualValueFloat == 26.1f);
    REQUIRE(p.lessEqualValueFloatOptional.has_value());
    CHECK(p.lessEqualValueFloatOptional == 26.2f);
    CHECK(p.lessEqualValueFloatVector == std::vector{ 26.3f, 26.4f, 26.5f });

    CHECK(p.greaterValueInt == 27);
    REQUIRE(p.greaterValueIntOptional.has_value());
    CHECK(p.greaterValueIntOptional == 28);
    CHECK(p.greaterValueIntVector == std::vector{ 29, 30, 31 });

    CHECK(p.greaterValueFloat == 32.1f);
    REQUIRE(p.greaterValueFloatOptional.has_value());
    CHECK(p.greaterValueFloatOptional == 32.2f);
    CHECK(p.greaterValueFloatVector == std::vector{ 32.3f, 32.4f, 32.5f });

    CHECK(p.greaterEqualValueInt == 33);
    REQUIRE(p.greaterEqualValueIntOptional.has_value());
    CHECK(p.greaterEqualValueIntOptional == 34);
    CHECK(p.greaterEqualValueIntVector == std::vector{ 35, 36, 37 });

    CHECK(p.greaterEqualValueFloat == 38.1f);
    REQUIRE(p.greaterEqualValueFloatOptional.has_value());
    CHECK(p.greaterEqualValueFloatOptional == 38.2f);
    CHECK(p.greaterEqualValueFloatVector == std::vector{ 38.3f, 38.4f, 38.5f });

    CHECK(p.unequalValueInt == 39);
    REQUIRE(p.unequalValueIntOptional.has_value());
    CHECK(p.unequalValueIntOptional == 40);
    CHECK(p.unequalValueIntVector == std::vector{ 41, 42, 43 });

    CHECK(p.unequalValueFloat == 44.1f);
    REQUIRE(p.unequalValueFloatOptional.has_value());
    CHECK(p.unequalValueFloatOptional == 44.2f);
    CHECK(p.unequalValueFloatVector == std::vector{ 44.3f, 44.4f, 44.5f });

    CHECK(p.descValue == true);

    CHECK(p.inListValue1 == "A");
    REQUIRE(p.inListValue1Optional.has_value());
    CHECK(p.inListValue1Optional == "B");
    CHECK(p.inListValue1Vector == std::vector<std::string>{ "C", "D", "E" });

    CHECK(p.inListValue2 == "F");
    REQUIRE(p.inListValue2Optional.has_value());
    CHECK(p.inListValue2Optional == "G");
    CHECK(p.inListValue2Vector == std::vector<std::string>{ "H", "I", "J" });

    CHECK(p.unequalValueString == "zyxwv");
    REQUIRE(p.unequalValueStringOptional.has_value());
    CHECK(p.unequalValueStringOptional == "zyxwv");
    CHECK(
        p.unequalValueStringVector ==
        std::vector<std::string>{ "zyxwv1", "zyxwv2", "zyxwv3"}
    );
    CHECK(p.notEmptyStringVector.size() == 3);
    CHECK(p.notEmptyStringVector == std::vector<std::string>{ "jkl", "mno", "pqr" });
    REQUIRE(p.notEmptyStringOptionalVector.has_value());
    CHECK(p.notEmptyStringOptionalVector->size() == 3);
    CHECK(p.notEmptyStringOptionalVector == std::vector<std::string>{ "jkl", "mno", "pqr" });

    CHECK(p.notEmptyString == "def");
    REQUIRE(p.notEmptyStringOptional.has_value());
    CHECK(p.notEmptyStringOptional == "def");


    CHECK(p.annotation == "annotation_abc");
    CHECK(p.annotationOptional == "annotation_def");
    CHECK(p.annotationVector.size() == 3);
    CHECK(
        p.annotationVector ==
        std::vector<std::string>{ "annotation_ghi", "annotation_jkl", "annotation_mno" }
    );

    CHECK(p.dcolor3Value == glm::dvec3(0.0, 0.1, 0.2));
    REQUIRE(p.optionalDcolor3Value.has_value());
    CHECK(*p.optionalDcolor3Value == glm::dvec3(0.3, 0.4, 0.5));
    REQUIRE(p.vectorDcolor3Value.size() == 3);
    CHECK(p.vectorDcolor3Value[0] == glm::dvec3(0.60, 0.61, 0.62));
    CHECK(p.vectorDcolor3Value[1] == glm::dvec3(0.63, 0.64, 0.65));
    CHECK(p.vectorDcolor3Value[2] == glm::dvec3(0.66, 0.67, 0.68));

    CHECK(p.color3Value == glm::vec3(0.70f, 0.71f, 0.72f));
    REQUIRE(p.optionalColor3Value.has_value());
    CHECK(*p.optionalColor3Value == glm::vec3(0.73f, 0.74f, 0.75f));
    REQUIRE(p.vectorColor3Value.size() == 3);
    CHECK(p.vectorColor3Value[0] == glm::vec3(0.80f, 0.81f, 0.82f));
    CHECK(p.vectorColor3Value[1] == glm::vec3(0.83f, 0.84f, 0.85f));
    CHECK(p.vectorColor3Value[2] == glm::vec3(0.86f, 0.87f, 0.88f));

    CHECK(p.dcolor4Value == glm::dvec4(0.0, 0.1, 0.2, 0.3));
    REQUIRE(p.optionalDcolor4Value.has_value());
    CHECK(*p.optionalDcolor4Value == glm::dvec4(0.4, 0.5, 0.6, 0.7));
    REQUIRE(p.vectorDcolor4Value.size() == 3);
    CHECK(p.vectorDcolor4Value[0] == glm::dvec4(0.60, 0.61, 0.62, 0.63));
    CHECK(p.vectorDcolor4Value[1] == glm::dvec4(0.64, 0.65, 0.66, 0.67));
    CHECK(p.vectorDcolor4Value[2] == glm::dvec4(0.68, 0.69, 0.70, 0.71));

    CHECK(p.color4Value == glm::vec4(0.80f, 0.81f, 0.82f, 0.83f));
    REQUIRE(p.optionalColor4Value.has_value());
    CHECK(*p.optionalColor4Value == glm::vec4(0.84f, 0.85f, 0.86f, 0.87f));
    REQUIRE(p.vectorColor4Value.size() == 3);
    CHECK(p.vectorColor4Value[0] == glm::vec4(0.90f, 0.91f, 0.92f, 0.93f));
    CHECK(p.vectorColor4Value[1] == glm::vec4(0.94f, 0.95f, 0.96f, 0.97f));
    CHECK(p.vectorColor4Value[2] == glm::vec4(0.98f, 0.99f, 0.991f, 0.992f));

    CHECK(p.dateTimeValue == std::string("1990 03 11 12:40:53"));
    REQUIRE(p.optionalDateTimeValue.has_value());
    CHECK(*p.optionalDateTimeValue == std::string("1991 03 11 12:40:53"));
    REQUIRE(p.vectorDateTimeValue.size() == 3);
    CHECK(p.vectorDateTimeValue[0] == std::string("1992 03 11 12:40:53"));
    CHECK(p.vectorDateTimeValue[1] == std::string("1993 03 11 12:40:53"));
    CHECK(p.vectorDateTimeValue[2] == std::string("1994 03 11 12:40:53"));
    REQUIRE(p.optionalVectorDateTimeValue.has_value());
    REQUIRE((*p.optionalVectorDateTimeValue).size() == 3);
    CHECK((*p.optionalVectorDateTimeValue)[0] == std::string("1995 03 11 12:40:53"));
    CHECK((*p.optionalVectorDateTimeValue)[1] == std::string("1996 03 11 12:40:53"));
    CHECK((*p.optionalVectorDateTimeValue)[2] == std::string("1997 03 11 12:40:53"));
}

TEST_CASE("Attributes Documentation", "[structs][execution]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>("");

    REQUIRE(doc.entries.size() == 87);
    {
        DocumentationEntry e = doc.entries[0];
        CHECK(e.key == "KeyKey");
        CHECK(!e.optional);
        CHECK(e.documentation == "keyValue documentation");
        CHECK(e.verifier->type() == "Double");
        CHECK(dynamic_cast<DoubleVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        CHECK(e.key == "KeyKeyOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "keyValueOptional documentation");
        CHECK(e.verifier->type() == "Double");
        CHECK(dynamic_cast<DoubleVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        CHECK(e.key == "KeyKeyVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "keyValueVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        CHECK(dynamic_cast<DoubleVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[3];
        CHECK(e.key == "InRangeValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "inRangeValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == -2);
        CHECK(v->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[4];
        CHECK(e.key == "InRangeValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "inRangeValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == -2);
        CHECK(v->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[5];
        CHECK(e.key == "InRangeValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "inRangeValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* w = dynamic_cast<InRangeVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->lower == -2);
        CHECK(w->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[6];
        CHECK(e.key == "InRangeValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "inRangeValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == 8.0);
        CHECK(v->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[7];
        CHECK(e.key == "InRangeValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "inRangeValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == 8.0);
        CHECK(v->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[8];
        CHECK(e.key == "InRangeValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "inRangeValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* w =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->lower == 8.0);
        CHECK(w->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[9];
        CHECK(e.key == "NotInRangeValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "notInRangeValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* v =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == 5);
        CHECK(v->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[10];
        CHECK(e.key == "NotInRangeValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "notInRangeValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* v =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == 5);
        CHECK(v->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[11];
        CHECK(e.key == "NotInRangeValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "notInRangeValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* w =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->lower == 5);
        CHECK(w->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[12];
        CHECK(e.key == "NotInRangeValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "notInRangeValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == -0.5);
        CHECK(v->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[13];
        CHECK(e.key == "NotInRangeValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "notInRangeValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->lower == -0.5);
        CHECK(v->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[14];
        CHECK(e.key == "NotInRangeValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "notInRangeValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* w =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->lower == -0.5);
        CHECK(w->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[15];
        CHECK(e.key == "LessValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[16];
        CHECK(e.key == "LessValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "lessValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[17];
        CHECK(e.key == "LessValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        LessVerifier<IntVerifier>* w = dynamic_cast<LessVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[18];
        CHECK(e.key == "LessValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 21.0);
    }
    {
        DocumentationEntry e = doc.entries[19];
        CHECK(e.key == "LessValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "lessValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 22.0);
    }
    {
        DocumentationEntry e = doc.entries[20];
        CHECK(e.key == "LessValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* w = dynamic_cast<LessVerifier<DoubleVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->value == 23.0);
    }
    {
        DocumentationEntry e = doc.entries[21];
        CHECK(e.key == "LessEqualValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessEqualValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* v =
            dynamic_cast<LessEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[22];
        CHECK(e.key == "LessEqualValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "lessEqualValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* v =
            dynamic_cast<LessEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[23];
        CHECK(e.key == "LessEqualValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessEqualValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* w = dynamic_cast<LessEqualVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[24];
        CHECK(e.key == "LessEqualValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessEqualValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 27.0);
    }
    {
        DocumentationEntry e = doc.entries[25];
        CHECK(e.key == "LessEqualValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "lessEqualValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 27.0);
    }
    {
        DocumentationEntry e = doc.entries[26];
        CHECK(e.key == "LessEqualValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "lessEqualValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* w =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == 27.0);
    }
    {
        DocumentationEntry e = doc.entries[27];
        REQUIRE(e.key == "GreaterValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* v =
            dynamic_cast<GreaterVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[28];
        CHECK(e.key == "GreaterValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "greaterValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* v =
            dynamic_cast<GreaterVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[29];
        CHECK(e.key == "GreaterValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* w = dynamic_cast<GreaterVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[30];
        CHECK(e.key == "GreaterValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[31];
        CHECK(e.key == "GreaterValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "greaterValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[32];
        CHECK(e.key == "GreaterValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* w =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[33];
        CHECK(e.key == "GreaterEqualValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterEqualValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[34];
        CHECK(e.key == "GreaterEqualValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "greaterEqualValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[35];
        CHECK(e.key == "GreaterEqualValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterEqualValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* w =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[36];
        CHECK(e.key == "GreaterEqualValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterEqualValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[37];
        CHECK(e.key == "GreaterEqualValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "greaterEqualValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[38];
        CHECK(e.key == "GreaterEqualValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "greaterEqualValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* w =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[39];
        CHECK(e.key == "UnequalValueInt");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueInt documentation");
        CHECK(e.verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* v =
            dynamic_cast<UnequalVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[40];
        CHECK(e.key == "UnequalValueIntOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "unequalValueIntOptional documentation");
        CHECK(e.verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* v =
            dynamic_cast<UnequalVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[41];
        CHECK(e.key == "UnequalValueIntVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueIntVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* w = dynamic_cast<UnequalVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[42];
        CHECK(e.key == "UnequalValueFloat");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueFloat documentation");
        CHECK(e.verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* v =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[43];
        CHECK(e.key == "UnequalValueFloatOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "unequalValueFloatOptional documentation");
        CHECK(e.verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* v =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[44];
        CHECK(e.key == "UnequalValueFloatVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueFloatVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* w =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[45];
        CHECK(e.key == "DescValue");
        CHECK(!e.optional);
        CHECK(e.documentation == description);
        CHECK(e.verifier->type() == "Boolean");
        CHECK(dynamic_cast<BoolVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[46];
        CHECK(e.key == "InListValue1");
        CHECK(!e.optional);
        CHECK(e.documentation == "inListValue1 documentation");
        CHECK(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[47];
        CHECK(e.key == "InListValue1Optional");
        CHECK(e.optional);
        CHECK(e.documentation == "inListValue1Optional documentation");
        CHECK(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[48];
        CHECK(e.key == "InListValue1Vector");
        CHECK(!e.optional);
        CHECK(e.documentation == "inListValue1Vector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "String");
        InListVerifier<StringVerifier>* w = dynamic_cast<InListVerifier<StringVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[49];
        CHECK(e.key == "InListValue2");
        CHECK(!e.optional);
        CHECK(e.documentation == "inListValue2 documentation");
        CHECK(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[50];
        CHECK(e.key == "InListValue2Optional");
        CHECK(e.optional);
        CHECK(e.documentation == "inListValue2Optional documentation");
        CHECK(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[51];
        CHECK(e.key == "InListValue2Vector");
        CHECK(!e.optional);
        CHECK(e.documentation == "inListValue2Vector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "String");
        InListVerifier<StringVerifier>* w = dynamic_cast<InListVerifier<StringVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[52];
        CHECK(e.key == "UnequalValueString");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueString documentation");
        CHECK(e.verifier->type() == "String");
        UnequalVerifier<StringVerifier>* v =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[53];
        CHECK(e.key == "UnequalValueStringOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "unequalValueStringOptional documentation");
        CHECK(e.verifier->type() == "String");
        UnequalVerifier<StringVerifier>* v =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[54];
        CHECK(e.key == "UnequalValueStringVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "unequalValueStringVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "String");
        UnequalVerifier<StringVerifier>* w =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        CHECK(w->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[55];
        CHECK(e.key == "NotEmptyString");
        CHECK(!e.optional);
        CHECK(e.documentation == "string not empty value documentation");
        CHECK(e.verifier->type() == "String");
        StringVerifier* v = dynamic_cast<StringVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->mustBeNotEmpty() == true);
    }
    {
        DocumentationEntry e = doc.entries[56];
        CHECK(e.key == "NotEmptyStringOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "string not empty optional value documentation");
        CHECK(e.verifier->type() == "String");
        StringVerifier* v = dynamic_cast<StringVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->mustBeNotEmpty() == true);
    }
    {
        DocumentationEntry e = doc.entries[57];
        CHECK(e.key == "NotEmptyStringVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "string not empty vector value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "String");

        StringVerifier* w =
            dynamic_cast<StringVerifier*>(v->documentations[0].verifier.get());
        REQUIRE(w);
        CHECK(w->mustBeNotEmpty() == true);
    }
    {
        DocumentationEntry e = doc.entries[58];
        CHECK(e.key == "NotEmptyStringOptionalVector");
        CHECK(e.optional);
        CHECK(e.documentation == "string not empty optional vector value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "String");

        StringVerifier* w =
            dynamic_cast<StringVerifier*>(v->documentations[0].verifier.get());
        REQUIRE(w);
        CHECK(w->mustBeNotEmpty() == true);
    }
    {
        DocumentationEntry e = doc.entries[59];
        CHECK(e.key == "ReferenceValueOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "referenceValueOptional documentation");
        CHECK(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[60];
        CHECK(e.key == "ReferenceValueVector");
        CHECK(e.optional);
        CHECK(e.documentation == "referenceValueVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* w = dynamic_cast<ReferencingVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[61];
        CHECK(e.key == "DictValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "dictValue documentation");
        CHECK(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[62];
        CHECK(e.key == "DictValueVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "dictValueVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* w = dynamic_cast<ReferencingVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[63];
        CHECK(e.key == "DictValueOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "dictValueOptional documentation");
        CHECK(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[64];
        CHECK(e.key == "DictValueMap");
        CHECK(!e.optional);
        CHECK(e.documentation == "dictValueMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* w = dynamic_cast<ReferencingVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[65];
        CHECK(e.key == "VectorDictValueMap");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorDictValueMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        TableVerifier* w = dynamic_cast<TableVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(w->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* u = dynamic_cast<ReferencingVerifier*>(
            w->documentations[0].verifier.get()
        );
        REQUIRE(u);
        CHECK(u->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[66];
        CHECK(e.key == "OptionalDictValueMap");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalDictValueMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* w = dynamic_cast<ReferencingVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        CHECK(w->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[67];
        CHECK(e.key == "OptionalVectorDictValueMap");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalVectorDictValueMap documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Table");
        TableVerifier* w = dynamic_cast<TableVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(w->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* u = dynamic_cast<ReferencingVerifier*>(
            w->documentations[0].verifier.get()
        );
        REQUIRE(u);
        CHECK(u->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[68];
        CHECK(e.key == "Annotation");
        CHECK(!e.optional);
        CHECK(e.documentation == "annotation documentation");
        CHECK(e.verifier->type() == "String");
        StringAnnotationVerifier* v =
            dynamic_cast<StringAnnotationVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->annotation == "abc");
    }
    {
        DocumentationEntry e = doc.entries[69];
        CHECK(e.key == "AnnotationOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "annotationOptional documentation");
        CHECK(e.verifier->type() == "String");
        StringAnnotationVerifier* v =
            dynamic_cast<StringAnnotationVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->annotation == "def");
    }
    {
        DocumentationEntry e = doc.entries[70];
        CHECK(e.key == "AnnotationVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "annotationVector documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "String");
        StringAnnotationVerifier* w =
            dynamic_cast<StringAnnotationVerifier*>(v->documentations[0].verifier.get());
        REQUIRE(w);
        CHECK(w->annotation == "ghi");
    }
    {
        DocumentationEntry e = doc.entries[71];
        CHECK(e.key == "Dcolor3Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "dcolor3Value documentation");
        CHECK(e.verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[72];
        CHECK(e.key == "OptionalDcolor3Value");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalDcolor3Value documentation");
        CHECK(e.verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[73];
        CHECK(e.key == "VectorDcolor3Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorDcolor3Value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[74];
        CHECK(e.key == "Color3Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "color3Value documentation");
        CHECK(e.verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[75];
        CHECK(e.key == "OptionalColor3Value");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalColor3Value documentation");
        CHECK(e.verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[76];
        CHECK(e.key == "VectorColor3Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorColor3Value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "Color3");
        CHECK(dynamic_cast<Color3Verifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[77];
        CHECK(e.key == "Dcolor4Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "dcolor4Value documentation");
        CHECK(e.verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[78];
        CHECK(e.key == "OptionalDcolor4Value");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalDcolor4Value documentation");
        CHECK(e.verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[79];
        CHECK(e.key == "VectorDcolor4Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorDcolor4Value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[80];
        CHECK(e.key == "Color4Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "color4Value documentation");
        CHECK(e.verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[81];
        CHECK(e.key == "OptionalColor4Value");
        CHECK(e.optional);
        CHECK(e.documentation == "optionalColor4Value documentation");
        CHECK(e.verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[82];
        CHECK(e.key == "VectorColor4Value");
        CHECK(!e.optional);
        CHECK(e.documentation == "vectorColor4Value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "Color4");
        CHECK(dynamic_cast<Color4Verifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[83];
        CHECK(e.key == "DateTimeValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "dateTime value documentation");
        CHECK(e.verifier->type() == "Date and time");
        CHECK(dynamic_cast<DateTimeVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[84];
        CHECK(e.key == "OptionalDateTimeValue");
        CHECK(e.optional);
        CHECK(e.documentation == "optional dateTime value documentation");
        CHECK(e.verifier->type() == "Date and time");
        CHECK(dynamic_cast<DateTimeVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[85];
        CHECK(e.key == "VectorDateTimeValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "vector dateTime value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].verifier->type() == "Date and time");
        CHECK(dynamic_cast<DateTimeVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[86];
        CHECK(e.key == "OptionalVectorDateTimeValue");
        CHECK(e.optional);
        CHECK(e.documentation == "optional vector dateTime value documentation");
        CHECK(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        CHECK(v->documentations[0].key == "*");
        CHECK(v->documentations[0].verifier->type() == "Date and time");
        CHECK(dynamic_cast<DateTimeVerifier*>(v->documentations[0].verifier.get()));
    }
}
