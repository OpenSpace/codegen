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
//   - Need support for a std::map?
//   - Name used for ReferencingVerifier has to be generated in a better way (including
//     some more information to disambiguate)

#ifdef WIN32
//#define USE_MULTITHREADED_GENERATION
#include <execution>
#endif // WIN32

long long totalTime = 0;
std::atomic_int ChangedFiles = 0;
std::atomic_int AllFiles = 0;

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr <<
            "Wrong number of parameters. Expected 3.\n"
            "Usage: codegen --file <file>\n"
            "       codegen --folder <folder>";
        exit(EXIT_FAILURE);
    }

    std::string_view type = argv[1];
    std::string_view src = argv[2];
    if (type == "--file") {
        try {
            Result r = handleFile(src);
            switch (r) {
                case Result::NotProcessed: std::cout << "Not processed\n"; break;
                case Result::Processed: std::cout << "Processed\n"; break;
                case Result::Skipped: std::cout << "Skipped\n"; break;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }
    else if (type == "--folder") {
        namespace fs = std::filesystem;
        if (!fs::is_directory(src)) {
            std::cerr << "When using --folder, the second parameter has to name a folder";
            exit(EXIT_FAILURE);
        }

        auto beg = std::chrono::high_resolution_clock::now();

        std::vector<fs::directory_entry> entries;
        std::string extFolder = fmt::format(
            "{0}ext{0}", static_cast<char>(std::filesystem::path::preferred_separator)
        );
        for (const fs::directory_entry& p : fs::recursive_directory_iterator(src)) {
            std::filesystem::path path = p.path();

            if (path.extension() == ".cpp" &&
                path.string().find("_codegen") == std::string::npos &&
                path.string().find(extFolder) == std::string::npos)
            {
                entries.push_back(p);
            }
        }



        std::for_each(
#ifdef USE_MULTITHREADED_GENERATION
            std::execution::par_unseq,
#endif // USE_MULTITHREADED_GENERATION
            entries.begin(), entries.end(),
            [](const fs::directory_entry& p) {
                try {
                    auto b = std::chrono::high_resolution_clock::now();
                    Result res = handleFile(p.path());
                    auto e = std::chrono::high_resolution_clock::now();
                    if (res == Result::Processed) {
                        ChangedFiles++;
                        totalTime += (e - b).count();
                    }
                    if (res != Result::Skipped) {
                        AllFiles++;
                    }
                }
                catch (const std::runtime_error& e) {
                    print("%s: %s\n", p.path().string().c_str(), e.what());
                    exit(EXIT_FAILURE);
                }
            }
        );

        auto end = std::chrono::high_resolution_clock::now();
        const double ms = (end - beg).count() / 1000000.0;

        const int nChangedFiles = ChangedFiles.load();
        const int nAllFiles = AllFiles.load();

        if (AlwaysOutputFiles) {
            if (PrintTiming) {
                std::cout << fmt::format(
                    "Force overwrite all files in {} ms.  Pure time in codegen: {} ms",
                    ms, totalTime / 1000000.0
                );
            }
            else {
                std::cout << "Force overwrite all files\n";
            }
        }
        else {
            if (PrintTiming) {
                std::cout << fmt::format(
                    "{}/{} files changed in {} ms.  Pure time in codegen: {} ms\n",
                    nChangedFiles, nAllFiles, ms, totalTime / 1000000.0
                );
            }
            else {
                std::cout << fmt::format(
                    "{}/{} files changed\n", nChangedFiles, nAllFiles
                );
            }
        }
    }
    else {
        std::cerr << fmt::format(
            "Unrecognized argument '{}'. Expected '--file' or '--folder'\n", type
        );
        exit(EXIT_FAILURE);
    }
}
