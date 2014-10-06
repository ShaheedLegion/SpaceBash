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
#if defined(USE_SDL)
    AsteroidField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
#else
	AsteroidField(BufferObject* surf, Camera* cam, int bpp);
#endif
    ~AsteroidField();

    void Update();
};

#endif // ASTEROIDFIELD_H_INCLUDED
