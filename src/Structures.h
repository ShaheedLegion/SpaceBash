#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL/SDL.h>

namespace spacebash
{
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#endif

typedef struct tagColor
{
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    #else
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
    #endif
} Color;
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
      Point vertices[9];
  } Cube;
};

#endif // STRUCTURES_H_INCLUDED
