#ifndef ACCOES_H
#define ACCOES_H

#include <stdio.h>
#include <string.h>
#include "bd.h"

void interagir(pessoa *pessoa1, int p2, pessoa *pessoas, int *total_pessoas, int *capacidade);
void criar_nova_pessoa(pessoa *pai, int mae, pessoa *pessoas, int *total_pessoas, int *capacidade);
int calcular_probablidade(int percentagem);

#endif //ACCOES_H