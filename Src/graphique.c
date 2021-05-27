#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "touches.h"

void retailler(GLsizei largeur, GLsizei hauteur) {

    GLsizei size = largeur < hauteur ? largeur : hauteur;
    glViewport((largeur-size)/2,(hauteur-size)/2, size,size);
    glutPostRedisplay();
}

/**
 * Fonction permettant de dessiner un cube centré sur l'origine
 * du repère de de taille dimxdimxdim.
 * @param dim la taille du côté du cube.
 */
static void cube(float dim) {
    dim = dim / 2.0f;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    {
        //Face 1
        glVertex3f(-dim, dim, dim);
        glVertex3f(dim, dim, dim);
        glVertex3f(dim, -dim, dim);
        glVertex3f(-dim, -dim, dim);
        //Face arrière
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-dim, dim, -dim);
        glVertex3f(dim, dim, -dim);
        glVertex3f(dim, -dim, -dim);
        glVertex3f(-dim, -dim, -dim);
        //Face inférieur
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-dim, -dim, dim);
        glVertex3f(dim, -dim, dim);
        glVertex3f(dim, -dim, -dim);
        glVertex3f(-dim, -dim, -dim);
        //Face supérieur
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(-dim, dim, dim);
        glVertex3f(dim, dim, dim);
        glVertex3f(dim, dim, -dim);
        glVertex3f(-dim, dim, -dim);
        //Face gauche
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-dim, -dim, dim);
        glVertex3f(-dim, dim, dim);
        glVertex3f(-dim, dim, -dim);
        glVertex3f(-dim, -dim, -dim);
        //Face droite
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(dim, -dim, dim);
        glVertex3f(dim, dim, dim);
        glVertex3f(dim, dim, -dim);
        glVertex3f(dim, -dim, -dim);
    }
    glEnd();
}


/**
 * Fonction permettant de dessiner le repère du monde sous
 * forme d'une croix 3D.
 * @param dim la taille de la ligne représentant un demi-axe.
 */

static void repere(float dim) {

    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-dim, 0.0, 0.0);
    glVertex3f(dim, 0.0, 0.0);
    glVertex3f(0.0, -dim, 0.0);
    glVertex3f(0.0, dim, 0.0);
    glVertex3f(0.0, 0.0, -dim);
    glVertex3f(0.0, 0.0, dim);

    glEnd();
}


/**
 * Fonction utilisée pour afficher le monde 3D à visualiser. Cette fonction
 * sera appelée à chaque fois qu'un "rafraichissement" de la fenêtre
 * d'affichage sera nécessaire.
 */

void dessiner(void) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, trans_axeZ);
    glRotatef(angle_rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(angle_rotX, 1.0f, 0.0f, 0.0f);
    glScalef(kx,ky,kz);

    /* effacer l'ecran */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* raz de la fenetre avec la couleur de fond */
    /* et raz du tampon de profondeur */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* dessin des objets */
    repere(2.0f);
    cube(2.0f);
    glFlush();
    return;

}
