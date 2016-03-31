//
// Created by samuel on 31.03.16.
//
// Human Input Manager

#pragma once

#include <memory>
#include <boost/signals2.hpp>
#include <SFML/Window.hpp>

enum class HIEvent {
    GO_LEFT,
    GO_RIGHT,
    CLOSE,
};

class HIManager {
public:
    HIManager(sf::Window *window): window(window){};
    int8_t process();

    boost::signals2::signal<void (HIEvent)> HIEvent_sig;

private:
    sf::Event event;
    sf::Window* window;
};

