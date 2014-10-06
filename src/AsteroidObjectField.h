#ifndef ASTEROIDOBJECTFIELD_H_INCLUDED
#define ASTEROIDOBJECTFIELD_H_INCLUDED
#include "Camera.hpp"
#include "PlaneObject.h"
#include "Asteroid.h"
#include "Structures.h"
#include <vector>

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
#if defined(USE_SDL)
    AsteroidObjectField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
#else
	AsteroidObjectField(BufferObject* surf, Camera* cam, int bpp);
#endif
    ~AsteroidObjectField();

    void Update();
    void GetVisibleObjects(std::vector<spacebash_s::Cube *> & objects);
};

#endif // ASTEROIDOBJECTFIELD_H_INCLUDED
