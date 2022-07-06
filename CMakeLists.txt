cmake_minimum_required(VERSION 3.5)

project(yubel VERSION 0.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra -ansi -pedantic)

macro(add_lib name)
    add_library(${name} ${name}/${name}.cpp ${name}/${name}.hpp)
    install(FILES ${name}/${name}.hpp DESTINATION include)
    install(TARGETS ${name} DESTINATION lib)
endmacro()

macro(add_exec name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} tux)
    install(PROGRAMS ${name} DESTINATION bin)
endmacro()


add_exec(zuu)
add_lib(Generator)
add_lib(Unit)
add_lib(Installation)
