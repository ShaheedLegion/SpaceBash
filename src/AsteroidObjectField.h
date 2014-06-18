#ifndef ASTEROIDOBJECTFIELD_H_INCLUDED
#define ASTEROIDOBJECTFIELD_H_INCLUDED
#include "Camera.hpp"
#include "PlaneObject.h"
#include "Asteroid.h"
#include "Structures.h"

class AsteroidObjectField : public PlaneObject
{
    protected:
    int nAsteroidObjects;
    Asteroid * asteroids;
    int theta;
    float cSize;
    spacebash_s::Cube * cubes;
    void PositionCube(spacebash_s::Cube * c, float x, float y, float z, float dim);
    void RotateVertex(spacebash_s::Point * v, spacebash_s::Point * c);

public:
    AsteroidObjectField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
    ~AsteroidObjectField();

    void Update();
};

#endif // ASTEROIDOBJECTFIELD_H_INCLUDED
