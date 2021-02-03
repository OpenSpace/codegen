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

#include "verifier.h"

#include "types.h"
#include <fmt/format.h>
#include <cassert>

namespace {
    void reportUnsupportedAttribute(BasicType::Type type,
                                    const Variable::Attributes& attributes)
    {
        auto report = [type](const std::string& attr, std::string_view name) {
            if (!attr.empty()) {
                std::string t = generateTypename(type);
                throw SpecificationError(fmt::format(
                    "Type '{}' does not support attribute '{}'", t, name
                ));
            }
        };

        using Type = BasicType::Type;
        if (type == Type::Bool ||
            type == Type::Ivec2 || type == Type::Ivec3 || type == Type::Ivec4 ||
            type == Type::Dvec2 || type == Type::Dvec3 || type == Type::Dvec4 ||
            type == Type::Vec2 || type == Type::Vec3 || type == Type::Vec4 ||
            type == Type::Mat2x2 || type == Type::Mat2x3 || type == Type::Mat2x4 ||
            type == Type::Mat3x2 || type == Type::Mat3x3 || type == Type::Mat3x4 ||
            type == Type::Mat4x2 || type == Type::Mat4x3 || type == Type::Mat4x4 ||
            type == Type::DMat2x2 || type == Type::DMat2x3 || type == Type::DMat2x4 ||
            type == Type::DMat3x2 || type == Type::DMat3x3 || type == Type::DMat3x4 ||
            type == Type::DMat4x2 || type == Type::DMat4x3 || type == Type::DMat4x4)
        {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.inrange, attributes::InRange);
            report(attributes.less, attributes::Less);
            report(attributes.lessequal, attributes::LessEqual);
            report(attributes.greater, attributes::Greater);
            report(attributes.greaterequal, attributes::GreaterEqual);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.notinrange, attributes::NotInRange);
            report(attributes.reference, attributes::Reference);
            report(attributes.unequal, attributes::Unequal);
        }
        else if (type == Type::Int || type == Type::Double || type == Type::Float) {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.reference, attributes::Reference);
        }
        else if (type == Type::String) {
            report(attributes.inrange, attributes::InRange);
            report(attributes.less, attributes::Less);
            report(attributes.lessequal, attributes::LessEqual);
            report(attributes.greater, attributes::Greater);
            report(attributes.greaterequal, attributes::GreaterEqual);
            report(attributes.notinrange, attributes::NotInRange);
            report(attributes.reference, attributes::Reference);
        }
        else if (type == Type::Monostate) {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.inrange, attributes::InRange);
            report(attributes.less, attributes::Less);
            report(attributes.lessequal, attributes::LessEqual);
            report(attributes.greater, attributes::Greater);
            report(attributes.greaterequal, attributes::GreaterEqual);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.notinrange, attributes::NotInRange);
            report(attributes.unequal, attributes::Unequal);
        }
    }


    std::string addQualifier(std::string ver, std::string qual, std::string_view param) {
        assert(!ver.empty());
        assert(!qual.empty());
        return fmt::format("{}<{}>({})", std::move(qual), std::move(ver), param);
    }
} // namespace

std::string verifierForType(BasicType::Type type, const Variable::Attributes& attributes,
                            std::string_view dictionaryName)
{
    using Type = BasicType::Type;

    reportUnsupportedAttribute(type, attributes);
    if (type == Type::Bool) { return "BoolVerifier"; }
    else if (type == Type::Int) {
        std::string res = "IntVerifier";
        if (!attributes.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attributes.inrange);
        }
        if (!attributes.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attributes.notinrange);
        }
        if (!attributes.less.empty()) {
            res = addQualifier(res, "LessVerifier", attributes.less);
        }
        if (!attributes.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attributes.lessequal);
        }
        if (!attributes.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attributes.greater);
        }
        if (!attributes.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attributes.greaterequal);
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attributes.unequal);
        }
        return res;
    }
    else if (type == Type::Double || type == Type::Float) {
        std::string res = "DoubleVerifier";
        if (!attributes.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attributes.inrange);
        }
        if (!attributes.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attributes.notinrange);
        }
        if (!attributes.less.empty()) {
            res = addQualifier(res, "LessVerifier", attributes.less);
        }
        if (!attributes.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attributes.lessequal);
        }
        if (!attributes.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attributes.greater);
        }
        if (!attributes.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attributes.greaterequal);
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attributes.unequal);
        }
        return res;
    }
    else if (type == Type::String) {
        std::string res = "StringVerifier";
        if (!attributes.inlist.empty()) {
            std::string param = '{' + std::string(attributes.inlist) + '}';
            res = addQualifier(res, "InListVerifier", param);
        }
        if (!attributes.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attributes.unequal);
        }
        if (!attributes.annotation.empty()) {
            if (!attributes.inlist.empty() || !attributes.unequal.empty()) {
                throw SpecificationError(fmt::format(
                    "With the annotation attribute, no other attribute can be used:\n{}",
                    type
                ));
            }
            res = addQualifier(res, "AnnotationVerifier", attributes.annotation);
        }
        return res;
    }
    else if (type == Type::Ivec2) { return "IntVector2Verifier"; }
    else if (type == Type::Ivec3) { return "IntVector3Verifier"; }
    else if (type == Type::Ivec4) { return "IntVector4Verifier"; }
    else if (type == Type::Dvec2) { return "DoubleVector2Verifier"; }
    else if (type == Type::Dvec3) { return "DoubleVector3Verifier"; }
    else if (type == Type::Dvec4) { return "DoubleVector4Verifier"; }
    else if (type == Type::Vec2) { return "DoubleVector2Verifier"; }
    else if (type == Type::Vec3) { return "DoubleVector3Verifier"; }
    else if (type == Type::Vec4) { return "DoubleVector4Verifier"; }
    else if (type == Type::DMat2x2) { return "DoubleMatrix2x2Verifier"; }
    else if (type == Type::DMat2x3) { return "DoubleMatrix2x3Verifier"; }
    else if (type == Type::DMat2x4) { return "DoubleMatrix2x4Verifier"; }
    else if (type == Type::DMat3x2) { return "DoubleMatrix3x2Verifier"; }
    else if (type == Type::DMat3x3) { return "DoubleMatrix3x3Verifier"; }
    else if (type == Type::DMat3x4) { return "DoubleMatrix3x4Verifier"; }
    else if (type == Type::DMat4x2) { return "DoubleMatrix4x2Verifier"; }
    else if (type == Type::DMat4x3) { return "DoubleMatrix4x3Verifier"; }
    else if (type == Type::DMat4x4) { return "DoubleMatrix4x4Verifier"; }
    else if (type == Type::Mat2x2) { return "DoubleMatrix2x2Verifier"; }
    else if (type == Type::Mat2x3) { return "DoubleMatrix2x3Verifier"; }
    else if (type == Type::Mat2x4) { return "DoubleMatrix2x4Verifier"; }
    else if (type == Type::Mat3x2) { return "DoubleMatrix3x2Verifier"; }
    else if (type == Type::Mat3x3) { return "DoubleMatrix3x3Verifier"; }
    else if (type == Type::Mat3x4) { return "DoubleMatrix3x4Verifier"; }
    else if (type == Type::Mat4x2) { return "DoubleMatrix4x2Verifier"; }
    else if (type == Type::Mat4x3) { return "DoubleMatrix4x3Verifier"; }
    else if (type == Type::Mat4x4) { return "DoubleMatrix4x4Verifier"; }
    else if (type == Type::Monostate) {
        if (attributes.reference.empty()) {
            throw SpecificationError("A monostate must have a 'reference' attribute");
        }

        std::string r = attributes.reference == "this" ?
            fmt::format(R"("{}")", dictionaryName) :
            std::string(attributes.reference);
        return fmt::format("ReferencingVerifier({})", r);
    }
    else {
        return std::string();
    }
}
