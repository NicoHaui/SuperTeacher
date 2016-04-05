#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Constants.h"
#include "Path.h"
#include "AbstractView.h"
#include "ResourceManager.h"
#include "HIManager.h"
#include "Logs.h"

using namespace std;


int main(int argc, char *argv[]) {

    log_init();

    LOG(info)  << "Superteacher is starting";
    LOG(debug) << "SRC Directory: " << _SRC_DIR;
    LOG(debug) << "Install Prefix: " << _INSTALL_PREFIX;

    LOG(info) << "Opening window";
    LOG(debug) << "Window size: " << SCREEN_X_PXSIZE << "x" << SCREEN_Y_PXSIZE;

    ResourceManager resource = {};
    auto config = resource.get_json("conf.json");
    auto style = sf::Style::Default;

    if((bool)(*config)["video"]["fullscreen"]){
        style = sf::Style::Fullscreen;
    }

    sf::RenderWindow window(
            sf::VideoMode(SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE),
            "SuperTeacher",
            style
    );

    window.setFramerateLimit(50);
    HIManager user_input = {&window};


    user_input.HIEvent_sig.connect([&window](HIEvent event)->void{
        switch(event) {
            case HIEvent::CLOSE:
                window.close();
                break;
            default:
                break;
        }
    });


    auto level = resource.get_json("levels/level.json");
    auto font = resource.get_font(FONT_INDIE_FLOWER);
    auto song = resource.get_music(SONG_1);

    sf::Text text("Hello SuperTeacher", *font, 50);
    text.move(25,25);
    const std::string bg = (*level)["background"];
    auto bg_texture = resource.get_texture("graphics/backgrounds/" + bg + ".png");
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

    std::string gr_name = (*level)["ground"]["name"];
    auto ground_texture = resource.get_texture("graphics/grounds/" + gr_name + "/top.png");
    ground_texture->setRepeated(true);
    sf::Sprite ground_sprite;
    ground_sprite.setTexture(*ground_texture);
    ground_sprite.setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE, BLOCK_PXSIZE));
    ground_sprite.move(0,SCREEN_Y_PXSIZE - (BLOCK_PXSIZE * (SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] )));

    auto ground_fill_texture = resource.get_texture("graphics/grounds/" + gr_name + "/fill.png");
    ground_fill_texture->setRepeated(true);
    sf::Sprite ground_fill_sprite;
    ground_fill_sprite.setTexture(*ground_fill_texture);
    ground_fill_sprite.setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE, BLOCK_PXSIZE*(SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] ) - 1));
    ground_fill_sprite.move(0,SCREEN_Y_PXSIZE - (BLOCK_PXSIZE * (SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] - 1 )));


    auto superteacher_texture = resource.get_texture("graphics/characters/superteacher.png");

    sf::Sprite superteacher;
    superteacher.setTexture(*superteacher_texture);
    superteacher.move(0,720 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] )));

    user_input.HIEvent_sig.connect([&superteacher](HIEvent event)->void{
        switch(event) {
            case HIEvent::GO_LEFT:
                superteacher.move(-10,0);
                break;
            case HIEvent::GO_RIGHT:
                superteacher.move(10,0);
				break;
			case HIEvent::GO_UP:
				superteacher.move(0, -10);
				break;
			case HIEvent::GO_DOWN:
				superteacher.move(0, 10);
				break;
            default:
                break;
            }
    });

    song->play();
    while(window.isOpen()){

        user_input.process();

        window.clear(sf::Color::White);

        // Dessin


        window.draw(bg_sprite);
        window.draw(ground_sprite);
        window.draw(ground_fill_sprite);
        window.draw(cloud_sprite);
        window.draw(cloud2_sprite);
        window.draw(text);
        window.draw(superteacher);



        window.display();
    }


    LOG(info) << "Good bye, end of main process";
    return 0;
}
