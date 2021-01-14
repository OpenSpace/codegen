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

#ifndef __OPENSPACE_CODEGEN___UTIL___H__
#define __OPENSPACE_CODEGEN___UTIL___H__

#include "types.h"
#include <mutex>
#include <string_view>
#include <vector>

inline std::mutex consoleMutex;
template <typename... Ts>
void print(const char format[], Ts... ts) {
    std::unique_lock lk(consoleMutex);
    printf(format, ts...);
}

[[nodiscard]] std::string_view strip(std::string_view sv);
[[nodiscard]] bool startsWith(std::string_view lhs, std::string_view rhs);
[[nodiscard]] std::string join(const std::vector<std::string_view>& list, std::string_view sep);
[[nodiscard]] std::string join(const std::vector<std::string>& list, std::string_view sep);
[[nodiscard]] std::string join(const std::vector<StackElement>& list, std::string_view sep);
[[nodiscard]] std::string_view extractLine(std::string_view sv, size_t* cursor);

[[nodiscard]] std::string_view validCode(std::string_view code);

#endif // __OPENSPACE_CODEGEN___UTIL___H__
