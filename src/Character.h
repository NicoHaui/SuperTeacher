#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include "HIManager.h"

    typedef struct {
    bool right_enable;
    bool left_enable;
    int walk_level;
    }colision;

class Character: public Object {
public:
    void process_event(HIEvent event);
    void update(void);
    Character(std::shared_ptr<ResourceManager> ressource, std::string level_name);
    int getJumpLevel(void);
    sf::FloatRect get_rectangle(void);
    void write_collision(colision coll);
private:
    std::shared_ptr<ResourceManager> m_resource;
    std::shared_ptr<sf::Sprite> m_animation;
    std::shared_ptr<sf::Sprite> m_throw;
    std::shared_ptr<sf::Sprite> m_student_animation;
    std::shared_ptr<sf::Sprite> m_superteacher;
    colision colisi;
    int jumpLevel;
    int MINLEVEL;
};
