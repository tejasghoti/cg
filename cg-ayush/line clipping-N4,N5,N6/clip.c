#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

int xmin=-100;int ymin=-100;int xmax=100;int ymax=100;
float xd1;float xd2;float yd1;float yd2;
void display();


void initialize()
{
	glClearColor(1.0,1.0,0,0);		
	glClear(GL_COLOR_BUFFER_BIT);		
	glPointSize(2);						
	gluOrtho2D(-300,300,-300,300);								
	glFlush();
	
}

int get_code(int x,int y){
    int c=0;
    if(y>ymax) c=c|8;
    if(y<ymin) c=c|4;
    if(x>xmax) c=c|2;
    if(x<xmin) c=c|1;
    return c;
}

void cohen(float x1,float y1,float x2,float y2){
    int c1=get_code(x1,y1);
    int c2=get_code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    
    while((c1|c2)>0){
       if(c1&c2==0){
       return;
       }

       int c ;
       if(c1){
         c=c1;
       }else{
         c=c2;
        }
       float x;float y;
       if((c&8)!=0){
          y=ymax;
	
	
          x=x1+(1.0/m)*(ymax-y1);
       }
       if((c&4)!=0){
          y=ymin;
          x=x1+(1.0/m)*(ymin-y1);
       }
       if((c&2)!=0){
          x=xmax;
          y=y1+m*(xmax-x1);
       }
       if((c&1)!=0){
          x=xmin;
          y=y1+m*(xmin-x1);
       }
       if(c==c1){
         xd1=x;
         yd1=y;
         c1=get_code(xd1,yd1);
       }
       if(c==c2){
         xd2=x;
         yd2=y;
         c2=get_code(xd2,yd2);
       }
    }
   display(); 
}

void myKey(unsigned char ch,int x,int y){
   if(ch=='c'){
      glutPostRedisplay();		
      cohen(xd1,yd1,xd2,yd2);
      glFlush();
   }
}

void plotpoint(float a, float b)
{
	glBegin(GL_POINTS);
	glVertex2f(a,b);
	glEnd();
}

void dda(float x1, float y1, float x2, float y2)
{
	float x,y,dx,dy,xinc,yinc;
	int steps;
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy)){
	   steps=abs(dx);
	}else{
	   steps=abs(dy);
	}
	   xinc=dx/float(steps);
	   yinc=dy/float(steps);
	   x=x1;y=y1;
	   plotpoint(x,y);
	for(int i=0;i<steps;i++){
	  x=x+xinc;
	  y=y+yinc;
	  plotpoint(x,y);
	}
	glFlush();
}

void display(){
     glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);				
	dda(xmin,ymin,xmax,ymin);			
	dda(xmax,ymin,xmax,ymax);
	dda(xmax,ymax,xmin,ymax);
	dda(xmin,ymax,xmin,ymin);
	
	glColor3f(0.0,0.0,1.0);				
	dda(xd1,yd1,xd2,yd2);	
	glEnd();			
	glFlush();
}

int main(int argC,char **argV){
  xd1=-240;yd1=-120;xd2=240,yd2=120;
  glutInit(&argC,argV);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(600,600);
  glutCreateWindow("cohen-Sutherland Algorithm");
  initialize();
  display();
  glutKeyboardFunc(myKey);
  glutMainLoop();
  return 0; 
}
