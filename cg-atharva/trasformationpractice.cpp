#include<GL/glut.h>
#include <bits/stdc++.h>
using namespace std;


vector<vector<double>>polygon;

void draw(vector<vector<double>> matrix) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < matrix.size(); i++) {
        glVertex2f(matrix[i][0], matrix[i][1]);
    }
    glEnd();
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
void scaling(vector<vector<double>> mat) {
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
void shearing(vector<vector<double>> mat) {
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
    glColor3f(1.0, 0.5, 1.0);
    draw(result);
}
void delay(int time){
for(int i=0;i<time;i++){
for(int j=0;j<5000;j++){

}


}
}





void display(){
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2d(-250, 0);
    glVertex2d(250, 0);
    glVertex2d(0, -250);
    glVertex2d(0, 250);
    glEnd();
    draw(polygon);
    glFlush();
}

void menu(int option){
    switch(option){
    case 1:
        translation(polygon);
        delay(300);
        break;
    case 2:
        scaling(polygon);
        delay(300);
        break;
    case 3:
        rotation(polygon);
        delay(300);
        break;
    case 4:
        shearing(polygon);
        delay(300);
        break;
    case 5:
        reflection(polygon);
        delay(300);
        break;



    }

glFlush();
}
void mouse(int button,int state,int x,int y){
if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN){
    float xs=x-250;
    float ys=250-y;
    polygon.push_back({xs,ys,1});

}
glutPostRedisplay();

}






int main(int argc , char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Transformation");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation",1);
    glutAddMenuEntry("Scaling",2);
    glutAddMenuEntry("Rotation",3);
    glutAddMenuEntry("Shearing",4);
    glutAddMenuEntry("Reflection",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;

}
