#include <stdlib.h>
#include "ObjectField.h"

#if defined(USE_SDL)
ObjectField::ObjectField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt) : PlaneObject(surf, cam, fmt), nCubes(cam->GetHeight()), theta(10)
#else
ObjectField::ObjectField(BufferObject * surf, Camera * cam, int bpp) : PlaneObject(surf, cam, bpp), nCubes(cam->GetHeight()), theta(10)
#endif
{
    cSize = 0.5f;  //actually half the size, but who's counting?
    float x, y, z;
    cubes = new spacebash_s::Cube[nCubes];
    for (int i = 0; i < nCubes; ++i)
    {
        x = (float)(rand() % 100 - 50);
		y = (float)(rand() % 100 - 50);
		z = (float)(rand() % 100 + 1);
        PositionCube(&cubes[i], x, y, z, cSize);
    }

}

ObjectField::~ObjectField()
{
    delete [] cubes;
}

void ObjectField::PositionCube(spacebash_s::Cube * c, float cx, float cy, float cz, float dim)
{
    c->vertices[0].x = cx - dim;
    c->vertices[0].y = cy - dim;
    c->vertices[0].z = cz - dim;

    c->vertices[1].x = cx + dim;
    c->vertices[1].y = cy - dim;
    c->vertices[1].z = cz - dim;

    c->vertices[2].x = cx + dim;
    c->vertices[2].y = cy + dim;
    c->vertices[2].z = cz - dim;

    c->vertices[3].x = cx - dim;
    c->vertices[3].y = cy + dim;
    c->vertices[3].z = cz - dim;

    c->vertices[4].x = cx - dim;
    c->vertices[4].y = cy - dim;
    c->vertices[4].z = cz + dim;

    c->vertices[5].x = cx + dim;
    c->vertices[5].y = cy - dim;
    c->vertices[5].z = cz + dim;

    c->vertices[6].x = cx + dim;
    c->vertices[6].y = cy + dim;
    c->vertices[6].z = cz + dim;

    c->vertices[7].x = cx - dim;
    c->vertices[7].y = cy + dim;
    c->vertices[7].z = cz + dim;

    c->vertices[8].x = cx;
    c->vertices[8].y = cy;
    c->vertices[8].z = cz;
}

void ObjectField::RotateVertex(spacebash_s::Point * v, spacebash_s::Point * c)
{
    camera->RotateArbX(v->x, &v->y, &v->z, c->y, c->z, theta);
    camera->RotateArbY(&v->x, v->y, &v->z, c->x, c->z, theta / 4);
    camera->RotateArbZ(&v->x, &v->y, v->z, c->x, c->y, theta / 2);
}

void ObjectField::Update()
{
#if defined(USE_SDL)
    Uint32 color = spacebash_s::GetCol(pixel_fmt, 0, 255, 0);
#else
	Uint32 color = spacebash_s::GetCol(0, 255, 0);
#endif
    spacebash_s::Cube * c;
    //++theta;

    for (int i = 0; i < nCubes; ++i)
    {
        c = &cubes[i];
        RotateVertex(&c->vertices[0], &c->vertices[8]);
        RotateVertex(&c->vertices[1], &c->vertices[8]);
        RotateVertex(&c->vertices[2], &c->vertices[8]);
        RotateVertex(&c->vertices[3], &c->vertices[8]);
        RotateVertex(&c->vertices[4], &c->vertices[8]);
        RotateVertex(&c->vertices[5], &c->vertices[8]);
        RotateVertex(&c->vertices[6], &c->vertices[8]);
        RotateVertex(&c->vertices[7], &c->vertices[8]);

        for (int j = 0; j < 9; ++j)
            camera->Transform(&c->vertices[j].tx, &c->vertices[j].ty, &c->vertices[j].x, &c->vertices[j].y, c->vertices[j].z);

        if (c->vertices[0].tx < 0 || c->vertices[0].tx > camera->GetWidth())
            continue;
        if (c->vertices[0].ty < 0 || c->vertices[0].ty > camera->GetHeight())
            continue;
        if (c->vertices[2].tx < 0 || c->vertices[2].tx > camera->GetWidth())
            continue;
        if (c->vertices[2].ty < 0 || c->vertices[2].ty > camera->GetHeight())
            continue;
        spacebash::line(surface, color, c->vertices[0].tx, c->vertices[0].ty, c->vertices[0].z, c->vertices[1].tx, c->vertices[1].ty, c->vertices[1].z);
        spacebash::line(surface, color, c->vertices[1].tx, c->vertices[1].ty, c->vertices[1].z, c->vertices[2].tx, c->vertices[2].ty, c->vertices[2].z);
        spacebash::line(surface, color, c->vertices[2].tx, c->vertices[2].ty, c->vertices[2].z, c->vertices[3].tx, c->vertices[3].ty, c->vertices[3].z);
        spacebash::line(surface, color, c->vertices[3].tx, c->vertices[3].ty, c->vertices[3].z, c->vertices[0].tx, c->vertices[0].ty, c->vertices[0].z);
        spacebash::line(surface, color, c->vertices[4].tx, c->vertices[4].ty, c->vertices[4].z, c->vertices[5].tx, c->vertices[5].ty, c->vertices[5].z);
        spacebash::line(surface, color, c->vertices[5].tx, c->vertices[5].ty, c->vertices[5].z, c->vertices[6].tx, c->vertices[6].ty, c->vertices[6].z);
        spacebash::line(surface, color, c->vertices[6].tx, c->vertices[6].ty, c->vertices[6].z, c->vertices[7].tx, c->vertices[7].ty, c->vertices[7].z);
        spacebash::line(surface, color, c->vertices[7].tx, c->vertices[7].ty, c->vertices[7].z, c->vertices[4].tx, c->vertices[4].ty, c->vertices[4].z);
        spacebash::line(surface, color, c->vertices[0].tx, c->vertices[0].ty, c->vertices[0].z, c->vertices[4].tx, c->vertices[4].ty, c->vertices[4].z);
        spacebash::line(surface, color, c->vertices[1].tx, c->vertices[1].ty, c->vertices[1].z, c->vertices[5].tx, c->vertices[5].ty, c->vertices[5].z);
        spacebash::line(surface, color, c->vertices[2].tx, c->vertices[2].ty, c->vertices[2].z, c->vertices[6].tx, c->vertices[6].ty, c->vertices[6].z);
        spacebash::line(surface, color, c->vertices[3].tx, c->vertices[3].ty, c->vertices[3].z, c->vertices[7].tx, c->vertices[7].ty, c->vertices[7].z);
        ++c;
    }
}


