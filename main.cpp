#include <SDL/SDL.h>
#include "src/SpaceBash.h"

int main( int argc, char * args[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );    //Start SDL
    SpaceBash spaceBash;
    SDL_Event e;

    int direction = 0;

    while ( SDL_WaitEvent(&e) )
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            break;
        if (e.type == SDL_MOUSEMOTION)
            spaceBash.UpdateMouse(e.motion.x, e.motion.y);
        if (e.type == SDL_MOUSEBUTTONDOWN)
            spaceBash.Fire(e.button.x, e.button.y);
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
            direction = 1;
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LEFT)
            direction = 0;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
            direction = -1;
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RIGHT)
            direction = 0;

        spaceBash.SetDirection(direction);
    }
    spaceBash.SetRunning(false);
    SDL_Quit();    //Quit SDL

    return 0;
}
