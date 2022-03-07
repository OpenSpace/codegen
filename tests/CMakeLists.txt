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

  execution_enums/execution_enums_basic.cpp
  execution_enums/execution_enums_mapping.cpp
  execution_enums/execution_enums_multiple.cpp
  execution_enums/execution_enums_keys.cpp
  execution_luawrapper/execution_luawrapper_basic.cpp
  execution_luawrapper/execution_luawrapper_comments.cpp
  execution_misc/execution_misc_parentdoc.cpp
  execution_structs/execution_structs_attributes.cpp
  execution_structs/execution_structs_basic_types.cpp
  execution_structs/execution_structs_basic_types_optional.cpp
  execution_structs/execution_structs_basic_types_optional_vector.cpp
  execution_structs/execution_structs_basic_types_vector.cpp
  execution_structs/execution_structs_enums.cpp
  execution_structs/execution_structs_enummapping.cpp
  execution_structs/execution_structs_map.cpp
  execution_structs/execution_structs_multiple.cpp
  execution_structs/execution_structs_optional_variant_vector.cpp
  execution_structs/execution_structs_other.cpp
  execution_structs/execution_structs_shadowing.cpp
  execution_structs/execution_structs_simple.cpp
  execution_structs/execution_structs_substructs.cpp
  execution_structs/execution_structs_variant.cpp

  parsing_enums/parsing_enums_basic.cpp
  parsing_enums/parsing_enums_mapping.cpp
  parsing_enums/parsing_enums_multiple.cpp
  parsing_enums/parsing_enums_keys.cpp
  parsing_luawrapper/parsing_luawrapper_arguments.cpp
  parsing_luawrapper/parsing_luawrapper_basic.cpp
  parsing_luawrapper/parsing_luawrapper_comments.cpp
  parsing_luawrapper/parsing_luawrapper_return.cpp
  parsing_mixed/parsing_mixed_basic.cpp
  parsing_structs/parsing_structs_attributes_bool.cpp
  parsing_structs/parsing_structs_attributes_dictionary.cpp
  parsing_structs/parsing_structs_attributes_float.cpp
  parsing_structs/parsing_structs_attributes_int.cpp
  parsing_structs/parsing_structs_attributes_ivec2.cpp
  parsing_structs/parsing_structs_attributes_ivec3.cpp
  parsing_structs/parsing_structs_attributes_ivec4.cpp
  parsing_structs/parsing_structs_attributes_path.cpp
  parsing_structs/parsing_structs_attributes_string.cpp
  parsing_structs/parsing_structs_attributes_vec2.cpp
  parsing_structs/parsing_structs_attributes_vec3.cpp
  parsing_structs/parsing_structs_attributes_vec4.cpp
  parsing_structs/parsing_structs_attributes_error_bool.cpp
  parsing_structs/parsing_structs_attributes_error_dictionary.cpp
  parsing_structs/parsing_structs_attributes_error_dmat2x2.cpp
  parsing_structs/parsing_structs_attributes_error_dmat2x3.cpp
  parsing_structs/parsing_structs_attributes_error_dmat2x4.cpp
  parsing_structs/parsing_structs_attributes_error_dmat3x2.cpp
  parsing_structs/parsing_structs_attributes_error_dmat3x3.cpp
  parsing_structs/parsing_structs_attributes_error_dmat3x4.cpp
  parsing_structs/parsing_structs_attributes_error_dmat4x2.cpp
  parsing_structs/parsing_structs_attributes_error_dmat4x3.cpp
  parsing_structs/parsing_structs_attributes_error_dmat4x4.cpp
  parsing_structs/parsing_structs_attributes_error_double.cpp
  parsing_structs/parsing_structs_attributes_error_dvec2.cpp
  parsing_structs/parsing_structs_attributes_error_dvec3.cpp
  parsing_structs/parsing_structs_attributes_error_dvec4.cpp
  parsing_structs/parsing_structs_attributes_error_float.cpp
  parsing_structs/parsing_structs_attributes_error_int.cpp
  parsing_structs/parsing_structs_attributes_error_ivec2.cpp
  parsing_structs/parsing_structs_attributes_error_ivec3.cpp
  parsing_structs/parsing_structs_attributes_error_ivec4.cpp
  parsing_structs/parsing_structs_attributes_error_mat2x2.cpp
  parsing_structs/parsing_structs_attributes_error_mat2x3.cpp
  parsing_structs/parsing_structs_attributes_error_mat2x4.cpp
  parsing_structs/parsing_structs_attributes_error_mat3x2.cpp
  parsing_structs/parsing_structs_attributes_error_mat3x3.cpp
  parsing_structs/parsing_structs_attributes_error_mat3x4.cpp
  parsing_structs/parsing_structs_attributes_error_mat4x2.cpp
  parsing_structs/parsing_structs_attributes_error_mat4x3.cpp
  parsing_structs/parsing_structs_attributes_error_mat4x4.cpp
  parsing_structs/parsing_structs_attributes_error_string.cpp
  parsing_structs/parsing_structs_attributes_error_vec2.cpp
  parsing_structs/parsing_structs_attributes_error_vec3.cpp
  parsing_structs/parsing_structs_attributes_error_vec4.cpp
  parsing_structs/parsing_structs_enums.cpp
  parsing_structs/parsing_structs_error.cpp
  parsing_structs/parsing_structs_map.cpp
  parsing_structs/parsing_structs_other.cpp
  parsing_structs/parsing_structs_struct.cpp
  parsing_structs/parsing_structs_variable.cpp
  parsing_structs/parsing_structs_variant.cpp
  parsing_structs/parsing_structs_variant_error.cpp
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
  COMMAND codegen ARGS "${CMAKE_CURRENT_SOURCE_DIR}/execution_enums" "${CMAKE_CURRENT_SOURCE_DIR}/execution_luawrapper" "${CMAKE_CURRENT_SOURCE_DIR}/execution_misc" "${CMAKE_CURRENT_SOURCE_DIR}/execution_structs"
  VERBATIM
)
