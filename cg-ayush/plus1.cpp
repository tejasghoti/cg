#include<iostream>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
using namespace std;

struct Color{
float r,g,b;
};

Color getPixelColor(float x,float y){
Color c;
glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c);
return c;
}

void setPixelColor(float x,float y){
glBegin(GL_POINTS);
   glColor3f(1.0,0.0,0.0);
   glVertex2f(x,y);
glEnd();
}

void floodFill(float x,float y){
Color c=getPixelColor(x,y);
Color old={1.0,1.0,1.0};
if(c.r==old.r && c.g==old.g && c.b==old.b){
setPixelColor(x,y);
floodFill(x+1,y);
floodFill(x-1,y);
floodFill(x,y-1);
floodFill(x,y+1);
}
glFlush();
}

void render(){
glClearColor(1.0,1.0,1.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,400,0,400);
glFlush();
}

void draw(){
glBegin(GL_LINES);

          glColor3f(0.0,0.0,0.0);//sets black color
                glVertex2d(100,150);
                glVertex2d(100,200);
                
                glVertex2d(100,200);
                glVertex2d(50,200);
                
                glVertex2d(50,200);
                glVertex2d(50,220);
                
                glVertex2d(50,220);
                glVertex2d(100,220);
                
                glVertex2d(100,220);
                glVertex2d(100,270);
                
                glVertex2d(100,270);
                glVertex2d(120,270);
                
                glVertex2d(120,270);
                glVertex2d(120,220);
                
                glVertex2d(120,220);
                glVertex2d(170,220);
                
                glVertex2d(170,220);
                glVertex2d(170,200);
                
                glVertex2d(170,200);
                glVertex2d(120,200);
                
                glVertex2d(120,200);
                glVertex2d(120,150);
                
                glVertex2d(120,150);
                glVertex2d(100,150);

glEnd();
floodFill(110,210);
glFlush();
}

void rotate(){
float y_tra=210 - (320/1.41);
glBegin(GL_LINES);
glColor3f(0.0,0.0,0.0);
glColor3f(0.0,0.0,0.0);//sets black color
                glVertex2d(400+(-50/1.41),250/1.41 + y_tra);
                glVertex2d(400+(-100/1.41),300/1.41 + y_tra);
                
                glVertex2d(400+(-100/1.41),300/1.41 + y_tra);
                glVertex2d(400+(-150/1.41),(250/1.41) + y_tra);
                
                glVertex2d(400+(-150/1.41),(250/1.41) + y_tra);
                glVertex2d(400+(-170/1.41),270/1.41 + y_tra);
                
                glVertex2d(400+(-170/1.41),270/1.41 + y_tra);
                glVertex2d(400 + (-120/1.41),320/1.41 + y_tra);
                
                glVertex2d(400 + (-120/1.41),320/1.41 + y_tra);
                glVertex2d(400 +(-170/1.41),370/1.41 + y_tra);
                
                glVertex2d(400 +(-170/1.41),370/1.41 + y_tra);
                glVertex2d(400+(-150/1.41),390/1.41 + y_tra);
                
                glVertex2d(400+(-150/1.41),390/1.41 + y_tra);
                glVertex2d(400+(-100/1.41),340/1.41 + y_tra);
                
                glVertex2d(400+(-100/1.41),340/1.41 + y_tra);
                glVertex2d(400+(-50/1.41),390/1.41 + y_tra);
                
                glVertex2d(400+(-50/1.41),390/1.41 + y_tra);
                glVertex2d(400+(-30/1.41),370/1.41 + y_tra);
                
                glVertex2d(400+(-30/1.41),370/1.41 + y_tra);
                glVertex2d(400+(-80/1.41),320/1.41 + y_tra);
                
                glVertex2d(400+(-80/1.41),320/1.41 + y_tra);
                glVertex2d(400+(-30/1.41),270/1.41 + y_tra);
                
                glVertex2d(400+(-30/1.41),270/1.41 + y_tra);
                glVertex2d(400+(-50/1.41),250/1.41 + y_tra);
        
glEnd();
floodFill(400 +(-100/1.41),(320/1.41)+y_tra);
glFlush();
}

int main(int argc, char** argv){
int e;
glutInit(&argc,argv);
glutInitWindowPosition(1000,200);
glutInitWindowSize(400,400);
glutCreateWindow("Plus Pracitce");
render();
do{
cout<<"Choose : \n1.Draw \n2.Rotate \n3.Exit"<<endl;
cout<<"Enter :"<<endl;
cin>>e;
switch(e){
case 1:
draw();
break;
case 2:
rotate();
break;
case 3:
exit(1);
break;
}
}while(e);
glutMainLoop();
return 0;
}

