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

namespace openspace { struct Attributes; }

namespace {
    struct Description {
        std::string description;
    };
    Description desc = { "Description" };

    std::vector<std::string> List = { "D", "E", "F" };

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
#include "attributes_codegen.cpp"
} // namespace

TEST_CASE("Attributes Bake", "[verifier]") {
    ghoul::Dictionary d;
    d.setValue("KeyKey", 2.1);
    d.setValue("KeyKeyOptional", 2.2);
    d.setValue("InRangeValueInt", 1.0);
    d.setValue("InRangeValueIntOptional", 2.0);
    d.setValue("InRangeValueFloat", 0.5);
    d.setValue("InRangeValueFloatOptional", 0.75);
    d.setValue("NotInRangeValueInt", 4.0);
    d.setValue("NotInRangeValueIntOptional", 3.0);
    d.setValue("NotInRangeValueFloat", 1.0);
    d.setValue("NotInRangeValueFloatOptional", 1.0);
    d.setValue("LessValueInt", -10.0);
    d.setValue("LessValueIntOptional", -10.0);
    d.setValue("LessValueFloat", 13.0);
    d.setValue("LessValueFloatOptional", 13.0);
    d.setValue("LessEqualValueInt", -11.0);
    d.setValue("LessEqualValueIntOptional", -11.0);
    d.setValue("LessEqualValueFloat", 12.0);
    d.setValue("LessEqualValueFloatOptional", 12.0);
    d.setValue("GreaterValueInt", 46.0);
    d.setValue("GreaterValueIntOptional", 46.0);
    d.setValue("GreaterValueFloat", -2.0);
    d.setValue("GreaterValueFloatOptional", -2.0);
    d.setValue("GreaterEqualValueInt", 5.0);
    d.setValue("GreaterEqualValueIntOptional", 5.0);
    d.setValue("GreaterEqualValueFloat", -25.0);
    d.setValue("GreaterEqualValueFloatOptional", -25.0);
    d.setValue("UnequalValueInt", 10.0);
    d.setValue("UnequalValueIntOptional", 10.0);
    d.setValue("UnequalValueFloat", 122.0);
    d.setValue("UnequalValueFloatOptional", 122.0);
    d.setValue("DescValue", true);
    d.setValue("InListValue1", std::string("A"));
    d.setValue("InListValue1Optional", std::string("A"));
    d.setValue("InListValue2", std::string("F"));
    d.setValue("InListValue2Optional", std::string("F"));
    d.setValue("UnequalValueString", std::string("zyxwv"));
    d.setValue("UnequalValueStringOptional", std::string("zyxwv"));

    Parameters p = codegen::bake<Parameters>(d);

    REQUIRE(p.keyValue == 2.1f);
    REQUIRE(p.keyValueOptional.has_value());
    REQUIRE(p.keyValueOptional == 2.2f);

    REQUIRE(p.inRangeValueInt == 1);
    REQUIRE(p.inRangeValueIntOptional.has_value());
    REQUIRE(p.inRangeValueIntOptional == 2);

    REQUIRE(p.inRangeValueFloat == 0.5f);
    REQUIRE(p.inRangeValueFloatOptional.has_value());
    REQUIRE(p.inRangeValueFloatOptional == 0.75f);

    REQUIRE(p.notInRangeValueInt == 4);
    REQUIRE(p.notInRangeValueIntOptional.has_value());
    REQUIRE(p.notInRangeValueIntOptional == 3);

    REQUIRE(p.notInRangeValueFloat == 1.f);
    REQUIRE(p.notInRangeValueFloatOptional.has_value());
    REQUIRE(p.notInRangeValueFloatOptional == 1.f);

    REQUIRE(p.lessValueInt == -10);
    REQUIRE(p.lessValueIntOptional.has_value());
    REQUIRE(p.lessValueIntOptional == -10);

    REQUIRE(p.lessValueFloat == 13.f);
    REQUIRE(p.lessValueFloatOptional.has_value());
    REQUIRE(p.lessValueFloatOptional == 13.f);

    REQUIRE(p.lessEqualValueInt == -11);
    REQUIRE(p.lessEqualValueIntOptional.has_value());
    REQUIRE(p.lessEqualValueIntOptional == -11);

    REQUIRE(p.lessEqualValueFloat == 12.f);
    REQUIRE(p.lessEqualValueFloatOptional.has_value());
    REQUIRE(p.lessEqualValueFloatOptional == 12.f);

    REQUIRE(p.greaterValueInt == 46);
    REQUIRE(p.greaterValueIntOptional.has_value());
    REQUIRE(p.greaterValueIntOptional == 46);

    REQUIRE(p.greaterValueFloat == -2.f);
    REQUIRE(p.greaterValueFloatOptional.has_value());
    REQUIRE(p.greaterValueFloatOptional == -2.f);

    REQUIRE(p.greaterEqualValueInt == 5);
    REQUIRE(p.greaterEqualValueIntOptional.has_value());
    REQUIRE(p.greaterEqualValueIntOptional == 5);

    REQUIRE(p.greaterEqualValueFloat == -25.f);
    REQUIRE(p.greaterEqualValueFloatOptional.has_value());
    REQUIRE(p.greaterEqualValueFloatOptional == -25.f);

    REQUIRE(p.unequalValueInt == 10);
    REQUIRE(p.unequalValueIntOptional.has_value());
    REQUIRE(p.unequalValueIntOptional == 10);

    REQUIRE(p.unequalValueFloat == 122.f);
    REQUIRE(p.unequalValueFloatOptional.has_value());
    REQUIRE(p.unequalValueFloatOptional == 122.f);

    REQUIRE(p.descValue == true);

    REQUIRE(p.inListValue1 == "A");
    REQUIRE(p.inListValue1Optional.has_value());
    REQUIRE(p.inListValue1Optional == "A");

    REQUIRE(p.inListValue2 == "F");
    REQUIRE(p.inListValue2Optional.has_value());
    REQUIRE(p.inListValue2Optional == "F");

    REQUIRE(p.unequalValueString == "zyxwv");
    REQUIRE(p.unequalValueStringOptional.has_value());
    REQUIRE(p.unequalValueStringOptional == "zyxwv");
}

TEST_CASE("Attributes Documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<openspace::Attributes>();

    REQUIRE(doc.entries.size() == 38);
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
        REQUIRE(e.key == "InRangeValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -2);
        REQUIRE(v->upper == 2);
    }
    {
        DocumentationEntry e = doc.entries[3];
        REQUIRE(e.key == "InRangeValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inRangeValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        InRangeVerifier<IntVerifier>* v =
            dynamic_cast<InRangeVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -2);
        REQUIRE(v->upper == 2);
    }
    {
        DocumentationEntry e = doc.entries[4];
        REQUIRE(e.key == "InRangeValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inRangeValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -0.5);
        REQUIRE(v->upper == 0.75);
    }
    {
        DocumentationEntry e = doc.entries[5];
        REQUIRE(e.key == "InRangeValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inRangeValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        InRangeVerifier<DoubleVerifier>* v =
            dynamic_cast<InRangeVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->lower == -0.5);
        REQUIRE(v->upper == 0.75);
    }
    {
        DocumentationEntry e = doc.entries[6];
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
        DocumentationEntry e = doc.entries[7];
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
        DocumentationEntry e = doc.entries[8];
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
        DocumentationEntry e = doc.entries[9];
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
        DocumentationEntry e = doc.entries[10];
        REQUIRE(e.key == "LessValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -5);
    }
    {
        DocumentationEntry e = doc.entries[11];
        REQUIRE(e.key == "LessValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        LessVerifier<IntVerifier>* v =
            dynamic_cast<LessVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == -5);
    }
    {
        DocumentationEntry e = doc.entries[12];
        REQUIRE(e.key == "LessValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 15.0);
    }
    {
        DocumentationEntry e = doc.entries[13];
        REQUIRE(e.key == "LessValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessVerifier<DoubleVerifier>* v =
            dynamic_cast<LessVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 15.0);
    }
    {
        DocumentationEntry e = doc.entries[14];
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
        DocumentationEntry e = doc.entries[15];
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
        DocumentationEntry e = doc.entries[16];
        REQUIRE(e.key == "LessEqualValueFloat");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "lessEqualValueFloat documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 12.0);
    }
    {
        DocumentationEntry e = doc.entries[17];
        REQUIRE(e.key == "LessEqualValueFloatOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "lessEqualValueFloatOptional documentation");
        REQUIRE(e.verifier->type() == "Double");
        LessEqualVerifier<DoubleVerifier>* v =
            dynamic_cast<LessEqualVerifier<DoubleVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 12.0);
    }
    {
        DocumentationEntry e = doc.entries[18];
        REQUIRE(e.key == "GreaterValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* v =
            dynamic_cast<GreaterVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 45);
    }
    {
        DocumentationEntry e = doc.entries[19];
        REQUIRE(e.key == "GreaterValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterVerifier<IntVerifier>* v =
            dynamic_cast<GreaterVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 45);
    }
    {
        DocumentationEntry e = doc.entries[20];
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
        DocumentationEntry e = doc.entries[21];
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
        DocumentationEntry e = doc.entries[22];
        REQUIRE(e.key == "GreaterEqualValueInt");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "greaterEqualValueInt documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 2);
    }
    {
        DocumentationEntry e = doc.entries[23];
        REQUIRE(e.key == "GreaterEqualValueIntOptional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "greaterEqualValueIntOptional documentation");
        REQUIRE(e.verifier->type() == "Integer");
        GreaterEqualVerifier<IntVerifier>* v =
            dynamic_cast<GreaterEqualVerifier<IntVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->value == 2);
    }
    {
        DocumentationEntry e = doc.entries[24];
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
        DocumentationEntry e = doc.entries[25];
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
        DocumentationEntry e = doc.entries[26];
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
        DocumentationEntry e = doc.entries[27];
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
        DocumentationEntry e = doc.entries[28];
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
        DocumentationEntry e = doc.entries[29];
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
        DocumentationEntry e = doc.entries[30];
        REQUIRE(e.key == "DescValue");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == desc.description);
        REQUIRE(e.verifier->type() == "Boolean");
        REQUIRE(dynamic_cast<BoolVerifier*>(e.verifier.get()));
    }
    {
        DocumentationEntry e = doc.entries[31];
        REQUIRE(e.key == "InListValue1");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue1 documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "A", "B", "C" });
    }
    {
        DocumentationEntry e = doc.entries[32];
        REQUIRE(e.key == "InListValue1Optional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inListValue1Optional documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "A", "B", "C" });
    }
    {
        DocumentationEntry e = doc.entries[33];
        REQUIRE(e.key == "InListValue2");
        REQUIRE(!e.optional);
        REQUIRE(e.documentation == "inListValue2 documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "D", "E", "F" });
    }
    {
        DocumentationEntry e = doc.entries[34];
        REQUIRE(e.key == "InListValue2Optional");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "inListValue2Optional documentation");
        REQUIRE(e.verifier->type() == "String");
        InListVerifier<StringVerifier>* v =
            dynamic_cast<InListVerifier<StringVerifier>*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values == std::vector<std::string>{ "D", "E", "F" });
    }
    {
        DocumentationEntry e = doc.entries[35];
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
        DocumentationEntry e = doc.entries[36];
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
        DocumentationEntry e = doc.entries[37];
        REQUIRE(e.key == "ReferenceValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "referenceValue documentation");
        REQUIRE(e.verifier->type() == "Table");
        ReferencingVerifier* v = dynamic_cast<ReferencingVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->identifier == "abc");
    }
}
