#include <GL/glut.h>
#include <compgraphmath2020.h>
#include <math.h>

GLsizei winWidth = 1000, winHeight = 500;

//vec2 r1 = { 325, 260 };

vec2 points[4] = { {50, 400}, {50, 200}, {250, 150}, { 325, 260 } };
vec2 points5s[5] = { {  points[3].x,  points[3].y },{ 420,400 },{ 580,375 },{ 740,275 }, { 740,100 } };

GLint dragged = -1;
GLint dragged5s = -1;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glPointSize(10.0);
	glLineWidth(5.0);
	//glLineStipple(1, 0xFF00);
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

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);

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
void drawBezierWithBernstein5s() {

	points5s[1].x = points[3].x + (points[3].x - points[2].x) / 1.333;
	points5s[1].y = points[3].y + (points[3].y - points[2].y) / 1.333;

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < 5; i++)
		glVertex2f(points5s[i].x, points5s[i].y);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(points5s[1].x, points5s[1].y);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINE_STRIP);
	for (float t = 0; t < 1; t += 0.01) {
		float sumx = 0;
		float sumy = 0;
		for (int i = 0; i < 5; i++) {
			sumx += points5s[i].x * binomialCoefficient(4, i) * pow(t, i) * pow(1 - t, 4 - i);
			sumy += points5s[i].y * binomialCoefficient(4, i) * pow(t, i) * pow(1 - t, 4 - i);
		}

		glVertex2d(sumx, sumy);
	}
	glVertex2d(points5s[4].x, points5s[4].y);
	glEnd();
}

void display()
{


	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	drawBezierWithBernstein();

	glColor3f(0.0, 0.0, 1.0);
	drawBezierWithBernstein5s();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 5; i++)
		glVertex2f(points5s[i].x, points5s[i].y);
	glEnd();

	glutSwapBuffers();
}

GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y)
{
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist2(p[i], P) < s)
			return i;
	return -1;
}

GLint getActivePoint2(vec2* p, GLint size, GLint sens, GLint x, GLint y)
{
	GLint i;
	for (i = 0; i < size; i++)
		if (fabs((*(p + i)).x - x) < sens && fabs((*(p + i)).y - y) < sens)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if ((i = getActivePoint1(points, 4, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;

		if ((i = getActivePoint2(points5s, 5, 10, xMouse, winHeight - yMouse)) != -1)
			dragged5s = i;
	}

	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
		dragged = -1;
		dragged5s = -1;
	}
}


void processMouseActiveMotion(GLint xMouse, GLint yMouse)
{
	GLint i;
	if (dragged >= 0) {
		points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}

	if (dragged5s >= 0) {
		points5s[dragged5s].x = xMouse;
		points5s[dragged5s].y = winHeight - yMouse;
		glutPostRedisplay();
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ali Shadman 2nd Assgmnt");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutMainLoop();
	return 0;
}


