#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

int main ( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *png;
    png = IMG_Load("obj/pc.png");
    if (!png)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect dstrect;
    dstrect.x = (screen->w - png->w) / 2;
    dstrect.y = (screen->h - png->h) / 2;

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            }
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        SDL_BlitSurface(png, 0, screen, &dstrect);

        SDL_Flip(screen);
    }

    SDL_FreeSurface(png);

    printf("Exited cleanly\n");
    return 0;
}
