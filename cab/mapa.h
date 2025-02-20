#ifndef MAPA_H
#define MAPA_H
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#include "index.h"
#include "desenho.h"

int inicializar_mapa(SDL_Renderer *renderer);
int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu);

#endif
