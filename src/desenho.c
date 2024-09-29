#include "../cab/desenho.h"

Point2D convert_3D_2D(Point3D p, float *anguloX, float *anguloY) {

    // Rotação ao redor do eixo X
    float y2 = p.y * cos(*anguloX) - p.z * sin(*anguloX);
    float z2 = p.y * sin(*anguloX) + p.z * cos(*anguloX);

    // Rotação ao redor do eixo Y
    float x2 = p.x * cos(*anguloY) - z2 * sin(*anguloY);
    float z3 = p.x * sin(*anguloY) + z2 * cos(*anguloY);

    Point2D p2d;

    // Projeção ortográfica 3D para 2D
    p2d.x = (int)(x2);// + WINDOW_WIDTH / 2);
    p2d.y = (int)(y2);// + WINDOW_HEIGHT / 2);

    return p2d;
}
