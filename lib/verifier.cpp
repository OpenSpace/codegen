/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2023                                                               *
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

#include <fmt/format.h>
#include <cassert>

namespace {
    void reportUnsupportedAttribute(BasicType::Type type,
                                    const Variable::Attributes& attributes)
    {
        auto report = [type](std::string_view attr, std::string_view name) {
            if (!attr.empty()) {
                std::string t = generateTypename(type);
                throw CodegenError(fmt::format(
                    "Type '{}' does not support attribute '{}'", t, name
                ));
            }
        };
        auto reportBool = [type](bool attr, std::string_view name) {
            if (attr) {
                std::string t = generateTypename(type);
                throw CodegenError(fmt::format(
                    "Type '{}' does not support attribute '{}'", t, name
                ));
            }
        };

        using Type = BasicType::Type;
        if (type == Type::Bool ||
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
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDirectory, attributes::Directory);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
        else if (
            type == Type::Ivec2 || type == Type::Ivec3 || type == Type::Ivec4 ||
            type == Type::Dvec2 || type == Type::Vec2)
        {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.reference, attributes::Reference);
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDirectory, attributes::Directory);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
        else if (
            type == Type::Dvec3 || type == Type::Dvec4 ||
            type == Type::Vec3 || type == Type::Vec4)
        {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.reference, attributes::Reference);
            reportBool(attributes.isDirectory, attributes::Directory);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
        else if (type == Type::Int || type == Type::Double || type == Type::Float) {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.reference, attributes::Reference);
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDirectory, attributes::Directory);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
        else if (type == Type::String) {
            report(attributes.inrange, attributes::InRange);
            report(attributes.less, attributes::Less);
            report(attributes.lessequal, attributes::LessEqual);
            report(attributes.greater, attributes::Greater);
            report(attributes.greaterequal, attributes::GreaterEqual);
            report(attributes.notinrange, attributes::NotInRange);
            report(attributes.reference, attributes::Reference);
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDirectory, attributes::Directory);
        }
        else if (type == Type::Path) {
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
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
        else if (type == Type::Dictionary) {
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
            reportBool(attributes.isColor, attributes::Color);
            reportBool(attributes.isDirectory, attributes::Directory);
            reportBool(attributes.isDateTime, attributes::DateTime);
            reportBool(attributes.isIdentifier, attributes::Identifier);
            reportBool(attributes.mustBeNotEmpty, attributes::Directory);
        }
    }

    std::string addQualifier(std::string ver, std::string qual, std::string_view param) {
        assert(!ver.empty());
        assert(!qual.empty());
        return fmt::format("{}<{}>({})", std::move(qual), std::move(ver), param);
    }
} // namespace

std::string verifierForType(BasicType::Type type, const Variable::Attributes& attr) {
    using Type = BasicType::Type;

    // @TODO (abock, 2021-02-12) Really the check for unsupported attributes should be
    // done directly after parsing and not when we are trying to generate the verifiers
    reportUnsupportedAttribute(type, attr);
    if (type == Type::Bool) { return "BoolVerifier"; }
    else if (type == Type::Int) {
        std::string res = "IntVerifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Double || type == Type::Float) {
        std::string res = "DoubleVerifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::String) {
        std::string res = "StringVerifier";
        if (!attr.inlist.empty()) {
            std::string param = '{' + std::string(attr.inlist) + '}';
            res = addQualifier(res, "InListVerifier", param);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        if (attr.mustBeNotEmpty) {
            if (!attr.inlist.empty() || !attr.unequal.empty() ||
                !attr.annotation.empty())
            {
                throw CodegenError(fmt::format(
                    "With the notempty attribute, no other attribute can be used:\n{}",
                    generateTypename(type)
                ));
            }

            res = "StringVerifier(true)";
        }
        if (!attr.annotation.empty()) {
            if (!attr.inlist.empty() || !attr.unequal.empty() || attr.mustBeNotEmpty) {
                throw CodegenError(fmt::format(
                    "With the annotation attribute, no other attribute can be used:\n{}",
                    generateTypename(type)
                ));
            }
            res = addQualifier(res, "AnnotationVerifier", attr.annotation);
        }
        if (attr.isDateTime) {
            return "DateTimeVerifier";
        }
        if (attr.isIdentifier) {
            return "IdentifierVerifier";
        }
        return res;
    }
    else if (type == Type::Path)  {
        if (attr.isDirectory) {
            return "DirectoryVerifier";
        }
        else {
            return "FileVerifier";
        }
    }
    else if (type == Type::Ivec2) {
        std::string res = "IntVector2Verifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Ivec3) {
        std::string res = "IntVector3Verifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Ivec4) { 
        std::string res = "IntVector4Verifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Dvec2 || type == Type::Vec2) {
        std::string res = "DoubleVector2Verifier";
        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Dvec3 || type == Type::Vec3) {
        std::string res;
        if (attr.isColor) {
            res ="Color3Verifier";
        }
        else {
            res = "DoubleVector3Verifier";
        }

        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
    else if (type == Type::Dvec4 || type == Type::Vec4) {
        std::string res;
        if (attr.isColor) {
            res = "Color4Verifier";
        }
        else {
            res = "DoubleVector4Verifier";
        }

        if (!attr.inrange.empty()) {
            res = addQualifier(res, "InRangeVerifier", attr.inrange);
        }
        if (!attr.notinrange.empty()) {
            res = addQualifier(res, "NotInRangeVerifier", attr.notinrange);
        }
        if (!attr.less.empty()) {
            res = addQualifier(res, "LessVerifier", attr.less);
        }
        if (!attr.lessequal.empty()) {
            res = addQualifier(res, "LessEqualVerifier", attr.lessequal);
        }
        if (!attr.greater.empty()) {
            res = addQualifier(res, "GreaterVerifier", attr.greater);
        }
        if (!attr.greaterequal.empty()) {
            res = addQualifier(res, "GreaterEqualVerifier", attr.greaterequal);
        }
        if (!attr.unequal.empty()) {
            res = addQualifier(res, "UnequalVerifier", attr.unequal);
        }
        return res;
    }
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
    else if (type == Type::Dictionary) {
        if (attr.reference.empty()) {
            return "TableVerifier";
        }
        else {
            return fmt::format("ReferencingVerifier({})", attr.reference);
        }
    }

    throw std::logic_error("Missing case label");
}
