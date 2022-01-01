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

set(FILES
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

add_library(codegen-lib ${FILES})
target_include_directories(codegen-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(codegen-lib PUBLIC cxx_std_17)
target_link_libraries(codegen-lib PUBLIC fmt)
