//
// Created by samuel on 01.04.16.
//

#include "Object.h"


void Object::add_drawable(std::shared_ptr<sf::Drawable> sprite)
{
	m_drawable.push_back(sprite);
}

std::vector<std::shared_ptr<sf::Drawable>> Object::get_drawables(void)
{
	return m_drawable;
}