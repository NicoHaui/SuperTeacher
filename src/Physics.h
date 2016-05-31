#pragma once

#include <array>
#include <bitset>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "HIManager.h"
#include "Logs.h"
#include <ctime>

typedef clock_t time_ms;
typedef clock_t time_s;

class Timer{
public:

    static time_ms get_time_ms();
    static time_s get_time_s();
    
private:
    
};

void jump_manager( std::shared_ptr<sf::Sprite> sprite, float GroundLevel, int vitesseInit);
class Physics {
public:
    // add_
private:
    std::array<std::bitset<SCREEN_X_BLOCKS>, SCREEN_Y_BLOCKS> blocks;
};
