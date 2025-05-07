
#include <GL/freeglut.h>
#include <GL/gl.h>


void init()
{
glClearColor(0.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0.0,500.0,0,500.0);
}
void renderFunction() {

glColor3f(1.0,1.0,1.0);

glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,400);
    glVertex2f(500,400);
    glVertex2f(500,0);
glEnd();
glFlush();
}


int main (int argc , char** argv)

{ 

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL-First Window demo");
    init();
    glutDisplayFunc(renderFunction);
    glutMainLoop();
return 0;
}
    
