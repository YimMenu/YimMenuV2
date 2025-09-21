include(FetchContent)

set(LIB_NAME "imgui")
message(STATUS "Setting up ${LIB_NAME}")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG d4f722d5b289d4d75b775acfb0a4b41e7df472a7
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})

file(GLOB SRC_IMGUI
    "${imgui_SOURCE_DIR}/*.cpp"
    "${imgui_SOURCE_DIR}/*.h"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_win32.*"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.*"
    "${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.*"
)

add_library(imgui STATIC ${SRC_IMGUI})
source_group(TREE ${imgui_SOURCE_DIR} PREFIX "imgui" FILES ${SRC_IMGUI})
target_include_directories(imgui PRIVATE
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends"
    "${imgui_SOURCE_DIR}/misc/cpp"
)