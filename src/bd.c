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
int BD_nova_pessoa(bd_pessoa dados)
{
    if(!conectar_BD());
        printf("nao foi possivel conectar ao banco de dados");

    char *erro;
    const char *sql = "CREATE TABLE IF NOT EXISTS usuarios(id INT, nome TEXT,genero INT, id_pai INT, id_mae INT, nacionalidade TEXT, cor INT);";
    int ver = sqlite3_exec(conectar_BD(), sql, 0, 0, &erro);
    
    if(ver != SQLITE_OK)
        return 0;

    sql = "INSERT INTO usuarios(id,nome,genero,id_pai,id_mae,nacionalidade,cor) VALUES()";
    return 1;
}

bd_pessoa BD_dados_pessoas(int id)
{
    bd_pessoa dados;
    
    return dados;
}