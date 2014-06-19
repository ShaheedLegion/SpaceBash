#ifndef SPACEBASH_H_INCLUDED
#define SPACEBASH_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include "Camera.hpp"
#include "BufferObject.h"
#include "PlaneObject.h"
#include "Overlay.h"
#include <vector>

class SpaceBash
{
public:
    SDL_Surface * screen;
    SDL_Thread * updateThread;
    BufferObject * screen_buffer;
    BufferObject * lightingMask;
    Overlay * overlay;
    Camera * camera;
    std::vector<PlaneObject *> planes;
    bool bRunning;

public:
    SpaceBash();
    ~SpaceBash();
    bool IsRunning();
    void SetRunning(bool);
    void UpdateMouse(int mcx, int mcy);
    void SetDirection(int dir);
    void Fire(int mcx, int mcy);
};

#endif // SPACEBASH_H_INCLUDED
