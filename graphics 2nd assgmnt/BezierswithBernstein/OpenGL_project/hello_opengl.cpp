#include <GL/glut.h>
#include <compgraphmath2020.h>
#include <math.h>
#include <vector>

GLsizei winWidth = 600, winHeight = 600;

vec2 points[4] = { { -250.0f, 250.0f },{ -100.0f, -100.0f },{100.0f, -100.0f },{ 250.0f, 250.0f } };


void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0);
	glLineWidth(1.0);
}

double binomialCoefficient(int n, int k)
{
	if (k > n - k)
		k = n - k;

	double c = 1.0;

	for (int i = 0; i < k; i++)
	{
		c = c * (n - i);
		c = c / (i + 1);
	}
	return c;
}

void drawBezierWithBernstein() {

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (float t = 0; t < 1; t += 0.01) {
		float sumx = 0;
		float sumy = 0;
		for (int i = 0; i < 4; i++) {
			sumx += points[i].x * binomialCoefficient(3, i) * pow(t, i) * pow(1 - t, 3 - i);
			sumy += points[i].y * binomialCoefficient(3, i) * pow(t, i) * pow(1 - t, 3 - i);
		}
		glVertex2d(sumx, sumy);
	}
	glVertex2d(points[3].x, points[3].y);
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	drawBezierWithBernstein();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}



