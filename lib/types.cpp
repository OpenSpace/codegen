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

#include "types.h"

#include <fmt/format.h>
#include "util.h"
#include <algorithm>
#include <cassert>
#include <functional>

bool operator==(const StackElement& lhs, const StackElement& rhs) {
    return
        lhs.type == rhs.type &&
        lhs.name == rhs.name &&
        lhs.comment == rhs.comment &&
        lhs.parent == rhs.parent;
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

    auto newBasicType = [](BasicType::Type t) -> BasicType* {
        BasicType* bt = new BasicType;
        bt->tag = VariableType::Tag::BasicType;
        bt->type = t;
        return bt;
    };

    VariableType* t = nullptr;

    if (type == "bool")                {  t = newBasicType(BasicType::Type::Bool); }
    else if (type == "int")            { t = newBasicType(BasicType::Type::Int); }
    else if (type == "double")         { t = newBasicType(BasicType::Type::Double); }
    else if (type == "float")          { t = newBasicType(BasicType::Type::Float); }
    else if (type == "std::string")    { t = newBasicType(BasicType::Type::String); }
    else if (type == "glm::ivec2")     { t = newBasicType(BasicType::Type::Ivec2); }
    else if (type == "glm::ivec3")     { t = newBasicType(BasicType::Type::Ivec3); }
    else if (type == "glm::ivec4")     { t = newBasicType(BasicType::Type::Ivec4); }
    else if (type == "glm::dvec2")     { t = newBasicType(BasicType::Type::Dvec2); }
    else if (type == "glm::dvec3")     { t = newBasicType(BasicType::Type::Dvec3); }
    else if (type == "glm::dvec4")     { t = newBasicType(BasicType::Type::Dvec4); }
    else if (type == "glm::vec2")      { t = newBasicType(BasicType::Type::Vec2); }
    else if (type == "glm::vec3")      { t = newBasicType(BasicType::Type::Vec3); }
    else if (type == "glm::vec4")      { t = newBasicType(BasicType::Type::Vec4); }
    else if (type == "glm::mat2x2")    { t = newBasicType(BasicType::Type::Mat2x2); }
    else if (type == "glm::mat2x3")    { t = newBasicType(BasicType::Type::Mat2x3); }
    else if (type == "glm::mat2x4")    { t = newBasicType(BasicType::Type::Mat2x4); }
    else if (type == "glm::mat3x2")    { t = newBasicType(BasicType::Type::Mat3x2); }
    else if (type == "glm::mat3x3")    { t = newBasicType(BasicType::Type::Mat3x3); }
    else if (type == "glm::mat3x4")    { t = newBasicType(BasicType::Type::Mat3x4); }
    else if (type == "glm::mat4x2")    { t = newBasicType(BasicType::Type::Mat4x2); }
    else if (type == "glm::mat4x3")    { t = newBasicType(BasicType::Type::Mat4x3); }
    else if (type == "glm::mat4x4")    { t = newBasicType(BasicType::Type::Mat4x4);}
    else if (type == "glm::dmat2x2")   { t = newBasicType(BasicType::Type::DMat2x2); }
    else if (type == "glm::dmat2x3")   { t = newBasicType(BasicType::Type::DMat2x3); }
    else if (type == "glm::dmat2x4")   { t = newBasicType(BasicType::Type::DMat2x4); }
    else if (type == "glm::dmat3x2")   { t = newBasicType(BasicType::Type::DMat3x2); }
    else if (type == "glm::dmat3x3")   { t = newBasicType(BasicType::Type::DMat3x3); }
    else if (type == "glm::dmat3x4")   { t = newBasicType(BasicType::Type::DMat3x4); }
    else if (type == "glm::dmat4x2")   { t = newBasicType(BasicType::Type::DMat4x2); }
    else if (type == "glm::dmat4x3")   { t = newBasicType(BasicType::Type::DMat4x3); }
    else if (type == "glm::dmat4x4")   { t = newBasicType(BasicType::Type::DMat4x4); }
    else if (type == "std::monostate") { t = newBasicType(BasicType::Type::Monostate); }
    else if (startsWith(type, "std::vector<")) {
        type.remove_prefix("std::vector<"sv.size());
        type.remove_suffix(">"sv.size());

        VectorType* vt = new VectorType;
        vt->tag = VariableType::Tag::VectorType;
        vt->type = parseType(type, context);
        t = vt;
    }
    else if (startsWith(type, "std::optional<")) {
        type.remove_prefix("std::optional<"sv.size());
        type.remove_suffix(">"sv.size());

        OptionalType* op = new OptionalType;
        op->tag = VariableType::Tag::OptionalType;
        op->type = parseType(type, context);
        t = op;
    }
    else if (startsWith(type, "std::map<")) {
        type.remove_prefix("std::map<"sv.size());
        //type.remove_suffix(">"sv.size());

        std::vector<std::string_view> list = extractTemplateTypeList(type);
        assert(list.size() == 2);

        MapType* mp = new MapType;
        mp->tag = VariableType::Tag::MapType;
        mp->keyType = parseType(list[0], context);
        mp->valueType = parseType(list[1], context);

        // For now, we just want to support std::map<std::string, std::string>
        if ((mp->keyType->tag == VariableType::Tag::BasicType) &&
            (static_cast<BasicType*>(mp->keyType)->type != BasicType::Type::String) &&
            (mp->valueType->tag == VariableType::Tag::BasicType) &&
            (static_cast<BasicType*>(mp->valueType)->type != BasicType::Type::String))
        {
            throw SpecificationError(fmt::format(
                "Currently only std:map<std::string, std::string> is supported\n{}", type
            ));
        }

        t = mp;
    }
    else if (startsWith(type, "std::variant<")) {
        type.remove_prefix("std::variant<"sv.size());
        //type.remove_suffix(">"sv.size());

        std::vector<std::string_view> list = extractTemplateTypeList(type);

        VariantType* vt = new VariantType;
        vt->tag = VariableType::Tag::VariantType;
        
        for (std::string_view elem : list) {
            VariableType* t = parseType(elem, context);
            vt->types.push_back(t);
        }
        t = vt;
    }

    if (!t) {
        // We don't have a standard type, so 'type' must now be a struct or an enum
        // visible in the variable's context

        const StackElement* el = resolveType(context, type);
        if (!el) {
            throw ParsingError(fmt::format(
                "Type detected that codegen doesn't know how to handle: {}", type
            ));
        }
        CustomType* ct = new CustomType;
        ct->tag = VariableType::Tag::CustomType;
        ct->type = el;
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
        case BasicType::Type::Monostate: return "std::monostate";
    }

    throw std::logic_error("Missing case label");
}

std::string generateTypename(const BasicType* type) {
    return generateTypename(type->type);
}

std::string generateTypename(const MapType* type) {
    std::string t1 = generateTypename(type->keyType);
    std::string t2 = generateTypename(type->valueType);
    return fmt::format("std::map<{}, {}>", t1, t2);
}

std::string generateTypename(const OptionalType* type) {
    std::string t1 = generateTypename(type->type);
    return fmt::format("std::optional<{}>", t1);
}

std::string generateTypename(const VariantType* type) {
    std::string res = "std::variant<";
    for (VariableType* v : type->types) {
        res += generateTypename(v);
        res += ", ";
    }
    
    res.pop_back();   // Remove the final ' '
    res.back() = '>'; // Replace the final , with the >

    return res;
}

std::string generateTypename(const VectorType* type) {
    std::string t1 = generateTypename(type->type);
    return fmt::format("std::vector<{}>", t1);
}

std::string generateTypename(const CustomType* type) {
    return type->type->name;
}

std::string generateTypename(const VariableType* type) {
    switch (type->tag) {
        case VariableType::Tag::BasicType:
            return generateTypename(static_cast<const BasicType*>(type));
        case VariableType::Tag::MapType:
            return generateTypename(static_cast<const MapType*>(type));
        case VariableType::Tag::OptionalType:
            return generateTypename(static_cast<const OptionalType*>(type));
        case VariableType::Tag::VariantType:
            return generateTypename(static_cast<const VariantType*>(type));
        case VariableType::Tag::VectorType:
            return generateTypename(static_cast<const VectorType*>(type));
        case VariableType::Tag::CustomType:
            return generateTypename(static_cast<const CustomType*>(type));
    }
    throw std::logic_error("Missing case label");
}
