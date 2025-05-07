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
    glutCreateWindow("OpenGL - Bresenham Algorithm: Monitor with Hill");
    initialize();
    glutDisplayFunc(primitives);
    glutMainLoop();
    return 0;
}
