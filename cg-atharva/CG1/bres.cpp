#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
using namespace std;

void displayPoint(int x,int y){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void displayBoldPoint(int x,int y){
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void BSA_Algo(int x1,int y1,int x2,int y2){
    int P;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1,y= y1;

    if(dx < 0){
        dx = -dx;
    }
    if(dy < 0){
        dy = -dy;
    }

    int x_chng = 1,y_chng = 1;

    if(x1 > x2){
        x_chng = -1;
    }
    if(y1 > y2){
        y_chng = -1;
    }

    // plotting (x1,y1)
    displayPoint(x,y);

    //if horizontal line
    if (dy == 0){
        for (int i = 1; i<dx; i++)
        {
        x = x + x_chng;
        displayPoint(x,y);
        }
        return;
    }

    //if vertical line
    if (dx == 0){
        for(int i = 1;i<dy;i++){
            y = y + y_chng;
            displayPoint(x,y);
        }
        return;
    }

    //if other than horizontal and vertical line
    if(dx > dy){
        P = 2*dy-dx;
        for(int i = 0;i<dx;i++){
            if(P > 0){
                y += y_chng;
                P = P + 2*(dy-dx);
            }
            else{
                P = P + 2*dy;
            }
            x += x_chng;
            displayPoint(x,y);
        }
    }
    else{
        P = 2*dx-dy;
        for(int i = 0;i<dy;i++){
            if(P > 0){
                x += x_chng;
                P = P + 2*(dx-dy);
            }
            else{
                P = P + 2*dx;
            }
            y += y_chng;
            displayPoint(x,y);
        } 
    }
}

void BSA_Dashed_Algo(int x1,int y1,int x2,int y2){
    int P;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1,y= y1;

    if(dx < 0){
        dx = -dx;
    }
    if(dy < 0){
        dy = -dy;
    }

    int x_chng = 1,y_chng = 1;

    if(x1 > x2){
        x_chng = -1;
    }
    if(y1 > y2){
        y_chng = -1;
    }

    // plotting (x1,y1)
    displayPoint(x,y);

    //if horizontal line
    if (dy == 0){
        for (int i = 1; i<dx; i++)
        {
            x = x + x_chng;
            if(i % 7 ==0 ){
                displayPoint(x,y);
            }
        }
        return;
    }

    //if vertical line
    if (dx == 0){
        for(int i = 1;i<dy;i++){
            y = y + y_chng;
            if(i % 7 ==0){
                displayPoint(x,y);
            }
        }
        return;
    }

    //if other than horizontal and vertical line
    if(dx > dy){
        P = 2*dy-dx;
        for(int i = 0;i<dx;i++){
            if(P > 0){
                y += y_chng;
                P = P + 2*(dy-dx);
            }
            else{
                P = P + 2*dy;
            }
            x += x_chng;
            if(i % 7 == 0){
                displayPoint(x,y);
            }
        }
    }
    else{
        P = 2*dx-dy;
        for(int i = 0;i<dy;i++){
            if(P > 0){
                x += x_chng;
                P = P + 2*(dx-dy);
            }
            else{
                P = P + 2*dx;
            }
            y += y_chng;
            if(i % 7 == 0){
                displayPoint(x,y);
            }
        } 
    }
}

void BSA_Dotted_Algo(int x1,int y1,int x2,int y2){
    int P;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1,y= y1;

    if(dx < 0){
        dx = -dx;
    }
    if(dy < 0){
        dy = -dy;
    }

    int x_chng = 1,y_chng = 1;

    if(x1 > x2){
        x_chng = -1;
    }
    if(y1 > y2){
        y_chng = -1;
    }

    // plotting (x1,y1)
    displayPoint(x,y);

    //if horizontal line
    if (dy == 0){
        for (int i = 1; i<dx; i++)
        {
            x = x + x_chng;
            if(i % 3 == 0){
                displayPoint(x,y);
            }
        }
        return;
    }

    //if vertical line
    if (dx == 0){
        for(int i = 1;i<dy;i++){
            y = y + y_chng;
            if(i % 3 ==0){
                displayPoint(x,y);
            }
        }
        return;
    }

    //if other than horizontal and vertical line
    if(dx > dy){
        P = 2*dy-dx;
        for(int i = 0;i<dx;i++){
            if(P > 0){
                y += y_chng;
                P = P + 2*(dy-dx);
            }
            else{
                P = P + 2*dy;
            }
            x += x_chng;
            if(i % 3 == 0){
                displayPoint(x,y);
            }
        }
    }
    else{
        P = 2*dx-dy;
        for(int i = 0;i<dy;i++){
            if(P > 0){
                x += x_chng;
                P = P + 2*(dx-dy);
            }
            else{
                P = P + 2*dx;
            }
            y += y_chng;
            if(i % 3 == 0){
                displayPoint(x,y);
            }
        } 
    }
}

void BSA_Solid_Algo(int x1,int y1,int x2,int y2){
    int P;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1,y= y1;

    if(dx < 0){
        dx = -dx;
    }
    if(dy < 0){
        dy = -dy;
    }

    int x_chng = 1,y_chng = 1;

    if(x1 > x2){
        x_chng = -1;
    }
    if(y1 > y2){
        y_chng = -1;
    }

    // plotting (x1,y1)
    displayBoldPoint(x,y);

    //if horizontal line
    if (dy == 0){
        for (int i = 1; i<dx; i++)
        {
        x = x + x_chng;
        displayBoldPoint(x,y);
        }
        return;
    }

    //if vertical line
    if (dx == 0){
        for(int i = 1;i<dy;i++){
            y = y + y_chng;
            displayBoldPoint(x,y);
        }
        return;
    }

    //if other than horizontal and vertical line
    if(dx > dy){
        P = 2*dy-dx;
        for(int i = 0;i<dx;i++){
            if(P > 0){
                y += y_chng;
                P = P + 2*(dy-dx);
            }
            else{
                P = P + 2*dy;
            }
            x += x_chng;
            displayBoldPoint(x,y);
        }
    }
    else{
        P = 2*dx-dy;
        for(int i = 0;i<dy;i++){
            if(P > 0){
                x += x_chng;
                P = P + 2*(dx-dy);
            }
            else{
                P = P + 2*dx;
            }
            y += y_chng;
            displayBoldPoint(x,y);
        } 
    }
}


void renderfunction(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
     glOrtho(-100,100,-100,100,-3,3);
    glColor3f(1.0,1.0,0.0);
    BSA_Algo(-300,0,300,0);
    BSA_Algo(0,-300,0,300);
    BSA_Algo(100,100,250,250);
    BSA_Dotted_Algo(-300,100,300,100);
    BSA_Dashed_Algo(-200,-100,200,-100);
    BSA_Solid_Algo(-100,200,100,200);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Assignment 2 Bre");
    
    glutDisplayFunc(renderfunction);
    glutMainLoop();
    return 0;
}


