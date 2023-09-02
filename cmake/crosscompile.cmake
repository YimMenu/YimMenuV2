option(CROSSCOMPILE "Enables crosscompiling you still need to set USE_GCC or USE_CLANG after this.")
option(USE_GCC "Use MinGW toolchain with gcc compiler and uasm assembler.")
option(USE_CLANG "Use MinGW toolchain with clang compiler and uasm assembler. Clang support is experimental.")

if(CROSSCOMPILE)
    message(STATUS "Crosscompile is enabled. Using MinGW and uasm.")

    set(TOOLCHAIN_PREFIX "x86_64-w64-mingw32" CACHE STRING "Set toolchain. Default: x86_64-w64-mingw32")
    message(STATUS "Using ${TOOLCHAIN_PREFIX} toolchain")
    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
    set(CMAKE_SYSTEM_NAME "Windows")
    set(CMAKE_ASM_MASM_COMPILER "uasm")

    set(CMAKE_C_COMPILER_TARGET x86_64-windows-gnu)
    set(CMAKE_CXX_COMPILER_TARGET x86_64-windows-gnu)
    set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
    set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

    # modify default behavior of FIND_XXX() commands
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    add_compile_options("$<$<COMPILE_LANGUAGE:ASM_MASM>:-win64${ASM_MASM_FLAGS}>")
    add_link_options(-static)
    add_compile_definitions(CROSSCOMPILING)

    if(USE_GCC)
        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fpermissive;${CXX_FLAGS}>")
        set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
        set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    endif()

    if(USE_CLANG)
        message(STATUS "Using clang compiler.")
        set(CMAKE_C_COMPILER clang)
        set(CMAKE_CXX_COMPILER clang++)

        add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fuse-ld=lld;-femulated-tls${CXX_FLAGS}>")
        add_link_options(-fuse-ld=lld -femulated-tls)
    endif()

endif() 
