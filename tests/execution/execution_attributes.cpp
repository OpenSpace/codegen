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

#include <openspace/documentation/documentation.h>
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
        float keyValue [[codegen::key(KeyKey)]];

        // keyValueOptional documentation
        std::optional<float> keyValueOptional [[codegen::key(KeyKeyOptional)]];

        // keyValueVector documentation
        std::vector<float> keyValueVector [[codegen::key(KeyKeyVector)]];

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

        // referenceValueOptional documentation
        std::optional<std::monostate> referenceValueOptional [[codegen::reference("abc")]];

        // referenceValueVector documentation
        std::optional<std::vector<std::monostate>> referenceValueVector [[codegen::reference("abc")]];

        // annotation documentation
        std::string annotation [[codegen::annotation("abc")]];

        // annotationOptional documentation
        std::optional<std::string> annotationOptional [[codegen::annotation("def")]];

        // annotationVector documentation
        std::vector<std::string> annotationVector [[codegen::annotation("ghi")]];
    };
#include "execution_attributes_codegen.cpp"
} // namespace

TEST_CASE("Attributes Bake", "[verifier]") {
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

    d.setValue("Annotation", std::string("annotation_abc"));
    d.setValue("AnnotationOptional", std::string("annotation_def"));
    {
        ghoul::Dictionary e;
        e.setValue("1", std::string("annotation_ghi"));
        e.setValue("2", std::string("annotation_jkl"));
        e.setValue("3", std::string("annotation_mno"));
        d.setValue("AnnotationVector", e);
    }

    Parameters p = codegen::bake<Parameters>(d);

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

    CHECK(p.annotation == "annotation_abc");
    CHECK(p.annotationOptional == "annotation_def");
    CHECK(p.annotationVector.size() == 3);
    CHECK(
        p.annotationVector ==
        std::vector<std::string>{ "annotation_ghi", "annotation_jkl", "annotation_mno" }
    );
}

TEST_CASE("Attributes Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 60);
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
        CHECK(e.key == "ReferenceValueOptional");
        CHECK(e.optional);
        CHECK(e.documentation == "referenceValueOptional documentation");
        CHECK(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        CHECK(v->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[56];
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
        DocumentationEntry e = doc.entries[57];
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
        DocumentationEntry e = doc.entries[58];
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
        DocumentationEntry e = doc.entries[59];
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
}
