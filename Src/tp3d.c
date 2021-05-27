#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "touches.h"
#include "graphique.h"

/* dimensions initiales de la fen�tre d'affichage */
#define LARGEUR  256
#define HAUTEUR  256


/**
 * Fonction d'initialisation des param�tres d'affichage
 */
static void init_screen(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.00f, 1.00f, 50.00f);
    glViewport(0, 0, LARGEUR, HAUTEUR);
    trans_axeZ = -5.0f;
    angle_rotY = 0.0f;
    angle_rotX = 0.f;
    kx = 1.0f;
    ky = 1.0f;
    kz = 1.0f;
}


/**
 * Fonction principale qui crée et initialise la fenêtre
 * d'affichage et lance la boucle d'affichage Glut.
 * @param argc le nombre d'argument sur la ligne de commande
 * @param argv une table de chaîne de caractères contenant chacun
 * des arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {

    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(LARGEUR, HAUTEUR);

    glutInitDisplayMode(GLUT_DEPTH);

    glutCreateWindow(argv[0]);

    /* choix de la fonction de rafraichissement */
    glutDisplayFunc(dessiner);
    glutReshapeFunc(retailler);
    glutKeyboardUpFunc(gerer_clavier);
    glutSpecialUpFunc(gerer_clavier);
    init_screen();

    // activer l'élimination des parties cachées
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();


    return 0;
}


