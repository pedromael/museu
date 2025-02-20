#ifndef BD_H
#define BD_H

#include "index.h"
#include "pessoa.h"
#include <sqlite3.h>

int BD_nova_pessoa(bd_pessoa dados);
bd_pessoa* BD_dados_pessoa(int id);

#endif