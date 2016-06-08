//
//  Interactives.cpp
//  SuperTeacher
//
//  Created by Etienne Houriet on 06.06.16.
//
//

#include "Interactives.h"
#include "Constants.h"
#include <algorithm>

function_enum string_conv(std::string text)
{
    function_enum convert_val=nothing;
    if (text == "platform")
    {
        convert_val = platform;
    }
    if (text == "bonus")
    {
        convert_val = bonus;
    }
    if (text == "mob")
    {
        convert_val = mob;
    }
    if (text == "charge")
    {
        convert_val = charge;
    }
    return convert_val;
}

Interactives::Interactives(std::shared_ptr<ResourceManager> resource, std::string level_name) {

    m_resource = resource;

    auto level = m_resource->get_json("levels/" + level_name + ".json");

    auto objects = (*level)["interactive"];
    
    for (auto object : objects) {
        std::string name = object["image"];
        auto texture = m_resource->get_texture("graphics/" + name + ".png");
        auto temp = std::make_shared<sf::Sprite>();
        auto sprite = std::make_shared<act_pack>();
        temp->setTexture(*texture);
        float x = object["x"];
        float y = object["y"];
        temp->setScale(object["size"], object["size"]);
        sprite->scale = object["size"];
        temp->move(x*BLOCK_PXSIZE, y*BLOCK_PXSIZE-temp->getGlobalBounds().height);
        sprite->sprite = temp;
        sprite->function = string_conv(object["function"]);
        if (sprite->function == mob || sprite->function == bonus || sprite->function == charge)
        {
            sprite->value = object["value"];
        }
        sprite->use = false;
        sprite->deleteFlag = false;
        m_sprites.push_back(sprite);
        //add_drawable(sprite->sprite);
    }
}


colision Interactives::update(Character& mainPerson, std::shared_ptr<sf::Text> score, int GroundLevel)
{
    colision col;
    static float val = 0;
    val += 0.2;
    static int points = 0;
    bool no_col = true;
    bool del_pack = false;
    bool del_pen = false;
    auto rect = mainPerson.get_rectangle();
    auto pencil = mainPerson.getPencil();
    //void *supp = NULL;
    col.walk_level = GroundLevel;//658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    col.right_enable = true;
    col.left_enable = true;
    for (auto& pack : m_sprites)
    {
        if (pack->function == platform)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {

                if (((rect.top) <= pack->sprite->getGlobalBounds().top + SECUR_SPACE &&
                    rect.left < pack->sprite->getGlobalBounds().left+pack->sprite->getGlobalBounds().width - SECUR_SPACE &&
                    rect.left + rect.width > pack->sprite->getGlobalBounds().left + SECUR_SPACE) ||
                    ((rect.top + rect.height) <= pack->sprite->getGlobalBounds().top + 1 &&
                    rect.left < pack->sprite->getGlobalBounds().left+pack->sprite->getGlobalBounds().width - 1 &&
                    rect.left + rect.width > pack->sprite->getGlobalBounds().left + 1))
                {
                    col.walk_level = pack->sprite->getGlobalBounds().top+1;// - rect.height + 1;
                }
                else if (rect.left + rect.width / 2 >= pack->sprite->getGlobalBounds().left + pack->sprite->getGlobalBounds().width / 2&&
                         (rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col.left_enable = false;
                    //col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                else if((rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col.right_enable = false;
                    //col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                no_col = false;
            }
        }
        if (pack->function == bonus)
        {
            pack->sprite->setScale(pack->scale + (pack->scale*sin(val/FLASH_SPEED_FACTOR) / FLASH_SIZE_FACTOR), pack->scale + (pack->scale*sin(val/FLASH_SPEED_FACTOR) / FLASH_SPEED_FACTOR));
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                points += pack->value;
                pack->deleteFlag = true;
                del_pack = true;
            }

        }
        if (pack->function == charge)
        {
            pack->sprite->setScale(pack->scale + (pack->scale*sin(val / FLASH_SPEED_FACTOR) / FLASH_SIZE_FACTOR), pack->scale + (pack->scale*sin(val / FLASH_SPEED_FACTOR) / FLASH_SPEED_FACTOR));
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                mainPerson.addPencil(pack->value);
                pack->deleteFlag = true;
                del_pack = true;
            }

        }
        if (pack->function == mob)
        {
            pack->sprite->move(cos(val / 5) * 10, 0);
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    points -= pack->value;
                }
                pack->use = true;
            }
            else
            {
                pack->use = false;
            }
            for(auto& pen : pencil)
            {
                if (pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()))
                {
                    pack->deleteFlag = true;
                    del_pack = true;
                    //break;
                }
            }
        }
        for (auto& pen : pencil)
        {
            if (pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()))
            {
                del_pen = true;
                //break;
            }
        }
        if (del_pen)
        {
            pencil.erase(std::remove_if(
                pencil.begin(),
                pencil.end(),
                [pack](auto pen) {return pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()); }));
        }
        del_pen = false;
        
    }
    mainPerson.setPencil(pencil);
    if (del_pack)
    {
        m_sprites.erase(std::remove_if(
            m_sprites.begin(),
            m_sprites.end(),
            [](auto x) {return x->deleteFlag; }));
    }
    
/*
    if (no_col == true)
    {
        col.left_enable = true;
        col.right_enable = true;
        col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    }*/
    score->setString("Points: " + std::to_string(points));
    return col;
}

std::vector<std::shared_ptr<sf::Drawable>> Interactives::get_drawables(void)
{
    std::vector<std::shared_ptr<sf::Drawable>> drawable;
    for (auto n : m_drawable)
    {
        drawable.push_back(n);
    }
    for (auto n : m_sprites)
    {
        drawable.push_back(n->sprite);
    }
    return drawable;
}