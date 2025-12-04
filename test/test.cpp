//
// Created by Stephen Donlin on 12/3/25.
//


#include <iostream>
#include <cassert>
#include <memory>

#include "../headers/utils.hpp"
#include "../headers/board.hpp"
#include "../headers/hex.hpp"
#include "../headers/unionFind.hpp"

//  utils tests
bool test_round_trip_offset_axial(int N) {
    std::cout << "[TEST] round-trip offset <-> axial for " << N << "x" << N << " board\n";

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            auto [q, r] = utils::offset_to_axial(row, col);
            auto [row2, col2] = utils::axial_to_offset(q, r);

            if (row != row2 || col != col2) {
                std::cerr << "  MISMATCH at (row,col)=(" << row << "," << col << ")\n"
                          << "    axial(q,r)=(" << q << "," << r << ")\n"
                          << "    back to (row2,col2)=(" << row2 << "," << col2 << ")\n";
                return false;
            }
        }
    }

    std::cout << "  OK: all offset <-> axial round-trips match\n";
    return true;
}

//  Board / neighbor tests
bool test_neighbors_center() {
    std::cout << "[TEST] neighbors for a center tile\n";

    const int N = 5;
    Board board(N);
    board.Build(N);

    // centet tile
    int center_row = 2;
    int center_col = 2;

    auto [center_q, center_r] = utils::offset_to_axial(center_row, center_col);
    auto center_tile = board.GetTile(center_q, center_r);

    auto neighbors = board.GetNeighbors(center_tile->GetCoords());

    std::cout << "  center: " << center_tile->StringifyCoords() << "\n";
    std::cout << "  neighbors:\n";
    for (const auto& n : neighbors) {
        std::cout << "    " << n->StringifyCoords() << "\n";
    }

    // 5x5 board, geometric center = 6 neighbors
    if (neighbors.size() != 6) {
        std::cerr << "  Expected 6 neighbors, got " << neighbors.size() << "\n";
        return false;
    }

    // neighbors must not be null
    for (const auto& n : neighbors) {
        if (!n) {
            std::cerr << "  Found null neighbor pointer\n";
            return false;
        }
    }

    std::cout << "  OK: center tile has 6 non-null neighbors\n";
    return true;
}

bool test_neighbors_edges() {
    std::cout << "[TEST] neighbors for some edge tiles\n";

    const int N = 5;
    Board board(N);
    board.Build(N);

    // Some edge offset coords to sample
    std::pair<int, int> edge_offsets[] = {
        {0, 0},          // top-left
        {0, N - 1},      // top-right
        {N - 1, 0},      // bottom-left
        {N - 1, N - 1},  // bottom-right
    };

    for (auto [row, col] : edge_offsets) {
        auto [q, r] = utils::offset_to_axial(row, col);
        auto tile = board.GetTile(q, r);
        auto neighbors = board.GetNeighbors(tile->GetCoords());

        std::cout << "  tile " << tile->StringifyCoords()
                  << " (row=" << row << ", col=" << col << ")\n";
        std::cout << "    neighbors:\n";
        for (const auto& n : neighbors) {
            std::cout << "      " << n->StringifyCoords() << "\n";
        }

        // all neighbors must be in bounds and non-null
        for (const auto& n : neighbors) {
            if (!n) {
                std::cerr << "    ERROR: null neighbor\n";
                return false;
            }
        }
    }

    std::cout << "  OK: edge tiles have valid, non-null neighbors\n";
    return true;
}

// UnionFind tests

bool test_unionfind_basic() {
    std::cout << "[TEST] UnionFind basic connectivity\n";

    UnionFind uf;

    auto a = std::make_shared<Hex>(0, 0);
    auto b = std::make_shared<Hex>(1, 0);
    auto c = std::make_shared<Hex>(2, 0);

    uf.MakeSet(a);
    uf.MakeSet(b);
    uf.MakeSet(c);

    auto root_a = uf.FindRoot(a);
    auto root_b = uf.FindRoot(b);
    auto root_c = uf.FindRoot(c);

    // Initially each should be its own root
    assert(root_a == a);
    assert(root_b == b);
    assert(root_c == c);
    assert(root_a != root_b);
    assert(root_a != root_c);
    assert(root_b != root_c);

    // Union a, b
    uf.Union(a, b);
    root_a = uf.FindRoot(a);
    root_b = uf.FindRoot(b);

    if (root_a != root_b) {
        std::cerr << "  ERROR: after Union(a,b), roots differ\n";
        return false;
    }

    // c should  be separate
    root_c = uf.FindRoot(c);
    if (root_c == root_a) {
        std::cerr << "  ERROR: c incorrectly connected to a/b\n";
        return false;
    }

    // union b and c
    uf.Union(b, c);
    root_a = uf.FindRoot(a);
    root_b = uf.FindRoot(b);
    root_c = uf.FindRoot(c);

    if (!(root_a == root_b && root_b == root_c)) {
        std::cerr << "  ERROR: after Union(b,c), not all three share root\n";
        return false;
    }

    std::cout << "  OK: UnionFind connects a, b, c as expected\n";
    return true;
}

//  test runner main

int main() {
    bool all_ok = true;

    all_ok &= test_round_trip_offset_axial(3);   // small
    all_ok &= test_round_trip_offset_axial(5);   // medium
    all_ok &= test_round_trip_offset_axial(11);  // your default size

    all_ok &= test_neighbors_center();
    all_ok &= test_neighbors_edges();

    all_ok &= test_unionfind_basic();

    if (all_ok) {
        std::cout << "\nALL TESTS PASSED\n";
        return 0;
    } else {
        std::cerr << "\nSOME TESTS FAILED\n";
        return 1;
    }
}