#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "mapa.h"

// Definição da estrutura pessoa
typedef struct {
    int x, y;
    int tamanho;
    int idade;
    int filiacao[2];
    int genero;
    int solteiro;
    int nacionalidade;
    int velocidade;
    Uint8 cor;  // Usar Uint8 para cor já que você tem um único valor de cor
    int dx, dy;
    int id;
} pessoa;

// Função para desenhar uma pessoa
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p);
void actualizar_rotina(pessoa *p, int *total_pessoas,pessoa *pessoas[],int *capacidade);
void atualizar_pessoa(pessoa *p,mapa map[], int num_mapas);

void verificar_pessoa_a_volta(pessoa *pessoa1, pessoa *pessoas[], int *total_pessoas, int *capacidade);

#endif // PESSOA_H
