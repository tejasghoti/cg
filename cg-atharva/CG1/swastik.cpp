#include<GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>

struct Pixel{
    GLubyte r,g,b;
};

Pixel F = {225,0,0};
Pixel B = {0,0,0};

void displayPoint(int x , int y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void setPixelColor(int x , int y , Pixel color){
    glColor3ub(color.r , color.g , color.b);
    displayPoint(x,y);
    glFlush();

}

Pixel getPixelColor(int x , int y){
    Pixel pixel;
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&pixel);
    return pixel;
}

bool isdifferent(Pixel a , Pixel b){
    return (a.r!=b.r || a.g!= b.g || a.b!= b.b);
}


void boundaryfillalgo(int x , int y , Pixel fillcolor , Pixel boundarycolor){
    Pixel current = getPixelColor(x,y);
    if(isdifferent(current , fillcolor) && isdifferent(current , boundarycolor)){
        setPixelColor(x,y,fillcolor);
        boundaryfillalgo(x+1 , y , fillcolor , boundarycolor);
        boundaryfillalgo(x , y+1 , fillcolor , boundarycolor);
        boundaryfillalgo(x-1 , y , fillcolor , boundarycolor);
        boundaryfillalgo(x , y-1 , fillcolor , boundarycolor);

    }
}


void DDA_simpleLine(float xi , float yi , float xf , float yf){
    float dx = xf-xi;
    float dy = yf-yi;
    float step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float x_change = dx/step , y_change = dy/step;
    float x = xi , y = yi;

    for (int i=0 ; i<=step ; i++){
        displayPoint(x,y);
        x += x_change;
        y += y_change;
    }
    glFlush();
}

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,500,0,500);
}

void renderFunc(){

    glColor3f(0,0,0);
    DDA_simpleLine(50, 50, 100, 50);
    DDA_simpleLine(100, 50, 100, 200);
    DDA_simpleLine(100, 200, 200, 200);
    DDA_simpleLine(250, 200, 400, 200);
    DDA_simpleLine(400, 200, 400, 400);
    DDA_simpleLine(400, 400, 350, 400);
    DDA_simpleLine(350, 400, 350, 250);
    DDA_simpleLine(350, 250, 250, 250);
    DDA_simpleLine(200, 250, 50, 250);
    DDA_simpleLine(50, 250, 50, 50);


    DDA_simpleLine(50, 350, 200, 350);
    DDA_simpleLine(200, 350, 200, 50);
    DDA_simpleLine(200, 50, 400, 50);
    DDA_simpleLine(400, 50, 400, 100);
    DDA_simpleLine(400, 100, 250, 100);
    DDA_simpleLine(250, 100, 250, 400);
    DDA_simpleLine(250, 400, 50, 400);
    DDA_simpleLine(50, 400 , 50 ,350);

    glFlush();
}

void myMouse(int button, int state, int x, int y) {
    y = 500 - y; // Invert Y for OpenGL coordinates

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Adjust these ranges to the actual inside area of the swastik
        if (x > 50 && x < 400 && y > 50 && y < 400) {
            boundaryfillalgo(x, y, F, B);
        }
    }
}

int main (int argc , char** argv){
    glutInit(&argc , argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE);
    glutCreateWindow("HOLA");
    init();
    glutDisplayFunc(renderFunc);
    glutMouseFunc(myMouse);
    glutMainLoop();
}


