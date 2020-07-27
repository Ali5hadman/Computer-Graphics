#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


GLsizei winWidth = 300, winHeight = 300;

BOOLEAN GREED = true;

bool fullscreen = false;

float circel_x, circel_y, movespeedx, movespeedy;
float radius = 0.07f;





bool init()
{

	glColor3f(1.0f, 0.0f, 0.0f);
	glClearColor(1.0, 1.0, 1.0, 0.0);


	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int PI = 3.14;

	glBegin(GL_LINES);
	glVertex2f(0.9f, 0.9f);
	glVertex2f(-0.9f, -0.9f);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);

	if (GREED == true) {
		glBegin(GL_POLYGON);
		for (float angle = 0; angle < 360; angle += 5)
		{
			float x = sin(angle * PI / 180) * radius;
			float y = cos(angle * PI / 180) * radius;
			glVertex3f(x + circel_x, y + circel_y, 0.0f);
			glEnd();
		}
	}
	else
	{
		glBegin(GL_LINE_LOOP);

		for (float angle = 0; angle < 360; angle += 5)
		{
			float x = sin(angle * PI / 180) * radius;
			float y = cos(angle * PI / 180) * radius;
			glVertex3f(x + circel_x, y + circel_y, 0.0f);
			glEnd();
		}
	}


	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}



void update(int n) {


	if (circel_x + radius > 1.0f || circel_x - radius < -1.0f)
	{
		if (GREED == true)
			GREED = false;

		else
			GREED = true;

		movespeedx *= -1;
	}
	if (circel_y + radius > 1.0 || circel_y - radius < -1.0f)
	{
		movespeedy *= -1;
	}
	circel_x += movespeedx;
	circel_y += movespeedy;

	glutPostRedisplay();
	glutTimerFunc(3, update, 0);

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(1);
}

void specialKeyboard(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_F2:
		fullscreen = !fullscreen;
		if (fullscreen)
			glutFullScreen();
		else
		{
			glutReshapeWindow(500, 500);
			glutPositionWindow(200, 200);
		}
		break;
	}
}

int main(int argc, char* argv[])
{

	movespeedx = 0.02f;
	movespeedy = 0.03f;


	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);


	glutCreateWindow(" BOUNCING BALL");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	if (!init())
		return 1;

	glutMainLoop();

	return 0;
}

