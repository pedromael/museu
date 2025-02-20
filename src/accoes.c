#include "../cab/accoes.h"

int calcular_probablidade(int percentagem){
    int perc = rand()%101;
    if(percentagem <= perc) return 1;
    return 0;
}

void interagir(int p1, int p2) {
    if (calcular_probablidade(5) && verificar_se_familia(&pessoas[p1],&pessoas[p2],7) > 6) {
        printf("%d\n",verificar_se_familia(&pessoas[p1],&pessoas[p2],7));
        criar_pessoa(p1, p2);
    }
    
    printf("%d\n",verificar_se_familia(&pessoas[p1],&pessoas[p2],7));
}
