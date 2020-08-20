cmake_minimum_required(VERSION 3.9)
project(invite_controller)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


file(GLOB_RECURSE SOURCE_FILES src/plugin.cc)
file(GLOB_RECURSE CORN_SOURCE src/sdk/**.cc)

set(LIB_NAME "test")
add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${CORN_SOURCE})
target_link_options(${LIB_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/EXPORT:apprun=_apprun@8>")

