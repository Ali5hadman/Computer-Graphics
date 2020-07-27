#include <GL/glut.h>
#include <compgraphmath2020.h>
#include <math.h>


GLsizei winWidth = 800, winHeight = 800;
int pause = -1;
int N = 9;
vec3 cube[9] =
{
    vec3(-0.5,-0.5, 0.5),
    vec3(0.5,-0.5, 0.5),
    vec3(0.5, 0.5, 0.5),
    vec3(-0.5, 0.5, 0.5),
    vec3(-0.5,-0.5,-0.5),
    vec3(0.5,-0.5,-0.5),
    vec3(0.5, 0.5,-0.5),
    vec3(-0.5, 0.5,-0.5),
    vec3(0, 0,1.5),
};
vec2 drawableCube[9] = {};

vec3 last3Dposition[9] = {};

mat4 w2v, projection, rotation;


void initMatrices() {

    projection = ortho();

    vec2 windowSize = { 2, 2 };
    vec2 windowPosition = {-1, -1 };
    vec2 viewportSize = { 500, 500 };
    vec2 viewportPosition = { winWidth / 2 - viewportSize.x / 2, winHeight / 2 - viewportSize.y / 2 };
    w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(0.0);
    glLineWidth(10.0);

    initMatrices();
}

void drawCube() {

    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++) {
        glVertex2d(drawableCube[i].x, drawableCube[i].y);
    }
    glEnd();

    // front

    if ((cross(last3Dposition[1] - last3Dposition[0], last3Dposition[2] - last3Dposition[0])).z > 0) {
        //glColor3f(0, 0, 0);
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glEnd();


        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glEnd();
    }

    // right
    if ((cross(last3Dposition[5] - last3Dposition[1], last3Dposition[6] - last3Dposition[1])).z > 0) {
        //glColor3f(1, 0, 0);
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glEnd();
    }

    // back
    if ((cross(last3Dposition[7] - last3Dposition[4], last3Dposition[6] - last3Dposition[4])).z > 0) {
       // glColor3f(0, 1, 0);
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glEnd();
    }

    // left
    if ((cross(last3Dposition[3] - last3Dposition[0], last3Dposition[7] - last3Dposition[0])).z > 0) {
        //glColor3f(0, 0, 1);



        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glEnd();

        glColor3f(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glEnd();
    }

    // bottom
    if ((cross(last3Dposition[4] - last3Dposition[0], last3Dposition[5] - last3Dposition[0])).z > 0) {
       // glColor3f(1, 1, 0);
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[4].x, drawableCube[4].y);
        glVertex2d(drawableCube[5].x, drawableCube[5].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glEnd();
    }

    // top
    if ((cross(last3Dposition[2] - last3Dposition[3], last3Dposition[6] - last3Dposition[3])).z > 0) {
        //glColor3f(0, 1, 1);
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[6].x, drawableCube[6].y);
        glVertex2d(drawableCube[7].x, drawableCube[7].y);
        glEnd();
    }
    //----------------------------------------------------------------Triangles--------------------------------------------------------//


    if ((cross(last3Dposition[3] - last3Dposition[8], last3Dposition[3] - last3Dposition[2])).z > 0) {
        //glColor3f(0.5, 1, 0.5);
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();
    }

    if ((cross(last3Dposition[1] - last3Dposition[2], last3Dposition[1] - last3Dposition[8])).z > 0) {
       // glColor3f(1, 0.5,0);
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[2].x, drawableCube[2].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();
    }

    if ((cross(last3Dposition[0] - last3Dposition[8], last3Dposition[0] - last3Dposition[3])).z > 0) {
       // glColor3f(0.5, 0.5, 1);
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[3].x, drawableCube[3].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();
    }

    if ((cross(last3Dposition[0] - last3Dposition[1], last3Dposition[0] - last3Dposition[8])).z > 0) {
        //glColor3f(1, 1, 0.5);
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2d(drawableCube[0].x, drawableCube[0].y);
        glVertex2d(drawableCube[1].x, drawableCube[1].y);
        glVertex2d(drawableCube[8].x, drawableCube[8].y);
        glEnd();
    }

}

//float alpha = pi() / 3;
float alpha = -pi()/4 ;
float beta = pi() / 2;
float rot = 0;


void transform() {

        rotation = rotateX(-45) * rotateZ(beta);
        mat4 temp = rotation;
        mat4 M = w2v * projection * rotation;

        for (int i = 0; i < N; i++) {

            vec4 pointH = ihToH(cube[i]);
            vec4 transformedPoint = M * pointH;

            vec4 temptransformedH = temp * pointH;

            last3Dposition[i] = { hToIh(temptransformedH).x, hToIh(temptransformedH).y, hToIh(temptransformedH).z };

            if (transformedPoint.w != 0)
            {
                drawableCube[i] = { hToIh(transformedPoint).x, hToIh(transformedPoint).y };
            }
        }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);

    transform();

    drawCube();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
        pause = pause * -1;

        break;
    }
    glutPostRedisplay();
}

void update(int n)
{
    if (pause < 0) {

       beta += pi() /150.0f;


        //alpha += pi() / 180.0f;
        //beta += pi() / 360.0f;

    }
    glutPostRedisplay();
    glutTimerFunc(17, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ali Shadman 3rd assgmnt");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(17, update, 0);
    glutMainLoop();
    return 0;
}



