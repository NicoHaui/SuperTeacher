//
// Created by samuel on 31.03.16.
//

#include "ResourceManager.h"

#include <fstream>
#include "Path.h"


using namespace std;
std::shared_ptr<sf::Music> ResourceManager::get_music(std::string key){
        auto music = make_shared<sf::Music>();
        if(!music->openFromFile(get_file(key))){
            abort();
        }
    
        return music;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(std::string key) {
    if(m_texture_cache.count(key)){
        
        return m_texture_cache[key];
    } else {
    
        auto texture = make_shared<sf::Texture>();
        if(!texture->loadFromFile(get_file(key))){
            abort();
        }
        
        m_texture_cache[key] = texture;

        return texture;
    }
}

std::shared_ptr<const sf::Font> ResourceManager::get_font(std::string key) {
    if (m_font_cache.count(key)) {
        
        return m_font_cache[key];
    } else {
        
        auto font = make_shared<sf::Font>();
        if(!font->loadFromFile(get_file(key))){
            abort();
        }

        m_font_cache[key] = font;
        
        return font;
    }
}

std::shared_ptr<const json> ResourceManager::get_json(std::string key){
    if(m_json_cache.count(key)){
        return m_json_cache[key];
    } else {
        
        auto object = make_shared<json>();
        std::ifstream ifs(get_file(key));
        
        ifs >> *object;
        
        m_json_cache[key] = object;
    
        return object;
    }
}
