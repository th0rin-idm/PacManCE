#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 40;
const int NUM_ROWS = SCREEN_HEIGHT / CELL_SIZE;
const int NUM_COLS = SCREEN_WIDTH / CELL_SIZE;

int maze[NUM_ROWS][NUM_COLS] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


bool can_move_to_cell(int row, int col) {
    return (maze[row][col] == 0);
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("PAC-MAN_CE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //negra
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = CELL_SIZE;
    rect.h  = CELL_SIZE;
    bool quit = false;


    // Carga la imagen del jugador
    SDL_Surface* pacmanSurface = IMG_Load("sprites/pacman.png");
    if (!pacmanSurface) {
        printf("No se pudo cargar la imagen del jugador: %s\n", SDL_GetError());
        return 1;
    }

    // Convierte la superficie del jugador en una textura del jugador
    SDL_Texture* pacman = SDL_CreateTextureFromSurface(renderer, pacmanSurface);
    SDL_FreeSurface(pacmanSurface); // ya no se necesita la superficie

    // Establece la posición inicial del jugador
    SDL_Rect playerRect;
    playerRect.x = 45;
    playerRect.y = 100;
    playerRect.w = 20;
    playerRect.h = 20;

    while (!quit){
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { // evento de cierre de ventana
                quit = true; // establece la bandera de salida
            } else if (event.type == SDL_KEYDOWN) { // evento de tecla presionada
                switch (event.key.keysym.sym) {
                    case SDLK_UP: // tecla de flecha hacia arriba
                        if (can_move_to_cell(playerRect.y / CELL_SIZE - 1, playerRect.x / CELL_SIZE)) {
                            playerRect.y -= CELL_SIZE/2;
                        }
                        break;
                    case SDLK_DOWN: // tecla de flecha hacia abajo
                        if (can_move_to_cell(playerRect.y / CELL_SIZE + 1, playerRect.x / CELL_SIZE)) {
                            playerRect.y += CELL_SIZE/2;
                        }
                        break;
                    case SDLK_LEFT: // tecla de flecha hacia la izquierda
                        if (can_move_to_cell(playerRect.y / CELL_SIZE, playerRect.x / CELL_SIZE - 1)) {
                            playerRect.x -= CELL_SIZE/2;
                        }
                        break;
                    case SDLK_RIGHT: // tecla de flecha hacia la derecha
                        if (can_move_to_cell(playerRect.y / CELL_SIZE, playerRect.x / CELL_SIZE + 1)) {
                            playerRect.x += CELL_SIZE/2;
                        }
                        break;
                    default:
                        break;
                }
            }
        }    

        for (int row = 0; row < NUM_ROWS; row++) {
            for (int col = 0; col < NUM_COLS; col++) {
                if (maze[row][col] == 1) { //se hace negra
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else { //azul
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                }
                rect.x = col * CELL_SIZE;
                rect.y = row * CELL_SIZE;

                SDL_RenderFillRect(renderer, &rect);
            }
        }
        // Dibuja al jugador en la posición actual si está en una celda azul
        if (maze[playerRect.y / CELL_SIZE][playerRect.x / CELL_SIZE] == 0) {
            SDL_RenderCopy(renderer, pacman, NULL, &playerRect);
        }

        SDL_RenderPresent(renderer);
    }

    // Libera la memoria de la textura del jugador
    SDL_DestroyTexture(pacman);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
