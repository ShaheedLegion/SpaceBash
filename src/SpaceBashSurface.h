#pragma once

#ifndef SPACE_BASH_SURFACE
#define SPACE_BACH_SURFACE

#include <Windows.h>
#include <cstring>

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
		m_pixels = NULL;
		m_backBuffer = NULL;
	}


	void SetScreen(unsigned char * buffer, HDC screenDC, HDC memDC) {
		m_screen = buffer;
		m_screenDC = screenDC;
		m_dc = memDC;
	}

	void Flip() {
		//We need a mechanism to actually present the buffer to the drawing system.
		unsigned char * temp = m_pixels;
		m_pixels = m_backBuffer;
		m_backBuffer = temp;

		memcpy(m_screen, m_pixels, (m_w * m_h * (m_bpp / 8)));
		BitBlt(m_screenDC, 0, 0, m_w, m_h, m_dc, 0, 0, SRCCOPY);
	}

	Uint32* GetPixels() {
		return reinterpret_cast<Uint32*>(m_backBuffer); 
	}

	int GetBPP() const {
		return m_bpp;
	}

	int GetWidth() const {
		return m_w;
	}

	int GetHeight() const {
		return m_h;
	}

protected:
	unsigned char* m_pixels;
	unsigned char* m_backBuffer;
	unsigned char* m_screen;
	int m_w;
	int m_h;
	int m_bpp;
	HDC m_screenDC;
	HDC m_dc;
};

#endif  // SPACE_BASH_SURFACE