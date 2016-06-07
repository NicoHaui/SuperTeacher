#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class Pencil : public Object {
public:
    Pencil(std::shared_ptr<ResourceManager> ressource, float posx, float posy, int direction);
    void update(void);
private:
    std::shared_ptr<ResourceManager> m_resource;
    std::shared_ptr<sf::Sprite> m_pencil;
    int m_direction;
};
