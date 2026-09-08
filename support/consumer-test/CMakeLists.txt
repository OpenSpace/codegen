##########################################################################################
#                                                                                        #
# OpenSpace Codegen                                                                      #
#                                                                                        #
# Copyright (c) 2021-2026                                                                #
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

# Minimal stand-in for a third-party project. It consumes codegen the same way an external
# developer would - through the `codegen` overlay port and `find_package` - and therefore
# catches breakage in the port, the install rules, and the exported targets that building
# codegen in-tree cannot catch.
#
#   cmake -S support/consumer-test -B build/consumer-test
#     --toolchain $env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
#     -DVCPKG_TARGET_TRIPLET=x64-windows
#   cmake --build build/consumer-test
#   ctest --test-dir build/consumer-test

cmake_minimum_required(VERSION 3.25)
project(CodegenConsumerTest LANGUAGES CXX)

find_package(codegen CONFIG REQUIRED)

add_executable(CodegenConsumerTest main.cpp)
target_compile_features(CodegenConsumerTest PRIVATE cxx_std_23)
target_link_libraries(CodegenConsumerTest PRIVATE codegen::codegen-lib)

enable_testing()
add_test(NAME CodegenConsumerTest COMMAND CodegenConsumerTest)

# The exported executable target has to be runnable for a superproject that drives codegen
# as a build step. Point it at an empty directory so it does a clean no-op run (exit 0)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/emptyscan)
add_test(NAME CodegenTool COMMAND codegen::codegen-tool ${CMAKE_CURRENT_BINARY_DIR}/emptyscan)
