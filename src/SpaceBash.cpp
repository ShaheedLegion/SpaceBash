#include "SpaceBash.h"
#include "StarField.h"
#include "AsteroidField.h"
#include "ObjectField.h"
#include "Overlay.h"
#include "Utilities.h"

#define BPP 32

typedef std::vector<PlaneObject*>::iterator pIter;
SpaceBash * g_spaceBash;

int Update(void * data)
{   //poll fr some kind of event here to signal that we want to exit.
    pIter i = g_spaceBash->planes.begin(), e = g_spaceBash->planes.end();
    while (g_spaceBash->IsRunning())
    {
        g_spaceBash->screen_buffer->Clear();
        g_spaceBash->camera->StartBatch();
        for (i = g_spaceBash->planes.begin(); i != e; ++i)
            (*i)->Update();

        //g_spaceBash->screen_buffer->Blur();   //leave it out while we optimize it
        int len = g_spaceBash->screen_buffer->GetWidth() * g_spaceBash->screen_buffer->GetHeight();
        spacebash::Color * bp =  g_spaceBash->screen_buffer->GetBuffer();

        if (SDL_MUSTLOCK(g_spaceBash->screen))
            SDL_LockSurface(g_spaceBash->screen);

        Uint32 * pixels = (Uint32*)g_spaceBash->screen->pixels;
        while (--len > 0)
        {
            *((Uint32*)pixels) = *(Uint32*)(bp);
            bp++;
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
    screen_buffer = new BufferObject(width, height);
    planes.push_back(new StarField(screen_buffer, camera));
    planes.push_back(new AsteroidField(screen_buffer, camera));
    planes.push_back(new ObjectField(screen_buffer, camera));
    planes.push_back(new Overlay(screen_buffer, camera));

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
