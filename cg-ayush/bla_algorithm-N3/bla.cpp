
#include<GL/freeglut.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std ;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500,500,-500,500);
}

void plotpixel(int x , int y)
{	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
			 
}
void bla(int x1,int y1, int x2,int y2)
{
	int p ;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x = x1 ,y = y1;
	if(dx<0)
	{	
		dx=-dx;
	}
	if(dy<0)
	{
		dy=-dy;
	}
	int x_change=1,y_change=1;
	if(x1>x2)
	{
		x_change = -1 ;
	}
	if(y1>y2)
	{
		y_change = -1;
	}
	plotpixel(x,y);
	
	if(dx>dy)
	{
		p=2*dy-dx;
		for (int i = 0;i<dx ;i++)
		{
			if(p>0)
			{
				y= y + y_change;
				p=p + 2*(dy-dx);
			}
			else 
			{
				p = p +2*dy;
			}
			x = x + x_change;
			plotpixel(x,y);
		}								
	}
	else
	{
		p=2*dx-dy;
		for (int i = 0;i<dy ;i++)
		{
			if(p>0)
			{
				x= x + x_change;
				p=p + 2*(dx-dy);
			}
			else 
			{
				p = p +2*dx;
			}
			y = y + y_change;
			plotpixel(x,y);
		}
	}
		
	 	
}

void renderfunction()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2i(-500,0);
		glVertex2i( 500,0);
		glVertex2i( 0,-500);
		glVertex2i( 0, 500);
	glEnd();
	
	bla(-100,-200,-100,200);
	bla(-100,200,100,200);
	bla(100,200,100,-200);
	bla(-100,-200,-50,-200);
	bla(100,-200,50,-200);
	bla(-50,-200,-80,-230);
	bla(50,-200,80,-230);
	bla(-80,-230,80,-230);
	
	bla(-80,-100,-80,100);
	bla(-80,100,80,100);
	bla(80,100,80,-100);
	bla(80,-100,-80,-100);
	bla(-80,-100,-40,-50);
	bla(-40,-50,0,-100);
	bla(0,-100,40,-20);
	bla(40,-20,80,-100);
	
	glFlush();
	
			
}

int main (int argc ,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("BLA");
	init();
	glutDisplayFunc(renderfunction);
	glutMainLoop();
	return 0;
}	
