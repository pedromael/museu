#include "../cab/accoes.h"

int calcular_probablidade(int percentagem){
    int perc = rand()%101;
    if(percentagem <= perc) return 1;
    return 0;
}
void criar_nova_pessoa(pessoa *pai, int mae, pessoa *pessoas, int *total_pessoas, int *capacidade) {
    if (pai->genero != pessoas[mae].genero) { // Verifica se os gêneros são opostos
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
        filho->cor = (Uint8)(rand() % 256); // Cor aleatória
        filho->filiacao[0] = pai->id; // Armazena ID do pai
        filho->filiacao[1] = pessoas[mae].id; // Armazena ID da mãe
        filho->genero = rand() % 2; // Gênero aleatório para o filho
        filho->idade = 0; // Idade inicial do filho
        printf("criado: %d por %d e %d\n", *total_pessoas,pai->id,pessoas[mae].id);
    }
}

void interagir(pessoa *pessoa1, int p2, pessoa *pessoas, int *total_pessoas, int *capacidade) {
    if (calcular_probablidade(25)) {
        //printf("Usuário: %d em x-%d e y-%d acionou %d em x-%d e y-%d\n", pessoa1->id, pessoa1->x, pessoa1->y, pessoas[p2].id, pessoas[p2].x, pessoas[p2].y);
        criar_nova_pessoa(pessoa1, p2, pessoas, total_pessoas, capacidade);
    }
}
