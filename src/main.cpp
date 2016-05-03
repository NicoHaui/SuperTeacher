#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Constants.h"
#include "Path.h"
#include "AbstractView.h"
#include "ResourceManager.h"
#include "HIManager.h"
#include "Logs.h"
#include "Object.h"

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
    
    std::array<std::array<int, 18>,32> ColisionDetect = {};
    const int SOLID = 1;
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

	Object ground = {};
	Object back_ground = {};
	Object people = {};
	Object front_print = {};

    auto level = resource.get_json("levels/level.json");
    auto font = resource.get_font(FONT_INDIE_FLOWER);
    auto song = resource.get_music(SONG_1);
    int ground_level = (*level)["ground"]["level"];

    std::shared_ptr<sf::Text> text = make_shared<sf::Text>("Hello SuperTeacher", *font, 50);
    text->move(25,25);
    const json bg_map = (*level)["background"];
    const std::string bg = (*level)["background"]["fill"];
    auto bg_texture = resource.get_texture("graphics/backgrounds/" + bg + ".png");
    bg_texture->setRepeated(true);
	front_print.add_drawable(text);
    auto bg_sprite = make_shared<sf::Sprite>();
    bg_sprite->setTexture(*bg_texture);
    bg_sprite->setTextureRect(sf::IntRect(0,0,1920,1080));

    auto cloud_texture = resource.get_texture("graphics/tests/Items/cloud3.png");
    auto cloud_sprite = make_shared<sf::Sprite>();
    cloud_sprite->setTexture(*cloud_texture);
    cloud_sprite->move(200,200);
    
    auto cactus_texture = resource.get_texture("graphics/tests/Items/cactus.png");
    auto cactus_sprite = make_shared<sf::Sprite>();
    cactus_sprite->setTexture(*cactus_texture);
    cactus_sprite->setScale(4,2);
    cactus_sprite->setTextureRect(sf::IntRect(0,0,BLOCK_PXSIZE * 3,BLOCK_PXSIZE * 3));

    cactus_sprite->move(500, (ground_level - 6) * BLOCK_PXSIZE);
	front_print.add_drawable(cactus_sprite);

    auto cloud2_sprite = make_shared<sf::Sprite>();
    cloud2_sprite->setTexture(*cloud_texture);
    cloud2_sprite->move(400,175);

	back_ground.add_drawable(bg_sprite);
	back_ground.add_drawable(cloud_sprite);
	back_ground.add_drawable(cloud2_sprite);

    for (int y = 17;  y >= ground_level; y--) {
        for (int x = 0; x < 32; x++) {
            ColisionDetect[x][y] = SOLID;
        }
    }
    
    std::string gr_name = (*level)["ground"]["name"];
    auto ground_texture = resource.get_texture("graphics/grounds/" + gr_name + "/top.png");
    ground_texture->setRepeated(true);
    auto ground_sprite = make_shared<sf::Sprite>();
    ground_sprite->setTexture(*ground_texture);
    ground_sprite->setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE, BLOCK_PXSIZE));
    ground_sprite->move(0,SCREEN_Y_PXSIZE - (BLOCK_PXSIZE * (SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] )));

	ground.add_drawable(ground_sprite);

    auto ground_fill_texture = resource.get_texture("graphics/grounds/" + gr_name + "/fill.png");
    ground_fill_texture->setRepeated(true);
    auto ground_fill_sprite = make_shared<sf::Sprite>();
    ground_fill_sprite->setTexture(*ground_fill_texture);
    ground_fill_sprite->setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE, BLOCK_PXSIZE*(SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] ) - 1));
    ground_fill_sprite->move(0,SCREEN_Y_PXSIZE - (BLOCK_PXSIZE * (SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] - 1 )));

	ground.add_drawable(ground_fill_sprite);
	

    auto superteacher_texture = resource.get_texture("graphics/characters/superteacher.png");

    auto superteacher = make_shared<sf::Sprite>();
    superteacher->setTexture(*superteacher_texture);
    const int MINLEVEL = 658 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] ));
    superteacher->move(0,MINLEVEL );

    people.add_drawable(superteacher);

    user_input.HIEvent_sig.connect([&superteacher, &MINLEVEL](HIEvent event)->void{
        float y = 0;
        switch(event) {
            case HIEvent::GO_LEFT:
                superteacher->move(-5,0);
                break;
            case HIEvent::GO_RIGHT:
                superteacher->move(5,0);
				break;
			case HIEvent::GO_UP:
				superteacher->move(0, -5);
				break;
			case HIEvent::GO_DOWN:
                y = superteacher->getPosition().y;
                if(y < MINLEVEL ){
                    superteacher->move(0, 5);
                }
				break;
            case HIEvent::JUMP:
                
                superteacher->move(10, -5);
            
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


		for (auto n : back_ground.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : ground.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : people.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : front_print.get_drawables())
		{
			window.draw(*n);
		}

        window.display();
    }


    LOG(info) << "Good bye, end of main process";
    return 0;
}
