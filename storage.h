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

#ifndef __OPENSPACE_CODEGEN___STORAGE___H__
#define __OPENSPACE_CODEGEN___STORAGE___H__

#include <atomic>
#include <thread>
#include <vector>

constexpr const int BufferSize = 32768;


inline thread_local char* VerifierResultBase = nullptr;
inline thread_local char* VerifierResult = nullptr;

inline thread_local char* ConverterResultBase = nullptr;
inline thread_local char* ConverterResult = nullptr;

inline thread_local char* ScratchSpaceBase = nullptr;
inline thread_local char* ScratchSpace = nullptr;

struct Memory {
    // Key
    std::thread::id id;

    // Value
    char* VerifierResult = nullptr;
    char* ConverterResult = nullptr;
    char* ScratchSpace = nullptr;
};

inline std::vector<Memory> MemoryPool;

inline std::atomic_int ChangedFiles = 0;
inline std::atomic_int AllFiles = 0;


#endif // __OPENSPACE_CODEGEN___STORAGE___H__
