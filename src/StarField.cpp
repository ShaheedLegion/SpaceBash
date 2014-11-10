#if defined(USE_SDL)
#include <SDL/SDL.h>
#endif
#include <stdlib.h>
#include "StarField.h"

#if defined(USE_SDL)
StarField::StarField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt) : PlaneObject(surf, cam, fmt)
#else
StarField::StarField(BufferObject * surf, Camera * cam, int bpp) : PlaneObject(surf, cam, bpp)
#endif
{
    nstars = cam->GetHeight() * 6;
    stars = new spacebash_s::Point[nstars]; //should be less, but this is fine for testing

    for (int i = 0; i < nstars; ++i)
    {
		stars[i].x = (float)(rand() % 100 - 50);
		stars[i].y = (float)(rand() % 100 - 50);
		stars[i].z = (float)(rand() % 100 + 1);
    }
    speed = 2.0f;
}

StarField::~StarField()
{
    delete [] stars;
}

void StarField::Update()
{
    int tempx;
    int tempy;
    bool bPushBack = false;
    bool bSkip = false;

    spacebash_s::Point * star;
#if defined(USE_SDL)
    Uint32 col = spacebash_s::GetCol(pixel_fmt, 99, 99, 99);
#else
	Uint32 col = spacebash_s::GetCol(99, 99, 99);
#endif
	int w(camera->GetWidth());
	int h(camera->GetHeight());
    for (int i = 0; i < nstars; ++i)
    {
        star = &stars[i];
        star->z -= speed;
        bPushBack = false;
        bSkip = false;

        camera->Transform(&star->tx, &star->ty, &star->x, &star->y, star->z);
        tempx = star->tx;
        tempy = star->ty;

        if (star->z < 4)
            bPushBack = true;
        if (tempx < 0 || tempx > w)
            bSkip = true;
        if (tempy < 0 || tempy > h)
            bSkip = true;

		if (bPushBack)
        {
            star->z += 100.0f;
            continue;
        }
        if (bSkip) continue;

        surface->Write(tempx, tempy, star->z, col);
    }
}
