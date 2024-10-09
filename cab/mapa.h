#ifndef MAPA_H
#define MAPA_H
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#include "desenho.h"

typedef struct
{ 
    int x,y,z;
    Point3D vertices[8];
    int tx,ty,tz;
    int habitavel;
    int cor;
} mapa;

extern float anguloX;
extern float anguloY;
int inicializar_mapa(SDL_Renderer *renderer);
int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu);

#endif
