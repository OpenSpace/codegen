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

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary";
} // namespace

std::string_view extractLine(std::string_view sv, size_t* cursor) {
    assert(!sv.empty());
    assert(cursor);
    assert(*cursor == 0 || sv[*cursor - 1] == '\n');

    const size_t p = sv.find('\n', *cursor);

    if (p != std::string_view::npos) {
        std::string_view line = sv.substr(*cursor, p - *cursor);
        *cursor = p + 1;
        return strip(line);
    }
    else {
        std::string_view line = sv.substr(*cursor);
        *cursor = std::string_view::npos;
        return strip(line);
    }
}

struct ParseResult {
    std::string_view key;
    std::string_view value;
};

std::vector<ParseResult> parseAttribute(std::string_view block) {
    assert(!block.empty());

    std::string_view key = "codegen::";
    const size_t p = block.find(key);
    if (p == std::string::npos) {
        return {};
    }
    const size_t beg = block.find('(', p) + 1;

    std::string_view name = block.substr(p + key.size(), beg - (p + key.size()) - 1);
    if (const size_t end = block.find(')', beg); end == std::string_view::npos) {
        throw CodegenError(fmt::format(
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
    std::vector<ParseResult> res;
    res.push_back({ name, strip(content) });

    // Skip over whitespaces
    while (cursor < block.size() && ::isspace(block[cursor])) {
        cursor++;
    }
    if (block[cursor] == ',') {
        std::vector<ParseResult> recRes = parseAttribute(block.substr(cursor));
        res.insert(res.end(), recRes.begin(), recRes.end());
    }
    else if (block[cursor] != ']') {
        throw CodegenError(fmt::format(
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

bool booleanValue(std::string_view v) {
    if (v != "true" && v != "false" && !v.empty()) {
        throw CodegenError(fmt::format(
            "Boolean attribute needs to be empty, 'true', or 'false'. Got {}", v
        ));
    }
    return (v == "true") || v.empty();
}

Variable::Attributes parseAttributes(std::string_view line) {
    Variable::Attributes res;

    std::vector<ParseResult> attributes = parseAttribute(line);
    for (const ParseResult& p : attributes) {
        if (p.key == attributes::Key)               { res.key = p.value; }
        else if (p.key == attributes::Reference)    { res.reference = p.value; }
        else if (p.key == attributes::InRange)      { res.inrange = p.value; }
        else if (p.key == attributes::NotInRange)   { res.notinrange = p.value; }
        else if (p.key == attributes::Less)         { res.less = p.value; }
        else if (p.key == attributes::LessEqual)    { res.lessequal = p.value; }
        else if (p.key == attributes::Greater)      { res.greater = p.value; }
        else if (p.key == attributes::GreaterEqual) { res.greaterequal = p.value; }
        else if (p.key == attributes::Unequal)      { res.unequal = p.value; }
        else if (p.key == attributes::InList)       { res.inlist = p.value; }
        else if (p.key == attributes::NotInList)    { res.notinlist = p.value; }
        else if (p.key == attributes::Annotation)   {
            // Remove \" characters in the middle of the string that users will have added
            // to make it possible to have an annotation span multiple lines. We want to
            // maintain the ones in the beginning and the end, so we don't check those
            // characters
            std::string v = std::string(p.value);
            for (size_t i = 1; i < v.size() - 1; i += 1) {
                if (v[i] == '\"') {
                    v.erase(i, 1);
                    i -= 1;
                }
            }

            res.annotation = v;
        }
        else if (p.key == attributes::Directory) {
            res.isDirectory = booleanValue(p.value);
        }
        else if (p.key == attributes::DateTime) {
            res.isDateTime = booleanValue(p.value);
        }
        else if (p.key == attributes::Color) { res.isColor = booleanValue(p.value); }
        else if (p.key == attributes::MustBeNotEmpty) {
            res.mustBeNotEmpty = booleanValue(p.value);
        }
        else {
            throw CodegenError(fmt::format(
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

    if (const size_t begin = line.find("[[", cursor); begin != std::string_view::npos) {
        const size_t endAttr = line.find("]]", begin) + 2;
        std::string_view block = line.substr(begin, endAttr - begin);
        std::vector<ParseResult> attrs = parseAttribute(block);
        for (const ParseResult& a : attrs) {
            if (a.key == attributes::Dictionary) {
                s->attributes.dictionary = a.value;
            }
            else if (a.key == attributes::NoExhaustive) {
                s->attributes.noExhaustive = (a.value == "true" || a.value.empty());
            }
            else {
                throw CodegenError(fmt::format(
                    "Unknown attribute '{}' in struct definition found\n{}", a.key, line
                ));
            }
        }
        if (s->attributes.dictionary.empty()) {
            throw CodegenError(fmt::format(
                "No name specified for root struct\n{}", line
            ));
        }
        char firstChar = s->attributes.dictionary[0];
        char lastChar = s->attributes.dictionary[s->attributes.dictionary.size() - 1];
        if (firstChar == '"' && lastChar == '"') {
            throw CodegenError(fmt::format(
                "Root struct name must not be enclosed by \"\n{}", line
            ));
        }
        cursor = endAttr + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if ((endStruct == std::string_view::npos) || (endStruct == line.size() - 1)) {
        throw CodegenError(fmt::format(
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
        throw CodegenError(fmt::format(
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
        std::vector<ParseResult> attr = parseAttribute(attributes);
        for (const ParseResult& a : attr) {
            if (a.key == "key") {
                e->attributes.key = a.value;
            }
            else {
                throw CodegenError(fmt::format(
                    "Unrecognized attribute '{}' found when parsing enum value\n{}",
                    a.key, line
                ));
            }
        }
    }
    if (e->attributes.key.empty()) {
        e->attributes.key = fmt::format("\"{}\"", e->name);
    }
    return e;
}

Variable* parseVariable(std::string_view line, Struct* s) {
    assert(!line.empty());

    // Remove the trailing ;
    line.remove_suffix(1);

    if (line.find('=') != std::string_view::npos) {
        throw CodegenError(fmt::format(
            "Found '=' in variable definition but default parameters are not allowed\n{}",
            line
        ));
    }

    if (line.find(' ') == std::string_view::npos) {
        throw CodegenError(fmt::format(
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
        throw CodegenError(fmt::format("Unbalanced number of < > brackets\n{}", line));
    }

    const size_t p1 = cursor;
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        throw CodegenError(fmt::format(
            "Too few spaces in variable definition\n{}", line
        ));
    }

    Variable* res = new Variable;

    std::string_view typeString = line.substr(0, p1);
    res->type = parseType(typeString, s);
    res->name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        std::string_view attr = strip(attributes);
        if (!attr.empty()) {
            res->attributes = parseAttributes(attributes);
        }
    }

    if (!res->attributes.key.empty()) {
        res->key = std::string(res->attributes.key);
    }
    else {
        res->key = fmt::format("\"{}\"", res->name);
        res->key[1] = static_cast<char>(::toupper(res->name[0]));
    }

    return res;
}

std::string_view validCode(std::string_view code) {
    assert(!code.empty());

    const size_t mainLoc = code.find(AttributeDictionary);
    if (mainLoc == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLoc + 1) != std::string_view::npos) {
        throw CodegenError(fmt::format(
            "We currently only support one struct per file annotated with {}, "
            "including commented out ones",
            AttributeDictionary
        ));
    }

    int64_t cursor = mainLoc;
    while (code.substr(cursor, mainLoc - cursor).find("struct") == std::string_view::npos)
    {
        cursor--;

        if (cursor < 0) {
            std::string_view sb = code.substr(
                static_cast<size_t>(std::max(0, static_cast<int>(mainLoc) - 50)),
                std::min<size_t>(50, code.size() - 1)
            );
            throw CodegenError(fmt::format(
                "Could not find 'struct' before '[[codegen::Dictionary' before reaching "
                "the beginning of the file\n{}",
                sb
            ));
        }
    }

    std::string_view nameCheck = code.substr(cursor, mainLoc - cursor);
    assert(startsWith(nameCheck, "struct"));

    using namespace std::literals;
    nameCheck.remove_prefix("struct"sv.size());
    for (char c : nameCheck) {
        if (::isspace(c) == 0) {
            throw CodegenError(fmt::format(
                "Only 'struct' can appear directly before [[codegen::Dictionary\n{}",
                code.substr(0, std::min<size_t>(code.size(), 50))
            ));
        }
    }

    const size_t lastNewLine = static_cast<size_t>(cursor);

    cursor = code.find('{', lastNewLine) + 1;
    for (int counter = 1; counter > 0; cursor++) {
        if (cursor >= static_cast<int64_t>(code.size())) {
            throw CodegenError(fmt::format(
                "Could not find closing }} of root struct\n{}", code
            ));
        }

        if (code[cursor] == '{') {
            counter++;
        }
        if (code[cursor] == '}') {
            counter--;
        }
    }

    return code.substr(lastNewLine, cursor - lastNewLine + 1);
}

Struct* parseRootStruct(std::string_view code) {
    // I really would prefer not to have this code as it basically makes any UTF-8
    // character invalid, which would be a shame
    //for (char c : code) {
    //    // This only should really happen when a UTF-8 character is encountered
    //    if (c < 0) {
    //        throw ParsingError(fmt::format("Illegal character '{}' detected", c));
    //    }
    //}

    std::string_view content = strip(validCode(code));
    if (content.empty()) {
        return nullptr;
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        throw CodegenError(fmt::format(
            "Block comments are not allowed\n{}", content.substr(p, 50)
        ));
    }


    Struct* rootStruct = nullptr;
    std::vector<StackElement*> stack;
    std::string structBuffer;
    std::string enumBuffer;
    std::string variableBuffer;
    std::string commentBuffer;

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (line.empty()) {
            continue;
        }

        // If the buffer is filled, then we are in a continuation of a variable definition
        if (variableBuffer.empty()) {
            if (startsWith(line, "//")) {
                std::string_view comment = parseCommentLine(line);
                commentBuffer += comment;
                commentBuffer += " ";
                continue;
            }

            if (startsWith(line, "struct") || !structBuffer.empty()) {
                structBuffer += line;
                structBuffer += " ";
                // Check if we have a continuation going on
                if (line.back() != '{') {
                    continue;
                }

                if (!stack.empty() && stack.back()->type != StackElement::Type::Struct) {
                    throw CodegenError(fmt::format(
                        "Struct definition found outside a parent struct\n{}",
                        structBuffer
                    ));
                }

                Struct* s = parseStruct(structBuffer);
                assert(s);
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
                assert(e);
                if (stack.back()->type != StackElement::Type::Struct) {
                    throw CodegenError(fmt::format(
                        "Enum class definition found inside another enum definition\n{}",
                        line
                    ));
                }
                Struct* parent = static_cast<Struct*>(stack.back());
                assert(parent);
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
                throw CodegenError(
                    "Old-style 'enum' not supported. Use 'enum class' instead"
                );
            }

            if (startsWith(line, "};")) {
                // A bit of a special case for enums.  Since we want to support multiple
                // lines for enum value we have to store the line in a buffer to check
                // when we are finished.  We use a finalizing , for it, which does not
                // have to exist and it would also be annoying to force people to enter
                // that for every enum and it is error prone.  So we need to check here if
                // we still have an enum in the buffer and add that if it is so

                if (stack.back()->type == StackElement::Type::Enum && !enumBuffer.empty())
                {
                    Enum* e = static_cast<Enum*>(stack.back());
                
                    enumBuffer += line;
                    EnumElement* el = parseEnumElement(enumBuffer);
                    assert(el);
                    enumBuffer.clear();
                    e->elements.push_back(el);
                }

                stack.pop_back();
                continue;
            }
        }

        // If we got this far, we must be in a variable definition or an enum defintion
        // if the highest stack element is a struct, we are in a variable definition, if
        // the highest stack element is an enum, we are in an enum definition
        StackElement* e = stack.back();
        assert(e);
        switch (e->type) {
            case StackElement::Type::Struct: {
                if (line.find(';') == std::string_view::npos) {
                    // No semicolon on this line but we are looking for a variable, so we
                    // are in a definition line that spans multiple lines
                    variableBuffer += line;
                    variableBuffer += " ";
                    continue;
                }
                Struct* s = static_cast<Struct*>(e);

                Variable* var;
                if (variableBuffer.empty()) {
                    var = parseVariable(line, s);
                }
                else {
                    variableBuffer += line;
                    var = parseVariable(variableBuffer, s);
                    variableBuffer.clear();
                }
                assert(var);
                if (!commentBuffer.empty() && commentBuffer.back() == ' ') {
                    commentBuffer.pop_back();
                }
                var->comment = commentBuffer;
                commentBuffer.clear();
                s->variables.push_back(var);
                continue;
            }
            case StackElement::Type::Enum: {
                if (line.back() != ',') {
                    // No comma at the end means that this line is not finished yet.
                    // Though this means that that the last value will be added to the
                    // buffer since it will not be finished
                    enumBuffer += line;
                    enumBuffer += " ";
                    continue;
                }
                
                EnumElement* el;
                if (enumBuffer.empty()) {
                    el = parseEnumElement(line);
                }
                else {
                    enumBuffer += line;
                    el = parseEnumElement(enumBuffer);
                    enumBuffer.clear();
                }
                assert(el);
                Enum* en = static_cast<Enum*>(e);
                en->elements.push_back(el);
                continue;
            }
        }
    }

    assert(rootStruct);
    assert(!rootStruct->attributes.dictionary.empty());
    return rootStruct;
}
