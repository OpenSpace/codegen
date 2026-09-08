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

# Verifies that the `codegen` overlay port under support/vcpkg/ports declares the same
# runtime dependencies and optional features as the root vcpkg.json. A superproject that
# adds codegen through the port (instead of add_subdirectory) cannot use codegen's own
# manifest, since vcpkg only reads the manifest of the top-level project, so the two lists
# have to stay identical apart from the intentional differences listed below.
#
# Intentional differences (a mismatch in these is allowed, anything else is an error):
#   - the port additionally depends on the vcpkg-cmake / vcpkg-cmake-config host tools,
#     which the standalone manifest gets from vcpkg itself
#
# Run with:  cmake -P support/vcpkg/check-manifest-sync.cmake

cmake_minimum_required(VERSION 3.19)

get_filename_component(CODEGEN_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(MANIFEST "${CODEGEN_ROOT_DIR}/vcpkg.json")
set(PORT "${CMAKE_CURRENT_LIST_DIR}/ports/codegen/vcpkg.json")

# Dependencies that are allowed to appear only in the port
set(PORT_ONLY_DEPENDENCIES "vcpkg-cmake" "vcpkg-cmake-config")
# Features that are allowed to appear only in the manifest
set(MANIFEST_ONLY_FEATURES "")

function (flatten_dependencies outVar dependencies)
  set(result "")
  string(JSON count LENGTH "${dependencies}")
  if (count GREATER 0)
    math(EXPR lastIndex "${count} - 1")
    foreach (i RANGE ${lastIndex})
      string(JSON entryType TYPE "${dependencies}" ${i})
      string(JSON entry GET "${dependencies}" ${i})

      if (entryType STREQUAL "STRING")
        list(APPEND result "${entry}")
        continue ()
      endif ()

      string(JSON name GET "${entry}" "name")

      string(JSON features ERROR_VARIABLE featuresError GET "${entry}" "features")
      set(featureList "")
      if (featuresError STREQUAL "NOTFOUND")
        string(JSON featureCount LENGTH "${features}")
        if (featureCount GREATER 0)
          math(EXPR lastFeature "${featureCount} - 1")
          foreach (j RANGE ${lastFeature})
            string(JSON feature GET "${features}" ${j})
            list(APPEND featureList "${feature}")
          endforeach ()
          list(SORT featureList)
        endif ()
      endif ()
      list(JOIN featureList "+" featureText)

      string(JSON defaults ERROR_VARIABLE defaultsError GET "${entry}" "default-features")
      if (NOT defaultsError STREQUAL "NOTFOUND")
        set(defaults "ON")
      endif ()

      list(APPEND result "${name}[${featureText}](default-features=${defaults})")
    endforeach ()
  endif ()

  list(SORT result)
  set(${outVar} "${result}" PARENT_SCOPE)
endfunction ()

# Removes every flattened entry whose dependency name is in `excluded` from `list`
function (drop_dependencies outVar list excluded)
  set(result "")
  foreach (entry IN LISTS list)
    string(REGEX REPLACE "\\[.*$" "" entryName "${entry}")
    if (NOT entryName IN_LIST excluded)
      list(APPEND result "${entry}")
    endif ()
  endforeach ()
  set(${outVar} "${result}" PARENT_SCOPE)
endfunction ()

function (feature_names outVar features)
  string(JSON count LENGTH "${features}")
  set(result "")
  if (count GREATER 0)
    math(EXPR lastIndex "${count} - 1")
    foreach (i RANGE ${lastIndex})
      string(JSON name MEMBER "${features}" ${i})
      list(APPEND result "${name}")
    endforeach ()
    list(SORT result)
  endif ()
  set(${outVar} "${result}" PARENT_SCOPE)
endfunction ()

# Returns the "dependencies" array of `feature`, or "[]" if the feature declares none
function (feature_dependencies outVar features feature)
  string(JSON deps ERROR_VARIABLE depsError GET "${features}" "${feature}" "dependencies")
  if (NOT depsError STREQUAL "NOTFOUND")
    set(deps "[]")
  endif ()
  set(${outVar} "${deps}" PARENT_SCOPE)
endfunction ()

file(READ "${MANIFEST}" manifestJson)
file(READ "${PORT}" portJson)

set(errors "")

string(JSON manifestDependencies ERROR_VARIABLE manifestDepsError GET "${manifestJson}" "dependencies")
if (NOT manifestDepsError STREQUAL "NOTFOUND")
  set(manifestDependencies "[]")
endif ()
string(JSON portDependencies ERROR_VARIABLE portDepsError GET "${portJson}" "dependencies")
if (NOT portDepsError STREQUAL "NOTFOUND")
  set(portDependencies "[]")
endif ()
flatten_dependencies(manifestDeps "${manifestDependencies}")
flatten_dependencies(portDeps "${portDependencies}")
drop_dependencies(portDeps "${portDeps}" "${PORT_ONLY_DEPENDENCIES}")
if (NOT manifestDeps STREQUAL portDeps)
  list(APPEND errors "  dependencies\n    vcpkg.json:  ${manifestDeps}\n    port:        ${portDeps}")
endif ()

string(JSON manifestFeatures ERROR_VARIABLE manifestFeaturesError GET "${manifestJson}" "features")
if (NOT manifestFeaturesError STREQUAL "NOTFOUND")
  set(manifestFeatures "{}")
endif ()
string(JSON portFeatures ERROR_VARIABLE portFeaturesError GET "${portJson}" "features")
if (NOT portFeaturesError STREQUAL "NOTFOUND")
  set(portFeatures "{}")
endif ()
feature_names(manifestFeatureNames "${manifestFeatures}")
feature_names(portFeatureNames "${portFeatures}")
if (manifestFeatureNames AND MANIFEST_ONLY_FEATURES)
  list(REMOVE_ITEM manifestFeatureNames ${MANIFEST_ONLY_FEATURES})
endif ()
if (NOT manifestFeatureNames STREQUAL portFeatureNames)
  list(APPEND errors "  feature names\n    vcpkg.json:  ${manifestFeatureNames}\n    port:        ${portFeatureNames}")
else ()
  foreach (feature ${manifestFeatureNames})
    feature_dependencies(manifestFeatureDependencies "${manifestFeatures}" "${feature}")
    feature_dependencies(portFeatureDependencies "${portFeatures}" "${feature}")
    flatten_dependencies(manifestFeatureDeps "${manifestFeatureDependencies}")
    flatten_dependencies(portFeatureDeps "${portFeatureDependencies}")
    if (NOT manifestFeatureDeps STREQUAL portFeatureDeps)
      list(APPEND errors "  feature '${feature}'\n    vcpkg.json:  ${manifestFeatureDeps}\n    port:        ${portFeatureDeps}")
    endif ()
  endforeach ()
endif ()

if (errors)
  list(JOIN errors "\n" errorText)
  message(FATAL_ERROR
    "vcpkg.json and support/vcpkg/ports/codegen/vcpkg.json have diverged:\n${errorText}\n"
  )
endif ()

message(STATUS "vcpkg.json and the codegen port are in sync")
