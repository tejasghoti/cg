
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include<GL/gl.h>

void display(){
   
    glClearColor(1.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -3, 3);



    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(0,50);
    glVertex2i(-50,-30);
    glVertex2i(50,-30);
    glEnd();


    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0,-50);
    glVertex2i(-50,30);
    glVertex2i(50,30);
    glEnd();


   
     glFlush();


}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,500);
    glutInitDisplayMode(GLUT_SINGLE);

    glutCreateWindow(" star");

    glutDisplayFunc(display);

    glutMainLoop();

}
