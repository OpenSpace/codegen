project(Codegen VERSION 1.0)

set(FILES
  main.cpp
  codegen.h
  codegen.cpp
  types.h
  parsing.h
  parsing.cpp
  settings.h
  snippets.h
  storage.h
  util.h
  util.cpp
  verifier.h
  verifier.cpp
)

add_executable(codegen ${FILES})
target_compile_features(codegen PRIVATE cxx_std_17)
target_link_libraries(codegen PRIVATE fmt)
