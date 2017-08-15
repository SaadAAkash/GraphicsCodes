#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int r1=40,r2=30;
#define Ymax 240
#define Ymin -240
#define Xmax 320
#define Xmin -320

#define Top 8
#define Bottom 4
#define Right 2
#define Left 1

#define PI 3.14159265

int X0,X1,Y0,Y1,dy,dx,i;

void init()
{
	glClearColor(0,0,0,0.0);  
	//glMatrixMode (GL_PROJECTION);
	glOrtho (-320,319,-240,239,-1,1);
}

void drawline(int x0, int y0, int x1, int y1, int z)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int dinit,de,dne;
	int x=x0;
	int y=y0;
	dinit = 2*dy - dx;
	de = 2*dy;
	dne = 2*(dy -dx);
	glColor3f(1.0,1.0,1.0);
	if(z==0)
	{
		//
		glBegin(GL_POINTS);
			glVertex2i(x0,y0);
		glEnd();
		//printf(" with color 1,0,0\n");
	}
	else if(z==1)
	{
		//glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(y0,x0);
		glEnd();
		//printf(" with color 0,1,0\n");
	}
	else if(z==2)
	{
		//glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(-y0,x0);
		glEnd();
		//printf(" with color 0,0,1\n");
	}
	else if(z==3)
	{
		//glColor3f(1.0,1.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(-x0,y0);
		glEnd();
		//printf(" with color 1,1,0\n");
	}
	else if(z==4)
	{
		//glColor3f(1.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(-x0,-y0);
		glEnd();
		//printf(" with color 1,0,1\n");
	}
	else if(z==5)
	{
		//glColor3f(0.0,1.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(-y0,-x0);
		glEnd();
		//printf(" with color 0,1,1\n");
	}
	else if(z==6)
	{
		//glColor3f(1.0,0.5,0.5);
		glBegin(GL_POINTS);
			glVertex2i(y0,-x0);
		glEnd();
		//printf(" with color 1,.5,.5\n");
	}
	else
	{
		//glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(x0,-y0);
		glEnd();
		//printf(" with color 1,1,1\n");
	}

	
	while(x <= x1)
	{
		if(dinit < 0)
		{
			x++;
			dinit += de;
		}
		else
		{
			x++;
			y++;
			dinit += dne;
		}
		glBegin(GL_POINTS);
			if(z==0)
				glVertex2i(x,y);
			else if(z==1)
				glVertex2i(y,x);
			else if(z==2)
				glVertex2i(-y,x);
			else if(z==3)
				glVertex2i(-x,y);
			else if(z==4)
				glVertex2i(-x,-y);
			else if(z==5)
				glVertex2i(-y,-x);
			else if(z==6)
				glVertex2i(y,-x);
			else if(z==7)
				glVertex2i(x,-y);
		glEnd();
	}
	
}

void drawPoint(int x, int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//glFlush();
}

void circle1(int i,int j)
{
	int x=0;
	int y=r1;
	int dint=-r1+5/4;

	glColor3f(1.0,0.0,0.0);
	drawPoint(x+i,y+j);
	drawPoint(x+i,-y+j);
	drawPoint(-x+i,y+j);
	drawPoint(y+i,x+j);
	drawPoint(-y+i,x+j);
	drawPoint(-y+i,-x+j);
	drawPoint(-x+i,-y+j);
	drawPoint(y+i,-x+j);
	while(x<=y)
	{
		if(dint<0)
		{
			x++;
			dint+=2*x+3;

		}
		else
		{
			x++;
			y--;
	    		dint+=2*x-2*y+3;

		}
		//usleep(10000);
	drawPoint(x+i,y+j);
	drawPoint(x+i,-y+j);
	drawPoint(-x+i,y+j);
	drawPoint(y+i,x+j);
	drawPoint(-y+i,x+j);
	drawPoint(-y+i,-x+j);
	drawPoint(-x+i,-y+j);
	drawPoint(y+i,-x+j);
	}
}
void line(int x0,int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(abs(dx) >= abs(dy))
	{
		if(dx>=0 && dy>=0)
		{
			////printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 0",x0,y0,x1,y1);
			drawline(x0,y0,x1,y1,0);
			//i++;
		}
		else if(dx>=0 && dy<0)
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 7",x0,y0,x1,y1);
			drawline(x0,-y0,x1,-y1,7);
			//i++;
		}
		else if(dx<0 && dy>=0)
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 3",x0,y0,x1,y1);
			drawline(-x0,y0,-x1,y1,3);
			//i++;
		}
		else
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 4",x0,y0,x1,y1);
			drawline(-x0,-y0,-x1,-y1,4);
			//i++;
		}
	}
	else
	{
		if(dx>0 && dy>0)
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 1",x0,y0,x1,y1);
			drawline(y0,x0,y1,x1,1);
			//i++;
		}
		else if(dx<0 && dy>=0)
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 2",x0,y0,x1,y1);
			drawline(y0,-x0,y1,-x1,2);
			//i++;
		}
		else if(dx<0 && dy<0)
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 5",x0,y0,x1,y1);
			drawline(-y0,-x0,-y1,-x1,5);
			//i++;
		}
		else
		{
			//printf("x0 = %d y0 = %d x1 = %d y1= %d line of zone 6",x0,y0,x1,y1);
			drawline(-y0,x0,-y1,x1,6);
			//i++;
		}
	}
}
void circle2(int i,int j,int k)
{
	int x=r2;
	int y=0;
	int dint=-4*r1+5;
	
	glColor3f(0.0,1.0,0.0);
	drawPoint(x+i,y+j);
	drawPoint(x+i,-y+j);
	drawPoint(-x+i,y+j);
	drawPoint(y+i,x+j);
	drawPoint(-y+i,x+j);
	drawPoint(-y+i,-x+j);
	drawPoint(-x+i,-y+j);
	drawPoint(y+i,-x+j);
	int x0,y0,x1,y1;
	x0=x;
	y0=0;
	
	//line(x+i,y+j,-x+i,-y+j);
	//line(x+i,y+j,-x+i,-y+j);
	
	
	while(y<=x)
	{
		if(dint<0)
		{
			y++;
			dint+=(2*y+3)*4;

		}
		else
		{
			y++;
			x--;
	    		dint+=(-2*x+2*y+5)*4;

		}
		glColor3f(0.0,1.0,0.0);
		drawPoint(x+i,y+j);
		drawPoint(x+i,-y+j);
		drawPoint(-x+i,y+j);
		drawPoint(y+i,x+j);
		drawPoint(-y+i,x+j);
		drawPoint(-y+i,-x+j);
		drawPoint(-x+i,-y+j);
		drawPoint(y+i,-x+j);
	}
	x0 = r2*cos(k*PI/180);
	y0 = r2*sin(k*PI/180);
	line(x0+i,-y0+j,-x0+i,y0+j);

	x0 = r2*cos((45-k)*PI/180);
	y0 = r2*sin((45-k)*PI/180);
	line(x0+i,y0+j,-x0+i,-y0+j);
	
	x0 = r2*cos((90-k)*PI/180);
	y0 = r2*sin((90-k)*PI/180);
	line(x0+i,y0+j,-x0+i,-y0+j);

	x0 = r2*cos((135-k)*PI/180);
	y0 = r2*sin((135-k)*PI/180);
	line(x0+i,y0+j,-x0+i,-y0+j);
}
void hill()
{
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,1.0);
		glVertex2i(-320,-100);
		glVertex2i(319,-100);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,1.0);
		glVertex2i(-320,100);
		glVertex2i(-200,100);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,1.0);
		glVertex2i(-200,100);
		glVertex2i(0,-100);
	glEnd();
	glFlush();
}
void object(int x,int y)
{
	glBegin(GL_LINES);
		glColor3f(1.0,1.0,0.0);
		glVertex2i(90-x,-100+y);
		glVertex2i(90-x,-40+y);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	hill();
	int incX,incY;
	int x,y;
	x=-270;y=140;
	incX=2;incY=2;
	
	for(x=-270;x<=-190;x++)
	{
		hill();
		object(0,0);
	    	glColor3f(1.0,0.0,0.0);
		
		circle1(x,y);
		glFlush();

		glColor3f(0.0,1.0,0.0);
		circle2(x,y,(x+270)%45);
		
		glFlush();
		usleep(10000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	for(x = -185,y=140;x<=15;x++,y--)
	{
		hill();
		object(0,0);
	    	glColor3f(1.0,0.0,0.0);
		
		circle1(x,y);
		glFlush();

		glColor3f(0.0,1.0,0.0);
		circle2(x,y,(x+270)%45);
		
		glFlush();
		usleep(10000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	for(;x<319;x++)
	{
		hill();
		if(x<50)
			object(0,0);
		else if(x<260)
			object(x-15,x-15);
		else
			object(300,200);
	    	glColor3f(1.0,0.0,0.0);
		
		circle1(x,y);
		glFlush();

		glColor3f(0.0,1.0,0.0);
		circle2(x,y,(x+270)%45);
		
		glFlush();
		usleep(10000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
}

int main(int argc, char *argv[])
{
	//scanf("%d %d",&r1,&r2);
	//scanf("%d %d",&x,&y);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	
	glutCreateWindow("Simple GLUT 8-way Symmetry test");
	init();

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
