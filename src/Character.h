#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"

class Character: public Object {
public:
    Character(std::shared_ptr<ResourceManager> ressource, std::string level_name);
private:
    std::shared_ptr<ResourceManager> m_resource;
};
