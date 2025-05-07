#include <GL/glut.h>
#include <cmath>
float ball_y = -0.8f;   // Starting Y position
float speed = 0.02f;    // Initial upward speed
float gravity = -0.001f; // Gravity pulling the ball down
bool going_up = true;

void init() {
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f); // Light background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1); // 2D orthographic view
}

void drawBall() {
    glColor3f(1.0f, 0.2f, 0.2f); // Red ball
    float radius = 0.1f;
    int triangleAmount = 100;
    float twicePi = 2.0f * 3.1416f;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, ball_y); // center
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                radius * cos(i * twicePi / triangleAmount),
                ball_y + radius * sin(i * twicePi / triangleAmount)
            );
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall();
    glFlush();
}

void timer(int) {
    speed += gravity;
    ball_y += speed;

    // Bounce condition
    if (ball_y <= -0.8f) {
        ball_y = -0.8f;
        speed = 0.02f; // Reset speed to simulate bounce
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // roughly 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bouncing Ball Animation - OpenGL");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

