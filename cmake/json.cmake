include(FetchContent)

message(STATUS "Setting up nlohmann::json")
FetchContent_Declare(json GIT_REPOSITORY "https://github.com/nlohmann/json/" GIT_TAG v3.11.2 GIT_SHALLOW TRUE)
option(JSON_MultipleHeaders "Disable nlohmann JSON multi header default." OFF)
FetchContent_MakeAvailable(json)