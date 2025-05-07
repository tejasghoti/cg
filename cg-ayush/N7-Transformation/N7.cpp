#include<GL/freeglut.h>
#include<GL/gl.h>
#include<iostream>
#include<cmath>
using namespace std;
void display();


double original[4][3];
double transform[3][3];
double result[4][3];



void matrixmult()
{
          for(int i=0;i<4;i++)
	  {


		for (int j=0;j<3;j++)
		{
                  double sum=0;

                	for(int k=0;k<3;k++)
			{
                    		sum = sum + original[i][k]*transform[k][j];
                     
                        }
                    result[i][j]=sum;
                      


		}
          


          }

}


void translate(){
int tx,ty;
cout<<"Enter translational coordinates";
cin>>tx>>ty;
transform[0][0]=1;
transform[0][1]=0;
transform[0][2]=0;
transform[1][0]=0;
transform[1][1]=1;
transform[1][2]=0;
transform[2][0]=tx;
transform[2][1]=ty;
transform[2][2]=1;
matrixmult();

}
void rotateAC()
{

double a;

cin>>a;
double theta=a*(3.14/180);
transform[0][0]=cos(theta);
transform[0][1]=sin(theta);
transform[0][2]=0;
transform[1][0]=-sin(theta);
transform[1][1]=cos(theta);
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}

void rotateC()
{
double a;
cin>>a;
double theta=a*(3.14/180);
transform[0][0]=cos(theta);
transform[0][1]=-sin(theta);
transform[0][2]=0;
transform[1][0]=sin(theta);
transform[1][1]=cos(theta);
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}
void reflectXY()
{

transform[0][0]=0;
transform[0][1]=1;
transform[0][2]=0;
transform[1][0]=1;
transform[1][1]=0;
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}



void shearx()
{
double s;
cout<<"Enter shearing w.r.t x";
cin>>s;
transform[0][0]=1;
transform[0][1]=0;
transform[0][2]=0;
transform[1][0]=s;
transform[1][1]=1;
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}

void sheary()
{
double sheary;
cout<<"Enter shearing w.r.t y";
cin>>sheary;
transform[0][0]=1;
transform[0][1]=sheary;
transform[0][2]=0;
transform[1][0]=0;
transform[1][1]=1;
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}


void scale ()
{double sx,sy;
cout<<"Enter scaling coordinates";
cin>>sx>>sy;
transform[0][0]=sx;
transform[0][1]=0;
transform[0][2]=0;
transform[1][0]=0;
transform[1][1]=sy;
transform[1][2]=0;
transform[2][0]=0;
transform[2][1]=0;
transform[2][2]=1;
matrixmult();
}




void display (){

glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
        glVertex2i(original[0][0],original[0][1]);
	glVertex2i(original[1][0],original[1][1]);		
	glVertex2i(original[2][0],original[2][1]);
	glVertex2i(original[3][0],original[3][1]);	
glEnd();


glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
	glVertex2i(result[0][0],result[0][1]);
	glVertex2i(result[1][0],result[1][1]);
	glVertex2i(result[2][0],result[2][1]);
	glVertex2i(result[3][0],result[3][1]);
glEnd();
glFlush();






}



void goswitch(){

int c ;
cout<<"What do you want baby,I can satisfy you";
cin>>c;

switch (c) {
case 1 :
translate();
break;
case 2 :
rotateAC();
break;
case 3 :
rotateC();
break;
case 4 :
reflectXY();
break;
case 5 :
shearx();
break;
case 6 :
sheary();
break;
case 7 :
scale();
break;
default :
cout<<"Wrong Choice";
exit(0);

}



}











void userinput(){


     int x,y,w;
     cout<<"Enter elements of matrix";
     cin>>x>>y>>w;
    
	original[0][0]=x;
	original[0][1]=y;
	original[0][2]=1;
	original[1][0]=x;
	original[1][1]=y+w;
	original[1][2]=1;
	original[2][0]=x+w;
	original[2][1]=y+w;
	original[2][2]=1;	
	original[3][0]=x+w;
	original[3][1]=y;
	original[3][2]=1;


    goswitch();

}









void init(){

glClear(GL_COLOR_BUFFER_BIT);
glClearColor(0,0,0,0);
gluOrtho2D(-500,500,-500,500);

}











  
int main (int argc,char** argv){


glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE);
glutInitWindowSize(1000,1000);
glutInitWindowPosition(0,0);
glutCreateWindow("N7");
init();
userinput();

glutDisplayFunc(display);



glutMainLoop();
return 0;

}


