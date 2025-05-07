#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

GLfloat xRotated, yRotated, zRotated;

void init(void)
{
    glClearColor(0, 0, 0, 0); // Set background color to black
}

void DrawCube(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT); // Clear the drawing buffer
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.5); // Move into the screen

    glRotatef(xRotated, 1.0, 0.0, 0.0); // Rotate about X axis
    glRotatef(yRotated, 0.0, 1.0, 0.0); // Rotate about Y axis
    glRotatef(zRotated, 0.0, 0.0, 1.0); // Rotate about Z axis

    glBegin(GL_QUADS); // Start drawing the cube

    // Top face (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face (orange)
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (violet)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd(); // End drawing the cube

    glFlush(); // Force execution of OpenGL commands
}

void animation(void)
{
    yRotated += 0.01f;
    xRotated += 0.02f;
    DrawCube();
}

void reshape(int w, int h)
{
    if (w == 0 || h == 0)
        return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating 3D Cube");

    init();
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);

    glutMainLoop();
    return 0;
}