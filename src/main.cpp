#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[]) {
    fprintf(stdout, "SuperTeaching is starting..\n");

    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL init Error: %s \n", SDL_GetError);
        return -1;
    }
    SDL_Quit();
    return 0;
}
