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

#include "parsing.h"

#include "types.h"
#include "util.h"
#include <fmt/format.h>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <numeric>

namespace {
    constexpr std::string_view AttributeDictionary = "[[codegen::Dictionary";
    constexpr std::string_view AttributeEnum = "[[codegen::enum";
    constexpr std::string_view AttributeStringify = "[[codegen::stringify";
    constexpr std::string_view AttributeMap = "[[codegen::map";
    constexpr std::string_view AttributeLuaWrap = "[[codegen::luawrap";
} // namespace

/**
 * Extracts everything until the next newline character and updates the \param cursor to
 * the following character. Any whitespaces from the extracted line are trimmed from
 * either end.
 *
 * \param sv The string from which the line is extracted
 * \param cursor The location inside \p sv that is the beginning of the line extraction
 */
std::string_view extractLine(std::string_view sv, size_t* cursor) {
    assert(!sv.empty());
    assert(cursor);
    assert(*cursor == 0 || sv[*cursor - 1] == '\n');
    assert(*cursor < sv.size());

    // Find the next newline character
    const size_t p = sv.find('\n', *cursor);

    if (p != std::string_view::npos) {
        // If there was a newline character, extract everything until then and update the
        // cursor to the following character
        std::string_view line = sv.substr(*cursor, p - *cursor);
        *cursor = p + 1;
        return strip(line);
    }
    else {
        // If there was no newline character, extract the remainder of the string and set
        // the cursor to the npos position
        std::string_view line = sv.substr(*cursor);
        *cursor = std::string_view::npos;
        return strip(line);
    }
}

void escapeString(std::string& line) {
    for (size_t i = 0; i < line.size(); i += 1) {
        if (line[i] == '\\' || line[i] == '"') {
            line.insert(line.begin() + i, '\\');
            i += 1;
        }
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
    if (beg == 0) {
        // The find function returned npos, which +1 == 0

        // No parameters are needed, but if there's a ) without a corresponding ( it's bad
        if (const size_t end = block.find(')');  end != std::string_view::npos) {
            throw CodegenError(fmt::format(
                "Attribute parameter parantheses unbalanced\n{}", block
            ));
        }

        return {};
    }

    // If there is a ( then there has to be a ) as well
    std::string_view name = block.substr(p + key.size(), beg - (p + key.size()) - 1);
    if (const size_t end = block.find(')', beg);  end == std::string_view::npos) {
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
    if (cursor == block.size()) {
        throw CodegenError(fmt::format("Unterminated attribute brackets\n{}", block));
    }
    else if (block[cursor] == ',') {
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
    assert(!line.empty());

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
        else if (p.key == attributes::Color) {
            res.isColor = booleanValue(p.value);
        }
        else if (p.key == attributes::Identifier) {
            res.isIdentifier = booleanValue(p.value);
        }
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

    if (const size_t begin = line.find("[[", cursor);  begin != std::string_view::npos) {
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
            "Missing space or struct name before the opening {{ of a struct\n{}", line
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

    if (const size_t begin = line.find("[[", cursor);  begin != std::string_view::npos) {
        const size_t endAttr = line.find("]]", begin) + 2;
        std::string_view block = line.substr(begin, endAttr - begin);
        std::vector<ParseResult> attrs = parseAttribute(block);

        for (const ParseResult& a : attrs) {
            if (a.key == attributes::Map) {
                if (a.value.empty()) {
                    throw CodegenError("The `map` attribute must have a string argument");
                }
                e->attributes.mappedTo = a.value;
            }
            if (a.key == attributes::Stringify) {
                e->attributes.stringify = true;
            }
        }
        cursor = endAttr + 1;
    }
    const size_t endEnum = line.find(' ', cursor);
    if (endEnum == std::string_view::npos) {
        throw CodegenError(fmt::format(
            "Missing space before the opening {{ of an enum\n{}", line
        ));
    }
    e->name = line.substr(cursor, endEnum - cursor);
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
        res->key = res->attributes.key;
    }
    else {
        res->key = fmt::format("\"{}\"", res->name);
        res->key[1] = static_cast<char>(::toupper(res->name[0]));
    }

    return res;
}

std::pair<size_t, size_t> validStructCode(std::string_view code) {
    assert(!code.empty());

    const size_t loc = code.find(AttributeDictionary);
    if (loc == std::string_view::npos) {
        // We did't find the attribute
        return { std::string_view::npos, std::string_view::npos };
    }

    int64_t cursor = loc;
    while (code.substr(cursor, loc - cursor).find("struct") == std::string_view::npos) {
        cursor--;

        if (cursor < 0) {
            std::string_view sb = code.substr(
                static_cast<size_t>(std::max(0, static_cast<int>(loc) - 50)),
                std::min<size_t>(50, code.size() - 1)
            );
            throw CodegenError(fmt::format(
                "Could not find 'struct' before '[[codegen::Dictionary' before reaching "
                "the end of the file\n{}",
                sb
            ));
        }
    }

    std::string_view nameCheck = code.substr(cursor, loc - cursor);
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

    return { lastNewLine, cursor - lastNewLine + 1 };
}

std::pair<size_t, size_t> validEnumCode(std::string_view code) {
    assert(!code.empty());

    const size_t locEnum = code.find(AttributeEnum);
    const size_t locStringify = code.find(AttributeStringify);
    const size_t locMap = code.find(AttributeMap);
    const size_t loc = std::min({ locEnum, locStringify, locMap });
    if (loc == std::string_view::npos) {
        // We didn't find the attribute
        return { std::string_view::npos, std::string_view::npos };
    }

    int64_t cursor = loc;
    while (code.substr(cursor, loc - cursor).find("enum class") == std::string_view::npos)
    {
        cursor--;

        if (cursor < 0) {
            std::string_view sb = code.substr(
                static_cast<size_t>(std::max(0, static_cast<int>(loc) - 50)),
                std::min<size_t>(50, code.size() - 1)
            );
            throw CodegenError(fmt::format(
                "Could not find 'enum class' before '[[codegen::stringify' before "
                "reaching the end of the file\n{}",
                sb
            ));
        }
    }

    std::string_view nameCheck = code.substr(cursor, loc - cursor);
    assert(startsWith(nameCheck, "enum class"));

    using namespace std::literals;
    nameCheck.remove_prefix("enum class"sv.size());
    for (char c : nameCheck) {
        if (::isspace(c) == 0) {
            throw CodegenError(fmt::format(
                "Only 'enum class' can appear directly before [[codegen::stringify\n{}",
                code.substr(0, std::min<size_t>(code.size(), 50))
            ));
        }
    }

    const size_t lastNewLine = static_cast<size_t>(cursor);
    cursor = code.find('{', lastNewLine) + 1;
    for (int counter = 1; counter > 0; cursor++) {
        if (cursor >= static_cast<int64_t>(code.size())) {
            throw CodegenError(fmt::format(
                "Could not find closing }} of root enum\n{}", code
            ));
        }

        if (code[cursor] == '{') {
            counter++;
        }
        if (code[cursor] == '}') {
            counter--;
        }
    }

    return { lastNewLine, cursor - lastNewLine + 1 };
}

std::pair<size_t, size_t> validFunctionCode(std::string_view code) {
    assert(!code.empty());

    const size_t locWrapLua = code.find(AttributeLuaWrap);
    if (locWrapLua == std::string_view::npos) {
        // We didn't find the attribute
        return { std::string_view::npos, std::string_view::npos };
    }

    const size_t start = locWrapLua + AttributeLuaWrap.size();

    // Find the end of the attribute
    size_t cursor = code.find(']', start) + 1;

    // We have to iterate until we find the first { character that is not contained in
    // any parantheses. { } pairs in parantheses might be used for default initializing a
    // function parameter
    int nParantheses = 0;
    while (true) {
        if (cursor >= code.size()) {
            throw CodegenError(fmt::format(
                "Illformed function definition at {}", code.substr(start, 50)
            ));
        }

        if (code[cursor] == '(') {
            nParantheses += 1;
        }
        if (code[cursor] == ')') {
            nParantheses -= 1;
        }

        if (code[cursor] == '{' && nParantheses == 0) {
            break;
        }

        cursor += 1;
    }

    return { start, cursor + 1 - start };
}

[[nodiscard]] Struct* parseRootStruct(std::string_view code, size_t begin, size_t end) {
    std::string_view content = strip(code.substr(begin, end));

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
                    if (rootStruct) {
                        throw CodegenError(fmt::format(
                            "Found nested structs annotated with the Dictionary "
                            "attribute. It is not allowed to nest these top level "
                            "structs\n\n{} -> {}",
                            rootStruct->name, s->attributes.dictionary
                        ));
                    }
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
                    variableBuffer += ' ';
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
                    enumBuffer += ' ';
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

[[nodiscard]] Enum* parseRootEnum(std::string_view code, size_t begin, size_t end) {
    std::string_view content = strip(code.substr(begin, end));
    assert(!content.empty());

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        throw CodegenError(fmt::format(
            "Block comments are not allowed\n{}", content.substr(p, 50)
        ));
    }

    Enum* rootEnum = nullptr;
    std::string enumBuffer;

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (line.empty()) {
            continue;
        }

        if (startsWith(line, "enum class")) {
            assert(!rootEnum);
            rootEnum = parseEnum(line);
            assert(rootEnum);
            continue;
        }

        if (startsWith(line, "};")) {
            // A bit of a special case for enums.  Since we want to support multiple
            // lines for enum value we have to store the line in a buffer to check
            // when we are finished.  We use a finalizing `,` for it, which does not
            // have to exist and it would also be annoying to force people to enter
            // that for every enum and it is error prone.  So we need to check here if
            // we still have an enum in the buffer and add that if it is so

            if (!enumBuffer.empty()) {
                enumBuffer += line;
                EnumElement* el = parseEnumElement(enumBuffer);
                assert(el);
                enumBuffer.clear();
                rootEnum->elements.push_back(el);
            }
            continue;
        }

        if (line.back() != ',') {
            // No comma at the end means that this line is not finished yet.
            // Though this means that that the last value will be added to the
            // buffer since it will not be finished
            enumBuffer += line;
            enumBuffer += ' ';
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
        rootEnum->elements.push_back(el);
        continue;
    }

    return rootEnum;
}

Function* parseRootFunction(std::string_view code, size_t begin, size_t end,
                            std::vector<Struct*> structs, std::vector<Enum*> enums)
{
    std::string_view content = strip(code.substr(begin, end));
    assert(!content.empty());

    auto eatType = [&content](size_t& cursor) -> std::pair<size_t, size_t> {
        bool foundBeginningOfReturnValue = false;
        int nOpenBrackets = 0;

        std::pair<size_t, size_t> loc = std::pair(0, 0);
        while (true) {
            if (cursor == content.size()) {
                throw CodegenError(fmt::format(
                    "Error detecting end of return value\n{}", content.substr(cursor, 50)
                ));
            }

            // Find the first non-space character as the start of the return value
            if (content[cursor] != ' ' && content[cursor] != '\n' &&
                !foundBeginningOfReturnValue)
            {
                loc.first = cursor;
                foundBeginningOfReturnValue = true;
            }

            if (content[cursor] == '<') {
                nOpenBrackets += 1;
            }

            if (content[cursor] == '>') {
                nOpenBrackets -= 1;
            }

            bool isEndCharacter =
                content[cursor] == ' ' || content[cursor] == '\n' ||
                content[cursor] == ')' || content[cursor] == ',';

            if (isEndCharacter && nOpenBrackets == 0) {
                // We have reached the space that separates the return value from the
                // function name
                loc.second = cursor;
                break;
            }

            cursor += 1;
        }

        return loc;
    };

    auto eatName = [&content](size_t& cursor) -> std::pair<size_t, size_t> {
        std::pair<size_t, size_t> loc = std::pair(0, 0);

        // Skip the first whitespace(s)
        cursor = content.find_first_not_of(' ', cursor);
        loc.first = cursor;

        // The name of the variable is all characters until the first separator which is
        // one of these four characters
        cursor = content.find_first_of(" ,=)", cursor);
        loc.second = cursor;

        return loc;
    };

    Function* f = new Function;

    // Let's see if there is a documentation entry just preceding this function. It is
    // optional and we don't want to accidentally pick up some other documentation higher
    // up in the file, so we have to be a bit conservative with what we try to pick up
    {
        using namespace std::literals;

        size_t b = begin - AttributeLuaWrap.size();


        //
        // First check for block comments
        //
        size_t endBlockComment = code.rfind("*/", b);
        bool hasValidBlockComment = endBlockComment != std::string_view::npos;
        endBlockComment += "/*"sv.size();

        // Check that there are only empty character between the end of the block and the
        // beginning of the function
        size_t firstRealCharAfterBlock = code.find_first_not_of(" \n", endBlockComment);
        hasValidBlockComment &= (firstRealCharAfterBlock >= b);


        //
        // Then check for regular // comments
        //
        size_t endRegularComment = code.rfind("//", b);
        bool hasValidRegularComment = endRegularComment != std::string_view::npos;
        endRegularComment += "//"sv.size();

        // Check that there are only empty character between the end of the block and the
        // beginning of the function
        size_t regularCursor = code.find('\n', endRegularComment);
        size_t firstRealCharAfterRegular = code.find_first_not_of(" \n", regularCursor);
        hasValidRegularComment &= (firstRealCharAfterRegular >= b);

        // There should only be at most one of them
        assert(!(hasValidBlockComment && hasValidRegularComment));


        std::vector<std::string_view> lines;
        if (hasValidBlockComment) {
            // Find the beginning /* for that comment
            size_t beginBlockComment = code.rfind("/*", endBlockComment);

            std::string_view cmnt = code.substr(
                beginBlockComment,
                endBlockComment - beginBlockComment
            );
            cmnt.remove_prefix("/*"sv.size());
            cmnt.remove_suffix("*/"sv.size());

            size_t c = 0;
            size_t p = cmnt.find('\n', 1);
            while (p != std::string_view::npos) {
                std::string_view line = cmnt.substr(c, p - c);
                std::string_view stripLine = strip(line);

                if (stripLine[0] == '*') {
                    stripLine.remove_prefix(1);
                }

                stripLine = strip(stripLine);
                lines.push_back(stripLine);
                c = p;
                p = cmnt.find('\n', c + 1);
            }
        }

        if (hasValidRegularComment) {
            // Extract lines backwards until we find the first non-commented line and then
            // abort
            size_t cursor = code.find('\n', endRegularComment);
            assert(cursor != std::string_view::npos);
            while (true) {
                size_t lineBegin = code.rfind('\n', cursor - 1);

                std::string_view line = code.substr(lineBegin, cursor - lineBegin);
                std::string_view stripLine = strip(line);
                if (stripLine.substr(0, 2) != "//") {
                    // The line did not start with a comment, therefore we have reached
                    // the end of the comment block
                    break;
                }

                stripLine.remove_prefix("//"sv.size());
                stripLine = strip(stripLine);
                lines.push_back(stripLine);
                cursor = lineBegin;
            }

            std::reverse(lines.begin(), lines.end());
        }

        f->documentation = std::accumulate(
            lines.cbegin(),
            lines.cend(),
            std::string(),
            [](std::string lhs, std::string_view rhs) {
                return rhs.empty() ? lhs : lhs + std::string(strip(rhs)) + ' ';
            }
        );
        // There is an empty character at the end which we should remove
        f->documentation = f->documentation.substr(0, f->documentation.size() - 1);

        // People might be using \ in the documentation which we should escape. Similarly
        // we want to replace " with \"
        escapeString(f->documentation);
    }

    // Check if there are any arguments to the luawrap attribute, which would be the
    // custom name that we should use
    size_t precursor = 0;
    size_t beginName = std::string_view::npos;
    size_t endName = std::string_view::npos;
    while (content[precursor] != ']') {
        if (content[precursor] == '(') {
            beginName = precursor + 1;
        }
        if (content[precursor] == ')') {
            endName = precursor;
        }

        precursor += 1;
    }
    precursor += 2; // ]]
    precursor = content.find_first_not_of(" \n", precursor);

    if (beginName != std::string_view::npos && endName != std::string_view::npos) {
        std::string_view luaName = content.substr(beginName, endName - beginName);

        if (luaName.empty() || luaName.size() == 2) {
            throw CodegenError(fmt::format(
                "Error in custom name for luawrap function. Provided name was empty\n{}",
                content
            ));
        }
        if (luaName[0] != '"' || luaName[luaName.size() - 1] != '"') {
            throw CodegenError(fmt::format(
                "Error in custom name for luawrap function. Provided name must be "
                "enclosed by \"\n{}", content
            ));
        }

        assert(luaName[0] == '"');
        luaName.remove_prefix(1);
        assert(luaName[luaName.size() - 1] == '"');
        luaName.remove_suffix(1);
        f->luaName = std::string(luaName);
    }

    content.remove_prefix(precursor);
    size_t cursor = 0;


    // This pseudo-struct holds all of the root elements that have been declared prior to
    // this function. We need to pass this as a context into the parseType function in
    // order to use custom structs and enums as parameters or return values as we need to
    // resolve those types locally
    Struct* root = nullptr;
    if (!structs.empty() || !enums.empty()) {
        root = new Struct;
        root->name = "_root";

        root->children.insert(root->children.end(), structs.begin(), structs.end());
        root->children.insert(root->children.end(), enums.begin(), enums.end());
    }


    // Find and parse the return value
    std::pair<size_t, size_t> retValueLoc = eatType(cursor);
    std::string_view returnValueStr = content.substr(
        retValueLoc.first,
        retValueLoc.second
    );
    f->returnValue = parseType(returnValueStr, root);

    //
    // Extract the function name
    //
    {
        // Move the cursor forward as long as there are space characters
        cursor = content.find_first_not_of(" \n", cursor + 1);

        std::pair<size_t, size_t> loc = std::pair(cursor, 0);
        cursor = content.find_first_of(" (", cursor);
        loc.second = cursor;

        cursor += 1;

        std::string_view name = content.substr(loc.first, loc.second - loc.first);
        f->functionName = std::string(strip(name));
        if (::isupper(f->functionName[0])) {
            throw CodegenError(fmt::format(
                "Marked functions must not start with an uppercase letter\n{}", content
            ));
        }
    }

    // If no custom Lua name given, we use the function name instead
    if (f->luaName.empty()) {
        f->luaName = f->functionName;
    }


    // Parse the parameters
    while (true) {
        if (content[cursor] == ' ' || content[cursor] == ',' || content[cursor] == '\n') {
            cursor += 1;
            continue;
        }
        if (content[cursor] == ')') {
            break;
        }

        std::pair<size_t, size_t> locType = eatType(cursor);
        std::string_view typeStr =
            content.substr(locType.first, locType.second - locType.first);

        if (strip(typeStr) == "const") {
            cursor += 1;
            std::pair<size_t, size_t> l = eatType(cursor);
            std::string_view typeStr2 = content.substr(l.first, l.second - l.first);
            assert(!typeStr2.empty());
            if (typeStr2[typeStr2.size() - 1] == '*') {
                throw CodegenError(fmt::format(
                    "Illegal pointer type '{} {}' found in function '{}'\n{}",
                    typeStr, typeStr2, f->functionName, content
                ));
            }
            else if (typeStr2[typeStr2.size() - 1] == '&') {
                throw CodegenError(fmt::format(
                    "Illegal reference type '{} {}' found in function '{}'\n{}",
                    typeStr, typeStr2, f->functionName, content
                ));
            }
        }

        Variable* v = new Variable;
        v->type = parseType(typeStr, root);

        if (v->type->isTupleType()) {
            throw CodegenError(fmt::format(
                "Tuples are not supported in parameter arguments\n{}",
                content.substr(cursor, 50)
            ));
        }

        cursor = content.find_first_not_of(' ', cursor);
        if (size_t beg = content.substr(cursor).find("[[codegen::");
            beg != std::string_view::npos)
        {
            Variable::Attributes attr = parseAttributes(content.substr(cursor));
            size_t e = content.substr(cursor).find("]]");
            cursor += (e - beg) + 3;  // 2 -> ]]
            cursor = content.find_first_not_of(' ', cursor);
        }

        {
            std::pair<size_t, size_t> l = eatName(cursor);
            v->name = std::string(content.substr(l.first, l.second - l.first));

            if (v->name.empty()) {
                throw CodegenError(fmt::format(
                    "Parameter {} of function '{}' has no name, which is not allowed",
                    f->arguments.size(), f->functionName
                ));
            }

            if (v->name == "res") {
                throw CodegenError(
                    "'res' is a reserved name and cannot be used for parameter naems"
                );
            }
        }


        // There are a few options for characters that follow the name;  either it can be
        // a , meaning that there are more arguments coming, a = representing a default
        // parameter which we don't want to parse (but mark the type as an optional type)
        // or ) which means that we are done parsing the parameter list. The first and
        // third case are handled at the top of this loop, so we only need to care about
        // the = case
        size_t equalLoc = content.find('=', cursor);
        size_t commaLoc = content.find(',', cursor);
        size_t paranLoc = content.find(')', cursor);

        if (equalLoc != std::string_view::npos &&  // -> there is an equal sign
            equalLoc < commaLoc && equalLoc < paranLoc) // -> it comes before the next , )
        {
            // If the variable has a default value allocated with it, we wrap the type in
            // an optional type to represent that
            OptionalType* ot = new OptionalType;
            ot->tag = VariableType::Tag::OptionalType;
            ot->type = v->type;

            // Skip over the actual value for the default parameter as it would otherwise
            // confuse the rest of this function. This can be a bit tricky since the
            // default value can take a few different forms. The tricky ones would be
            // 1. int a = int(2)  or 2. int a = { 2 }  where we have to iterate and keep
            // track of the brackets opening and closing
            //cursor = std::min(commaLoc, paranLoc);

            int nOpenParans = 0;
            cursor = equalLoc;
            while (true) {
                if (cursor >= content.size()) {
                    throw CodegenError(fmt::format(
                        "Illformed function definition at {}", content
                    ));
                }

                if (content[cursor] == '{' || content[cursor] == '}') {
                    throw CodegenError(fmt::format(
                        "Default initialization of function parameters using the "
                        "initializer list syntax is not supported", content
                    ));
                }

                if (content[cursor] == '(') {
                    nOpenParans += 1;
                }
                if (content[cursor] == ')') {
                    if (nOpenParans == 0) {
                        // There are no open parantheses left, so we are done as this
                        // closing parantheis is the end of the function declaration.
                        // There can't be any open curlys left or the code would be
                        // illformed C++
                        break;
                    }
                    else {
                        nOpenParans -= 1;
                    }
                }
                if (content[cursor] == ',' && nOpenParans == 0) {
                    // No open parantheses or curlies means that this command is the
                    // separator to the next argument
                    break;
                }

                cursor += 1;
            }

            // Jump over the = sign
            equalLoc += 1;
            while (content[equalLoc] == ' ') {
                equalLoc += 1;
            }

            std::string_view defaultValue = content.substr(equalLoc, cursor - equalLoc);
            ot->defaultArgument = std::string(defaultValue);
            v->type = ot;
        }

        f->arguments.push_back(v);
    }

    // Verify that the arguments are ordered correctly. The correct order is that there
    // can be optional arguments in the beginning, then required arguments in the middle,
    // followed by more optional arguments at the end. Only the ending optional arguments
    // may have default values or else the originating C function was illformed
    enum class Phase {
        Initial,
        FirstOptional,
        Required,
        SecondOptional
    };
    Phase phase = Phase::Initial;
    for (size_t i = 0; i < f->arguments.size(); i +=1) {
        Variable* var = f->arguments[i];
        bool isOptional = var->type->isOptionalType();
        switch (phase) {
            case Phase::Initial:
                phase = isOptional ? Phase::FirstOptional : Phase::Required;
                break;
            case Phase::Required:
                if (isOptional) {
                    phase = Phase::SecondOptional;
                }
                break;
            case Phase::FirstOptional:
                if (!isOptional) {
                    phase = Phase::Required;

                    // Make sure that the last optional and the first required are not the
                    // same type or there might be confusion in the end
                    if (i > 0) {
                        Variable* lastVar = f->arguments[i - 1];
                        assert(lastVar->type->isOptionalType());
                        OptionalType* ot = static_cast<OptionalType*>(lastVar->type);
                        if (*var->type == *ot->type) {
                            throw CodegenError(fmt::format(
                                "When using optional arguments in the beginning of the "
                                "argument list, the last optional argument must not have "
                                "the same type as the first required argument or we "
                                "can't distinguish whether the parameter is the last "
                                "optional or the first required one"
                            ));
                        }
                    }
                }
                break;
            case Phase::SecondOptional:
                if (!isOptional) {
                    // We have seen the first optional parameter but now there is a
                    // not-optional one, so we have a wrong ordering of parameters
                    throw CodegenError(fmt::format(
                        "It is not supported to have non-optional parameters after "
                        "optional ones\n{}", content.substr(cursor, 50)
                    ));
                }
                break;
        }
    }

    return f;
}

[[nodiscard]] Code parse(std::string codeStr, std::string fileName) {
    // When trying to generate code checked out on a Windows machine on a Linux virtual
    // machine, codegen gets confused with the \r\n vs \n mess.  In order to prevent that
    // we just remove all of the \r characters here
    codeStr.erase(std::remove(codeStr.begin(), codeStr.end(), '\r'), codeStr.end());
    std::string_view code = codeStr;

    // We want to keep track of the line number where we find different parts. Since we
    // remove the code parts that we have successfully dealt with, we need to manually
    // count the number of lines that have already been processed
    int nSkippedLines = 0;

    Code res;

    while (!code.empty()) {
        enum class Type {
            Struct,
            Enum,
            Function,
            None
        };
        struct NextCode {
            Type type;
            std::pair<size_t, size_t> cursors;
        };
        std::vector<NextCode> nextCodes;

        // Collect all of the possible next code blocks
        nextCodes.push_back({ Type::Struct, validStructCode(code) });
        nextCodes.push_back({ Type::Enum, validEnumCode(code) });
        nextCodes.push_back({ Type::Function, validFunctionCode(code) });

        // Sort so that we can find the one that is coming up next
        std::sort(
            nextCodes.begin(),
            nextCodes.end(),
            [](const NextCode& lhs, const NextCode& rhs) {
                return lhs.cursors.first < rhs.cursors.first;
            }
        );

        NextCode next = nextCodes.front();
        if (next.cursors.first == std::string_view::npos) {
            // If the closest cursor is already the npos, then there is no more code left
            break;
        }

        switch (next.type) {
            case Type::Struct: {
                Struct* s = parseRootStruct(
                    code,
                    next.cursors.first,
                    next.cursors.second
                );
                assert(s);
                res.structs.push_back(s);
                break;
            }
            case Type::Enum: {
                Enum* e = parseRootEnum(code, next.cursors.first, next.cursors.second);
                assert(e);
                res.enums.push_back(e);
                break;
            }
            case Type::Function: {
                Function* f = parseRootFunction(
                    code,
                    next.cursors.first,
                    next.cursors.second,
                    res.structs,
                    res.enums
                );
                assert(f);

                // Count the number of \n between the beginning and 'begin' to get the
                // line number. Since we do line numbers 1-based, we have to add 1
                int nLines = static_cast<int>(
                    std::count(code.begin(), code.begin() + next.cursors.first, '\n')
                ) + 1;

                f->sourceLocation.line = nSkippedLines + nLines;

                // There is probably something smarter that we can do here, but if we use
                // the `fileName` as is we are going to end up with the
                f->sourceLocation.file = fileName;
                std::replace(
                    f->sourceLocation.file.begin(),
                    f->sourceLocation.file.end(),
                    '\\',
                    '/'
                );

                for (Function* func : res.luaWrapperFunctions) {
                    if (f->functionName == func->functionName) {
                        throw CodegenError(fmt::format(
                            "Cannot define multiple functions with the same name\n{}",
                            code.substr(next.cursors.first, 50)
                        ));
                    }
                }

                res.luaWrapperFunctions.push_back(f);
                break;
            }
            default:
                throw std::logic_error("Missing case exception");
        }

        const size_t p = std::min(next.cursors.first + next.cursors.second, code.size());

        // Count the number of skipped lines so that our source location stays correct
        nSkippedLines += static_cast<int>(
            std::count(code.begin(), code.begin() + p, '\n')
        );

        // Remove the code that we just handled
        code.remove_prefix(p);
    }

    return res;
}
