//
// Created by samuel on 31.03.16.
//

#include "RessourceManager.h"

#include "Path.h"

using namespace std;

std::shared_ptr<sf::Music> ResourceManager::get_music(std::string id){
    auto music = make_shared<sf::Music>();
    if(!music->openFromFile(get_file(id))){
        abort();
    }

    return music;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(std::string id) {
    auto texture = make_shared<sf::Texture>();
    if(!texture->loadFromFile(get_file(id))){
       abort();
    }

    return texture;
}

std::shared_ptr<sf::Font> ResourceManager::get_font(std::string id) {
    auto font = make_shared<sf::Font>();
    if(!font->loadFromFile(get_file(id))){
       abort();
    }

    return font;
}
