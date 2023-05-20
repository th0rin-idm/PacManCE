#include <SDL2/SDL.h>

class VentanaEmergente {
public:
    VentanaEmergente() {
        ventanaEmergente = SDL_CreateWindow("¡Has ganado!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
    }

    ~VentanaEmergente() {
        SDL_DestroyWindow(ventanaEmergente);
    }

    void Mostrar() {
        SDL_ShowWindow(ventanaEmergente);

        // Esperar hasta que se cierre la ventana emergente
        bool ventanaAbierta = true;
        while (ventanaAbierta) {
            SDL_Event evento;
            while (SDL_PollEvent(&evento)) {
                if (evento.type == SDL_QUIT) {
                    ventanaAbierta = false;
                }
            }
        }
    }

private:
    SDL_Window* ventanaEmergente;
};

int main() {
    // Inicializar SDL2 y crear la ventana principal del juego

    // Simular que el jugador ha ganado el juego
    VentanaEmergente ventana;
    ventana.Mostrar();

    // Continuar con el resto del juego

    // Cerrar SDL2 y liberar recursos

    return 0;
}
