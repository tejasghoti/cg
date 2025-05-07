#include <GL/glut.h>
#include <iostream>
#include <cmath>

int R = 100;

void plotpixel(int x, int y, int xc, int yc)
{
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex2f(x + xc, y + yc);
    glVertex2f(-x + xc, y + yc);
    glVertex2f(x + xc, -y + yc);
    glVertex2f(-x + xc, -y + yc);
    glVertex2f(y + xc, x + yc);
    glVertex2f(y + xc, -x + yc);
    glVertex2f(-y + xc, -x + yc);
    glVertex2f(-y + xc, x + yc);
    glEnd();
}

void circle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;
    while (x <= y)
    {
        plotpixel(x, y, xc, yc);
        if (p >= 0)
        {
            y--;
            p = p + 4 * (x - y) + 10;
        }
        else
        {
            p = p + 4 * x + 6;
        }
        x++;
    }
}

void bangle()
{
    int n = 31;
    float angleStep = 2 * M_PI / n;
    int r = R / 10;

    for (int i = 0; i < n; i++)
    {
        float theta = i * angleStep;
        int x = R * cos(theta);
        int y = R * sin(theta);
        circle(1.14 * x, 1.14 * y, r);
    }
}

void render()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    // Always draw full bangle
    circle(0, 0, R);
    circle(0, 0, R - 10);
    bangle();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BCA - Bangle Drawing");
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}
