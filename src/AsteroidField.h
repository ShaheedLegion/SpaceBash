#ifndef ASTEROIDFIELD_H_INCLUDED
#define ASTEROIDFIELD_H_INCLUDED
#include "Camera.hpp"
#include "PlaneObject.h"
#include "Asteroid.h"

class AsteroidField : public PlaneObject
{
protected:
    int nAsteroids;
    Asteroid * asteroids;

public:
    AsteroidField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
    ~AsteroidField();

    void Update();
};

#endif // ASTEROIDFIELD_H_INCLUDED
