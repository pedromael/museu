#include <math.h>
#include "../cab/pessoa.h"
#include "../cab/mapa.h"
#include "../cab/accoes.h"

// Verifica se uma área é habitável
int verificar_habitabilidade(int x, int y, mapa *mapas, int num_mapas) {
    //parada devido a mudanca no mapa
    return 1;

    for (int i = 0; i < num_mapas; i++) {
        mapa *m = &mapas[i];
        if (!m->habitavel) // Verifica se a área é não habitável
            if (x >= m->x && x < m->x + m->tx && y >= m->y && y < m->y + m->ty)
                return 0;
    }
    return 1;
}

// Verifica se há pessoas próximas
void verificar_pessoa_a_volta(pessoa *pessoa1, pessoa *pessoas, int *total_pessoas, int *capacidade) {
    int raio = 10;
    //printf("verificacao de pessoa a volta:");
    for (int i = 0; i < *total_pessoas; i++) {
        if (i != pessoa1->id) {
            int diffX = abs(pessoa1->x - pessoas[i].x);
            int diffY = abs(pessoa1->y - pessoas[i].y);
            if (diffX <= raio && diffY <= raio) {
                interagir(pessoa1, i, pessoas, total_pessoas, capacidade);
                break;
            }
        }
    }
}

char* criar_nome()
{
    int tamanho = rand() % 11;
    if (tamanho < 4)
        tamanho = 4;
    
    char* nome = malloc((tamanho+1) * sizeof(char));
    char alfabeto[] = "bcdfghjklmnpqrstvwxyz";//21
    char vogais[] = "aeiou";//5

    int primeira_letra = rand()%2;

    for (int i = 0; i < tamanho; i++)
    {
        if ((i + primeira_letra) % 2 == 0)
        {
            if (calcular_probablidade(85)) // 85% de chance de ser verdadeiro
                nome[i] = alfabeto[rand()%21];
            else
                nome[i] = vogais[rand()%5];
        }
        else
        {
            if (calcular_probablidade(85))
                nome[i] = vogais[rand()%5];
            else
                nome[i] = alfabeto[rand()%21];
        }
        
    }
    
    return nome;    
}

// Função para desenhar uma pessoa
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p, float *anguloX, float *anguloY) {
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    SDL_Color cor = { p->cor, 100, 100, 255 }; // Exemplo, ajuste conforme necessário
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);

    for (int i = 0; i < 12; i++)
    {
        Point2D p1 = convert_3D_2D(p->vertices[edges[i][0]],anguloX,anguloY);
        Point2D p2 = convert_3D_2D(p->vertices[edges[i][1]],anguloX,anguloY);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y );
    }
}

// Atualiza a rotina de uma pessoa
void actualizar_rotina(pessoa *p, int *total_pessoas, pessoa *pessoas, int *capacidade, int actualizacao_completa) {
    p->tamanho = 4;
    p->velocidade = rand() % 2;
    if (actualizacao_completa) {

        bd_pessoa dado;

        dado.id = *total_pessoas;
        dado.genero = calcular_probablidade(45); 
        strcpy(dado.nome, criar_nome());
        dado.cor = (Uint8)255;
        dado.id_pai = 0;
        dado.id_mae = 0;
        strcpy(dado.nacionalidade, "angola");

        BD_nova_pessoa(dado);

        p->x = (rand() % (WINDOW_WIDTH / p->tamanho)) * p->tamanho;
        p->y = (rand() % (WINDOW_HEIGHT / p->tamanho)) * p->tamanho;
        Point3D vertices[8] = {
            {p->x, p->y + 4, 0},        // Vértice inferior esquerdo frontal
            {p->x + 4, p->y + 4, 0},      // Vértice inferior direito frontal
            {p->x + 4, p->y, 0},         // Vértice superior direito frontal
            {p->x, p->y , 0},                    // Vértice superior esquerdo frontal
            
            {p->x, p->y + 4, 4},       // Vértice inferior esquerdo traseiro
            {p->x + 4, p->y + 4, 4},     // Vértice inferior direito traseiro
            {p->x + 4, p->y, 4},        // Vértice superior direito traseiro
            {p->x, p->y, 4}                    // Vértice superior esquerdo traseiro
        };

        for (int i = 0; i < 8; i++)
            p->vertices[i] = vertices[i];

        p->cor = (Uint8)255;  // Cor aleatória
        p->id = *total_pessoas;
    }else verificar_pessoa_a_volta(p, pessoas, total_pessoas, capacidade);
    
    p->dx = (calcular_probablidade(50)) ? -1 : 1; // Direção aleatória entre -1 e 1
    p->dy = (calcular_probablidade(50)) ? -1 : 1;
}

// Função para atualizar a posição de uma pessoa
void atualizar_pessoa(pessoa *p, mapa mapas[], int num_mapas) {
    // Normalizar a direção
    int comprimento = sqrt(p->dx * p->dx + p->dy * p->dy);
    if (comprimento > 0) {
        p->dx /= comprimento;
        p->dy /= comprimento;
    }

    // Atualizar a posição com base na velocidade e direção
    int nova_x = p->x + p->velocidade * p->dx;
    int nova_y = p->y + p->velocidade * p->dy;

    // Verificar se a nova posição é habitável
    if (verificar_habitabilidade(nova_x, nova_y, mapas, num_mapas)) {
        p->x = nova_x;
        p->y = nova_y;
    } else {
        p->dx = (calcular_probablidade(50)) ? -1 : 1;
        p->dy = (calcular_probablidade(50)) ? -1 : 1;
    }

    // Verificar limites e ajustar posição e direção
    if (p->x < 0) { p->x = 0; p->dx = -p->dx; }
    if (p->x > WINDOW_WIDTH - p->tamanho) {
        p->x = WINDOW_WIDTH - p->tamanho;
        p->dx = -p->dx;
    }
    if (p->y < 0) { p->y = 0; p->dy = -p->dy; }
    if (p->y > WINDOW_HEIGHT - p->tamanho) {
        p->y = WINDOW_HEIGHT - p->tamanho;
        p->dy = -p->dy;
    }
}
