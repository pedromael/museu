#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include "mapa.h"
#include "bd.h"

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


extern float anguloX;
extern float anguloY;
extern int total_pessoas;
extern int capacidade;
extern pessoa *pessoas;

char* criar_nome();
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p);
void actualizar_rotina(pessoa *p, int actualizacao_completa);
void atualizar_pessoa(pessoa *p,mapa map[], int num_mapas);

#endif // PESSOA_H
