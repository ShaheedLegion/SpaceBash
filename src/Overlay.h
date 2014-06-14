#ifndef OVERLAY_H_INCLUDED
#define OVERLAY_H_INCLUDED

#include "PlaneObject.h"
#include "Structures.h"

class Overlay : public PlaneObject
{
protected:
    int nOculusPoints;
    spacebash::Point * oculus;

    int nGyroPoints;
    spacebash::Point * gyro;

    void SetPoint(spacebash::Point * pt, float x, float y);

public:
    Overlay(BufferObject * surf, Camera * cam);
    ~Overlay();

    void Update();
};

#endif // OVERLAY_H_INCLUDED
