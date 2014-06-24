#ifndef OVERLAY_H_INCLUDED
#define OVERLAY_H_INCLUDED

#include "PlaneObject.h"
#include "Structures.h"

class Overlay : public PlaneObject
{
protected:
    int nOculusPoints;
    spacebash_s::Point * oculus;

    int nGyroPoints;
    spacebash_s::Point * gyro;

    int nFireCount;
    bool isFiring;

    void SetPoint(spacebash_s::Point * pt, float x, float y);

public:
    Overlay(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
    ~Overlay();

    void Update();
    void SetFiring(int mx, int my);
    bool IsFiring();
};

#endif // OVERLAY_H_INCLUDED
