include(FetchContent)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/tupoy-ya/GTAV-Classes.git
    GIT_TAG        19bd48547d7c7d721e52ee344c46524bad3a5d0e
    GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
message("GTAV-Classes")
if(NOT gtav_classes_POPULATED)
    FetchContent_Populate(gtav_classes)
endif()