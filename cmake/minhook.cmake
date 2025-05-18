include(FetchContent)

set(LIB_NAME "minhook")
message(STATUS "Setting up ${LIB_NAME}")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        2b003bb063d66f016cc1aef7d63951350ce60f35
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})