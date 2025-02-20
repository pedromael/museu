int numero_pessoas = 0;
int capacidade_pessoas = 10; 
float anguloX = -0.3f;
float anguloY = 0.3f;
pessoa *pessoas;

#include "cab/index.h"
#include "cab/verificacoes.h"
#include "cab/control.h"
#include "cab/desenho.h"
#include "cab/mapa.h"
#include "cab/pessoa.h"
#include "cab/accoes.h"
#include "cab/bd.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    SDL_Window* window = SDL_CreateWindow("MUSEU",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    pessoas = malloc(capacidade_pessoas * sizeof(pessoa));

    BD_dados_pessoa(0); // verificar se existe pessoa na BD: modifica a variavel numeros_pessoas com numero de usuarios encontrados

    bd_pessoa dados;
    for(size_t i = 0; i < numero_pessoas; i++){
        if(i >= capacidade_pessoas){
            capacidade_pessoas *= 2;
            pessoas = realloc(pessoas, capacidade_pessoas * sizeof(pessoa));
        }
        dados = BD_dados_pessoa(0)[i];
        pessoas[i].x = dados.x;
        pessoas[i].y = dados.y;
        pessoas[i].id = dados.id;
        pessoas[i].id_pai = dados.id_pai;
        pessoas[i].id_mae = dados.id_mae;
        actualizar_rotina(&pessoas[i],2);
    }

    free(dados);

    if (pessoas == NULL) return 1;

    populacao_inicial += numero_pessoas;
    int ii = numero_pessoas;
    for (int i = ii; i < NUMERO_DE_PESSOAIS_INICIAIS; i++) {
        numero_pessoas++;
        if (numero_pessoas >= capacidade) {
            capacidade *= 2; // Aumenta a capacidade
            pessoas = realloc(pessoas, capacidade * sizeof(pessoa));
            if (pessoas == NULL)
                return 1; 
        }
        actualizar_rotina(&pessoas[numero_pessoas],1);
    }

    // Variável para controlar a frequência da mudança de direção
    const int freqMudancaDirecao = 75; // Alterar a direção a cada X atualizações
    int contadorMudancaDirecao = 0;
    printf("inicio: 1\n");
    
    while (1) {
        // Processar eventos
        //printf("entrou em loop principal\n");
        if(!control()) break;
        control();
        // Limpe a tela
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if(!inicializar_mapa(renderer)){
            printf("mapa nao inicializado");
            return 1;
        }
        //for (int i = 0; i < 6; i++)
        //    desenhar_mapa(renderer,&map[i]);

        contadorMudancaDirecao++;
        if (contadorMudancaDirecao >= freqMudancaDirecao) {
            for (int i = 0; i < numero_pessoas; i++){
                //printf("passou");
                actualizar_rotina(&pessoas[i],0); // Atualiza direção aleatória
                atualizar_pessoa(&pessoas[i],NULL,6);
                desenhar_pessoa(renderer, &pessoas[i]);
            }
            contadorMudancaDirecao = 0;
            //printf("%d - esta no %d-%d indo a %d-%d \n",pes[i].id,pes[i].x,pes[i].y,pes[i].dx,pes[i].dy);
        }else{
            // Atualize e desenhe as pessoas
            for (int i = 0; i < numero_pessoas; i++) {
                atualizar_pessoa(&pessoas[i],NULL,6);
                desenhar_pessoa(renderer, &pessoas[i]);
            }
        }

        // Apresente o renderer
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // Libere recursos e feche a SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
