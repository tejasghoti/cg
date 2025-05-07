

#include <GL/glut.h>

float flag_y = -0.8f; // Initial Y position of the flag
bool raise_flag = false;

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1); // 2D orthographic projection
}

void drawPole() {
    glColor3f(0.3f, 0.3f, 0.3f); // Grey pole
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.8f);
        glVertex2f(0.02f, -0.8f);
        glVertex2f(0.02f, 0.8f);
        glVertex2f(-0.02f, 0.8f);
    glEnd();
}

void drawFlag() {
    glColor3f(0.0f, 1.0f, 0.0f); // Green

    glBegin(GL_POLYGON);
        glVertex2f(0.02f, flag_y);
        glVertex2f(0.4f, flag_y);
        glVertex2f(0.4f, flag_y + 0.06f);
        glVertex2f(0.02f, flag_y + 0.06f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_POLYGON);
        glVertex2f(0.02f, flag_y + 0.06f);
        glVertex2f(0.4f, flag_y + 0.06f);
        glVertex2f(0.4f, flag_y + 0.12f);
        glVertex2f(0.02f, flag_y + 0.12f);
    glEnd();

     glColor3f(1.0f, 0.5f, 0.0f); // Saffron
    glBegin(GL_POLYGON);
        glVertex2f(0.02f, flag_y + 0.12f);
        glVertex2f(0.4f, flag_y + 0.12f);
        glVertex2f(0.4f, flag_y + 0.18f);
        glVertex2f(0.02f, flag_y + 0.18f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPole();
    drawFlag();
    glFlush();
}

void timer(int) {
    if (raise_flag && flag_y < 0.6f) {
        flag_y += 0.005f; // Raise the flag gradually
        glutPostRedisplay(); // Redraw
        glutTimerFunc(16, timer, 0); // 60 fps
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        raise_flag = true;
        glutTimerFunc(0, timer, 0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Flag Hosting Animation - OpenGL");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
