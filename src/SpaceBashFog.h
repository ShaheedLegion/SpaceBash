#pragma once

#ifndef SPACE_BASH_FOG
#define SPACE_BACH_FOG

#include <Windows.h>
#include <cstring>

#include "Structures.h"

class SpaceBashFog {
public:
  SpaceBashFog(int w, int h, int depth)
      : m_w(w), m_h(h), m_d(depth), m_size(w * h) {
    m_particles = new unsigned char[m_size];
  }

  ~SpaceBashFog() {
    delete [] m_particles;
    m_particles = NULL;
  }

  void UpdatePixel(spacebash_s::tagColor *color, int idx) {
    // Update the pixel based on the intensity at that position in our buffer.
    if (idx < 0)
      return;
    if (idx > m_size)
      return;

    unsigned char numParticlesAtIdx = m_particles[idx];

    unsigned char intensity = static_cast<unsigned char>(
        static_cast<float>(numParticlesAtIdx) /
        static_cast<float>(m_d)); // some calculation which gets the
                                  // value from the buffer and does
                                  // something with it...

    color->r = std::max(255, color->r + intensity);
    color->g = std::max(255, color->g + intensity);
    color->b = std::max(255, color->b + intensity);
    color->a = std::max(255, color->a + intensity);
  }

  void ProcessFog() {
    // Handle the "movement" and "interactions" in the fog buffer
  }

protected:
  unsigned char *m_particles;
  int m_w;
  int m_h;
  int m_d;
  int m_size;
};

#endif // SPACE_BASH_FOG