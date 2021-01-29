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

    Parameters p = codegen::bake<Parameters>(d);

    REQUIRE(p.keyValue == 2.1f);
    REQUIRE(p.keyValueOptional.has_value());
    REQUIRE(p.keyValueOptional == 2.2f);
    REQUIRE(p.keyValueVector == std::vector{ 2.3f, 2.4f, 2.5f });

    REQUIRE(p.inRangeValueInt == 3);
    REQUIRE(p.inRangeValueIntOptional.has_value());
    REQUIRE(p.inRangeValueIntOptional == 4);
    REQUIRE(p.inRangeValueIntVector == std::vector{ 5, 6, 7 });

    REQUIRE(p.inRangeValueFloat == 8.1f);
    REQUIRE(p.inRangeValueFloatOptional.has_value());
    REQUIRE(p.inRangeValueFloatOptional == 8.2f);
    REQUIRE(p.inRangeValueFloatVector == std::vector{ 8.3f, 8.4f, 8.5f });

    REQUIRE(p.notInRangeValueInt == 9);
    REQUIRE(p.notInRangeValueIntOptional.has_value());
    REQUIRE(p.notInRangeValueIntOptional == 10);
    REQUIRE(p.notInRangeValueIntVector == std::vector{ 11, 12, 13 });

    REQUIRE(p.notInRangeValueFloat == 14.1f);
    REQUIRE(p.notInRangeValueFloatOptional.has_value());
    REQUIRE(p.notInRangeValueFloatOptional == 14.2f);
    REQUIRE(p.notInRangeValueFloatVector == std::vector{ 14.3f, 14.4f, 14.5f });

    REQUIRE(p.lessValueInt == 15);
    REQUIRE(p.lessValueIntOptional.has_value());
    REQUIRE(p.lessValueIntOptional == 16);
    REQUIRE(p.lessValueIntVector == std::vector{ 17, 18, 19 });

    REQUIRE(p.lessValueFloat == 20.1f);
    REQUIRE(p.lessValueFloatOptional.has_value());
    REQUIRE(p.lessValueFloatOptional == 20.2f);
    REQUIRE(p.lessValueFloatVector == std::vector{ 20.3f, 20.4f, 20.5f });

    REQUIRE(p.lessEqualValueInt == 21);
    REQUIRE(p.lessEqualValueIntOptional.has_value());
    REQUIRE(p.lessEqualValueIntOptional == 22);
    REQUIRE(p.lessEqualValueIntVector == std::vector{ 23, 24, 25 });

    REQUIRE(p.lessEqualValueFloat == 26.1f);
    REQUIRE(p.lessEqualValueFloatOptional.has_value());
    REQUIRE(p.lessEqualValueFloatOptional == 26.2f);
    REQUIRE(p.lessEqualValueFloatVector == std::vector{ 26.3f, 26.4f, 26.5f });

    REQUIRE(p.greaterValueInt == 27);
    REQUIRE(p.greaterValueIntOptional.has_value());
    REQUIRE(p.greaterValueIntOptional == 28);
    REQUIRE(p.greaterValueIntVector == std::vector{ 29, 30, 31 });

    REQUIRE(p.greaterValueFloat == 32.1f);
    REQUIRE(p.greaterValueFloatOptional.has_value());
    REQUIRE(p.greaterValueFloatOptional == 32.2f);
    REQUIRE(p.greaterValueFloatVector == std::vector{ 32.3f, 32.4f, 32.5f });

    REQUIRE(p.greaterEqualValueInt == 33);
    REQUIRE(p.greaterEqualValueIntOptional.has_value());
    REQUIRE(p.greaterEqualValueIntOptional == 34);
    REQUIRE(p.greaterEqualValueIntVector == std::vector{ 35, 36, 37 });

    REQUIRE(p.greaterEqualValueFloat == 38.1f);
    REQUIRE(p.greaterEqualValueFloatOptional.has_value());
    REQUIRE(p.greaterEqualValueFloatOptional == 38.2f);
    REQUIRE(p.greaterEqualValueFloatVector == std::vector{ 38.3f, 38.4f, 38.5f });

    REQUIRE(p.unequalValueInt == 39);
    REQUIRE(p.unequalValueIntOptional.has_value());
    REQUIRE(p.unequalValueIntOptional == 40);
    REQUIRE(p.unequalValueIntVector == std::vector{ 41, 42, 43 });

    REQUIRE(p.unequalValueFloat == 44.1f);
    REQUIRE(p.unequalValueFloatOptional.has_value());
    REQUIRE(p.unequalValueFloatOptional == 44.2f);
    REQUIRE(p.unequalValueFloatVector == std::vector{ 44.3f, 44.4f, 44.5f });

    REQUIRE(p.descValue == true);

    REQUIRE(p.inListValue1 == "A");
    REQUIRE(p.inListValue1Optional.has_value());
    REQUIRE(p.inListValue1Optional == "B");
    REQUIRE(p.inListValue1Vector == std::vector<std::string>{ "C", "D", "E" });

    REQUIRE(p.inListValue2 == "F");
    REQUIRE(p.inListValue2Optional.has_value());
    REQUIRE(p.inListValue2Optional == "G");
    REQUIRE(p.inListValue2Vector == std::vector<std::string>{ "H", "I", "J" });

    REQUIRE(p.unequalValueString == "zyxwv");
    REQUIRE(p.unequalValueStringOptional.has_value());
    REQUIRE(p.unequalValueStringOptional == "zyxwv");
    REQUIRE(
        p.unequalValueStringVector ==
        std::vector<std::string>{ "zyxwv1", "zyxwv2", "zyxwv3"}
    );
}

TEST_CASE("Attributes Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 57);
    {
        DocumentationEntry e = doc.entries[0];
        REQUIRE(e.key == "KeyKey");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "keyValue documentation");
        REQUIRE(e.verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        REQUIRE(e.key == "KeyKeyOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "keyValueOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        REQUIRE(e.key == "KeyKeyVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "keyValueVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(v->documentations[0].verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[3];
        REQUIRE(e.key == "InRangeValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -2);
        REQUIRE(v->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[4];
        REQUIRE(e.key == "InRangeValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inRangeValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -2);
        REQUIRE(v->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[5];
        REQUIRE(e.key == "InRangeValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* w = dynamic_cast<InRangeVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->lower == -2);
        REQUIRE(w->upper == 8);
    }
    {
        DocumentationEntry e = doc.entries[6];
        REQUIRE(e.key == "InRangeValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == 8.0);
        REQUIRE(v->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[7];
        REQUIRE(e.key == "InRangeValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inRangeValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == 8.0);
        REQUIRE(v->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[8];
        REQUIRE(e.key == "InRangeValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* w =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->lower == 8.0);
        REQUIRE(w->upper == 9.0);
    }
    {
        DocumentationEntry e = doc.entries[9];
        REQUIRE(e.key == "NotInRangeValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "notInRangeValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* v =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == 5);
        REQUIRE(v->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[10];
        REQUIRE(e.key == "NotInRangeValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "notInRangeValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* v =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == 5);
        REQUIRE(v->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[11];
        REQUIRE(e.key == "NotInRangeValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "notInRangeValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        NotInRangeVerifier<IntVerifier>* w =
            dynamic_cast<NotInRangeVerifier<IntVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->lower == 5);
        REQUIRE(w->upper == 7);
    }
    {
        DocumentationEntry e = doc.entries[12];
        REQUIRE(e.key == "NotInRangeValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "notInRangeValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -0.5);
        REQUIRE(v->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[13];
        REQUIRE(e.key == "NotInRangeValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "notInRangeValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -0.5);
        REQUIRE(v->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[14];
        REQUIRE(e.key == "NotInRangeValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "notInRangeValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        NotInRangeVerifier<DoubleVerifier>* w =
            dynamic_cast<NotInRangeVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->lower == -0.5);
        REQUIRE(w->upper == 0.5);
    }
    {
        DocumentationEntry e = doc.entries[15];
        REQUIRE(e.key == "LessValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[16];
        REQUIRE(e.key == "LessValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[17];
        REQUIRE(e.key == "LessValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        LessVerifier<IntVerifier>* w = dynamic_cast<LessVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->value == 20);
    }
    {
        DocumentationEntry e = doc.entries[18];
        REQUIRE(e.key == "LessValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 21.0);
    }
    {
        DocumentationEntry e = doc.entries[19];
        REQUIRE(e.key == "LessValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 22.0);
    }
    {
        DocumentationEntry e = doc.entries[20];
        REQUIRE(e.key == "LessValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* w = dynamic_cast<LessVerifier<DoubleVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->value == 23.0);
    }
    {
        DocumentationEntry e = doc.entries[21];
        REQUIRE(e.key == "LessEqualValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessEqualValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* v =
            dynamic_cast<LessEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[22];
        REQUIRE(e.key == "LessEqualValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessEqualValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* v =
            dynamic_cast<LessEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[23];
        REQUIRE(e.key == "LessEqualValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessEqualValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        LessEqualVerifier<IntVerifier>* w = dynamic_cast<LessEqualVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[24];
        REQUIRE(e.key == "LessEqualValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessEqualValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 27.0);
    }
    {
        DocumentationEntry e = doc.entries[25];
        REQUIRE(e.key == "LessEqualValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessEqualValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 27.0);
    }
    {
        DocumentationEntry e = doc.entries[26];
        REQUIRE(e.key == "LessEqualValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessEqualValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* w =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->value == 27.0);
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
        REQUIRE(e.key == "GreaterValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* v =
            dynamic_cast<GreaterVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[29];
        REQUIRE(e.key == "GreaterValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* w = dynamic_cast<GreaterVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->value == 25);
    }
    {
        DocumentationEntry e = doc.entries[30];
        REQUIRE(e.key == "GreaterValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[31];
        REQUIRE(e.key == "GreaterValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[32];
        REQUIRE(e.key == "GreaterValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        GreaterVerifier<DoubleVerifier>* w =
            dynamic_cast<GreaterVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->value == -5.0);
    }
    {
        DocumentationEntry e = doc.entries[33];
        REQUIRE(e.key == "GreaterEqualValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterEqualValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[34];
        REQUIRE(e.key == "GreaterEqualValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterEqualValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[35];
        REQUIRE(e.key == "GreaterEqualValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterEqualValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* w =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->value == 33);
    }
    {
        DocumentationEntry e = doc.entries[36];
        REQUIRE(e.key == "GreaterEqualValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterEqualValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[37];
        REQUIRE(e.key == "GreaterEqualValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterEqualValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[38];
        REQUIRE(e.key == "GreaterEqualValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterEqualValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        GreaterEqualVerifier<DoubleVerifier>* w =
            dynamic_cast<GreaterEqualVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->value == -25.0);
    }
    {
        DocumentationEntry e = doc.entries[39];
        REQUIRE(e.key == "UnequalValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* v =
            dynamic_cast<UnequalVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[40];
        REQUIRE(e.key == "UnequalValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "unequalValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* v =
            dynamic_cast<UnequalVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[41];
        REQUIRE(e.key == "UnequalValueIntVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueIntVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Integer");
        UnequalVerifier<IntVerifier>* w = dynamic_cast<UnequalVerifier<IntVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->value == 1);
    }
    {
        DocumentationEntry e = doc.entries[42];
        REQUIRE(e.key == "UnequalValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* v =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[43];
        REQUIRE(e.key == "UnequalValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "unequalValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* v =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[44];
        REQUIRE(e.key == "UnequalValueFloatVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueFloatVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Double");
        UnequalVerifier<DoubleVerifier>* w =
            dynamic_cast<UnequalVerifier<DoubleVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w);
        REQUIRE(w->value == 123.0);
    }
    {
        DocumentationEntry e = doc.entries[45];
        REQUIRE(e.key == "DescValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == description);
        REQUIRE(e.verifier->type() == "Boolean");
        REQUIRE(dynamic_cast<BoolVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[46];
        REQUIRE(e.key == "InListValue1");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue1 documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[47];
        REQUIRE(e.key == "InListValue1Optional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inListValue1Optional documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[48];
        REQUIRE(e.key == "InListValue1Vector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue1Vector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "String");
        InListVerifier<StringVerifier>* w = dynamic_cast<InListVerifier<StringVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w->values == std::vector<std::string>{ "A", "B", "C", "D", "E" });
    }
    {
        DocumentationEntry e = doc.entries[49];
        REQUIRE(e.key == "InListValue2");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue2 documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[50];
        REQUIRE(e.key == "InListValue2Optional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inListValue2Optional documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[51];
        REQUIRE(e.key == "InListValue2Vector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue2Vector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "String");
        InListVerifier<StringVerifier>* w = dynamic_cast<InListVerifier<StringVerifier>*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w->values == std::vector<std::string>{ "F", "G", "H", "I", "J" });
    }
    {
        DocumentationEntry e = doc.entries[52];
        REQUIRE(e.key == "UnequalValueString");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueString documentation");
        REQUIRE(e.verifier->type() == "String");
        UnequalVerifier<StringVerifier>* v =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[53];
        REQUIRE(e.key == "UnequalValueStringOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "unequalValueStringOptional documentation");
        REQUIRE(e.verifier->type() == "String");
        UnequalVerifier<StringVerifier>* v =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[54];
        REQUIRE(e.key == "UnequalValueStringVector");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "unequalValueStringVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "String");
        UnequalVerifier<StringVerifier>* w =
            dynamic_cast<UnequalVerifier<StringVerifier>*>(
                v->documentations[0].verifier.get()
            );
        REQUIRE(w->value == "abcdef");
    }
    {
        DocumentationEntry e = doc.entries[55];
        REQUIRE(e.key == "ReferenceValueOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "referenceValueOptional documentation");
        REQUIRE(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->identifier == "abc");
    }
    {
        DocumentationEntry e = doc.entries[56];
        REQUIRE(e.key == "ReferenceValueVector");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "referenceValueVector documentation");
        REQUIRE(e.verifier->type() == "Table");
        TableVerifier* v = dynamic_cast<TableVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->documentations.size() == 1);
        REQUIRE(v->documentations[0].key == "*");
        REQUIRE(v->documentations[0].verifier->type() == "Table");
        ReferencingVerifier* w = dynamic_cast<ReferencingVerifier*>(
            v->documentations[0].verifier.get()
        );
        REQUIRE(w);
        REQUIRE(w->identifier == "abc");
    }
}
