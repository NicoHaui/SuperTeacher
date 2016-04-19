#pragma once
#include <utility>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"


class Object {
public:
	//void add_drawable(std::shared_ptr<sf::Sprite> sprite);
    void add_drawable(std::shared_ptr<sf::Drawable> drawable);
    std::vector<std::shared_ptr<sf::Drawable>> get_drawables(void);
	//void add_drawable(std::shared_ptr<sf::Text> text);
private:
	/*int pos_x;
	int pos_y;
	int size_x;
	int size_y;
	bool repeat;*/
	/*enum type
	{
		type_sprite,
		type_text,
		type_null
	};*/
	//std::type_info m_type;
	
	//std::vector<std::shared_ptr<sf::Sprite>> m_sprites;
	//std::vector<std::shared_ptr<sf::Text>> m_texts;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawable;
	
};
