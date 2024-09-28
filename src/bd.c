#include "../cab/bd.h"

 conectar_BD(sqlite3 **conn)
{
    const char *indereco_de_arquivo = "bancoDeDados.db";
    int ver = sqlite3_open(indereco_de_arquivo,conn);
    if (ver != SQLITE_OK)
        return 0;
    return 1;
}
int BD_nova_pessoa(bd_pessoa dados)
{
    sqlite3 *conn;

    if(!conectar_BD(&conn))
        printf("nao foi possivel conectar ao banco de dados\n");

    char *erro;
    const char *sql = "CREATE TABLE IF NOT EXISTS usuarios(id INT, nome TEXT,genero INT, id_pai INT, id_mae INT, nacionalidade TEXT, cor INT);";
    int ver = sqlite3_exec(conn, sql, 0, 0, erro);
    
    if(ver != SQLITE_OK){
        printf("falha na execucao do codigo sql %s\n", erro);
        return 0;
    }
        
    sql = "INSERT INTO usuarios(id,nome,genero,id_pai,id_mae,nacionalidade,cor) VALUES(?,?,?,?,?,?,?);";
    sqlite3_stmt *stmt;
    ver = sqlite3_prepare_v2(conn, sql, -1, &stmt, 0);
    if(ver != SQLITE_OK) {
        printf("Falha na preparação da declaração SQL: %s\n", sqlite3_errmsg(conn));
        sqlite3_close(conn);
        return 0;
    }

    // Bind de dados
    sqlite3_bind_int(stmt, 1, dados.id);
    sqlite3_bind_text(stmt, 2, dados.nome, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, dados.genero);
    sqlite3_bind_int(stmt, 4, dados.id_pai);
    sqlite3_bind_int(stmt, 5, dados.id_mae);
    sqlite3_bind_text(stmt, 6, dados.nacionalidade, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, dados.cor);

    return 1;
}

bd_pessoa BD_dados_pessoa(int id)
{
    bd_pessoa dados;

    return dados;
}