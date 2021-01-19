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

#include <string_view>
#include <map>
#include <unordered_map>
#include <variant>

struct Struct;

struct StackElement {
    enum class Type { Struct, Enum };
    Type type;

    std::string name;
    std::string comment;
    Struct* parent = nullptr;
};


struct Variable {
    std::string type;
    std::string name;
    std::string key;

    std::string comment;

    struct Attributes {
        std::string key;
        std::string reference;
        std::string inrange;
        std::string notinrange;
        std::string less;
        std::string lessequal;
        std::string greater;
        std::string greaterequal;
        std::string unequal;
        std::string inlist;
        std::string notinlist;
        std::string annotation;
    };
    Attributes attributes;
};


struct Struct : public StackElement {
    Struct() { type = StackElement::Type::Struct; }

    std::vector<StackElement*> children;
    std::vector<Variable*> variables;

    struct Attributes {
        std::string dictionary;
        std::string namespaceSpecifier;
        bool noExhaustive = true; // @TODO change to false once OpenSpace works with it
    };
    Attributes attributes;
};

const Struct* rootStruct(const Struct* s);
const StackElement* resolveType(const Struct* context, std::string_view type);
std::string fqn(const StackElement* s, std::string_view separator);


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

#endif // __OPENSPACE_CODEGEN___TYPES___H__
