#ifndef MAPA_H
#define MAPA_H

#include "desenho.h"

typedef struct
{ 
    int x,y,z;
    Point3D vertices[8];
    int tx,ty,tz;
    int habitavel;
    int cor;
} mapa;

int inicializar_mapa(SDL_Renderer *renderer, float *anguloX, float *anguloY);
int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu, float *anguloX, float *anguloY);

#endif
