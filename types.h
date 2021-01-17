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

    std::string_view name;
    Struct* parent = nullptr;
};


struct Variable {
    std::string_view type;
    std::string_view name;
    std::string key;

    std::string comment;

    using Attributes = std::unordered_map<std::string_view, std::string_view>;
    Attributes attributes;
};


struct Struct : public StackElement {
    Struct() { type = StackElement::Type::Struct; }

    std::vector<Variable> variables;

    struct Attributes {
        std::string_view dictionary;
        std::string_view namespaceSpecifier;
        bool noTypeCheck = true;
        bool noExhaustive = true;
    };
    Attributes attributes;

    std::vector<StackElement*> children;
};

Struct* rootStruct(Struct* s);
const StackElement* resolveType(const Struct* context, std::string_view type);
std::string fqn(const StackElement* s, std::string_view separator);


struct EnumElement {
    std::string_view name;

    struct Attributes {
        std::string_view key;
    };
    Attributes attributes;
};

struct Enum : public StackElement {
    Enum() { type = StackElement::Type::Enum; }

    std::vector<EnumElement> elements;
};



struct State {
    std::map<std::string, std::string, std::less<>> structComments;
    std::map<std::string, std::string, std::less<>> structConverters;
    //std::map<std::string, std::vector<std::string>, std::less<>> structVariables;

    std::map<std::string, bool, std::less<>> typeUsage;
};

#endif // __OPENSPACE_CODEGEN___TYPES___H__
