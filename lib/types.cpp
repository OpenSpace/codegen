/*****************************************************************************************
 *                                                                                       *
 * OpenSpace Codegen                                                                     *
 *                                                                                       *
 * Copyright (c) 2021-2022                                                               *
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

#include "types.h"

#include <fmt/format.h>
#include "util.h"
#include <algorithm>
#include <cassert>
#include <functional>

namespace {
    std::string join(const std::vector<std::string_view>& list, std::string_view sep) {
        assert(
            std::none_of(list.begin(), list.end(), std::mem_fn(&std::string_view::empty))
        );
        assert(!sep.empty());

        size_t size = 0;
        for (std::string_view l : list) {
            size += l.size();
        }
        // this allocates space for one sep more than needed, but it simplifies the loop
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
} // namespace

CodegenError::CodegenError(std::string e) : std::runtime_error(std::move(e)) {}
CodegenError::operator std::string() const noexcept { return what(); }

bool operator==(const StackElement& lhs, const StackElement& rhs) {
    return lhs.type == rhs.type && lhs.name == rhs.name &&
           lhs.comment == rhs.comment && lhs.parent == rhs.parent;
}

bool operator==(const VariableType& lhs, const VariableType& rhs) {
    if (lhs.tag != rhs.tag) {
        return false;
    }

    using Tag = VariableType::Tag;

    switch (lhs.tag) {
        case Tag::BasicType:
            return static_cast<const BasicType&>(lhs) ==
                   static_cast<const BasicType&>(rhs);
        case Tag::MapType:
            return static_cast<const MapType&>(lhs) ==
                   static_cast<const MapType&>(rhs);
        case Tag::OptionalType:
            return static_cast<const OptionalType&>(lhs) ==
                   static_cast<const OptionalType&>(rhs);
        case Tag::VariantType:
            return static_cast<const VariantType&>(lhs) ==
                   static_cast<const VariantType&>(rhs);
        case Tag::TupleType:
            return static_cast<const TupleType&>(lhs) ==
                   static_cast<const TupleType&>(rhs);
        case Tag::VectorType:
            return static_cast<const VectorType&>(lhs) ==
                   static_cast<const VectorType&>(rhs);
        case Tag::CustomType:
            return static_cast<const CustomType&>(lhs) ==
                   static_cast<const CustomType&>(rhs);
    }
    throw std::logic_error("Missing case exception");
}

bool operator==(const BasicType& lhs, const BasicType& rhs) {
    return lhs.type == rhs.type;
}

bool operator==(const MapType& lhs, const MapType& rhs) {
    return (*lhs.keyType == *rhs.keyType) && (*lhs.valueType == *rhs.valueType);
}

bool operator==(const OptionalType& lhs, const OptionalType& rhs) {
    return *lhs.type == *rhs.type;
}

bool operator==(const VariantType& lhs, const VariantType& rhs) {
    if (lhs.types.size() != rhs.types.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.types.size(); ++i) {
        if (!(*lhs.types[i] == *rhs.types[i])) {
            return false;
        }
    }
    return true;
}

bool operator==(const TupleType& lhs, const TupleType& rhs) {
    if (lhs.types.size() != rhs.types.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.types.size(); ++i) {
        if (!(*lhs.types[i] == *rhs.types[i])) {
            return false;
        }
    }
    return true;
}

bool operator==(const CustomType& lhs, const CustomType& rhs) {
    return *lhs.type == *rhs.type;
}

bool operator==(const VectorType& lhs, const VectorType& rhs) {
    return *lhs.type == *rhs.type;
}

const Struct* rootStruct(const Struct* s) {
    assert(s);

    while (s->parent) {
        s = s->parent;
    }
    return s;
}

const StackElement* resolveType(const Struct* context, std::string_view type) {
    assert(context);
    assert(!type.empty());

    if (context->name == type) {
        return context;
    }

    // Check the children of the context first
    const auto it = std::find_if(
        context->children.cbegin(), context->children.cend(),
        [type](StackElement* e) { return e->name == type; }
    );
    if (it != context->children.end()) {
        return *it;
    }

    // Then check the parent
    if (context->parent) {
        const StackElement* s = resolveType(context->parent, type);
        if (s) {
            return s;
        }
    }

    // If we got this far, noone knew what to do with the type
    return nullptr;
}

std::string fqn(const StackElement* s, std::string_view separator) {
    assert(s);
    assert(!separator.empty());

    std::vector<std::string_view> names;
    names.push_back(s->name);
    while (s->parent) {
        s = s->parent;
        names.push_back(s->name);
    };
    std::reverse(names.begin(), names.end());

    assert(
        std::none_of(names.begin(), names.end(), std::mem_fn(&std::string_view::empty))
    );

    return join(names, separator);
}

VariableType* parseType(std::string_view type, Struct* context) {
    using namespace std::literals;

    if (type == "void") {
        return nullptr;
    }

    assert(!type.empty());

    if (type[type.size() - 1] == '&') {
        throw CodegenError(fmt::format("Illegal reference type found: {}", type));
    }
    if (type[type.size() - 1] == '*') {
        throw CodegenError(fmt::format("Illegal pointer type found: {}", type));
    }

    auto newType = [](BasicType::Type t) -> BasicType* {
        BasicType* bt = new BasicType;
        bt->tag = VariableType::Tag::BasicType;
        bt->type = t;
        return bt;
    };

    VariableType* t = nullptr;
    if (type == "bool")                       { t = newType(BasicType::Type::Bool); }
    else if (type == "int")                   { t = newType(BasicType::Type::Int); }
    else if (type == "double")                { t = newType(BasicType::Type::Double); }
    else if (type == "float")                 { t = newType(BasicType::Type::Float); }
    else if (type == "std::string")           { t = newType(BasicType::Type::String); }
    else if (type == "std::filesystem::path") { t = newType(BasicType::Type::Path); }
    else if (type == "glm::ivec2")            { t = newType(BasicType::Type::Ivec2); }
    else if (type == "glm::ivec3")            { t = newType(BasicType::Type::Ivec3); }
    else if (type == "glm::ivec4")            { t = newType(BasicType::Type::Ivec4); }
    else if (type == "glm::dvec2")            { t = newType(BasicType::Type::Dvec2); }
    else if (type == "glm::dvec3")            { t = newType(BasicType::Type::Dvec3); }
    else if (type == "glm::dvec4")            { t = newType(BasicType::Type::Dvec4); }
    else if (type == "glm::vec2")             { t = newType(BasicType::Type::Vec2); }
    else if (type == "glm::vec3")             { t = newType(BasicType::Type::Vec3); }
    else if (type == "glm::vec4")             { t = newType(BasicType::Type::Vec4); }
    else if (type == "glm::mat2x2")           { t = newType(BasicType::Type::Mat2x2); }
    else if (type == "glm::mat2")             { t = newType(BasicType::Type::Mat2x2); }
    else if (type == "glm::mat2x3")           { t = newType(BasicType::Type::Mat2x3); }
    else if (type == "glm::mat2x4")           { t = newType(BasicType::Type::Mat2x4); }
    else if (type == "glm::mat3x2")           { t = newType(BasicType::Type::Mat3x2); }
    else if (type == "glm::mat3x3")           { t = newType(BasicType::Type::Mat3x3); }
    else if (type == "glm::mat3")             { t = newType(BasicType::Type::Mat3x3); }
    else if (type == "glm::mat3x4")           { t = newType(BasicType::Type::Mat3x4); }
    else if (type == "glm::mat4x2")           { t = newType(BasicType::Type::Mat4x2); }
    else if (type == "glm::mat4x3")           { t = newType(BasicType::Type::Mat4x3); }
    else if (type == "glm::mat4x4")           { t = newType(BasicType::Type::Mat4x4); }
    else if (type == "glm::mat4")             { t = newType(BasicType::Type::Mat4x4); }
    else if (type == "glm::dmat2x2")          { t = newType(BasicType::Type::DMat2x2); }
    else if (type == "glm::dmat2")            { t = newType(BasicType::Type::DMat2x2); }
    else if (type == "glm::dmat2x3")          { t = newType(BasicType::Type::DMat2x3); }
    else if (type == "glm::dmat2x4")          { t = newType(BasicType::Type::DMat2x4); }
    else if (type == "glm::dmat3x2")          { t = newType(BasicType::Type::DMat3x2); }
    else if (type == "glm::dmat3x3")          { t = newType(BasicType::Type::DMat3x3); }
    else if (type == "glm::dmat3")            { t = newType(BasicType::Type::DMat3x3); }
    else if (type == "glm::dmat3x4")          { t = newType(BasicType::Type::DMat3x4); }
    else if (type == "glm::dmat4x2")          { t = newType(BasicType::Type::DMat4x2); }
    else if (type == "glm::dmat4x3")          { t = newType(BasicType::Type::DMat4x3); }
    else if (type == "glm::dmat4x4")          { t = newType(BasicType::Type::DMat4x4); }
    else if (type == "glm::dmat4")            { t = newType(BasicType::Type::DMat4x4); }
    else if (type == "ghoul::Dictionary")    { t = newType(BasicType::Type::Dictionary); }
    else if (startsWith(type, "std::vector<")) {
        type.remove_prefix("std::vector<"sv.size());
        type.remove_suffix(">"sv.size());

        VectorType* vt = new VectorType;
        vt->tag = VariableType::Tag::VectorType;
        vt->type = parseType(type, context);
        assert(vt->type);
        t = vt;
    }
    else if (startsWith(type, "std::optional<")) {
        type.remove_prefix("std::optional<"sv.size());
        type.remove_suffix(">"sv.size());

        OptionalType* op = new OptionalType;
        op->tag = VariableType::Tag::OptionalType;
        op->type = parseType(type, context);
        assert(op->type);
        t = op;
    }
    else if (startsWith(type, "std::map<")) {
        type.remove_prefix("std::map<"sv.size());

        std::vector<std::string_view> list = extractTemplateTypeList(type);
        assert(list.size() == 2);

        MapType* mp = new MapType;
        mp->tag = VariableType::Tag::MapType;
        mp->keyType = parseType(list[0], context);
        assert(mp->keyType);
        mp->valueType = parseType(list[1], context);
        assert(mp->valueType);

        // only strings are allowed for keys in maps right now
        const bool isValidKey =
            (mp->keyType->tag == VariableType::Tag::BasicType) &&
            (static_cast<BasicType*>(mp->keyType)->type == BasicType::Type::String);

        if (!isValidKey) {
            throw CodegenError(fmt::format(
                "Currently only std::string as key is supported\n{}", type
            ));
        }

        t = mp;
    }
    else if (startsWith(type, "std::variant<")) {
        type.remove_prefix("std::variant<"sv.size());

        std::vector<std::string_view> list = extractTemplateTypeList(type);

        VariantType* vt = new VariantType;
        vt->tag = VariableType::Tag::VariantType;

        for (std::string_view elem : list) {
            VariableType* t = parseType(elem, context);
            assert(t);
            vt->types.push_back(t);
        }

        // Check for multiple vector types
        int nVectorTypes = 0;
        for (VariableType* t : vt->types) {
            if (t->tag == VariableType::Tag::VectorType) {
                nVectorTypes += 1;
            }
        }
        if (nVectorTypes > 1) {
            throw CodegenError(fmt::format(
                "We can't have a variant containing multiple vector types, try a "
                "vector of variants instead\n{}", type
            ));
        }

        // Check for illegal types
        for (VariableType* t : vt->types) {
            const bool isBasicType = t->tag == VariableType::Tag::BasicType;
            const bool isVectorType = t->tag == VariableType::Tag::VectorType;
            const bool isEnum =
                t->tag == VariableType::Tag::CustomType &&
                static_cast<CustomType*>(t)->type->type == StackElement::Type::Enum;
            if (!isBasicType && !isVectorType && !isEnum) {
                throw CodegenError(fmt::format(
                    "Unsupported type '{}' found in variant list\n{}",
                    generateTypename(t), type
                ));
            }
        }

        t = vt;
    }
    else if (startsWith(type, "std::tuple<")) {
        type.remove_prefix("std::tuple<"sv.size());

        std::vector<std::string_view> list = extractTemplateTypeList(type);

        TupleType* tt = new TupleType;
        tt->tag = VariableType::Tag::TupleType;

        for (std::string_view elem : list) {
            VariableType* t = parseType(elem, context);
            assert(t);
            tt->types.push_back(t);
        }

        t = tt;
    }

    if (!t) {
        // We don't have a standard type, so 'type' must now be a struct or an enum
        // visible in the variable's context
        CustomType* ct = new CustomType;
        ct->tag = VariableType::Tag::CustomType;
        ct->name = std::string(type);
        if (context) {
            const StackElement* el = resolveType(context, type);
            if (!el) {
                throw CodegenError(fmt::format(
                    "Type detected that codegen doesn't know how to handle: {}", type
                ));
            }
            ct->type = el;
        }
        t = ct;
    }
    assert(t);
    return t;
}

std::string generateTypename(BasicType::Type type) {
    switch (type) {
        case BasicType::Type::Bool:    return "bool";
        case BasicType::Type::Int:     return "int";
        case BasicType::Type::Double:  return "double";
        case BasicType::Type::Float:   return "float";
        case BasicType::Type::String:  return "std::string";
        case BasicType::Type::Path:    return "std::filesystem::path";
        case BasicType::Type::Ivec2:   return "glm::ivec2";
        case BasicType::Type::Ivec3:   return "glm::ivec3";
        case BasicType::Type::Ivec4:   return "glm::ivec4";
        case BasicType::Type::Dvec2:   return "glm::dvec2";
        case BasicType::Type::Dvec3:   return "glm::dvec3";
        case BasicType::Type::Dvec4:   return "glm::dvec4";
        case BasicType::Type::Vec2:    return "glm::vec2";
        case BasicType::Type::Vec3:    return "glm::vec3";
        case BasicType::Type::Vec4:    return "glm::vec4";
        case BasicType::Type::Mat2x2:  return "glm::mat2x2";
        case BasicType::Type::Mat2x3:  return "glm::mat2x3";
        case BasicType::Type::Mat2x4:  return "glm::mat2x4";
        case BasicType::Type::Mat3x2:  return "glm::mat3x2";
        case BasicType::Type::Mat3x3:  return "glm::mat3x3";
        case BasicType::Type::Mat3x4:  return "glm::mat3x4";
        case BasicType::Type::Mat4x2:  return "glm::mat4x2";
        case BasicType::Type::Mat4x3:  return "glm::mat4x3";
        case BasicType::Type::Mat4x4:  return "glm::mat4x4";
        case BasicType::Type::DMat2x2: return "glm::dmat2x2";
        case BasicType::Type::DMat2x3: return "glm::dmat2x3";
        case BasicType::Type::DMat2x4: return "glm::dmat2x4";
        case BasicType::Type::DMat3x2: return "glm::dmat3x2";
        case BasicType::Type::DMat3x3: return "glm::dmat3x3";
        case BasicType::Type::DMat3x4: return "glm::dmat3x4";
        case BasicType::Type::DMat4x2: return "glm::dmat4x2";
        case BasicType::Type::DMat4x3: return "glm::dmat4x3";
        case BasicType::Type::DMat4x4: return "glm::dmat4x4";
        case BasicType::Type::Dictionary: return "ghoul::Dictionary";
    }

    throw std::logic_error("Missing case label");
}

std::string generateDescriptiveTypename(BasicType::Type type) {
    switch (type) {
        case BasicType::Type::Bool:       return "Boolean";
        case BasicType::Type::Int:        return "Integer";
        case BasicType::Type::Double:     return "Number";
        case BasicType::Type::Float:      return "Number";
        case BasicType::Type::String:     return "String";
        case BasicType::Type::Path:       return "Path";
        case BasicType::Type::Ivec2:      return "ivec2";
        case BasicType::Type::Ivec3:      return "ivec3";
        case BasicType::Type::Ivec4:      return "ivec4";
        case BasicType::Type::Dvec2:      return "vec2";
        case BasicType::Type::Dvec3:      return "vec3";
        case BasicType::Type::Dvec4:      return "vec4";
        case BasicType::Type::Vec2:       return "vec2";
        case BasicType::Type::Vec3:       return "vec3";
        case BasicType::Type::Vec4:       return "vec4";
        case BasicType::Type::Mat2x2:     return "mat2x2";
        case BasicType::Type::Mat2x3:     return "mat2x3";
        case BasicType::Type::Mat2x4:     return "mat2x4";
        case BasicType::Type::Mat3x2:     return "mat3x2";
        case BasicType::Type::Mat3x3:     return "mat3x3";
        case BasicType::Type::Mat3x4:     return "mat3x4";
        case BasicType::Type::Mat4x2:     return "mat4x2";
        case BasicType::Type::Mat4x3:     return "mat4x3";
        case BasicType::Type::Mat4x4:     return "mat4x4";
        case BasicType::Type::DMat2x2:    return "mat2x2";
        case BasicType::Type::DMat2x3:    return "mat2x3";
        case BasicType::Type::DMat2x4:    return "mat2x4";
        case BasicType::Type::DMat3x2:    return "mat3x2";
        case BasicType::Type::DMat3x3:    return "mat3x3";
        case BasicType::Type::DMat3x4:    return "mat3x4";
        case BasicType::Type::DMat4x2:    return "mat4x2";
        case BasicType::Type::DMat4x3:    return "mat4x3";
        case BasicType::Type::DMat4x4:    return "mat4x4";
        case BasicType::Type::Dictionary: return "Table";
    }

    throw std::logic_error("Missing case label");
}

std::string generateTypename(const BasicType* type) {
    return generateTypename(type->type);
}

std::string generateDescriptiveTypename(const BasicType* type) {
    return generateDescriptiveTypename(type->type);
}

std::string generateTypename(const MapType* type, bool fullyQualified) {
    std::string t1 = generateTypename(type->keyType, fullyQualified);
    std::string t2 = generateTypename(type->valueType, fullyQualified);
    return fmt::format("std::map<{}, {}>", t1, t2);
}

std::string generateDescriptiveTypename(const MapType* type) {
    std::string t1 = generateDescriptiveTypename(type->keyType);
    std::string t2 = generateDescriptiveTypename(type->valueType);
    return fmt::format("{} -> {}", t1, t2);
}

std::string generateTypename(const OptionalType* type, bool fullyQualified) {
    std::string t1 = generateTypename(type->type, fullyQualified);
    return fmt::format("std::optional<{}>", t1);
}

std::string generateDescriptiveTypename(const OptionalType* type) {
    std::string t1 = generateDescriptiveTypename(type->type);
    return fmt::format("{}?", t1);
}

std::string generateTypename(const VariantType* type, bool fullyQualified) {
    std::string res = "std::variant<";
    for (VariableType* v : type->types) {
        res += generateTypename(v, fullyQualified);
        res += ", ";
    }
    
    res.pop_back();   // Remove the final ' '
    res.back() = '>'; // Replace the final , with the >

    return res;
}

std::string generateDescriptiveTypename(const VariantType* type) {
    std::string res;
    for (size_t i = 0; i < type->types.size(); i += 1) {
        res += generateDescriptiveTypename(type->types[i]);

        if (i != type->types.size() - 1) {
            res += " | ";
        }
    }
    return res;
}

std::string generateTypename(const TupleType* type, bool fullyQualified) {
    std::string res = "std::tuple<";
    for (VariableType* v : type->types) {
        res += generateTypename(v, fullyQualified);
        res += ", ";
    }

    res.pop_back();   // Remove the final ' '
    res.back() = '>'; // Replace the final , with the >

    return res;
}

std::string generateDescriptiveTypename(const TupleType* type) {
    std::string res;
    for (size_t i = 0; i < type->types.size(); i += 1) {
        res += generateDescriptiveTypename(type->types[i]);

        if (i != type->types.size() - 1) {
            res += ", ";
        }
    }
    return res;
}

std::string generateTypename(const VectorType* type, bool fullyQualified) {
    std::string t1 = generateTypename(type->type, fullyQualified);
    return fmt::format("std::vector<{}>", t1);
}

std::string generateDescriptiveTypename(const VectorType* type) {
    return "[" + generateDescriptiveTypename(type->type) + "]";
}

std::string generateTypename(const CustomType* type, bool fullyQualified) {
    if (fullyQualified) {
        return fqn(type->type, "::");
    }
    else {
        return type->type->name;
    }
}

std::string generateDescriptiveTypename(const CustomType* type) {
    return type->type->name;
}

std::string generateTypename(const VariableType* type, bool fullyQualified) {
    assert(type);

    const bool fq = fullyQualified;
    switch (type->tag) {
        case VariableType::Tag::BasicType:
            return generateTypename(static_cast<const BasicType*>(type));
        case VariableType::Tag::MapType:
            return generateTypename(static_cast<const MapType*>(type), fq);
        case VariableType::Tag::OptionalType:
            return generateTypename(static_cast<const OptionalType*>(type), fq);
        case VariableType::Tag::VariantType:
            return generateTypename(static_cast<const VariantType*>(type), fq);
        case VariableType::Tag::TupleType:
            return generateTypename(static_cast<const TupleType*>(type), fq);
        case VariableType::Tag::VectorType:
            return generateTypename(static_cast<const VectorType*>(type), fq);
        case VariableType::Tag::CustomType:
            return generateTypename(static_cast<const CustomType*>(type), fq);
    }
    throw std::logic_error("Missing case label");
}

std::string generateDescriptiveTypename(const VariableType* type) {
    assert(type);

    switch (type->tag) {
    case VariableType::Tag::BasicType:
        return generateDescriptiveTypename(static_cast<const BasicType*>(type));
    case VariableType::Tag::MapType:
        return generateDescriptiveTypename(static_cast<const MapType*>(type));
    case VariableType::Tag::OptionalType:
        return generateDescriptiveTypename(static_cast<const OptionalType*>(type));
    case VariableType::Tag::VariantType:
        return generateDescriptiveTypename(static_cast<const VariantType*>(type));
    case VariableType::Tag::TupleType:
        return generateDescriptiveTypename(static_cast<const TupleType*>(type));
    case VariableType::Tag::VectorType:
        return generateDescriptiveTypename(static_cast<const VectorType*>(type));
    case VariableType::Tag::CustomType:
        return generateDescriptiveTypename(static_cast<const CustomType*>(type));
    }
    throw std::logic_error("Missing case label");
}

