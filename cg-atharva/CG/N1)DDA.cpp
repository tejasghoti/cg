#include <GL/glut.h>
#include <iostream>
#include <cmath>

void displayPoint(int x, int y)
{
    glColor3f(0, 0, 0); // Color of the staircase line
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void SimpleLine(float x1, float y1, float x2, float y2)
{
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    step = (std::abs(dx) > std::abs(dy)) ? std::abs(dx) : std::abs(dy);

    float Xinc = dx / step;
    float Yinc = dy / step;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++)
    {
        displayPoint(static_cast<int>(x), static_cast<int>(y));
        x += Xinc;
        y += Yinc;
    }
    glFlush();
}

void initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
}

void primitives()
{
    glColor3f(0, 0, 0);

    // Monitor outer rectangle
    SimpleLine(100, 500, 500, 500); // Top
    SimpleLine(500, 500, 500, 300); // Right
    SimpleLine(500, 300, 100, 300); // Bottom
    SimpleLine(100, 300, 100, 500); // Left

    // Inner display rectangle
    SimpleLine(130, 470, 470, 470); // Top
    SimpleLine(470, 470, 470, 330); // Right
    SimpleLine(470, 330, 130, 330); // Bottom
    SimpleLine(130, 330, 130, 470); // Left

    // Small hill (left)
    SimpleLine(130, 330, 200, 420); // Left slope
    SimpleLine(200, 420, 250, 330); // Right slope

    // Big hill (right)
    SimpleLine(250, 330, 350, 450); // Left slope
    SimpleLine(350, 450, 470, 330); // Right slope

    // Monitor stand (triangle shape)
    SimpleLine(300, 300, 350, 250); // Top right
    SimpleLine(350, 250, 250, 250); // Bottom
    SimpleLine(250, 250, 300, 300); // Top left
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL - DDA Algorithm A Monitor Screen with a Hill On Display");
    initialize();
    glutDisplayFunc(primitives);
    glutMainLoop();
    return 0;
}
