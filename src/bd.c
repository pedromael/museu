#include "../cab/bd.h"

sqlite3* conectar_BD()
{
    sqlite3 *conn;
    const char *indereco_de_arquivo = "bancoDeDados.db";
    int ver = sqlite3_open(indereco_de_arquivo,&conn);
    if (ver != SQLITE_OK)
        return 0;
    return conn;
}
int BD_nova_pessoa()
{
    if(conectar_BD());
        printf("nova pessoa adicionada");
    return 1;
}