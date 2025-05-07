#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int length, xi, yi;
double angle, triangle[3][3], initialTriangle[3][3];
bool isFirstTransformation = true;

// Draw the triangle
void drawTriangle(double triangle[3][3]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2i(triangle[i][0], triangle[i][1]);
    }
    glEnd();
}

// Display function
void display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
    
    // Draw coordinate axes
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
    
    // Draw original triangle
    glColor3f(1, 0, 0);
    drawTriangle(triangle);
    
    glFlush();
}

// Matrix multiplication 3x3
void multiplyMatrix(double triangleMatrix[3][3], double transformMatrix[3][3]) {
    // Create temporary result matrix to avoid modifying while calculating
    double tempResult[3][3] = {0};
    
    // Perform matrix multiplication
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tempResult[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                tempResult[i][j] += triangleMatrix[i][k] * transformMatrix[k][j];
            }
        }
    }
    
    // Copy result back to original triangle for further transformations
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            triangle[i][j] = tempResult[i][j];
        }
    }
}

// Translation
void translateTriangle() {
    double tx, ty;
    double transformMatrix[3][3] = {0};
    
    cout << "\nTranslating Equilateral triangle";
    cout << "\nEnter Tx: ";
    cin >> tx;
    cout << "Enter Ty: ";
    cin >> ty;
    
    // Initialize translation matrix
    transformMatrix[0][0] = 1;
    transformMatrix[1][1] = 1;
    transformMatrix[2][2] = 1;
    transformMatrix[2][0] = tx;
    transformMatrix[2][1] = ty;
    
    // Save the first transformation result
    if (isFirstTransformation) {
        // Store initial triangle before first transformation
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                initialTriangle[i][j] = triangle[i][j];
            }
        }
        isFirstTransformation = false;
    }
    
    multiplyMatrix(triangle, transformMatrix);
    
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle(triangle);
    glFlush();
}

// Rotation
void rotateTriangle() {
    double rx, ry, rotationAngle;
    double transformMatrix[3][3] = {0};
    
    cout << "\n**ROTATION**\n";
    cout << "Arbitrary Point (x,y): ";
    cin >> rx >> ry;
    cout << "Angle (in degrees): ";
    cin >> rotationAngle;
    
    // Convert to radians
    rotationAngle = rotationAngle * (M_PI / 180);
    
    // Initialize rotation matrix around arbitrary point
    transformMatrix[0][0] = cos(rotationAngle);
    transformMatrix[0][1] = sin(rotationAngle);
    transformMatrix[1][0] = -sin(rotationAngle);
    transformMatrix[1][1] = cos(rotationAngle);
    transformMatrix[2][0] = (-(rx * cos(rotationAngle)) + (ry * sin(rotationAngle)) + rx);
    transformMatrix[2][1] = (-(rx * sin(rotationAngle)) - (ry * cos(rotationAngle)) + ry);
    transformMatrix[2][2] = 1;
    
    // Save the first transformation result
    if (isFirstTransformation) {
        // Store initial triangle before first transformation
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                initialTriangle[i][j] = triangle[i][j];
            }
        }
        isFirstTransformation = false;
    }
    
    multiplyMatrix(triangle, transformMatrix);
    
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle(triangle);
    glFlush();
}

// Scaling
void scaleTriangle() {
    double sx, sy;
    double transformMatrix[3][3] = {0};
    
    cout << "\nScaling Equilateral triangle";
    cout << "\nSx: ";
    cin >> sx;
    cout << "Sy: ";
    cin >> sy;
    
    // Initialize scaling matrix
    transformMatrix[0][0] = sx;
    transformMatrix[1][1] = sy;
    transformMatrix[2][2] = 1;
    
    // Save the first transformation result
    if (isFirstTransformation) {
        // Store initial triangle before first transformation
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                initialTriangle[i][j] = triangle[i][j];
            }
        }
        isFirstTransformation = false;
    }
    
    multiplyMatrix(triangle, transformMatrix);
    
    glColor3f(1.0, 1.0, 0.0);
    drawTriangle(triangle);
    glFlush();
}

// Shearing
void shearTriangle() {
    int choice;
    double shearValue;
    double transformMatrix[3][3] = {0};
    
    cout << "\nShear Equilateral triangle";
    cout << "\nPress 1: X-Shear";
    cout << "\nPress 2: Y-Shear";
    cout << "\nEnter your Choice: ";
    cin >> choice;
    
    // Initialize identity matrix
    for (int i = 0; i < 3; i++) {
        transformMatrix[i][i] = 1;
    }
    
    switch (choice) {
        case 1:
            cout << "X-shear value: ";
            cin >> shearValue;
            transformMatrix[0][1] = shearValue;  // X-shear affects x-coordinate based on y-value
            break;
        case 2:
            cout << "Y-shear value: ";
            cin >> shearValue;
            transformMatrix[1][0] = shearValue;  // Y-shear affects y-coordinate based on x-value
            break;
        default:
            cout << "Invalid choice!";
            return;
    }
    
    // Save the first transformation result
    if (isFirstTransformation) {
        // Store initial triangle before first transformation
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                initialTriangle[i][j] = triangle[i][j];
            }
        }
        isFirstTransformation = false;
    }
    
    multiplyMatrix(triangle, transformMatrix);
    
    glColor3f(0.0, 0.0, 1.0); // Change to blue for clear visualization
    drawTriangle(triangle);
    glFlush();
}

// Menu handler
void menu(int item) {
    switch (item) {
        case 1:
            translateTriangle();
            break;
        case 2:
            rotateTriangle();
            break;
        case 3:
            scaleTriangle();
            break;
        case 4:
            shearTriangle();
            break;
        case 5:
            exit(0);
            break;
    }
}

// Reset the triangle to initial position
void resetTriangle() {
    // Clear and redraw
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate axes
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
    
    // Initialize triangle coordinates
    triangle[0][0] = xi;
    triangle[0][1] = yi;
    triangle[1][0] = xi + length;
    triangle[1][1] = yi;
    triangle[2][0] = length / 2 + xi;
    triangle[2][1] = (sqrt(3) / 2 * length) + yi;
    
    // Set homogeneous coordinates
    for (int i = 0; i < 3; i++) {
        triangle[i][2] = 1;
    }
    
    // Reset first transformation flag
    isFirstTransformation = true;
    
    // Draw initial triangle
    glColor3f(1, 0, 0);
    drawTriangle(triangle);
    glFlush();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        resetTriangle();
    }
}

// Main function
int main(int argc, char** argv) {
    cout << "\n*** 2D TRANSFORMATIONS FOR TRIANGLE ***\n";
    cout << "Enter X coordinate of the base point: ";
    cin >> xi;
    cout << "Enter Y coordinate of the base point: ";
    cin >> yi;
    cout << "Enter length of sides: ";
    cin >> length;
    
    // Initialize triangle vertices with homogeneous coordinates
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            triangle[i][j] = 1;
        }
    }
    
    // Set specific triangle coordinates
    triangle[0][0] = xi;
    triangle[0][1] = yi;
    triangle[1][0] = xi + length;
    triangle[1][1] = yi;
    triangle[2][0] = length / 2 + xi;
    triangle[2][1] = (sqrt(3) / 2 * length) + yi;
    
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Triangle Transformations");
    
    // Set callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    // Create menu
    glutCreateMenu(menu);
    glutAddMenuEntry("1. Translation", 1);
    glutAddMenuEntry("2. Rotation", 2);
    glutAddMenuEntry("3. Scaling", 3);
    glutAddMenuEntry("4. Shear", 4);
    glutAddMenuEntry("5. EXIT", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    cout << "\nInstructions:";
    cout << "\n- Right-click to access transformation menu";
    cout << "\n- Press 'r' to reset the triangle";
    cout << "\n";
    
    glutMainLoop();
    return 0;
}
