cmake_minimum_required(VERSION 3.17.3)
project(binary C)

set(CMAKE_C_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(binary STATIC bits.c)
target_compile_options(binary PRIVATE -Wpedantic -Wall -Wextra)

add_executable(dcdump dump.c)
target_link_libraries(dcdump binary dc rt m)
target_compile_options(dcdump PRIVATE -Wpedantic -Wall -Wextra)

add_executable(dccreate create.c)
target_link_libraries(dccreate binary dc rt)
target_compile_options(dccreate PRIVATE -Wpedantic -Wall -Wextra)

install(TARGETS dcdump DESTINATION bin)
install(TARGETS dccreate DESTINATION bin)
