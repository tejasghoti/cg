
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include<GL/gl.h>

void display(){
   
    glClearColor(0.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100,100,-100,100,-3,3);


    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0,70);
    glVertex2i(-40,0);
    glVertex2i(40,0);
    glEnd();


    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0,70);
    glVertex2i(-30,0);
    glVertex2i(30,0);
    glEnd();


    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0,40);
    glVertex2i(-60,-50);
    glVertex2i(60,-50);
    glEnd();

    glColor3f(1.0,0.5,0.6);
    glBegin(GL_QUADS);
    glVertex2i(-5,-50);
    glVertex2i(5,-50);
    glVertex2i(5,-90);
    glVertex2i(-5,-90);
    glEnd();


	glFlush();

}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,500);
    glutInitDisplayMode(GLUT_SINGLE);

    glutCreateWindow("tree ");

    glutDisplayFunc(display);

    glutMainLoop();

}
