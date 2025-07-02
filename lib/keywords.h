/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2025                                                               *
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

#ifndef __OPENSPACE_CODEGEN___KEYWORDS___H__
#define __OPENSPACE_CODEGEN___KEYWORDS___H__

#include <string_view>

namespace keywords {

constexpr std::string_view Verbatim = "verbatim";
constexpr std::string_view Dictionary = "Dictionary";
constexpr std::string_view Enum = "[[codegen::enum";
constexpr std::string_view Stringify = "[[codegen::stringify";
constexpr std::string_view Map = "[[codegen::map";
constexpr std::string_view LuaWrap = "[[codegen::luawrap";
constexpr std::string_view Arrayify = "[[codegen::arrayify";

} // namespace keywords

constexpr size_t findKeyword(std::string_view text, std::string_view keyword) {
    constexpr std::string_view Prefix = "[[codegen::";

    const size_t prefixIdx = text.find(Prefix);
    const size_t kwdIdx = text.find(keyword, prefixIdx);

    if (prefixIdx == std::string_view::npos || kwdIdx == std::string_view::npos) {
        // One of the components was not found
        return std::string_view::npos;
    }

    // We found the keyword if the prefix and the keyword follow each other directly
    const bool found = kwdIdx == (prefixIdx + Prefix.length());
    return found ? prefixIdx : std::string_view::npos;
}

#endif // __OPENSPACE_CODEGEN___KEYWORDS___H__
