#ifndef SPACEBASH_H_INCLUDED
#define SPACEBASH_H_INCLUDED

#if defined(USE_SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#else
#define Uint32 unsigned int
#include "SpaceBashSurface.h"
#include "SpaceBashThread.h"
#endif

#include "Camera.hpp"
#include "BufferObject.h"
#include "PlaneObject.h"
#include "Overlay.h"
#include "AsteroidObjectField.h"
#include <vector>

class SpaceBash
{
public:
#if defined(USE_SDL)
    SDL_Surface * screen;
    SDL_Thread * updateThread;
#else
	SpaceBash_Surface* screen;
	SpaceBash_Thread* updateThread;
#endif

    BufferObject * screen_buffer;
    BufferObject * lightingMask;
    Overlay * overlay;
    AsteroidObjectField * field;
    Camera * camera;
    std::vector<PlaneObject *> planes;
    bool bRunning;

    void CheckCollisions();

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
