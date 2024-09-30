#ifndef DESENHO_H
#define DESENHO_H

#define WINDOW_WIDTH 1400//1400
#define WINDOW_HEIGHT 900//900
#define PROFUNDIDADE 750
#define ROTATION_SPEED 0.005f
#define EX_M 500 // expansao do mapa sobre o tamanho da telas

#include <SDL2/SDL.h>
#include <math.h>

typedef struct
{
    int x,y;
} Point2D;

typedef struct
{
    float x,y,z;
} Point3D;

Point2D convert_3D_2D(Point3D p, float *anguloX, float *anguloY);

#endif