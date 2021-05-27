#include <GL/glut.h>

float trans_axeZ;
float angle_rotY;
float angle_rotX;
float kx, ky, kz;

void gerer_clavier(unsigned char touche, int x, int y) {

    switch (touche) {
        case '+':
            trans_axeZ++;
            break;
        case '-':
            trans_axeZ--;
            break;
        case '6':
            angle_rotY += 10;
            break;
        case '4':
            angle_rotY -= 10;
            break;
        case '8':
            angle_rotX -= 10;
            break;
        case '2':
            angle_rotX += 10;
            break;
        case GLUT_KEY_UP:
            ky *= 2;
            break;
        case GLUT_KEY_DOWN:
            ky *= 0.5f;
            break;
        case GLUT_KEY_RIGHT:
            kx *= 2;
            break;
        case GLUT_KEY_LEFT:
            kx *= 0.5f;
            break;

        case GLUT_KEY_PAGE_UP:
            kz *= 2;
            break;

        case GLUT_KEY_PAGE_DOWN:
            kz *= 0.5f;
            break;

        default:
            break;
    }

    glutPostRedisplay();
}