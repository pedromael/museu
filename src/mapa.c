#include "../cab/mapa.h" // Inclua o cabeçalho para declarações de funções e tipos

// Função para inicializar o mapa
int inicializar_mapa() {
    // Inicialização do mapa (se necessário)
    return 0;
}

int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu) {

    if(qu->habitavel) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);     
    SDL_Rect rect = { qu->x, qu->y, qu->tx, qu->ty };
    SDL_RenderFillRect(renderer, &rect);

    return 0;
}
