/* Name -Shridhar Anil Vaidya
   Class-Se-11
   Batch-G11
   Roll no.-23351
   Problem Statement - WAP in Open Gl on linux platform to draw pattern of staircase by a line using DDA line algorithm.




*/



#include<GL/freeglut.h>
#include<GL/gl.h>
#include<iostream>
#include<cmath>
using namespace std ;
int x,y; //Global variables



// function to plot point 
void plotpixel(int x ,int y){ 

 glColor3f(1.0,0.0,0.0);
 glBegin(GL_POINTS);
 glVertex2i(x,y);
 glEnd();
 
}


// Digital differential analyser algorithm implmentation 
void DDA(float x1,float y1, float x2,float y2){
float dx =x2-x1;
float dy =y2-y1;
float x=x1;
float y=y1;
float step ;
float xinc ,yinc;
plotpixel(x,y);

if(abs(dx)>abs(dy)){
step = abs(dx);
xinc=dx/(float)step;
yinc=dy/(float)step;
for(int i=0;i<dx;i++){
    x=x+xinc;
    y=y+yinc;
   plotpixel(x,y);
    
}
   
}  
else  {
step = abs(dy);
xinc=dx/(float)step;
yinc=dy/(float)step;

for(int i=0;i<dy;i++){
    x=x+xinc;
    y=y+yinc;
   plotpixel(x,y);
    
}
  
}

}

void init(){
glClearColor(1.0,1.0,1.0,0.0);//setting color of display to white 
glClear(GL_COLOR_BUFFER_BIT);//clearing buffer 

gluOrtho2D(0,500,0,500);// LRBT i.e screen diplays for x in range (0,500) and y in range (0,500)

}

void RenderFunction(){
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES);
   glVertex2i(0,250);
   glVertex2i(500,250);
   glVertex2i(250,0);
   glVertex2i(250,500);
glEnd();
//calling DDA algorithm
DDA(260,260,460,260);
DDA(460,260,460,460);
DDA(260,260,260,300);
DDA(260,300,300,300);
DDA(300,300,300,340);
DDA(300,340,340,340);
DDA(340,340,340,380);
DDA(340,380,380,380);
DDA(380,380,380,420);
DDA(380,420,420,420);
DDA(420,420,420,460);
DDA(420,460,460,460);




glFlush();

}

//Main function 
int main (int argc,char** argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowPosition(100,100);//position of window
glutInitWindowSize(1000,1000);//size of window 
glutCreateWindow("mock");
init();
glutDisplayFunc(RenderFunction);
glutMainLoop();
return 0 ;
}



















