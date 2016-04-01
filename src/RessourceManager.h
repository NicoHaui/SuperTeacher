#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    std::shared_ptr<sf::Music> get_music(std::string id);
    std::shared_ptr<sf::Texture> get_texture(std::string id);
    std::shared_ptr<sf::Font> get_font(std::string id);
};
