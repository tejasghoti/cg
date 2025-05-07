#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <cstdlib> // for abs()

void displayPoint(int x, int y)
{
    glColor3f(0, 0, 0); // Color of the line
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham's Line Drawing Algorithm
void SimpleLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1, y = y1;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    displayPoint(x, y);

    if (dx > dy)
    {
        int p = 2 * dy - dx;
        for (int i = 0; i < dx; ++i)
        {
            x += sx;
            if (p >= 0)
            {
                y += sy;
                p += 2 * (dy - dx);
            }
            else
            {
                p += 2 * dy;
            }
            displayPoint(x, y);
        }
    }
    else
    {
        int p = 2 * dx - dy;
        for (int i = 0; i < dy; ++i)
        {
            y += sy;
            if (p >= 0)
            {
                x += sx;
                p += 2 * (dx - dy);
            }
            else
            {
                p += 2 * dx;
            }
            displayPoint(x, y);
        }
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
    glColor3f(0, 0, 0);

    // Drawing the staircase using Bresenham's Line Algorithm
    SimpleLine(250, 350, 430, 350); // First horizontal line
    SimpleLine(250, 350, 250, 320); // First vertical line
    SimpleLine(250, 320, 280, 320); // Horizontal line to right
    SimpleLine(280, 320, 280, 290); // Vertical line downward
    SimpleLine(280, 290, 310, 290); // Horizontal line to right
    SimpleLine(310, 290, 310, 260); // Vertical line downward
    SimpleLine(310, 260, 340, 260); // Horizontal line to right
    SimpleLine(340, 260, 340, 230); // Vertical line downward
    SimpleLine(340, 230, 370, 230); // Horizontal line to right
    SimpleLine(370, 230, 370, 200); // Vertical line downward
    SimpleLine(370, 200, 400, 200); // Horizontal line to right
    SimpleLine(400, 200, 400, 170); // Vertical line downward
    SimpleLine(400, 170, 430, 170); // Horizontal line to right
    SimpleLine(430, 170, 430, 350); // Final vertical line back to top
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL - Bresenham Algorithm: Staircase");
    initialize();
    glutDisplayFunc(primitives);
    glutMainLoop();
    return 0;
}
