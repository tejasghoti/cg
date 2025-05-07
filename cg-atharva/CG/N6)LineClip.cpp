#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Predefined coordinates for the line
float xd1 = -150, yd1 = -50, xd2 = 150, yd2 = 50;

// Clipping window coordinates
int ymax = 100, ymin = -100, xmax = 100, xmin = -100;

// Function declarations
void disp();
float round_value(float v);
void plotpoint(float a, float b);
void lineLoop(float X1, float Y1, float X2, float Y2);
int code(int x, int y);
void cohen(float x1, float y1, float x2, float y2);
void mykey(unsigned char ch, int x, int y);
void init();

// Function to round a value to the next greater float
float round_value(float v)
{
    return (v + 0.5);
}

// Function to plot a point
void plotpoint(float a, float b)
{
    glBegin(GL_POINTS);
    glVertex2f(a, b);
    glEnd();
}

// OpenGL's built-in line drawing
void lineLoop(float X1, float Y1, float X2, float Y2)
{
    glBegin(GL_LINES); // Using OpenGL's built-in line drawing
    glVertex2f(X1, Y1);
    glVertex2f(X2, Y2);
    glEnd();
}

// Function to determine outcode for a given point (used in Cohen-Sutherland)
int code(int x, int y)
{
    int c = 0;

    if (y > ymax)
        c = 8; // If greater than ymax set code to 8
    if (y < ymin)
        c = 4; // If less than ymin set code to 4
    if (x > xmax)
        c = c | 2; // If greater than xmax set code to 2
    if (x < xmin)
        c = c | 1; // If less than xmin set code to 1

    return c;
}

// Cohen-Sutherland algorithm to clip a line
void cohen(float x1, float y1, float x2, float y2)
{
    int c1 = code(x1, y1);           // Outcode for point 1
    int c2 = code(x2, y2);           // Outcode for point 2
    float m = (y2 - y1) / (x2 - x1); // Slope of the line

    while ((c1 | c2) > 0)
    { // Iterate until both points are inside the window
        if ((c1 & c2) > 0)
        {           // If both points are completely outside the window
            return; // Don't draw anything (completely outside)
        }

        int c;
        float xi = x1, yi = y1;
        c = c1;
        float x, y;

        if (c == 0)
        {
            c = c2;
            xi = x2;
            yi = y2;
        }

        // Now find the intersection point with the window
        if ((c & 8) > 0) // Above the window
        {
            y = ymax;
            x = xi + (1.0 / m) * (ymax - yi);
        }
        else if ((c & 4) > 0) // Below the window
        {
            y = ymin;
            x = xi + (1.0 / m) * (ymin - yi);
        }
        else if ((c & 2) > 0) // To the right of the window
        {
            x = xmax;
            y = yi + m * (xmax - xi);
        }
        else if ((c & 1) > 0) // To the left of the window
        {
            x = xmin;
            y = yi + m * (xmin - xi);
        }

        // Update the point to be inside the clipping window
        if (c == c1)
        {
            xd1 = x;
            yd1 = y;
            c1 = code(xd1, yd1);
        }
        else
        {
            xd2 = x;
            yd2 = y;
            c2 = code(xd2, yd2);
        }
    }

    // Now the line should be within the clip window. Redraw the scene.
    disp(); // Redraw the window with the clipped line
}

// Function to handle keyboard input
void mykey(unsigned char ch, int x, int y)
{
    if (ch == 'c')
    {
        cohen(xd1, yd1, xd2, yd2); // Call Cohen-Sutherland algorithm on 'c' key press
        glFlush();
    }
}

// Display function to plot the window and line
void disp()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer
    glColor3f(1.0, 0.0, 0.0);     // Set color to red

    // Draw the window (rectangle)
    lineLoop(xmin, ymin, xmax, ymin);
    lineLoop(xmax, ymin, xmax, ymax);
    lineLoop(xmax, ymax, xmin, ymax);
    lineLoop(xmin, ymax, xmin, ymin);

    glColor3f(0.0, 0.0, 1.0);     // Set color to blue for the line
    lineLoop(xd1, yd1, xd2, yd2); // Draw the clipped line
    glFlush();
}

// Initialization function
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0);   // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);     // Clear the buffer
    glPointSize(2);                   // Set point size
    gluOrtho2D(-320, 320, -240, 240); // Set orthographic projection
    glFlush();
}

// Main function
int main(int argc, char **argv)
{
    printf("Window coordinates are (-100, 100, -100, 100)\n");
    printf("Press 'C' to clip the predefined line.\n");

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
