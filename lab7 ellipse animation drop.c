#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define UP 8
#define DOWN 4
#define RIGHT 2
#define LEFT 1

#define SWAP(x,y) { int temp=x; x=y; y=temp; }

unsigned int lines = 0;
int XMAX=200,XMIN=-200,YMAX=200,YMIN=-200;

int offsetx=0,offsety=0;

int getSlope(int x0,int y0,int x1,int y1) {
	int dx=x1-x0;
	int dy=y1-y0;
	if(abs(dx)>=abs(dy))
		if(dx>=0)
			if(dy>=0) return 0;
			else return 7;
		else {
			if(dy>=0) return 3;
			else return 4;
		}
	else {
		if(dx>=0)
			if(dy>=0) return 1;
			else return 6;
		else {
			if(dy>=0) return 2;
			else return 5;
		}
	}
}

void pointSwapper(int *x0,int *y0,int *x1,int *y1,int slope)
{
	int temp;
	switch(slope)
	{
		case 0:
		break;
		case 1:
		temp = *y1; *y1 = *x1; *x1 = temp;
		temp = *y0; *y0 = *x0; *x0 = temp;
		break;
		case 2:
		temp = *y0; *y0 = -*x0; *x0 = temp;
		temp = *y1; *y1 = -*x1; *x1 = temp;
		break;
		case 3:
		*x0 = -*x0; *x1 = -*x1;
		break;
		case 4:
		*x0 = -*x0; *x1 = -*x1;
		*y0 = -*y0; *y1 = -*y1;
		break;
		case 5:
		temp = -*y0; *y0 = -*x0; *x0 = temp;
		temp = -*y1; *y1 = -*x1; *x1 = temp;
		break;
		case 6:
		temp = -*y0; *y0 = *x0; *x0 = temp;
		temp = -*y1; *y1 = *x1; *x1 = temp;
		break;
		case 7:
		*y0 = -*y0; *y1 = -*y1;
		break;
	}
}

void pointDrawer(int x,int y,int slope) {
	int xx,yy;
	switch(slope) {
		case 0:
		xx=x; yy=y;
		//glColor3f(1.0,0.0,0.0);
		break;
		case 1:
		xx=y; yy=x;
		//glColor3f(0.0,1.0,0.0);
		break;
		case 2:
		xx=-y; yy=x;
		//glColor3f(0.0,0.0,1.0);
		break;
		case 3:
		xx=-x; yy=y;
		//glColor3f(1.0,1.0,0.0);
		break;
		case 4:
		xx=-x; yy=-y;
		//glColor3f(1.0,0.0,1.0);
		break;
		case 5:
		xx=-y; yy=-x;
		//glColor3f(0.0,1.0,1.0);
		break;
		case 6:
		xx=y; yy=-x;
		break;
		case 7:
		xx=x,yy=-y;
		break;
	}
	glVertex2i(xx+offsetx,yy+offsety);
}

void myDrawLine(int x0,int y0,int x1,int y1,int slope) {
	offsetx=0;offsety=0;
	int dx = x1 - x0;
	int dy = y1 - y0;
	int dinit = 2*dy - dx;
	int dE = 2*dy;
	int dNE = 2*(dy - dx);

	int x = x0, y = y0;
	pointDrawer(x,y,slope);
	while(x<=x1) {
		if(dinit < 0) {
			x++;
			dinit += dE;
		}
		else {
			x++; y++;
			dinit += dNE;
		}
		pointDrawer(x,y,slope);
	}
}

void drawline8seg(int x0,int y0,int x1,int y1)
{
	int slope = getSlope(x0,y0,x1,y1);

	pointSwapper(&x0,&y0,&x1,&y1,slope);

	myDrawLine(x0,y0,x1,y1,slope);
}

void cyrusBeak(int x0,int y0,int x1,int y1)
{
	double tTop,tBottom,tLeft,tRight,tE=0.0,tL=1.0;

	if(x0==x1||y0==y1)
		return;

	tTop = -(double)(y0-YMAX)/(y1-y0);

	if(y1>y0)
	{
		if(tTop<tL) tL = tTop;
	}
	else
	{
		if(tTop>tE) tE = tTop;
	}

	tBottom = -(double)(y0-YMIN)/(y1-y0);

	if(y1<y0)
	{
		if(tBottom<tL)
            tL = tBottom;
	}
	else
	{
		if(tBottom>tE)
            tE = tBottom;
	}

	tRight = -(double)(x0-XMAX)/(x1-x0);

	if(x1>x0)
	{
		if(tRight<tL)
            tL = tRight;
	}
	else
	{
		if(tRight>tE)
            tE = tRight;
	}

	tLeft = -(double)(x0-XMIN)/(x1-x0);

	if(x1<x0)
	{
		if(tLeft<tL)
            tL = tLeft;
	}
	else
	{
		if(tLeft>tE)
            tE = tLeft;
	}

	//printf("tTop = %lf\ntBottom = %lf\ntRight = %lf\ntLeft = %lf\n",tTop,tBottom,tRight,tLeft);

	if((tE>=0.0&&tE<=1.0)||(tL>=0.0&&tL<=1.0))
	{
		if(tE<tL)
		{
			int nx0 = x0 + tE*(x1-x0);
			int ny0 = y0 + tE*(y1-y0);
			int nx1 = x0 + tL*(x1-x0);
			int ny1 = y0 + tL*(y1-y0);

			//printf("Clips To: (%d,%d) (%d,%d)\n",nx0,ny0,nx1,ny1);
			glColor3f(0.0f,0.0f,1.0f);
			drawline8seg(x0,y0,nx0,ny0);
			drawline8seg(nx1,ny1,x1,y1);
			glColor3f(0.0f,1.0f,0.0f);
			drawline8seg(nx0,ny0,nx1,ny1);
		}
	}
}

void myDrawCircleClock(int a,int b,int R) {
	glColor3f(0.0,0.0,1.0);
	offsetx = a;
	offsety = b;
	int x=0,y=R;
	int dE, dSE,temp;
	int dinit = -4*R + 5;
	int i;
	for(i=0;i<8;i++)
		pointDrawer(x,y,i);
	while(y>x) {
		dE = 4*(2*x + 3);
		dSE = 4*(2*x - 2*y + 5);
		if(dinit>=0) {
			//going diagonal
			dinit += dSE;
			x++; y--;
		}
		else {
			dinit += dE;
			x++;
		}
		for(i=0;i<8;i++)
			pointDrawer(x,y,i);
		//printf("Drawn for point (%d,%d)\n",x,y);
	}
}

void myDrawCircleAnti(int a,int b,int R) {
	offsetx = a;
	offsety = b;
	int x=R,y=0;
	int dN, dNW,temp;
	int dinit = -4*R + 5;
	int i;
	for(i=0;i<8;i++)
		pointDrawer(x,y,i);
	while(x>y) {
		dN = 4*(2*y + 3);
		dNW = 4*(2*y - 2*x + 5);
		if(dinit>=0) {
			//going diagonal
			dinit += dNW;
			x--; y++;
		}
		else {
			dinit += dN;
			y++;
		}
		for(i=0;i<8;i++)
			pointDrawer(x,y,i);
		//printf("Drawn for point (%d,%d)\n",x,y);
	}
}

void myDrawEllipse(int offx,int offy,int a,int b) {

	glColor3f(1.10,0.0,1.0);offsetx=offx;
	offsety=offy;
	int dE,dSE,dS;
	int dinit = 4*b*b - 4*a*a*b + a*a;
	int x=0,y=b,i;
	while(a*a*(y-.5) > b*b*(x+1.0)) {
		dE = 4*b*b*(2*x+3);
		dSE = 4*(b*b*(2*x+3) + a*a*(-2*y+2));
		if(dinit<0) {
			dinit += dE;
			x++;
		}
		else {
			dinit += dSE;
			x++; y--;
		}
		pointDrawer(x,y,0);
		pointDrawer(-x,y,0);
		pointDrawer(x,-y,0);
		pointDrawer(-x,-y,0);
	}
	dinit = 4*b*b*x*x + 4*b*b*x + b*b + 4*a*a*y*y - 8*a*a*y + 4*a*a - 4*a*a*b*b;
	while(y>=0) {
		dS = 4*a*a*(-2*y + 3);
		dSE = 4*(b*b*(2*x+2) + a*a*(-2*y +3));
		if(dinit>=0) {
			dinit += dS;
			y--;
		}
		else {
			dinit += dSE;
			x++; y--;
		}
		pointDrawer(x,y,0);
		pointDrawer(-x,y,0);
		pointDrawer(x,-y,0);
		pointDrawer(-x,-y,0);
	}
}

void drawRandLines()
{
	while(lines)
    {
		int x0 = (rand() % 640) - 320;
		int x1 = (rand() % 640) - 320;
		int y0 = (rand() % 480) - 240;
		int y1 = (rand() % 480) - 240;

		//printf("(%d,%d) (%d,%d)\n",x0,y0,x1,y1);
		lines--;
		cyrusBeak(x0,y0,x1,y1);
	}
	cyrusBeak(-210,-230,260,215);
}

void drawCirclesBothDir() {

	glBegin(GL_POINTS);
	myDrawCircleClock(40,20,20);
	glEnd();

	glBegin(GL_POINTS);
	myDrawEllipse(0,0,200,100);
	glEnd();
}

void dropAnimation()
{
	int R = 50;
	int A,B,i,j,k,l=0,m,n=0,slp1=5000,slp2=5000;
    int y = (WINDOW_HEIGHT)/2-R;
	for(i=0;i<5;i++)
	{
        while(y>(-WINDOW_HEIGHT/2+R))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            myDrawCircleClock(0,y--,R);
            glEnd();
            glFlush();
            usleep(slp2);
        }
        A=R+1,B=R-1;
        m=y;
        while(B>=R/2+l)
        {
            printf("%d %d\n",A,B);
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            myDrawEllipse(0,m--,A++,B--);
            glEnd();
            glFlush();
            usleep(35000-slp1);
        }
        while(A>B)
        {
            printf("111111111%d %d\n",A,B);
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            myDrawEllipse(0,m++,A--,B++);
            glEnd();
            glFlush();
            usleep(35000-slp1);
        }
        l+=5;
        n+=200;
        while(y<(WINDOW_HEIGHT-n)/2-R)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            myDrawCircleClock(0,y++,R);
            glEnd();
            glFlush();
            usleep(slp1);
        }
        slp1-=1500;
        slp2+=1000;
    }
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glOrtho(-320,319,-240,239,-1,1);
	dropAnimation();
	glFlush();
}

void init(int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("Ellipse");
}

int main(int argc, char **argv)
{
	init(&argc, argv);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
