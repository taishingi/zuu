cmake_minimum_required(VERSION 3.5)

project(yubel VERSION 0.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra -ansi -pedantic)

macro(add_lib name)
    add_library(${name} libs/${name}/${name}.cpp libs/${name}/${name}.hpp)
    install(FILES libs/${name}/${name}.hpp DESTINATION include)
    install(TARGETS ${name} DESTINATION lib)
endmacro()

macro(add_exec name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} tux)
    install(PROGRAMS ${name} DESTINATION bin)
endmacro()


add_lib(generator)
add_lib(unit)
add_lib(installation)
add_lib(zuu)
install(PROGRAMS zuu DESTINATION bin)
