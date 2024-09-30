#include "../cab/mapa.h" // Inclua o cabeçalho para declarações de funções e tipos

// Função para preencher a face frontal
void preencher_frente(SDL_Renderer *renderer, Point2D p1, Point2D p2, Point2D p3, Point2D p4) {
    // Definir a cor para o preenchimento (por exemplo, azul)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Encontrar os valores mínimos e máximos de Y
    int minY = min(min(p1.y, p2.y), min(p3.y, p4.y));
    int maxY = max(max(p1.y, p2.y), max(p3.y, p4.y));

    // Loop sobre as linhas entre minY e maxY para preencher a área
    for (int y = minY; y <= maxY; y++) {
        // Encontrar os pontos de interseção com essa linha
        int startX = min(min(p1.x, p2.x), min(p3.x, p4.x));
        int endX = max(max(p1.x, p2.x), max(p3.x, p4.x));

        // Desenhar a linha horizontal entre startX e endX
        SDL_RenderDrawLine(renderer, startX, y, endX, y);
    }
}

// Função para desenhar a face frontal
int desenhar_frente(SDL_Renderer *renderer, const mapa *qu, float *anguloX, float *anguloY) {
    // Definir os vértices da face frontal (vértices 0 a 3)
    Point2D pontos2D[4];
    for (int i = 0; i < 4; i++) {
        pontos2D[i] = convert_3D_2D(qu->vertices[i], anguloX, anguloY);
    }

    // Preencher a face frontal
    preencher_frente(renderer, pontos2D[0], pontos2D[1], pontos2D[2], pontos2D[3]);

    return 1;
}

// Função principal para desenhar o mapa
int desenhar_mapa(SDL_Renderer *renderer, const mapa *qu, float *anguloX, float *anguloY) {
    // Definir as arestas do cubo
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Definir a cor para as linhas do cubo (por exemplo, preto)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Desenhar as linhas do cubo
    for (int i = 0; i < 12; i++) {
        Point2D p1 = convert_3D_2D(qu->vertices[edges[i][0]], anguloX, anguloY);
        Point2D p2 = convert_3D_2D(qu->vertices[edges[i][1]], anguloX, anguloY);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    }

    // Desenhar e preencher a face frontal
    //desenhar_frente(renderer, qu, anguloX, anguloY);

    return 1;
}

// Função para inicializar o mapa com vértices do cubo
int inicializar_mapa(SDL_Renderer *renderer, float *anguloX, float *anguloY) {
    // Definir os vértices do cubo (um retângulo 3D)
    
    Point3D vertices[8] = {
        {0 - EX_M, WINDOW_HEIGHT + EX_M, 10},        // Vértice inferior esquerdo frontal
        {WINDOW_WIDTH + EX_M, WINDOW_HEIGHT + EX_M, 10},      // Vértice inferior direito frontal
        {WINDOW_WIDTH + EX_M, 0 - EX_M, 10},         // Vértice superior direito frontal
        {0 - EX_M, 0 - EX_M, 10},                    // Vértice superior esquerdo frontal
        {0 - EX_M, WINDOW_HEIGHT + EX_M, 20},       // Vértice inferior esquerdo traseiro
        {WINDOW_WIDTH + EX_M, WINDOW_HEIGHT + EX_M, 20},     // Vértice inferior direito traseiro
        {WINDOW_WIDTH + EX_M, 0 - EX_M, 20},        // Vértice superior direito traseiro
        {0 - EX_M, 0 - EX_M, 20}                    // Vértice superior esquerdo traseiro
    };

    // Criar a estrutura do mapa
    mapa meu_mapa;
    for (int i = 0; i < 8; i++) {
        meu_mapa.vertices[i] = vertices[i];
    }

    // Desenhar o mapa
    if (desenhar_mapa(renderer, &meu_mapa, anguloX, anguloY)) {
        return 1;
    }

    return 0;
}
