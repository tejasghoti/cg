#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

// Line struct with type
struct Line {
    int xs, ys, xe, ye;
    char type; // 'a' for simple, 'b' for dotted, 'c' for dashed, 'd' for solid
};

vector<Line> lines; // Store all drawn lines
int flag = 0;       // To track clicks
int xs, ys, xe, ye; // Temporary coordinates for new line

void plotpixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// DDA for normal
void dda(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    float x = x1, y = y1;
    int steps = max(abs(dx), abs(dy));
    float xinc = float(dx) / steps;
    float yinc = float(dy) / steps;

    for (int i = 0; i < steps; i++) {
        plotpixel(int(x), int(y));
        x += xinc;
        y += yinc;
    }
}

// Dotted line
void ddaDotted(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    float x = x1, y = y1;
    int steps = max(abs(dx), abs(dy));
    float xinc = float(dx) / steps;
    float yinc = float(dy) / steps;

    for (int i = 0; i < steps; i++) {
        if (i % 4 == 0)
            plotpixel(int(x), int(y));
        x += xinc;
        y += yinc;
    }
}

// Dashed line
void ddaDashed(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    float x = x1, y = y1;
    int steps = max(abs(dx), abs(dy));
    float xinc = float(dx) / steps;
    float yinc = float(dy) / steps;

    for (int i = 0; i < steps; i++) {
        if ((i / 5) % 2 == 0) // Show 5 pixels, skip 5
            plotpixel(int(x), int(y));
        x += xinc;
        y += yinc;
    }
}

// Solid (thick) line
void ddaSolid(int x1, int y1, int x2, int y2) {
    glPointSize(2); // Make it thick
    dda(x1, y1, x2, y2);
    glPointSize(1); // Reset
}

// Redraw everything
void render() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    glColor3f(1, 1, 1); // Set color to white

    // Draw axes
    dda(0, 250, 0, -250);
    dda(-250, 0, 250, 0);

    // Draw all lines
    for (auto l : lines) {
        switch (l.type) {
            case 'a': case 'A': dda(l.xs, l.ys, l.xe, l.ye); break;
            case 'b': case 'B': ddaDotted(l.xs, l.ys, l.xe, l.ye); break;
            case 'c': case 'C': ddaDashed(l.xs, l.ys, l.xe, l.ye); break;
            case 'd': case 'D': ddaSolid(l.xs, l.ys, l.xe, l.ye); break;
        }
    }

    glFlush();
}

// Track two mouse clicks to get line
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        if (flag == 0) {
            xs = x - 250;
            ys = 250 - y;
            cout << "Start: (" << xs << "," << ys << ")" << endl;
            flag = 1;
        } else if (flag == 1) {
            xe = x - 250;
            ye = 250 - y;
            cout << "End: (" << xe << "," << ye << ")" << endl;
            flag = 0;
            cout << "Now press a key:\nA - Simple\nB - Dotted\nC - Dashed\nD - Solid\n";
        }
    }
}

// Keyboard: choose line type after 2nd click
void keyboard(unsigned char key, int x, int y) {
    if (flag == 0 && (key == 'a' || key == 'b' || key == 'c' || key == 'd' ||
                      key == 'A' || key == 'B' || key == 'C' || key == 'D')) {
        // Store the new line with type
        lines.push_back({ xs, ys, xe, ye, key });
        glutPostRedisplay();
    } else {
        cout << "Please select start and end point using mouse first.\n";
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing with Keyboard Line Type");
    glutDisplayFunc(render);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
