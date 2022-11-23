#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846 /* pi */

bool dibujarLampara02 = false;

static float spotExponent = 2.0; // Spotlight exponent = attenuation.

GLdouble xPos = 0, yPos = 3, zPos = 10;
GLdouble eyex = 0, eyey = 0, eyez = 0;
GLUquadricObj *p = gluNewQuadric();

static float spotAngle = 10.0; // Spotlight cone half-angle.
float angle = 0.0f;

void DibujarCono(float largo, float radio, int proximidad)
{
    glBegin(GL_POLYGON);
    for (size_t angulo = 0; angulo <= 360; angulo += (360 / proximidad))
    {
        glVertex3f(radio * cos((M_PI / 180) * angulo), radio * sin((M_PI / 180) * angulo), largo);
        glVertex3f(0, 0, 0); // inicio
        glVertex3f(radio * cos((M_PI / 180) * angulo), radio * sin((M_PI / 180) * angulo), largo);
    }
    glEnd();
}

void inicializar()
{
    glClearColor(0.6, 0.6, 0.6, 0.0);
    glEnable(GL_DEPTH_TEST);
    gluQuadricDrawStyle(p, GLU_LINE);
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

// Variables Lampara 1
float TrasladarBrazoX1 = 0;
float TrasladarBrazoY1 = 0;
float TrasladarBrazoZ1 = 0;

float rotarAnteBrazo1 = 50;
float rotarAnteBrazo12 = 0;
float rotarBrazo1 = -30;

float rotarCabeza11 = 0;
float rotarCabeza21 = 110;
float rotarCabeza31 = 0;

float rotarCuerpo1Y = 0;

// Variables Lampara 2
float TrasladarBrazoX2 = 0;
float TrasladarBrazoY2 = 0;
float TrasladarBrazoZ2 = 0;

float rotarAnteBrazo2 = 50;
float rotarAnteBrazo22 = 0;
float rotarBrazo2 = -30;

float rotarCabeza12 = 0;
float rotarCabeza22 = 70;
float rotarCabeza32 = 0;

float rotarCuerpo2Y = 0;

// Variable de pelota
float rotarPelota = 0;
float trasladarPelota = 7;
float trasladarPelotaz = 0;

void dibujarLampara(float TrasladarBrazoX, float TrasladarBrazoY, float TrasladarBrazoZ, float rotarBrazo, float rotarAnteBrazo, float rotarAnteBrazo2, float rotarCabeza1, float rotarCabeza2, float rotarCabeza3, float rotarY)
{
    glRotatef(-90, 1, 0, 0);
    glTranslatef(TrasladarBrazoX, 0, 0);
    glTranslatef(0, 0, TrasladarBrazoY);
    glTranslatef(0, TrasladarBrazoZ, 0);

    glRotatef(rotarY, 0, 0, 1);
    glPushMatrix(); // Lampara
    glColor3ub(80, 80, 80);
    glutSolidCone(3, 1.0f, 30, 30); // Base

    glTranslatef(0, 0, 1.0f);
    glColor3ub(80, 80, 80);
    glRotatef(rotarBrazo, 0, 1, 0);

    glPushMatrix();                           // Primera Parte
    gluCylinder(p, 0.5f, 0.5f, 5.0f, 10, 10); // Brazo

    glTranslatef(0, 0, 5.0f + 0.3);
    glRotatef(40, 0, 1, 0);
    glRotatef(rotarAnteBrazo, 0, 1, 0);
    glRotatef(rotarAnteBrazo2, 1, 0, 0);

    glPushMatrix();                           // Segunda Parte
    gluCylinder(p, 0.5f, 0.5f, 5.0f, 10, 10); // Brazo 2

    glTranslatef(0, 0, 5.0f);
    glRotatef(rotarCabeza1, 0, 0, 1); // X
    glRotatef(rotarCabeza2, 0, 1, 0); // y
    glRotatef(rotarCabeza3, 1, 0, 0); // X

    glColor3ub(120, 120, 120);
    glPushMatrix(); // Tercer Parte
    DibujarCono(3, 2.7, 30);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

void dibujarConector()
{
    glRotatef(-90, 1, 0, 0);
    glPushMatrix();
    gluCylinder(p, 0.1, 0.1, 4, 10, 10);

    glTranslatef(0, 0, 4);
    glColor3ub(80, 80, 80);
    glPushMatrix();
    glutSolidCube(1.3);

    glTranslatef(0, -0.8, 0);
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glutSolidSphere(.3, 10, 10);
    glPopMatrix();

    glPopMatrix();

    glTranslatef(0, 0, 1.3);
    glColor3ub(80, 80, 80);
    glPushMatrix();
    glutSolidCube(1.3);

    glTranslatef(0, -0.8, 0);
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glutSolidSphere(.3, 10, 10);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

void dibujarPelota()
{
    glPushMatrix();
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
}

void dibujarMesa()
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(10, 0, 5);
    glVertex3f(10, 0, -5);
    glVertex3f(-10, 0, -5);
    glVertex3f(-10, 0, 5);
    glEnd();
    glPopMatrix();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(xPos, yPos, zPos, eyex, eyey, eyez, 0, 1, 0); // CAMARA

    glRotatef(angle, 0, 1, 0);
    graficarEjes();

    glPushMatrix();
    glColor3ub(173, 102, 33);
    dibujarMesa();

    // Primer lampara
    glPushMatrix();
    glTranslatef(-2.8, 0, 0);
    glScalef(0.4, 0.4, 0.4);
    dibujarLampara(TrasladarBrazoX1, TrasladarBrazoY1, TrasladarBrazoZ1, rotarBrazo1, rotarAnteBrazo1, rotarAnteBrazo12, rotarCabeza11, rotarCabeza21, rotarCabeza31, rotarCuerpo1Y);
    glPopMatrix();

    // Segunda lampara
    if (dibujarLampara02)
    {
        glPushMatrix();
        glTranslatef(6, 0, 0);
        glRotatef(180, 0, 1, 0);
        glScalef(0.2, 0.2, 0.2);
        dibujarLampara(TrasladarBrazoX2, TrasladarBrazoY2, TrasladarBrazoZ2, rotarBrazo2, rotarAnteBrazo2, rotarAnteBrazo22, rotarCabeza12, rotarCabeza22, rotarCabeza32, rotarCuerpo2Y);
        glPopMatrix();
    }

    // Conector
    glPushMatrix();
    glTranslatef(0, 0, -2);
    glScalef(0.4, 0.4, 0.4);
    dibujarConector();
    glPopMatrix();

    // Pelota
    glPushMatrix();
    glTranslatef(trasladarPelota, 0.2, trasladarPelotaz);
    glRotatef(rotarPelota, 1, 0, 0);
    glScalef(0.3, 0.3, 0.3);
    dibujarPelota();
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void redimensionar(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (float)w / (float)h, 1, 50);
}

void teclado(unsigned char c, int m, int n)
{
    switch (c)
    {
    case 'a':
        angle += 2.0f;
        break;
    case 'd':
        angle -= 2.0f;
        break;
    case 'w':
        rotarCabeza21 -= 2.0f;
        break;
    case 's':
        rotarCabeza21 += 2.0f;
        break;
    case 'q':
        rotarCabeza12 -= 2.0f;
        break;
    case 'e':
        rotarCabeza12 += 2.0f;
        break;
    case '1':
        rotarBrazo1 += 2.0f;
        break;
    case '2':
        rotarBrazo1 -= 2.0f;
        break;
    case '3':
        rotarAnteBrazo1 += 2.0f;
        break;
    case '4':
        rotarAnteBrazo1 -= 2.0f;
        break;
    }
    glutPostRedisplay();
}

void temporizador1(int t)
{
    glutTimerFunc(100, temporizador1, 1);
    rotarCabeza11 += 2.0f;
    glutPostRedisplay();
}

#pragma region Variables de animacion

float TagacharBrazo = 1, TagacharBrazo2 = 2, rotarVariable01 = 0, trasladoBrazoX = 0.3, trasladoBrazoX2 = 0.12, trasladoBrazoY = 0.3, trasladoBrazoZ = 0.3;
bool animacion01 = true, animacion02 = false, animacion03 = false;

#pragma endregion

#pragma region Pelota

bool pelota = true, rebote = false;

#pragma endregion

#pragma region MirarPelota

bool lampara = false;
bool moverCabeza1 = false;
bool parte1 = false;
bool parte2 = false;
bool parte3 = false;
bool parte4 = false;
bool parte5 = false;
bool parte6 = false;
bool parte7 = false;
bool parte8 = false;

#pragma endregion

#pragma region Caminar

bool caminar = false;
int i = 0, Npasos = 8;

#pragma endregion

#pragma region Interaccion

bool mirarL1 = false;
float rotarCuerpo = 0.5;
int nVeces = 10, j = 0;
int Npasos2 = 3, k = 0;
#pragma endregion

bool reiniciar = true;
void reiniciarVariables()
{
    TagacharBrazo = 1, rotarVariable01 = 0, trasladoBrazoX = 0.15, trasladoBrazoY = 0.15;
    animacion01 = true, animacion02 = false, animacion03 = false;
}

// Trasladar Brazo
void animacionLinterna(int t)
{
    glutTimerFunc(30, animacionLinterna, 1);
    if (pelota)
    {
        rotarPelota += 1;
        trasladarPelota -= 0.1;

        if (trasladarPelota <= -0.73)
        {
            rebote = true;
            pelota = false;
        }
    }

    if (rebote)
    {
        rotarPelota -= 1;
        trasladarPelota += 0.04;

        if (trasladarPelota >= 0)
        {
            rebote = false;
            lampara = true;
        }
    }

    if (lampara)
    {
        rotarCabeza21 -= 0.5;

        if (rotarCabeza21 <= 80)
        {
            lampara = false;
            moverCabeza1 = true;
            parte1 = true;
        }
    }

    if (moverCabeza1)
    {
        if (parte1)
        {
            if (rotarVariable01 >= 20)
            {
                parte1 = false;
                parte2 = true;
            }

            rotarVariable01 += TagacharBrazo;
            rotarBrazo1 -= TagacharBrazo;
            rotarAnteBrazo1 += TagacharBrazo;
        }

        if (parte2)
        {
            if (rotarBrazo1 >= 0)
            {
                parte2 = false;
                parte3 = true;
            }

            rotarAnteBrazo1 -= 0.5;
            rotarBrazo1 += TagacharBrazo;
        }

        if (parte3)
        {
            if (rotarAnteBrazo12 <= -20)
            {
                parte3 = false;
                parte4 = true;
            }

            rotarAnteBrazo12 -= 0.5;
            rotarAnteBrazo1 += 0.4;
            rotarCabeza11 -= 1;
        }

        if (parte4)
        {
            if (rotarAnteBrazo12 >= 0)
            {
                parte4 = false;
                parte5 = true;
            }

            rotarAnteBrazo12 += 0.5;
            rotarAnteBrazo1 -= 0.4;
            rotarCabeza11 += 1;
        }

        if (parte5)
        {
            if (rotarVariable01 >= 40)
            {
                parte5 = false;
                parte6 = true;
            }

            rotarVariable01 += TagacharBrazo;
            rotarAnteBrazo1 += TagacharBrazo;
            rotarCabeza21 += 1.1;
        }

        if (parte6)
        {
            if (trasladarPelota >= 7)
            {
                parte6 = false;
                parte7 = true;
            }

            if (rotarCabeza21 >= 30)
            {
                rotarCabeza21 -= 3;
            }
            else
            {
                trasladarPelota += 0.1;
                rotarAnteBrazo1 -= 0.25;
                rotarCabeza21 -= 0.27;
            }
        }

        if (parte7)
        {
            rotarPelota += 1;
            trasladarPelota -= 0.1;
            trasladarPelotaz += 0.02;
            rotarCabeza21 += 1;
            rotarCabeza31 += 0.2;

            if (trasladarPelota <= -0.73)
            {
                parte7 = false;
                parte8 = true;
            }
        }

        if (parte8)
        {
            rotarPelota -= 1;
            trasladarPelota += 0.04;

            if (trasladarPelota >= -0.5)
            {
                parte8 = false;
                moverCabeza1 = false;
                caminar = true;
                dibujarLampara02 = true;
            }
        }
    }

    if (caminar)
    {
        if (reiniciar)
        {
            reiniciarVariables();
            reiniciar = false;
        }
        
        if (i >= Npasos)
        {
            caminar = false;
            mirarL1 = true;
            parte1 = true;
            reiniciarVariables();
        }
        if (animacion01) // Abajo
        {
            if (rotarVariable01 >= 20)
            {
                animacion01 = false;
                animacion02 = true;
                TagacharBrazo = -1;
            }

            rotarVariable01 += TagacharBrazo;
            rotarAnteBrazo2 += TagacharBrazo;
        }

        if (animacion02) // Arriba y saltar
        {
            if (rotarVariable01 <= 0)
            {
                reiniciarVariables();
                animacion01 = true;
                animacion02 = false;
                i++;
            }

            rotarVariable01 += TagacharBrazo;
            rotarAnteBrazo2 += TagacharBrazo;

            TrasladarBrazoX2 += trasladoBrazoX;
            TrasladarBrazoY2 += trasladoBrazoY;

            if (TrasladarBrazoY2 <= 0)
                trasladoBrazoY = 0;

            if (TrasladarBrazoY2 >= 1.6)
                trasladoBrazoY = -trasladoBrazoY;
        }
    }

    if (mirarL1)
    {
        if (parte1)
        {
            if (rotarVariable01 >= 20)
            {
                parte1 = false;
                parte2 = true;
            }

            rotarVariable01 += TagacharBrazo;
            rotarAnteBrazo1 -= TagacharBrazo;

            TrasladarBrazoZ2 += trasladoBrazoZ;
            TrasladarBrazoY2 += trasladoBrazoY;

            if (TrasladarBrazoY2 <= 0)
                trasladoBrazoY = 0;

            if (TrasladarBrazoY2 >= 1.6)
                trasladoBrazoY = -trasladoBrazoY;
                
        }

        if (parte2)
        {
            if (rotarAnteBrazo12 <= -20)
            {
                parte2 = false;
                parte3 = true;
            }

            rotarAnteBrazo12 -= 0.5;
            rotarAnteBrazo1 += 0.4;
            rotarCabeza11 -= 1;

            rotarAnteBrazo22 -= 0.5;
            rotarAnteBrazo2 += 0.4;
            rotarCabeza32 += 1;
            rotarCabeza22 -= 1;
            rotarCabeza12 -= 1;
        }

        if (parte3)
        {
            if (j >= nVeces)
            {
                parte3 = false;
                parte4 = true;
                trasladoBrazoY = -trasladoBrazoY;
            }
            
            if ((rotarCuerpo2Y >= 2) || (rotarCuerpo2Y <= -2))
            {
                rotarCuerpo = -rotarCuerpo;
                j++;
            }
            
            rotarCuerpo2Y += rotarCuerpo;
            
        }
        
        if (parte4)
        {
            if (k >= Npasos2)
            {
                parte4 = false;
                parte5 = true;
            }
            
            TrasladarBrazoX2 += trasladoBrazoX2;
            TrasladarBrazoY2 += trasladoBrazoY;

            if ((TrasladarBrazoY2 <= 0))
            {
                trasladoBrazoY = -trasladoBrazoY;
                k++;
            }
            
            if (k == 2)
            {
                TrasladarBrazoY2 = 2.2;
                k++;
            }
            else if ((TrasladarBrazoY2 >= 2.5))
                trasladoBrazoY = -trasladoBrazoY;
        }

        if (parte5)
        {
            TrasladarBrazoY2 += trasladoBrazoY;
            
            if ((TrasladarBrazoY2 >= 5) || (TrasladarBrazoY2 <= 2.5))
                trasladoBrazoY = -trasladoBrazoY;
        }
                
    }
    
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

    glutTimerFunc(30, animacionLinterna, 1);
    glutMainLoop();

    return 0;
}
