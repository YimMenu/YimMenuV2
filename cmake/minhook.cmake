include(FetchContent)

set(LIB_NAME "minhook")
message(STATUS "Setting up ${LIB_NAME}")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        98b74f1fc12d00313d91f10450e5b3e0036175e3
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})