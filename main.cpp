#if defined(USE_SDL)

#include <SDL/SDL.h>
#include "src/SpaceBash.h"

int main(int argc, char *args[]) {
  SDL_Init(SDL_INIT_EVERYTHING); // Start SDL
  SpaceBash spaceBash;
  SDL_Event e;

  int direction = 0;

  while (SDL_WaitEvent(&e)) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
      break;
    if (e.type == SDL_MOUSEMOTION)
      spaceBash.UpdateMouse(e.motion.x, e.motion.y);
    if (e.type == SDL_MOUSEBUTTONDOWN)
      spaceBash.Fire(e.button.x, e.button.y);
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
      direction = 1;
    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LEFT)
      direction = 0;
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
      direction = -1;
    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RIGHT)
      direction = 0;

    spaceBash.SetDirection(direction);
  }
  spaceBash.SetRunning(false);
  SDL_Quit(); // Quit SDL

  return 0;
}

#else
#include <Windows.h>
#include "src/SpaceBash.h"

namespace _main {
SpaceBash *g_spaceBash = nullptr;
unsigned char *bits = nullptr;
}

void HandleKey(WPARAM wp) {
  switch (wp) {
  case VK_ESCAPE:
    if (_main::g_spaceBash)
      _main::g_spaceBash->SetRunning(false);
    PostQuitMessage(0);
    break;
  case VK_LEFT:
    if (_main::g_spaceBash)
      _main::g_spaceBash->SetDirection(1);
    break;
  case VK_RIGHT:
    if (_main::g_spaceBash)
      _main::g_spaceBash->SetDirection(-1);
    break;
  default:
    break;
  }
}

long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp,
                               LPARAM lp) {
  switch (msg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    if (_main::g_spaceBash)
      _main::g_spaceBash->SetRunning(false);
    return 0L;
  case WM_KEYDOWN:
    HandleKey(wp);
    return 0L;
  case WM_MOUSEMOVE:
    if (_main::g_spaceBash) {
      _main::g_spaceBash->UpdateMouse(LOWORD(lp), HIWORD(lp));
    }
    return 0L;
  case WM_LBUTTONDOWN:
    if (_main::g_spaceBash)
      _main::g_spaceBash->Fire(LOWORD(lp), HIWORD(lp));
    return 0L;
  default:
    return DefWindowProc(window, msg, wp, lp);
  }
}

int main(int argc, char *args[]) {
  HDC windowDC;

  SpaceBash spaceBash;
  _main::g_spaceBash = &spaceBash;

  const wchar_t *const myclass = L"SpaceBash";
  WNDCLASSEX wndclass = {
      sizeof(WNDCLASSEX),           CS_DBLCLKS,
      WindowProcedure,              0,
      0,                            GetModuleHandle(0),
      LoadIcon(0, IDI_APPLICATION), LoadCursor(0, IDC_ARROW),
      HBRUSH(COLOR_WINDOW + 1),     0,
      myclass,                      LoadIcon(0, IDI_APPLICATION)};
  if (RegisterClassEx(&wndclass)) {
    HWND window = CreateWindowEx(0, myclass, L"SpaceBash", WS_POPUPWINDOW, 0, 0,
                                 640, 480, 0, 0, GetModuleHandle(0), 0);
    if (window) {

      windowDC = GetWindowDC(window);
      HDC hImgDC = CreateCompatibleDC(windowDC);
      if (hImgDC == NULL)
        MessageBox(NULL, L"Dc is NULL", L"ERROR!", MB_OK);

      SetBkMode(hImgDC, TRANSPARENT);
      SetTextColor(hImgDC, RGB(47, 67, 47));
      SetStretchBltMode(hImgDC, COLORONCOLOR);

      BITMAPINFO bf;
      ZeroMemory(&bf, sizeof(BITMAPINFO));

      bf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bf.bmiHeader.biWidth = 640;
      bf.bmiHeader.biHeight = 480;
      bf.bmiHeader.biPlanes = 1;
      bf.bmiHeader.biBitCount = 32;
      bf.bmiHeader.biCompression = BI_RGB;
      bf.bmiHeader.biSizeImage = (640 * 480 * (32 / 8));
      bf.bmiHeader.biXPelsPerMeter = -1;
      bf.bmiHeader.biYPelsPerMeter = -1;

      HBITMAP hImg = CreateDIBSection(hImgDC, &bf, DIB_RGB_COLORS,
                                      (void **)&_main::bits, NULL, 0);
      if (hImg == NULL)
        MessageBox(NULL, L"Image is NULL", L"ERROR!", MB_OK);
      else if (hImg == INVALID_HANDLE_VALUE)
        MessageBox(NULL, L"Image is invalid", L"Error!", MB_OK);

      unsigned char *bits_copy = _main::bits;
      DWORD err = GetLastError();

      SelectObject(hImgDC, hImg);

      spaceBash.SetBuffer(_main::bits, windowDC, hImgDC);

      ShowWindow(window, SW_SHOWDEFAULT);
      MSG msg;
      while (GetMessage(&msg, 0, 0, 0))
        DispatchMessage(&msg);
    }
  }

  return 0;
}
#endif
