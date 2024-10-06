#ifndef BD_H
#define BD_H

#include <stdio.h>
#include <sqlite3.h>
#include "pessoa.h"

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

extern int total_pessoas;
int BD_nova_pessoa(bd_pessoa dados);
bd_pessoa* BD_dados_pessoa(int id);

#endif