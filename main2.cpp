#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

GLdouble xPos = 10, yPos = 3, zPos = 10;
GLdouble eyex = 0, eyey = 0, eyez = 0;
# define M_PI 3.14159265358979323846  /* pi */
GLUquadricObj *p = gluNewQuadric();

float angle = 0.0f;

void inicializar()
{
	glClearColor(0, 0, 0, 0.0);
	glEnable(GL_DEPTH_TEST);
    gluQuadricDrawStyle(p,GLU_LINE);

//    glEnable(GL_LIGHTING);

//    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
//    float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
//    float globAmb[] = { 0.05, 0.05, 0.05, 1.0 };

//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);

//    glEnable(GL_LIGHT0); // Enable particular light source.
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

//    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
//    float matShine[] = { 50.0 };

//    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
//    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void graficarEjes()
{
	glBegin(GL_LINES);
	
    glColor3f(1, 0, 0);
	glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);

    glColor3f(0, 1, 0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
 	glEnd();
}

float alturaBase = 1.0f;
float anchuraBrazo = 0.5f;

float alturaParte1 = 5.0f;

float alturaParte2 = 5.0f;
float altoCabeza = 5.0f;

float rotarCabeza1 = -60;
float rotarCabeza2 = 0;

static float spotAngle = 10.0; // Spotlight cone half-angle.
static float spotExponent = 2.0; // Spotlight exponent = attenuation.

void DibujarCono(float largo, float radio, int proximidad){
    glBegin(GL_POLYGON);
    for (size_t angulo = 0; angulo <= 360; angulo+=(360/proximidad))
    {
        glVertex3f( radio * cos( ( M_PI/ 180) * angulo), radio * sin( (M_PI / 180) * angulo), largo);
        glVertex3f(0, 0, 0); // inicio
        glVertex3f( radio * cos( ( M_PI/ 180) * angulo), radio * sin( (M_PI / 180) * angulo), largo);
    }
    glEnd();
}

void graficar()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(xPos, yPos, zPos, eyex, eyey, eyez, 0, 1, 0); // CAMARA
    glRotatef(angle, 0, 1, 0);
    
	graficarEjes();

    glScalef(0.3, 0.3, 0.3);

    glRotatef(rotarCabeza1, 0, 1, 0);
    glColor3ub(255, 255, 255);
    DibujarCono(10, 5, 30);

	glutSwapBuffers();
}

void redimensionar(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (float)w / (float)h, 1, 50);
}

void teclado(unsigned char c, int m, int n){
    switch (c)
    {
    case 'a':
        angle += 2.0f;
        break;
    case 'd':
        angle -= 2.0f;
        break;
    }
    glutPostRedisplay();
}

void temporizador1(int t){
    glutTimerFunc(100, temporizador1, 1);
    rotarCabeza1 += 2.0f;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Hola Mundo");

	inicializar();

	glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
    glutKeyboardFunc(teclado);
    glutTimerFunc(100, temporizador1, 1);
	glutMainLoop();

	return 0;
}