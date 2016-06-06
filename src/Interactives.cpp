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
        act_pack sprite;//
        auto temp = std::make_shared<sf::Sprite>();
        //auto sprite = act_pack();
        /*sprite.sprite.reset();
        sprite.sprite->setTexture(*texture);*/
        temp->setTexture(*texture);
        int x = object["x"];
        int y = object["y"];
        //sprite.sprite->move(x * BLOCK_PXSIZE, y * BLOCK_PXSIZE);
        temp->move(x*BLOCK_PXSIZE, y*BLOCK_PXSIZE);
        temp->setScale(object["size"], object["size"]);
        sprite.sprite = temp;
        sprite.sprite->setOrigin((sprite.sprite->getGlobalBounds().width / 2), (sprite.sprite->getGlobalBounds().height / 2));
        sprite.sprite->move((sprite.sprite->getGlobalBounds().width / 2), (sprite.sprite->getGlobalBounds().height / 2));
        //add_drawable(sprite);
        sprite.function = string_conv(object["function"]);
        m_sprites.push_back(sprite);
        //m_function.push_back((function)object["function"]);
        add_drawable(sprite.sprite);
    }
}

void Interactives::update(Character mainPerson)
{
    
    /*static float val = 0;
    val+=0.2;*/
    for (auto pack : m_sprites)
    {
        if (pack.function == platform)
        {

        }
        if(pack.function == bonus)
        {
            if (mainPerson.get_rectangle().intersects(pack.sprite->getGlobalBounds()))
            {
                if (!pack.use)
                {
                    auto texture = m_resource->get_texture("graphics/interactives/invisible.png");
                    pack.sprite->setTexture(*texture);
                }
                pack.use = true;
            }
            else
            {
                pack.use = false;
            }
            
        }
        if (pack.function == mob)
        {
            if (mainPerson.get_rectangle().intersects(pack.sprite->getGlobalBounds()))
            {
                if (!pack.use)
                {

                }
                pack.use = true;
            }
            else
            {
                pack.use = false;
            }
        }
    }
}
