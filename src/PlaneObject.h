#ifndef PLANEOBJECT_H_INCLUDED
#define PLANEOBJECT_H_INCLUDED
#include "BufferObject.h"
#include "Camera.hpp"

class PlaneObject
{
protected:
    BufferObject * surface;
    Camera * camera;
    SDL_PixelFormat * pixel_fmt;
    int w;
    int h;
public:
    PlaneObject(BufferObject * obj, Camera * cam, SDL_PixelFormat * fmt);
    virtual ~PlaneObject();

    virtual void Update();
};

#endif // PLANEOBJECT_H_INCLUDED
