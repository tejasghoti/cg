#include <GL/glut.h>
#include <cmath>

int R = 60; // Radius of each petal circle

// Plot 8 symmetric points for a circle
void plotPixel(int x, int y, int xc, int yc)
{
    glBegin(GL_POINTS);
    glVertex2f(x + xc, y + yc);
    glVertex2f(-x + xc, y + yc);
    glVertex2f(x + xc, -y + yc);
    glVertex2f(-x + xc, -y + yc);
    glVertex2f(y + xc, x + yc);
    glVertex2f(-y + xc, x + yc);
    glVertex2f(y + xc, -x + yc);
    glVertex2f(-y + xc, -x + yc);
    glEnd();
}

// Bresenham's Circle Algorithm
void drawCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 3 - 2 * r;

    while (x <= y)
    {
        plotPixel(x, y, xc, yc);
        if (p >= 0)
        {
            y--;
            p += 4 * (x - y) + 10;
        }
        else
        {
            p += 4 * x + 6;
        }
        x++;
    }
}

// Draw petal circles and outer boundary
void drawPattern()
{
    int numPetals = 8;
    float angleStep = 2 * M_PI / numPetals;

    // Petal circles
    for (int i = 0; i < numPetals; i++)
    {
        float angle = i * angleStep;
        int xc = R * cos(angle);
        int yc = R * sin(angle);
        drawCircle(xc, yc, R);
    }

    // Final large outer circle touching all petal circles
    drawCircle(0, 0, 2 * R);
}

void render()
{
    glClearColor(1, 1, 1, 1); // White background
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    glColor3f(0, 0, 0); // Black color
    drawPattern();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flower Pattern with Outer Circle");
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}
