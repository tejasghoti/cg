#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>

using namespace std;

int length, x, y, choice, flag;
vector<vector<double>> ET(3, vector<double>(3, 1));
double angle;
vector<vector<double>> RH(4, vector<double>(4, 1));

void draw(vector<vector<double>> matrix) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < matrix.size(); i++) {
        glVertex2f(matrix[i][0], matrix[i][1]);
    }
    glEnd();
}

void Display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -240, 240);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
    glColor3f(1, 0, 0);
    if (flag == 0)
        draw(ET);
    else if (flag == 1)
        draw(RH);
    glFlush();
}

vector<vector<double>> multiply(vector<vector<double>> mat1, vector<vector<double>> mat2) {
    vector<vector<double>> ans(mat1.size(), vector<double>(mat2[0].size(), 0));
    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            double temp = 0;
            for (int k = 0; k < mat1[0].size(); k++) {
                temp += mat1[i][k] * mat2[k][j];
            }
            ans[i][j] = temp;
        }
    }
    return ans;
}

void translation(vector<vector<double>> mat) {
    double tx, ty;
    vector<vector<double>> ans(mat.size(), vector<double>(mat[0].size(), 0));
    cout << "Enter the value of Tx: ";
    cin >> tx;
    cout << "Enter the value of Ty: ";
    cin >> ty;

    for (int i = 0; i < mat.size(); i++) {
        ans[i][0] = mat[i][0] + tx;
        ans[i][1] = mat[i][1] + ty;
    }
    glColor3f(0.0, 1.0, 0.0);
    draw(ans);
}

void scale(vector<vector<double>> mat) {
    double Sx, Sy;
    vector<vector<double>> ans(mat.size(), vector<double>(mat[0].size(), 0));
    cout << "Enter the value of Sx: ";
    cin >> Sx;
    cout << "Enter the value of Sy: ";
    cin >> Sy;

    vector<vector<double>> scale_matrix = {
        {Sx, 0, 0},
        {0, Sy, 0},
        {0, 0, 1}
    };

    vector<vector<double>> result = multiply(mat, scale_matrix);
    glColor3f(0.0, 1.0, 0.0);
    draw(result);
}

void rotation(vector<vector<double>> mat) {
    double angle_degrees, cx, cy;
    string direction;
    cout << "Enter the angle of rotation (in degrees): ";
    cin >> angle_degrees;
    cout << "Enter the point (cx, cy) about which to rotate: ";
    cin >> cx >> cy;
    cout << "Enter direction (clockwise or anticlockwise): ";
    cin >> direction;

    double angle = angle_degrees * M_PI / 180.0;
    if (direction == "clockwise") {
        angle = -angle;
    }

    vector<vector<double>> rotation_matrix = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {cx * (1 - cos(angle)) + cy * sin(angle), cy * (1 - cos(angle)) - cx * sin(angle), 1}
    };

    vector<vector<double>> result = multiply(mat, rotation_matrix);
    glColor3f(1.0, 1.0, 0.0);
    draw(result);
}

void shear(vector<vector<double>> mat) {
    double Sh_x, Sh_y;
    cout << "Enter the value of X shear (Sh_x): ";
    cin >> Sh_x;
    cout << "Enter the value of Y shear (Sh_y): ";
    cin >> Sh_y;

    vector<vector<double>> shear_matrix = {
        {1, Sh_x, 0},
        {Sh_y, 1, 0},
        {0, 0, 1}
    };

    vector<vector<double>> result = multiply(mat, shear_matrix);
    glColor3f(0.0, 0.0, 1.0);
    draw(result);
}

void reflection(vector<vector<double>> mat) {
    int choice_reflection;
    cout << "Choose the reflection type: \n";
    cout << "1. Reflection about X-axis\n";
    cout << "2. Reflection about Y-axis\n";
    cout << "3. Reflection about Origin\n";
    cout << "4. Reflection about y=x\n";
    cout << "5. Reflection about y=-x\n";
      
    cout << "Enter your choice: ";
    cin >> choice_reflection;

    vector<vector<double>> reflection_matrix(3, vector<double>(3, 0));
    
    switch (choice_reflection) {
    case 1: 
        reflection_matrix = {
            {1, 0, 0},
            {0, -1, 0},
            {0, 0, 1}
        };
        break;
    case 2: 
        reflection_matrix = {
            {-1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };
        break;
    case 3: 
        reflection_matrix = {
            {-1, 0, 0},
            {0, -1, 0},
            {0, 0, 1}
        };
        break;
    case 4: 
        reflection_matrix = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 1}
        };
        break;     
     case 5: 
        reflection_matrix = {
            {0, -1, 0},
            {-1, 0, 0},
            {0, 0, 1}
        };
        break;    
    default:
        cout << "Invalid choice!\n";
        return;
    }

    vector<vector<double>> result = multiply(mat, reflection_matrix);
    glColor3f(1.0, 1.0, 1.0);
    draw(result);
}

void Menu(int item) {
    switch (item) {
    case 1:
        if (choice == 1)
            translation(ET);
        else
            translation(RH);
        break;
    case 2:
        if (choice == 1)
            scale(ET);
        else
            scale(RH);
        break;
    case 3:
        if (choice == 1)
            rotation(ET);
        else
            rotation(RH);
        break;
    case 4:
        if (choice == 1)
            shear(ET);
        else
            shear(RH);
        break;
    case 5:
        if (choice == 1)
            reflection(ET);
        else
            reflection(RH);
        break;
    }
}

int main(int argc, char** argv) {
    cout << "\n*MENU*";
    cout << "\n1. To draw Equilateral Triangle";
    cout << "\n2. To draw Rhombus";
    cout << "\n3. To Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;
    switch (choice) {
    int i, j;
    case 1:
        flag = 0;
        cout << "\nEnter X co-ordinate of a Base point: ";
        cin >> x;
        cout << "\nEnter Y co-ordinate of the Base point: ";
        cin >> y;
        cout << "\nEnter length of sides: ";
        cin >> length;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                ET[i][j] = 1;
            }
        }
        ET[0][0] = x;
        ET[0][1] = y;
        ET[1][0] = x + length;
        ET[1][1] = y;
        ET[2][0] = length / 2 + x;
        ET[2][1] = (sqrt(3) / 2 * length) + y;
        break;
    case 2:
        flag = 1;
        cout << "\nEnter X co-ordinates of a Base point: ";
        cin >> x;
        cout << "\nEnter Y co-ordinates of the Base point: ";
        cin >> y;
        cout << "\nEnter length of sides: ";
        cin >> length;
        cout << "\nEnter angle of Rhombus (in degrees): ";
        cin >> angle;
        angle = angle * M_PI / 180;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                RH[i][j] = 1;
            }
        }
        RH[0][0] = x;
        RH[0][1] = y;
        RH[1][0] = x + length;
        RH[1][1] = y;
        RH[2][0] = length + x + length * cos(angle);
        RH[2][1] = y + length * sin(angle);
        RH[3][0] = x + length * cos(angle);
        RH[3][1] = y + length * sin(angle);
        break;
    case 3:
        exit(0);
        break;
    default:
        printf("\nInvalid Input!");
        break;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D - TRANSFORMATIONS");
    glutDisplayFunc(Display);
    glutCreateMenu(Menu);
    glutAddMenuEntry("1.Translation", 1);
    glutAddMenuEntry("2.Scaling", 2);
    glutAddMenuEntry("3.Rotation", 3);
    glutAddMenuEntry("4.Shear", 4);
    glutAddMenuEntry("5.Reflection", 5);
    glutAddMenuEntry("6.EXIT", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

