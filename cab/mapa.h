#ifndef MAPA_H
#define MAPA_H

#include <SDL2/SDL.h>
#define WINDOW_WIDTH 700//1400
#define WINDOW_HEIGHT 500//900
typedef struct
{
    int x,y,z;
    int tx,ty; //tamanho
    int habitavel;
    int cor;
} mapa;

int inicializar_mapa();
int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu);

#endif
