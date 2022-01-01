##########################################################################################
#                                                                                        #
# OpenSpace Codegen                                                                      #
#                                                                                        #
# Copyright (c) 2021-2022                                                                #
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

add_executable(
  codegentest
  main.cpp

  execution/execution_attributes.cpp
  execution/execution_basic_types.cpp
  execution/execution_basic_types_optional.cpp
  execution/execution_basic_types_optional_vector.cpp
  execution/execution_basic_types_vector.cpp
  execution/execution_enums.cpp
  execution/execution_enummapping.cpp
  execution/execution_map.cpp
  execution/execution_optional_variant_vector.cpp
  execution/execution_other.cpp
  execution/execution_shadowing.cpp
  execution/execution_simple.cpp
  execution/execution_substructs.cpp
  execution/execution_variant.cpp

  parsing_attributes.cpp
  parsing_attributes_error_bool.cpp
  parsing_attributes_error_dmat2x2.cpp
  parsing_attributes_error_dmat2x3.cpp
  parsing_attributes_error_dmat2x4.cpp
  parsing_attributes_error_dmat3x2.cpp
  parsing_attributes_error_dmat3x3.cpp
  parsing_attributes_error_dmat3x4.cpp
  parsing_attributes_error_dmat4x2.cpp
  parsing_attributes_error_dmat4x3.cpp
  parsing_attributes_error_dmat4x4.cpp
  parsing_attributes_error_double.cpp
  parsing_attributes_error_dvec2.cpp
  parsing_attributes_error_dvec3.cpp
  parsing_attributes_error_dvec4.cpp
  parsing_attributes_error_float.cpp
  parsing_attributes_error_int.cpp
  parsing_attributes_error_ivec2.cpp
  parsing_attributes_error_ivec3.cpp
  parsing_attributes_error_ivec4.cpp
  parsing_attributes_error_mat2x2.cpp
  parsing_attributes_error_mat2x3.cpp
  parsing_attributes_error_mat2x4.cpp
  parsing_attributes_error_mat3x2.cpp
  parsing_attributes_error_mat3x3.cpp
  parsing_attributes_error_mat3x4.cpp
  parsing_attributes_error_mat4x2.cpp
  parsing_attributes_error_mat4x3.cpp
  parsing_attributes_error_mat4x4.cpp
  parsing_attributes_error_monostate.cpp
  parsing_attributes_error_string.cpp
  parsing_attributes_error_vec2.cpp
  parsing_attributes_error_vec3.cpp
  parsing_attributes_error_vec4.cpp
  parsing_error.cpp
  parsing_map.cpp
  parsing_other.cpp
  parsing_struct.cpp
  parsing_variable.cpp
  parsing_variant.cpp
  parsing_variant_error.cpp
)

target_include_directories(codegentest PUBLIC "${GHOUL_BASE_DIR}/ext/catch2/single_include")
target_link_libraries(codegentest PUBLIC codegen-lib openspace-core openspace-module-collection)
if (MSVC)
  target_compile_options(codegentest PRIVATE "/wd5030")
else ()
  target_compile_options(codegentest PRIVATE "-Wno-ignored-attributes" "-Wno-attributes")
endif ()

if (OPENSPACE_MODULE_WEBBROWSER AND CEF_ROOT)
  # wanted by CEF
  set(PROJECT_ARCH "x86_64")

  if (WIN32)
    set(RESOURCE_FILE ${OPENSPACE_APPS_DIR}/OpenSpace/openspace.rc)
  endif ()

  # Add the CEF binary distribution's cmake/ directory to the module path and
  # find CEF to initialize it properly.
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${WEBBROWSER_MODULE_PATH}/cmake")
  include(webbrowser_helpers)

  set_cef_targets("${CEF_ROOT}" codegentest)
  run_cef_platform_config("${CEF_ROOT}" "${CEF_TARGET}" "${WEBBROWSER_MODULE_PATH}")
elseif ()
  message(WARNING "Web configured to be included, but no CEF_ROOT was found, please try configuring CMake again.")
endif ()

# It is important that the __codegen.h does not actually exist so that this target
# is never considered as finished
add_custom_target(run_test_codegen ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/__codegen_unittest.h")
add_dependencies(run_test_codegen codegen)
add_dependencies(codegentest run_test_codegen)
add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/__codegen_unittest.h"
  COMMAND codegen ARGS "${CMAKE_CURRENT_SOURCE_DIR}/execution"
  VERBATIM
)
