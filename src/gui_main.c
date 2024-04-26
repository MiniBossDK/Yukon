#include <SDL.h>
#include <SDL_image.h>
#include <view/gui/gui_card_view.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

    /*
    LinkedCard *deck = create_deck();
    LinkedCard *column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    LinkedCard *foundation_piles[4] = {NULL, NULL, NULL, NULL};

    GameState *game_state = create_game_state(deck, column, foundation_piles);

    show_deck(game_state);

    ColumnView *column_view[7];

    FoundationView *foundation_view[4];

    BoardView *board_view;

    for (int i = 0; i < 7; ++i) {
        column_view[i] = convert_column_to_column_view(game_state->column[i], gRenderer);
    }

    for (int i = 0; i < 4; ++i) {
        foundation_view[i] = convert_foundation_to_foundation_view(game_state->foundation[i], gRenderer);
    }

    board_view = create_board_view(0, 0, 0, 0, column_view, foundation_view);
    */
    //Main loop flag
    int quit = 0;

    //Clear screen
    SDL_RenderClear( gRenderer );
    //Render texture to screen
    //SDL_RenderCopy( gRenderer, gTexture, NULL, &stretchRect);

    CardView cards[35];
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 5; ++j) {
            SDL_Rect *stretchRect = create_cardview_rect(0, 0);
            stretchRect->x = ((240/2)+20)*i+50;
            stretchRect->y = 50*j+50;
            stretchRect->w = 240/2;
            stretchRect->h = 320/2;
            CardView *cardView = create_card_view(stretchRect, create_card('K', 'C'), gRenderer);
            set_clickable_area(cardView, stretchRect->x, stretchRect->y, 0);
            render_card_view(cardView, gRenderer);
            cards[i*5+j] = *cardView;
        }
    }
    //Update screen
    SDL_RenderPresent(gRenderer);
    //Event handler
    SDL_Event e;
    SDL_Point mouse_pos;
    CardView *dragged_card = NULL;
    int dragging = 0;
    int drag_offset_x = 0;
    int drag_offset_y = 0;
    while( !quit )
    {
        SDL_PollEvent(&e);
        //Handle events on queue
        switch (e.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEMOTION:

                mouse_pos.x = e.motion.x;
                mouse_pos.y = e.motion.y;

                // TODO - Update card drag pos on this if dragged
                if(dragging) {
                    if(dragged_card == NULL) break;

                    dragged_card->card_image_rect->x = mouse_pos.x - drag_offset_x;
                    dragged_card->card_image_rect->y = mouse_pos.y - drag_offset_y;

                    SDL_RenderClear(gRenderer);
                    for (int i = 0; i < 35; ++i) {
                        render_card_view(&cards[i], gRenderer);
                    }
                    SDL_RenderPresent(gRenderer);
                }

                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT && !dragging) {
                    printf("Mouse down at (%d, %d)\n", e.button.x, e.button.y);
                    for (int i = 0; i < 35; ++i) {
                        if(SDL_PointInRect(&mouse_pos, cards[i].clickable_area)) {
                            printf("Card clicked %d\n", i);
                            dragging = 1;
                            dragged_card = &cards[i];
                            drag_offset_x = mouse_pos.x - dragged_card->card_image_rect->x;
                            drag_offset_y = mouse_pos.y - dragged_card->card_image_rect->y;
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    printf("Mouse released at (%d, %d)\n", e.button.x, e.button.y);
                    if(dragging) {
                        // TODO - Check if card is dropped on a valid location and snap it there
                        dragging = 0;
                        if(dragged_card == NULL) break;
                        dragged_card->clickable_area->x = mouse_pos.x - drag_offset_x;
                        dragged_card->clickable_area->y = mouse_pos.y - drag_offset_y;
                        dragged_card->clickable_area->h = dragged_card->card_image_rect->h;
                        dragged_card = NULL;
                    }
                }
                break;
        }
    }

    for (int i = 0; i < 35; ++i) {
        destroy_card_view(&cards[i]);
    }

    //Free resources and close SDL
    close();

    return 1;
}
