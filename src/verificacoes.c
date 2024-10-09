#include "../cab/verificacoes.h"

// Verifica se uma área é habitável
int verificar_habitabilidade(int x, int y, mapa *mapas, int num_mapas) {
    //parada devido a mudanca no mapa
    return 1;

    for (int i = 0; i < num_mapas; i++) {
        mapa *m = &mapas[i];
        if (!m->habitavel) // Verifica se a área é não habitável
            if (x >= m->x && x < m->x + m->tx && y >= m->y && y < m->y + m->ty)
                return 0;
    }
    return 1;
}

// Verifica se há pessoas próximas
int verificar_pessoa_a_volta(pessoa *pessoa1) {
    int raio = 7;
    //printf("verificacao de pessoa a volta:");
    for (int i = 0; i < total_pessoas; i++) {
        if (pessoas[i].id != pessoa1->id) {
            int diffX = (pessoa1->x - pessoas[i].x);
            int diffY = (pessoa1->y - pessoas[i].y);
            diffX = (diffX < 0)? diffX * -1 : diffX;
            diffY = (diffY < 0)? diffY * -1 : diffY;
            if (diffX <= raio && diffY <= raio) {
                printf("raio %d-%d\n", diffX,diffY);
                return i;
                break;
            }
        }
    }
    return 0;
}

// Função auxiliar para buscar o id do ancestral em um determinado grau
int buscar_ancestral(int id, int grau) {
    if (grau == 0 || id == 0) {
        return id;
    }

    bd_pessoa *dados = BD_dados_pessoa(id);
    if (dados == NULL) {
        return 0; // Ancestral não encontrado ou erro ao buscar
    }

    int id_pai = buscar_ancestral(dados[0].id_pai, grau - 1);
    if (id_pai != 0) {
        free(dados); // Libera a memória alocada
        return id_pai;
    }

    int id_mae = buscar_ancestral(dados[0].id_mae, grau - 1);
    free(dados); // Libera a memória alocada

    return id_mae;
}

// Função auxiliar para buscar pai ou mãe de uma pessoa

int verificar_se_familia(pessoa *p1, pessoa *p2, int grau_maximo) {

    if((p1->id_pai + p1->id_mae + p2->id_pai + p2->id_mae) == 0){
        return 10;
    }

    if ((p1->id_pai != 0 && p1->id_pai == p2->id_pai) || (p1->id_mae != 0 && p1->id_mae == p2->id_mae)) {
        return 2; // São irmãos
    }

    int id_p2_pai_pai = pessoas[p2->id_pai - 1].id_pai;
    int id_p2_pai_mae = pessoas[p2->id_pai - 1].id_mae;
    int id_p2_mae_pai = pessoas[p2->id_mae - 1].id_pai;
    int id_p2_mae_mae = pessoas[p2->id_mae - 1].id_mae;

    if ((id_p2_pai_pai != 0 && buscar_ancestral(p1->id, 1) == id_p2_pai_pai) ||
        (id_p2_pai_mae != 0 && buscar_ancestral(p1->id, 1) == id_p2_pai_mae) ||
        (id_p2_mae_pai != 0 && buscar_ancestral(p1->id, 1) == id_p2_mae_pai) ||
        (id_p2_mae_mae != 0 && buscar_ancestral(p1->id, 1) == id_p2_mae_mae)) {
        return 3; // p1 é tia de p2
    }

    // Verifica se p2 é tia de p1 (grau 3, simetria)
    int id_p1_pai_pai = pessoas[p1->id_pai - 1].id_pai;
    int id_p1_pai_mae = pessoas[p1->id_pai - 1].id_mae;
    int id_p1_mae_pai = pessoas[p1->id_mae - 1].id_pai;
    int id_p1_mae_mae = pessoas[p1->id_mae - 1].id_mae;

    if ((id_p1_pai_pai != 0 && buscar_ancestral(p2->id, 1) == id_p1_pai_pai) ||
        (id_p1_pai_mae != 0 && buscar_ancestral(p2->id, 1) == id_p1_pai_mae) ||
        (id_p1_mae_pai != 0 && buscar_ancestral(p2->id, 1) == id_p1_mae_pai) ||
        (id_p1_mae_mae != 0 && buscar_ancestral(p2->id, 1) == id_p1_mae_mae)) {
        return 3; // p2 é tia de p1
    }

    // Verifica outros graus de parentesco
    for (int grau = 1; grau <= grau_maximo; grau++) {
        int ancestral_p1 = buscar_ancestral(p1->id, grau);
        int ancestral_p2 = buscar_ancestral(p2->id, grau);

        // Se encontrarmos um ancestral comum, então são parentes
        if (ancestral_p1 != 0 && ancestral_p1 == ancestral_p2) {
            return grau;
        }
    }

    return 0;
}



