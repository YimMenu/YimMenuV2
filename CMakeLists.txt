cmake_minimum_required(VERSION 3.20.x)

include(cmake/cross-compile.cmake)

project(YimMenuV2 VERSION 0.0.1 DESCRIPTION "A new base using new C++ features optimised for speed and ease of use")

# libs
include(cmake/async-logger.cmake)
include(cmake/imgui.cmake)
include(cmake/json.cmake)
include(cmake/minhook.cmake)

# source
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.cpp"    
)

add_library(${PROJECT_NAME} MODULE ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_precompile_headers(${PROJECT_NAME} PUBLIC "${SRC_DIR}/common.hpp")

add_compile_definitions(
    _CRT_SECURE_NO_WARNINGS
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    IMGUI_DEFINE_MATH_OPERATORS
)

message(STATUS "Setting up include directories.")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${SRC_DIR}"
    "${imgui_SOURCE_DIR}"
    "${minhook_SOURCE_DIR}/include"
    "${minhook_SOURCE_DIR}/src/hde"
)

message(STATUS "Setting up linked libraries")
target_link_libraries(${PROJECT_NAME} PRIVATE AsyncLogger imgui minhook nlohmann_json::nlohmann_json dbghelp d3dcompiler dwmapi)