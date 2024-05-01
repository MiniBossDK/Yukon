#include <SDL.h>
#include <SDL_image.h>
#include <view/gui/gui_card_view.h>
#include <stdio.h>
#include <controller/game_state.h>
#include <view/gui/snap_zone.h>
#include <view/gui/event_handler.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

//Starts up SDL and creates window
int init();

//Frees media and shuts down SDL
void close();

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
        /*
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
         */
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

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        return 0;
    }


    LinkedCard *deck = create_deck();
    LinkedCard *column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    LinkedCard *foundation_piles[4] = {NULL, NULL, NULL, NULL};

    GameState *game_state = create_game_state(deck, column, foundation_piles);

    //show_deck(game_state, 1);
    game_init(game_state);
    ColumnView *column_view[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    FoundationView *foundation_view[4] = {NULL, NULL, NULL, NULL};


    for (int i = 0; i < 7; ++i) {
        column_view[i] = convert_column_to_column_view(create_columnview_rect(((240/2)+20)*i+50, 50),
                                                       &game_state->column[i],
                                                        i + 1,
                                                       gRenderer);
    }

    for (int i = 0; i < 4; ++i) {
        foundation_view[i] = convert_foundation_to_foundation_view(
                create_foundationview_rect(8 * (240/2) + 100, (336/2 + 20) * i + 50),
                i + 1,
                game_state->foundation,
                gRenderer);
    }

    SDL_Rect board_rect;
    board_rect.x = 0;
    board_rect.y = 0;
    board_rect.w = SCREEN_WIDTH;
    board_rect.h = SCREEN_HEIGHT;
    BoardView *board_view = create_board_view(&board_rect, column_view, foundation_view);

    set_board_snap_zones(board_view);
    //Main loop flag
    int quit = 0;

    //Clear screen
    SDL_RenderClear( gRenderer );

    render_board_view(board_view, gRenderer);
    //Update screen
    SDL_RenderPresent(gRenderer);
    //Event handler
    SDL_Event e;
    while( !quit )
    {
        SDL_PollEvent(&e);
        //Handle events on queue
        int status = handle_event(&e, board_view, gRenderer);
        if(status == -1) {
            quit = 1;
            break;
        }
    }
    //Free resources and close SDL
    close();

    return 1;
}
