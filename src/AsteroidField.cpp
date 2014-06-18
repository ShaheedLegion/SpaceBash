#include "AsteroidField.h"

AsteroidField::AsteroidField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt) : PlaneObject(surf, cam, fmt)
{
    nAsteroids = 50;    //reasonable number ... for now
    asteroids = new Asteroid[nAsteroids];
}
AsteroidField::~AsteroidField()
{
    delete [] asteroids;
}

void AsteroidField::Update()
{
    for (int i = 0; i < nAsteroids; ++i)
        asteroids[i].Render(camera, surface, pixel_fmt);
}
