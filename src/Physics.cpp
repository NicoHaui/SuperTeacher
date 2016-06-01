//
// Created by samuel on 01.04.16.
//

#include "Physics.h"

#include <cmath>
#include <ctime>

time_t clock_at_startup = std::clock();

    
time_ms Timer::get_time_ms(){
    
    auto clocktime = std::clock() - clock_at_startup;
    return ((clocktime*1000)/CLOCKS_PER_SEC);
}


time_s Timer::get_time_s(){

    return (clock() / CLOCKS_PER_SEC);
}



void jump_manager( std::shared_ptr<sf::Sprite> sprite, float GroundLevel,int vitesseInit,bool ColisionFlag)
{
    static std::clock_t time_jump[3];
	static int vitesse0 = 0;
	static float posy_m_un = 0;
	float posy = 0;

	if (sprite->getPosition().y >= GroundLevel || ColisionFlag)
	{
        time_jump[0] = std::clock();
		vitesse0 = vitesseInit;
		posy_m_un = 0;
	}

    time_jump[1] = std::clock();
    posy = (
            (float)(time_jump[1] - time_jump[0]+1)/CLOCKS_PER_SEC
           ) * vitesse0 * METER
        + (
           std::pow((float)(time_jump[1] - time_jump[0])/CLOCKS_PER_SEC, 2)*GRAVITY
        ) * METER / 2.0;
    
    
	if ((posy- posy_m_un)+ sprite->getPosition().y >= GroundLevel)
		posy = GroundLevel-(sprite->getPosition().y-posy_m_un);
	sprite->move(0, (posy - posy_m_un));
	posy_m_un = posy;

}


