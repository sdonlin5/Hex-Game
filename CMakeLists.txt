cmake_minimum_required(VERSION 3.16)
project(Hex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt path from Homebrew
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

# Core sources used by both versions
set(HEX_SOURCES
        src/hex.cpp
        src/board.cpp
        src/gameManager.cpp
        src/unionFind.cpp
        src/utils.cpp
)

set(HEX_HEADERS
        headers/hex.hpp
        headers/state.hpp
        headers/column.hpp
        headers/coords.hpp
        headers/board.hpp
        headers/gameManager.hpp
        headers/unionFind.hpp
        headers/utils.hpp
        headers/direction.h
        headers/theme.hpp
)

# Qt-specific sources
set(HEX_QT_SOURCES
        src/hexTile.cpp
        src/hexBoard.cpp
        src/Window.cpp
)

set(HEX_QT_HEADERS
        headers/hexTile.hpp
        headers/hexBoard.hpp
        headers/Window.hpp
)

# Console version - COMMENTED OUT
# add_executable(Hex
#         main.cpp
#         ${HEX_SOURCES}
#         ${HEX_HEADERS}
# )
# target_include_directories(Hex PRIVATE headers)

# Qt GUI version
add_executable(HexQt
        src/main_qt.cpp
        ${HEX_SOURCES}
        ${HEX_HEADERS}
        ${HEX_QT_SOURCES}
        ${HEX_QT_HEADERS}
        src/Window.ui
)

target_include_directories(HexQt PRIVATE headers)
target_link_libraries(HexQt
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
)

# Test executable
add_executable(HexTests
        test/test.cpp
        ${HEX_SOURCES}
        ${HEX_HEADERS}
)
target_include_directories(HexTests PRIVATE headers)

enable_testing()
add_test(NAME HexTests COMMAND HexTests)