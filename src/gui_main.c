#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL2_rotozoom.h>

#define GRID_ROWS 4
#define GRID_COLS 13
#define CELL_WIDTH 450
#define CELL_HEIGHT 630
#define SCREEN_WIDTH (1920/2)
#define SCREEN_HEIGHT (1080/2)

// Array of card names
const char* cards[] = {
        "2C", "2D", "2H", "2S", "3C", "3D", "3H", "3S", "4C", "4D", "4H", "4S", "5C",
        "5D", "5H", "5S", "6C", "6D", "6H", "6S", "7C", "7D", "7H", "7S", "8C", "8D",
        "8H", "8S", "9C", "9D", "9H", "9S", "TC", "TD", "TH", "TS", "JC", "JD", "JH",
        "JS", "QC", "QD", "QH", "QS", "KC", "KD", "KH", "KS", "AC", "AD", "AH", "AS"
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    int imgFlags = IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 0;
    }

    return 1;
}

SDL_Texture* loadTexture(const char* path, double scale) {
    SDL_Texture* texture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        // Scale the surface
        SDL_Surface* zoomedSurface = rotozoomSurface(loadedSurface, 0, scale, SMOOTHING_ON);
        if (zoomedSurface == NULL) {
            printf("Unable to scale image %s! SDL_rotozoom Error: %s\n", path, SDL_GetError());
        } else {
            texture = SDL_CreateTextureFromSurface(gRenderer, zoomedSurface);
            if (texture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
            }
            SDL_FreeSurface(zoomedSurface);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    // Calculate scaling factor
    double scaleW = (double)SCREEN_WIDTH / (GRID_COLS * CELL_WIDTH);
    double scaleH = (double)SCREEN_HEIGHT / (GRID_ROWS * CELL_HEIGHT);
    double scale = (scaleW < scaleH) ? scaleW : scaleH;

    // Apply scaling factor to cell width and height
    int scaledCellWidth = CELL_WIDTH * scale;
    int scaledCellHeight = CELL_HEIGHT * scale;

    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    SDL_RenderClear(gRenderer);

    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            int cardIndex = row * GRID_COLS + col;
            char path[256];
            sprintf(path, "resources/cards/%s.webp", cards[cardIndex]);

            SDL_Texture* texture = loadTexture(path, scale);
            if (texture == NULL) {
                printf("Failed to load texture!\n");
                closeSDL();
                return -1;
            }
            SDL_Rect destRect = {col * scaledCellWidth, row * scaledCellHeight, scaledCellWidth, scaledCellHeight};
            SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
            SDL_DestroyTexture(texture); // Don't forget to destroy the texture after using it
        }
    }

    SDL_RenderPresent(gRenderer);

    // Event loop
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_RETURN:
                        quit = 1;
                        break;
                }
            } else if (e.type == SDL_WINDOWEVENT) {
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        // Recalculate scaling factor
                        scaleW = (double)e.window.data1 / (GRID_COLS * CELL_WIDTH);
                        scaleH = (double)e.window.data2 / (GRID_ROWS * CELL_HEIGHT);
                        scale = (scaleW < scaleH) ? scaleW : scaleH;

                        // Apply scaling factor to cell width and height
                        scaledCellWidth = CELL_WIDTH * scale;
                        scaledCellHeight = CELL_HEIGHT * scale;

                        // Clear the renderer
                        SDL_RenderClear(gRenderer);

                        // Reload and redraw the images
                        for (int row = 0; row < GRID_ROWS; ++row) {
                            for (int col = 0; col < GRID_COLS; ++col) {
                                int cardIndex = row * GRID_COLS + col;
                                char path[256];
                                sprintf(path, "resources/cards/%s.webp", cards[cardIndex]);

                                SDL_Texture* texture = loadTexture(path, scale);
                                if (texture == NULL) {
                                    printf("Failed to load texture!\n");
                                    closeSDL();
                                    return -1;
                                }
                                SDL_Rect destRect = {col * scaledCellWidth, row * scaledCellHeight, scaledCellWidth, scaledCellHeight};
                                SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
                                SDL_DestroyTexture(texture); // Don't forget to destroy the texture after using it
                            }
                        }

                        // Update the screen
                        SDL_RenderPresent(gRenderer);
                        break;
                }
            }
        }
    }

    closeSDL();

    return 0;
}
