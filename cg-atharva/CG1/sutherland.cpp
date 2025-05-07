#include <GL/glut.h>
#include<iostream>
#include <vector>
using namespace std;
int xmin=-100;
int xmax=100;
int ymin=-100;
int ymax=100;

struct Point{
    float x,y;
};

vector<Point> polygon , clippedPolygon;

void drawpolygon(vector<Point> polygon , int r , int g, int b){

    glColor3f(r,g,b);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<polygon.size();i++){
        glVertex2f(polygon[i].x,polygon[i].y);
    }
    glEnd();

   glutPostRedisplay();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);

    //first step to draw polygon
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmin,ymax);
    glVertex2f(xmax,ymax);
    glVertex2f(xmax,ymin);

    glEnd();

    drawpolygon(polygon,1,1,0);
    if(!clippedPolygon.empty()){
        drawpolygon(polygon,1,1,1);
        drawpolygon(clippedPolygon,1,0,1);
    }
    
    glFlush();

}

void init(){
    glClearColor(1,1,1,0);
    gluOrtho2D(-250,250,-250,250);
}
void mouse(int button,int state, int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        Point p;
        p.x=x-250;
        p.y=250-y;
        polygon.push_back(p);

    }

    glutPostRedisplay();
}

Point intersect(Point p1 , Point p2 , int edge){
    Point p;  //intersection point

    float m;

    if((p2.x-p1.x)!=0){
        m=(p2.y-p1.y)/(p2.x-p1.x);
    }
    else{
        m=0;
    }

    switch(edge){
        case 0 :
        p.x=xmin;
        p.y=p1.y + m*(xmin-p1.x);
        break;

        case 1:
        p.x=xmax;
        p.y=p1.y + m*(xmax-p1.x);
        break;

        case 2:
        p.y=ymin;
        p.x=p1.x + (ymin-p1.y)/m;
        break;

        case 3 :
        p.y=ymax;
        p.x=p1.x + (ymax-p1.y)/m;
        break;
    }

    return p;
}

bool inside(Point p , int edge){
    switch(edge){
        case 0:return p.x>=xmin;
        break;

        case 1: return p.x<=xmax;
        break;

        case 2: return p.y >=ymin;
        break;

        case 3: return p.y<=ymax;
        break;
    }
    return true;
}
vector<Point> clipEdge(vector<Point> input , int edge){
    vector<Point> output;
    int n=input.size();
    for(int i=0;i<n;i++){
        Point curr=input[i];
        Point prev=input[(i+n-1)%n];


        bool currIn=inside(curr,edge);
        bool prevIn=inside(prev,edge);

        if(currIn && prevIn){
            output.push_back(curr);
        }else if(!currIn && prevIn){
            output.push_back(intersect(prev,curr,edge));
        }else if(currIn && !prevIn){
            output.push_back(intersect(prev,curr,edge));
            output.push_back(curr);
        }
}
    return output;

}

void clipPolygon(){
    clippedPolygon=polygon;
    for(int i=0;i<4;i++){
        clippedPolygon=clipEdge(clippedPolygon,i);
    }

    //glutPostRedisplay();
}
void keyboard(unsigned char key,int x,int y){
    if(key=='C' || key=='c'){
        clipPolygon();
    }
}
int main(int argc, char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Polygon Clipping");
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutMainLoop();

}
