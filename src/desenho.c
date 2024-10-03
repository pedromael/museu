#include "../cab/desenho.h"

Point2D convert_3D_2D(Point3D p, float *anguloX, float *anguloY) {
    // Definir o centro do objeto (isso pode ser ajustado dependendo do objeto)
    float centerX = WINDOW_WIDTH / 2.0f;
    float centerY = WINDOW_HEIGHT / 2.0f;
    float centerZ = 10.0f / 2.0f;  // Supondo profundidade de 10 (ou ajuste conforme necessário)

    // Transladar o ponto para o centro do objeto
    float x = p.x - centerX; 
    float y = p.y - centerY;
    float z = p.z - centerZ;

    // Rotação ao redor do eixo X
    float y2 = y * cos(*anguloX) - z * sin(*anguloX);
    float z2 = y * sin(*anguloX) + z * cos(*anguloX);

    // Rotação ao redor do eixo Y
    float x2 = x * cos(*anguloY) - z2 * sin(*anguloY);
    //float z3 = x * sin(*anguloY) + z2 * cos(*anguloY);

    Point2D p2d;

    // Projeção ortográfica 3D para 2D
    // Após a rotação, transladar de volta para o sistema de coordenadas original
    p2d.x = (int)(x2 + centerX);
    p2d.y = (int)(y2 + centerY);

    return p2d;
}

