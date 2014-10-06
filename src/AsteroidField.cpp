#include "AsteroidField.h"

#if defined(USE_SDL)
AsteroidField::AsteroidField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt) : PlaneObject(surf, cam, fmt)
#else
AsteroidField::AsteroidField(BufferObject * surf, Camera * cam, int bpp) : PlaneObject(surf, cam, bpp)
#endif
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
        asteroids[i].Render(camera, surface);
}
