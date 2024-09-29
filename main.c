#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cab/control.h"
#include "cab/desenho.h"
#include "cab/mapa.h"
#include "cab/pessoa.h"
#include "cab/accoes.h"
#include "cab/bd.h"

float anguloX = 0.0f;
float anguloY = 0.0f;

int main(int argc, char* argv[]) {
    srand(time(NULL));

    SDL_Window* window = SDL_CreateWindow("MUSEU",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Inicialize as pessoas com direções e velocidades aleatórias
    int total_pessoas = 0;
    int capacidade = 10; // Capacidade inicial
    int populacao_inicial = 20;

    // Aloca memória dinamicamente para o array de pessoas
    pessoa *pessoas = malloc(capacidade * sizeof(pessoa));
    if (pessoas == NULL) return 1;

    for (int i = 0; i < populacao_inicial; i++) {
        total_pessoas++;
        if (total_pessoas >= capacidade) {
            capacidade *= 2; // Aumenta a capacidade
            pessoas = realloc(pessoas, capacidade * sizeof(pessoa));
            if (pessoas == NULL)
                return 1; 
        }
        actualizar_rotina(&pessoas[total_pessoas], &total_pessoas, pessoas,&capacidade,1);
    }

    // Variável para controlar a frequência da mudança de direção
    const int freqMudancaDirecao = 1; // Alterar a direção a cada X atualizações
    int contadorMudancaDirecao = 0;
    printf("inicio: 1\n");
    
    while (1) {
        // Processar eventos
        control(&anguloX,&anguloY);
    
        // Limpe a tela
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if(!inicializar_mapa(renderer,&anguloX,&anguloY)){
            printf("mapa nao inicializado");
            return 1;
        }
        //for (int i = 0; i < 6; i++)
        //    desenhar_mapa(renderer,&map[i]);

        contadorMudancaDirecao++;
        if (contadorMudancaDirecao >= freqMudancaDirecao) {
            for (int i = 0; i < populacao_inicial; i++){
                //printf("passou");
                actualizar_rotina(&pessoas[i], &total_pessoas,pessoas,&capacidade,0); // Atualiza direção aleatória
                atualizar_pessoa(&pessoas[i],NULL,6);
                desenhar_pessoa(renderer, &pessoas[i]);
            }
            contadorMudancaDirecao = 0;
            //printf("%d - esta no %d-%d indo a %d-%d \n",pes[i].id,pes[i].x,pes[i].y,pes[i].dx,pes[i].dy);
        }else{
            // Atualize e desenhe as pessoas
            for (int i = 0; i < total_pessoas; i++) {
                atualizar_pessoa(&pessoas[i],NULL,6);
                desenhar_pessoa(renderer, &pessoas[i]);
            }
        }

        // Apresente o renderer
        SDL_RenderPresent(renderer);
        SDL_Delay(16*2); // Aproximadamente 60 FPS
    }

    // Libere recursos e feche a SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
