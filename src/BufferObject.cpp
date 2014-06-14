#include "BufferObject.h"

BufferObject::BufferObject(int width, int height) : w(width), h(height)
{
    screen_buffer = new spacebash::Color[w * h];
    depth_buffer = new float[w * h];
    Clear();
}
BufferObject::~BufferObject()
{
    delete [] screen_buffer;
    delete [] depth_buffer;
}

void BufferObject::Clear()
{
    int len = GetWidth() * GetHeight();
    memset(&depth_buffer[0], -500.0f, len * sizeof(float));
    memset(&screen_buffer[0], 0xff000000, len * sizeof(Uint32));
}

/*
Experimental, horrible, unoptimized blur function - just until I have
the time to write a stack blur algorithm in place of this mess.
*/
void BufferObject::Blur()
{

    int w = GetWidth();
    int h = GetHeight();
    spacebash::Color pc, pp, pn;
    spacebash::Color * ptc, *ptt, *ptb;
    for (int y = 1; y < h-1; ++y)
    {
        ptt = &screen_buffer[0 + ((y - 1) * w)];
        ptc = &screen_buffer[0 + ((y + 0) * w)];
        ptb = &screen_buffer[0 + ((y + 1) * w)];
        for (int x = 0; x < w; ++x)
        {
            pp = *(spacebash::Color*)(ptt);
            pc = *(spacebash::Color*)(ptc);
            pn = *(spacebash::Color*)(ptb);

            ptc->r = (char)(((int)pp.r + pn.r) >> 1);
            ptc->g = (char)(((int)pp.g + pn.g) >> 1);
            ptc->b = (char)(((int)pp.b + pn.b) >> 1);
            ptt++;
            ptc++;
            ptb++;
        }
    }
    for (int y = 0; y < h; ++y)
    {
        ptc = &screen_buffer[1 + (y * w)];
        for (int x = 0; x < w - 2; ++x)
        {
            pp = *(spacebash::Color*)(--ptc);
            ++ptc;
            pn = *(spacebash::Color*)(++ptc);

            ptc->r = (char)(((int)pp.r + pn.r) >> 1);
            ptc->g = (char)(((int)pp.g + pn.g) >> 1);
            ptc->b = (char)(((int)pp.b + pn.b) >> 1);
            ptc++;
        }
    }
}
//write to the screen buffer, and do some depth testing.
void BufferObject::Write(int x, int y, float z, Uint32 color)
{
    if (x < 0) return;
    if (y < 0) return;
    if (x > w) return;
    if (x == w) x = w - 1;
    if (y > h) return;
    if (y == h) y = h - 1;

    spacebash::Color * pt = &screen_buffer[x + (y * w)];
    float * cz = &depth_buffer[x + (y * w)];
    if (*cz > z) return;  //depth test

    *cz = z;
    *pt = *(spacebash::Color*)&(color);
}

int BufferObject::GetWidth()
{
    return w;
}
int BufferObject::GetHeight()
{
    return h;
}
spacebash::Color * BufferObject::GetBuffer()
{
    return &screen_buffer[0];
}
