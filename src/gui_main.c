/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <view/gui/gui_card_view.h>
#include <view/gui/gui_column_view.h>
#include <view/gui/gui_board_view.h>
#include <stdio.h>
#include <string.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
int init();

//Loads media
int loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

int init()
{
    //Initialization flag
    int success = 1;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = 0;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_WEBP;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = 0;
                }
            }
        }
    }

    return success;
}

int loadMedia()
{
    //Loading success flag
    int success = 1;

    //Load PNG texture
    gTexture = loadTexture();
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = 0;
    }
    return success;
}

void close()
{
    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture()
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    LinkedCard *card = create_card('K', 'C');
    SDL_Surface* loadedSurface = get_card_image(card);
    if( loadedSurface == NULL )
    {
        //printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            //printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    free(card);
    return newTexture;
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        return 0;
    }

    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return 0;
    }

    LinkedCard* column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    LinkedCard* foundation_piles[4] = {NULL, NULL, NULL, NULL};

    //BoardView board_view = create_board_view(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, column, foundation_piles);


    //Main loop flag
    int quit = 0;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }
        }

        //Clear screen
        SDL_RenderClear( gRenderer );
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = 240;
        stretchRect.h = 336;
        //Render texture to screen
        SDL_RenderCopy( gRenderer, gTexture, NULL, &stretchRect);

        //Update screen
        SDL_RenderPresent( gRenderer );
    }



    //Free resources and close SDL
    close();

    return 1;
}
