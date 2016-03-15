#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    bool quit = false;
    SDL_Event e;

    fprintf(stdout, "SuperTeaching is starting..\n"); 

    if(SDL_Init(SDL_INIT_VIDEO)) {
        goto on_error;
    }

    MainWindow_Open();
    fprintf(stdout, "Window is opened\n");

    while( !quit )
    {
        while( SDL_PollEvent(&e) != 0 )
        {
           switch( e.type ){

               case SDL_QUIT:
                   quit = true;
                   break;
               case SDL_KEYDOWN:
                   switch( e.key.keysym.sym ){
                       case SDLK_UP:
                           printf("UP\n");
                           break;
                       case SDLK_DOWN:
                           printf("DOWN\n");
                           break;
                        case SDLK_LEFT:
                           printf("<-LEFT\n");
                           break;
                        case SDLK_RIGHT:
                            printf("RIGHT->\n");
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

    fprintf(stdout, "Window is closing\n");
    MainWindow_Close();
    SDL_Quit();
    return 0;

on_error:
    fprintf(stderr, "SDL Error: %s \n", SDL_GetError);
    SDL_Quit();
    return -1;
}
