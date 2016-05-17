#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"

class Ground : public Object {
public:
    Ground(std::shared_ptr<ResourceManager> ressource, std::string level_name);
private:
    std::shared_ptr<ResourceManager> m_resource;
};
