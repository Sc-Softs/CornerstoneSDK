cmake_minimum_required(VERSION 3.10)
# TODO: set your project name here
set(LIB_NAME "test")

# =======================SHOULD NOT EDIT!============================
project(invite_controller)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(SOURCE "")
set(CORN_SOURCE "")
set(DEF_FILE "")
file(GLOB_RECURSE SOURCE src/plugin.cc)
file(GLOB_RECURSE CORN_SOURCE src/sdk/**.cc)
file(GLOB_RECURSE DEF_FILE def/config.def)

add_library(${LIB_NAME} SHARED ${SOURCE} ${CORN_SOURCE} ${DEF_FILE})

# target_link_options(${LIB_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/EXPORT:apprun=_apprun@8>")

