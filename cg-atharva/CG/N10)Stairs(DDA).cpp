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
    gluOrtho2D(0, 600, 600, 0);
}

void primitives()
{
    glColor3f(1, 0, 0);

    // Drawing the staircase using DDA Algorithm
    SimpleLine(250, 350, 430, 350);
    SimpleLine(250, 350, 250, 320);
    SimpleLine(250, 320, 280, 320);
    SimpleLine(280, 320, 280, 290);
    SimpleLine(280, 290, 310, 290);
    SimpleLine(310, 290, 310, 260);
    SimpleLine(310, 260, 340, 260);
    SimpleLine(340, 260, 340, 230);
    SimpleLine(340, 230, 370, 230);
    SimpleLine(370, 230, 370, 200);
    SimpleLine(370, 200, 400, 200);
    SimpleLine(400, 200, 400, 170);
    SimpleLine(400, 170, 430, 170);
    SimpleLine(430, 170, 430, 350);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL - DDA Algorithm Staircase");
    initialize();
    glutDisplayFunc(primitives);
    glutMainLoop();
    return 0;
}
