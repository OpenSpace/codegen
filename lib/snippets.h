/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2023                                                               *
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
    constexpr std::string_view BakeFunctionVectorDeclaration = "template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);\n";
    constexpr std::string_view BakeFunctionMapDeclaration = "template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val);\n";
    constexpr std::string_view BakeFunctionOptionalDeclaration = "template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);\n";

    constexpr std::string_view BackFunctionFallback = "template<typename T> [[maybe_unused]] T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }";
    constexpr std::string_view BakeToFunctionFallback = "template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }";
    constexpr std::string_view MapFunctionFallback = "template<typename T, typename U> [[maybe_unused]] T map(U) { static_assert(sizeof(T) == 0); }";
    constexpr std::string_view DocumentationFallback = R"(template<typename T> [[maybe_unused]] openspace::documentation::Documentation doc(std::string, [[maybe_unused]] openspace::documentation::Documentation parentDoc = openspace::documentation::Documentation()) {
    static_assert(sizeof(T) == 0);
    return openspace::documentation::Documentation();
}
)";
    
    constexpr std::string_view ToStringFallback = "template<typename T> [[maybe_unused]] std::string_view toString(T) { static_assert(sizeof(T) == 0); return \"\"; }";
    constexpr std::string_view FromStringFallback = "template<typename T> [[maybe_unused]] T fromString(std::string_view) { static_assert(sizeof(T) == 0); return T(); }";

    constexpr std::string_view BakeEnumFallback = "template<typename T> [[maybe_unused]] T bake(std::string_view) { static_assert(sizeof(T) == 0); return T(); }";

    constexpr std::string_view BakeStructPreamble = R"(
template <> [[maybe_unused]] {0} bake<{0}>(const ghoul::Dictionary& dict) {{
    openspace::documentation::testSpecificationAndThrow(codegen::doc<{0}>("{0}"), dict, "{1}");
    {0} res;
)";

    constexpr std::string_view BakeEnum = R"(
template <> [[maybe_unused]] {0} bake<{0}>(std::string_view value) {{
    return fromString<{0}>(value);
}}
)";

    constexpr std::string_view BakeCustomMapDeclaration = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::map<std::string, U>& v);
)";

    constexpr std::string_view BakeCustomOptionalDeclaration = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::optional<U>& v);
)";

    constexpr std::string_view BakeCustomVectorDeclaration = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::vector<U>& v);
)";

    constexpr std::string_view BakeCustomMap = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::map<std::string, U>& v) {
    T res;
    for (auto [k, v] : v) {
        typename T::mapped_type r = bake<typename T::mapped_type>(std::move(v));
        res[std::move(k)] = r;
    }
    return res;
}
)";

    constexpr std::string_view BakeCustomOptional = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::optional<U>& v) {
    if (v.has_value()) {
        return bake<typename T::value_type>(*v);
    }
    else {
        return std::nullopt;
    }
}
)";

    constexpr std::string_view BakeCustomVector = R"(
template <typename T, typename U> [[maybe_unused]] T bake(const std::vector<U>& v) {
    T res;
    res.reserve(v.size());
    for (const U& d : v) {
        typename T::value_type r = bake<typename T::value_type>(d);
        res.push_back(r);
    }
    return res;
}
)";

    constexpr std::string_view DocumentationPreamble = R"(
template <> [[maybe_unused]] openspace::documentation::Documentation doc<{}>(std::string id, openspace::documentation::Documentation parentDoc) {{
    using namespace openspace::documentation;

)";

    constexpr std::string_view DocumentationEpilog = R"(
    openspace::documentation::Documentation d = {{ "{0}", std::move(id), std::move(codegen_{1}->documentations) }};
    
    // Move the entries from the parent doc into this one
    d.entries.insert(d.entries.begin(), parentDoc.entries.begin(), parentDoc.entries.end());

    return d;
}}

)";

    constexpr std::string_view LuaWrapperPreamble = "static const openspace::scripting::LuaLibrary::Function {} = {{\n";

    constexpr std::string_view LuaWrapperOptionalTypeExtraction = R"(
        {0} {1};
        if (ghoul::lua::hasValue<{2}>(L)) {{
            {1} = ghoul::lua::value<{2}>(L);
        }}
)";

    constexpr std::string_view LuaWrapperPushTupleOptional = R"(
            if (std::get<{0}>(res).has_value()) {{
                ghoul::lua::push(L, *std::get<{0}>(res));
                nArguments++;
            }}
)";

    constexpr std::string_view LuaWrapperPushTupleRegular = R"(
            ghoul::lua::push(L, std::get<{}>(res));
            nArguments++;
)";

    constexpr std::string_view LuaWrapperPushOptional = R"(
            if (res.has_value()) {
                ghoul::lua::push(L, std::move(*res));
                return 1;
            }
            else {
                return 0;
            }
)";

    constexpr std::string_view LuaWrapperPushVariant = R"(
            if (std::holds_alternative<{0}>(res)) {{
                ghoul::lua::push(L, std::move(std::get<{0}>(res)));
            }}
)";

    constexpr std::string_view FileHeader = R"(// This file has been auto-generated by the codegen tool
//
// Under **no** circumstances change this file manually as any change will be
// automatically overwritten. Instead change the struct tagged with "codegen::Dictionary"
// or the enum class tagged with "codegen::stringify" in the main file from which he code
// in this file was generated.
//
// If a compiler error brought you into this file, a struct tagged with
// "codegen::Dictionary" or an enum class tagged with "codegen::stringify" was changed
// without the codegen tool being run again.

)";

    constexpr std::string_view BakeFunctionOptional = R"(
template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
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

    constexpr std::string_view BakeFunctionVector = R"(
template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {
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

    constexpr std::string_view BakeFunctionMap = R"(
template<typename T> [[maybe_unused]] void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val) {
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
std::string enumBakeFunctionForType(std::string_view type);
std::string_view variantConversionFunctionForType(std::string_view type);

std::string enumToEnumMapping(Enum* e);

#endif // __OPENSPACE_CODEGEN___SNIPPETS___H__
