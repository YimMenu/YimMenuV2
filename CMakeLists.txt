cmake_minimum_required(VERSION 3.20.x)

include(cmake/cross-compile.cmake)

project(YimMenuV2 VERSION 0.0.1 DESCRIPTION "A new base using new C++ features optimised for speed and ease of use")
include(CTest)

# libs
include(cmake/async-logger.cmake)
include(cmake/imgui.cmake)
include(cmake/json.cmake)
include(cmake/minhook.cmake)
include(cmake/luajit.cmake)

# source
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
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
    "${luajit_SOURCE_DIR}/src"
    "${luajit_BINARY_DIR}/src"
)

message(STATUS "Setting up linked libraries")
target_link_libraries(${PROJECT_NAME} PRIVATE
    # Project dependencies
    AsyncLogger
    imgui
    minhook
    nlohmann_json::nlohmann_json
    dbghelp

    # ImGui dependencies
    $<IF:$<BOOL:${CROSSCOMPILE}>,d3dcompiler_47,d3dcompiler>
    dwmapi
    gdi32
    libluajit
)

target_compile_options(${PROJECT_NAME} PRIVATE
    # Do not warn about non-reproducible code
    $<$<COMPILE_LANG_AND_ID:C,Clang>:-Wno-date-time>
    $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-Wno-date-time>
)

if(BUILD_TESTING)
    add_executable(dat_bit_buffer_tests tests/datBitBufferTests.cpp)
    target_compile_features(dat_bit_buffer_tests PRIVATE cxx_std_23)
    target_include_directories(dat_bit_buffer_tests PRIVATE "${SRC_DIR}")
    add_test(NAME dat_bit_buffer_tests COMMAND dat_bit_buffer_tests)

    add_executable(protection_telemetry_tests
        tests/protectionTelemetryTests.cpp
        src/game/backend/ProtectionTelemetry.cpp
    )
    target_compile_features(protection_telemetry_tests PRIVATE cxx_std_23)
    target_include_directories(protection_telemetry_tests PRIVATE "${SRC_DIR}")
    add_test(NAME protection_telemetry_tests COMMAND protection_telemetry_tests)
endif()
