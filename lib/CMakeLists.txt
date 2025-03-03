##########################################################################################
#                                                                                        #
# OpenSpace Codegen                                                                      #
#                                                                                        #
# Copyright (c) 2021-2025                                                                #
#                                                                                        #
# Permission is hereby granted, free of charge, to any person obtaining a copy of this   #
# software and associated documentation files (the "Software"), to deal in the Software  #
# without restriction, including without limitation the rights to use, copy, modify,     #
# merge, publish, distribute, sublicense, and/or sell copies of the Software, and to     #
# permit persons to whom the Software is furnished to do so, subject to the following    #
# conditions:                                                                            #
#                                                                                        #
# The above copyright notice and this permission notice shall be included in all copies  #
# or substantial portions of the Software.                                               #
#                                                                                        #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,    #
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A          #
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT     #
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF   #
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE   #
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                          #
##########################################################################################

add_library(codegen-lib ${FILES})
target_sources(
  codegen-lib
  PRIVATE
    codegen.h
    codegen.cpp
    parsing.h
    parsing.cpp
    settings.h
    snippets.h
    snippets.cpp
    types.h
    types.cpp
    util.h
    util.cpp
    verifier.h
  verifier.cpp
)

target_include_directories(codegen-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# Switching to cxx_std_23 triggers a bug in Clang17
# https://github.com/llvm/llvm-project/issues/61415
target_compile_features(codegen-lib PUBLIC cxx_std_20)

set(MSVC_WARNINGS
  "/MP"       # Multi-threading support
  "/W4"       # Highest warning level
  "/w44062"   # missing case label
  "/w44165"   # 'HRESULT' is being converted to 'bool'
  "/wd4201"   # nonstandard extension used : nameless struct/union
  "/w44242"   # conversion from 'type1' to 'type2', possible loss of data
  "/w44254"   # conversion from 'type1' to 'type2', possible loss of data
  "/w44263"   # member function does not override any base class virtual member function
  "/w44265"   # class has virtual functions, but destructor is not virtual
  "/w44287"   # unsigned/negative constant mismatch
  "/w44289"   # using for-loop variable outside of loop
  "/w44296"   # expression is always true/false
  "/w44437"   # dynamic_cast could fail in some contexts
  "/w44545"   # expression before comma evaluates to a function missing an argument list
  "/w44547"   # operator before comma has no effect
  "/w44548"   # operator before comma has no effect
  "/w44549"   # operator before comma has no effect
  "/w44555"   # expression has no effect; expected expression with side-effect
  "/w44574"   # 'identifier' is defined to be '0': did you mean to use '#if identifier'?
  "/w44619"   # #pragma warning: there is no warning number 'number'
  "/w44643"   # Forward declaring 'identifier' in namespace std is not permitted
  "/w44800"   # Implicit conversion from 'type' to bool. Possible information loss
  "/w44822"   # local class member function does not have a body
  "/w44841"   # non-standard extension used: compound member designator used in offsetof
  "/w44842"   # the result of 'offsetof' applied to a type using multiple inheritance is
  # not guaranteed to be consistent between compiler releases
  "/w44946"   # reinterpret_cast used between related classes: 'class1' and 'class2'
  "/w44986"   # exception specification does not match previous declaration
  "/w44987"   # nonstandard extension used: 'throw (...)'
  "/w45022"   # multiple move constructors specified
  "/w45023"   # multiple move assignment operators specified
  "/w45031"   # #pragma warning(pop): likely mismatch, popping warning state pushed in
              # different file
  "/w45032"   # detected #pragma warning(push) with no #pragma warning(pop)
  "/w45038"   # data member 'member1' will be initialized after data member 'member2'
  "/w45041"   # out-of-line definition for constexpr data is deprecated
  "/w45042"   # function declarations at block scope cannot be specified 'inline'
  "/w45204"   # virtual class has non-virtual trivial destructor
  "/w45233"   # explicit lambda capture 'identifier' is not used
  "/w45340"   # attribute is ignored in this syntactic position
  "/w45243"   # using incomplete class 'class-name' can cause potential one definition
              # rule violation due to ABI limitation
  "/w45245"   # unreferenced function with internal linkage has been removed
  "/w45249"   # 'bitfield' of type 'enumeration_name' has named enumerators with values
              # that cannot be represented in the given bit field width of
              # 'bitfield_width'.
  "/w45258"   # explicit capture of 'symbol' is not required for this use
  "/w45259"   # explicit specialization requires 'template <>'
  "/w45262"   # implicit fall-through occurs here
  "/w45263"   # calling 'std::move' on a temporary object prevents copy elision
  "/w45264"   # 'const' variable is not used
  "/w45266"   # 'const' qualifier on return type has no effect
  "/wd4127"   # conditional expression is constant
  "/permissive-"
  "/Zc:twoPhase-"  # Used to prevent C:\Program Files (x86)\Windows Kits\8.1\Include\um\combaseapi.h(229): error C2187: syntax error: 'identifier' was unexpected here
                    # This is a bug in Visual Studio 15.3 and can be removed with the next version:
                    # https://developercommunity.visualstudio.com/content/problem/94419/vs-2017-153-with-permissive-shows-error-c2187-in-c.html
  "/Zc:strictStrings-"    # Windows header don't adhere to this
  "/Zc:__cplusplus" # Correctly set the __cplusplus macro
)

set(CLANG_WARNINGS
  "-Wall"
  "-Wextra"
  "-Wabstract-vbase-init"
  "-Warray-bounds-pointer-arithmetic"
  "-Wassign-enum"
  "-Wauto-import"
  "-Wbad-function-cast"
  "-Wbitfield-constant-conversion"
  "-Wcast-calling-convention"
  "-Wcast-qual"
  "-Wchar-subscripts"
  "-Wcomma"
  "-Wcomment"
  "-Wcomplex-component-init"
  "-Wconditional-uninitialized"
  "-Wdate-time"
  "-Wdeprecated-implementations"
  "-Wdollar-in-identifier-extension"
  "-Wduplicate-enum"
  "-Wduplicate-method-match"
  "-Wempty-body"
  "-Wformat-pedantic"
  "-Wheader-hygiene"
  "-Widiomatic-parentheses"
  "-Wimplicit-fallthrough"
  "-Wimport-preprocessor-directive-pedantic"
  "-Winconsistent-missing-override"
  "-Winfinite-recursion"
  "-Wkeyword-macro"
  "-Wlanguage-extension-token"
  "-Wloop-analysis"
  "-Wmethod-signatures"
  "-Wmicrosoft-end-of-file"
  "-Wmicrosoft-enum-forward-reference"
  "-Wmicrosoft-fixed-enum"
  "-Wmicrosoft-flexible-array"
  "-Wmismatched-tags"
  "-Wmissing-field-initializers"
  "-Wmissing-noreturn"
  "-Wnon-virtual-dtor"
  "-Wold-style-cast"
  "-Woverloaded-virtual"
  "-Wpessimizing-move"
  "-Wpointer-arith"
  "-Wpragmas"
  "-Wredundant-move"
  "-Wreorder"
  "-Wsemicolon-before-method-body"
  # "-Wshadow-field"
  "-Wshadow-field-in-constructor"
  # "-Wshadow-all"  Add this again once the Properties don't throw warnings --abock
  "-Wshift-sign-overflow"
  "-Wshorten-64-to-32"
  "-Wsign-compare"
  "-Wstring-conversion"
  "-Wtautological-compare"
  "-Wthread-safety"
  "-Wundef"
  "-Wundefined-reinterpret-cast"
  "-Wuninitialized"
  "-Wunneeded-internal-declaration"
  "-Wunneeded-member-function"
  "-Wunreachable-code-break"
  "-Wunreachable-code-loop-increment"
  "-Wunreachable-code-return"
  "-Wunused-exception-parameter"
  "-Wunused-label"
  "-Wunused-local-typedef"
  "-Wunused-macros"
  "-Wunused-parameter"
  "-Wunused-private-field"
  "-Wunused-result"
  "-Wunused-variable"
  "-Wused-but-marked-unused"
  "-Wvariadic-macros"
  "-Wvla"
  "-Wzero-length-array"
  "-Wno-missing-braces"
  "-Wno-ignored-attributes"
  "-Wno-unknown-attributes"
)

set(GCC_WARNINGS
  "-ggdb"
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-Wunused-parameter"
  "-Wuninitialized"
  "-Wsuggest-override"
  "-Walloc-zero"
  "-Wduplicated-cond"
  "-Wshadow"
  "-Wundef"
  "-Wcast-qual"
  "-Wzero-as-null-pointer-constant"
  "-Wdate-time"
  "-Wuseless-cast"
  "-Wlogical-op"
  "-Wint-in-bool-context"
  "-Wno-deprecated-copy"
  "-Wno-float-equal"
  "-Wno-write-strings"
  "-Wnon-virtual-dtor"
  "-Wold-style-cast"
  "-Woverloaded-virtual"
  "-Wno-long-long"
  "-Wno-ignored-attributes"
  "-Wno-attributes"
)

if (MSVC)
  target_compile_options(codegen-lib PRIVATE ${MSVC_WARNINGS})
elseif (NOT LINUX AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(codegen-lib PRIVATE ${CLANG_WARNINGS})
elseif (UNIX AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(codegen-lib PRIVATE ${CLANG_WARNINGS})
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(codegen-lib PRIVATE ${GCC_WARNINGS})
else ()
  message("Compiler not handled in CmakeLists")
endif ()
