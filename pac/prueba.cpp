#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

struct Posicion {
    int fila;
    int columna;
};

const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;
const int ANCHO_MATRIZ = 10;
const int ALTO_MATRIZ = 10;
const int ANCHO_CELDA = ANCHO_VENTANA / ANCHO_MATRIZ;
const int ALTO_CELDA = ALTO_VENTANA / ALTO_MATRIZ;

// Función para dibujar una imagen en la ventana
void dibujarImagen(SDL_Renderer* renderer, SDL_Texture* textura, int posX, int posY)
{
    SDL_Rect destino;
    destino.x = posX;
    destino.y = posY;
    SDL_QueryTexture(textura, NULL, NULL, &destino.w, &destino.h);
    SDL_RenderCopy(renderer, textura, NULL, &destino);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    // Crear la ventana y el renderer
    SDL_Window* ventana = SDL_CreateWindow("Movimiento en matriz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA, ALTO_VENTANA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, 0);

    // Cargar las imágenes
    SDL_Surface* imagen1 = IMG_Load("sprites/blue.png");
    SDL_Surface* imagen2 = IMG_Load("sprites/xtra.png");
    SDL_Texture* textura1 = SDL_CreateTextureFromSurface(renderer, imagen1);
    SDL_Texture* textura2 = SDL_CreateTextureFromSurface(renderer, imagen2);

    // Vectores de posiciones en la matriz para cada imagen
    std::vector<Posicion> posiciones1;
    posiciones1.push_back({2, 3});
    posiciones1.push_back({4, 7});
    // Agrega las demás posiciones para la imagen 1 según necesites

    std::vector<Posicion> posiciones2;
    posiciones2.push_back({6, 1});
    posiciones2.push_back({8, 5});
    // Agrega las demás posiciones para la imagen 2 según necesites

    bool ejecutando = true;
    SDL_Event evento;

    while (ejecutando)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                ejecutando = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar las imágenes en las posiciones correspondientes
        for (const auto& posicion : posiciones1)
        {
            int posX = posicion.columna * ANCHO_CELDA;
            int posY = posicion.fila * ALTO_CELDA;
            dibujarImagen(renderer, textura1, posX, posY);
        }

        for (const auto& posicion : posiciones2)
        {
            int posX = posicion.columna * ANCHO_CELDA;
            int posY = posicion.fila * ALTO_CELDA;
            dibujarImagen(renderer, textura2, posX, posY);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textura1);
    SDL_DestroyTexture(textura2);
    SDL_FreeSurface(imagen1);
    SDL_FreeSurface(imagen2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}

