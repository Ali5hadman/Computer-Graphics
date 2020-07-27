#include <GL/glut.h>					// (or others, depending on the system in use)
#include <compgraphmath2020.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

vec2 P1 = { 100,100 };
vec2 P2 = { 200,210 };
vec2 P3 = { 300,300 };
vec2 P4 = { 100,500 };

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

void Hermite4points(vec2 P1, vec2 P2, vec2 P3, vec2 P4) {
	glBegin(GL_LINE_STRIP);
	for (GLdouble t = -1; t < 2; t += 0.01)
		glVertex2d(P1.x * ((-1.0 / 6.0) * t * t * t + (1.0 / 2.0) * t * t - (1.0 / 3.0) * t) +
			P2.x * ((1.0 / 2.0) * t * t * t - t * t - (1.0 / 2.0) * t + 1) +
			P3.x * ((-1.0 / 2.0) * t * t * t + (1.0 / 2.0) * t * t + t) +
			P4.x * ((1.0 / 6.0) * t * t * t - (1.0 / 6.0) * t),

			P1.y * ((-1.0 / 6.0) * t * t * t + (1.0 / 2.0) * t * t - (1.0 / 3.0) * t) +
			P2.y * ((1.0 / 2.0) * t * t * t - t * t - (1.0 / 2.0) * t + 1) +
			P3.y * ((-1.0 / 2.0) * t * t * t + (1.0 / 2.0) * t * t + t) +
			P4.y * ((1.0 / 6.0) * t * t * t - (1.0 / 6.0) * t));
	glVertex2d(P4.x, P4.y);
	glEnd();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);

	Hermite4points(P1, P2, P3, P4);

	glPointSize(5.0);

	glBegin(GL_POINTS);
	glVertex2d(P1.x, P1.y);
	glVertex2d(P2.x, P2.y);
	glVertex2d(P3.x, P3.y);
	glVertex2d(P4.x, P4.y);
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