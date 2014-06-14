#include "Asteroid.h"
#include "Utilities.h"

Asteroid::Asteroid()
{
    particle_speed = 0.57f + (float)((float)rand() / (float)RAND_MAX) * 0.5f;
    npoints = 90;   //not too much or it will weigh down the cpu.
    vertices = new spacebash::Point[npoints];
    position.x = (float)(rand() % 80 - 40);
    position.y = (float)(rand() % 80 - 40);
    position.z = (float)(rand() % 70 + 20);

    for (int i = 0; i < npoints; i++)
		InitParticle(&vertices[i]);
}

Asteroid::~Asteroid()
{
    delete [] vertices;
}

void Asteroid::InitParticle(spacebash::Point * pt)
{
    pt->x = position.x + (float)((float)rand() / (float)RAND_MAX) * 0.5f;
    pt->y = position.y + (float)((float)rand() / (float)RAND_MAX) * 0.5f;
    pt->z = position.z + (float)((float)rand() / (float)RAND_MAX) * 7.0f;
}

void Asteroid::Render(Camera * cam, BufferObject * surf)
{
    spacebash::Point * p;
    int tx, ty;

    position.z -= particle_speed;
    if (position.z < 2.0f)
    {
        position.z += 80.0f;
        for (int i = 0; i < npoints; ++i)
            InitParticle(&vertices[i]);
    }

    p = &vertices[0];
    bool bRender;
    unsigned int col = 0;
    for (int i = 0; i < npoints; ++i)
    {
        bRender = true;
        p->z += particle_speed + (float)((float)rand() / (float)RAND_MAX) * 0.5f;
        if (p->z - position.z > 10.0f)
            InitParticle(p);

        cam->Transform(&p->tx, &p->ty, &p->x, &p->y, p->z);
        tx = p->tx;
        ty = p->ty;

        if (tx < 0) bRender = false;
        if (tx > cam->GetWidth()) bRender = false;
        if (ty < 0) bRender = false;
        if (ty > cam->GetHeight()) bRender = false;

        if (bRender)
        {
            float dist = (((p->z - position.z) + 0.5f) / 10.0f) * 235.0f;
            col = 0xff << 24 | 0xff << 16 | (int)(255 - (int)dist) << 8 | 0;
            surf->Write(tx, ty, p->z, (Uint32)col);
        }

        ++p;
    }
}
