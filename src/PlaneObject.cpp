#include "PlaneObject.h"

#if defined(USE_SDL)
PlaneObject::PlaneObject(BufferObject * obj, Camera * cam, SDL_PixelFormat * fmt) : surface(obj), camera(cam), pixel_fmt(fmt)
#else
PlaneObject::PlaneObject(BufferObject * obj, Camera * cam, int bpp) : surface(obj), camera(cam), m_bpp(bpp)
#endif
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

