cmake_minimum_required(VERSION 2.8.11)
project(little-schemer C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options("-Wall")
add_compile_options("-Werror")
add_compile_options("--std=c11")

add_custom_command(
    PRE_BUILD
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
    COMMAND re2c -o ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re
    )

add_executable(lemon
    lemon.c
    )

add_executable(little-schemer
    main.c
    lexer.h
    )
