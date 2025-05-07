#include <GL/glut.h>
#include <iostream>

int windowWidth = 500, windowHeight = 500;
int seedX = 0, seedY = 0;
bool seedCaptured = false;

float newColor[3] = {1.0, 0.0, 0.0}; // Default Red
bool firstRenderDone = false;

void object() {
    glColor3f(1, 1, 1); // White border
    for(int i=0;i<=4;i++){
    glBegin(GL_LINES);
    glVertex2f(100, 100-i*50);
    glVertex2f(-100, 100-i*50);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(100-i*50,-100 );
    glVertex2f(100-i*50, 100);
    glEnd();
    }
    }

void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float *color) {
    glReadPixels(x + windowWidth / 2, y + windowHeight / 2, 1, 1, GL_RGB, GL_FLOAT, color);
}

void floodFill(int x, int y, float *oldColor, float *newColor) {
    float current[3];
    getPixelColor(x, y, current);

    if (abs(current[0] - oldColor[0]) < 0.01 &&
        abs(current[1] - oldColor[1]) < 0.01 &&
        abs(current[2] - oldColor[2]) < 0.01) {

        setPixel(x, y, newColor[0], newColor[1], newColor[2]);

        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void menu(int option) {
    switch(option) {
        case 1: newColor[0] = 1.0; newColor[1] = 0.0; newColor[2] = 0.0; break; // Red
        case 2: newColor[0] = 0.0; newColor[1] = 1.0; newColor[2] = 0.0; break; // Green
        case 3: newColor[0] = 0.0; newColor[1] = 0.0; newColor[2] = 1.0; break; // Blue
        case 4: newColor[0] = 1.0; newColor[1] = 1.0; newColor[2] = 0.0; break; // Yellow
    }

    if (seedCaptured) {
        float oldColor[] = {0.0, 0.0, 0.0}; // Background color
        floodFill(seedX, seedY, oldColor, newColor);
        seedCaptured = false;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        seedX = x - windowWidth / 2;
        seedY = (windowHeight / 2) - y;
        seedCaptured = true;
        std::cout << "Seed captured at: (" << seedX << "," << seedY << ")\n";
    }
}

void render() {
    if (!firstRenderDone) {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        gluOrtho2D(-250, 250, -250, 250);
        object();
        glFlush();
        firstRenderDone = true;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill");
    glutDisplayFunc(render);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
