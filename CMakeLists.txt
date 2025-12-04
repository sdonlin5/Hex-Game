cmake_minimum_required(VERSION 3.16)
project(Hex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core sources used by both the game and the tests
set(HEX_SOURCES
        src/hex.cpp
        src/board.cpp
        src/gameManager.cpp
        src/unionFind.cpp
        src/utils.cpp
)

# Core headers (not strictly needed in target, but harmless)
set(HEX_HEADERS
        headers/hex.hpp
        headers/state.hpp
        headers/column.hpp
        headers/coords.hpp
        headers/row_labels.hpp
        headers/board.hpp
        headers/gameManager.hpp
        headers/unionFind.hpp
        headers/utils.hpp
        headers/direction.h
)

# Main Hex program
add_executable(Hex
        main.cpp
        ${HEX_SOURCES}
        ${HEX_HEADERS}
)

# Test executable: uses the same core code plus the test runner
add_executable(HexTests
        test/test.cpp
        ${HEX_SOURCES}
        ${HEX_HEADERS}
)

target_include_directories(Hex PRIVATE headers)
target_include_directories(HexTests PRIVATE headers)

enable_testing()
add_test(NAME HexTests COMMAND HexTests)