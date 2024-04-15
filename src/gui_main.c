#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main(int argc, char** args)
{
    // screen dimensions
    const int SCREEN_WIDTH = 854;
    const int SCREEN_HEIGHT = 480;

    // fps cap
    const float fps_cap = 60.0f;
    const float fps_cap_in_ms = 1000.0f/fps_cap;
    uint64_t start;
    uint64_t end;
    float delta;

    // window title
    const char* TITLE = "Hardware Accelerated Blue Screen!";

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    bool is_game_loop_stopped = false;

    // Initialize SDL2
    // goto is used only for exception handling
    if(0 != SDL_Init(SDL_INIT_EVERYTHING)) goto bail;

    // create the window
    window = SDL_CreateWindow(
            TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
    );

    // check if window was created
    // goto is used only for exception handling
    if(NULL == window) goto cleanup;

    // create a 2D accelerated renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // check if renderer was created
    // goto is used only for exception handling
    if(NULL == renderer) goto cleanup_window;

    while(!is_game_loop_stopped)
    {
        start = SDL_GetPerformanceCounter();

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    is_game_loop_stopped = true;
                    break;
            }
        }

        // set drawing color
        SDL_SetRenderDrawColor(renderer, 50, 100, 255, 255);

        // clear screen
        SDL_RenderClear(renderer);

        // update screen
        SDL_RenderPresent(renderer);

        end = SDL_GetPerformanceCounter();

        // get how long each cycle has taken
        delta = (end - start)/(float)SDL_GetPerformanceFrequency() * 1000.0f;

        // limit fps
        // wait if time taken is less than target fps in ms.
        if(delta < fps_cap_in_ms)
        {
            SDL_Delay(fps_cap_in_ms - delta);
        }
    }

    // free resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

    cleanup_window:
    SDL_DestroyWindow(window);

    cleanup:
    SDL_Quit();

    bail:
    return EXIT_FAILURE;
}
