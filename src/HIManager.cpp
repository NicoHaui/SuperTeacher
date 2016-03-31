//
// Created by samuel on 31.03.16.
//

#include "HIManager.h"

int8_t HIManager::process() {

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
                        case sf::Keyboard::Left:
                            HIEvent_sig(HIEvent::GO_LEFT);
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

}
