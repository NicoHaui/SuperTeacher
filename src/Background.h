#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"

class Background: public Object {
public:
    Background(std::shared_ptr<ResourceManager> ressource, std::string level_name, sf::IntRect PlaySpaceInit);
private:
    std::shared_ptr<ResourceManager> m_resource;
};
