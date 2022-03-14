cmake_minimum_required(VERSION 3.21)
project(yubel C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -ansi -pedantic)
enable_testing()

macro(add_lib name)
    add_library(${name} ${name}.c ${name}.h)
    install(FILES ${name}.h DESTINATION include)
    install(TARGETS ${name} DESTINATION lib)
    add_executable(yubel specs/${name}_tests.c ${name}.h)
    target_link_libraries(yubel ${name})
    add_test(${name} ./yubel !=1)
endmacro()


add_lib(unit)

