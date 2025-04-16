#include "freeglut.h"
#include "tablero.h"

Tablero tablero; // Tablero global

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Ajedrez Balbo 2D");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-7, 7, -6, 6); // vista perfecta para 11 casillas de ancho centradas


	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);

	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    tablero.dibuja(); // Dibuja el tablero

    glutSwapBuffers();
}


void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	glutPostRedisplay();
}

void OnTimer(int value)
{
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}
