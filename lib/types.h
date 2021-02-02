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

#ifndef __OPENSPACE_CODEGEN___TYPES___H__
#define __OPENSPACE_CODEGEN___TYPES___H__

#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

struct ParsingError : public std::runtime_error {
    ParsingError(std::string e) : std::runtime_error(e) {}

    // We don't really need this operator, but catch2 wants it for a string matcher -.-
    operator std::string() const noexcept { return what(); }
};

struct SpecificationError : public std::runtime_error {
    SpecificationError(std::string e) : std::runtime_error(e) {}

    // We don't really need this operator, but catch2 wants it for a string matcher -.-
    operator std::string() const noexcept { return what(); }
};

struct CodegenError : public std::runtime_error {
    CodegenError(std::string e) : std::runtime_error(e) {}

    // We don't really need this operator, but catch2 wants it for a string matcher -.-
    operator std::string() const noexcept { return what(); }
};


struct Struct;

struct StackElement {
    enum class Type { Struct, Enum };
    Type type;

    std::string name;
    std::string comment;
    Struct* parent = nullptr;
};

namespace attributes {
    constexpr const char Annotation[] = "annotation";
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

} // namespace attributes

struct Variable {
    std::string type;
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
    std::string sourceFile;
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

    std::vector<EnumElement*> elements;
};


const Struct* rootStruct(const Struct* s);
const StackElement* resolveType(const Struct* context, std::string_view type);
std::string fqn(const StackElement* s, std::string_view separator);

#endif // __OPENSPACE_CODEGEN___TYPES___H__
