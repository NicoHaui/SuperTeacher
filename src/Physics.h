#pragma once

#include <array>
#include <bitset>
#include <time.h>
#include <SFML\Graphics.hpp>

#include "Constants.h"
#include "HIManager.h"
#include "Logs.h"



void jump_manager( std::shared_ptr<sf::Sprite> sprite, float GroundLevel, int vitesseInit);
class Physics {
public:
    // add_
private:
    std::array<std::bitset<SCREEN_X_BLOCKS>, SCREEN_Y_BLOCKS> blocks;
};
