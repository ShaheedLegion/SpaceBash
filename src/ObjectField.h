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
    spacebash::Cube * cubes;
    void PositionCube(spacebash::Cube * c, float x, float y, float z, float dim);
    void RotateVertex(spacebash::Point * v, spacebash::Point * c);

public:
    ObjectField(BufferObject * surf, Camera * cam);
    ~ObjectField();

    void Update();
};

#endif // OBJECTFIELD_H_INCLUDED
