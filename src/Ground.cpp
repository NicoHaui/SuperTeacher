//
//  Sol.cpp
//  SuperTeacher
//
//  Created by Etienne Houriet on 17.05.16.
//
//

#include "Ground.h"
#include "Constants.h"

Ground::Ground(std::shared_ptr<ResourceManager> resource, std::string level_name) {

    m_resource = resource;

    auto level = m_resource->get_json("levels/" + level_name + ".json");

    auto ground_config = (*level)["ground"];

    std::string fill_name = ground_config["name"];
    // Fill seting
    auto texture = m_resource->get_texture("graphics/grounds/"+  fill_name + "/fill.png");
    texture->setRepeated(true);
    auto fill_sprite = std::make_shared<sf::Sprite>();
    fill_sprite->setTexture(*texture);
    
    fill_sprite->setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE*BLOCK_FACTOR, (SCREEN_Y_BLOCKS - (int) ground_config["level"]- (int) ground_config["size"])*BLOCK_PXSIZE));
    fill_sprite->move(0, ((float)ground_config["size"] + (int) ground_config["level"]) * BLOCK_PXSIZE);

    // Top seting
    texture = m_resource->get_texture("graphics/grounds/" + fill_name + "/top.png");
    texture->setRepeated(true);
    auto top_sprite = std::make_shared<sf::Sprite>();
    top_sprite->setTexture(*texture);

    // Resizing (top)
    auto factor = (texture->getSize().y/BLOCK_PXSIZE);
    top_sprite->scale((float)ground_config["size"] /factor,(float)ground_config["size"] /factor);

    top_sprite->setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE*BLOCK_FACTOR, factor*BLOCK_PXSIZE));
    top_sprite->move(0, (int) ground_config["level"] * BLOCK_PXSIZE);

    // Print
    add_drawable(fill_sprite); 
    add_drawable(top_sprite);
}
