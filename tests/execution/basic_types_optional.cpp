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

namespace openspace { struct BasicTypesOptional; }

namespace {
    struct [[codegen::Dictionary(BasicTypesOptional)]] Parameters {
        // bool value documentation
        std::optional<bool> boolValue;

        // int value documentation
        std::optional<int> intValue;

        // double value documentation
        std::optional<double> doubleValue;

        // float value documentation
        std::optional<float> floatValue;

        // string value documentation
        std::optional<std::string> stringValue;

        // ivec2 value documentation
        std::optional<glm::ivec2> ivec2Value;

        // ivec3 value documentation
        std::optional<glm::ivec3> ivec3Value;

        // ivec4 value documentation
        std::optional<glm::ivec4> ivec4Value;

        // dvec2 value documentation
        std::optional<glm::dvec2> dvec2Value;

        // dvec3 value documentation
        std::optional<glm::dvec3> dvec3Value;

        // dvec4 value documentation
        std::optional<glm::dvec4> dvec4Value;

        // vec2 value documentation
        std::optional<glm::vec2> vec2Value;

        // vec3 value documentation
        std::optional<glm::vec3> vec3Value;

        // vec4 value documentation
        std::optional<glm::vec4> vec4Value;

        // mat2x2 value documentation
        std::optional<glm::mat2x2> mat2x2Value;

        // mat2x3 value documentation
        std::optional<glm::mat2x3> mat2x3Value;

        // mat2x4 value documentation
        std::optional<glm::mat2x4> mat2x4Value;

        // mat3x2 value documentation
        std::optional<glm::mat3x2> mat3x2Value;

        // mat3x3 value documentation
        std::optional<glm::mat3x3> mat3x3Value;

        // mat3x4 value documentation
        std::optional<glm::mat3x4> mat3x4Value;

        // mat4x2 value documentation
        std::optional<glm::mat4x2> mat4x2Value;

        // mat4x3 value documentation
        std::optional<glm::mat4x3> mat4x3Value;

        // mat4x4 value documentation
        std::optional<glm::mat4x4> mat4x4Value;

        // dmat2x2 value documentation
        std::optional<glm::dmat2x2> dmat2x2Value;

        // dmat2x3 value documentation
        std::optional<glm::dmat2x3> dmat2x3Value;

        // dmat2x4 value documentation
        std::optional<glm::dmat2x4> dmat2x4Value;

        // dmat3x2 value documentation
        std::optional<glm::dmat3x2> dmat3x2Value;

        // dmat3x3 value documentation
        std::optional<glm::dmat3x3> dmat3x3Value;

        // dmat3x4 value documentation
        std::optional<glm::dmat3x4> dmat3x4Value;

        // dmat4x2 value documentation
        std::optional<glm::dmat4x2> dmat4x2Value;

        // dmat4x3 value documentation
        std::optional<glm::dmat4x3> dmat4x3Value;

        // dmat4x4 value documentation
        std::optional<glm::dmat4x4> dmat4x4Value;
    };
#include "basic_types_optional_codegen.cpp"
} // namespace

TEST_CASE("Basic Types Optional bake", "[verifier]") {
    ghoul::Dictionary d;
    d.setValue("BoolValue", true);
    d.setValue("IntValue", 2.0);
    d.setValue("DoubleValue", 3.1);
    d.setValue("FloatValue", 4.1);
    d.setValue("StringValue", std::string("abc"));
    d.setValue("Ivec2Value", glm::dvec2(5.0, 6.0));
    d.setValue("Ivec3Value", glm::dvec3(7.0, 8.0, 9.0));
    d.setValue("Ivec4Value", glm::dvec4(10.0, 11.0, 12.0, 13.0));
    d.setValue("Dvec2Value", glm::dvec2(14.1, 14.2));
    d.setValue("Dvec3Value", glm::dvec3(15.1, 15.2, 15.3));
    d.setValue("Dvec4Value", glm::dvec4(16.1, 16.2, 16.3, 16.4));
    d.setValue("Vec2Value", glm::dvec2(17.1, 17.2));
    d.setValue("Vec3Value", glm::dvec3(18.1, 18.2, 18.3));
    d.setValue("Vec4Value", glm::dvec4(19.1, 19.2, 19.3, 19.4));
    d.setValue("Mat2x2Value", glm::dmat2x2(20.1, 20.2, 20.3, 20.4));
    d.setValue("Mat2x3Value", glm::dmat2x3(21.1, 21.2, 21.3, 21.4, 21.5, 21.6));
    d.setValue(
        "Mat2x4Value",
        glm::dmat2x4(22.1, 22.2, 22.3, 22.4, 22.5, 22.6, 22.7, 22.8)
    );
    d.setValue("Mat3x2Value", glm::dmat3x2(23.1, 23.2, 23.3, 23.4, 23.5, 23.6));
    d.setValue(
        "Mat3x3Value",
        glm::dmat3x3(24.1, 24.2, 24.3, 24.4, 24.5, 24.6, 24.7, 24.8, 24.9)
    );
    d.setValue(
        "Mat3x4Value",
        glm::dmat3x4(
            25.1, 25.2, 25.3, 25.4, 25.5, 25.6, 25.7, 25.8, 25.9, 25.10, 25.11, 25.12
        )
    );
    d.setValue(
        "Mat4x2Value",
        glm::dmat4x2(26.1, 26.2, 26.3, 26.4, 26.5, 26.6, 26.7, 26.8)
    );
    d.setValue(
        "Mat4x3Value",
        glm::dmat4x3(
            27.1, 27.2, 27.3, 27.4, 27.5, 27.6, 27.7, 27.8, 27.9, 27.10, 27.11, 27.12
        )
    );
    d.setValue(
        "Mat4x4Value",
        glm::dmat4x4(
            28.1, 28.2, 28.3, 28.4, 28.5, 28.6, 28.7, 28.8,
            28.9, 28.10, 28.11, 28.12, 28.13, 28.14, 28.15, 28.16
        )
    );
    d.setValue("Dmat2x2Value", glm::dmat2x2(29.1, 29.2, 29.3, 29.4));
    d.setValue("Dmat2x3Value", glm::dmat2x3(30.1, 30.2, 30.3, 30.4, 30.5, 30.6));
    d.setValue(
        "Dmat2x4Value",
        glm::dmat2x4(31.1, 31.2, 31.3, 31.4, 31.5, 31.6, 31.7, 31.8)
    );
    d.setValue("Dmat3x2Value", glm::dmat3x2(32.1, 32.2, 32.3, 32.4, 32.5, 32.6));
    d.setValue(
        "Dmat3x3Value",
        glm::dmat3x3(33.1, 33.2, 33.3, 33.4, 33.5, 33.6, 33.7, 33.8, 33.9)
    );
    d.setValue(
        "Dmat3x4Value",
        glm::dmat3x4(
            34.1, 34.2, 34.3, 34.4, 34.5, 34.6, 34.7, 34.8, 34.9, 34.10, 34.11, 34.12
        )
    );
    d.setValue(
        "Dmat4x2Value",
        glm::dmat4x2(35.1, 35.2, 35.3, 35.4, 35.5, 35.6, 35.7, 35.8)
    );
    d.setValue(
        "Dmat4x3Value",
        glm::dmat4x3(
            36.1, 36.2, 36.3, 36.4, 36.5, 36.6, 36.7, 36.8, 36.9, 36.10, 36.11, 36.12
        )
    );
    d.setValue(
        "Dmat4x4Value",
        glm::dmat4x4(
            37.1, 37.2, 37.3, 37.4, 37.5, 37.6, 37.7, 37.8,
            3.9, 37.10, 37.11, 37.12, 37.13, 37.14, 37.15, 37.16
        )
    );

    const Parameters p = codegen::bake<Parameters>(d);
    REQUIRE(p.boolValue.has_value());
    REQUIRE(*p.boolValue == true);
    REQUIRE(p.intValue.has_value());
    REQUIRE(*p.intValue == 2);
    REQUIRE(p.doubleValue.has_value());
    REQUIRE(*p.doubleValue == 3.1);
    REQUIRE(p.floatValue.has_value());
    REQUIRE(*p.floatValue == 4.1f);
    REQUIRE(p.stringValue.has_value());
    REQUIRE(*p.stringValue == "abc");
    REQUIRE(p.ivec2Value.has_value());
    REQUIRE(*p.ivec2Value == glm::ivec2(5, 6));
    REQUIRE(p.ivec3Value.has_value());
    REQUIRE(*p.ivec3Value == glm::ivec3(7, 8, 9));
    REQUIRE(p.ivec4Value.has_value());
    REQUIRE(*p.ivec4Value == glm::ivec4(10, 11, 12, 13));
    REQUIRE(p.dvec2Value.has_value());
    REQUIRE(*p.dvec2Value == glm::dvec2(14.1, 14.2));
    REQUIRE(p.dvec3Value.has_value());
    REQUIRE(*p.dvec3Value == glm::dvec3(15.1, 15.2, 15.3));
    REQUIRE(p.dvec4Value.has_value());
    REQUIRE(*p.dvec4Value == glm::dvec4(16.1, 16.2, 16.3, 16.4));
    REQUIRE(p.vec2Value.has_value());
    REQUIRE(*p.vec2Value == glm::vec2(17.1f, 17.2f));
    REQUIRE(p.vec3Value.has_value());
    REQUIRE(*p.vec3Value == glm::vec3(18.1f, 18.2f, 18.3f));
    REQUIRE(p.vec4Value.has_value());
    REQUIRE(*p.vec4Value == glm::vec4(19.1f, 19.2f, 19.3, 19.4f));
    REQUIRE(p.mat2x2Value.has_value());
    REQUIRE(
        *p.mat2x2Value == glm::mat2x2(20.1f, 20.2f, 20.3f, 20.4f)
    );
    REQUIRE(p.mat2x3Value.has_value());
    REQUIRE((
         &&
        *p.mat2x3Value == glm::mat2x3(21.1f, 21.2f, 21.3f, 21.4f, 21.5f, 21.6f)
    ));
    REQUIRE(p.mat2x4Value.has_value());
    REQUIRE(
        *p.mat2x4Value ==
        glm::mat2x4(22.1f, 22.2f, 22.3f, 22.4f, 22.5f, 22.6f, 22.7f, 22.8f)
    );
    REQUIRE(p.mat3x2Value.has_value());
    REQUIRE(
        *p.mat3x2Value == glm::mat3x2(23.1f, 23.2f, 23.3f, 23.4f, 23.5f, 23.6f)
    );
    REQUIRE(p.mat3x3Value.has_value());
    REQUIRE(
        *p.mat3x3Value ==
        glm::mat3x3(24.1f, 24.2f, 24.3f, 24.4f, 24.5f, 24.6f, 24.7f, 24.8f, 24.9f)
    );
    REQUIRE(p.mat3x4Value.has_value());
    REQUIRE(
        *p.mat3x4Value ==
        glm::mat3x4(
            25.1f, 25.2f, 25.3f, 25.4f, 25.5f, 25.6f,
            25.7f, 25.8f, 25.9f, 25.10f, 25.11f, 25.12f
        )
    );
    REQUIRE(p.mat4x2Value.has_value());
    REQUIRE(
        *p.mat4x2Value ==
        glm::mat4x2(26.1f, 26.2f, 26.3f, 26.4f, 26.5f, 26.6f, 26.7f, 26.8f)
    );
    REQUIRE(p.mat4x3Value.has_value());
    REQUIRE(
        *p.mat4x3Value ==
        glm::mat4x3(
            27.1f, 27.2f, 27.3f, 27.4f, 27.5f, 27.6f,
            27.7f, 27.8f, 27.9f, 27.10f, 27.11f, 27.12f
        )
    );
    REQUIRE(p.mat4x4Value.has_value());
    REQUIRE(
        *p.mat4x4Value ==
        glm::mat4x4(
            28.1f, 28.2f, 28.3f, 28.4f, 28.5f, 28.6f, 28.7f, 28.8f,
            28.9f, 28.10f, 28.11f, 28.12f, 28.13f, 28.14f, 28.15f, 28.16f
        )
    );
    REQUIRE(p.dmat2x2Value.has_value());
    REQUIRE(
        *p.dmat2x2Value == glm::dmat2x2(29.1, 29.2, 29.3, 29.4)
    );
    REQUIRE(p.dmat2x3Value.has_value());
    REQUIRE(
        *p.dmat2x3Value == glm::dmat2x3(30.1, 30.2, 30.3, 30.4, 30.5, 30.6)
    );
    REQUIRE(p.dmat2x4Value.has_value());
    REQUIRE(
        *p.dmat2x4Value ==
        glm::dmat2x4(31.1, 31.2, 31.3, 31.4, 31.5, 31.6, 31.7, 31.8)
    );
    REQUIRE(p.dmat3x2Value.has_value());
    REQUIRE(
        *p.dmat3x2Value == glm::dmat3x2(32.1, 32.2, 32.3, 32.4, 32.5, 32.6)
    );
    REQUIRE(p.dmat3x3Value.has_value());
    REQUIRE(
        *p.dmat3x3Value ==
        glm::dmat3x3(33.1, 33.2, 33.3, 33.4, 33.5, 33.6, 33.7, 33.8, 33.9)
    );
    REQUIRE(p.dmat3x4Value.has_value());
    REQUIRE(
        *p.dmat3x4Value ==
        glm::dmat3x4(
            34.1, 34.2, 34.3, 34.4, 34.5, 34.6, 34.7, 34.8, 34.9, 34.10, 34.11, 34.12
        )
    );
    REQUIRE(p.dmat4x2Value.has_value());
    REQUIRE(
        *p.dmat4x2Value ==
        glm::dmat4x2(35.1, 35.2, 35.3, 35.4, 35.5, 35.6, 35.7, 35.8)
    );
    REQUIRE(p.dmat4x3Value.has_value());
    REQUIRE(
        *p.dmat4x3Value ==
        glm::dmat4x3(
            36.1, 36.2, 36.3, 36.4, 36.5, 36.6, 36.7, 36.8, 36.9, 36.10, 36.11, 36.12
        )
    );
    REQUIRE(p.dmat4x4Value.has_value());
    REQUIRE(
        *p.dmat4x4Value ==
        glm::dmat4x4(
            37.1, 37.2, 37.3, 37.4, 37.5, 37.6, 37.7, 37.8,
            3.9, 37.10, 37.11, 37.12, 37.13, 37.14, 37.15, 37.16
        )
    );

    ghoul::Dictionary e;
    const Parameters p2 = codegen::bake<Parameters>(e);
    REQUIRE(!p2.boolValue.has_value());
    REQUIRE(!p2.intValue.has_value());
    REQUIRE(!p2.doubleValue.has_value());
    REQUIRE(!p2.floatValue.has_value());
    REQUIRE(!p2.stringValue.has_value());
    REQUIRE(!p2.ivec2Value.has_value());
    REQUIRE(!p2.ivec3Value.has_value());
    REQUIRE(!p2.ivec4Value.has_value());
    REQUIRE(!p2.dvec2Value.has_value());
    REQUIRE(!p2.dvec3Value.has_value());
    REQUIRE(!p2.dvec4Value.has_value());
    REQUIRE(!p2.vec2Value.has_value());
    REQUIRE(!p2.vec3Value.has_value());
    REQUIRE(!p2.vec4Value.has_value());
    REQUIRE(!p2.mat2x2Value.has_value());
    REQUIRE(!p2.mat2x3Value.has_value());
    REQUIRE(!p2.mat2x4Value.has_value());
    REQUIRE(!p2.mat3x2Value.has_value());
    REQUIRE(!p2.mat3x3Value.has_value());
    REQUIRE(!p2.mat3x4Value.has_value());
    REQUIRE(!p2.mat4x2Value.has_value());
    REQUIRE(!p2.mat4x3Value.has_value());
    REQUIRE(!p2.mat4x4Value.has_value());
    REQUIRE(!p2.dmat2x2Value.has_value());
    REQUIRE(!p2.dmat2x3Value.has_value());
    REQUIRE(!p2.dmat2x4Value.has_value());
    REQUIRE(!p2.dmat3x2Value.has_value());
    REQUIRE(!p2.dmat3x3Value.has_value());
    REQUIRE(!p2.dmat3x4Value.has_value());
    REQUIRE(!p2.dmat4x2Value.has_value());
    REQUIRE(!p2.dmat4x3Value.has_value());
    REQUIRE(!p2.dmat4x4Value.has_value());
}

TEST_CASE("Basic Types Optional documentation", "[verifier]") {
    using namespace openspace::documentation;
    Documentation doc = codegen::doc<openspace::BasicTypesOptional>();

    REQUIRE(doc.entries.size() == 32);
    {
        DocumentationEntry e = doc.entries[0];
        REQUIRE(e.key == "BoolValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "bool value documentation");
        REQUIRE(e.verifier->type() == "Boolean");
        REQUIRE(dynamic_cast<BoolVerifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[1];
        REQUIRE(e.key == "IntValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "int value documentation");
        REQUIRE(e.verifier->type() == "Integer");
        REQUIRE(dynamic_cast<IntVerifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[2];
        REQUIRE(e.key == "DoubleValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "double value documentation");
        REQUIRE(e.verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[3];
        REQUIRE(e.key == "FloatValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "float value documentation");
        REQUIRE(e.verifier->type() == "Double");
        REQUIRE(dynamic_cast<DoubleVerifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[4];
        REQUIRE(e.key == "StringValue");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "string value documentation");
        REQUIRE(e.verifier->type() == "String");
        REQUIRE(dynamic_cast<StringVerifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[5];
        REQUIRE(e.key == "Ivec2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "ivec2 value documentation");
        REQUIRE(e.verifier->type() == "Vector2<int>");
        REQUIRE(dynamic_cast<IntVector2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[6];
        REQUIRE(e.key == "Ivec3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "ivec3 value documentation");
        REQUIRE(e.verifier->type() == "Vector3<int>");
        REQUIRE(dynamic_cast<IntVector3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[7];
        REQUIRE(e.key == "Ivec4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "ivec4 value documentation");
        REQUIRE(e.verifier->type() == "Vector4<int>");
        REQUIRE(dynamic_cast<IntVector4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[8];
        REQUIRE(e.key == "Dvec2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dvec2 value documentation");
        REQUIRE(e.verifier->type() == "Vector2<double>");
        REQUIRE(dynamic_cast<DoubleVector2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[9];
        REQUIRE(e.key == "Dvec3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dvec3 value documentation");
        REQUIRE(e.verifier->type() == "Vector3<double>");
        REQUIRE(dynamic_cast<DoubleVector3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[10];
        REQUIRE(e.key == "Dvec4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dvec4 value documentation");
        REQUIRE(e.verifier->type() == "Vector4<double>");
        REQUIRE(dynamic_cast<DoubleVector4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[11];
        REQUIRE(e.key == "Vec2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "vec2 value documentation");
        REQUIRE(e.verifier->type() == "Vector2<double>");
        REQUIRE(dynamic_cast<DoubleVector2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[12];
        REQUIRE(e.key == "Vec3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "vec3 value documentation");
        REQUIRE(e.verifier->type() == "Vector3<double>");
        REQUIRE(dynamic_cast<DoubleVector3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[13];
        REQUIRE(e.key == "Vec4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "vec4 value documentation");
        REQUIRE(e.verifier->type() == "Vector4<double>");
        REQUIRE(dynamic_cast<DoubleVector4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[14];
        REQUIRE(e.key == "Mat2x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat2x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[15];
        REQUIRE(e.key == "Mat2x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat2x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[16];
        REQUIRE(e.key == "Mat2x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat2x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[17];
        REQUIRE(e.key == "Mat3x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat3x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[18];
        REQUIRE(e.key == "Mat3x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat3x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[19];
        REQUIRE(e.key == "Mat3x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat3x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[20];
        REQUIRE(e.key == "Mat4x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat4x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[21];
        REQUIRE(e.key == "Mat4x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat4x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[22];
        REQUIRE(e.key == "Mat4x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "mat4x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[23];
        REQUIRE(e.key == "Dmat2x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat2x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[24];
        REQUIRE(e.key == "Dmat2x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat2x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[25];
        REQUIRE(e.key == "Dmat2x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat2x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix2x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix2x4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[26];
        REQUIRE(e.key == "Dmat3x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat3x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[27];
        REQUIRE(e.key == "Dmat3x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat3x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[28];
        REQUIRE(e.key == "Dmat3x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat3x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix3x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix3x4Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[29];
        REQUIRE(e.key == "Dmat4x2Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat4x2 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x2<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x2Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[30];
        REQUIRE(e.key == "Dmat4x3Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat4x3 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x3<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x3Verifier*>(e.verifier.get()) != nullptr);
    }
    {
        DocumentationEntry e = doc.entries[31];
        REQUIRE(e.key == "Dmat4x4Value");
        REQUIRE(e.optional);
        REQUIRE(e.documentation == "dmat4x4 value documentation");
        REQUIRE(e.verifier->type() == "Matrix4x4<double>");
        REQUIRE(dynamic_cast<DoubleMatrix4x4Verifier*>(e.verifier.get()) != nullptr);
    }
}
