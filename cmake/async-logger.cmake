include(FetchContent)
add_compile_definitions(CXX_FORMAT_SUPPORT)
message(STATUS "Setting up AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG 25b5ed31b33c40fabc6b80213c330a10cccf3b49
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)
