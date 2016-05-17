//
//  Background.cpp
//  SuperTeacher
//
//  Created by Samuel Dolt on 03.05.16.
//
//

#include "Character.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Physics.h"

Character::Character(std::shared_ptr<ResourceManager> resource, std::string level_name){

    
    
    m_resource = resource;
    auto level = m_resource->get_json("levels/" + level_name + ".json");
    
    
    auto superteacher_texture = resource->get_texture("graphics/characters/superteacher.png");
    m_superteacher = std::make_shared<sf::Sprite>();
    m_superteacher->setTexture(*superteacher_texture);
    const int MINLEVEL = 658 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] ));
    m_superteacher->move(0,MINLEVEL );
    
    auto animation_texture = resource->get_texture("graphics/characters/spritefile.png");
    m_animation = std::make_shared<sf::Sprite>();
    m_animation->setTexture(*animation_texture);
    animation_texture->setSmooth(true);
    m_animation->move(10,MINLEVEL);
    m_animation->setScale(0.4, 0.4);
    
    static sf::Vector2i source(0,0);
    m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1500));
    
    add_drawable(m_animation);
    jumpLevel = 0;
}

void Character::process_event(HIEvent event){

    static sf::Vector2i source(0,0);
    static int counter1 = 0;
    
    auto superteacher_texture = m_resource->get_texture("graphics/characters/superteachersaut.png");

    switch(event) {
        case HIEvent::GO_LEFT:
            m_animation->move(-5,0);
            //m_superteacher->move(-5, 0);
            break;
        case HIEvent::GO_RIGHT:
            m_animation->move(5,0);
            m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1500));
            //m_superteacher->move(5,0);
            counter1++;
            if(counter1 >= 5)
            {
                source.x++;
                counter1 = 0;
            }
            if(source.x >= 8)
            {
                source.x = 0;
            }
            break;

        case HIEvent::JUMP:
            //jump_manager(m_superteacher, MINLEVEL, -levelJump);
            jump_manager(m_animation, 16, jumpLevel);
            //m_superteacher->setTexture(*superteacher_texture);
            //m_superteacher->setScale(1.2,1.2);
            //m_animation
            //add_drawable(m_superteacher);
            break;
        case HIEvent::GO_UP:
            jumpLevel--;
            break;
        case HIEvent::GO_DOWN:
            jumpLevel++;
            break;
        default:
            break;
            
            
    }

}


void Character::update(void)
{
    auto level = m_resource->get_json("levels/level.json");
    jump_manager(m_animation, 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-(int)(*level)["ground"]["level"])), 0);
    
}

int Character::getJumpLevel(void)
{
    return -jumpLevel;
}
/*
std::vector<std::shared_ptr<sf::Drawable>> Object::get_drawables(void)
{
    std::vector<std::shared_ptr<sf::Drawable>> all;
    all.reserve(m_drawable.size() + 1);
    //all.push_back((();
    for (auto n : m_drawable)
    {
        all.push_back(n);
    }
    return m_drawable;
}*/