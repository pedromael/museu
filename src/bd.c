#include "../cab/bd.h"

int conectar_BD(sqlite3 **conn)
{
    const char *indereco_de_arquivo = "bancoDeDados.db";
    int ver = sqlite3_open(indereco_de_arquivo,conn);
    if (ver != SQLITE_OK) return 0;
    return 1;
}

int BD_nova_pessoa(bd_pessoa dados)
{
    sqlite3 *conn;

    if(!conectar_BD(&conn))
        printf("nao foi possivel conectar ao banco de dados\n");

    char *erro;
    const char *sql = "CREATE TABLE IF NOT EXISTS usuarios(id INT, nome TEXT,genero INT, id_pai INT, id_mae INT, nacionalidade TEXT, cor INT,x INT, y INT);";
    int ver = sqlite3_exec(conn, sql, 0, 0, &erro);
    
    if(ver != SQLITE_OK){
        printf("falha na execucao do codigo sql %s\n", erro);
        return 0;
    }
        
    sql = "INSERT INTO usuarios(id,nome,genero,id_pai,id_mae,nacionalidade,cor,x,y) VALUES(?,?,?,?,?,?,?,?,?);";
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
    sqlite3_bind_int(stmt, 8, dados.x);
    sqlite3_bind_int(stmt, 9, dados.y);

    ver = sqlite3_step(stmt);
    if (ver != SQLITE_DONE) return 0;
    capacidade = total_pessoas;
    sqlite3_finalize(stmt);
    sqlite3_close(conn);

    return 1;
}

bd_pessoa* BD_dados_pessoa(int id)
{
    int capacidade_dados = 2;
    bd_pessoa *dados = malloc(capacidade_dados * sizeof(bd_pessoa));
    sqlite3 *conn;
    sqlite3_stmt *stmt;
    const char *sql;
    
    if(!conectar_BD(&conn))
        printf("Falha ao conectar ao banco de dados\n");

    if(id != 0) 
        sql = "SELECT * FROM usuarios WHERE id = ?;";
    else
        sql = "SELECT * FROM usuarios;";

    int rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Falha ao preparar a consulta: %s\n", sqlite3_errmsg(conn));
        sqlite3_close(conn);
        return dados; // Retorna dados vazios
    }

    if (id != 0){
        sqlite3_bind_int(stmt, 1, id);

        // Caso tenha um ID, espera-se apenas um resultado
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            dados[0].id = sqlite3_column_int(stmt, 0);
            strcpy(dados[0].nome, (const char*)sqlite3_column_text(stmt, 1));
            dados[0].genero = sqlite3_column_int(stmt, 2);          
            dados[0].id_pai = sqlite3_column_int(stmt, 3);
            dados[0].id_mae = sqlite3_column_int(stmt, 4);
            strcpy(dados[0].nacionalidade, (const char*)sqlite3_column_text(stmt, 5));
            dados[0].cor = sqlite3_column_int(stmt, 6);
            dados[0].x = sqlite3_column_int(stmt, 7);
            dados[0].y = sqlite3_column_int(stmt, 8);
        } else {
            printf("Nenhum registro encontrado\n");
        }
    } else {
        int i = 0;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            if (i >= capacidade_dados)
            {
                capacidade_dados *= 2;
                dados = realloc(dados, capacidade_dados * sizeof(bd_pessoa));
            }
            
            // Processar os dados de cada linha aqui
            dados[i].id = sqlite3_column_int(stmt, 0);
            strcpy(dados[i].nome, (const char*)sqlite3_column_text(stmt, 1));
            dados[i].genero = sqlite3_column_int(stmt, 2);          
            dados[i].id_pai = sqlite3_column_int(stmt, 3);
            dados[i].id_mae = sqlite3_column_int(stmt, 4);
            strcpy(dados[i].nacionalidade, (const char*)sqlite3_column_text(stmt, 5));
            dados[i].cor = sqlite3_column_int(stmt, 6);
            dados[i].x = sqlite3_column_int(stmt, 7);
            dados[i].y = sqlite3_column_int(stmt, 8);

            i++;
        }
        total_pessoas = --i;
    }

    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        printf("Erro ao realizar o SELECT: %s\n", sqlite3_errmsg(conn));
        if (id == 0)
        {
            total_pessoas = 0;
        }
        
    }

    sqlite3_finalize(stmt);
    sqlite3_close(conn);

    return dados;
}
