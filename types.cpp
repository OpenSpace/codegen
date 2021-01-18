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

#include "util.h"
#include <algorithm>
#include <cassert>
#include <functional>

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
        context->children.begin(), context->children.end(),
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