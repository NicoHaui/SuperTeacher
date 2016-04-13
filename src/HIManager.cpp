//
// Created by samuel on 31.03.16.
//

#include "HIManager.h"

void HIManager::process(void) {

        while(window->pollEvent(event)){

            switch(event.type){

                // Window manager request a close
                case sf::Event::Closed:
                    HIEvent_sig(HIEvent::CLOSE);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Right:
                            HIEvent_sig(HIEvent::GO_RIGHT);
                            break;
						case sf::Keyboard::Escape:
                            HIEvent_sig(HIEvent::CLOSE);
							break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			HIEvent_sig(HIEvent::GO_LEFT);
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			HIEvent_sig(HIEvent::GO_RIGHT);
		};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			HIEvent_sig(HIEvent::GO_UP);
		};
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			HIEvent_sig(HIEvent::GO_DOWN);
		};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            HIEvent_sig(HIEvent::JUMP);
        };
}

