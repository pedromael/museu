#ifndef PESSOA_H
#define PESSOA_H

#include "index.h"
#include "mapa.h"
#include "bd.h"

char* criar_nome();
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p);
void actualizar_rotina(pessoa *p, int actualizacao_completa);
void atualizar_pessoa(pessoa *p,mapa map[], int num_mapas);

#endif // PESSOA_H
