//
// Created by Stephen Donlin on 12/3/25.
//

#ifndef HEX_UTILS_HPP
#define HEX_UTILS_HPP

#include <utility>
#include "coords.hpp"


namespace utils {
    std::pair<int, int> offset_to_axial(int row, int col);
    std::pair<int, int> axial_to_offset(int q, int r);



}

#endif //HEX_UTILS_HPP
