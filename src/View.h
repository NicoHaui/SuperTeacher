#pragma once
#include <SFML\Graphics.hpp>

#include "Constants.h"

class View
{
public:
    View(void);
    View(sf::FloatRect init);
    void process(void);
    sf::View GetView(void) { return view; };

private:
    sf::View view;
};