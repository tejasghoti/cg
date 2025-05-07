#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#define MAX_POINTS 20

// Window boundaries
float xmin = -100;
float ymin = -100;
float xmax = 100;
float ymax = 100;

// Arrays to store polygon vertices
float inX[MAX_POINTS], inY[MAX_POINTS];
float outX[MAX_POINTS], outY[MAX_POINTS];
int inVertices, outVertices;
int clipped = 0;  // Flag to track if clipping has been performed

void display();
void keyboard(unsigned char, int, int);
void init();
void clipPolygon();

// Check if a point is inside or outside a clipper edge
int inside(float x, float y, int edge) {
    switch(edge) {
        case 0: // Left edge
            return x >= xmin;
        case 1: // Right edge
            return x <= xmax;
        case 2: // Bottom edge
            return y >= ymin;
        case 3: // Top edge
            return y <= ymax;
    }
    return 0;
}

// Calculate intersection point with a clipper edge
// Returns intersection coordinates through ix and iy parameters
void computeIntersection(float x1, float y1, float x2, float y2, int edge, float tempX[], float tempY[], int index) {
    float m;
    
    if (x1 != x2)
        m = (y2 - y1) / (x2 - x1);
    else
        m = 1e6; // Large value for vertical lines
    
    switch(edge) {
        case 0: // Left edge
            tempX[index] = xmin;
            tempY[index] = y1 + m * (xmin - x1);
            break;
        case 1: // Right edge
            tempX[index] = xmax;
            tempY[index] = y1 + m * (xmax - x1);
            break;
        case 2: // Bottom edge
            tempY[index] = ymin;
            tempX[index] = x1 + (ymin - y1) / m;
            break;
        case 3: // Top edge
            tempY[index] = ymax;
            tempX[index] = x1 + (ymax - y1) / m;
            break;
    }
}

// Sutherland-Hodgman clipping for one edge
void clipPolygonAgainstEdge(int edge) {
    int i, j;
    float s_x, s_y, e_x, e_y;
    
    // Temporary arrays for the new vertices
    float tempX[MAX_POINTS], tempY[MAX_POINTS];
    int tempVertices = 0;
    
    for (i = 0; i < outVertices; i++) {
        j = (i + 1) % outVertices;
        s_x = outX[i];
        s_y = outY[i];
        e_x = outX[j];
        e_y = outY[j];
        
        // Check if points are inside the edge
        int s_inside = inside(s_x, s_y, edge);
        int e_inside = inside(e_x, e_y, edge);
        
        if (s_inside && e_inside) {
            // Case 1: Both inside - output end point
            tempX[tempVertices] = e_x;
            tempY[tempVertices] = e_y;
            tempVertices++;
        } else if (s_inside && !e_inside) {
            // Case 2: Going out - output intersection
            computeIntersection(s_x, s_y, e_x, e_y, edge, tempX, tempY, tempVertices);
            tempVertices++;
        } else if (!s_inside && e_inside) {
            // Case 3: Coming in - output intersection and end point
            computeIntersection(s_x, s_y, e_x, e_y, edge, tempX, tempY, tempVertices);
            tempVertices++;
            tempX[tempVertices] = e_x;
            tempY[tempVertices] = e_y;
            tempVertices++;
        }
        // Case 4: Both outside - output nothing
    }
    
    // Update output vertices
    outVertices = tempVertices;
    for (i = 0; i < outVertices; i++) {
        outX[i] = tempX[i];
        outY[i] = tempY[i];
    }
}

// Main clipping function
void clipPolygon() {
    // Copy input polygon to output arrays
    outVertices = inVertices;
    for (int i = 0; i < inVertices; i++) {
        outX[i] = inX[i];
        outY[i] = inY[i];
    }
    
    // Clip against each edge
    for (int edge = 0; edge < 4; edge++) {
        clipPolygonAgainstEdge(edge);
    }
    
    clipped = 1;  // Set the clipping flag
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
        // Draw original polygon in green
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);  // Using GL_POLYGON for filled polygon
        for (int i = 0; i < inVertices; i++) {
            glVertex2f(inX[i], inY[i]);
        }
        glEnd();
        
        // Draw the outline in darker green
        glColor3f(0.0, 0.5, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < inVertices; i++) {
            glVertex2f(inX[i], inY[i]);
        }
        glEnd();
    } else {
        // Draw clipped polygon in blue (filled)
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);  // Using GL_POLYGON for filled polygon
        for (int i = 0; i < outVertices; i++) {
            glVertex2f(outX[i], outY[i]);
        }
        glEnd();
        
        // Draw the outline in darker blue
        glColor3f(0.0, 0.0, 0.7);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < outVertices; i++) {
            glVertex2f(outX[i], outY[i]);
        }
        glEnd();
    }
    
    glFlush();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        clipPolygon();
        glutPostRedisplay();
    } else if (key == 'r' || key == 'R') {
        clipped = 0;  // Reset to show original polygon
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
    printf("Enter the number of vertices (max %d): ", MAX_POINTS);
    scanf("%d", &inVertices);
    
    if (inVertices < 3 || inVertices > MAX_POINTS) {
        printf("Invalid number of vertices. Must be between 3 and %d.\n", MAX_POINTS);
        return 1;
    }
    
    printf("Enter the coordinates of the polygon:\n");
    for (int i = 0; i < inVertices; i++) {
        printf("Vertex %d (x y): ", i+1);
        scanf("%f %f", &inX[i], &inY[i]);
    }
    
    printf("\nClipping window coordinates: (%g,%g) to (%g,%g)\n", xmin, ymin, xmax, ymax);
    printf("Press 'c' to clip the polygon\n");
    printf("Press 'r' to reset and show original polygon\n");
    printf("Press 'q' to quit\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Filled Polygon Clipping");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
