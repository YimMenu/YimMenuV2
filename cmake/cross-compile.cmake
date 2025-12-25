if(WIN32 OR CYGWIN)
    set(CROSSCOMPILE_DEFAULT OFF)
else()
    set(CROSSCOMPILE_DEFAULT ON)
endif()

option(CROSSCOMPILE "Enable cross-compilation by using Zig/Clang(with MinGW) toolchain." ${CROSSCOMPILE_DEFAULT})

if(CROSSCOMPILE)
    message(STATUS "Cross-compile is enabled.")

    # Set the CMake system name to Windows for cross-compilation
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_VERSION 10.0.26100)

    # adjust the default behavior of the FIND_XXX() commands:
    # search programs in the host environment
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

    # search headers and libraries in the target environment
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    # Link statically to avoid runtime dependencies
    add_link_options(-static)

    # Detect available compilers
    message(STATUS "Searching for compiler...")

    # Force specific compiler by using CMake cache variables
    set(USE_CROSSCOMPILER "Auto" CACHE STRING "Cross-compiler to use (default: Auto)")
    set_property(CACHE USE_CROSSCOMPILER PROPERTY STRINGS "Auto" "Zig" "Clang")

    # Seach for Zig
    find_program(ZIG_EXECUTABLE zig)
    if(ZIG_EXECUTABLE AND (USE_CROSSCOMPILER STREQUAL "Auto" OR USE_CROSSCOMPILER STREQUAL "Zig"))
        set(USE_CROSSCOMPILER "Zig")
    elseif(NOT ZIG_EXECUTABLE)
        message(STATUS "Zig compiler not found.")
    endif()

    # Search for Clang
    find_program(CLANG_EXECUTABLE clang)
    if(CLANG_EXECUTABLE AND (USE_CROSSCOMPILER STREQUAL "Auto" OR USE_CROSSCOMPILER STREQUAL "Clang"))
        set(USE_CROSSCOMPILER "Clang")
    elseif(NOT CLANG_EXECUTABLE)
            message(STATUS "Clang compiler not found.")
    endif()

    # Configure the toolchain based on the selected compiler
    if(USE_CROSSCOMPILER STREQUAL "Zig")

        message(STATUS "Using Zig for cross-compilation.")

        # Set Zig target triple
        set(ZIG_ARCH "x86_64")
        set(ZIG_SYS  "windows")
        set(ZIG_ENV  "gnu") # "msvc" will not work, as it lacks libc support
        set(ZIG_TARGET "${ZIG_ARCH}-${ZIG_SYS}-${ZIG_ENV}")

        # Define Zig toolchain commands
        # Some of them intentionally are not in double quotes
        set(ZIG_AR      "${ZIG_EXECUTABLE} ar")
        set(ZIG_CC       ${ZIG_EXECUTABLE} cc)
        set(ZIG_CXX      ${ZIG_EXECUTABLE} c++)
        #set(ZIG_DLLTOOL "${ZIG_EXECUTABLE} dlltool")
        set(ZIG_LD      "${ZIG_EXECUTABLE} ld.lld")
        #set(ZIG_LIB     "${ZIG_EXECUTABLE} lib")
        set(ZIG_RANLIB  "${ZIG_EXECUTABLE} ranlib")
        #set(ZIG_OBJCOPY "${ZIG_EXECUTABLE} objcopy")
        set(ZIG_RC      "${ZIG_EXECUTABLE} rc")

        # Setup archive commands
        # We're not using `CMAKE_AR` and `CMAKE_RANLIB` because they expect path without arguments
        # and `ar` and `ranlib` are arguments of `zig` command
        set(CMAKE_C_ARCHIVE_CREATE   "${ZIG_AR} qc <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_CXX_ARCHIVE_CREATE "${ZIG_AR} qc <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_C_ARCHIVE_APPEND   "${ZIG_AR} q <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_CXX_ARCHIVE_APPEND "${ZIG_AR} q <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_C_ARCHIVE_FINISH   "${ZIG_RANLIB} <TARGET>")
        set(CMAKE_CXX_ARCHIVE_FINISH "${ZIG_RANLIB} <TARGET>")

        # Setup compiler
        set(CMAKE_C_COMPILER ${ZIG_CC} -target ${ZIG_TARGET})
        set(CMAKE_CXX_COMPILER ${ZIG_CXX} -target ${ZIG_TARGET})
        set(CMAKE_C_COMPILER_TARGET ${ZIG_TARGET})
        set(CMAKE_CXX_COMPILER_TARGET ${ZIG_TARGET})

        # Setup linker
        set(CMAKE_LINKER_TYPE LLD)
        if (CMAKE_VERSION VERSION_LESS "4.0.0")
            set(CMAKE_C_USING_LINKER_MODE TOOL)
            set(CMAKE_CXX_USING_LINKER_MODE TOOL)
        else()
            set(CMAKE_C_LINK_MODE LINKER)
            set(CMAKE_CXX_LINK_MODE LINKER)
        endif()
        set(CMAKE_C_USING_LINKER_LLD ${ZIG_LD})
        set(CMAKE_CXX_USING_LINKER_LLD ${ZIG_LD})

        # Setup resource compiler
        set(CMAKE_RC_COMPILER ${ZIG_RC})

        # Enable Microsoft Extensions for Zig (__try/__except/__finally, etc.)
        add_compile_options("$<$<COMPILE_LANGUAGE:C>:-fms-extensions${C_FLAGS}>")
        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fms-extensions${CXX_FLAGS}>")

    elseif(USE_CROSSCOMPILER STREQUAL "Clang")

        message(STATUS "Using Clang(MinGW) compiler.")

        set(TOOLCHAIN_PREFIX "auto" CACHE STRING "Set toolchain. Default: auto")

        if(TOOLCHAIN_PREFIX STREQUAL "auto")
            # Define list of possible toolchain prefixes to try
            set(POSSIBLE_TOOLCHAIN_PREFIXES
                "x86_64-w64-mingw32ucrt"
                "x86_64-w64-mingw32"
            )
            
            # Probe each prefix to find the first existing one
            foreach(PREFIX ${POSSIBLE_TOOLCHAIN_PREFIXES})
                if(EXISTS "/usr/${PREFIX}")
                    set(TOOLCHAIN_PREFIX ${PREFIX})
                    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
                    message(STATUS "Found toolchain: ${TOOLCHAIN_PREFIX}")
                    break()
                endif()
            endforeach()
            
            # Check if we found a valid toolchain
            if(TOOLCHAIN_PREFIX STREQUAL "auto")
                message(FATAL_ERROR "No MinGW toolchain found in /usr/. Tried: ${POSSIBLE_TOOLCHAIN_PREFIXES}")
            endif()
            message(STATUS "Using auto-detected toolchain.")
        else()
            # Use the specified by user toolchain prefix
            set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
            message(STATUS "Using specified toolchain prefix: ${TOOLCHAIN_PREFIX}")
        endif()

        set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE})
        set(CMAKE_CXX_COMPILER ${CLANG_EXECUTABLE}++)
        set(CMAKE_C_COMPILER_TARGET ${TOOLCHAIN_PREFIX})
        set(CMAKE_CXX_COMPILER_TARGET ${TOOLCHAIN_PREFIX})

        # Enable Microsoft Extensions for Clang (__try/__except/__finally, etc.)
        add_compile_options("$<$<COMPILE_LANGUAGE:C>:-fms-extensions${C_FLAGS}>")
        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fms-extensions${CXX_FLAGS}>")

        # Emulate TLS for Clang
        # This is needed for compatibility with MinGW's libstdc++.
        # See https://github.com/msys2/MINGW-packages/issues/5786
        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-femulated-tls${CXX_FLAGS}>")

        # Disable RTTI to work around libstdc++ issue https://stackoverflow.com/a/77025827
        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fuse-ld=lld;-fno-rtti${CXX_FLAGS}>")
        add_link_options(-fuse-ld=lld -fno-rtti)

    else()

        message(FATAL_ERROR
            "No suitable cross-compilation toolchain found."
            "\nInstall either:"
            "\n  - Zig:"
            "\n    - Just install Zig and make sure it is in PATH."
            "\n  - Clang:"
            "\n    - Install Clang and MinGW toolchain (recommended: x86_64-w64-mingw32ucrt)."
        )

    endif()

endif() 