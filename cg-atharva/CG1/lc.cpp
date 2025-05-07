#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

// Window boundaries
float xmin = -100;
float ymin = -100;
float xmax = 100;
float ymax = 100;

// Arrays to store lines
#define MAX_LINES 10
float x1[MAX_LINES], y1[MAX_LINES], x2[MAX_LINES], y2[MAX_LINES]; // Original lines
float cx1[MAX_LINES], cy1[MAX_LINES], cx2[MAX_LINES], cy2[MAX_LINES]; // Clipped lines
int lineCount = 0;
int clipped = 0; // Flag to track if clipping has been performed
int isVisible[MAX_LINES]; // Flag to track if each line is visible after clipping

// Region codes
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

void display();
void keyboard(unsigned char, int, int);
void init();
void clipAllLines();
void clipLine(int i);
int computeCode(float, float);

// Compute the region code for a point (x, y)
int computeCode(float x, float y) {
    int code = INSIDE;
    
    if (x < xmin)      // to the left of clip window
        code |= LEFT;
    else if (x > xmax) // to the right of clip window
        code |= RIGHT;
    
    if (y < ymin)      // below the clip window
        code |= BOTTOM;
    else if (y > ymax) // above the clip window
        code |= TOP;
    
    return code;
}

// Cohen-Sutherland line clipping algorithm
void clipLine(int i) {
    float x_1 = x1[i];
    float y_1 = y1[i];
    float x_2 = x2[i];
    float y_2 = y2[i];
    
    // Compute region codes for P1, P2
    int code1 = computeCode(x_1, y_1);
    int code2 = computeCode(x_2, y_2);
    
    int accept = 0;
    
    while (1) {
        // Both endpoints inside the clip window
        if ((code1 | code2) == 0) {
            accept = 1;
            break;
        }
        // Both endpoints are outside the clip window in same region
        else if (code1 & code2) {
            break;
        }
        // Line needs clipping; at least one endpoint is outside
        else {
            int code_out;
            float x, y;
            
            // Pick the outside point
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;
            
            // Find intersection point
            // Using formulas y = y1 + slope * (x - x1) and x = x1 + (y - y1) / slope
            if (code_out & TOP) {           // point is above the clip window
                x = x_1 + (x_2 - x_1) * (ymax - y_1) / (y_2 - y_1);
                y = ymax;
            } else if (code_out & BOTTOM) { // point is below the clip window
                x = x_1 + (x_2 - x_1) * (ymin - y_1) / (y_2 - y_1);
                y = ymin;
            } else if (code_out & RIGHT) {  // point is to the right of clip window
                y = y_1 + (y_2 - y_1) * (xmax - x_1) / (x_2 - x_1);
                x = xmax;
            } else if (code_out & LEFT) {   // point is to the left of clip window
                y = y_1 + (y_2 - y_1) * (xmin - x_1) / (x_2 - x_1);
                x = xmin;
            }
            
            // Replace outside point with intersection point
            if (code_out == code1) {
                x_1 = x;
                y_1 = y;
                code1 = computeCode(x_1, y_1);
            } else {
                x_2 = x;
                y_2 = y;
                code2 = computeCode(x_2, y_2);
            }
        }
    }
    
    if (accept) {
        cx1[i] = x_1;
        cy1[i] = y_1;
        cx2[i] = x_2;
        cy2[i] = y_2;
        isVisible[i] = 1; // Line is visible
    } else {
        isVisible[i] = 0; // Line is not visible
    }
}

// Clip all lines
void clipAllLines() {
    for (int i = 0; i < lineCount; i++) {
        clipLine(i);
    }
    clipped = 1;
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw clipping window in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    
    if (!clipped) {
        // Draw original lines in green
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        for (int i = 0; i < lineCount; i++) {
            glVertex2f(x1[i], y1[i]);
            glVertex2f(x2[i], y2[i]);
        }
        glEnd();
    } else {
        // Draw original lines in light green with dotted pattern
        glColor3f(0.0, 0.5, 0.0);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);  // Dotted line pattern
        glBegin(GL_LINES);
        for (int i = 0; i < lineCount; i++) {
            glVertex2f(x1[i], y1[i]);
            glVertex2f(x2[i], y2[i]);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        
        // Draw clipped lines in blue
        glColor3f(0.0, 0.0, 1.0);
        glLineWidth(2.0);  // Make clipped lines thicker for better visibility
        glBegin(GL_LINES);
        for (int i = 0; i < lineCount; i++) {
            if (isVisible[i]) {
                glVertex2f(cx1[i], cy1[i]);
                glVertex2f(cx2[i], cy2[i]);
            }
        }
        glEnd();
        glLineWidth(1.0);  // Reset line width
    }
    
    glFlush();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        clipAllLines();
        glutPostRedisplay();
    } else if (key == 'r' || key == 'R') {
        clipped = 0;  // Reset to show original lines
        glutPostRedisplay();
    } else if (key == 'q' || key == 'Q' || key == 27) {  // 27 is ESC
        exit(0);
    }
}

// Initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main function
int main(int argc, char** argv) {
    printf("Enter the number of lines (max %d): ", MAX_LINES);
    scanf("%d", &lineCount);
    
    if (lineCount < 1 || lineCount > MAX_LINES) {
        printf("Invalid number of lines. Must be between 1 and %d.\n", MAX_LINES);
        return 1;
    }
    
    printf("Enter the coordinates of the lines:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("Line %d (x1 y1 x2 y2): ", i+1);
        scanf("%f %f %f %f", &x1[i], &y1[i], &x2[i], &y2[i]);
    }
    
    printf("\nClipping window coordinates: (%g,%g) to (%g,%g)\n", xmin, ymin, xmax, ymax);
    printf("Press 'c' to clip the lines\n");
    printf("Press 'r' to reset and show original lines\n");
    printf("Press 'q' to quit\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Clipping - Cohen-Sutherland Algorithm");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
