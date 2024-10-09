#ifndef ACCOES_H
#define ACCOES_H

#include <string.h>
#include "pessoa.h"
#include "bd.h"
#include "verificacoes.h"

void interagir(pessoa *pessoa1, int p2);
void criar_nova_pessoa(pessoa *pai, int mae);
int calcular_probablidade(int percentagem);

#endif //ACCOES_H