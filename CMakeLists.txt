project(Codegen VERSION 1.0)

add_executable(codegen main.cpp)
target_compile_features(codegen PRIVATE cxx_std_17)
target_link_libraries(codegen PRIVATE fmt)
