#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Path.h"

using namespace std;

int main(int argc, char *argv[]) {

    sf::RenderWindow window(
            sf::VideoMode(800, 600), "SuperTeacher"
    );

    cout << "SRC:" << _SRC_DIR << endl;

    sf::Font font;
    std::string test = get_file(FONT_INDIE_FLOWER);
    if(!font.loadFromFile(get_file(FONT_INDIE_FLOWER))){
        cout << "FONT NOT FOUND" << endl;
        return -1;
    }

    sf::Music song;
    if(!song.openFromFile(get_file(SONG_1))){
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
						case sf::Keyboard::Up:
							shape.move(0, -10);
							break;
						case sf::Keyboard::Down:
							shape.move(0, 10);
							break;
						case sf::Keyboard::Escape:
							window.close();
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
