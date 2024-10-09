#ifndef VERIFICACOES_H
#define VERIFICACOES_H

#include "pessoa.h"

//extern pessoa *pessoas;
int verificar_habitabilidade(int x, int y, mapa *mapas, int num_mapas);
int verificar_pessoa_a_volta(pessoa *pessoa1);
int verificar_se_familia(pessoa *p1, pessoa *p2, int grau_maximo);

#endif