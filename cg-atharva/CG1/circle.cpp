#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
int cx = 300, cy = 300, R = 70; // Default circle center and radius

// Angle conversion to radians
double ang(int degree) {
    return degree * 3.142 / 180.0;
}

// Plot a single pixel if it satisfies the pattern
void plotpixel(int x, int y, int count) {
    if (count % 5 == 0) {
        glPointSize(1.5);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
    }
}

// Plot 8-way symmetric pixels for the circle
void octant(int xc, int yc, int x, int y, int& count) {
    plotpixel(xc + x, yc + y, count++);
    plotpixel(xc + y, yc + x, count++);
    plotpixel(xc + y, yc - x, count++);
    plotpixel(xc + x, yc - y, count++);
    plotpixel(xc - x, yc - y, count++);
    plotpixel(xc - y, yc - x, count++);
    plotpixel(xc - y, yc + x, count++);
    plotpixel(xc - x, yc + y, count++);
}

// Midpoint Circle Drawing Algorithm (Bresenham)
void circleMP(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;
    int count = 0;
    while (x < y) {
        octant(xc, yc, x, y, count);
        x++;
        if (p > 0) {
            y--;
            p += 2 * (x - y) + 1;
        } else {
            p += 2 * x + 1;
        }
    }
}

// Draw the full bangle pattern with non-overlapping circles
void drawcircles(int x, int y, int r) {
    // Center circle (main bangle)
    circleMP(x, y, 2*r);
    
    // Small circle size
    int smallRadius = r/3; // Adjust size of small circles
    
    // Calculate the number of small circles that can fit around the perimeter without overlapping
    double mainCircumference = 2 * M_PI * (2*r); // Circumference of main circle
    double smallCircleDiameter = 2 * smallRadius; // Diameter of small circle
    
    // Maximum number of circles that can fit without overlapping
    // Each small circle needs smallCircleDiameter space on the circumference
    int maxCircles = floor(mainCircumference / smallCircleDiameter);
    
    // Use a number slightly less than maxCircles to ensure no overlap
    int numCircles = 20; // You can adjust this based on the image
    
    // Draw the small circles around the perimeter
    for (int i = 0; i < numCircles; i++) {
        double angleRad = i * (2 * M_PI / numCircles);
        
        // Position each small circle touching the main circle
        // Distance from center = radius of main circle (2*r) + smallRadius
        int newX = x + (2*r + smallRadius) * cos(angleRad);
        int newY = y + (2*r + smallRadius) * sin(angleRad);
        
        circleMP(newX, newY, smallRadius);
    }
}

// OpenGL init
void init() {
    glClearColor(1, 1, 1, 0);  // white background
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 0, 600);
    glColor3f(0, 0, 0);        // black drawing color
}

// Display function: draws automatically on window open
void draw() {
    drawcircles(cx, cy, R);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle - Bangle Pattern");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
