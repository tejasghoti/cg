#include <GL/glut.h>
#include <cmath>
float train_pos = -1.2f; // Initial position of the train (off screen)

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); // Sky blue background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1416f * float(i) / float(100);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawTrain() {
    glPushMatrix();
    glTranslatef(train_pos, -0.3f, 0.0f); // Move the train along x-axis

    // Main body
    glColor3f(0.9f, 0.1f, 0.1f); // Red
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.6f, 0.0f);
        glVertex2f(0.6f, 0.3f);
        glVertex2f(0.0f, 0.3f);
    glEnd();

    // Engine top
    glColor3f(0.2f, 0.2f, 0.2f); // Gray
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.2f, 0.3f);
        glVertex2f(0.2f, 0.45f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    // Windows
    glColor3f(0.2f, 0.6f, 0.9f); // Blue
    glBegin(GL_POLYGON);
        glVertex2f(0.25f, 0.15f);
        glVertex2f(0.35f, 0.15f);
        glVertex2f(0.35f, 0.25f);
        glVertex2f(0.25f, 0.25f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.4f, 0.15f);
        glVertex2f(0.5f, 0.15f);
        glVertex2f(0.5f, 0.25f);
        glVertex2f(0.4f, 0.25f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawCircle(0.15f, -0.05f, 0.05f);
    drawCircle(0.45f, -0.05f, 0.05f);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTrain();
    glFlush();
}

void timer(int) {
    train_pos += 0.01f; // Move train to the right
    if (train_pos > 1.2f) train_pos = -1.2f; // Loop back to left

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 fps
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Train Animation - OpenGL");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

