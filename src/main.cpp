#include <iostream>
#include <memory>
#include <time.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <clock.hpp>

#include "Constants.h"
#include "Path.h"
#include "AbstractView.h"
#include "ResourceManager.h"
#include "HIManager.h"
#include "Logs.h"
#include "Object.h"
#include "Background.h"
#include "Physics.h"

using namespace std;


int main(int argc, char *argv[]) {

    log_init();

    LOG(info)  << "Superteacher is starting";
    LOG(debug) << "SRC Directory: " << _SRC_DIR;
    LOG(debug) << "Install Prefix: " << _INSTALL_PREFIX;

    LOG(info) << "Opening window";
    LOG(debug) << "Window size: " << SCREEN_X_PXSIZE << "x" << SCREEN_Y_PXSIZE;


    auto resource = make_shared<ResourceManager>();
    auto config = resource->get_json("conf.json");
    auto style = sf::Style::Default;
    
    Object ground = {};
    Object people = {};
    Object front_print = {};
    Background background(resource, "level");
    int levelJump = 0;
    int counter1 = 0;
    char flag = 0;
    sf::Vector2i source(0,0);
    
    auto level = resource->get_json("levels/level.json");
    auto font = resource->get_font(FONT_INDIE_FLOWER);
    auto song = resource->get_music(SONG_1);
    int ground_level = (*level)["ground"]["level"];
    
    std::shared_ptr<sf::Text> text = make_shared<sf::Text>("Hello SuperTeacher", *font, 50);
    text->move(25,25);
    
    const json bg_map = (*level)["background"];

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
    
	std::shared_ptr<sf::Text> high_jump = make_shared<sf::Text>("Jump level " + to_string(levelJump), *font, 50);
	high_jump->move(900, 25);
	front_print.add_drawable(text);
	front_print.add_drawable(high_jump);

    auto window_texture = resource->get_texture("graphics/backgrounds/window.png");
    auto window_sprite = make_shared<sf::Sprite>();
    window_sprite->setTexture(*window_texture);
    window_sprite->setScale(0.6,0.6);
    window_sprite->setTextureRect(sf::IntRect(0,0,BLOCK_PXSIZE * 9,BLOCK_PXSIZE * 14));
    window_sprite->move(300, (ground_level - 12) * BLOCK_PXSIZE);
//    auto window2_sprite = make_shared<sf::Sprite>();
//    window2_sprite->setTexture(*window_texture);
//    window2_sprite->setScale(0.6,0.6);
//    window2_sprite->move(1300,(ground_level - 12) * BLOCK_PXSIZE);
    
	background.add_drawable(window_sprite);
//    background.add_drawable(window2_sprite);
    
    for (int y = 17;  y >= ground_level; y--) {
        for (int x = 0; x < 32; x++) {
            ColisionDetect[x][y] = SOLID;
        }
    }
    
    std::string gr_name = (*level)["ground"]["name"];


    auto ground_fill_texture = resource->get_texture("graphics/grounds/" + gr_name + ".png");
    ground_fill_texture->setRepeated(true);
    auto ground_fill_sprite = make_shared<sf::Sprite>();
    ground_fill_sprite->setTexture(*ground_fill_texture);
    ground_fill_sprite->setTextureRect(sf::IntRect(0, 0, SCREEN_X_PXSIZE, BLOCK_PXSIZE*(SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] ) - 1));
    ground_fill_sprite->move(0,SCREEN_Y_PXSIZE - (BLOCK_PXSIZE * (SCREEN_Y_BLOCKS - (int)(*level)["ground"]["level"] - 1 )));

	ground.add_drawable(ground_fill_sprite);
	

    auto superteacher_texture = resource->get_texture("graphics/characters/superteacher.png");
    auto superteacher = make_shared<sf::Sprite>();
    superteacher->setTexture(*superteacher_texture);
    const int MINLEVEL = 658 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] ));
    superteacher->move(0,MINLEVEL );
   
    auto animation_texture = resource->get_texture("graphics/characters/spritefile.png");
    auto animation = make_shared<sf::Sprite>();
    animation->setTexture(*animation_texture);
    animation_texture->setSmooth(true);
    animation->move(10,MINLEVEL);
    animation->setScale(0.4, 0.4);
    
    animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1500));

    user_input.HIEvent_sig.connect([&superteacher, &MINLEVEL,&levelJump,&superteacher_texture,&resource,&source,&animation,&counter1,&people,&window_sprite,&flag,&animation_texture](HIEvent event)->void{
        switch(event) {
            case HIEvent::GO_LEFT:
				animation->move(-5,0);
                window_sprite->move(3, 0);
                superteacher->move(-5, 0);
                break;
            case HIEvent::GO_RIGHT:
                    animation->move(5,0);
                    window_sprite->move(-3, 0);
                    animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1500));
					superteacher->move(5,0);
                    counter1++;
                    if(counter1 >= 5)
                    {
                        source.x++;
                        counter1 = 0;
                    }
                    if(source.x >= 8)
                    {
                        source.x = 0;
                    }
				break;
			case HIEvent::GO_UP:
				levelJump++;
            source.x=2;
				break;
			case HIEvent::GO_DOWN:
				levelJump--;
				break;
            case HIEvent::JUMP:
				jump_manager(superteacher, MINLEVEL, -levelJump);
                superteacher_texture = resource->get_texture("graphics/characters/superteachersaut.png");
                superteacher->setTexture(*superteacher_texture);
                superteacher->setScale(1.2,1.2);
                people.add_drawable(superteacher);
                break;
            case HIEvent::THROW:
                
                break;
			case HIEvent::DEFAULT:
				break;
            default:
                break;
            
            
        }
    });
    
    people.add_drawable(animation);
    
    
    if((bool)(*config)["audio"]){
        song->play();
    }
    
    while(window.isOpen()){

       
        user_input.process();
        window.clear(sf::Color::White);
		jump_manager(superteacher, MINLEVEL,0);

        if (superteacher->getPosition().y >= MINLEVEL)
        {
            superteacher_texture = resource->get_texture("graphics/characters/transparent.png");
            superteacher->setTexture(*superteacher_texture);
            superteacher->setScale(1,1);
        }
		high_jump->setString("Jump level " + to_string(levelJump));
      
        // Dessin
        
    
		for (auto n : background.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : ground.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : people.get_drawables())
		{
            //window.clear();
			window.draw(*n);
		}
		for (auto n : front_print.get_drawables())
		{
			window.draw(*n);
		}
        window.display();
        window.clear();
    }

    LOG(info) << "Good bye, end of main process";
    return 0;
}
