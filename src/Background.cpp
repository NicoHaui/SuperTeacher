//
//  Background.cpp
//  SuperTeacher
//
//  Created by Samuel Dolt on 03.05.16.
//
//

#include "Background.h"

Background::Background(std::shared_ptr<ResourceManager> resource, std::string level_name){
    
    m_resource = resource;
    
    auto level = m_resource->get_json("levels/" + level_name + ".json");
    
    auto background_config = (*level)["background"];
    
    std::string fill_name = background_config["fill"];
    
    
}
