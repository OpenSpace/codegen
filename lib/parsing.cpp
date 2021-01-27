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

#include "parsing.h"

#include "types.h"
#include "util.h"
#include <fmt/format.h>
#include <cassert>

bool hasAttribute(std::string_view block, std::string_view name) {
    assert(!block.empty());
    assert(!name.empty());

    std::string key = fmt::format("codegen::{}", name);
    const size_t p = block.find(key);
    if (p == std::string::npos) {
        return false;
    }

    size_t cursor = p + key.size();

    if (block[cursor] != '(') {
        // No parameter provided -> true
        return true;
    }
    cursor++;
    const size_t end = block.find(')', cursor);
    std::string_view param = block.substr(cursor, end - cursor);

    if (param == "true" || param.empty()) {
        return true;
    }
    if (param == "false") {
        return false;
    }
    throw ParsingError(fmt::format(
        "Unexpected boolean attribute parameter '{}'. Expected empty, true, or false",
        param
    ));
}

struct AttributeParsing {
    std::string_view key;
    std::string_view value;
};

std::vector<AttributeParsing> parseAttribute(std::string_view block) {
    assert(!block.empty());

    std::string_view key = "codegen::";
    const size_t p = block.find(key);
    if (p == std::string::npos) {
        return {};
    }
    const size_t beg = block.find('(', p) + 1;

    std::string_view name = block.substr(p + key.size(), beg - (p + key.size()) - 1);
    if (const size_t end = block.find(')', beg); end == std::string_view::npos) {
        throw ParsingError(fmt::format(
            "Attribute parameter has unterminated parameter list\n{}", block
        ));
    }

    size_t cursor = beg;
    int paranthesisCount = 1;
    while (cursor < block.size() && paranthesisCount > 0) {
        if (block[cursor] == '(') {
            paranthesisCount++;
        }
        if (block[cursor] == ')') {
            paranthesisCount--;
        }

        cursor++;
    }

    std::string_view content = block.substr(beg, cursor - beg - 1);
    std::vector<AttributeParsing> res;
    res.push_back({ name, content });

    // Skip over whitespaces
    while (cursor < block.size() && ::isspace(block[cursor])) {
        cursor++;
    }
    if (block[cursor] == ',') {
        std::vector<AttributeParsing> recRes = parseAttribute(block.substr(cursor));
        res.insert(res.end(), recRes.begin(), recRes.end());
    }
    else if (block[cursor] != ']') {
        throw ParsingError(fmt::format(
            "Parameter attribute was not terminated\n{}", block
        ));
    }

    return res;
}

std::string_view parseCommentLine(std::string_view line) {
    assert(line.size() >= 2);

    // Remove the starting // characters
    std::string_view comment = strip(line.substr(2));
    return comment;
}

Variable::Attributes parseAttributes(std::string_view line) {
    Variable::Attributes res;

    std::vector<AttributeParsing> a = parseAttribute(line);
    for (const AttributeParsing& p : a) {
        if (p.key == "key")  res.key = p.value;
        else if (p.key == "reference")  res.reference = p.value;
        else if (p.key == "inrange")  res.inrange = p.value;
        else if (p.key == "notinrange")  res.notinrange = p.value;
        else if (p.key == "less")  res.less = p.value;
        else if (p.key == "lessequal")  res.lessequal = p.value;
        else if (p.key == "greater")  res.greater = p.value;
        else if (p.key == "greaterequal")  res.greaterequal = p.value;
        else if (p.key == "unequal")  res.unequal = p.value;
        else if (p.key == "inlist")  res.inlist = p.value;
        else if (p.key == "notinlist")  res.notinlist = p.value;
        else if (p.key == "annotation")  res.annotation = p.value;
        else {
            throw SpecificationError(fmt::format(
                "Unknown attribute '{}' in attribute found\n{}", p.key, line
            ));
        }
    }

    return res;
}

Struct* parseStruct(std::string_view line) {
    assert(!line.empty());

    Struct* s = new Struct;

    size_t cursor = line.find(' ');
    assert(line.substr(0, cursor) == "struct");
    cursor++;

    if (const size_t beginAttr = line.find("[[", cursor);
        beginAttr != std::string_view::npos)
    {
        const size_t endAttr = line.find("]]", beginAttr) + 2;
        std::string_view block = line.substr(beginAttr, endAttr - beginAttr);
        std::vector<AttributeParsing> attrs = parseAttribute(block);
        for (const AttributeParsing& a : attrs) {
            if (a.key == "Dictionary")  s->attributes.dictionary = a.value;
            else if (a.key == "namespace")  s->attributes.namespaceSpecifier = a.value;
            else if (a.key == "noexhaustive") {
                s->attributes.noExhaustive = (a.value == "true" || a.value.empty());
            }
            else {
                throw SpecificationError(fmt::format(
                    "Unknown attribute '{}' in struct definition found\n{}", a.key, line
                ));
            }
        }
        if (s->attributes.dictionary.empty()) {
            throw SpecificationError(fmt::format(
                "No name specified for root struct\n{}", line
            ));
        }
        cursor = endAttr + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw ParsingError(fmt::format(
            "Missing space or struct name before the closing {{ of a struct\n{}", line
        ));
    }
    s->name = line.substr(cursor, endStruct - cursor);
    return s;
}

Enum* parseEnum(std::string_view line) {
    assert(!line.empty());

    Enum* e = new Enum;

    size_t cursor = line.find(' ', line.find(' ') + 1);
    assert(line.substr(0, cursor) == "enum class");
    cursor++;

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw ParsingError(fmt::format(
            "Missing space before the closing {{ of a struct\n{}", line
        ));
    }
    e->name = line.substr(cursor, endStruct - cursor);
    return e;
}

EnumElement* parseEnumElement(std::string_view line) {
    assert(!line.empty());

    EnumElement* e = new EnumElement;

    if (line.back() == ',') {
        line.remove_suffix(1);
    }

    const size_t i = line.find(' ');
    e->name = line.substr(0, i);
    if (i != std::string_view::npos) {
        std::string_view attributes = line.substr(i + 1);
        std::vector<AttributeParsing> attr = parseAttribute(attributes);
        for (const AttributeParsing& a : attr) {
            if (a.key == "key") {
                e->attributes.key = a.value;
                continue;
            }

            throw SpecificationError(fmt::format(
                "Unrecognized attribute '{}' found when parsing enum value\n{}",
                a.key, line
            ));
        }
    }
    return e;
}

Variable* parseVariable(std::string_view line) {
    assert(!line.empty());

    // Remove the trailing ;
    line.remove_suffix(1);

    if (line.find(' ') == std::string_view::npos) {
        throw ParsingError(fmt::format(
            "Variable definition does not contain any empty character\n{}", line
        ));
    }

    // Find the end of the variable definition, ignoring spaces in template parameter
    // arguments
    size_t cursor = 0;
    int nBrackets = 0;
    while (cursor < line.size()) {
        if (line[cursor] == '<') {
            nBrackets++;
        }
        if (line[cursor] == '>') {
            nBrackets--;
        }

        if (line[cursor] == ' ' && nBrackets == 0) {
            break;
        }

        cursor++;
    }

    if (nBrackets != 0) {
        throw ParsingError(fmt::format("Unbalanced number of < > brackets\n{}", line));
    }

    const size_t p1 = cursor;
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        throw ParsingError(fmt::format(
            "Too few spaces in variable definition\n{}", line
        ));
    }

    Variable* res = new Variable;

    res->type = line.substr(0, p1);
    res->name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        res->attributes = parseAttributes(attributes);
    }

    std::string variableName;
    if (!res->attributes.key.empty()) {
        res->key = std::string(res->attributes.key);
    }
    else {
        res->key = std::string(res->name);
        res->key[0] = static_cast<char>(::toupper(res->name[0]));
    }

    return res;
}

Struct* parseRootStruct(std::string_view code) {
    for (char c : code) {
        if (c < 0) {
            throw ParsingError(fmt::format("Illegal character '{}' detected", c));
        }
    }

    std::string_view content = strip(validCode(code));
    if (content.empty()) {
        return nullptr;
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        constexpr const int ErrorContext = 50;
        throw ParsingError(fmt::format(
            "Block comments are not allowed\n{}", content.substr(p, ErrorContext)
        ));
    }


    Struct* rootStruct = nullptr;
    std::vector<StackElement*> stack;

    std::string structBuffer;
    std::string variableBuffer;
    std::string commentBuffer;

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (strip(line).empty()) {
            continue;
        }

        // If the variable buffer is filled, then we are in a continuation of a variable
        // definition
        if (variableBuffer.empty()) {
            if (startsWith(line, "//")) {
                std::string_view comment = parseCommentLine(line);
                commentBuffer.append(comment);
                commentBuffer.append(" ");
                continue;
            }

            if (startsWith(line, "struct") || !structBuffer.empty()) {
                structBuffer += line;
                structBuffer += " ";
                // Check if we have a continuation going on
                if (strip(line).back() != '{')  continue;

                if (!stack.empty() &&
                    stack.back()->type != StackElement::Type::Struct)
                {
                    throw ParsingError(fmt::format(
                        "Struct definition found outside a parent struct\n{}",
                        structBuffer
                    ));
                }

                Struct* s = parseStruct(structBuffer);
                if (!stack.empty()) {
                    assert(stack.back()->type == StackElement::Type::Struct);
                    s->parent = static_cast<Struct*>(stack.back());
                    s->parent->children.push_back(s);
                }

                stack.push_back(s);
                if (!commentBuffer.empty() && commentBuffer.back() == ' ') {
                    commentBuffer.pop_back();
                }
                s->comment = commentBuffer;
                commentBuffer.clear();

                if (!s->attributes.dictionary.empty()) {
                    assert(rootStruct == nullptr);
                    rootStruct = s;
                }
                structBuffer.clear();
                continue;
            }

            if (startsWith(line, "enum class")) {
                Enum* e = parseEnum(line);
                Struct* parent = static_cast<Struct*>(stack.back());
                assert(parent->type == StackElement::Type::Struct);
                parent->children.push_back(e);
                e->parent = parent;
                stack.push_back(e);
                if (!commentBuffer.empty() && commentBuffer.back() == ' ') {
                    commentBuffer.pop_back();
                }
                e->comment = commentBuffer;
                commentBuffer.clear();
                continue;
            }

            if (startsWith(line, "enum")) {
                throw ParsingError(
                    "Old-style 'enum' not supported. Use 'enum class' instead"
                );
            }

            if (startsWith(line, "};")) {
                stack.pop_back();
                continue;
            }
        }

        // If we got this far, we must be in a variable definition or an enum defintion
        // if the highest stack element is a struct, we are in a variable definition, if
        // the highest stack element is an enum, we are in an enum definition
        StackElement* e = stack.back();
        switch (e->type) {
            case StackElement::Type::Struct:
                if (line.find(';') == std::string_view::npos) {
                    // No semicolon on this line but we are looking for a variable, so we
                    // are in a definition line that spans multiple lines
                    variableBuffer += std::string(line) + " ";
                    continue;
                }
                if (variableBuffer.empty()) {
                    Variable* var = parseVariable(line);
                    if (!commentBuffer.empty() && commentBuffer.back() == ' ') {
                        commentBuffer.pop_back();
                    }
                    var->comment = commentBuffer;
                    commentBuffer.clear();
                    static_cast<Struct*>(e)->variables.push_back(var);
                }
                else {
                    variableBuffer += std::string(line);
                    Variable* var = parseVariable(variableBuffer);
                    if (!commentBuffer.empty() && commentBuffer.back() == ' ') {
                        commentBuffer.pop_back();
                    }
                    var->comment = commentBuffer;
                    commentBuffer.clear();
                    static_cast<Struct*>(e)->variables.push_back(var);
                    variableBuffer.clear();
                }
                continue;
            case StackElement::Type::Enum: {
                EnumElement* el = parseEnumElement(line);
                static_cast<Enum*>(e)->elements.push_back(el);
                continue;
            }
        }
    }

    assert(rootStruct);
    assert(!rootStruct->attributes.dictionary.empty());
    return rootStruct;
}
