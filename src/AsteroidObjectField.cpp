#include "AsteroidObjectField.h"

#if defined(USE_SDL)
AsteroidObjectField::AsteroidObjectField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt) :
    PlaneObject(surf, cam, fmt), nAsteroidObjects(cam->GetHeight() / 2), theta(20)
#else
AsteroidObjectField::AsteroidObjectField(BufferObject * surf, Camera * cam, int bpp) :
    PlaneObject(surf, cam, bpp), nAsteroidObjects(cam->GetHeight() / 2), theta(20)
#endif
{
    cSize = 0.35f;  //actually half the size, but who's counting?
    cubes = new spacebash_s::Cube[nAsteroidObjects];
    asteroids = new Asteroid[nAsteroidObjects];

    for (int i = 0; i < nAsteroidObjects; ++i)
    {
        PositionCube(&cubes[i], asteroids[i].position.x, asteroids[i].position.y, asteroids[i].position.z, cSize);
        cubes[i].exploding = false;
    }
}

AsteroidObjectField::~AsteroidObjectField()
{
    delete [] asteroids;
    delete [] cubes;
}

void AsteroidObjectField::PositionCube(spacebash_s::Cube * c, float cx, float cy, float cz, float dim)
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

    c->dimensions[0].x = cx;
    c->dimensions[0].y = cy;
    c->dimensions[0].z = cz;

    c->dimensions[1].x = cx - dim;
    c->dimensions[1].y = cy;
    c->dimensions[1].z = cz;

    c->dimensions[2].x = cx + dim;
    c->dimensions[2].y = cy;
    c->dimensions[2].z = cz;
}

void AsteroidObjectField::RotateVertex(spacebash_s::Point * v, spacebash_s::Point * c)
{
    camera->RotateArbX(v->x, &v->y, &v->z, c->y, c->z, theta);
    camera->RotateArbY(&v->x, v->y, &v->z, c->x, c->z, theta / 4);
    camera->RotateArbZ(&v->x, &v->y, v->z, c->x, c->y, theta / 2);
}

void AsteroidObjectField::Update()
{
#if defined(USE_SDL)
    Uint32 color = spacebash_s::GetCol(pixel_fmt, 0, 255, 0);
#else
	Uint32 color = spacebash_s::GetCol(0, 255, 0);
#endif
    spacebash_s::Cube * c;

    for (int i = 0; i < nAsteroidObjects; ++i)
    {
        theta += 4;
        if (theta > 360)
            theta = 0;
#if defined(USE_SDL)
        asteroids[i].Render(camera, surface, pixel_fmt);
#else
		asteroids[i].Render(camera, surface);
#endif
        c = &cubes[i];
        c->visible = false;
        PositionCube(c, asteroids[i].position.x, asteroids[i].position.y, asteroids[i].position.z, cSize);

        RotateVertex(&c->vertices[0], &c->dimensions[0]);
        RotateVertex(&c->vertices[1], &c->dimensions[0]);
        RotateVertex(&c->vertices[2], &c->dimensions[0]);
        RotateVertex(&c->vertices[3], &c->dimensions[0]);
        RotateVertex(&c->vertices[4], &c->dimensions[0]);
        RotateVertex(&c->vertices[5], &c->dimensions[0]);
        RotateVertex(&c->vertices[6], &c->dimensions[0]);
        RotateVertex(&c->vertices[7], &c->dimensions[0]);

        for (int j = 0; j < 8; ++j)
            camera->Transform(&c->vertices[j].tx, &c->vertices[j].ty, &c->vertices[j].x, &c->vertices[j].y, c->vertices[j].z);

        camera->Transform(&c->dimensions[0].tx, &c->dimensions[0].ty, &c->dimensions[0].x, &c->dimensions[0].y, c->dimensions[0].z);
        camera->Transform(&c->dimensions[1].tx, &c->dimensions[1].ty, &c->dimensions[1].x, &c->dimensions[1].y, c->dimensions[1].z);
        camera->Transform(&c->dimensions[2].tx, &c->dimensions[2].ty, &c->dimensions[2].x, &c->dimensions[2].y, c->dimensions[2].z);

        if (c->vertices[0].tx < 0 || c->vertices[0].tx > camera->GetWidth())
            continue;
        if (c->vertices[0].ty < 0 || c->vertices[0].ty > camera->GetHeight())
            continue;
        if (c->vertices[2].tx < 0 || c->vertices[2].tx > camera->GetWidth())
            continue;
        if (c->vertices[2].ty < 0 || c->vertices[2].ty > camera->GetHeight())
            continue;

        c->visible = true;

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

void AsteroidObjectField::GetVisibleObjects(std::vector<spacebash_s::Cube *> & objects)
{
    for (int i = 0; i < nAsteroidObjects; ++i)
    {
        if (cubes[i].visible)
            objects.push_back((&cubes[i]));
    }
}
