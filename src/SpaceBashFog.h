#pragma once

#ifndef SPACE_BASH_FOG
#define SPACE_BACH_FOG

#include <cstring>
#include <algorithm>
#include <vector>

#include "Structures.h"

class SpaceBashFog {
public:
  SpaceBashFog(int w, int h, int depth)
      : m_w(w), m_h(h), m_noiseDepth(depth), m_size(w * h), m_currentFrame(0), m_frameDelta(0) {
    m_perturbation = new float[m_size];

    for (int i = 0; i < m_noiseDepth; ++i){
        GenerateWhiteNoise(m_w, m_h, i);
        float * buffer = new float[m_size];
        GeneratePerlinNoise(buffer, m_noiseMap, m_perturbation, m_w, m_h);
        m_perlinNoise.push_back(buffer);
    }
  }

  ~SpaceBashFog() {
    delete[] m_perturbation;
    delete[] m_noiseMap;
    for (int i = 0; i < m_noiseDepth; ++i)
        delete[] m_perlinNoise[i];

    m_perturbation = 0;
    m_noiseMap = 0;
  }

void GenerateWhiteNoise(int width, int height, int offset)
{
    int len = width * height;
    m_noiseMap = new float[len];

    srand(2635 + offset);    //deterministic
    for (int i = 0; i < len; ++i)
    {
        m_noiseMap[i] = (static_cast<float>(rand()) / RAND_MAX) + 1.0f;
    }
}

float Interpolate(float x0, float x1, float alpha)
{
    return x0 * (1 - alpha) + alpha * x1;
}

void GenerateSmoothNoise(float* baseNoise, float * smoothNoise, int w, int h, int octave)
{
    int len = w * h;
    int samplePeriod = 1 << octave; // calculates 2 ^ k
    float sampleFrequency = 1.0f / static_cast<float>(samplePeriod);

    float * outp = smoothNoise;

    for (int i = 0; i < w; i++)
    {
        //calculate the horizontal sampling indices
        int sample_i0 = (i / samplePeriod) * samplePeriod;
        int sample_i1 = (sample_i0 + samplePeriod) % w; //wrap around
        float horizontal_blend = (i - sample_i0) * sampleFrequency;

        for (int j = 0; j < h; j++)
        {
            //calculate the vertical sampling indices
            int sample_j0 = (j / samplePeriod) * samplePeriod;
            int sample_j1 = (sample_j0 + samplePeriod) % h; //wrap around
            float vertical_blend = (j - sample_j0) * sampleFrequency;

            //blend the top two corners
            float top = Interpolate(baseNoise[sample_i0 + (sample_j0 * w)],
                baseNoise[sample_i1 + (sample_j0 * w)], horizontal_blend);

            //blend the bottom two corners
            float bottom = Interpolate(baseNoise[sample_i0 + (sample_j1 * w)],
                baseNoise[sample_i1 + (sample_j1 * w)], horizontal_blend);

            //final blend
            *outp = Interpolate(top, bottom, vertical_blend);
            outp++;
        }
        outp++;
    }
}

void GeneratePerlinNoise(float * perlinNoise, float * baseNoise, float * tempNoise, int w, int h)
{
    int octaves = 8;    //play with this value a little...
    int len = w * h;
    float persistence = 0.7f;
    float amplitude = 1.0f;
    float totalAmplitude = 0.0f;

    for (int i = 0; i < octaves; ++i) {
        GenerateSmoothNoise(baseNoise, tempNoise, m_w, m_h, i);

        //blend noise together
        amplitude *= persistence;
        totalAmplitude += amplitude;

        for (int j = 0; j < len; ++j)
        {
           perlinNoise[j] += (tempNoise[j] * amplitude);
        }
    }

    //normalisation
    for (int i = 0; i < len; ++i)
    {
       perlinNoise[i] /= totalAmplitude;
    }
}

  void UpdatePixel(spacebash_s::tagColor *color, int idx) {
    // Update the pixel based on the intensity at that position in our buffer.
    if (idx < 0)
      return;
    if (idx > m_size)
      return;

    float * currentFrame(m_perlinNoise[m_currentFrame]);
    // Get a number between 0 and 64
    float whiteIntensity = (currentFrame[idx] * 64.0);

    color->r = std::min(255, (color->r >> 1) + static_cast<char>(whiteIntensity));
    color->g = std::min(255, (color->g >> 1) + static_cast<char>(whiteIntensity));
    color->b = std::min(255, (color->b >> 1) + static_cast<char>(whiteIntensity));
    color->a = std::min(255, (color->a >> 1) + static_cast<char>(whiteIntensity));
  }

void NextFrame() {
    m_frameDelta++;
    if (m_frameDelta > 4) {
        m_frameDelta = 0;
        m_currentFrame++;
        if (m_currentFrame > m_perlinNoise.size() - 1)
            m_currentFrame = 0;
        }
}

protected:

  float *m_perturbation;
  float *m_noiseMap;
  std::vector<float*> m_perlinNoise;

  int m_w;
  int m_h;
  int m_noiseDepth;
  int m_size;
  int m_currentFrame;
  int m_frameDelta;
};

#endif // SPACE_BASH_FOG
