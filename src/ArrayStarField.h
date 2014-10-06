#ifndef ARRAYSTARFIELD_H_INCLUDED
#define ARRAYSTARFIELD_H_INCLUDED
#include "Camera.hpp"
#include "PlaneObject.h"

class ArrayStarField : public PlaneObject
{
protected:
    int nstars;
    float speed;
    float * _x;
    float * _y;
    float * _z;
    int * _tx;
    int * _ty;

public:
#if defined(USE_SDL)
    ArrayStarField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
#else
	ArrayStarField(BufferObject * surf, Camera * cam, int bpp);
#endif
    ~ArrayStarField();

    void Update();
};

#endif // ARRAYSTARFIELD_H_INCLUDED
