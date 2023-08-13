include(FetchContent)

message(STATUS "Setting up AsyncLogger")

set(USE_FMT ON CACHE INTERNAL "")

FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG v0.0.6
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

target_compile_definitions(AsyncLogger PRIVATE USE_FMT) # Why?
set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)