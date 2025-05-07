#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>
#include<iostream>
using namespace std;
#define torad (3.14/180)  
int n;
void plotpixel(float x1, float y1,float x2,float y2){

glColor3f(1.0,0.0,0.0);
   glBegin(GL_LINES);
     glVertex2i(x1,y1);
     glVertex2i(x2,y2);   
   glEnd();
   

}


void koch(float x1,float y1,float x2,float y2,int n){
   float x3 = (2*x1 + x2)/3 ;
   float y3 = (2*y1 + y2)/3 ;   
   float x4 = (x1 + 2*x2)/3 ;
   float y4 = (y1 + 2*y2)/3 ;
   

   int x =x3 + (x4-x3)*(cos(60*(3.14/180))) +(y4-y3)*(sin(60*(3.14/180)));    
   int y =y3 - (x4-x3)*(sin(60*(3.14/180))) +(y4-y3)*(cos(60*(3.14/180)));

  if(n>0){
            koch(x1,y1,x3,y3,n-1);
            koch(x3,y3,x,y,n-1);
            koch(x,y,x4,y4,n-1);
            koch(x4,y4,x2,y2,n-1);


} 


else 
	{

plotpixel(x1,y1,x2,y2);

}

}
void init(){

glClear(GL_COLOR_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,1000,0,1000);//LRBT


}

void Renderfunction(){

glColor3f(1.0,0.0,0.0);
  glBegin(GL_LINES);
	koch(600,100,800,400,n);
	koch(800,400,400,400,n);
	koch(400,400,600,100,n);
	glEnd();
   glFlush();
 



}


int main (int argc,char** argv){

      
      
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE);
     glutInitWindowSize(1000,1000);
     glutInitWindowPosition(0,0);
     glutCreateWindow("koch");
     init();
     cout<< "Enter no of iteration ";
     cin>>n;
     glutDisplayFunc(Renderfunction);
     glutMainLoop();
     return 0;

}
