#include <GL/glut.h>				
#include <compgraphmath2020.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

vec2 points[4] = { { 300,100 },{ 400,250 },{ 350,400 },{ 450,200 } };
vec2 points2[5] = { { points[1].x, points[1].y },{ 400, 200 },{500, 250 },{ 570, 300},{ 500, 320 } };

GLint dragged = -1;
GLint dragged2 = -1;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(8.0);
	glLineWidth(1.0);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
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

	points2[1].x = (points[1].x + (points[3].x - points[1].x) / 4);
	points2[1].y = (points[1].y + (points[3].y - points[1].y) / 4);

	glBegin(GL_POINTS);
	for (int i = 0; i < 5; i++)
		glVertex2i(points2[i].x, points2[i].y);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2i(points2[1].x, points2[1].y);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 5; i++)
		glVertex2i(points2[i].x, points2[i].y);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (float t = 0; t < 1; t += 0.01) {
		float sumx = 0;
		float sumy = 0;
		for (int i = 0; i < 5; i++) {
			sumx += points2[i].x * binomialCoefficient(4, i) * pow(t, i) * pow(1 - t, 4 - i);
			sumy += points2[i].y * binomialCoefficient(4, i) * pow(t, i) * pow(1 - t, 4 - i);
		}
		glVertex2d(sumx, sumy);
	}
	glVertex2d(points2[4].x, points2[4].y);
	glEnd();
}

void Hermite2points2tangents(vec2 P1, vec2 P2, vec2 r1, vec2 r2) {

	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (GLdouble t = 0; t < 1; t += 0.01)
		glVertex2d(P1.x * (2 * t * t * t - 3 * t * t + 1) +
			P2.x * (-2 * t * t * t + 3 * t * t) +
			r1.x * (t * t * t - 2 * t * t + t) +
			r2.x * (pow(t, 3) - pow(t, 2)),

			P1.y * (2 * t * t * t - 3 * t * t + 1) +
			P2.y * (-2 * t * t * t + 3 * t * t) +
			r1.y * (t * t * t - 2 * t * t + t) +
			r2.y * (pow(t, 3) - pow(t, 2)));
	glVertex2d(P2.x, P2.y);
	glEnd();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);

	vec2 r1 = { points[2].x - points[0].x, points[2].y - points[0].y };
	vec2 r2 = { points[3].x - points[1].x, points[3].y - points[1].y };

	glBegin(GL_LINE_STRIP);
	glVertex2i(points[2].x, points[2].y);
	glVertex2i(points[0].x, points[0].y);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(points[3].x, points[3].y);
	glVertex2i(points[1].x, points[1].y);
	glEnd();

	Hermite2points2tangents(points[0], points[1], r1, r2);

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex2d(points[i].x, points[i].y);
	glEnd();

	drawBezierWithBernstein();

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

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if ((i = getActivePoint1(points, 4, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
		if ((i = getActivePoint1(points2, 5, 8, xMouse, winHeight - yMouse)) != -1)
			dragged2 = i;
	}
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
		dragged = -1;
		dragged2 = -1;
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

	if (dragged2 >= 0) {
		points2[dragged2].x = xMouse;
		points2[dragged2].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Grade 2 Project");

	init();
	glutDisplayFunc(draw);

	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutMainLoop();
	return 0;
}