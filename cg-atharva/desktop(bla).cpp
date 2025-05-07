#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;


int flag=0;
void displaypoint(float x,float y){
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
		glVertex2f(x,y);

	glEnd();
}
void BLA(int xs, int ys,int xe,int ye){
	int p;
	int dx=abs(xe-xs);
	int dy=abs(ye-ys);
	int x=xs;
	int y=ys;
	int xinc=1;
	int yinc=1;
	if(xs>xe){
		xinc=-1;
	}
	if(ys>ye){
		yinc=-1;
	}
	displaypoint(x,y);
	if(dx==0){
		for(int i=0;i<dy;i++){
			y=y+yinc;
			displaypoint(x,y);

		}
		return;
	}
	if(dy==0){
		for(int i=0;i<dx;i++){
			x=x+xinc;
			displaypoint(x,y);
		}
		return;
	}
	if(dx>dy){
		p=2*dy-dx;
		for(int i=0;i<dx;i++){
			if(p>0){
				y=y+yinc;
				p=p+2*(dy-dx);

			}else{
				p=p+2*dy;
			}
			x=x+xinc;
			displaypoint(x,y);
		}
	}else{
		p=2*dx-dy;
		for(int i=0;i<dy;i++){
			if(p>0){
				x=x+xinc;
				p=p+2*(dx-dy);

			}else{
				p=p+2*dx;
			}
			y=y+yinc;
			displaypoint(x,y);
		}
	}



}
void  dotted_BLA(int xs, int ys,int xe,int ye){
	int p;
	int dx=abs(xe-xs);
	int dy=abs(ye-ys);
	int x=xs;
	int y=ys;
	int xinc=1;
	int yinc=1;
	if(xs>xe){
		xinc=-1;
	}
	if(ys>ye){
		yinc=-1;
	}
	displaypoint(x,y);
	if(dx==0){
		for(int i=0;i<dy;i++){
			y=y+yinc;
			if(i%3==0){
				displaypoint(x,y);
			}


		}
		return;
	}
	if(dy==0){
		for(int i=0;i<dx;i++){
			x=x+xinc;
			if(i%3==0){
				displaypoint(x,y);
			}
		}
		return;
	}
	if(dx>dy){
		p=2*dy-dx;
		for(int i=0;i<dx;i++){
			if(p>0){
				y=y+yinc;
				p=p+2*(dy-dx);

			}else{
				p=p+2*dy;
			}
			x=x+xinc;
			if(i%3==0){
				displaypoint(x,y);
			}
		}
	}else{
		p=2*dx-dy;
		for(int i=0;i<dy;i++){
			if(p>0){
				x=x+xinc;
				p=p+2*(dx-dy);

			}else{
				p=p+2*dx;
			}
			y=y+yinc;
			if(i%3==0){
				displaypoint(x,y);
			}
		}
	}



}
void  dashed_BLA(int xs, int ys,int xe,int ye){
	int p;
	int dx=abs(xe-xs);
	int dy=abs(ye-ys);
	int x=xs;
	int y=ys;
	int xinc=1;
	int yinc=1;
	if(xs>xe){
		xinc=-1;
	}
	if(ys>ye){
		yinc=-1;
	}
	displaypoint(x,y);
	if(dx==0){
		for(int i=0;i<dy;i++){
			y=y+yinc;
			if(i%15!=0){
				displaypoint(x,y);
			}


		}
		return;
	}
	if(dy==0){
		for(int i=0;i<dx;i++){
			x=x+xinc;
			if(i%15!=0){
				displaypoint(x,y);
			}
		}
		return;
	}
	if(dx>dy){
		p=2*dy-dx;
		for(int i=0;i<dx;i++){
			if(p>0){
				y=y+yinc;
				p=p+2*(dy-dx);

			}else{
				p=p+2*dy;
			}
			x=x+xinc;
			if(i%15!=0){
				displaypoint(x,y);
			}
		}
	}else{
		p=2*dx-dy;
		for(int i=0;i<dy;i++){
			if(p>0){
				x=x+xinc;
				p=p+2*(dx-dy);

			}else{
				p=p+2*dx;
			}
			y=y+yinc;
			if(i%15!=0){
				displaypoint(x,y);
			}
		}
	}



}

void displaypoint1(float x,float y){
	glColor3f(1.0,1.0,1.0);
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2f(x,y);

	glEnd();
	glPointSize(1);
}
void solid_BLA(int xs, int ys,int xe,int ye){
	int p;
	int dx=abs(xe-xs);
	int dy=abs(ye-ys);
	int x=xs;
	int y=ys;
	int xinc=1;
	int yinc=1;
	if(xs>xe){
		xinc=-1;
	}
	if(ys>ye){
		yinc=-1;
	}
	displaypoint1(x,y);
	if(dx==0){
		for(int i=0;i<dy;i++){
			y=y+yinc;
			displaypoint1(x,y);

		}
		return;
	}
	if(dy==0){
		for(int i=0;i<dx;i++){
			x=x+xinc;
			displaypoint1(x,y);
		}
		return;
	}
	if(dx>dy){
		p=2*dy-dx;
		for(int i=0;i<dx;i++){
			if(p>0){
				y=y+yinc;
				p=p+2*(dy-dx);

			}else{
				p=p+2*dy;
			}
			x=x+xinc;
			displaypoint1(x,y);
		}
	}else{
		p=2*dx-dy;
		for(int i=0;i<dy;i++){
			if(p>0){
				x=x+xinc;
				p=p+2*(dx-dy);

			}else{
				p=p+2*dx;
			}
			y=y+yinc;
			displaypoint1(x,y);
		}
	}



}
void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(flag == 0){
            flag = 1;
        } else if (flag == 1) {
            flag = 2;
        }
        glutPostRedisplay(); // request to re-render
    }
}


void render() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    if (flag >= 1) {
        BLA(0, 250, 0, -250); // Y axis
        BLA(-250, 0, 250, 0); // X axis
    }

    if (flag >= 2) {
        BLA(100,100,-100,100);
        BLA(100,100,100,-100);
        BLA(-100,100,-100,-100);
        BLA(-100,-100,100,-100);

        dashed_BLA(80,80,-80,80);
        dashed_BLA(80,80,80,-80);
        dashed_BLA(-80,80,-80,-80);
        dashed_BLA(-80,-80,80,-80);

        solid_BLA(0,-100,-25,-125);
        solid_BLA(-25,-125,25,-125);
        solid_BLA(0,-100,25,-125);
    }

    glFlush();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BLA Line Drawing with Keyboard Line Type");
    glutDisplayFunc(render);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

