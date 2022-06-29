cmake_minimum_required(VERSION 3.5)

project(yubel VERSION 0.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -ansi -pedantic)
enable_testing()

macro(add_lib name)
    add_library(${name} ${name}/${name}.cpp ${name}/${name}.hpp)
    install(FILES ${name}/${name}.h DESTINATION include)
    install(TARGETS ${name} DESTINATION lib)
endmacro()

macro(add_exec name)
    add_executable(${name} ${name}.c ${name}.h)
    install(FILES ${name}.hpp DESTINATION include)
    install(TARGETS ${name} DESTINATION lib)
endmacro()


add_lib(Unit)
add_lib(Installation)