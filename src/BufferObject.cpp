#include "BufferObject.h"

BufferObject::BufferObject(int width, int height) : w(width), h(height)
{
    screen_buffer = new spacebash_s::Color[w * h];
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
    for (int i = 0; i < len; ++i)
        depth_buffer[i] = -500.0f;
    memset(&screen_buffer[0], 0, len * sizeof(Uint32));
}

/*
Experimental, horrible, unoptimized blur function - just until I have
the time to write a stack blur algorithm in place of this mess.
*/
void BufferObject::Blur()
{

    int w = GetWidth();
    int h = GetHeight();
    spacebash_s::Color pc, pp, pn;
    spacebash_s::Color * ptc, *ptt, *ptb;
    for (int y = 1; y < h-1; ++y)
    {
        ptt = &screen_buffer[0 + ((y - 1) * w)];
        ptc = &screen_buffer[0 + ((y + 0) * w)];
        ptb = &screen_buffer[0 + ((y + 1) * w)];
        for (int x = 0; x < w; ++x)
        {
            pp = *(spacebash_s::Color*)(ptt);
            pc = *(spacebash_s::Color*)(ptc);
            pn = *(spacebash_s::Color*)(ptb);

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
            pp = *(spacebash_s::Color*)(--ptc);
            ++ptc;
            pn = *(spacebash_s::Color*)(++ptc);

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

    spacebash_s::Color * pt = &screen_buffer[x + (y * w)];
    float * cz = &depth_buffer[x + (y * w)];
    if (*cz > z) return;  //depth test

    *cz = z;
    *pt = *(spacebash_s::Color*)&(color);
}

int BufferObject::GetWidth()
{
    return w;
}
int BufferObject::GetHeight()
{
    return h;
}
spacebash_s::Color * BufferObject::GetBuffer()
{
    return &screen_buffer[0];
}
