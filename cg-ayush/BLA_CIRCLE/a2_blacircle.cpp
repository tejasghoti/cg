#include<GL/freeglut.h>
#include<GL/gl.h>
#include<cmath>
#include<iostream>
using namespace std;





int r,xc,yc,R;

void setPixel(int x ,int y)
{ 
glBegin(GL_POINTS);
     glVertex2i(x,y);
glEnd();
}


void plotPixel(int xc,int yc,int x,int y){


        setPixel(xc+x, yc+y);
	setPixel(xc-x, yc+y);
	setPixel(xc+x, yc-y);
    	setPixel(xc-x, yc-y);
    	setPixel(xc+y, yc+x);
    	setPixel(xc-y, yc+x);
    	setPixel(xc+y, yc-x);
    	setPixel(xc-y, yc-x);

}


//Bresenham's Circle drawing alogorithm

void drawCircle(int xc,int yc, int r){
int x=0,y=r;
int d =3-2*r;
plotPixel(xc,yc,x,y);

 while(x<=y){
        x++;
        if(d<=0){
             
              d=d+4*x+6;
              y=y;

       }
           
        else
        {     d=d +4*(x-y) + 10 ;
              y=y-1;


        }

     plotPixel(xc,yc,x,y);     
  }

}





void renderFunction(){
glClearColor(1,1,1,0);
glColor3f(1.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity(); //
gluOrtho2D(0,500,0,500);//LRBT
glBegin(GL_LINES);
        glVertex2i(0,250);
        glVertex2i(500,250);
        glVertex2i(250,0);
        glVertex2i(250,500);
glEnd();

drawCircle(xc,yc,r);
drawCircle(xc,yc-r-R,R);
drawCircle(xc,yc-r-3*R,R);
glFlush();

}  

int main(int argc,char** argv){

      cout<<"Enter radius";
      cin>>r;
      cout<<"Enter xc";
      cin>>xc;
      cout<<"Enter yc";
      cin>>yc;
    
      cout<<"Enter R";
      cin>>R; 


     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE);
     glutInitWindowSize(1000,1000);
     glutInitWindowPosition(100,100);
     glutCreateWindow("Assignment_3");
     glutDisplayFunc(renderFunction);
     glutMainLoop();
     return 0 ;

}































