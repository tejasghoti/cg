#include<GL/glu.h>
#include<GL/glut.h>
 int state =1;
void init()
{
   glClearColor(1.0,0.0,0.0,0.0);
   gluOrtho2D(-10,10,-10,10);
 }    
 float xposition=-10.0;
void display()
{
 
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glVertex2f(xposition,1.0);
glVertex2f(xposition,-1.0);
glVertex2f(xposition+2.0,-1.0);
glVertex2f(xposition+2.0,1.0);
glEnd();
glutSwapBuffers();

}
void timer(int)
{
glutPostRedisplay();   //redisplay of display
glutTimerFunc(1000/60, timer,0);
 
switch(state)
 {
   case 1:
        if(xposition<8)
        {
           xposition +=0.15;
         }
         else
           state=-1;
           break;
     case -1:
         if(xposition>-10)
            xposition-=0.15;
          else
            state=1;
            break;

}
}
int main(int argc, char** argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(200,100);
    glutCreateWindow("ANIMATION");
    glutDisplayFunc(display);
    glutTimerFunc(1000,timer,0);
    init();
    
    glutMainLoop();
    return 0;
}
