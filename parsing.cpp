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

#include "types.h"

#include "util.h"
#include <fmt/format.h>
#include <cassert>

std::string_view parseCommentLine(std::string_view line) {
    assert(line.size() >= 2);

    // Remove the starting // characters
    std::string_view comment = strip(line.substr(2));
    return comment;
}

std::string_view parseAttribute(std::string_view block, std::string_view name) {
    assert(!block.empty());
    assert(!name.empty());

    std::string key = std::string("codegen::" + std::string(name));
    const size_t p = block.find(key);
    if (p == std::string_view::npos) {
        return std::string_view();
    }
    const size_t beg = block.find('(', p) + 1;

    if (const size_t end = block.find(')', beg); end == std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "Attribute parameter has unterminated parameter list:\n{}", block
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
    cursor--;

    std::string_view content = block.substr(beg, cursor - beg);
    return content;
}

Struct parseStruct(std::string_view line) {
    assert(!line.empty());

    Struct s;

    size_t cursor = line.find(' ');
    assert(line.substr(0, cursor) == "struct");
    cursor++;

    const size_t beginAttribute = line.find("[[", cursor);
    if (beginAttribute != std::string_view::npos) {
        const size_t endAttribute = line.find("]]", beginAttribute) + 2;
        std::string_view block = line.substr(
            beginAttribute,
            endAttribute - beginAttribute
        );
        s.attributes.dictionary = parseAttribute(block, "Dictionary");
        if (s.attributes.dictionary.empty()) {
            throw std::runtime_error(
                fmt::format("No name specified for root struct:\n{}", line)
            );
        }

        s.attributes.namespaceSpecifier = parseAttribute(block, "namespace");
        cursor = endAttribute + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Missing space before the closing {{ of a struct:\n{}", line)
        );
    }
    s.name = line.substr(cursor, endStruct - cursor);
    return s;
}

Enum parseEnum(std::string_view line) {
    assert(!line.empty());

    Enum e;

    size_t cursor = line.find(' ', line.find(' ') + 1);
    assert(line.substr(0, cursor) == "enum class");
    cursor++;

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Missing space before the closing {{ of a struct:\n{}", line)
        );
    }
    e.name = line.substr(cursor, endStruct - cursor);
    return e;
}

EnumElement parseEnumElement(std::string_view line) {
    assert(!line.empty());

    if (line.back() == ',') {
        line.remove_suffix(1);
    }

    size_t i = line.find(' ');
    EnumElement e;
    e.name = line.substr(0, i);
    if (i != std::string_view::npos) {
        std::string_view attributes = line.substr(i + 1);
        e.attributes.key = parseAttribute(attributes, "key");
    }
    return e;
}

Variable parseVariable(std::string_view line) {
    assert(!line.empty());

    // Remove the trailing ;
    line.remove_suffix(1);

    if (line.find(' ') == std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "Variable definition does not contain any empty character:\n{}", line
        ));
    }

    // Find the end of the variable definition, ignoring spaces in template parameter
    // arguments
    size_t cursor = 0;
    int nBrackets = 0;
    while (true) {
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

    const size_t p1 = cursor;
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        throw std::runtime_error(
            fmt::format("Too few spaces in variable definition:\n{}", line)
        );
    }

    Variable res;
    res.type = line.substr(0, p1);
    res.name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        if (std::string_view a = parseAttribute(attributes, "key"); !a.empty()) {
            res.attributes["key"] = parseAttribute(attributes, "key");
        }
        if (std::string_view a = parseAttribute(attributes, "reference"); !a.empty()) {
            res.attributes["reference"] = parseAttribute(attributes, "reference");
        }

        if (std::string_view a = parseAttribute(attributes, "inrange"); !a.empty()) {
            res.attributes["inrange"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "notinrange"); !a.empty()) {
            res.attributes["notinrange"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "less"); !a.empty()) {
            res.attributes["less"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "lessequal"); !a.empty()) {
            res.attributes["lessequal"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "greater"); !a.empty()) {
            res.attributes["greater"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "greaterequal"); !a.empty()) {
            res.attributes["greaterequal"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "unequal"); !a.empty()) {
            res.attributes["unequal"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "inlist"); !a.empty()) {
            res.attributes["inlist"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "notinlist"); !a.empty()) {
            res.attributes["notinlist"] = a;
        }
        if (std::string_view a = parseAttribute(attributes, "annotation"); !a.empty()) {
            res.attributes["annotation"] = a;
        }
    }

    return res;
}
