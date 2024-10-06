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
    int id;
} pessoa;


extern float anguloX;
extern float anguloY;
extern int total_pessoas;
extern int capacidade;

char* criar_nome();
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p);
void actualizar_rotina(pessoa *p,pessoa *pessoas, int actualizacao_completa);
void atualizar_pessoa(pessoa *p,mapa map[], int num_mapas);
void verificar_pessoa_a_volta(pessoa *pessoa1, pessoa *pessoas);

#endif // PESSOA_H
