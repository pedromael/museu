#include "../cab/mapa.h" // Inclua o cabeçalho para declarações de funções e tipos

int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu, float *anguloX, float *anguloY) {

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    if(qu->habitavel) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);     
    
    for (int i = 0; i < 12; i++)
    {
        Point2D p1 = convert_3D_2D(qu->vertices[edges[i][0]],anguloX,anguloY);
        Point2D p2 = convert_3D_2D(qu->vertices[edges[i][1]],anguloX,anguloY);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y );
    }
    
    return 1;
}

// Função para inicializar o mapa
int inicializar_mapa(SDL_Renderer *renderer, float *anguloX, float *anguloY) {
    Point3D vertices[8] = {
        {0, WINDOW_HEIGHT, 6},        // Vértice inferior esquerdo frontal
        {WINDOW_WIDTH, WINDOW_HEIGHT, 6},      // Vértice inferior direito frontal
        {WINDOW_WIDTH, 0, 6},         // Vértice superior direito frontal
        {0, 0, 6},                    // Vértice superior esquerdo frontal
        {0, WINDOW_HEIGHT, 10},       // Vértice inferior esquerdo traseiro
        {WINDOW_WIDTH, WINDOW_HEIGHT, 10},     // Vértice inferior direito traseiro
        {WINDOW_WIDTH, 0, 10},        // Vértice superior direito traseiro
        {0, 0, 10}                    // Vértice superior esquerdo traseiro
    };

    mapa meu_mapa;
    for (int i = 0; i < 8; i++)
        meu_mapa.vertices[i] = vertices[i];

    if(desenhar_mapa(renderer,&meu_mapa,anguloX,anguloY))
        return 1;
    return 0;
}
