#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SQUARE_SIZE = 50;

int main(int argc, char* args[]) {

    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Inicializar SDL_image
    IMG_Init(IMG_INIT_PNG);

    // Crear ventana
    SDL_Window* window = SDL_CreateWindow("Movimiento de imagen",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    // Crear renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Cargar imagen
    SDL_Surface* image = IMG_Load("sprites/blue.png");
    if (!image) {
        std::cerr << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return 1;
    }

    // Crear textura a partir de la imagen
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    // Liberar superficie
    SDL_FreeSurface(image);

    // Definir posición inicial de la imagen
    int x = SCREEN_WIDTH / 2 - SQUARE_SIZE / 2;
    int y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;

    // Definir dirección del movimiento
    int dx = 1;
    int dy = 1;

    // Bucle principal
    bool quit = false;
    while (!quit) {

        // Manejar eventos
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar posición
        x += dx;
        y += dy;

        // Cambiar dirección si llega al borde
        if (x <= 0 || x >= SCREEN_WIDTH - SQUARE_SIZE) {
            dx *= -1;
        }
        if (y <= 0 || y >= SCREEN_HEIGHT - SQUARE_SIZE) {
            dy *= -1;
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Renderizar imagen
        SDL_Rect destRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);

        // Actualizar pantalla
        SDL_RenderPresent(renderer);

        // Esperar un poco
        SDL_Delay(10);
    }

    // Liberar recursos
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
