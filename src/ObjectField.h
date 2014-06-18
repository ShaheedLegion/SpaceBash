#ifndef OBJECTFIELD_H_INCLUDED
#define OBJECTFIELD_H_INCLUDED

#include "Camera.hpp"
#include "PlaneObject.h"
#include "Structures.h"

class ObjectField : public PlaneObject
{
protected:
    int nCubes;
    int theta;
    float cSize;
    spacebash_s::Cube * cubes;
    void PositionCube(spacebash_s::Cube * c, float x, float y, float z, float dim);
    void RotateVertex(spacebash_s::Point * v, spacebash_s::Point * c);

public:
    ObjectField(BufferObject * surf, Camera * cam, SDL_PixelFormat * fmt);
    ~ObjectField();

    void Update();
};

#endif // OBJECTFIELD_H_INCLUDED
