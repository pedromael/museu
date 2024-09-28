#include "../cab/accoes.h"

int calcular_probablidade(int percentagem){
    int perc = rand()%101;
    if(percentagem <= perc) return 1;
    return 0;
}
void criar_nova_pessoa(pessoa *pai, int mae, pessoa *pessoas, int *total_pessoas, int *capacidade) {

    if (BD_dados_pessoa(pai->id).genero != BD_dados_pessoa(mae).genero) { // Verifica se os gêneros são opostos
        if (*total_pessoas >= *capacidade) {
            *capacidade *= 2;
            pessoas = realloc(pessoas, *capacidade * sizeof(pessoa));
            //if (*pessoas == NULL) return 1;
        }
        *total_pessoas += 1;
        pessoa *filho = &(pessoas)[*total_pessoas]; // Ponteiro para a nova pessoa

        filho->id = *total_pessoas; // Atribui um ID
        filho->x = (pai->x + pessoas[mae].x) / 2; // Posição média dos pais
        filho->y = (pai->y + pessoas[mae].y) / 2; // Posição média dos pais
        filho->tamanho = 4; // Tamanho padrão
        filho->cor = (Uint8)100; // Cor aleatória

        bd_pessoa dado;

        dado.id = *total_pessoas;
        dado.genero = calcular_probablidade(45); 
        strcpy(dado.nome, criar_nome());
        dado.cor = (Uint8)255;
        dado.id_pai = 0;
        dado.id_mae = 0;
        strcpy(dado.nacionalidade, "angola");

        BD_nova_pessoa(dado);

        printf("criado: %d por %d e %d\n", *total_pessoas,pai->id,pessoas[mae].id);
    }
}

void interagir(pessoa *pessoa1, int p2, pessoa *pessoas, int *total_pessoas, int *capacidade) {
    if (calcular_probablidade(25)) {
        //printf("Usuário: %d em x-%d e y-%d acionou %d em x-%d e y-%d\n", pessoa1->id, pessoa1->x, pessoa1->y, pessoas[p2].id, pessoas[p2].x, pessoas[p2].y);
        criar_nova_pessoa(pessoa1, p2, pessoas, total_pessoas, capacidade);
    }
}
