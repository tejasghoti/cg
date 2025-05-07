#include <GL/freeglut.h> // Handles window, input, etc.
#include <GL/gl.h>        // Core OpenGL commands

#include <GL/freeglut.h>
#include <GL/gl.h>

void display(){
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);

    // Red Line
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(-100.0, -100.0);
        glVertex2f(100.0, 100.0);
    glEnd();

    // Magenta Line
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);#include <GL/freeglut.h>
#include <GL/gl.h>
void renderFunction()

{
glClearColor(0.6, 0.7, 0.4, 0.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 1.0, 1.0);
glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
glBegin(GL_POLYGON);
glVertex2f(-0.3, 0.2);
glVertex2f(-0.3, 0.6);
glVertex2f(-0.8, 0.6);
glVertex2f(-0.8, 0.2);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(0.5, -0.1);
glVertex2f(0.3, -0.3);
glVertex2f(0.3, -0.6);
glVertex2f(0.7,-0.6);
glVertex2f(0.7, -0.3);
glEnd();
glFlush();
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("OpenGL - First window demo");
glutDisplayFunc(renderFunction);
glutMainLoop();
return 0;
}


        glVertex2f(-100.0, 100.0);
        glVertex2f(100.0, -100.0);
    glEnd();

    glFlush();
}

int main(int argc , char** argv){
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_SINGLE);
	
	glutCreateWindow("my first cg program");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100); 
	
	glutDisplayFunc(display);
	
	glutMainLoop();
	
	}
	
