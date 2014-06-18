#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <SDL/SDL.h>
#include "BufferObject.h"
#include "Structures.h"
#include "Camera.hpp"

class Asteroid
{
public:
    spacebash_s::Point position;  //the location of this asteroid
protected:
    int npoints;
    spacebash_s::Point * vertices;
    float particle_speed;
public:
    Asteroid();
    ~Asteroid();
    void InitParticle(spacebash_s::Point * pt);
    void Render(Camera * cam, BufferObject * surf, SDL_PixelFormat * fmt);
};

#endif // ASTEROID_H_INCLUDED
