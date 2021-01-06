cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Codegen VERSION 1.0)

add_subdirectory(fmt)

add_executable(codegen main.cpp)
target_compile_features(codegen PRIVATE cxx_std_17)
target_link_libraries(codegen PRIVATE fmt)
# target_include_directories(codegen PRIVATE fmt/include)
