#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Path.h"

using namespace std;

int main(int argc, char *argv[]) {

    sf::RenderWindow window(
            sf::VideoMode(800, 600), "SuperTeacher"
    );

    sf::Font font;
    if(!font.loadFromFile(FONT_INDIE_FLOWER)){
        return -1;
    }

    sf::Music song;
    if(!song.openFromFile(SONG_1)){
        return -1;
    }

    sf::Text text("Hello SuperTeacher", font, 50);
    text.move(25,25);

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);
    shape.move(25,200);

    cout << "SuperTeaching is starting..." << endl;

    song.play();
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){

            switch(event.type){

                // Window manager request a close
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Right:
                            shape.move(10,0);
                            break;
                        case sf::Keyboard::Left:
                            shape.move(-10,0);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);

        // Dessin


        window.draw(shape);
        window.draw(text);



        window.display();
    }


    fprintf(stdout, "Window is closing\n");
    return 0;
}
