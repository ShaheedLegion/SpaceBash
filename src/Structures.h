#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL/SDL.h>

namespace spacebash_s
{
typedef Uint8 _uc;

typedef struct tagColor
{
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
    #else
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    #endif
} Color;

Uint32 GetCol(SDL_PixelFormat * pixel_fmt, _uc r, _uc g, _uc b)
{
    Uint32 col = SDL_MapRGB(pixel_fmt, r, g, b);
    return col;
}
Uint32 GetCol_A(SDL_PixelFormat * pixel_fmt, _uc r, _uc g, _uc b, _uc a)
{
    Uint32 col = SDL_MapRGBA(pixel_fmt, r, g, b, a);
    return col;
}
typedef struct tagPoint
{
    float x;
    float y;
    float z;
    int tx;
    int ty;
} Point;

typedef struct tagBufferPoint
{
    float z;
    Uint32 color;
} BufferPoint;

typedef struct tagCube
{
    Point vertices[8];
    Point dimensions[3];
    bool exploding;
    bool visible;
} Cube;
};

#endif // STRUCTURES_H_INCLUDED
