//
//  Background.cpp
//  SuperTeacher
//
//  Created by Samuel Dolt on 03.05.16.
//
//

#include "Interactives.h"
#include "Constants.h"

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
    return convert_val;
}

Interactives::Interactives(std::shared_ptr<ResourceManager> resource, std::string level_name) {

    m_resource = resource;

    auto level = m_resource->get_json("levels/" + level_name + ".json");

    auto objects = (*level)["interactive"];

    /*std::string fill_name = background_config["fill"];

    auto fill_texture = m_resource->get_texture("graphics/backgrounds/" + fill_name + ".png");
    fill_texture->setRepeated(true);
    auto fill_sprite = std::make_shared<sf::Sprite>();
    fill_sprite->setTexture(*fill_texture);
    fill_sprite->setTextureRect(sf::IntRect(0, 0, 5000, 1080));

    add_drawable(fill_sprite);*/


    //auto objects = background_config["objects"];
    
    for (auto object : objects) {
        std::string name = object["image"];
        auto texture = m_resource->get_texture("graphics/" + name + ".png");
        //act_pack sprite;//
        auto temp = std::make_shared<sf::Sprite>();
        auto sprite = std::make_shared<act_pack>();
        /*sprite.sprite.reset();
        sprite.sprite->setTexture(*texture);*/
        temp->setTexture(*texture);
        int x = object["x"];
        int y = object["y"];
        //sprite.sprite->move(x * BLOCK_PXSIZE, y * BLOCK_PXSIZE);
        temp->move(x*BLOCK_PXSIZE, y*BLOCK_PXSIZE);
        temp->setScale(object["size"], object["size"]);
        sprite->sprite = temp;
        //sprite->sprite->setOrigin((sprite->sprite->getGlobalBounds().width / 2), (sprite->sprite->getGlobalBounds().height / 2));
        //sprite->sprite->move((sprite->sprite->getGlobalBounds().width / 2), (sprite->sprite->getGlobalBounds().height / 2));
        //add_drawable(sprite);
        sprite->function = string_conv(object["function"]);
        sprite->use = false;
        m_sprites.push_back(sprite);
        //m_function.push_back((function)object["function"]);
        add_drawable(sprite->sprite);
    }
}


colision Interactives::update( sf::FloatRect rect, std::shared_ptr<sf::Text> score)
{
    colision col;
    static float val = 0;
    val += 0.2;
    static int points = 0;
    bool no_col = true;
    for (auto pack : m_sprites)
    {
        if (points == -5)
        {
            auto texture = m_resource->get_texture("graphics/interactives/point0.png");
            pack->sprite->setTexture(*texture);
        }
        if (pack->function == platform)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if ((rect.top ) <= pack->sprite->getGlobalBounds().top - pack->sprite->getGlobalBounds().height+10)
                {
                    col.walk_level = pack->sprite->getGlobalBounds().top-pack->sprite->getGlobalBounds().height;
                    //col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
        points = 0;
                }
                else if (rect.left + rect.width / 2 >= pack->sprite->getGlobalBounds().left + pack->sprite->getGlobalBounds().width / 2)
                {
                    col.left_enable = false;
                    col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                else
                {
                    col.right_enable = false;
                    col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                no_col = false;
            }

        }
        if (pack->function == bonus)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    auto texture = m_resource->get_texture("graphics/interactives/invisible.png");
                    pack->sprite->setTexture(*texture);
                    points++;
                }
                pack->use = true;
            }
            else
            {
                pack->use = false;
            }

        }
        if (pack->function == mob)
        {
            pack->sprite->move(cos(val / 5) * 10, 0);
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    points--;
                    //pack.sprite->setRotation(90);
                }
                pack->use = true;
            }
            else
            {
                pack->use = false;
            }
        }
    }
    if (no_col==true)
    {
        col.left_enable = true;
        col.right_enable = true;
        col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    }
    score->setString("Points: " + std::to_string(points));
    return col;
}