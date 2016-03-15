#include "MainWindow.h"
#include <assert.h>

struct MainWindow {
   SDL_Window * window;
} MainWindow_t;

struct MainWindow mw = { NULL };

void MainWindow_Open(void) {

    SDL_Surface * surface = NULL;

    // Only one main window must be open
    assert(mw.window == NULL);


    mw.window = SDL_CreateWindow(
        "SuperTeacher",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    // Check for error
    if(mw.window == NULL){
        fprintf(stderr, "SDL Error: %s \n", SDL_GetError());
        abort();
    }

    surface = SDL_GetWindowSurface( mw.window );
    SDL_FillRect(
        surface,
        NULL,
        SDL_MapRGB(
            surface->format,
            0x33,
            0x33,
            0x33
        )
    );

    SDL_UpdateWindowSurface( mw.window );
}

void MainWindow_Close() {
   SDL_DestroyWindow( mw.window);
   mw.window = NULL;
}
