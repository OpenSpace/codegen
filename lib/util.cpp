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

std::vector<std::string_view> extractTemplateTypeList(std::string_view types) {
    assert(!types.empty());

    std::vector<std::string_view> res;

    size_t base = 0;
    size_t cursor = 0;
    size_t nBrackets = 1;
    do {
        cursor++;

        if (types[cursor] == '<') {
            nBrackets += 1;
        }

        if (types[cursor] == '>') {
            nBrackets -= 1;
        }

        if (types[cursor] == ',' || ((types[cursor] == '>') && (nBrackets == 0))) {
            std::string_view subtype = types.substr(base, cursor - base);
            res.push_back(strip(subtype));
            base = cursor + 1;
        }
    } while (nBrackets > 0);

    return res;
}
