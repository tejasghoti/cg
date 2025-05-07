#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// === Drawing a pixel ===
void displayPoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// === DDA Line Drawing Algorithm ===
void drawLineDDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(abs(dx), abs(dy));
    float Xinc = dx / steps;
    float Yinc = dy / steps;
    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++)
    {
        displayPoint(round(x), round(y));
        x += Xinc;
        y += Yinc;
    }
}

// === Bresenham Circle Drawing ===
void drawCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 3 - 2 * r;

    while (x <= y)
    {
        displayPoint(xc + x, yc + y);
        displayPoint(xc - x, yc + y);
        displayPoint(xc + x, yc - y);
        displayPoint(xc - x, yc - y);
        displayPoint(xc + y, yc + x);
        displayPoint(xc - y, yc + x);
        displayPoint(xc + y, yc - x);
        displayPoint(xc - y, yc - x);

        if (p < 0)
        {
            p += 4 * x + 6;
        }
        else
        {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// === Truck Drawing ===
void drawTruck()
{
    glColor3f(0, 0, 0); // Black lines

    // Truck back (rectangle)
    drawLineDDA(150, 200, 350, 200); // Bottom
    drawLineDDA(150, 300, 350, 300); // Top
    drawLineDDA(150, 200, 150, 300); // Left
    drawLineDDA(350, 200, 350, 300); // Right

    // Truck cabin
    drawLineDDA(100, 200, 150, 200); // Bottom
    drawLineDDA(100, 240, 150, 240); // Middle slope base
    drawLineDDA(100, 200, 100, 240); // Back of cabin
    drawLineDDA(150, 240, 150, 300); // Join to top

    // Diagonal slope
    drawLineDDA(100, 240, 120, 260);
    drawLineDDA(120, 260, 150, 260);

    // Window inside cabin
    drawLineDDA(110, 220, 130, 220);
    drawLineDDA(130, 220, 130, 240);
    drawLineDDA(130, 240, 110, 240);
    drawLineDDA(110, 240, 110, 220);

    // Wheels
    drawCircle(130, 180, 20);
    drawCircle(130, 180, 10);
    drawCircle(250, 180, 20);
    drawCircle(250, 180, 10);
    drawCircle(320, 180, 20);
    drawCircle(320, 180, 10);
}

// === Rendering ===
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawTruck();
    glFlush();
}

// === Setup OpenGL window ===
void init()
{
    glClearColor(1, 1, 1, 1); // White background
    gluOrtho2D(0, 500, 0, 500);
}

// === Main ===
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Truck using DDA and Bresenham Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
