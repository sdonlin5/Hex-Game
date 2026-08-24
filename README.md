# Hex

A two-player desktop version of the board game Hex built in C++ using the Qt6 framework for the graphical interface.

Hex is a two-player game strategy game where two players compete by placing stones on a rhombus-shaped board of hexagonal tiles. The first player to create an unbroken chain of adjoining stones between their two assigned sides, top/bottom or left/right, wins the game. Games are typically played on an 11x11 board; however, the size can vary to include larger or smaller-sized boards. 

The properties of the game board ensure that each match ends with a decisive winner. The “Hex Theorem” states that no matter how the board is filled, there will be one, and only one, player that has connected their edges of the board. To account for the advantage of being the first player (A) to play a move, the swap rule states that after player A (red) plays the first move, player B (blue) can decide whether to swap colors. If player B opts to swap colors, they become red, and player A becomes blue. Whichever player ends up playing the blue stones makes the next move.


## Build and Run
### Prerequisites
- CMake 3.16 or higher
- C++ Compiler (g++ / clang)
- Qt6 for GUI (for the GUI)

#### GUI Build
```
# From the repository root
mkdir build && cd build
cmake - B build -DQT_DIR_PATH=YOUR_QT_PATH
cmake --build . -j
./HexQT 		# Runs the GUI
./HexTests      # runs the console unit tests
```

**Note:** If the argument `-DQT_DIR_PATH=YOUR_QT_PATH` is committed, CMake’s normal Qt discovery is used (system, Qt6_DIR env variable… ).

#### Console Test Build

```
# From the repository root
mkdir build && cd build
cmake --build . --target HexTests
./HexTests  
```

## Known Issues
- `HexBoard` GUI controller class is not complete, it will included the following features
  - Board initialization
  - Pause/Resume
  - Sound
  - Timer with expiration notification
- `Window` class drives the entire game. Because the `HexBoard` controller was not complete, the entire game is driven from the `Window` class. This was the initial design to ensure functionality but was not intended to be the final product. 


## Additional Details

The codebase consists of three layers:   

**Core Game:** C++17 with no Qt dependency. Can be compiled independently of the graphical interface for testing. 

**Qt GUI:** Used to build the user interface and interactivity used in playing the game. 

**Tests:** Assertion-based test runner executable.


### Design Patterns and Idioms

#### Singleton 
`GameManager::GetInstance()` is a Meyers-style static member to ensure a no additional instances of `GameManager` can manipulate data. 

#### Hexagon Coordinate Systems
Two coordinate systems are used for game tiles: 
- Offset (row, col): for storage and on-screen rendering.
- Axial (q, r): for neighbor arithmetic.

#### Disjoint-Set / Union-Find Forest Data Structure
The game uses a disjoint-set forest data structure (one for each player) with a union-by-rank + path compression algorithm to query for connectivity in near O(1) time. 

#### Virtual Tiles
Instead of checking whether any stone is adjacent to row (or column) `0` and `N-1`, any stone placed on the edge of the board is unioned with a virtual tile representing the edge, allowing for a single call to find the root of the node and detect the win.

#### Observer
The Qt layer implements the Observer pattern throughout for signaling. 


