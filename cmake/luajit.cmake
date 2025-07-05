include(FetchContent)

message(STATUS "Setting up LuaJIT")

set(LUAJIT_BUILD_TOOL OFF)
set(LUAJIT_FORCE_UTF8_FOPEN ON)

FetchContent_Declare(
    luajit
    GIT_REPOSITORY https://github.com/WohlSoft/LuaJIT.git
    GIT_TAG 27878965958986687f8caaf8a2b6b73bc5df85e0
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(luajit)
target_compile_definitions(libluajit PRIVATE
    "_CRT_SECURE_NO_WARNINGS"
    "LUAJIT_ENABLE_LUA52COMPAT"
)