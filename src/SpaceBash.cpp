#include "SpaceBash.h"
#include "StarField.h"
#include "AsteroidObjectField.h"
#include "Utilities.h"

#define BPP 32

typedef std::vector<PlaneObject *>::iterator pIter;
SpaceBash *g_spaceBash;

#if defined(USE_SDL)
int Update(void *data)
#else
DWORD WINAPI Update(LPVOID lpParameter)
#endif
{ // poll for some kind of event here to signal that we want to exit.
  pIter i = g_spaceBash->planes.begin(), e = g_spaceBash->planes.end();
  while (g_spaceBash->IsRunning()) {
    g_spaceBash->screen_buffer->Clear();
    g_spaceBash->CheckCollisions(); // check collisions first - then we can
                                    // immediately render the exlosion.
    g_spaceBash->fog->ProcessFog();
    g_spaceBash->camera->StartBatch();
    for (i = g_spaceBash->planes.begin(); i != e; ++i)
      (*i)->Update();

    // g_spaceBash->screen_buffer->Blur();   //leave it out while we optimize it
    int len = g_spaceBash->screen_buffer->GetWidth() *
              g_spaceBash->screen_buffer->GetHeight();
    spacebash_s::Color *bp = g_spaceBash->screen_buffer->GetBuffer();
    spacebash_s::Color *lp = g_spaceBash->lightingMask->GetBuffer();

#if defined(USE_SDL)
    if (SDL_MUSTLOCK(g_spaceBash->screen))
      SDL_LockSurface(g_spaceBash->screen);
#endif

    int index = 0;
    Uint32 *pixels = (Uint32 *)g_spaceBash->screen->GetPixels();
    while (--len > 0) {
      spacebash_s::Color result(*(Uint32 *)(bp) & *(Uint32 *)(lp));
      g_spaceBash->fog->UpdatePixel(&result, index);
      *((Uint32 *)pixels) = *(Uint32 *)(&result);
      bp++;
      lp++;
      pixels++;
      index++;
    }
#if defined(USE_SDL)
    if (SDL_MUSTLOCK(g_spaceBash->screen))
      SDL_UnlockSurface(g_spaceBash->screen);

    SDL_Flip(g_spaceBash->screen); // Update Screen
    SDL_Delay(30); // Pause
#else
    g_spaceBash->screen->Flip();
    g_spaceBash->updateThread->Delay(15);
#endif
  }

  return 0;
}

SpaceBash::SpaceBash() {
  g_spaceBash = this;
  int width = 640;
  int height = 480;
  spacebash::InitTables();
#if defined(USE_SDL)
  const SDL_VideoInfo *pVidInfo = SDL_GetVideoInfo();
  if (pVidInfo) {
    width = pVidInfo->current_w / 2;
    height = pVidInfo->current_h / 2;
  }

  screen = SDL_SetVideoMode(width, height, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
  screen = new SpaceBashSurface(width, height, BPP);
#endif
  camera = new Camera(width, height);

  // Hard code the depth for now.
  fog = new SpaceBashFog(width, height, 100);

  lightingMask = new BufferObject(width, height);
  if (lightingMask) { // create the mask we apply to create lighting effect
    int cx = width / 2;
    int cy = height / 2;
    for (int y = 0; y < (cy + 1); ++y) {
      for (int x = 0; x < (cx + 1); ++x) {
        spacebash::grad_line(lightingMask, cx, cy, x, 0);
        spacebash::grad_line(lightingMask, cx, cy, width - x, 0);
        spacebash::grad_line(lightingMask, cx, cy, x, height);
        spacebash::grad_line(lightingMask, cx, cy, width - x, height);
      }
      spacebash::grad_line(lightingMask, cx, cy, 0, y);
      spacebash::grad_line(lightingMask, cx, cy, 0, height - y);
      spacebash::grad_line(lightingMask, cx, cy, width, y);
      spacebash::grad_line(lightingMask, cx, cy, width, height - y);
    }
  }
  screen_buffer = new BufferObject(width, height);
  planes.push_back(new StarField(screen_buffer, camera, screen->GetBPP()));
  field = new AsteroidObjectField(screen_buffer, camera, screen->GetBPP());
  planes.push_back(field);
  overlay = new Overlay(screen_buffer, camera, screen->GetBPP());
  planes.push_back(overlay);

  SetRunning(true);
#if defined(USE_SDL)
  updateThread = SDL_CreateThread(&Update, (void *)NULL);
#else
  updateThread = new SpaceBashThread(&Update);
#endif
}

SpaceBash::~SpaceBash() {
#if defined(USE_SDL)
  SDL_KillThread(updateThread);
#else
  updateThread->Join();
#endif
  pIter i = planes.begin(), e = planes.end();
  for (; i != e; ++i)
    delete (*i);

  delete screen_buffer;
  delete lightingMask;
  spacebash::DestroyTables();
}

#if !defined(USE_SDL)
void SpaceBash::SetBuffer(unsigned char *buffer, HDC scrDC, HDC memDC) {
  if (screen) {
    screen->SetScreen(buffer, scrDC, memDC);
    if (updateThread)
      updateThread->Start();
  }
}
#endif

bool SpaceBash::IsRunning() { return bRunning; }

void SpaceBash::SetRunning(bool bRun) { bRunning = bRun; }

void SpaceBash::UpdateMouse(int mcx, int mcy) { camera->UpdateMouse(mcx, mcy); }

void SpaceBash::SetDirection(int dir) { camera->SetRotation(dir); }

void SpaceBash::Fire(int mcx, int mcy) { overlay->SetFiring(mcx, mcy); }

void SpaceBash::CheckCollisions() {
  if (!overlay->IsFiring())
    return;
#if 0
    std::vector<spacebash_s::Cube *> visibleObjects;
    field->GetVisibleObjects(visibleObjects);

    std::vector::<spacebash_s::Cube *>::iterator _it(visibleObjects.begin()), _end(visibleObjects.end());
    spacebash_s::Cube * c;
    for (; _it != _end; ++_it)
    {
        c = *_it;
        if (c->vertices[8].tx ... )
        {
            if (c->vertices[8].ty ...)
            {
                c->exploding = true;
            }
        }
    }
#endif // 0
  // run collission tests here
  /*
  Start by enumerating the objects from the AstroidObjectField, then running the
  collission test
  against all those objects. We can easily cull more than hald of the objets out
  of the test since
  they will not be visible on the screen.

  The rest of the objects we will test by proximity to the center of the screen.
  We test proximity to the center
  point of each cube - it was there by luck.

  If the proximity is within a certain boundary, then we simply cause the
  particle trail to "explode" from the center
  of the cube - we then increment the point scheduler (still to be written).
  */
}
