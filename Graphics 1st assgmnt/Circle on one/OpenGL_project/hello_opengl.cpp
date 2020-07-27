#include <GL/glut.h>					// (or others, depending on the system in use)
#include <compgraphmath2020.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 800;

vec2 O = { 600,200 };
GLdouble r = 50;
GLint y;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

GLdouble t = 0;
int fill =1;

void circle(vec2 O, GLdouble r) {
	if (fill < 0 ) {

		glBegin(GL_POLYGON);
		for (t = 0; t < 2 * pi(); t += 0.01)
			glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for (t = 0; t < 2 * pi(); t += 0.01)
			glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
		glEnd();
	}

	
}


GLint clr;

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	if (O.y > y) {

		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else 
	{
		glColor3f(0.0f, 0.0f, 1.0f);
	}

	circle(O, r);


	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(1000, 1000);

	glEnd();

	glFlush();
}




GLint novX = 1;
GLint novy = 1;
BOOLEAN nx = true; 
BOOLEAN ny = true;


void update(int n)
{
	
	O.x += novX;
	if (O.x + r > 800 || O.x - r < 0) {
		if (nx == true) {
			novX = (rand() % 3) +1;            // A BIT OF RANDOMNESS SO THE MOVEMENT WONT BE A LOOP 
			novX *= -1;
			nx = false;
		}else  {
			novX *= -1;
			nx = true;
		}

		fill *= -1;
	}
	

	O.y += novy;
	if ( O.y + r >800 || O.y - r < 0) {
		if (ny == true) {
			novy = (rand() % 3) + 1;              // SAME FOR HERE 
			novy *= -1;
			ny = false;
		}
		else {
			novy *= -1;
			ny = true;
		}

		fill *= -1;
	}
	y = ((1) * O.x);

	
	glutPostRedisplay();
	glutTimerFunc(3, update, 0);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(winWidth, winHeight);      // Set display-window width and height.
	glutCreateWindow("Ali Shadman N# FT0E0Q 1st assignment"); // Create display window.

	init();                            // Execute initialization procedure.
	glutDisplayFunc(draw);       // Send graphics to display window.
	glutTimerFunc(1, update, 0);
	glutMainLoop();                    // Display everything and wait.
	return 0;
}