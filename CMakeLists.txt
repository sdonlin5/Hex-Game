cmake_minimum_required(VERSION 3.16)

project(Hex VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.9.3")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(Hex
        main.cpp

        src/hex.cpp
        src/board.cpp
        src/gameManager.cpp
        src/unionFind.cpp
        src/utils.cpp

        headers/hex.hpp
        headers/state.hpp
        headers/column.hpp
        headers/row_labels.hpp
        headers/board.hpp
        headers/gameManager.hpp
        headers/unionFind.hpp
        headers/utils.hpp
        #src/player.cpp
        #headers/player.h
)

target_link_libraries(Hex
        Qt::Core
        Qt::Gui
        Qt::Widgets
)