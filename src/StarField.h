#ifndef STARFIELD_H_INCLUDED
#define STARFIELD_H_INCLUDED
#include "Camera.hpp"
#include "PlaneObject.h"
#include "Structures.h"

class StarField : public PlaneObject
{
protected:
    int nstars;
    float speed;
    spacebash_s::Point * stars;

public:
#if defined(USE_SDL)
	StarField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
#else
	StarField(BufferObject * surf, Camera * cam, int bpp);
#endif
	
    ~StarField();

    void Update();
};

#endif // STARFIELD_H_INCLUDED
