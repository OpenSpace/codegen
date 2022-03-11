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

#ifndef __OPENSPACE_CODEGEN___TYPES___H__
#define __OPENSPACE_CODEGEN___TYPES___H__

#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

// If this is defined, all types are declared with an empty virtual destructor, meaning
// that they will properly disambiguate in the Visual Studio Watch window, making the
// debugging of these types a bit easier.  No need to declare this define otherwise

#define TYPES_ADD_DEBUG_INFORMATION

struct CodegenError : public std::runtime_error {
    CodegenError(std::string e);

    // We don't really need this operator, but catch2 wants it for a string matcher -.-
    operator std::string() const noexcept;
};

namespace attributes {
    constexpr const char Annotation[] = "annotation";
    constexpr const char Color[] = "color";
    constexpr const char DateTime[] = "datetime";
    constexpr const char Directory[] = "directory";
    constexpr const char InList[] = "inlist";
    constexpr const char InRange[] = "inrange";
    constexpr const char Less[] = "less";
    constexpr const char LessEqual[] = "lessequal";
    constexpr const char Greater[] = "greater";
    constexpr const char GreaterEqual[] = "greaterequal";
    constexpr const char NotInList[] = "notinlist";
    constexpr const char NotInRange[] = "notinrange";
    constexpr const char Reference[] = "reference";
    constexpr const char Unequal[] = "unequal";

    constexpr const char Key[] = "key";

    constexpr const char Dictionary[] = "Dictionary";
    constexpr const char NoExhaustive[] = "noexhaustive";
    constexpr const char MustBeNotEmpty[] = "notempty";

    constexpr const char Map[] = "map";

} // namespace attributes


struct Struct;

struct StackElement {
#ifdef TYPES_ADD_DEBUG_INFORMATION
    virtual ~StackElement() = default;
#endif // TYPES_ADD_DEBUG_INFORMATION

    enum class Type { Struct, Enum };
    Type type;

    std::string name;
    std::string comment;
    Struct* parent = nullptr;
};

struct VariableType {
#ifdef TYPES_ADD_DEBUG_INFORMATION
    virtual ~VariableType() = default;
#endif // TYPES_ADD_DEBUG_INFORMATION

    enum class Tag {
        BasicType,
        MapType,
        OptionalType,
        VariantType,
        TupleType,
        VectorType,
        CustomType
    };

    Tag tag;
};
bool operator==(const VariableType& lhs, const VariableType& rhs);

VariableType* parseType(std::string_view type, Struct* s);
std::string generateTypename(const VariableType* type, bool fullyQualified = false);
std::string generateDescriptiveTypename(const VariableType* type);

struct BasicType : public VariableType {
    enum class Type {
        Bool,
        Int,
        Double,
        Float,
        String,
        Path,
        Ivec2, Ivec3, Ivec4,
        Dvec2, Dvec3, Dvec4,
        Vec2, Vec3, Vec4,
        Mat2x2, Mat2x3, Mat2x4,
        Mat3x2, Mat3x3, Mat3x4,
        Mat4x2, Mat4x3, Mat4x4,
        DMat2x2, DMat2x3, DMat2x4,
        DMat3x2, DMat3x3, DMat3x4,
        DMat4x2, DMat4x3, DMat4x4,
        Dictionary
    };
    Type type;
};
bool operator==(const BasicType& lhs, const BasicType& rhs);
std::string generateTypename(BasicType::Type type);

struct MapType : public VariableType {
    VariableType* keyType = nullptr;
    VariableType* valueType = nullptr;
};
bool operator==(const MapType& lhs, const MapType& rhs);

struct OptionalType : public VariableType {
    VariableType* type = nullptr;
    // If this is true, we generated this OptionalType because someone requested a default
    // initialized variable in a function definition
    std::optional<std::string> defaultArgument;
};
bool operator==(const OptionalType& lhs, const OptionalType& rhs);

struct VariantType : public VariableType {
    std::vector<VariableType*> types;
};
bool operator==(const VariantType& lhs, const VariantType& rhs);

struct TupleType : public VariableType {
    std::vector<VariableType*> types;
};
bool operator==(const TupleType& lhs, const TupleType& rhs);

struct VectorType : public VariableType {
    VariableType* type = nullptr;
};
bool operator==(const VectorType& lhs, const VectorType& rhs);

struct CustomType : public VariableType {
    std::string name;
    const StackElement* type = nullptr;
};
bool operator==(const CustomType& lhs, const CustomType& rhs);

struct Variable {
    VariableType* type = nullptr;
    std::string name;
    std::string key;

    std::string comment;

    struct Attributes {
        std::string annotation;
        std::string key;
        std::string inlist;
        std::string inrange;
        std::string less;
        std::string lessequal;
        std::string greater;
        std::string greaterequal;
        std::string notinlist;
        std::string notinrange;
        std::string reference;
        std::string unequal;

        bool isDirectory = false;
        bool isColor = false;
        bool isDateTime = false;
        bool mustBeNotEmpty = false;
    };
    Attributes attributes;
};


struct Struct : public StackElement {
    Struct() { type = StackElement::Type::Struct; }

    std::vector<StackElement*> children;
    std::vector<Variable*> variables;

    struct Attributes {
        std::string dictionary;
        bool noExhaustive = true; // @TODO change to false once OpenSpace works with it
    };
    Attributes attributes;
};

struct EnumElement {
    std::string name;

    struct Attributes {
        std::string key;
    };
    Attributes attributes;
};

struct Enum : public StackElement {
    Enum() { type = StackElement::Type::Enum; }

    std::string mappedTo; // another FQ enum that values of this should be mapped to
    std::vector<EnumElement*> elements;
};


const Struct* rootStruct(const Struct* s);
const StackElement* resolveType(const Struct* context, std::string_view type);
std::string fqn(const StackElement* s, std::string_view separator);

struct Function {
    std::string name;
    std::string customName;
    std::string documentation;

    VariableType* returnValue = nullptr;
    std::vector<Variable*> arguments;
};


struct Code {
    std::vector<Struct*> structs;
    std::vector<Enum*> enums;
    std::vector<Function*> luaWrapperFunctions;

    std::string sourceFile;
};

#endif // __OPENSPACE_CODEGEN___TYPES___H__
