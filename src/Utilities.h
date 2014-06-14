#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <SDL/SDL.h>
#include "BufferObject.h"
#include <math.h>

namespace spacebash
{
    static float * sin_table;
    static float * cos_table;

    void line(BufferObject * surface, Uint32 color, int x0, int y0, float z0, int x1, int y1, float z1)
    {
        int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
        int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;
        float zdist = (z1 - z0);    //cannot use absolute value here, since sz depends on the sign of this calculation
        int len = sqrt( dx * dx + dy * dy );
        float sz = zdist / (float)len;

        for(;;)
        {
            surface->Write(x0, y0, z0, color);

            if (x0 == x1 && y0 == y1) break;
            e2 = err;
            if (e2 >-dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
            z0 += sz;
        }
    }
    /*
    void line(BufferObject * surface, Uint32 color, float x0, float y0, float z0, float x1, float y1, float z1)
    {
        line(surface, color, (int)x0, (int)y0, z0, (int)x1, (int)y1, z1);
    }
    */
    void InitTables()
    {
        int len = 361;
        sin_table = new float[len];
        cos_table = new float[len];

        float c_radian = 0.0f;

        for (int i = 0; i < len; ++i)
        {
            sin_table[i] = sin(c_radian);
            cos_table[i] = cos(c_radian);
            c_radian += 0.0174532925f;
        }
    }
    void DestroyTables()
    {
        delete [] sin_table;
        delete [] cos_table;
    }
};

#endif // UTILITIES_H_INCLUDED
