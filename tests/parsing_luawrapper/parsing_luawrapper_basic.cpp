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

#include "catch2/catch.hpp"

#include "codegen.h"
#include "parsing.h"
#include "types.h"

TEST_CASE("Parsing LuaWrapper: No Arguments", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void foo() {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);
}

TEST_CASE("Parsing LuaWrapper: 1 Argument", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void foo(int arg) {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 1);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg");
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = dynamic_cast<BasicType*>(v->type);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::Int);
    }
}

TEST_CASE("Parsing LuaWrapper: 2 Arguments", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void foo(int arg1, std::string arg2) {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 2);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg1");
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = dynamic_cast<BasicType*>(v->type);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* v = f->arguments[1];
        REQUIRE(v);
        CHECK(v->name == "arg2");
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = dynamic_cast<BasicType*>(v->type);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::String);
    }
}

TEST_CASE("Parsing LuaWrapper: 2 Arguments (optional)", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] void foo(int arg1, std::optional<double> arg2) {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 2);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg1");
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = dynamic_cast<BasicType*>(v->type);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* v = f->arguments[1];
        REQUIRE(v);
        CHECK(v->name == "arg2");
        REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = dynamic_cast<OptionalType*>(v->type);
        REQUIRE(ot);
        REQUIRE(ot->type);
        BasicType* bt = dynamic_cast<BasicType*>(ot->type);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::Double);
    }

}

TEST_CASE("Parsing LuaWrapper: Return value", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] int foo() {
        return 1;
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::BasicType);
        BasicType* bt = dynamic_cast<BasicType*>(ret);
        REQUIRE(bt);
        CHECK(bt->type == BasicType::Type::Int);
    }
}

TEST_CASE("Parsing LuaWrapper: No Arguments, Multiple return values", "[luawrapper][parsing]") {
    constexpr const char Source[] = R"(
    [[codegen::wraplua]] std::tuple<int, double> foo() {
    }
};
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions[0];
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = dynamic_cast<TupleType*>(ret);
        REQUIRE(tt);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = dynamic_cast<BasicType*>(vt);
            REQUIRE(bt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = dynamic_cast<BasicType*>(vt);
            REQUIRE(bt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }
}
