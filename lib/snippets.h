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

#ifndef __OPENSPACE_CODEGEN___SNIPPETS___H__
#define __OPENSPACE_CODEGEN___SNIPPETS___H__

#include "types.h"
#include <string_view>

namespace {
    constexpr const char BakeFunctionVectorDeclaration[] = "template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);\n";
    constexpr const char BakeFunctionMapDeclaration[] = "template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val);\n";
    constexpr const char BakeFunctionOptionalDeclaration[] = "template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);\n";


    constexpr const char BakeFunctionPreamble[] = R"(
namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); } // This should never be called
)";

    constexpr const char DocumentationPreamble[] = R"(
namespace codegen {{
template <typename T> openspace::documentation::Documentation doc() {{
    static_assert(sizeof(T) == 0); // This should never be called
    return openspace::documentation::Documentation();
}}
template <> openspace::documentation::Documentation doc<{}>() {{
    using namespace openspace::documentation;

)";

    constexpr const char DocumentationEpilog[] = R"(
    openspace::documentation::Documentation d = {{ "{0}", "{0}", std::move(codegen_{1}->documentations) }};
    return d;
}}
}} // namespace codegen

)";

    constexpr const char FileHeader[] = R"(// This file has been auto-generated by the codegen tool
//
// Do not change this file manually as any change will be automatically overwritten,
// instead change the struct tagged with "codegen::Dictionary" in the main file from which
// the code in this file was generated.
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.
)";

    constexpr const char BakeFunctionOptional[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
    if (d.hasKey(key)) {
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }
    else {
        *val = std::nullopt;
    }
}
)";

    constexpr const char BakeFunctionVector[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    // For the moment we need to make sure in here that all of the keys are sequential
    // since our TableVerifier doesn't really do that and we don't have a VectorVerifier
    // for a flat list (yet).  So you might have gotten a specification error from here
    // iff the Dictionary that was passed in contained keys other than a linear sequence
    // from 1 - dict.size()  [1 because Lua for some strange reason wants to start at the
    // wrong number]

    for (size_t i = 1; i <= dict.size(); ++i) {
        std::string k = std::to_string(i);
        if (!dict.hasKey(k)) {
            throw std::runtime_error("Could not find key '" + k + "' in the dictionary");
        }
    }    

    for (size_t i = 1; i <= dict.size(); ++i) {
        T v;
        bakeTo(dict, std::to_string(i), &v);
        val->push_back(std::move(v));
    }
}
)";

    constexpr const char BakeFunctionMap[] = R"(
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    
    for (std::string_view k : dict.keys()) {
        T v;
        bakeTo(dict, k, &v);
        val->insert({ std::string(k), v });
    }
}
)";


} // namespace

std::string_view bakeFunctionForType(BasicType::Type type);
std::string vectorBakeFunctionForType(std::string_view type);
std::string_view variantConversionFunctionForType(std::string_view type);

#endif // __OPENSPACE_CODEGEN___SNIPPETS___H__
