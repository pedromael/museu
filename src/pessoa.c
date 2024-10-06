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
void verificar_pessoa_a_volta(pessoa *pessoa1, pessoa *pessoas) {
    int raio = 10;
    //printf("verificacao de pessoa a volta:");
    for (int i = 0; i < total_pessoas; i++) {
        if (i != pessoa1->id) {
            int diffX = abs(pessoa1->x - pessoas[i].x);
            int diffY = abs(pessoa1->y - pessoas[i].y);
            if (diffX <= raio && diffY <= raio) {
                interagir(pessoa1, i, pessoas);
                break;
            }
        }
    }
}

char* criar_nome()
{
    int tamanho = rand() % 11;
    if (tamanho < 4)
        tamanho = 3;
    
    char* nome = malloc((tamanho+1) * sizeof(char));
    char alfabeto[] = "bcdfghjklmnpqrstvwxz";//20
    char alfabeto_refinado[] = "rhs";//3
    char vogais[] = "aeiouy";//6

    int primeira_letra = rand()%2;

    int i;
    for (i = 0; i < tamanho; i++)
    {
        if ((i + primeira_letra) % 2 == 0)
        {
            if (calcular_probablidade(95)) {// 95% de chance de ser verdadeiro
                nome[i] = alfabeto_refinado[rand()%3];
                if(++i < tamanho)
                    nome[i] = vogais[rand()%6];
            }else
                nome[i] = vogais[rand()%6];
        }
        else
        {
            if (calcular_probablidade(95)){
                nome[i] = vogais[rand()%6];
                if(++i < tamanho)
                    nome[i] = alfabeto[rand()%20];
            }else
                nome[i] = alfabeto[rand()%20];
        }
        
    }
    nome[i] = '\0';
    return nome;    
}

// Função para desenhar uma pessoa
void desenhar_pessoa(SDL_Renderer *renderer, const pessoa *p) {
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    SDL_Color cor = { p->cor, 100, 100, 255 }; // Exemplo, ajuste conforme necessário
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);

    for (int i = 0; i < 12; i++)
    {
        Point2D p1 = convert_3D_2D(p->vertices[edges[i][0]]);
        Point2D p2 = convert_3D_2D(p->vertices[edges[i][1]]);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y );
    }
}

// Atualiza a rotina de uma pessoa
void actualizar_rotina(pessoa *p, pessoa *pessoas, int actualizacao_completa) {
    p->tamanho = 4;
    p->velocidade = rand() % 2;
    if (actualizacao_completa) {
        p->x = (rand() % ((WINDOW_WIDTH + EX_M * 2) / p->tamanho)) * p->tamanho - EX_M;
        p->y = (rand() % ((WINDOW_HEIGHT + EX_M * 2) / p->tamanho)) * p->tamanho - EX_M;

        bd_pessoa dado;

        dado.id = total_pessoas;
        dado.genero = calcular_probablidade(45); 
        strcpy(dado.nome, criar_nome());
        dado.cor = (Uint8)255;
        dado.id_pai = 0;
        dado.id_mae = 0;
        strcpy(dado.nacionalidade, "angola");
        dado.x = p->x;
        dado.y = p->y;

        printf("id- %d nome: %s \n", total_pessoas,dado.nome);
        BD_nova_pessoa(dado);

        Point3D vertices[8] = {
            {p->x, p->y + 4, 0},        // Vértice inferior esquerdo frontal
            {p->x + 4, p->y + 4, 0},      // Vértice inferior direito frontal
            {p->x + 4, p->y, 0},         // Vértice superior direito frontal
            {p->x, p->y , 0},                    // Vértice superior esquerdo frontal
            
            {p->x, p->y + 4, 10},       // Vértice inferior esquerdo traseiro
            {p->x + 4, p->y + 4, 10},     // Vértice inferior direito traseiro
            {p->x + 4, p->y, 10},        // Vértice superior direito traseiro
            {p->x, p->y, 10}                    // Vértice superior esquerdo traseiro
        };

        for (int i = 0; i < 8; i++)
            p->vertices[i] = vertices[i];

        p->cor = (Uint8)255;  // Cor aleatória
        p->id = total_pessoas;
    }else verificar_pessoa_a_volta(p, pessoas);
    
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

        Point3D vertices[8] = {
            {p->x, p->y + 4, 0},        // Vértice inferior esquerdo frontal
            {p->x + 4, p->y + 4, 0},      // Vértice inferior direito frontal
            {p->x + 4, p->y, 0},         // Vértice superior direito frontal
            {p->x, p->y , 0},                    // Vértice superior esquerdo frontal
            
            {p->x, p->y + 4, 10},       // Vértice inferior esquerdo traseiro
            {p->x + 4, p->y + 4, 10},     // Vértice inferior direito traseiro
            {p->x + 4, p->y, 10},        // Vértice superior direito traseiro
            {p->x, p->y, 10}                    // Vértice superior esquerdo traseiro
        };

        for (int i = 0; i < 8; i++)
            p->vertices[i] = vertices[i];
            
    } else {
        p->dx = (calcular_probablidade(50)) ? -1 : 1;
        p->dy = (calcular_probablidade(50)) ? -1 : 1;
    }

    // Verificar limites e ajustar posição e direção
    if (p->x < 0 - EX_M) { p->x = 0 - EX_M; p->dx = -p->dx; }
    if (p->x > WINDOW_WIDTH + EX_M - p->tamanho) {
        p->x = WINDOW_WIDTH + EX_M- p->tamanho;
        p->dx = -p->dx;
    }
    if (p->y < 0 - EX_M) { p->y = 0 - EX_M; p->dy = -p->dy; }
    if (p->y > WINDOW_HEIGHT + EX_M - p->tamanho) {
        p->y = WINDOW_HEIGHT + EX_M - p->tamanho;
        p->dy = -p->dy;
    }
}
