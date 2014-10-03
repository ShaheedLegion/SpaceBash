#pragma once

#ifndef SPACE_BASH_SURFACE
#define SPACE_BACH_SURFACE

typedef unsigned int Uint32;

class SpaceBashSurface {
public:
	SpaceBashSurface(int w, int h, int bpp) : m_w(w), m_h(h), m_bpp(bpp) {
		m_pixels = new unsigned char[m_w * m_h * (m_bpp / 8)];
		m_backBuffer = new unsigned char[m_w * m_h * (m_bpp / 8)];
	}

	~SpaceBashSurface() {
		delete m_pixels;
		delete m_backBuffer;
	}

	void Flip(){
		//We need a mechanism to actually present the buffer to the drawing system.
		unsigned char * temp = m_pixels;
		m_pixels = m_backBuffer;
		m_backBuffer = temp;
	}

	Uint32* GetPixels() {
		return reinterpret_cast<Uint32*>(m_pixels); 
	}

	int GetBPP() {
		return m_bpp;
	}

protected:
	unsigned char* m_pixels;
	unsigned char* m_backBuffer;

	int m_w;
	int m_h;
	int m_bpp;
};

#endif  // SPACE_BASH_SURFACE