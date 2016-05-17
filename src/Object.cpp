//
// Created by samuel on 01.04.16.
//

#include "Object.h"

void Object::process_event(HIEvent event)
{
    
}

void Object::add_drawable(std::shared_ptr<sf::Drawable> drawable)
{
	m_drawable.push_back(drawable);
}

std::vector<std::shared_ptr<sf::Drawable>> Object::get_drawables(void)
{
	return m_drawable;
}