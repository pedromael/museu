#include "../cab/accoes.h"

int calcular_probablidade(int percentagem){
    int perc = rand()%101;
    if(percentagem <= perc) return 1;
    return 0;
}
void criar_nova_pessoa(pessoa *pai, int mae) {

    if (BD_dados_pessoa(pai->id)[0].genero != BD_dados_pessoa(mae)[0].genero) { // Verifica se os gêneros são opostos
        if (total_pessoas >= capacidade) {
            capacidade *= 2;
            pessoas = realloc(pessoas, capacidade * sizeof(pessoa));
            //if (*pessoas == NULL) return 1;
        }
        total_pessoas += 1;
        pessoa *filho = &(pessoas)[total_pessoas]; // Ponteiro para a nova pessoa

        filho->id = total_pessoas; // Atribui um ID
        filho->x = (pai->x + pessoas[mae].x) / 2; // Posição média dos pais
        filho->y = (pai->y + pessoas[mae].y) / 2; // Posição média dos pais
        filho->tamanho = 4; // Tamanho padrão
        filho->cor = (Uint8)100;
        filho->dx = (calcular_probablidade(50)) ? -1 : 1; // Direção aleatória entre -1 e 1
        filho->dy = (calcular_probablidade(50)) ? -1 : 1;
        filho->velocidade = rand() % 2;
        filho->id_pai = pai->id;
        filho->id_mae = pessoas[mae].id;
        bd_pessoa dado;

        dado.id = total_pessoas;
        dado.genero = calcular_probablidade(45); 
        strcpy(dado.nome, criar_nome());
        dado.cor = (Uint8)255;
        dado.id_pai = pai->id;
        dado.id_mae = pessoas[mae].id;
        strcpy(dado.nacionalidade, "angola");

        BD_nova_pessoa(dado);

        //printf("criado: %d por %d e %d\n", pessoas[total_pessoas].id,pai->id,pessoas[mae].id);
    }
}

void interagir(pessoa *pessoa1, int p2) {
    if (calcular_probablidade(5) && verificar_se_familia(pessoa1,&pessoas[p2],7) > 6) {
        printf("%d\n",verificar_se_familia(pessoa1,&pessoas[p2],7));
        criar_nova_pessoa(pessoa1, p2);
    }
    printf("%d\n",verificar_se_familia(pessoa1,&pessoas[p2],7));
}
