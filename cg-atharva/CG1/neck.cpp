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

// Draw the pearl necklace pattern
void drawPearlNecklace(int x, int y, int r) {
    // Parameters for the necklace
    int mainRadius = r;           // Main circle radius
    int pearlRadius = r/3;        // Size of each pearl
    
    // Center circle (main pearl)
    circleMP(x, y, mainRadius);
    
    // Create the pearl necklace curve
    // The curve will be a partial semicircle/U-shape
    
    // Draw the hanging pearls at the bottom (3 descending pearls)
    for (int i = 0; i < 2; i++) {
        int pearlX = x;
        int pearlY = y - mainRadius - pearlRadius*2*i - pearlRadius;
        circleMP(pearlX, pearlY, pearlRadius);
    }
    
    // Draw the left side pearls of the necklace
    for (int i = 0; i < 6; i++) {
        // Calculate position on a curved path (quarter circle)
        double angle = ang(135 - i*3); // Start at 135 degrees and decrease
        
        // Distance from center increases with each pearl
        int distance = mainRadius + pearlRadius + pearlRadius*2*i;
        
        int pearlX = x + distance * cos(angle);
        int pearlY = y + distance * sin(angle);
        
        circleMP(pearlX, pearlY, pearlRadius);
    }
    
    // Draw the right side pearls of the necklace
    for (int i = 0; i < 6; i++) {
        // Calculate position on a curved path (quarter circle)
        double angle = ang(45 + i*3); // Start at 45 degrees and increase
        
        // Distance from center increases with each pearl
        int distance = mainRadius + pearlRadius + pearlRadius*2*i;
        
        int pearlX = x + distance * cos(angle);
        int pearlY = y + distance * sin(angle);
        
        circleMP(pearlX, pearlY, pearlRadius);
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
    drawPearlNecklace(cx, cy, R);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle - Pearl Necklace");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
