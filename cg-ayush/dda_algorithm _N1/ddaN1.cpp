#include<GL/freeglut.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std ;




void init()
{ 
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500,500,-500,500);

}

void plotpixel( float x , float y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();

}
void dda(float x1,float y1,float x2,float y2)
{
	float dx = x2-x1;
	float dy = y2-y1;
	float step ;
	float x = x1,y=y1;
	float xinc ,yinc;
	plotpixel(x1,y1);
	if(abs(dx)>abs(dy))
	{
		step = abs(dx);
		xinc = dx/(float)step;
		yinc = dy/(float)step;
		
	}
	else
	{
		step = abs(dy);
		xinc = dx/(float)step;
		yinc = dy/(float)step;
		
	}
	
	for(int i = 0; i < step ; i++)
	{
		x = x +	xinc;
		y = y + yinc;
		plotpixel(x,y);
	}
			
		

}

void display()
{
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2i(-500,0);
		glVertex2i(500,0);
		glVertex2i(0,-500);
		glVertex2i(0,500);
	glEnd();
	
	dda(-200,-200,-200, 200);
	dda(-200, 200, 200, 200);
	dda( 200, 200, 200,-200);
	dda( 200,-200,-200,-200);
	dda(-200,-200,-100,100);
	dda(-100,100,0,0);
	dda(0,0,100,100);
	dda(100,100,200,-200);
	
	glFlush();	
	
}



int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA pattern");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0 ;

}	
