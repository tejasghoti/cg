#include <GL/glut.h>
#include <vector>
using namespace std;

struct Point
{
    float x, y;
};

vector<Point> diamond = {
    {0, 150},  // Top (outside)
    {80, 0},   // Right (inside)
    {0, -150}, // Bottom (outside)
    {-80, 0}   // Left (inside)
};

vector<Point> clipped;
bool isClipped = false;

// Clipping window
int xmin = -100, xmax = 100, ymin = -100, ymax = 100;

bool inside(Point p, int edge)
{
    switch (edge)
    {
    case 0:
        return p.x >= xmin;
    case 1:
        return p.x <= xmax;
    case 2:
        return p.y >= ymin;
    case 3:
        return p.y <= ymax;
    }
    return true;
}

Point intersect(Point p1, Point p2, int edge)
{
    float m = (p2.x != p1.x) ? (p2.y - p1.y) / (p2.x - p1.x) : 1e5;
    Point i;
    switch (edge)
    {
    case 0:
        i.x = xmin;
        i.y = p1.y + m * (xmin - p1.x);
        break;
    case 1:
        i.x = xmax;
        i.y = p1.y + m * (xmax - p1.x);
        break;
    case 2:
        i.y = ymin;
        i.x = (m != 0) ? p1.x + (ymin - p1.y) / m : p1.x;
        break;
    case 3:
        i.y = ymax;
        i.x = (m != 0) ? p1.x + (ymax - p1.y) / m : p1.x;
        break;
    }
    return i;
}

vector<Point> clipEdge(const vector<Point> &poly, int edge)
{
    vector<Point> out;
    for (size_t i = 0; i < poly.size(); i++)
    {
        Point curr = poly[i];
        Point prev = poly[(i + poly.size() - 1) % poly.size()];
        bool inCurr = inside(curr, edge);
        bool inPrev = inside(prev, edge);

        if (inPrev && inCurr)
            out.push_back(curr);
        else if (inPrev && !inCurr)
            out.push_back(intersect(prev, curr, edge));
        else if (!inPrev && inCurr)
        {
            out.push_back(intersect(prev, curr, edge));
            out.push_back(curr);
        }
    }
    return out;
}

void clipPolygon()
{
    clipped = diamond;
    for (int edge = 0; edge < 4; edge++)
        clipped = clipEdge(clipped, edge);
    isClipped = true;
    glutPostRedisplay();
}

void drawPolygon(const vector<Point> &poly, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (auto &p : poly)
        glVertex2f(p.x, p.y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    if (isClipped)
        drawPolygon(clipped, 1, 0, 0); // red clipped polygon
    else
        drawPolygon(diamond, 0, 0, 1); // blue original diamond

    glFlush();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 'c' || key == 'C')
        clipPolygon();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Diamond Clipping - Sutherland-Hodgman");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
