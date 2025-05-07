#include<GL/freeglut.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>

using namespace std ;

int xc,yc ,r;


void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500,500,-500,500);
	
}

void plotpixel(int xc, int yc,int x, int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(xc+x,yc+y);
		glVertex2i(xc-x,yc+y);
		glVertex2i(xc+x,yc-y);
		glVertex2i(xc-x,yc-y);
		glVertex2i(xc+y,yc+x);
		glVertex2i(xc+y,yc-x);
		glVertex2i(xc-y,yc+x);
		glVertex2i(xc-y,yc-x);
	glEnd();
	

}
void bca(int xc ,int yc ,int r )
{
	int x=0 ,y=r;
	int d = 3-2*r;
	plotpixel(xc,yc,x,y);
	while(x<=y)
	{	
		x++;
		if(d<=0)
		{
			d=d+4*x+6;
			y=y;
		}
		else
		{
			d=d+4*(x-y)+10;
			y=y-1;
		}
						
		plotpixel(xc,yc,x,y);
	}	


}


void display()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2i(-500,0);
		glVertex2i( 500,0);
		glVertex2i( 0,-500);
		glVertex2i( 0, 500);
	glEnd();
	bca(0,0,200);
	bca(0,0,150);
	int angle = 0;
	int x = 0,y= 220 ;
	bca(x,y,20);
	int R = 220 ;
	//x=R*cos(angle*(3.14/180));
	//y=-R*sin(angle*(3.14/180));
	for (int i = 0;i<36;i++)
	{
		
				
		angle = angle + 10;
		x=R*cos(angle*(3.14/180));
		y=-R*sin(angle*(3.14/180));
		//x = x*(cos(angle*(3.14f/180))) + y*(sin(angle*(3.14f/180))) ;
		//y =  (-1)*x*(sin(angle*(3.14f/180))) + y*(cos(angle*(3.14f/180))) ;
		bca(x,y,20);
	}	
		
	glFlush();
		
}




int main (int argc , char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("bangle");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0 ;
}	
