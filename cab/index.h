#ifndef INDEX_H
#define INDEX_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void criar_pessoa(int pai, int mae)

#define NUMERO_DE_PESSOAS_INICIAIS 5;

// Definição da estrutura pessoa
typedef struct {
    int x, y, z;
    Point3D vertices[8];
    int tamanho;
    int velocidade;
    int dx, dy, dz;
    Uint8 cor;
    int id, id_pai, id_mae;
} pessoa;

typedef struct
{ 
    int x,y,z;
    Point3D vertices[8];
    int tx,ty,tz;
    int habitavel;
    int cor;
} mapa;

typedef struct 
{
    int id;
    int genero;
    char nome[25];
    char nacionalidade[15];
    int cor;
    int id_pai,id_mae;
    int x,y;
} bd_pessoa;

typedef struct
{
    int x,y;
} Point2D;

typedef struct
{
    float x,y,z;
} Point3D;

extern int numero_pessoas;
extern int capacidade_pessoas;
extern pessoa *pessoas;
extern float anguloX;
extern float anguloY;

#endif