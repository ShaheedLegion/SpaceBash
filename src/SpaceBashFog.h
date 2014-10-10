#pragma once

#ifndef SPACE_BASH_FOG
#define SPACE_BACH_FOG

#include <cstring>
#include <algorithm>

#include "Structures.h"

class SpaceBashFog {
public:
  SpaceBashFog(int w, int h, int depth)
      : m_w(w), m_h(h), m_d(depth), m_size(w * h) {
    m_particles = new unsigned char[m_size];

    // Evenly distribute the particles across the field.
    memset(m_particles, std::min(128, m_d), m_size * sizeof(unsigned char));

    m_perturbationSize = (m_w / 20) * (m_h / 20);
    m_perturbation = new Perturbation[m_perturbationSize];

    Perturbation *pert = m_perturbation;
    for (int y = 0; y < (m_h); y += 20) {
      for (int x = 0; x < m_w; x += 20) {
        pert->x = x;
        pert->y = y;
        pert->r = (rand() % 360);
        pert->dx = (rand() % 4);
        pert->dy = (rand() % 3);
        pert++;
      }
    }
  }

  ~SpaceBashFog() {
    delete[] m_particles;
    delete[] m_perturbation;
    m_particles = 0;
    m_perturbation = 0;
  }

  void UpdatePixel(spacebash_s::tagColor *color, int idx) {
    // Update the pixel based on the intensity at that position in our buffer.
    if (idx < 0)
      return;
    if (idx > m_size)
      return;

    unsigned char numParticlesAtIdx = m_particles[idx];

    char intensity = static_cast<char>((static_cast<float>(
        static_cast<float>(numParticlesAtIdx) /
        static_cast<float>(m_d))) * 64);

    color->r = std::min(255, color->r + intensity);
    color->g = std::min(255, color->g + intensity);
    color->b = std::min(255, color->b + intensity);
    color->a = std::min(255, color->a + intensity);
  }

  void ProcessFog() {
    // Handle the "movement" and "interactions" in the fog buffer.
    // This algorithm takes advantage of unsigned value overflow.
    int cdx = 0, cdy = 0;
    int index = 0;
    int idx = m_perturbationSize;
    Perturbation *pert = m_perturbation;
    while (idx-- > 0) {
      // Deal with applying the "fog kernel" to our buffer at the correct
      // position.
      index = (pert->y * m_w) + pert->x;
      cdx = pert->x + pert->dx;
      cdy = pert->y + pert->dy;

      // remove a particle at the current position.
      m_particles[index]--;

      index = (cdy * m_w) + cdx;

      // add the particle to the new position.
      m_particles[index]++;
      pert++;
    }
  }

protected:
  unsigned char *m_particles;

  struct Perturbation {
    unsigned short x;  //  current x position
    unsigned short y;  //  current y position
    unsigned short r;  //  current angle of rotation
    unsigned short dx; //  current speed delta x
    unsigned short dy; //  current speed delta y
  };

  Perturbation *m_perturbation;
  int m_perturbationSize;

  int m_w;
  int m_h;
  int m_d;
  int m_size;
};

#endif // SPACE_BASH_FOG