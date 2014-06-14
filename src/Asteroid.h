#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <SDL/SDL.h>
#include "BufferObject.h"
#include "Structures.h"
#include "Camera.hpp"

class Asteroid
{
protected:
    spacebash::Point position;  //the location of this asteroid
    int npoints;
    spacebash::Point * vertices;
    float particle_speed;
public:
    Asteroid();
    ~Asteroid();
    void InitParticle(spacebash::Point * pt);
    void Render(Camera * cam, BufferObject * surf);
};

#endif // ASTEROID_H_INCLUDED
