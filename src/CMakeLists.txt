cmake_minimum_required(VERSION 3.16)
project(StringRefsInCode)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(BINARY_NINJA_DIR /Users/wei/dev/github/binaryninja-api)
set(BINJA_PLUGINS_DIR "$ENV{HOME}/Library/Application Support/Binary Ninja/plugins")

file(
        GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(
        ${PROJECT_NAME} PRIVATE
        ${BINARY_NINJA_DIR}
)

file(
        GLOB BINARY_NINJA_LIBRARIES
        ${BINARY_NINJA_DIR}/bin/libbinaryninjaapi.a
        /Applications/Binary\ Ninja.app/Contents/MacOS/libbinaryninjacore.dylib
)

target_link_libraries(
        ${PROJECT_NAME}
        ${BINARY_NINJA_LIBRARIES}
)

install(TARGETS StringRefsInCode DESTINATION ${BINJA_PLUGINS_DIR})