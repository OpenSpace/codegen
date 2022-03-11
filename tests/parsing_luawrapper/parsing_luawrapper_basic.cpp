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

TEST_CASE("Parsing/LuaWrapper/Basic:  No Arguments") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    CHECK(f->arguments.size() == 0);

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  1 Argument") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo(int arg) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
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
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  1 Defaulted Argument") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo(int arg = 1) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    CHECK(f->returnValue == nullptr);
    REQUIRE(f->arguments.size() == 1);
    {
        Variable* v = f->arguments[0];
        REQUIRE(v);
        CHECK(v->name == "arg");
        REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(v->type);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  2 Arguments") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo(int arg1, std::string arg2) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
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
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* v = f->arguments[1];
        REQUIRE(v);
        CHECK(v->name == "arg2");
        REQUIRE(v->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  2 Arguments (optional/1)") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo(int arg1, std::optional<double> arg2) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
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
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* v = f->arguments[1];
        REQUIRE(v);
        CHECK(v->name == "arg2");
        REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(v->type);
        REQUIRE(ot->type);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  2 Arguments (optional/2)") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] void foo(int arg1, double arg2 = 2.0) {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
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
        BasicType* bt = static_cast<BasicType*>(v->type);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* v = f->arguments[1];
        REQUIRE(v);
        CHECK(v->name == "arg2");
        REQUIRE(v->type->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(v->type);
        REQUIRE(ot->type);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::Double);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Return value") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] int foo() {
        return 1;
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ret);
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  No Arguments, Multiple return values") {
    constexpr const char Source[] = R"(
    [[codegen::luawrap]] std::tuple<int, double> foo() {
    }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Multiline function definition") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]]
std::tuple<int, double>
foo()
{
}
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Silly multiline function definition") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]]
std::tuple<
int,
double
>
foo
()
{
}
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Silly multiline function definition with spaces") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]]
   std::tuple<
 int,
       double
                                 > foo
(    )
 {
      }
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Minimalistic function definition") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]] std::tuple<int, double> foo(){}
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Multiline argument function definition") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]] std::tuple<int, double> foo(int arg1,
float arg2,
                                                        std::string     arg3 = "abc")      {
}
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "foo");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 2);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Int);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
    }

    REQUIRE(f->arguments.size() == 3);
    {
        Variable* var = f->arguments[0];
        REQUIRE(var);
        CHECK(var->name == "arg1");
        REQUIRE(var->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(var->type);
        CHECK(bt->type == BasicType::Type::Int);
    }
    {
        Variable* var = f->arguments[1];
        REQUIRE(var);
        CHECK(var->name == "arg2");
        REQUIRE(var->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(var->type);
        CHECK(bt->type == BasicType::Type::Float);
    }
    {
        Variable* var = f->arguments[2];
        REQUIRE(var);
        CHECK(var->name == "arg3");
        REQUIRE(var->type->tag == VariableType::Tag::OptionalType);
        OptionalType* ot = static_cast<OptionalType*>(var->type);
        REQUIRE(ot->defaultArgument.has_value());
        CHECK(*ot->defaultArgument == "\"abc\"");
        REQUIRE(ot->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(ot->type);
        CHECK(bt->type == BasicType::Type::String);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

TEST_CASE("Parsing/LuaWrapper/Basic:  Multiline tuple return value") {
    constexpr const char Source[] = R"(
[[codegen::luawrap]] std::tuple<std::string, bool, std::string, bool, double,
    std::string, float, float, bool>
    functionName
(std::string arg1, int arg2)
{
}
)";

    Code code = parse(Source);
    CHECK(code.structs.size() == 0);
    CHECK(code.enums.size() == 0);
    REQUIRE(code.luaWrapperFunctions.size() == 1);
    Function* f = code.luaWrapperFunctions.front();
    REQUIRE(f);

    CHECK(f->name == "functionName");
    CHECK(f->documentation == "");
    {
        VariableType* ret = f->returnValue;
        REQUIRE(ret);
        REQUIRE(ret->tag == VariableType::Tag::TupleType);
        TupleType* tt = static_cast<TupleType*>(ret);
        REQUIRE(tt->types.size() == 9);
        {
            VariableType* vt = tt->types[0];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::String);
        }
        {
            VariableType* vt = tt->types[1];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Bool);
        }
        {
            VariableType* vt = tt->types[2];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::String);
        }
        {
            VariableType* vt = tt->types[3];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Bool);
        }
        {
            VariableType* vt = tt->types[4];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Double);
        }
        {
            VariableType* vt = tt->types[5];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::String);
        }
        {
            VariableType* vt = tt->types[6];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Float);
        }
        {
            VariableType* vt = tt->types[7];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Float);
        }
        {
            VariableType* vt = tt->types[8];
            REQUIRE(vt->tag == VariableType::Tag::BasicType);
            BasicType* bt = static_cast<BasicType*>(vt);
            CHECK(bt->type == BasicType::Type::Bool);
        }
    }

    REQUIRE(f->arguments.size() == 2);
    {
        Variable* var = f->arguments[0];
        REQUIRE(var);
        CHECK(var->name == "arg1");
        REQUIRE(var->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(var->type);
        CHECK(bt->type == BasicType::Type::String);
    }
    {
        Variable* var = f->arguments[1];
        REQUIRE(var);
        CHECK(var->name == "arg2");
        REQUIRE(var->type->tag == VariableType::Tag::BasicType);
        BasicType* bt = static_cast<BasicType*>(var->type);
        CHECK(bt->type == BasicType::Type::Int);
    }

    std::string r = generateResult(code);
    CHECK(!r.empty());
}

