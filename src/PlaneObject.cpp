#include "PlaneObject.h"

PlaneObject::PlaneObject(BufferObject * obj, Camera * cam, SDL_PixelFormat * fmt) : surface(obj), camera(cam), pixel_fmt(fmt)
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

