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
#include "Ground.h"
#include "Physics.h"
#include "Character.h"
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
    
    //Object ground = {};
    Ground ground(resource, "level");
    Object people = {};
    Object front_print = {};
    Background background(resource, "level");
    int levelJump = 0;
    char flag = 0;
    
    
    auto level = resource->get_json("levels/level.json");
    auto font = resource->get_font(FONT_INDIE_FLOWER);
    auto song = resource->get_music(SONG_1);
    int ground_level = (*level)["ground"]["level"];
    
    std::shared_ptr<sf::Text> text = make_shared<sf::Text>("Hello SuperTeacher", *font, 50);
    text->move(25,25);

    std::shared_ptr<sf::Text> timetext = make_shared<sf::Text>("Clock: " + to_string(Timer::get_time_ms()), *font, 50);
    text->move(100,50);
    front_print.add_drawable(timetext);
    
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
    
    for (int y = 17;  y >= ground_level; y--) {
        for (int x = 0; x < 32; x++) {
            ColisionDetect[x][y] = SOLID;
        }
    }
    
    std::string gr_name = (*level)["ground"]["name"];

	
    auto character = Character(resource, "level");

    user_input.HIEvent_sig.connect([&character](HIEvent event)->void {
        character.process_event(event);
    });
    
    
    if((bool)(*config)["audio"]){
        song->play();
    }
    
    while(window.isOpen()){

       
        user_input.process();
        window.clear(sf::Color::White);

		high_jump->setString("Jump level " + to_string(levelJump));
        
        auto tmp_time = Timer::get_time_ms();
        timetext->setString("Clock: " + to_string(tmp_time));
        
      
        // Dessin
        
    
		for (auto n : background.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : ground.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : character.get_drawables())
		{
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
