#include "../cab/control.h"  // Inclua o cabeçalho para a declaração da função

// Função para processar eventos e atualizar a posição do quadrado
int control(SDL_Rect *square) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;  // Retorna 0 se o evento de fechamento da janela for detectado
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_w) square->y -= 10;
            if (event.key.keysym.sym == SDLK_s) square->y += 10;
            if (event.key.keysym.sym == SDLK_a) square->x -= 10;
            if (event.key.keysym.sym == SDLK_d) square->x += 10;
        }
    }
    return 1;  // Retorna 1 para continuar o loop
}
