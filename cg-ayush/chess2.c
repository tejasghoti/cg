#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include<math.h>

#define size 120
#define sqrsize 30

struct Point{
double x,y;
}p[16],p1[16],m;

struct Color{
float r,g,b;
};

void init(){
glClearColor(1.0,1.0,1.0,1.0);

glColor3f(0.0,0.0,0.0);
glPointSize(1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,640,0,480);
}

void mulMat(double matA[3][3],double (*res)[3],double op[3][3]){
double ans;
int i,j,k;
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
ans=0;
for(int k=0;k<3;k++)

{
ans+=op[i][k]*matA[k][j];
}
res[i][j]=ans;
}}

}
void rotate(double matA[3][3],double(*res)[3],double angle){
double op[3][3]={{cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1}};
mulMat(matA,res,op);
}
void translate(double matA[3][3],double(*res)[3],double x,double y){
double op[3][3]={{1,0,x},{0,1,y},{0,0,1}};
mulMat(matA,res,op);
}

void floodFill(double x,double y,Color c1){
Color c2;
glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c2);
if(c2.r!=0 || c2.g!=0 || c2.b!=0){
glBegin(GL_POINTS);
glColor3f(c1.r,c1.g,c1.b);
glVertex2i(x,y);
glEnd();

floodFill(x+1,y,c1);
floodFill(x-1,y,c1);
floodFill(x,y+1,c1);
floodFill(x,y-1,c1);
}
}

void colorchessboard(){
double res[3][3],res1[3][3],res2[3][3];
Color c1;
c1.r=0;
c1.g=0;
c1.b=0;

double matA[3][3]={{(p[0].x+p[4].x)/2,(p[5].x+p[6].x)/2,(p[4].x+p[5].x)/2},{(p[0].y+p[10].y)/2,(p[0].y+p[10].y)/2,(p[10].y+p[11].y)/2},{1,1,1}};
translate(matA,res,-m.x,-m.y);
rotate(res,res1,3.14159265/4);
translate(res1,res2,m.x,m.y);
floodFill(res2[0][0],res2[1][0],c1);
floodFill(res2[0][1],res2[1][1],c1);
floodFill(res2[0][2],res2[1][2],c1);

double matB[3][3]={{(p[6].x+p[1].x)/2,(p[0].x+p[4].x)/2,(p[5].x+p[6].x)/2},{(p[10].y+p[11].y)/2,(p[11].y+p[12].y)/2,(p[11].y+p[12].y)/2},{1,1,1}};
translate(matB,res,-m.x,-m.y);
rotate(res,res1,3.14159265/4);
translate(res1,res2,m.x,m.y);
floodFill(res2[0][0],res2[1][0],c1);
floodFill(res2[0][1],res2[1][1],c1);
floodFill(res2[0][2],res2[1][2],c1);

double matC[3][3]={{(p[4].x+p[5].x)/2,(p[6].x+p[1].x)/2,1},{(p[12].y+p[3].y)/2,(p[12].y+p[3].y)/2},{1,1,1}};
translate(matC,res,-m.x,-m.y);
rotate(res,res1,3.14159265/4);
translate(res1,res2,m.x,m.y);
floodFill(res2[0][0],res2[1][0],c1);
floodFill(res2[0][1],res2[1][1],c1);


}

void rotatechessboard(){
double res[3][3],res1[3][3],res2[3][3];

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.5,0.5,0.5);
glBegin(GL_LINES);
glColor3f(0,0,1);
glVertex2i(320,0);
glVertex2i(320,480);

glVertex2i(0,240);
glVertex2i(640,240);
glEnd();

double matA[3][3]={{p[0].x,p[1].x,p[2].x},{p[0].y,p[1].y,p[2].y},{1,1,1}};
translate(matA,res,-m.x,-m.y);
rotate(res,res1,3.14159265/4);
translate(res1,res2,m.x,m.y);
p1[0].x = res2[0][0];
	p1[0].y = res2[1][0];
	p1[1].x = res2[0][1];
	p1[1].y = res2[1][1];
	p1[2].x = res2[0][2];
	p1[2].y = res2[1][2];


//for points 3,4,5
	double matB[3][3] = {{p[3].x,p[4].x,p[5].x},{p[3].y,p[4].y,p[5].y},{1,1,1}};
	translate(matB,res,-m.x,-m.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,m.x,m.y);
	p1[3].x = res2[0][0];
	p1[3].y = res2[1][0];
	p1[4].x = res2[0][1];
	p1[4].y = res2[1][1];
	p1[5].x = res2[0][2];
	p1[5].y = res2[1][2];

//for points 6,7,8
	double matC[3][3] = {{p[6].x,p[7].x,p[8].x},{p[6].y,p[7].y,p[8].y},{1,1,1}};
	translate(matC,res,-m.x,-m.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,m.x,m.y);
	p1[6].x = res2[0][0];
	p1[6].y = res2[1][0];
	p1[7].x = res2[0][1];
	p1[7].y = res2[1][1];
	p1[8].x = res2[0][2];
	p1[8].y = res2[1][2];
	
	//for points 9,10,11
	double matD[3][3] = {{p[9].x,p[10].x,p[11].x},{p[9].y,p[10].y,p[11].y},{1,1,1}};
	translate(matD,res,-m.x,-m.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,m.x,m.y);
	p1[9].x = res2[0][0];
	p1[9].y = res2[1][0];
	p1[10].x = res2[0][1];
	p1[10].y = res2[1][1];
	p1[11].x = res2[0][2];
	p1[11].y = res2[1][2];
	
	//for points 12,13,14
	double matE[3][3] = {{p[12].x,p[13].x,p[14].x},{p[12].y,p[13].y,p[14].y},{1,1,1}};
	translate(matE,res,-m.x,-m.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,m.x,m.y);
	p1[12].x = res2[0][0];
	p1[12].y = res2[1][0];
	p1[13].x = res2[0][1];
	p1[13].y = res2[1][1];
	p1[14].x = res2[0][2];
	p1[14].y = res2[1][2];
	
	//for points 15
	double matF[3][3] = {{p[15].x,1,1},{p[15].y,1,1},{1,1,1}};
	translate(matF,res,-m.x,-m.y);
	rotate(res,res1,3.14159265/4);
	translate(res1,res2,m.x,m.y);
	p1[15].x = res2[0][0];
	p1[15].y = res2[1][0];
	
	
	glBegin(GL_LINE_LOOP);
	glColor3f(0,0,0);
	glVertex2i(p1[0].x,p1[0].y);
	glVertex2i(p1[1].x,p1[1].y);
		glVertex2i(p1[2].x,p1[2].y);
			glVertex2i(p1[3].x,p1[3].y);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0,0,0);

		glVertex2i(p1[4].x,p1[4].y);
		glVertex2i(p1[7].x,p1[7].y);
		
		glVertex2i(p1[5].x,p1[5].y);
		glVertex2i(p1[8].x,p1[8].y);

		glVertex2i(p1[6].x,p1[6].y);
		glVertex2i(p1[9].x,p1[9].y);

		glVertex2i(p1[10].x,p1[10].y);
		glVertex2i(p1[13].x,p1[13].y);

		glVertex2i(p1[11].x,p1[11].y);
		glVertex2i(p1[14].x,p1[14].y);

		glVertex2i(p1[12].x,p1[12].y);
		glVertex2i(p1[15].x,p1[15].y);
	glEnd();
	
	colorchessboard();//color the chessboard

	glFlush();
}

void drawchessboard()
{
	//initialize all the points of chessboard
	p[1].x = p[0].x+size;
	p[1].y = p[0].y;

	p[2].x = p[0].x+size;
	p[2].y = p[0].y+size;

	p[3].x = p[0].x;
	p[3].y = p[0].y+size;

	p[4].x = p[0].x+sqrsize;
	p[4].y = p[0].y;
	
	p[5].x = p[0].x+2*sqrsize;
	p[5].y = p[0].y;

	p[6].x = p[0].x+3*sqrsize;
	p[6].y = p[0].y;

	p[7].x = p[0].x+sqrsize;
	p[7].y = p[0].y+size;
	
	p[8].x = p[0].x+2*sqrsize;
	p[8].y = p[0].y+size;

	p[9].x = p[0].x+3*sqrsize;
	p[9].y = p[0].y+size;

	
	p[10].x = p[0].x;
	p[10].y = p[0].y+sqrsize;
	
	p[11].x = p[0].x;
	p[11].y = p[0].y+2*sqrsize;

	p[12].x = p[0].x;
	p[12].y = p[0].y+3*sqrsize;

	
	p[13].x = p[0].x+size;
	p[13].y = p[0].y+sqrsize;
	
	p[14].x = p[0].x+size;
	p[14].y = p[0].y+2*sqrsize;

	p[15].x = p[0].x+size;
	p[15].y = p[0].y+3*sqrsize;	
		
	m.x = (p[5].x);
	m.y = (p[11].y);

	//draw the initial chessboard
	glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
		glVertex2i(p[0].x,p[0].y);
		glVertex2i(p[1].x,p[1].y);
		glVertex2i(p[2].x,p[2].y);
		glVertex2i(p[3].x,p[3].y);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0,0,0);

		glVertex2i(p[4].x,p[4].y);
		glVertex2i(p[7].x,p[7].y);
		
		glVertex2i(p[5].x,p[5].y);
		glVertex2i(p[8].x,p[8].y);

		glVertex2i(p[6].x,p[6].y);
		glVertex2i(p[9].x,p[9].y);

		glVertex2i(p[10].x,p[10].y);
		glVertex2i(p[13].x,p[13].y);

		glVertex2i(p[11].x,p[11].y);
		glVertex2i(p[14].x,p[14].y);

		glVertex2i(p[12].x,p[12].y);
		glVertex2i(p[15].x,p[15].y);
	glEnd();
	//color the chessboard
	Color c1;
	c1.r = 0;
	c1.g = 0;
	c1.b = 0;		
	floodFill((p[0].x+p[4].x)/2,(p[0].y+p[10].y)/2,c1);
	floodFill((p[5].x+p[6].x)/2,(p[0].y+p[10].y)/2,c1);
	floodFill((p[4].x+p[5].x)/2,(p[10].y+p[11].y)/2,c1);
	floodFill((p[6].x+p[1].x)/2,(p[10].y+p[11].y)/2,c1);
	floodFill((p[0].x+p[4].x)/2,(p[11].y+p[12].y)/2,c1);
	floodFill((p[5].x+p[6].x)/2,(p[11].y+p[12].y)/2,c1);
	floodFill((p[4].x+p[5].x)/2,(p[12].y+p[3].y)/2,c1);
	floodFill((p[6].x+p[1].x)/2,(p[12].y+p[3].y)/2,c1);
	
	
}

void keyListener(unsigned char key,int x,int y){
if(key=='c'){
rotatechessboard();}
else if(key=='r'){
glutPostRedisplay();
}
}

void display()
{	
	//function to clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.5,0.5,0.5);
	

	//display axis
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex2i(320,0);
		glVertex2i(320,480);
	
		glVertex2i(0,240);
		glVertex2i(640,240);
	glEnd();	

	drawchessboard();	

	glFlush();
}

int main(int argc,char** argv){
printf("Enter x coordinate :\n");
scanf("%lf",&p[0].x);
p[0].x+=320;
printf("\nEnter y coordinate :\n");
scanf("%lf",&p[0].y);
p[0].y+=240;
glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE);//set the display mode with one buffer
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Chess Practice");
	init();
    	glutDisplayFunc(display);
	glutKeyboardFunc(keyListener);
    	glutMainLoop();//keep on rendering the window    
    	return 0;
}


