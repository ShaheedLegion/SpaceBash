#include "SpaceBash.h"
#include "StarField.h"
//#include "AsteroidField.h"
//#include "ObjectField.h"
#include "AsteroidObjectField.h"
#include "Overlay.h"
#include "Utilities.h"

#define BPP 32

typedef std::vector<PlaneObject*>::iterator pIter;
SpaceBash * g_spaceBash;

int Update(void * data)
{   //poll for some kind of event here to signal that we want to exit.
    pIter i = g_spaceBash->planes.begin(), e = g_spaceBash->planes.end();
    while (g_spaceBash->IsRunning())
    {
        g_spaceBash->screen_buffer->Clear();
        g_spaceBash->camera->StartBatch();
        for (i = g_spaceBash->planes.begin(); i != e; ++i)
            (*i)->Update();

        //g_spaceBash->screen_buffer->Blur();   //leave it out while we optimize it
        int len = g_spaceBash->screen_buffer->GetWidth() * g_spaceBash->screen_buffer->GetHeight();
        spacebash_s::Color * bp =  g_spaceBash->screen_buffer->GetBuffer();
        spacebash_s::Color * lp =  g_spaceBash->lightingMask->GetBuffer();

        if (SDL_MUSTLOCK(g_spaceBash->screen))
            SDL_LockSurface(g_spaceBash->screen);

        Uint32 * pixels = (Uint32*)g_spaceBash->screen->pixels;
        while (--len > 0)
        {
            *((Uint32*)pixels) = *(Uint32*)(bp) & *(Uint32*)(lp);
            bp++;
            lp++;
            pixels++;
        }
        if (SDL_MUSTLOCK(g_spaceBash->screen))
            SDL_UnlockSurface(g_spaceBash->screen);

        SDL_Flip(g_spaceBash->screen);        //Update Screen
        SDL_Delay(30);        //Pause
    }

    return 0;
}

SpaceBash::SpaceBash()
{
    g_spaceBash = this;
    int width = 640;
    int height = 480;
    spacebash::InitTables();

    const SDL_VideoInfo * pVidInfo = SDL_GetVideoInfo();
    if (pVidInfo)
    {
        width = pVidInfo->current_w / 2;
        height = pVidInfo->current_h / 2;
    }

    screen = SDL_SetVideoMode(width, height, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
    camera = new Camera(width, height);
    lightingMask = new BufferObject(width, height);
    if (lightingMask)
    {   //create the mask we apply to create lighting effect
        int cx = width / 2;
        int cy = height / 2;
        for (int y = 0; y < (cy + 1); ++y)
        {
            for (int x = 0; x < (cx + 1); ++x)
            {
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
    planes.push_back(new StarField(screen_buffer, camera, screen->format));
 //   planes.push_back(new AsteroidField(screen_buffer, camera, screen->format));
 //   planes.push_back(new ObjectField(screen_buffer, camera, screen->format));
    planes.push_back(new AsteroidObjectField(screen_buffer, camera, screen->format));
    planes.push_back(new Overlay(screen_buffer, camera, screen->format));

    SetRunning(true);
    updateThread = SDL_CreateThread(&Update, (void *)NULL);
}

SpaceBash::~SpaceBash()
{
    SDL_KillThread(updateThread);
    pIter i = planes.begin(), e = planes.end();
    for (; i != e; ++i)
        delete (*i);

    delete screen_buffer;
    delete lightingMask;
    spacebash::DestroyTables();
}

bool SpaceBash::IsRunning()
{
    return bRunning;
}

void SpaceBash::SetRunning(bool bRun)
{
    bRunning = bRun;
}

void SpaceBash::UpdateMouse(int mcx, int mcy)
{
    camera->UpdateMouse(mcx, mcy);
}

void SpaceBash::SetDirection(int dir)
{
    camera->SetRotation(dir);
}
