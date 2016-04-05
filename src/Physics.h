#pragma once

#include <array>
#include <bitset>

#include "Constants.h"

class Physics {
public:
    // add_
private:
    std::array<std::bitset<SCREEN_X_BLOCKS>, SCREEN_Y_BLOCKS> blocks;
};
