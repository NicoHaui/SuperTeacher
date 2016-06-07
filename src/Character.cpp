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
    colisi.walk_level = 658 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] ));
    m_superteacher->move(0,colisi.walk_level);
    
    auto animation_texture = resource->get_texture("graphics/characters/spritefile.png");
    m_animation = std::make_shared<sf::Sprite>();
    m_animation->setTexture(*animation_texture);
    animation_texture->setSmooth(true);
    m_animation->move(10,colisi.walk_level);
    m_animation->setScale(0.4, 0.4);
    
    auto throw_texture = resource->get_texture("graphics/characters/pencil.png");
    m_throw = std::make_shared<sf::Sprite>();
    m_throw->setTexture(*throw_texture);
    throw_texture->setSmooth(true);
    m_throw->move(10,colisi.walk_level);
    m_throw->setScale(0.1, 0.1);
    
    auto animation_student_texture = resource->get_texture("graphics/characters/student.png");
    m_student_animation = std::make_shared<sf::Sprite>();
    m_student_animation->setTexture(*animation_student_texture);
    animation_texture->setSmooth(true);
    m_student_animation->move(800,colisi.walk_level);
    m_student_animation->setScale(0.25, 0.25);
    
    auto transparent_texture = resource->get_texture("graphics/characters/transparent.png");
    m_transparent = std::make_shared<sf::Sprite>();
    m_transparent->setTexture(*transparent_texture);
    
    static sf::Vector2i source(0,0);
    m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1200));
   
    add_drawable(m_throw);
    add_drawable(m_student_animation);
    add_drawable(m_animation);
    jumpLevel = JUMP;
}

void Character::process_event(HIEvent event){

    static sf::Vector2i source(0,0);
    static int counter1 = 0;
    static bool enable = 0;
    static int flag = 0;
    static int flag1 = 1;
    static int flag2 = 0;
    static int collisionflag1 = 0;
    static int collisionflag2 = 0;
    static int jumpcnt = 0;
    static int jumpcnt2 = 0;
    static int speed = SPEED;
    
    switch(event) {
        case HIEvent::GO_LEFT:
            throw_manager(m_transparent,m_animation->getPosition().x,m_animation->getPosition().y,0);
         
            if(colisi.left_enable)
            {
                m_animation->move(-speed,0);
                collisionflag1 = 0;
                collisionflag2 = 1;
            }
            if(m_animation->getPosition().y == colisi.walk_level)
            {
                flag = 0;
            }
            if(flag == 0)
            {
                if (flag2 == 0)
                {
                    source.x = 0;
                    flag2 = 1;
                    flag1 = 0;
                }
                source.y = 1;
                m_animation->setTextureRect(sf::IntRect(source.x * 670,source.y * 1150,700,1200));
                counter1++;
                if(counter1 >= 25/speed)
                {
                    source.x++;
                    counter1 = 0;
                }
                if(source.x >= 8)
                {
                    source.x = 0;
                }
            }
            break;
        case HIEvent::FAST_DOWN:
            speed = 2*SPEED;
            jumpLevel = JUMP * 4 / 3;
            break;
        case HIEvent::FAST_UP:
            speed = SPEED;
            jumpLevel = JUMP;
            break;
        case HIEvent::GO_RIGHT:
            throw_manager(m_transparent,m_animation->getPosition().x,m_animation->getPosition().y,0);
            if(colisi.right_enable)
            {
                m_animation->move(speed,0);
                collisionflag1 = 1;
                collisionflag2 = 0;
            }
            if(m_animation->getPosition().y == colisi.walk_level)
            {
                flag = 0;
            }
            if(flag == 0)
            {
                if(flag1 == 0)
                {
                    source.x = 0;
                    flag1 = 1;
                    flag2 = 0;
                }
                m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1200));
                counter1++;
                if(counter1 >= 25/speed)
                {
                    source.x++;
                    counter1 = 0;
                }
                if(source.x >= 8)
                {
                    source.x = 0;
                }
            }
            break;

        case HIEvent::JUMP:
            
            jump_manager(m_animation, colisi.walk_level, -jumpLevel, 0);
            throw_manager(m_transparent,m_animation->getPosition().x,m_animation->getPosition().y,0);
            flag = 1;
            if(flag1 == 1)
            {
                m_animation->setTextureRect(sf::IntRect(9 * 590,source.y,900,1200));
            }
            else
            {
                source.y = 1;
                m_animation->setTextureRect(sf::IntRect(8 * 676,source.y * 1150,900,1200));
            }
            break;
        case HIEvent::GO_UP:
            //jumpLevel--;
            break;
        case HIEvent::GO_DOWN:
            //jumpLevel++;
            break;
        case HIEvent::THROW:
            enable = 1;
            throw_manager(m_throw,m_animation->getPosition().x,m_animation->getPosition().y,enable);
            m_animation->setTextureRect(sf::IntRect(9 * 590,source.y,900,1200));
            break;
        default:
            if(m_animation->getPosition().y == colisi.walk_level)
            {
                flag = 0;
                if(flag1 == 1)
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 660,source.y,700,1200));
                }
                else
                {
                    source.y = 1;
                    m_animation->setTextureRect(sf::IntRect(0 * 670,source.y * 1150,700,1200));
                }
            }
            if(m_throw->getPosition().x == (m_animation->getPosition().x + MISSILE_OFFSET_X))
            {
                enable = 0;
                throw_manager(m_transparent,m_animation->getPosition().x,m_animation->getPosition().y,enable);
            }
            else
            {
                throw_manager(m_throw,m_animation->getPosition().x,m_animation->getPosition().y,enable);
            }
            break;
    }
}



void Character::update()
{
    int collisionflag3 = 0;
    if(!get_rectangle().intersects(m_student_animation->getGlobalBounds()))
    {
        collisionflag3 = 0;
    }
    jump_manager(m_animation, colisi.walk_level, 0,collisionflag3);
    
}

int Character::getJumpLevel(void)
{
    return jumpLevel;
}

sf::FloatRect Character::get_rectangle(void)
{
    return m_animation->getGlobalBounds();
}


void Character::write_collision(colision coll)
{
    colisi = coll;
}