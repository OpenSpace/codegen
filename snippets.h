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

#include <string_view>

namespace {
    constexpr const char BakeFunctionVectorDeclaration[] = "template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);\n";
    constexpr const char BakeFunctionOptionalDeclaration[] = "template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);\n";


    constexpr const char BakeFunctionPreamble[] = R"(
namespace codegen {{
namespace internal {{
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) {{ static_assert(sizeof(T) == 0); }} // This should never be called
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
    delete codegen_{1};
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

} // namespace

std::string_view bakeFunctionForType(std::string_view type);

#endif // __OPENSPACE_CODEGEN___SNIPPETS___H__