#include <GL/glut.h>
#include <iostream>
int seedX = 0, seedY = 0;
bool seedCaptured = false;

float newColor[3] = {1.0, 0.0, 0.0}; // Default Red
bool firstRenderDone = false;
void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float *color) {
    glReadPixels(x + 500 / 2, y + 500 / 2, 1, 1, GL_RGB, GL_FLOAT, color);
}

void boundaryFill(int x, int y, float *fillColor, float *boundaryColor) {
    float current[3];
    getPixelColor(x, y, current);

    bool isBoundary =
        (abs(current[0] - boundaryColor[0]) < 0.01 &&
         abs(current[1] - boundaryColor[1]) < 0.01 &&
         abs(current[2] - boundaryColor[2]) < 0.01);

    bool isFilled =
        (abs(current[0] - fillColor[0]) < 0.01 &&
         abs(current[1] - fillColor[1]) < 0.01 &&
         abs(current[2] - fillColor[2]) < 0.01);

    if (!isBoundary && !isFilled) {
        setPixel(x, y, fillColor[0], fillColor[1], fillColor[2]);
        glFlush(); // Ensure the pixel is updated

        // 4-connected boundary fill
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

void swastik() {

    glColor3f(1.0, 1.0, 1.0);  // White color

    glBegin(GL_LINE_LOOP);

        glVertex2f(15, 15);
        glVertex2f(95, 15);
        glVertex2f(95, -95);
        glVertex2f(65, -95);
        glVertex2f(65, -15);
        glVertex2f(15, -15);


        glVertex2f(15, -15);
        glVertex2f(15, -95);
        glVertex2f(-95, -95);
        glVertex2f(-95, -65);
        glVertex2f(-15, -65);
        glVertex2f(-15, -15);


        glVertex2f(-15, -15);
        glVertex2f(-95, -15);
        glVertex2f(-95, 95);
        glVertex2f(-65, 95);
        glVertex2f(-65, 15);
        glVertex2f(-15, 15);


        glVertex2f(-15, 15);
        glVertex2f(-15, 95);
        glVertex2f(95, 95);
        glVertex2f(95, 65);
        glVertex2f(15, 65);
        glVertex2f(15, 15);
    glEnd();

}

void menu(int option) {
    switch(option) {
        case 1: newColor[0] = 1.0; newColor[1] = 0.0; newColor[2] = 0.0; break; // Red
        case 2: newColor[0] = 0.0; newColor[1] = 1.0; newColor[2] = 0.0; break; // Green
        case 3: newColor[0] = 0.0; newColor[1] = 0.0; newColor[2] = 1.0; break; // Blue
        case 4: newColor[0] = 1.0; newColor[1] = 1.0; newColor[2] = 0.0; break; // Yellow
    }
    if (seedCaptured) {
        float boundaryColor[] = {1.0, 1.0, 1.0}; // White color used for Swastik
        boundaryFill(seedX, seedY, newColor, boundaryColor);
        seedCaptured = false;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        seedX = x - 500 / 2;
        seedY = (500 / 2) - y;
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
        swastik();
        glFlush();
        firstRenderDone = true;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Swastik");
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
