#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

// Line struct with type
struct Line {
    int xs, ys, xe, ye;
    char type; // 'a' for simple, 'b' for dotted, 'c' for dashed, 'd' for solid
};

vector<Line> lines; // Store all drawn lines
int flag = 0;       // To track clicks
int x1, y1, x2, y2; // Temporary coordinates for new line

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

// Redraw everything
void render() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    glColor3f(1, 1, 1); // Set color to white

    // Draw axes
    BLA(0, 250, 0, -250);
    BLA(-250, 0, 250, 0);

    // Draw all lines
    for (auto l : lines) {
        switch (l.type) {
            case 'a': case 'A': BLA(l.xs, l.ys, l.xe, l.ye); break;
            case 'b': case 'B': dotted_BLA(l.xs, l.ys, l.xe, l.ye); break;
            case 'c': case 'C': dashed_BLA(l.xs, l.ys, l.xe, l.ye); break;
            case 'd': case 'D': solid_BLA(l.xs, l.ys, l.xe, l.ye); break;
        }
    }

    glFlush();
}

// Track two mouse clicks to get line
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        if (flag == 0) {
            x1 = x - 250;
            y1 = 250 - y;
            cout << "Start: (" << x1 << "," << y1 << ")" << endl;
            flag = 1;
        } else if (flag == 1) {
            x2 = x - 250;
            y2 = 250 - y;
            cout << "End: (" << x2 << "," << y2 << ")" << endl;
            flag = 0;
            cout << "Now press a key:\nA - Simple\nB - Dotted\nC - Dashed\nD - Solid\n";
        }
    }
}

// Keyboard: choose line type after 2nd click
void keyboard(unsigned char key, int x, int y) {
    if (flag == 0 && (key == 'a' || key == 'b' || key == 'c' || key == 'd' ||
                      key == 'A' || key == 'B' || key == 'C' || key == 'D')) {
        // Store the new line with type
        lines.push_back({ x1, y1, x2, y2, key });
        glutPostRedisplay();
    } else {
        cout << "Please select start and end point using mouse first.\n";
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BLA Line Drawing with Keyboard Line Type");
    glutDisplayFunc(render);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
