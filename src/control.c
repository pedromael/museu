#include "../cab/control.h"  // Inclua o cabeçalho para a declaração da função

// Função para processar eventos e atualizar a posição do quadrado
int control() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    anguloX -= ROTATION_SPEED; // Gira ao redor do eixo X
                    break;
                case SDLK_DOWN:
                    anguloX += ROTATION_SPEED;
                    break;
                case SDLK_LEFT:
                    anguloY -= ROTATION_SPEED; // Gira ao redor do eixo Y
                    break;
                case SDLK_RIGHT:
                    anguloY += ROTATION_SPEED;
                    break;
            }
        }
    }
    return 1;
}
