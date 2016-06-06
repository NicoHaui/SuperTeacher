#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include "Character.h"
#include "Text.h"

typedef enum
{
    nothing,
    platform,
    bonus,
    mob
}function_enum;

typedef struct
{
    std::shared_ptr<sf::Sprite> sprite;
    function_enum function;
    bool use;
}act_pack;

class Interactives : public Object {
public:
    Interactives(std::shared_ptr<ResourceManager> ressource, std::string level_name);
    void update(Character mainPerson, std::shared_ptr<sf::Text> score);
private:
    std::shared_ptr<ResourceManager> m_resource;
    //std::vector<std::shared_ptr<sf::Sprite>> m_sprites;
    //std::vector<function> m_function;
    std::vector<std::shared_ptr<act_pack>> m_sprites;
};
