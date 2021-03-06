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

#include "codegen.h"
#include "parsing.h"
#include "settings.h"
#include "snippets.h"
#include "types.h"
#include "util.h"
#include "verifier.h"

#include <fmt/format.h>
#include <array>
#include <filesystem>
#include <iostream>

// TODO
//   - Check for extra keys in the bake function to protect against misspellings
//   - Name used for ReferencingVerifier has to be generated in a better way (including
//     some more information to disambiguate)
//   - Add support for glm::uvecX

long long totalTime = 0;
int ChangedFiles = 0;
int AllFiles = 0;

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr <<
            "Wrong number of parameters. Expected at least 2.\nUsage: codegen <folder>\n";
        exit(EXIT_FAILURE);
    }


    std::cout << fmt::format("codegen");
    std::vector<std::string_view> srcs;
    for (int i = 1; i < argc; ++i) {
        std::string_view src = argv[i];
        std::cout << " " << src;

        if (!fs::is_directory(src)) {
            std::cerr << fmt::format(
                "All parameters has to name a folder. '{}' is not\n", src
            );
            exit(EXIT_FAILURE);
        }

        srcs.push_back(src);
    }
    std::cout << '\n';

    auto beg = std::chrono::high_resolution_clock::now();

    std::vector<fs::directory_entry> entries;
    std::string extFolder = fmt::format(
        "{0}ext{0}", static_cast<char>(std::filesystem::path::preferred_separator)
    );
    for (std::string_view src : srcs) {
        for (const fs::directory_entry& p : fs::recursive_directory_iterator(src)) {
            std::filesystem::path path = p.path();

            if (path.extension() == ".cpp" &&
                path.string().find("_codegen.cpp") == std::string::npos &&
                path.string().find(extFolder) == std::string::npos)
            {
                entries.push_back(p);
            }
        }
    }

    std::for_each(
        entries.cbegin(), entries.cend(),
        [](const fs::directory_entry& p) {
            try {
                auto begin = std::chrono::high_resolution_clock::now();
                Result res = handleFile(p.path());
                auto end = std::chrono::high_resolution_clock::now();
                if (res == Result::Processed) {
                    ChangedFiles++;
                    totalTime += (end - begin).count();
                }
                if (res != Result::Skipped) {
                    AllFiles++;
                }
            }
            catch (const std::runtime_error& e) {
                std::cerr << fmt::format(
                    "\n\n{}: error: {}\n\n\n", p.path().string(), e.what()
                );
                exit(EXIT_FAILURE);
            }
        }
    );

    auto end = std::chrono::high_resolution_clock::now();
    const double ms = (end - beg).count() / 1000000.0;

    if (PrintTiming) {
        std::cout << fmt::format(
            "{}/{} files changed in {} ms.  Pure time in codegen: {} ms\n",
            ChangedFiles, AllFiles, ms, totalTime / 1000000.0
        );
    }
    else {
        std::cout << fmt::format("{}/{} files changed\n", ChangedFiles, AllFiles);
    }
}
