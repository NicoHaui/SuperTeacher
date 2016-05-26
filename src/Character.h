#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include "HIManager.h"

class Character: public Object {
public:
    void process_event(HIEvent event);
    void update(void);
    Character(std::shared_ptr<ResourceManager> ressource, std::string level_name);
    int getJumpLevel(void);
private:
    std::shared_ptr<ResourceManager> m_resource;
    std::shared_ptr<sf::Sprite> m_animation;
    std::shared_ptr<sf::Sprite> m_superteacher;
    int jumpLevel;
    int MINLEVEL;
};
