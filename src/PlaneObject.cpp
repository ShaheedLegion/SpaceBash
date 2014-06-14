#include "PlaneObject.h"

PlaneObject::PlaneObject(BufferObject * obj, Camera * cam) : surface(obj), camera(cam)
{
    w = surface->GetWidth();
    h = surface->GetHeight();
}
PlaneObject::~PlaneObject()
{

}

void PlaneObject::Update()
{

}

