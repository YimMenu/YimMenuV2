# cmake/evasive-toolchain.cmake
# Harden binary output without modifying source code.
# Included conditionally from root CMakeLists.txt when CI_EVASIVE_BUILD is set.

# Link-time code generation — whole program optimization merges functions
# making pattern-matching signatures unreliable
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")

    # Strip PDB path from the binary
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stripped")
    set(CMAKE_DEBUG_INFORMATION_FORMAT "")
    set_target_properties(YimMenuV2 PROPERTIES LINK_FLAGS "/PDBPATH:NONE")

    # LTCG, ASLR + Control Flow Guard (target-level, works for MODULE)
    target_link_options(YimMenuV2 PRIVATE /LTCG /DYNAMICBASE /GUARD:CF)
endif()

# Hide all symbols by default — reduces export table surface
# Clang/GCC only; MSVC ignores these
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
endif()
