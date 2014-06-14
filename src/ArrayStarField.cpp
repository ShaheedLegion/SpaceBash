#include <SDL/SDL.h>
#include <stdlib.h>
#include "ArrayStarField.h"

ArrayStarField::ArrayStarField(BufferObject * surf, Camera * cam) : PlaneObject(surf, cam)
{
    nstars = cam->GetHeight() * 6;
    _x = new float[nstars];
    _y = new float[nstars];
    _z = new float[nstars];
    _tx = new int[nstars];
    _ty = new int[nstars];

    float * x = _x, * y = _y, *z = _z;
    for (int i = 0; i < nstars; ++i)
    {
		*x = (float)(rand() % 70 - 35);
		*y = (float)(rand() % 70 - 35);
		*z = (float)(rand() % 100 + 1);
		++x;
		++y;
		++z;
    }
    speed = 2.0f;
}

ArrayStarField::~ArrayStarField()
{
    delete [] _x;
    delete [] _y;
    delete [] _z;
    delete [] _tx;
    delete [] _ty;
}

void ArrayStarField::Update()
{
    bool bPushBack = false;

    float * x = _x, * y = _y, *z = _z;
    int * tx = _tx, * ty = _ty;
    float ttx, tty, ttz;
    int tttx, ttty;
    for (int i = 0; i < nstars; ++i)
    {
        ttx = *x;
        tty = *y;
        ttz = *z;
        ttz -= speed;
        bPushBack = false;

        camera->Transform(tx, ty, x, y, ttz);
        tttx = *tx;
        ttty = *ty;

        if (*z < 4)
            bPushBack = true;
        if (tttx < 0 || tttx > camera->GetWidth())
            bPushBack = true;
        if (ttty < 0 || ttty > camera->GetHeight())
            bPushBack = true;

		if (bPushBack)
        {
            ttz += 100.0f;
            *x = (float)(rand() % 70 - 35);
            *y = (float)(rand() % 70 - 35);
            ++x;
            ++y;
            ++z;
            ++tx;
            ++ty;
            continue;
        }

        surface->Write(tttx, ttty, ttz, 0x66996699);
        *x = ttx;
        *y = tty;
        *z = ttz;
        *tx = tttx;
        *ty = ttty;
        ++x;
		++y;
		++z;
		++tx;
		++ty;
    }
}
