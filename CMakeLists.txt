cmake_minimum_required(VERSION 3.16)
project(Hex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# For homebrew cmake install
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/ui
)

# Core engine sources (no Qt) used by both the game and the tests
set(ENGINE_SOURCES
        src/hex.cpp
        src/board.cpp
        src/gameManager.cpp
        src/unionFind.cpp
        src/utils.cpp
        # if needed by engine/tests
)

set(ENGINE_HEADERS
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
        # if needed
)

# Qt UI sources (only for the Hex GUI app)
set(UI_SOURCES
        src/Window.cpp
        src/hexBoard.cpp
        src/hexTile.cpp         # your graphics item, if used
)

set(UI_HEADERS
        headers/Window.hpp
        src/HexBoard.cpp
        headers/hexTile.hpp
)

set(UI_FORMS
        ui/Window.ui
)

# Main Hex program (Qt GUI)
add_executable(Hex
        main.cpp
        ${UI_FORMS}
        ${ENGINE_SOURCES}
        ${ENGINE_HEADERS}
        ${UI_SOURCES}
        ${UI_HEADERS}
)

# Test executable: engine + tests, **no Qt**
add_executable(HexTests
        test/test.cpp
        ${ENGINE_SOURCES}
        ${ENGINE_HEADERS}
)

target_include_directories(Hex PRIVATE headers)
target_include_directories(HexTests PRIVATE headers)

target_link_libraries(Hex
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

enable_testing()
add_test(NAME HexTests COMMAND HexTests)