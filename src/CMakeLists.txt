cmake_minimum_required(VERSION 3.18.2)
project(binary C)

set(CMAKE_C_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library( binary STATIC bits.c)
target_compile_options(binary PRIVATE -Wpedantic -Wall -Wextra)

add_executable(dump dump.c)
target_link_libraries(dump binary dc)
target_compile_options(dump PRIVATE -Wpedantic -Wall -Wextra)

add_executable(create create.c)
target_link_libraries(create binary dc)
target_compile_options(create PRIVATE -Wpedantic -Wall -Wextra)
