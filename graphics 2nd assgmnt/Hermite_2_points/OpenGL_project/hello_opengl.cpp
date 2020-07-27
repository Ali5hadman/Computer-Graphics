#include <GL/glut.h>					// (or others, depending on the system in use)
#include <compgraphmath2020.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

vec2 P1 = { 300,100 };
vec2 P2 = { 400,100 };

vec2 r1 = { 50,300 };
vec2 r2 = { 200,100 };

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}


void circle(vec2 O, GLdouble r) {

	glBegin(GL_LINE_LOOP);
	for (GLdouble t = 0; t < 2 * pi(); t += 0.01)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

void Hermite4points(vec2 P1, vec2 P2, vec2 r1, vec2 r2) {
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

	glColor3f(0.0f, 0.4f, 0.2f);

	Hermite4points(P1, P2, r1, r2);

	glPointSize(5.0);

	glBegin(GL_POINTS);
	glVertex2d(P1.x, P1.y);
	glVertex2d(P2.x, P2.y);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(0, 0);
	glVertex2d(r1.x, r1.y);
	glVertex2d(0, 0);
	glVertex2d(r2.x, r2.y);

	glVertex2d(P1.x, P1.y);
	glVertex2d(P1.x + r1.x, P1.y + r1.y);
	glVertex2d(P2.x, P2.y);
	glVertex2d(P2.x + r2.x, P2.y + r2.y);
	glEnd();

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(winWidth, winHeight);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	glutDisplayFunc(draw);       // Send graphics to display window.
	glutMainLoop();                    // Display everything and wait.
	return 0;
}