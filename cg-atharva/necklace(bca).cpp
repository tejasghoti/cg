
#include <GL/glut.h>
#include<iostream>
#include <cmath>
int flag=0;
int R=30;
void plotpixel(int x,int y,int xc,int yc){
glColor3f(1,1,0);
glBegin(GL_POINTS);
glVertex2f(x+xc,y+yc);
glVertex2f(-x+xc,y+yc);
glVertex2f(x+xc,-y+yc);
glVertex2f(-x+xc,-y+yc);
glVertex2f(y+xc,x+yc);
glVertex2f(y+xc,-x+yc);
glVertex2f(-y+xc,-x+yc);
glVertex2f(-y+xc,x+yc);
glEnd();
}
void circle(int xc,int yc,int r){
int x=0;
int y=r;
int p=3-2*r;
while(x<=y){
        plotpixel(x,y,xc,yc);
if(p>=0){
    y--;
    p=p+4*(x-y)+10;
}
else if(p<0){
    p=p+4*x+6;
}
x++;

}
}
void necklace(){
        int n=6;
        for(int i=0;i<=n;i++){
            circle((35+i*20)*cos(45*M_PI/180),(-100+i*20)*sin(45*M_PI/180),R/3);
            circle((-35-i*20)*cos(45*M_PI/180),(-100+i*20)*sin(45*M_PI/180),R/3);

        }

}




void render(){
 glClearColor(0,0,0,0);
 glClear(GL_COLOR_BUFFER_BIT);
 glLoadIdentity();
 gluOrtho2D(-250,250,-250,250);

 if (flag==1){
    circle(0,-100,R);
    circle(0,-140,R/3);
    circle(-20,-136,R/3);
    circle(20,-136,R/3);
            necklace();

    if(flag==2){
    }
 }


glFlush();

}
void mouse(int button,int state,int x,int y){
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    if(flag==0){
            flag=1;

    }

 }

glutPostRedisplay();

}



int main(int argc,char ** argv){
    glutInit(&argc ,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("BCA");
    glutDisplayFunc(render);
    glutMouseFunc(mouse);
    glutMainLoop();
}
