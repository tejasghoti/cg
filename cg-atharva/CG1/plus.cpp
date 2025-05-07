#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct pixel {
    GLubyte r, g, b;
} pixel;

pixel f_color, b_color;
int ch = 1;

void draw_plus_outline() {
    glColor3ub(b_color.r, b_color.g, b_color.b); // Set boundary color
    glBegin(GL_LINE_LOOP);
        glVertex2f(180, 120);
        glVertex2f(220, 120);
        glVertex2f(220, 180);
        glVertex2f(280, 180);
        glVertex2f(280, 220);
        glVertex2f(220, 220);
        glVertex2f(220, 280);
        glVertex2f(180, 280);
        glVertex2f(180, 220);
        glVertex2f(120, 220);
        glVertex2f(120, 180);
        glVertex2f(180, 180);
    glEnd();
    glFlush();
}

void boundary_fill(int x, int y) {
    pixel c;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
    if ((c.r != b_color.r || c.g != b_color.g || c.b != b_color.b) &&
        (c.r != f_color.r || c.g != f_color.g || c.b != f_color.b)) {
        glColor3ub(f_color.r, f_color.g, f_color.b);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundary_fill(x + 1, y);
        boundary_fill(x - 1, y);
        boundary_fill(x, y + 1);
        boundary_fill(x, y - 1);
    }
}

void draw_plus_sign() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_plus_outline();

    // Fill color
    f_color.r = 255; f_color.g = 0; f_color.b = 0; // Red fill
    boundary_fill(200, 200); // Seed inside the plus
}

void mouse_click(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (ch == 1) {
            draw_plus_sign();
            ch = 2;
        }
    }
}

void init_func() {
    glFlush();
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);         // Black drawing color
    gluOrtho2D(0, 500, 0, 500);       // Coordinate system
}

int main(int argc, char **argv) {
    b_color.r = 0; b_color.g = 0; b_color.b = 0; // Boundary color: Black

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Seed Fill Plus Sign");
    Init();
    glutDisplayFunc(init_func);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0;
}

