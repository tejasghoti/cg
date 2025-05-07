#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

float xd1, yd1, xd2, yd2;
int ymax = 100;
int ymin = -100;
int xmax = 100;
int xmin = -100;

void disp();
float round_value(float v) {
    return (v + 0.5);
}

void plotpoint(float a, float b) {
    glBegin(GL_POINTS);
    glVertex2f(a, b);
    glEnd();
}

void dda(float X1, float Y1, float X2, float Y2) {
    float dx, dy, x, y, xinc, yinc;
    int k, steps;
    
    dx = X2 - X1;
    dy = Y2 - Y1;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) return;  // Prevent division by zero
    
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    x = X1;
    y = Y1;
    
    plotpoint(x, y);
    for(k = 0; k < steps; k++) {
        x += xinc;
        y += yinc;
        plotpoint(round_value(x), round_value(y));
    }
    glFlush();
}

int code(int x, int y) {
    int c = 0;
    if(y > ymax) c |= 8;
    if(y < ymin) c |= 4;
    if(x > xmax) c |= 2;
    if(x < xmin) c |= 1;
    return c;
}

void cohen(float x1, float y1, float x2, float y2) {
    int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    float m;
    int accept = 0;

    while(1) {
        if(!(c1 | c2)) {  // Both points inside - accept
            accept = 1;
            break;
        }
        else if(c1 & c2) {  // Both points outside same region - reject
            break;
        }
        else {
            float x, y;
            int outcode = c1 ? c1 : c2;

            // Calculate slope (handle vertical lines)
            if(x1 != x2) {
                m = (y2 - y1) / (x2 - x1);
            } else {
                m = 1e6;  // Large value for vertical lines
            }

            if(outcode & 8) {  // Top
                y = ymax;
                x = x1 + (y - y1) / m;
            }
            else if(outcode & 4) {  // Bottom
                y = ymin;
                x = x1 + (y - y1) / m;
            }
            else if(outcode & 2) {  // Right
                x = xmax;
                y = y1 + m * (x - x1);
            }
            else if(outcode & 1) {  // Left
                x = xmin;
                y = y1 + m * (x - x1);
            }

            if(outcode == c1) {
                x1 = x;
                y1 = y;
                c1 = code(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                c2 = code(x2, y2);
            }
        }
    }

    if(accept) {
        xd1 = x1;
        yd1 = y1;
        xd2 = x2;
        yd2 = y2;
    } else {
        // Make line invisible if completely outside
        xd1 = xd2 = yd1 = yd2 = 0;
    }
    disp();
}

void mykey(unsigned char ch, int x, int y) {
    if(ch == 'c') {
        cohen(xd1, yd1, xd2, yd2);
        glFlush();
    }
}

void disp() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw clipping window in red
    glColor3f(1.0, 0.0, 0.0);
    dda(xmin, ymin, xmax, ymin);
    dda(xmax, ymin, xmax, ymax);
    dda(xmax, ymax, xmin, ymax);
    dda(xmin, ymax, xmin, ymin);
    
    // Draw line in blue
    glColor3f(0.0, 0.0, 1.0);
    dda(xd1, yd1, xd2, yd2);
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    gluOrtho2D(-320, 320, -240, 240);
    glFlush();
}

int main(int argc, char **argv) {
    printf("Window coordinates are (-100,100,-100,100)\n");
    printf("\nEnter coordinates of the line(limits: -320,320,-240,240) \nAfter entering press 'c' to clip\n");
    
    printf("\nCoordinates of first point\n");
    printf("X1: ");
    scanf("%f", &xd1);
    printf("Y1: ");
    scanf("%f", &yd1);
    
    printf("\nCoordinates of second point\n");
    printf("X2: ");
    scanf("%f", &xd2);
    printf("Y2: ");
    scanf("%f", &yd2);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Line Clipping");
    init();
    glutDisplayFunc(disp);
    glutKeyboardFunc(mykey);
    glutMainLoop();
    return 0;
}
