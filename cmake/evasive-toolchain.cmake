# cmake/evasive-toolchain.cmake
# Harden binary output without modifying source code.
# Included conditionally from root CMakeLists.txt when CI_EVASIVE_BUILD is set.

# LTO — whole-program optimization merges functions, breaks pattern matching
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# Strip debug info
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/stripped")
set(CMAKE_DEBUG_INFORMATION_FORMAT "")
