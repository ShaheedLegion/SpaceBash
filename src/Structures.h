#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#if defined(USE_SDL)
#include <SDL/SDL.h>
#else
#define unsigned char Uint8
#define unsigned int Uint32
#endif

namespace spacebash_s
{
typedef unsigned char _uc;

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

#if defined(USE_SDL)
Uint32 GetCol(SDL_PixelFormat * pixel_fmt, _uc r, _uc g, _uc b)
{
    Uint32 col = SDL_MapRGB(pixel_fmt, r, g, b);
    return col;
}
#else
unsigned int GetCol(_uc r, _uc g, _uc b)
{
	unsigned int col = ((unsigned int)(((_uc)(r) | ((unsigned short)((_us)(g)) << 8)) | (((unsigned short)(_uc)(b)) << 16)));
	return col;
}
#endif
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
