#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
using namespace std;

void displayPoint(int x,int y){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}


void displayBoldPoint(int x,int y){
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}


void SimpleLine(float x1,float y1,float x2,float y2){
    float step;

    float dy = y2-y1;
    float dx = x2-x1;

    if(abs(dx) < abs(dy)){
        step = dy;
    }
    else{
        step = dx;
    }

    float xin = dx/(float)step;
    float yin = dy/(float)step;

    float x = x1;
    float y = y1;

    for(int i = 0;i<=step;i++){
        displayPoint(x,y);
        x = x + xin;
        y = y + yin;
    }

    glFlush();
}

void BoldLine(float x1,float y1,float x2,float y2){
    float step;

    float dy = y2-y1;
    float dx = x2-x1;

    if(abs(dx) < abs(dy)){
        step = dy;
    }
    else{
        step = dx;
    }

    float xin = dx/(float)step;
    float yin = dy/(float)step;

    float x = x1;
    float y = y1;

    for(int i = 0;i<=step;i++){
        displayBoldPoint(x,y);
        x = x + xin;
        y = y + yin;
    }

    glFlush();
}


void DottedLine(float x1, float y1, float x2 ,float y2){
    float step ;

    float dx = x2-x1;
    float dy = y2-y1;

    if(abs(dx) >abs(dy)){
        step = abs(dx);
    }
    else step = abs(dy);

    float Xinc = dx/(float) step;
    float Yinc = dy/ (float)step;
    float x = x1;
    float y = y1;
    displayPoint(x,y);

    for(int i=0 ; i<=step ;i++){
        x= x + Xinc;
        y= y + Yinc;
        if(i % 3 ==0 ){
            displayPoint(x,y);
        }
    }
    glFlush();
}
void DashedLine(float x1, float y1, float x2 ,float y2){
    float step ;

    float dx = x2-x1;
    float dy = y2-y1;

    if(abs(dx) >abs(dy)){
    step = abs(dx);
    }
    else step = abs(dy);

    float Xinc = dx/(float) step;
    float Yinc = dy/ (float)step;
    float x = x1;
    float y = y1;
    displayPoint(x,y);

    for(int i=0 ; i<=step ;i++){

        x= x + Xinc;
        y= y + Yinc;
        if(i % 6>3 ){
        displayPoint(x,y);
        }
    }
    glFlush();
}

void initialise(void){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,600,600,0);
}

void renderfunction(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    SimpleLine(300,0,300,600);
    SimpleLine(0,300,600,300);

    SimpleLine(100,100,250,250);
    DottedLine(150,200,250,300);
    DashedLine(40,30,250,100);
    BoldLine(10,20,100,250);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("DDA");
    initialise();
    glutDisplayFunc(renderfunction);
    glutMainLoop();
    return 0;
}


