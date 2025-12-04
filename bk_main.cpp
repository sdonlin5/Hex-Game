// ---------- test runner main ----------

int main() {
    bool all_ok = true;

    all_ok &= test_round_trip_offset_axial(3);   // small
    all_ok &= test_round_trip_offset_axial(5);   // medium
    all_ok &= test_round_trip_offset_axial(11);  // your default size

    all_ok &= test_neighbors_center();
    all_ok &= test_neighbors_edges();

    all_ok &= test_unionfind_basic();

    if (all_ok) {
        std::cout << "\nALL TESTS PASSED ✅\n";
        return 0;
    } else {
        std::cerr << "\nSOME TESTS FAILED ❌\n";
        return 1;
    }
}
