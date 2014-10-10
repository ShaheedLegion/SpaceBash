#pragma once
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#if defined(USE_SDL)
#include <SDL/SDL.h>
#else
typedef unsigned char Uint8;
typedef unsigned int Uint32;
#endif

namespace spacebash_s {
#if defined(USE_SDL)
typedef Uint8 _uc;
#else
typedef unsigned char _uc;
#endif

typedef struct tagColor {
#if defined(USE_SDL)
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
#else
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
#endif

  tagColor() : r(0), g(0), b(0), a(0) {}
  tagColor(Uint32 col) {
    Uint8 *src = reinterpret_cast<Uint8 *>(&col);
    r = src[0];
    g = src[1];
    b = src[2];
    a = src[3];
  }
} Color;

#if defined(USE_SDL)
static Uint32 GetCol(SDL_PixelFormat *pixel_fmt, _uc r, _uc g, _uc b) {
  Uint32 col = SDL_MapRGB(pixel_fmt, r, g, b);
  return col;
}
static Uint32 GetCol_A(SDL_PixelFormat *pixel_fmt, _uc r, _uc g, _uc b, _uc a) {
  Uint32 col = SDL_MapRGBA(pixel_fmt, r, g, b, a);
  return col;
}
#else
static Uint32 GetCol(_uc r, _uc g, _uc b) {
  unsigned int col =
      ((unsigned int)(((_uc)(r) | ((unsigned short)((_uc)(g)) << 8)) |
                      (((unsigned short)(_uc)(b)) << 16)));
  return col;
}
static Uint32 GetCol_A(_uc r, _uc g, _uc b, _uc a) {
  unsigned int col =
      ((unsigned int)(((_uc)(r) | ((unsigned short)((_uc)(g)) << 8)) |
                      (((unsigned short)(_uc)(b)) << 16))) |
      (((unsigned int)(_uc)(a)) << 24);
  return col;
}
#endif

typedef struct tagPoint {
  float x;
  float y;
  float z;
  int tx;
  int ty;
} Point;

typedef struct tagBufferPoint {
  float z;
  Uint32 color;
} BufferPoint;

typedef struct tagCube {
  Point vertices[8];
  Point dimensions[3];
  bool exploding;
  bool visible;
} Cube;
};

#endif // STRUCTURES_H_INCLUDED
