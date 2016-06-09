//
//  Background.cpp
//  SuperTeacher
//
//  Created by Samuel Dolt on 03.05.16.
//
//

#include "Background.h"
#include "Constants.h"

Background::Background(std::shared_ptr<ResourceManager> resource, std::string level_name, sf::IntRect PlaySpaceInit){
    
    m_resource = resource;
    
    auto level = m_resource->get_json("levels/" + level_name + ".json");
    
    auto background_config = (*level)["background"];
    
    std::string fill_name = background_config["fill"];
    
    auto fill_texture = m_resource->get_texture("graphics/backgrounds/" + fill_name + ".png");
    fill_texture->setRepeated(true);
    auto fill_sprite = std::make_shared<sf::Sprite>();
    fill_sprite->setTexture(*fill_texture);
    fill_sprite->setTextureRect(PlaySpaceInit);
    fill_sprite->move(0, SCREEN_Y_PXSIZE-PlaySpaceInit.height);
    
    add_drawable(fill_sprite);
    
    
    auto objects = background_config["objects"];
    
    for(auto object: objects){
        std::string name = object["image"];
        auto texture = m_resource->get_texture("graphics/" + name + ".png");
        auto sprite = std::make_shared<sf::Sprite>();
        sprite->setTexture(*texture);
        int x = object["x"];
        int y = object["y"];
        float size = object["size"];
        sprite->setScale(size, size);
        sprite->move( x * BLOCK_PXSIZE, y * BLOCK_PXSIZE);
        add_drawable(sprite);
    }
}
