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

#include "util.h"

#include <fmt/format.h>
#include <algorithm>
#include <cassert>
#include <functional>

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary";
} // namespace

std::string_view strip(std::string_view sv) {
    const size_t strBegin = sv.find_first_not_of(' ');
    if (strBegin == std::string::npos) {
        return sv;
    }

    const size_t strEnd = sv.find_last_not_of(' ');
    const size_t strRange = strEnd - strBegin + 1;
    return sv.substr(strBegin, strRange);
}

bool startsWith(std::string_view lhs, std::string_view rhs) {
    assert(!lhs.empty());
    assert(!rhs.empty());
    return lhs.size() >= rhs.size() && lhs.substr(0, rhs.size()) == rhs;
}

std::string join(const std::vector<std::string_view>& list, std::string_view sep) {
    assert(std::none_of(list.begin(), list.end(), std::mem_fn(&std::string_view::empty)));
    assert(!sep.empty());

    size_t size = 0;
    for (std::string_view l : list) {
        size += l.size();
    }
    // this allocates space for one sep more than needed, but it simplifies the for loop
    size += sep.size() * (list.size() - 1);

    std::string res;
    res.reserve(size);
    for (std::string_view l : list) {
        res.append(l.data(), l.size());
        res.append(sep.data(), sep.size());
    }
    // Remove the last separator
    for (size_t i = 0; i < sep.size(); ++i) {
        res.pop_back();
    }
    return res;
}

std::string join(const std::vector<std::string>& list, std::string_view sep) {
    assert(std::none_of(list.begin(), list.end(), std::mem_fn(&std::string::empty)));
    assert(!sep.empty());

    size_t size = 0;
    for (std::string_view l : list) {
        size += l.size();
    }
    // this allocates space for one sep more than needed, but it simplifies the for loop
    size += sep.size() * (list.size() - 1);

    std::string res;
    res.reserve(size);
    for (const std::string& l : list) {
        res.append(l);
        res.append(sep.data(), sep.size());
    }
    // Remove the last separator
    for (size_t i = 0; i < sep.size(); ++i) {
        res.pop_back();
    }
    return res;
}

std::string join(const std::vector<StackElement>& list, std::string_view sep) {
    assert(!sep.empty());

    std::vector<std::string_view> names;
    names.reserve(list.size());
    for (const StackElement& e : list) {
        if (e.type == StackElement::Type::Enum) {
            names.push_back(std::get<Enum>(e.payload).name);
        }
        if (e.type == StackElement::Type::Struct) {
            names.push_back(std::get<Struct>(e.payload).name);
        }
    }
    return join(names, sep);
}

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

std::string_view validCode(std::string_view code) {
    const size_t mainLocation = code.find(AttributeDictionary);
    if (mainLocation == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLocation + 1) != std::string_view::npos) {
        throw std::runtime_error(fmt::format(
            "We currently only support one struct per file annotated with {}, "
            "including commented out ones",
            AttributeDictionary
        ));
    }

    const size_t lastNewLine = code.rfind('\n', mainLocation) + 1;
    size_t cursor = code.find('{', lastNewLine) + 1;

    for (int counter = 1; counter > 0; cursor++) {
        if (code[cursor] == '{') {
            counter++;
        }
        if (code[cursor] == '}') {
            counter--;
        }
    }

    return code.substr(lastNewLine, cursor - lastNewLine + 1);
}
