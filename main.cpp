#if defined(USE_SDL)

#include <SDL/SDL.h>
#include "src/SpaceBash.h"

int main( int argc, char * args[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );    //Start SDL
    SpaceBash spaceBash;
    SDL_Event e;

    int direction = 0;

    while ( SDL_WaitEvent(&e) )
    {
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
    SDL_Quit();    //Quit SDL

    return 0;
}

#else
#include <Windows.h>
#include "src/SpaceBash.h"

namespace _main {
SpaceBash *g_spaceBash = nullptr;
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
    if (wp == VK_ESCAPE) {
      if (_main::g_spaceBash)
        _main::g_spaceBash->SetRunning(false);
      PostQuitMessage(0);
    }
    return 0L;
  case WM_MOUSEMOVE:
    if (_main::g_spaceBash) {
      _main::g_spaceBash->UpdateMouse(LOWORD(lp), HIWORD(lp));
    }
    return 0L;
  case WM_LBUTTONDOWN:
  //	std::cout << "\nmouse left button down at (" << LOWORD(lp)
  //		<< ',' << HIWORD(lp) << ")\n";
  // fall thru
  default:
    //	std::cout << '.';
    return DefWindowProc(window, msg, wp, lp);
  }
}

int main(int argc, char *args[]) {
  HDC window;
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
      ShowWindow(window, SW_SHOWDEFAULT);
      MSG msg;
      while (GetMessage(&msg, 0, 0, 0))
        DispatchMessage(&msg);
    }
  }

  // int direction = 0;
  /*
  while (SDL_WaitEvent(&e))
  {
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
  */
  // spaceBash.SetRunning(false);
  // SDL_Quit();    //Quit SDL

  return 0;
}
#endif

