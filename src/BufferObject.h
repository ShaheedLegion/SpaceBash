#ifndef BUFFEROBJECT_H_INCLUDED
#define BUFFEROBJECT_H_INCLUDED
#include "Structures.h"
/*
Screen buffer object, with some rudimentary depth sorting
*/
class BufferObject
{
protected:
    int w;
    int h;
    spacebash::Color * screen_buffer;
    float * depth_buffer;

public:
    BufferObject(int width, int height);
    ~BufferObject();

    void Clear();
    void Blur();
    //write to the screen buffer, and do some depth testing.
    void Write(int x, int y, float z, Uint32 color);
    int GetWidth();
    int GetHeight();
    spacebash::Color * GetBuffer();
};

#endif // BUFFEROBJECT_H_INCLUDED
