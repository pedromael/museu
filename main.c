#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cab/control.h"
#include "cab/mapa.h"
#include "cab/pessoa.h"
#include "cab/accoes.h"

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
    int capacidade = 50; // Capacidade inicial
    int populacao_inicial = 230;

    // Aloca memória dinamicamente para o array de pessoas
    pessoa *pessoas = malloc(capacidade * sizeof(pessoa));
    if (pessoas == NULL) return 1;

    for (int i = 0; i < populacao_inicial; i++) {
        total_pessoas++;
        if (total_pessoas >= capacidade) {
            capacidade = populacao_inicial + 5; // Aumenta a capacidade
            pessoas = realloc(pessoas, capacidade * sizeof(pessoa));
            if (pessoas == NULL)
                return 1; 
        }
        actualizar_rotina(&pessoas[total_pessoas], &total_pessoas, &pessoas,&capacidade);
    }
    int map_info[6][5] = {
        {0,0,WINDOW_WIDTH/2-30,WINDOW_HEIGHT/2,1},
        {WINDOW_WIDTH/2-30,0,30,WINDOW_HEIGHT/2,0},
        {WINDOW_WIDTH-WINDOW_WIDTH/2,0,WINDOW_WIDTH/2,WINDOW_HEIGHT/2,1},
        {0,WINDOW_HEIGHT/2+30,WINDOW_WIDTH/2-30,WINDOW_HEIGHT/2-30,1},
        {WINDOW_WIDTH/2-30,WINDOW_HEIGHT/2+30,30,WINDOW_HEIGHT/2-30,0},
        {WINDOW_WIDTH-WINDOW_WIDTH/2,WINDOW_HEIGHT/2+30,WINDOW_WIDTH/2,WINDOW_HEIGHT/2-30,1},
    };

    mapa map[6];
        for (int i = 0; i < 6; i++) {
            map[i].x = map_info[i][0];
            map[i].y = map_info[i][1];
            map[i].tx = map_info[i][2];
            map[i].ty = map_info[i][3];
            map[i].habitavel = map_info[i][4];
        }
        

    // Variável para controlar a frequência da mudança de direção
    const int freqMudancaDirecao = 85; // Alterar a direção a cada X atualizações
    int contadorMudancaDirecao = 0;
    printf("inicio:");
    // Loop principal
    int running = 1;
    while (running) {
        // Processar eventos
        running = control(NULL);

        // Limpe a tela
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 6; i++)
            desenhar_mapa(renderer,&map[i]);
        //free(map);
        //free(map_info);
        contadorMudancaDirecao++;
        if (contadorMudancaDirecao >= freqMudancaDirecao) {
            for (int i = 0; i < populacao_inicial; i++){
                int zero = 0;
                //printf("passou");
                actualizar_rotina(&pessoas[i], &zero,&pessoas,&capacidade); // Atualiza direção aleatória
                atualizar_pessoa(&pessoas[i],map,6);
                desenhar_pessoa(renderer, &pessoas[i]);
            }
            contadorMudancaDirecao = 0;
            //printf("%d - esta no %d-%d indo a %d-%d \n",pes[i].id,pes[i].x,pes[i].y,pes[i].dx,pes[i].dy);
        }else{
            // Atualize e desenhe as pessoas
            for (int i = 0; i < total_pessoas; i++) {
                atualizar_pessoa(&pessoas[i],map,6);
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
