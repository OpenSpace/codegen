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
    while (!sv.empty() && isspace(sv[0]) != 0) {
        sv.remove_prefix(1);
    }

    while (!sv.empty() && isspace(sv[sv.size() - 1]) != 0) {
        sv.remove_suffix(1);
    }

    return sv;
}

bool startsWith(std::string_view base, std::string_view test) {
    assert(!base.empty());
    assert(!test.empty());

    return base.size() >= test.size() && base.substr(0, test.size()) == test;
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
    assert(!code.empty());

    const size_t mainLoc = code.find(AttributeDictionary);
    if (mainLoc == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLoc + 1) != std::string_view::npos) {
        throw ParsingError(fmt::format(
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
            int beg = static_cast<int>(mainLoc) - 50;
            std::string_view sb = code.substr(
                static_cast<size_t>(std::max(0, beg)),
                std::min<size_t>(50, code.size() - 1)
            );
            throw ParsingError(fmt::format(
                "Could not find 'struct' before '[[codegen::Dictionary' before reaching "
                "the beginning of the file\n{}",
                sb
            ));
        }
    }

    std::string_view nameCheck = code.substr(cursor, mainLoc - cursor);
    assert(startsWith(nameCheck, "struct"));

    using namespace std::literals;
    nameCheck.remove_prefix(("struct"sv).size());
    for (char c : nameCheck) {
        if (::isspace(c) == 0) {
            throw SpecificationError(fmt::format(
                "Only 'struct' can appear directly before [[codegen::Dictionary\n{}",
                code.substr(0, std::min<size_t>(code.size(), 50))
            ));
        }
    }

    const size_t lastNewLine = static_cast<size_t>(cursor);
    
    cursor = code.find('{', lastNewLine) + 1;
    for (int counter = 1; counter > 0; cursor++) {
        if (cursor >= static_cast<int64_t>(code.size())) {
            throw ParsingError(fmt::format(
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
