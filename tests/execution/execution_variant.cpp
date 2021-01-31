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

namespace {
    struct [[codegen::Dictionary(Variant)]] Parameters {
        // boolDouble value documentation
        std::variant<bool, double> boolDoubleValue;

        // floatString value documentation
        std::variant<float, std::string> floatStringValue;

        // ivecs value documentation
        std::variant<glm::ivec2, glm::ivec3, glm::ivec4> ivecsValue;

        // vecmat1 value documentation
        std::variant<glm::dvec2, glm::dvec3, glm::dvec4, glm::mat2x3, glm::mat4x2,
            glm::dmat4x4> vecmat1;

        // vecmat2 value documentation
        std::variant<glm::mat2x2, glm::dmat3x3, glm::mat2x4> vecmat2;

        // rest value documentation
        std::variant<glm::vec2, glm::vec3, glm::vec4, glm::mat2x3, glm::mat2x4,
            glm::mat3x3, glm::mat3x4, glm::mat4x4> restValue;

        // optional documentation
        std::optional<std::variant<bool, int>> optionalValue;

        // variant vector documentation
        std::variant<std::vector<std::string>, std::string> variantVector;

        // variant vector 2 documentation
        std::variant<std::string, std::vector<std::string>> variantVector2;
    };
#include "execution_variant_codegen.cpp"
} // namespace

TEST_CASE("Variant bake", "[verifier]") {
    {
        ghoul::Dictionary d1;
        d1.setValue("BoolDoubleValue", false);
        d1.setValue("FloatStringValue", 2.0);
        d1.setValue("IvecsValue", glm::dvec2(1.0, 2.0));
        d1.setValue("Vecmat1", glm::dvec2(3.1, 3.2));
        d1.setValue("Vecmat2", glm::dmat2x2(4.1, 4.2, 4.3, 4.4));
        d1.setValue(
            "RestValue",
            glm::dmat3x4(5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 5.10, 5.11, 5.12)
        );
        d1.setValue("OptionalValue", 5.0);
        d1.setValue("VariantVector", std::string("abc"));
        d1.setValue("VariantVector2", std::string("def"));

        const Parameters p1 = codegen::bake<Parameters>(d1);
        CHECK(std::get<bool>(p1.boolDoubleValue) == false);
        CHECK(std::get<float>(p1.floatStringValue) == 2.f);
        CHECK(std::get<glm::ivec2>(p1.ivecsValue) == glm::ivec2(1, 2));
        CHECK(std::get<glm::dvec2>(p1.vecmat1) == glm::dvec2(3.1, 3.2));
        CHECK(std::get<glm::mat2x2>(p1.vecmat2) == glm::mat2x2(4.1f, 4.2f, 4.3f, 4.4f));
        CHECK(
            std::get<glm::mat3x4>(p1.restValue) ==
            glm::mat3x4(
                5.1f, 5.2f, 5.3f, 5.4f, 5.5f, 5.6f,
                5.7f, 5.8f, 5.9f, 5.10f, 5.11f, 5.12f
            )
        );
        REQUIRE(p1.optionalValue.has_value());
        CHECK(std::get<int>(*p1.optionalValue) == 5);
        REQUIRE(std::holds_alternative<std::string>(p1.variantVector));
        CHECK(std::get<std::string>(p1.variantVector) == "abc");
        REQUIRE(std::holds_alternative<std::string>(p1.variantVector2));
        CHECK(std::get<std::string>(p1.variantVector2) == "def");
    }

    {
        ghoul::Dictionary d2;
        d2.setValue("BoolDoubleValue", 6.0);
        d2.setValue("FloatStringValue", std::string("abc"));
        d2.setValue("IvecsValue", glm::dvec3(7.0, 8.0, 9.0));
        d2.setValue("Vecmat1", glm::dvec3(10.1, 10.2, 10.3));
        d2.setValue(
            "Vecmat2",
            glm::dmat3x3(11.1, 11.2, 11.3, 11.4, 11.5, 11.6, 11.7, 11.8, 11.9)
        );
        d2.setValue(
            "RestValue",
            glm::dmat3x4(
                12.1, 12.2, 12.3, 12.4, 12.5, 12.6,
                12.7, 12.8, 12.9, 12.10, 12.11, 12.12
            )
        );
        {
            ghoul::Dictionary e;
            e.setValue("1", std::string("abc"));
            e.setValue("2", std::string("def"));
            e.setValue("3", std::string("ghi"));
            e.setValue("4", std::string("jkl"));
            d2.setValue("VariantVector", e);
        }
        {
            ghoul::Dictionary e;
            e.setValue("1", std::string("mno"));
            e.setValue("2", std::string("pqr"));
            e.setValue("3", std::string("stu"));
            e.setValue("4", std::string("vwx"));
            d2.setValue("VariantVector2", e);
        }

        const Parameters p2 = codegen::bake<Parameters>(d2);
        CHECK(std::get<double>(p2.boolDoubleValue) == 6.0);
        CHECK(std::get<std::string>(p2.floatStringValue) == "abc");
        CHECK(std::get<glm::ivec3>(p2.ivecsValue) == glm::ivec3(7, 8, 9));
        CHECK(std::get<glm::dvec3>(p2.vecmat1) == glm::dvec3(10.1, 10.2, 10.3));
        CHECK(
            std::get<glm::dmat3x3>(p2.vecmat2) ==
            glm::dmat3x3(11.1, 11.2, 11.3, 11.4, 11.5, 11.6, 11.7, 11.8, 11.9)
        );
        CHECK(
            std::get<glm::mat3x4>(p2.restValue) ==
            glm::mat3x4(
                12.1f, 12.2f, 12.3f, 12.4f, 12.5f, 12.6f,
                12.7f, 12.8f, 12.9f, 12.10f, 12.11f, 12.12f
            )
        );
        CHECK(!p2.optionalValue.has_value());
        REQUIRE(std::holds_alternative<std::vector<std::string>>(p2.variantVector));
        CHECK(
            std::get<std::vector<std::string>>(p2.variantVector) ==
            std::vector<std::string>{ "abc", "def", "ghi", "jkl" }
        );
        REQUIRE(std::holds_alternative<std::vector<std::string>>(p2.variantVector2));
        CHECK(
            std::get<std::vector<std::string>>(p2.variantVector2) ==
            std::vector<std::string>{ "mno", "pqr", "stu", "vwx" }
        );
    }

    {
        ghoul::Dictionary d3;
        d3.setValue("BoolDoubleValue", 13.1);
        d3.setValue("FloatStringValue", std::string("abc"));
        d3.setValue("IvecsValue", glm::dvec4(14.0, 15.0, 16.0, 17.0));
        d3.setValue("Vecmat1", glm::dvec4(18.1, 18.2, 18.3, 18.4));
        d3.setValue(
            "Vecmat2",
            glm::dmat2x4(19.1, 19.2, 19.3, 19.4, 19.5, 19.6, 19.7, 19.8)
        );
        d3.setValue("RestValue", glm::dmat2x3(20.1, 20.2, 20.3, 20.4, 20.5, 20.6));
        d3.setValue("OptionalValue", true);
        d3.setValue("VariantVector", std::string("abc"));
        d3.setValue("VariantVector2", std::string("def"));
        const Parameters p3 = codegen::bake<Parameters>(d3);
        CHECK(std::get<double>(p3.boolDoubleValue) == 13.1);
        CHECK(std::get<std::string>(p3.floatStringValue) == "abc");
        CHECK(std::get<glm::ivec4>(p3.ivecsValue) == glm::ivec4(14, 15, 16, 17));
        CHECK(std::get<glm::dvec4>(p3.vecmat1) == glm::dvec4(18.1, 18.2, 18.3, 18.4));
        CHECK(
            std::get<glm::mat2x4>(p3.vecmat2) ==
            glm::mat2x4(19.1f, 19.2f, 19.3f, 19.4f, 19.5f, 19.6f, 19.7f, 19.8f)
        );
        CHECK(
            std::get<glm::mat2x3>(p3.restValue) ==
            glm::mat2x3(20.1f, 20.2f, 20.3f, 20.4f, 20.5f, 20.6f)
        );
        REQUIRE(p3.optionalValue.has_value());
        CHECK(std::get<bool>(*p3.optionalValue) == true);
        REQUIRE(std::holds_alternative<std::string>(p3.variantVector));
        CHECK(std::get<std::string>(p3.variantVector) == "abc");
        REQUIRE(std::holds_alternative<std::string>(p3.variantVector2));
        CHECK(std::get<std::string>(p3.variantVector2) == "def");
    }

    {
        ghoul::Dictionary d4;
        d4.setValue("BoolDoubleValue", 20.0);
        d4.setValue("FloatStringValue", std::string("abc"));
        d4.setValue("IvecsValue", glm::dvec2(21.0, 22.0));
        d4.setValue(
            "Vecmat1",
            glm::dmat4x4(
                23.1, 23.2, 23.3, 23.4, 23.5, 23.6, 23.7, 23.8,
                23.9, 23.10, 23.11, 23.12, 23.13, 23.14, 23.15, 23.16
            )
        );
        d4.setValue("Vecmat2", glm::dmat2x2(24.1, 24.2, 24.3, 24.4));
        d4.setValue(
            "RestValue",
            glm::dmat3x4(
                25.1, 25.2, 25.3, 25.4, 25.5, 25.6, 25.7, 25.8, 25.9, 25.10, 25.11, 25.12
            )
        );
        d4.setValue("VariantVector", std::string("abc"));
        d4.setValue("VariantVector2", std::string("def"));
        const Parameters p4 = codegen::bake<Parameters>(d4);
        CHECK(std::get<double>(p4.boolDoubleValue) == 20);
        CHECK(std::get<std::string>(p4.floatStringValue) == "abc");
        CHECK(std::get<glm::ivec2>(p4.ivecsValue) == glm::ivec2(21, 22));
        CHECK(
            std::get<glm::dmat4x4>(p4.vecmat1) ==
            glm::dmat4x4(
                23.1, 23.2, 23.3, 23.4, 23.5, 23.6, 23.7, 23.8,
                23.9, 23.10, 23.11, 23.12, 23.13, 23.14, 23.15, 23.16
            )
        );
        CHECK(
            std::get<glm::mat2x2>(p4.vecmat2) == glm::mat2x2(24.1f, 24.2f, 24.3f, 24.4f)
        );
        CHECK(
            std::get<glm::mat3x4>(p4.restValue) ==
            glm::mat3x4(
                25.1f, 25.2f, 25.3f, 25.4f, 25.5f, 25.6f,
                25.7f, 25.8f, 25.9f, 25.10f, 25.11f, 25.12f
            )
        );
        CHECK(!p4.optionalValue.has_value());
        REQUIRE(std::holds_alternative<std::string>(p4.variantVector));
        CHECK(std::get<std::string>(p4.variantVector) == "abc");
        REQUIRE(std::holds_alternative<std::string>(p4.variantVector2));
        CHECK(std::get<std::string>(p4.variantVector2) == "def");
    }
}

TEST_CASE("Variant documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<Parameters>();

    REQUIRE(doc.entries.size() == 9);
    {
        DocumentationEntry e = doc.entries[0];
        CHECK(e.key == "BoolDoubleValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "boolDouble value documentation");
        CHECK(e.verifier->type() == "Boolean, or Double");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 2);
        CHECK(v->values[0]->type() == "Boolean");
        CHECK(dynamic_cast<BoolVerifier*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Double");
        CHECK(dynamic_cast<DoubleVerifier*>(v->values[1].get()));
    }
    {
        DocumentationEntry e = doc.entries[1];
        CHECK(e.key == "FloatStringValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "floatString value documentation");
        CHECK(e.verifier->type() == "Double, or String");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 2);
        CHECK(v->values[0]->type() == "Double");
        CHECK(dynamic_cast<DoubleVerifier*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(v->values[1].get()));
    }
    {
        DocumentationEntry e = doc.entries[2];
        CHECK(e.key == "IvecsValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "ivecs value documentation");
        CHECK(e.verifier->type() == "Vector2<int>, Vector3<int>, or Vector4<int>");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 3);
        CHECK(v->values[0]->type() == "Vector2<int>");
        CHECK(dynamic_cast<Vector2Verifier<int>*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Vector3<int>");
        CHECK(dynamic_cast<Vector3Verifier<int>*>(v->values[1].get()));
        CHECK(v->values[2]->type() == "Vector4<int>");
        CHECK(dynamic_cast<Vector4Verifier<int>*>(v->values[2].get()));
    }
    {
        DocumentationEntry e = doc.entries[3];
        CHECK(e.key == "Vecmat1");
        CHECK(!e.optional);
        CHECK(e.documentation == "vecmat1 value documentation");
        CHECK(
            e.verifier->type() ==
            "Vector2<double>, Vector3<double>, Vector4<double>, Matrix2x3<double>, "
            "Matrix4x2<double>, or Matrix4x4<double>"
        );
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 6);
        CHECK(v->values[0]->type() == "Vector2<double>");
        CHECK(dynamic_cast<Vector2Verifier<double>*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Vector3<double>");
        CHECK(dynamic_cast<Vector3Verifier<double>*>(v->values[1].get()));
        CHECK(v->values[2]->type() == "Vector4<double>");
        CHECK(dynamic_cast<Vector4Verifier<double>*>(v->values[2].get()));
        CHECK(v->values[3]->type() == "Matrix2x3<double>");
        CHECK(dynamic_cast<Matrix2x3Verifier<double>*>(v->values[3].get()));
        CHECK(v->values[4]->type() == "Matrix4x2<double>");
        CHECK(dynamic_cast<Matrix4x2Verifier<double>*>(v->values[4].get()));
        CHECK(v->values[5]->type() == "Matrix4x4<double>");
        CHECK(dynamic_cast<Matrix4x4Verifier<double>*>(v->values[5].get()));
    }
    {
        DocumentationEntry e = doc.entries[4];
        CHECK(e.key == "Vecmat2");
        CHECK(!e.optional);
        CHECK(e.documentation == "vecmat2 value documentation");
        CHECK(
            e.verifier->type() ==
            "Matrix2x2<double>, Matrix3x3<double>, or Matrix2x4<double>"
        );
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 3);
        CHECK(v->values[0]->type() == "Matrix2x2<double>");
        CHECK(dynamic_cast<Matrix2x2Verifier<double>*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Matrix3x3<double>");
        CHECK(dynamic_cast<Matrix3x3Verifier<double>*>(v->values[1].get()));
        CHECK(v->values[2]->type() == "Matrix2x4<double>");
        CHECK(dynamic_cast<Matrix2x4Verifier<double>*>(v->values[2].get()));
    }
    {
        DocumentationEntry e = doc.entries[5];
        CHECK(e.key == "RestValue");
        CHECK(!e.optional);
        CHECK(e.documentation == "rest value documentation");
        CHECK(
            e.verifier->type() ==
            "Vector2<double>, Vector3<double>, Vector4<double>, Matrix2x3<double>, "
            "Matrix2x4<double>, Matrix3x3<double>, Matrix3x4<double>, or "
            "Matrix4x4<double>"
        );
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 8);
        CHECK(v->values[0]->type() == "Vector2<double>");
        CHECK(dynamic_cast<Vector2Verifier<double>*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Vector3<double>");
        CHECK(dynamic_cast<Vector3Verifier<double>*>(v->values[1].get()));
        CHECK(v->values[2]->type() == "Vector4<double>");
        CHECK(dynamic_cast<Vector4Verifier<double>*>(v->values[2].get()));
        CHECK(v->values[3]->type() == "Matrix2x3<double>");
        CHECK(dynamic_cast<Matrix2x3Verifier<double>*>(v->values[3].get()));
        CHECK(v->values[4]->type() == "Matrix2x4<double>");
        CHECK(dynamic_cast<Matrix2x4Verifier<double>*>(v->values[4].get()));
        CHECK(v->values[5]->type() == "Matrix3x3<double>");
        CHECK(dynamic_cast<Matrix3x3Verifier<double>*>(v->values[5].get()));
        CHECK(v->values[6]->type() == "Matrix3x4<double>");
        CHECK(dynamic_cast<Matrix3x4Verifier<double>*>(v->values[6].get()));
        CHECK(v->values[7]->type() == "Matrix4x4<double>");
        CHECK(dynamic_cast<Matrix4x4Verifier<double>*>(v->values[7].get()));
    }
    {
        DocumentationEntry e = doc.entries[6];
        CHECK(e.key == "OptionalValue");
        CHECK(e.optional);
        CHECK(e.documentation == "optional documentation");
        CHECK(e.verifier->type() == "Boolean, or Integer");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 2);
        CHECK(v->values[0]->type() == "Boolean");
        CHECK(dynamic_cast<BoolVerifier*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Integer");
        CHECK(dynamic_cast<IntVerifier*>(v->values[1].get()));
    }
    {
        DocumentationEntry e = doc.entries[7];
        CHECK(e.key == "VariantVector");
        CHECK(!e.optional);
        CHECK(e.documentation == "variant vector documentation");
        CHECK(e.verifier->type() == "Table, or String");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 2);
        CHECK(v->values[0]->type() == "Table");
        TableVerifier* w = dynamic_cast<TableVerifier*>(v->values[0].get());
        REQUIRE(w);
        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(w->documentations[0].optional);
        CHECK(w->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));
        CHECK(v->values[1]->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(v->values[1].get()));
    }
    {
        DocumentationEntry e = doc.entries[8];
        CHECK(e.key == "VariantVector2");
        CHECK(!e.optional);
        CHECK(e.documentation == "variant vector 2 documentation");
        CHECK(e.verifier->type() == "String, or Table");
        OrVerifier* v = dynamic_cast<OrVerifier*>(e.verifier.get());
        REQUIRE(v);
        REQUIRE(v->values.size() == 2);
        CHECK(v->values[0]->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(v->values[0].get()));
        CHECK(v->values[1]->type() == "Table");
        TableVerifier* w = dynamic_cast<TableVerifier*>(v->values[1].get());
        REQUIRE(w);
        REQUIRE(w->documentations.size() == 1);
        CHECK(w->documentations[0].key == "*");
        CHECK(w->documentations[0].optional);
        CHECK(w->documentations[0].verifier->type() == "String");
        CHECK(dynamic_cast<StringVerifier*>(w->documentations[0].verifier.get()));
    }
}
