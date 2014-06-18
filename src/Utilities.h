#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <SDL/SDL.h>
#include "BufferObject.h"
#include <math.h>

namespace spacebash
{
Uint32 rmask = 0x000000ff;
Uint32 rshift = 0;
Uint32 gmask = 0x0000ff00;
Uint32 gshift = 8;
Uint32 bmask = 0x00ff0000;
Uint32 bshift = 16;
Uint32 amask = 0xff000000;
Uint32 ashift = 24;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    rshift = 24;
    gmask = 0x00ff0000;
    gshift = 16;
    bmask = 0x0000ff00;
    bshift = 8;
    amask = 0x000000ff;
    ashift = 0;
#endif

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
    void grad_line(BufferObject * surf, int x0, int y0, int x1, int y1)
    {
        int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
        int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;
        int len = sqrt( dx * dx + dy * dy );

        float delta_c = (float)(0 - 255) / (float)((len / 6) * 5);
        float c_c = (float)255;

        Uint32 ccol;
        for(;;)
        {
            #if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                ccol = (Uint32)((Uint32)(c_c) << rshift)| ((Uint32)(c_c) << gshift)| ((Uint32)(c_c) << bshift)| ((Uint32)(100) << ashift);
            #else
                ccol = (Uint32)((Uint32)(100) << ashift| (Uint32)(c_c) << bshift| (Uint32)(c_c) << gshift| (Uint32)(c_c) << rshift);
            #endif
            surf->Write(x0, y0, 0, ccol);

            if (x0 == x1 && y0 == y1) break;
            e2 = err;
            if (e2 >-dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }

            c_c += delta_c;

            if (c_c < 0)
                c_c = 0;
        }
    }

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
