#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "touches.h"
#include "time.h"

void retailler(GLsizei largeur, GLsizei hauteur) {

    GLsizei size = largeur < hauteur ? largeur : hauteur;
    glViewport((largeur - size) / 2, (hauteur - size) / 2, size, size);
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
 * Fonction permettant de dessiner un cylindre
 * @param r
 * @param h
 * @param nb
 */
void cylindre(float r, float h, int nb) {
    double angleValue = (double) 2 * M_PI / (double) nb;
    double oldX = r;
    double oldY = 0;
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        for (double i = angleValue; i <= 2 * M_PI; i += angleValue) {

            glVertex3f(r * cos(i), r * sin(i), 0);
            glVertex3f(oldX, oldY, 0);
            glVertex3f(oldX, oldY, h);
            glVertex3f(r * cos(i), r * sin(i), h);

            oldX = r * cos(i);
            oldY = r * sin(i);
        }
    }
    glEnd();
}

/**
 * Créer un losange d'hauteur bas 1 et en +y la hauteur est de 75% h
 * @param l
 * @param h
 */
void pale(float l, float h) {
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    {
        glVertex3f(0, -h, 0);
        glVertex3f(l, 0, 0);
        glVertex3f(0, h * 0.75, 0);
        glVertex3f(-l, 0, 0);

    }
    glEnd();
}

/**
 * Crée une paire d'hélice
 */
void helice() {
    glMatrixMode(GL_MODELVIEW);
    glutSolidCone(0.5, -0.5, 100, 100);
    glPushMatrix();
    glTranslatef(0, -0.75, -0.25);
    pale(0.25, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.75, -0.25);
    pale(0.25, 1);
    glPopMatrix();
}

/**
 * Crée une roue avec quatre cones
 * @param rayonRoue
 * @param rayonPneu
 */
void roue(float rayonRoue, float rayonPneu) {
    glColor3f(0, 0, 1);
    glutSolidTorus(rayonPneu, rayonRoue, 100, 100);
    glColor3f(1, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    //Helice de gauche
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.25, rayonRoue, 100, 100);
    glPopMatrix();
    //Helice en bas
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glutSolidCone(0.25, rayonRoue, 100, 100);
    glPopMatrix();
    //helice droite
    glPushMatrix();
    glRotatef(90, 0, -1, 0);
    glutSolidCone(0.25, rayonRoue, 100, 100);
    glPopMatrix();
    //helice haut
    glPushMatrix();
    glRotatef(90, -1, 0, 0);
    glutSolidCone(0.25, rayonRoue, 100, 100);
    glPopMatrix();

}

void aile() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3, .1, .5);
    glutSolidSphere(1, 100, 100);
    glPopMatrix();
}

/**
 * Création du fuselage de l'avion
 */
void fuselage() {
    double hauteur = 2;
    double largeur = 1;
    cylindre(largeur, hauteur, 100);
    glColor3f(0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();//On sauvegarde avant le translate
    glTranslatef(0, 0, 0);
    glColor3f(0, 1, 0);
    glutSolidSphere(largeur, 100, 100);
    glPopMatrix(); //Retablie la pos.
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,0,-0.75);
    helice();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,2);
    glColor3f(0,1,1);
    glutSolidCone(1,1,100,100);
    glPopMatrix();

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
    glScalef(kx, ky, kz);
    srand(time(NULL));
    /* effacer l'ecran */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* raz de la fenetre avec la couleur de fond */
    /* et raz du tampon de profondeur */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* dessin des objets */
    repere(2.0f);
    //cube(2.0f);
    //glutWireSphere(2,10, 10);
    //glutSolidCone(2, 2, 10, 10);
    //glutSolidTorus(1,2,10,10);

    /**
     * AVION
     */
    glMatrixMode(GL_MODELVIEW);
    fuselage();
    glPushMatrix();
    glTranslatef(1, -0.75, 1);
    glRotatef(90, 0, 1, 0);
    roue(0.5, 0.5 * 0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1, -0.75, 1);
    glRotatef(90, 0, 1, 0);
    roue(0.5, 0.5 * 0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.75, -0.75, 1);
    glRotatef(90,0,1,0);
    cylindre(0.1,1.5,100);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.5,0.5,0.75);
    glTranslatef(0,0.75,1);
    aile();
    glPopMatrix();
    /**
     * FIN AVION
     */

    glFlush();
    glutSwapBuffers();
}
