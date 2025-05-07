#include<iostream>
#include<cmath>
#include<GL/glut.h>
#include<GL/gl.h>
using namespace std;
int xmax=100,xmin=-100,ymax=100,ymin=-100;
float xa[3],ya[3];
float clippedx1[3],clippedx2[3],clippedy1[3],clippedy2[3];

int clippededges;
bool clipdone=false;

void displaypoint(float x,float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void dda(float x1,float y1,float x2,float y2)
{
    float dx=x2-x1;
    float dy=y2-y1;

    float steps;
    if(fabs(dx)>fabs(dy))
    {
        steps=fabs(dx);
    }
    else{
        steps=fabs(dy);
    }
    float xinc=dx/steps;
    float yinc=dy/steps;

    float x=x1,y=y1;

    for(int i=0;i<=steps;i++)
    {
        displaypoint(x,y);
        x=x+xinc;
        y=y+yinc;
    }
    glFlush();
}

int code(int x,int y)
{
    int c=0;
    if(y>ymax) c|=8;
    if(y<ymin) c|=4;
    if(x>xmax) c|=2;
    if(x<xmin) c|=1;

    return c;
}

void cohen(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m;
    if(x1!=x2)
    {
        m=(y2-y1)/(x2-x1);
    }
    else{m=0;}

    while((c1|c2)>0)
    {
        if((c1&c2)>0)
        {
            return;
        }
        int c=c1;
        float xi=x1;
        float yi=y1;
        float x,y;
        if(c==0)
        {
            c=c2;
            xi=x2;
            yi=y2;
        }

        if(c&8)
        {
            y=ymax;
            x=xi+(1.0/m)*(ymax-yi);
        }
        else if(c&4)
        {
            y=ymin;
            x=xi+(1.0/m)*(ymin-yi);
        }
        else if(c&2)
        {
            x=xmax;
            y=yi+m*(xmax-xi);
        }
        else
        {
            x=xmin;
            y=yi+m*(xmin-xi);
        }
        if(c==c1)
        {
            x1=x;
            y1=y;
            c1=code(x1,y1);
        }
        if(c==c2)
        {
            x2=x;
            y2=y;
            c2=code(x2,y2);
        }
    }
    clippedx1[clippededges]=x1;
    clippedx2[clippededges]=x2;
    clippedy1[clippededges]=y1;
    clippedy2[clippededges]=y2;

    clippededges++;
}

void keyboard(unsigned char c,int,int)
{
    if(c=='c')
    {
        clippededges=0;
        for(int i=0;i<3;++i)
        {
            int next=(i+1)%3;
            cohen(xa[i],ya[i],xa[next],ya[next]);
        }
    }
    clipdone=true;
    glutPostRedisplay();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window in red
    glColor3f(1.0f, 0.0f, 0.0f);
    dda(xmin, ymin, xmax, ymin);
    dda(xmax, ymin, xmax, ymax);
    dda(xmax, ymax, xmin, ymax);
    dda(xmin, ymax, xmin, ymin);

    if (!clipdone) {
        glColor3f(0.0f, 0.0f, 1.0f); // Blue for original triangle
        for (int i = 0; i < 3; ++i) {
            int next = (i + 1) % 3;
            dda(xa[i], ya[i], xa[next], ya[next]);
        }
    } else {
        glColor3f(0.0f, 0.6f, 0.0f); // Green for clipped lines
        for (int i = 0; i < clippededges; ++i) {
            dda(clippedx1[i], clippedy1[i], clippedx2[i], clippedy2[i]);
        }
    }

    glFlush();

}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    gluOrtho2D(-320, 320, -240, 240);
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Window coordinates are (-100, 100, -100, 100)\n";
    cout << "Enter 3 coordinates of triangle vertices (x y):\n";

    for (int i = 0; i < 3; ++i) {
        cout << "Vertex " << i + 1 << ":\nX: ";
        cin >> xa[i];
        cout << "Y: ";
        cin >> ya[i];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Triangle Line Clipping - Cohen Sutherland (C++)");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
