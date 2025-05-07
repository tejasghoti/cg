#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath> 

void displaypoint(int x,int y){
    glColor3f(0,0,1);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void dashedBSA(int x1,int y1,int x2,int y2){
   int dx=x2-x1;
   int dy=y2-y1;
   int x=x1;
   int y=y1;

   int x_change;
   if(x1<x2){
    x_change=1;
   }else{
    x_change=-1;
   }

   int y_change;
   if(y1<y2){
    y_change=1;
   }else{
    y_change=-1;
   }
   displaypoint(x,y);

   if(dx==0){
    for(int i=0;i<dy;i++){
        y+=y_change;
        displaypoint(x,y);
    }
    return;
   }
   if(dy==0){
    for(int i=0;i<dx;i++){
        x+=x_change;
        displaypoint(x,y);
    }
    return;
   }

   int p;
   if(dx>dy){
    p=2*dy-dx;
    for(int i=0;i<dx;i++){
        x+=x_change;
        if(p>0){
            y+=y_change;
            p+=2*(dy-dx);
        }else{
            p+=2*dy;
        }
        displaypoint(x,y);
    }
   }else{
    p+2*dx-dy;
    for(int i=0;i<dy;i++){
        y+=y_change;
        if(p>0){
            x+=x_change;
            p+=2*(dx-dy);
        }else{
            p+=2*dx;
        }
        displaypoint(x,y);
    }
   }
}

void initialize(void){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,600,600,0);
}

void renderfunction(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    dashedBSA(150,150,450,150);
    dashedBSA(450,150,450,450);
    dashedBSA(450,450,150,450);
    dashedBSA(150,450,150,150);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bresenham");
    initialize();
    glutDisplayFunc(renderfunction);
    glutMainLoop();
    return 0;
}
