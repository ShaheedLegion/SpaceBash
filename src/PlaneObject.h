#ifndef PLANEOBJECT_H_INCLUDED
#define PLANEOBJECT_H_INCLUDED
#include "BufferObject.h"
#include "Camera.hpp"

class PlaneObject
{
protected:
    BufferObject * surface;
    Camera * camera;
    int w;
    int h;
public:
    PlaneObject(BufferObject * obj, Camera * cam);
    virtual ~PlaneObject();

    virtual void Update();
};

#endif // PLANEOBJECT_H_INCLUDED
