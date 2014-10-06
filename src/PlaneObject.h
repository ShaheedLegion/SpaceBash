#ifndef PLANEOBJECT_H_INCLUDED
#define PLANEOBJECT_H_INCLUDED
#include "BufferObject.h"
#include "Camera.hpp"

class PlaneObject
{
protected:
    BufferObject * surface;
    Camera * camera;
#if defined(USE_SDL)
    SDL_PixelFormat * pixel_fmt;
#else
	int m_bpp;
#endif
    int w;
    int h;
public:
#if defined(USE_SDL)
    PlaneObject(BufferObject * obj, Camera * cam, SDL_PixelFormat * fmt);
#else
	PlaneObject(BufferObject* obj, Camera* cam, int bpp);
#endif
    virtual ~PlaneObject();

    virtual void Update();
};

#endif // PLANEOBJECT_H_INCLUDED
