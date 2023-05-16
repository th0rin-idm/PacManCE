#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "maps.cpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 40;
const int NUM_ROWS = SCREEN_HEIGHT / CELL_SIZE;
const int NUM_COLS = SCREEN_WIDTH / CELL_SIZE;

int **maze=SelectMap();

// Función para actualizar la posición del fantasma
void update_ghost_position(SDL_Rect& blueRect, int& DestRow, int& DestCol, int GhostSpeed) {
    // Calcula la dirección del fantasma (arriba, abajo, izquierda o derecha)
    int rowDiff = DestRow - (blueRect.y / CELL_SIZE);
    int colDiff = DestCol - (blueRect.x / CELL_SIZE);

    if (rowDiff == 0 && colDiff == 0) {
        // Si el fantasma ya está en su destino, elige un nuevo destino al azar
        DestRow = rand() % NUM_ROWS;
        DestCol = rand() % NUM_COLS;
    } else {
        // Mueve el fantasma en la dirección del destino
        if (abs(rowDiff) >= abs(colDiff)) {
            if (rowDiff > 0) {
                blueRect.y += GhostSpeed;
            } else {
                blueRect.y -= GhostSpeed;
            }
        } else {
            if (colDiff > 0) {
                blueRect.x += GhostSpeed;
            } else {
                blueRect.x -= GhostSpeed;
            }
        }
    }
}


bool can_move_to_cell(int row, int col) {
    return (maze[row][col] == 0);
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("PAC-MAN_CE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //negra
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = CELL_SIZE;
    rect.h  = CELL_SIZE;
    bool quit = false;

    int centerX;
    int centerY;

    // Carga la imagen del jugador
    SDL_Surface* cherrySurface = IMG_Load("sprites/cherry.png");
    if (!cherrySurface) {
        printf("No se pudo cargar la imagen de cherry: %s\n", SDL_GetError());
        return 1;
    }
    // Convierte la superficie del jugador en una textura del jugador
    SDL_Texture* cherry = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(cherrySurface); // ya no se necesita la superficie    
    SDL_Rect cherryRect; // Establece la posición inicial del jugador
    cherryRect.x = 45;
    cherryRect.y = 100;
    cherryRect.w = 20;
    cherryRect.h = 20;

    // Carga la imagen del jugador
    SDL_Surface* pacmanSurface = IMG_Load("sprites/pacman.png");
    if (!pacmanSurface) {
        printf("No se pudo cargar la imagen del jugador: %s\n", SDL_GetError());
        return 1;
    }
    // Convierte la superficie del jugador en una textura del jugador
    SDL_Texture* pacman = SDL_CreateTextureFromSurface(renderer, pacmanSurface);
    //SDL_FreeSurface(pacmanSurface); // ya no se necesita la superficie    
    SDL_Rect playerRect; // Establece la posición inicial del jugador
    playerRect.x = 45;
    playerRect.y = 100;
    playerRect.w = 20;
    playerRect.h = 20;

    int DestRow = 6; // Fila de destino del fantasma azul
    int DestCol = 4; // Columna de destino del fantasma azul
    int GhostSpeed = 1; // Velocidad de movimiento del fantasma azul

    SDL_Surface* blueSurface = IMG_Load("sprites/blue.png");
    if (!blueSurface) {
        printf("No se pudo cargar la imagen del azul: %s\n", SDL_GetError());
        return 1;
    }
    //Convierte la superficie del fantasma en una textura
    SDL_Texture* blue = SDL_CreateTextureFromSurface(renderer, blueSurface);
    SDL_FreeSurface(blueSurface); // ya no se necesita la superficie
    SDL_Rect blueRect; // Establece la posición inicial blue
    blueRect.x = 45;
    blueRect.y = 150;
    blueRect.w = 20;
    blueRect.h = 20;


    SDL_Surface* blackSurface = IMG_Load("sprites/black.png");
    if (!blackSurface) {
        printf("No se pudo cargar la imagen del negro: %s\n", SDL_GetError());
        return 1;
    }
    //Convierte la superficie del fantasma en una textura
    SDL_Texture* black = SDL_CreateTextureFromSurface(renderer, blackSurface);
    SDL_FreeSurface(blackSurface); // ya no se necesita la superficie
    SDL_Rect blackRect;
    blackRect.x = 35;
    blackRect.y = 160;
    blackRect.w = 20;
    blackRect.h = 20;


    SDL_Surface* yellowSurface = IMG_Load("sprites/yellow.png");
    if (!yellowSurface) {
        printf("No se pudo cargar la imagen del amarillo: %s\n", SDL_GetError());
        return 1;
    }
    // Convierte la superficie del fantasma en una textura
    SDL_Texture* yellow = SDL_CreateTextureFromSurface(renderer, yellowSurface);
    SDL_FreeSurface(yellowSurface); // ya no se necesita la superficie
    SDL_Rect yellowRect;
    yellowRect.x = 35;
    yellowRect.y = 170;
    yellowRect.w = 20;
    yellowRect.h = 20;


    SDL_Surface* xtraSurface = IMG_Load("sprites/xtra.png");
    if (!xtraSurface) {
        printf("No se pudo cargar la imagen del xtra: %s\n", SDL_GetError());
        return 1;
    }
    // Convierte la superficie del fantasma en una textura
    SDL_Texture* xtra = SDL_CreateTextureFromSurface(renderer, xtraSurface);
    SDL_FreeSurface(xtraSurface); // ya no se necesita la superficie
    SDL_Rect xtraRect;
    xtraRect.x = 35;
    xtraRect.y = 180;
    xtraRect.w = 20;
    xtraRect.h = 20;

    //Cargar la imagen de las monedas
    SDL_Texture* coinTexture = IMG_LoadTexture(renderer, "sprites/coin.png");
    
    //vector para guardar las monedas
    std::vector<SDL_Rect> coins;
    int score=0;
    int life=3;
    int level=0;
    int maxcoins=0;

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

        SDL_RenderClear(renderer);

        for (int row = 0; row < 12; row++) {
            for (int col = 0; col < 12; col++) {
                if (maze[row][col] == 1) { //se hace negra
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else if(maze[row][col]==0){ //azul
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    // Calcula la posición del centro del cuadrado blanco
                    centerX = rect.x + CELL_SIZE/2;
                    centerY = rect.y + CELL_SIZE/2;
                    int COIN_SIZE = 22;
                    SDL_Rect coinRect = { centerX + 26, centerY - 12, COIN_SIZE, COIN_SIZE };
                    
                    //SDL_RenderFillRect(renderer, &rect);
                    if(maxcoins<80){
                    coins.push_back(coinRect);
                    maxcoins++;
                    }else if(score==400){ 
                        maxcoins=0;
                    }
                }else{//blanco o eso queria pero printea negro igual xd
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                rect.x = col * CELL_SIZE;
                rect.y = row * CELL_SIZE;

                SDL_RenderFillRect(renderer, &rect);
            }
        }
        
        // Dibujar las monedas
        for (const auto& coin : coins) {
    SDL_RenderCopy(renderer, coinTexture, nullptr, &coin);
            }   
        //Dibujar los fantasmas
        // Actualiza la posición del fantasma azul
        
        if (blueRect.x < DestCol * CELL_SIZE) {
            if (can_move_to_cell(blueRect.y / CELL_SIZE, (blueRect.x + GhostSpeed) / CELL_SIZE)) {
                blueRect.x += GhostSpeed;
            } else {
                DestCol = blueRect.x / CELL_SIZE;
            }
        }else if (blueRect.x > DestCol * CELL_SIZE) {
            if (can_move_to_cell(blueRect.y / CELL_SIZE, (blueRect.x - GhostSpeed) / CELL_SIZE)) {
                blueRect.x -= GhostSpeed;
            } else {
                DestCol = blueRect.x / CELL_SIZE;
            }
        } else if (blueRect.y < DestRow * CELL_SIZE) {
            if (can_move_to_cell((blueRect.y + GhostSpeed) / CELL_SIZE, blueRect.x / CELL_SIZE)) {
                blueRect.y += GhostSpeed;
            } else {
                DestRow = blueRect.y / CELL_SIZE;
            }
        } else if (blueRect.y > DestRow * CELL_SIZE) {
            if (can_move_to_cell((blueRect.y - GhostSpeed) / CELL_SIZE, blueRect.x / CELL_SIZE)) {
                blueRect.y -= GhostSpeed;
            } else {
                DestRow = blueRect.y / CELL_SIZE;
            }
        } 
        


        update_ghost_position(blueRect, DestRow, DestCol, GhostSpeed/15);

        SDL_RenderCopy(renderer, blue, nullptr, &blueRect);
        if(score>=100){
            SDL_RenderCopy(renderer, xtra, nullptr, &xtraRect);
            if(score>=200){
                SDL_RenderCopy(renderer, yellow, nullptr, &yellowRect);
                if(score>=300){
                    SDL_RenderCopy(renderer, black, nullptr, &blackRect);
                    if(score>=350){
                        SDL_RenderCopy(renderer, cherry, nullptr, &cherryRect);
                    }
                }
            }
        }

        // Dibuja al jugador en la posición actual si está en una celda azul
        if (maze[playerRect.y / CELL_SIZE][playerRect.x / CELL_SIZE] == 0) {
            SDL_RenderCopy(renderer, pacman, NULL, &playerRect);
        }
        
        // Verificar si el jugador colisionó con una moneda
    for (int i = 0; i < coins.size(); i++) {
        if (SDL_HasIntersection(&playerRect, &coins[i])) {
            // Remover la moneda de la lista y sumar puntos
            coins.erase(coins.begin() + i);
            score += 5;

        }else if (SDL_HasIntersection(&playerRect, &blueRect) || 
                  SDL_HasIntersection(&playerRect, &blackRect)|| 
                  SDL_HasIntersection(&playerRect, &xtraRect) || 
                  SDL_HasIntersection(&playerRect, &yellowRect)){
            life=2;
            
        }
    }
        SDL_Color textColor = { 255, 255, 255 }; // Color blanco para el texto
        TTF_Font* font = TTF_OpenFont("sprites/arial.ttf", 24); // Cargar una fuente de texto

        // Crear una textura para el puntaje
        std::string scoreText = "Puntaje: " + std::to_string(score);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_FreeSurface(scoreSurface);

        // Crear una textura para el nivel
        std::string levelText = "Nivel: " + std::to_string(level);
        SDL_Surface* levelSurface = TTF_RenderText_Solid(font, levelText.c_str(), textColor);
        SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
        SDL_FreeSurface(levelSurface);

        // Crear una textura para la vida
        std::string lifeText = "Vida: " + std::to_string(life);
        SDL_Surface* lifeSurface = TTF_RenderText_Solid(font, lifeText.c_str(), textColor);
        SDL_Texture* lifeTexture = SDL_CreateTextureFromSurface(renderer, lifeSurface);
        SDL_FreeSurface(lifeSurface);

        // Borrar el puntaje viejo
        SDL_Rect oldScoreRect = { SCREEN_WIDTH - 150, 10, 0, 0 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Establecer el color de relleno a negro
        SDL_RenderFillRect(renderer, &oldScoreRect);

        // Dibujar las texturas en la ventana
        SDL_Rect scoreRect = { SCREEN_WIDTH - 150, 10, 0, 0 }; // Posición del puntaje en la ventana
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);



        SDL_Rect levelRect = { SCREEN_WIDTH  - 150, 50, 0, 0 }; // Posición del nivel en la ventana
        SDL_QueryTexture(levelTexture, NULL, NULL, &levelRect.w, &levelRect.h);
        SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);

        SDL_Rect lifeRect = { SCREEN_WIDTH  - 150, 90, 0, 0 }; // Posición de la vida en la ventana
        SDL_QueryTexture(lifeTexture, NULL, NULL, &lifeRect.w, &lifeRect.h);
        SDL_RenderCopy(renderer, lifeTexture, NULL, &lifeRect);
        // Limpiar la memoria de las texturas
        SDL_DestroyTexture(scoreTexture);
        SDL_DestroyTexture(levelTexture);
        SDL_DestroyTexture(lifeTexture);

        // Cerrar la fuente
        TTF_CloseFont(font);
        SDL_RenderPresent(renderer);
    }

    // Libera la memoria de la textura del jugador
    SDL_DestroyTexture(pacman);
    SDL_DestroyTexture(blue);
    SDL_DestroyTexture(black);
    SDL_DestroyTexture(yellow);
    SDL_DestroyTexture(xtra);
    SDL_DestroyTexture(cherry);
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
