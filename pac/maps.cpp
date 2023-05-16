#include <cstdlib>
#include <iostream>
#include <ctime> // necesario para obtener una semilla aleatoria

int  **SelectMap(void){
    int maze1[12][12] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int maze2[12][12] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int maze3[12][12] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int maze4[12][12] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int maze5[12][12] = { //12 x 12
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
    int **maze;
    // establecemos la semilla aleatoria
   std::srand(std::time(nullptr));
   // generamos un número aleatorio entre 0 y 4 (ambos incluidos)
   int random = std::rand() % 5;
   // sumamos 1 para obtener un número aleatorio entre 1 y 5 (ambos incluidos)
   random += 1;
    //printf("%d",random);
    std::cout << "Número aleatorio entre 1 y 5: " << random << std::endl;
    if(random==1){
        // Copiar la matriz original a la matriz copia
           maze = new int *[12];
        for (int i = 0; i < 12; i++) {
             maze[i] = new int[12];
            for (int j = 0; j < 12; j++) {
                maze[i][j] = maze1[i][j];
    }}
    }else if(random==2){
         // Copiar la matriz original a la matriz copia
           maze = new int *[12];
        for (int i = 0; i < 12; i++) {
             maze[i] = new int[12];
            for (int j = 0; j < 12; j++) {
                maze[i][j] = maze2[i][j];
    }}
    }else if(random==3){
         // Copiar la matriz original a la matriz copia
           maze = new int *[12];
        for (int i = 0; i < 12; i++) {
             maze[i] = new int[12];
            for (int j = 0; j < 12; j++) {
                maze[i][j] = maze3[i][j];
    }}
    }else if(random==4){
          // Copiar la matriz original a la matriz copia
           maze = new int *[12];
        for (int i = 0; i < 12; i++) {
             maze[i] = new int[12];
            for (int j = 0; j < 12; j++) {
                maze[i][j] = maze4[i][j];
    }}
    }else if(random==5){
          // Copiar la matriz original a la matriz copia
           maze = new int *[12];
        for (int i = 0; i < 12; i++) {
             maze[i] = new int[12];
            for (int j = 0; j < 12; j++) {
                maze[i][j] = maze5[i][j];
    }}
    };
   return maze;
}
/*
int main(){
    int** maze=SelectMap();
    // Imprimir matriz
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%d",maze[i][j],"");
        }
        printf("\n");
    }

    return 0;

}
*/