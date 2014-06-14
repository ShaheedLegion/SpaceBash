#include "AsteroidField.h"

AsteroidField::AsteroidField(BufferObject * surf, Camera * cam) : PlaneObject(surf, cam)
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
