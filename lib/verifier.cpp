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
    void reportUnsupportedAttribute(std::string_view type,
                                    const Variable::Attributes& attributes)
    {
        assert(!type.empty());
     
        auto report = [type](const std::string& attr, std::string_view name) {
            if (!attr.empty()) {
                throw SpecificationError(fmt::format(
                    "Type '{}' does not support attribute '{}'", type, name
                ));
            }
        };

        if (type == "bool" ||
            type == "glm::ivec2" || type == "glm::ivec3" || type == "glm::ivec4" ||
            type == "glm::dvec2" || type == "glm::dvec3" || type == "glm::dvec4" ||
            type == "glm::vec2"  || type == "glm::vec3"  || type == "glm::vec4" ||
            type == "glm::mat2x2" || type == "glm::mat2x3" || type == "glm::mat2x4" ||
            type == "glm::mat3x2" || type == "glm::mat3x3" || type == "glm::mat3x4" ||
            type == "glm::mat4x2" || type == "glm::mat4x3" || type == "glm::mat4x4" ||
            type == "glm::dmat2x2" || type == "glm::dmat2x3" || type == "glm::dmat2x4" ||
            type == "glm::dmat3x2" || type == "glm::dmat3x3" || type == "glm::dmat3x4" ||
            type == "glm::dmat4x2" || type == "glm::dmat4x3" || type == "glm::dmat4x4")
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
        else if (type == "int" || type == "double" || type == "float") {
            report(attributes.annotation, attributes::Annotation);
            report(attributes.inlist, attributes::InList);
            report(attributes.notinlist, attributes::NotInList);
            report(attributes.reference, attributes::Reference);
        }
        else if (type == "std::string") {
            report(attributes.inrange, attributes::InRange);
            report(attributes.less, attributes::Less);
            report(attributes.lessequal, attributes::LessEqual);
            report(attributes.greater, attributes::Greater);
            report(attributes.greaterequal, attributes::GreaterEqual);
            report(attributes.notinrange, attributes::NotInRange);
            report(attributes.reference, attributes::Reference);
        }
        else if (type == "std::monostate") {
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

std::string verifierForType(std::string_view type, const Variable::Attributes& attributes, 
                            std::string_view dictionaryName)
{
    assert(!type.empty());

    reportUnsupportedAttribute(type, attributes);
    if (type == "bool") { return "BoolVerifier"; }
    else if (type == "int") {
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
    else if (type == "double" || type == "float") {
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
    else if (type == "std::string") {
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
    else if (type == "glm::ivec2") { return "IntVector2Verifier"; }
    else if (type == "glm::ivec3") { return "IntVector3Verifier"; }
    else if (type == "glm::ivec4") { return "IntVector4Verifier"; }
    else if (type == "glm::dvec2") { return "DoubleVector2Verifier"; }
    else if (type == "glm::dvec3") { return "DoubleVector3Verifier"; }
    else if (type == "glm::dvec4") { return "DoubleVector4Verifier"; }
    else if (type == "glm::vec2") { return "DoubleVector2Verifier"; }
    else if (type == "glm::vec3") { return "DoubleVector3Verifier"; }
    else if (type == "glm::vec4") { return "DoubleVector4Verifier"; }
    else if (type == "glm::dmat2x2") { return "DoubleMatrix2x2Verifier"; }
    else if (type == "glm::dmat2x3") { return "DoubleMatrix2x3Verifier"; }
    else if (type == "glm::dmat2x4") { return "DoubleMatrix2x4Verifier"; }
    else if (type == "glm::dmat3x2") { return "DoubleMatrix3x2Verifier"; }
    else if (type == "glm::dmat3x3") { return "DoubleMatrix3x3Verifier"; }
    else if (type == "glm::dmat3x4") { return "DoubleMatrix3x4Verifier"; }
    else if (type == "glm::dmat4x2") { return "DoubleMatrix4x2Verifier"; }
    else if (type == "glm::dmat4x3") { return "DoubleMatrix4x3Verifier"; }
    else if (type == "glm::dmat4x4") { return "DoubleMatrix4x4Verifier"; }
    else if (type == "glm::mat2x2") { return "DoubleMatrix2x2Verifier"; }
    else if (type == "glm::mat2x3") { return "DoubleMatrix2x3Verifier"; }
    else if (type == "glm::mat2x4") { return "DoubleMatrix2x4Verifier"; }
    else if (type == "glm::mat3x2") { return "DoubleMatrix3x2Verifier"; }
    else if (type == "glm::mat3x3") { return "DoubleMatrix3x3Verifier"; }
    else if (type == "glm::mat3x4") { return "DoubleMatrix3x4Verifier"; }
    else if (type == "glm::mat4x2") { return "DoubleMatrix4x2Verifier"; }
    else if (type == "glm::mat4x3") { return "DoubleMatrix4x3Verifier"; }
    else if (type == "glm::mat4x4") { return "DoubleMatrix4x4Verifier"; }
    else if (type == "std::monostate") {
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
