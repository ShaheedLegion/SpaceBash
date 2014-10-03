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
#if defined(USE_SDL)
typedef Uint8 _uc;
#else
#define unsigned char _uc
#endif

#if defined(USE_SDL)
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
#else
	typedef struct tagColor{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} Color;
#endif

#if defined(USE_SDL)
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
#else
unsigned int GetCol(_uc r, _uc g, _uc b)
{
	unsigned int col = ((unsigned int)(((_uc)(r) | ((unsigned short)((_uc)(g)) << 8)) | (((unsigned short)(_uc)(b)) << 16)));
	return col;
}
unsigned int GetCol_A(_uc r, _uc g, _uc b, _uc a)
{
	unsigned int col = ((unsigned int)(((_uc)(r) | ((unsigned short)((_uc)(g)) << 8)) | (((unsigned short)(_uc)(b)) << 16))) | (((unsigned int)(_uc)(a)) << 24);
	return col;
}
#endif

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
