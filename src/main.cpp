#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Path.h"
#include "AbstractView.h"
#include "RessourceManager.h"
#include "HIManager.h"

using namespace std;

static uint32_t SCREEN_SIZE[2] = {1920, 1080};

int main(int argc, char *argv[]) {

    sf::RenderWindow window(
            sf::VideoMode(SCREEN_SIZE[0], SCREEN_SIZE[1]), "SuperTeacher"
    );

    window.setFramerateLimit(50);
    HIManager user_input = {&window};
    ResourceManager resource = {};

    user_input.HIEvent_sig.connect([&window](HIEvent event)->void{
        switch(event) {
            case HIEvent::CLOSE:
                window.close();
                break;
            default:
                break;
        }
    });

    cout << "SRC:" << _SRC_DIR << endl;

    auto font = resource.get_font(FONT_INDIE_FLOWER);
    auto song = resource.get_music(SONG_1);

    sf::Text text("Hello SuperTeacher", *font, 50);
    text.move(25,25);

    auto bg_texture = resource.get_texture("graphics/tests/bg.png");
    bg_texture->setRepeated(true);

    sf::Sprite bg_sprite;
    bg_sprite.setTexture(*bg_texture);
    bg_sprite.setTextureRect(sf::IntRect(0,0,1920,1080));

    auto cloud_texture = resource.get_texture("graphics/tests/Items/cloud3.png");
    sf::Sprite cloud_sprite;
    cloud_sprite.setTexture(*cloud_texture);
    cloud_sprite.move(200,200);

    sf::Sprite cloud2_sprite;
    cloud2_sprite.setTexture(*cloud_texture);
    cloud2_sprite.move(400,175);

    sf::Texture ground_texture;
    ground_texture.loadFromFile(get_file("graphics/tests/Tiles/grassMid.png"));
    ground_texture.setRepeated(true);

    sf::Sprite ground_sprite;
    ground_sprite.setTexture(ground_texture);
    ground_sprite.setTextureRect(sf::IntRect(0, 0, 1920, 70));
    ground_sprite.move(0,1010);

    auto superteacher_texture = resource.get_texture("graphics/characters/superteacher.png");

    sf::Sprite superteacher;
    superteacher.setTexture(*superteacher_texture);
    superteacher.move(0,650);

    user_input.HIEvent_sig.connect([&superteacher](HIEvent event)->void{
        switch(event) {
            case HIEvent::GO_LEFT:
                superteacher.move(-10,0);
                break;
            case HIEvent::GO_RIGHT:
                superteacher.move(10,0);
            default:
                break;
            }
    });

    cout << "SuperTeaching is starting..." << endl;

    song->play();
    while(window.isOpen()){

        user_input.process();

        window.clear(sf::Color::White);

        // Dessin


        window.draw(bg_sprite);
        window.draw(ground_sprite);
        window.draw(cloud_sprite);
        window.draw(cloud2_sprite);
        window.draw(text);
        window.draw(superteacher);



        window.display();
    }


    fprintf(stdout, "Window is closing\n");
    return 0;
}
