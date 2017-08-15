#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

#define N 4 //Number of Points
#define X 640   //Window Width
#define Y 480   //Window Height

//int xmax=200,xmin=-200,ymax=200,ymin=-200;
int xmax=100,xmin=-100,ymax=80,ymin=-80;


void cyrus_beck_main(int x0,int y0,int x1, int y1)
{
    printf("%d %d %d %d\n",x0,y0,x1,y1);

    double te=0.0,tl=1.0;
    double t[5];
    int dx=x1-x0;
    int dy=y1-y0;

    if(dy==0 )
    {
        printf("Horizontal Line\n");
        return;
    }
    else if(dx==0 )
    {
        printf("Vertical Line\n");
        return;
    }
    //Top

    double l=((double)(y0-ymax)/dy);
    t[0]= (-1.0)*l;
    if(y1>y0)
    {
        //leaving
        if(t[0]<tl)
            tl=t[0];
    }
    else
    {
        //entering
        if(t[0]>te)
            te=t[0];
    }

    //Bottom

    t[1]= (-1.0)*((double)(y0-ymin)/dy);
    if(y1>y0)
    {
        //entering
        if(t[1]>te)
            te=t[1];
    }
    else
    {
        //leaving
        if(t[1]<tl)
            tl=t[1];

    }

    //Right
    t[2]= (-1.0)*((double)(x0-xmax)/dx);
    if(x1>x0)
    {
        //leaving
        if(t[2]<tl)
            tl=t[2];
    }
    else
    {
        //entering
        if(t[2]>te)
            te=t[2];
    }

    //Left

    t[3]= (-1.0)*((double)(x0-xmin)/dx);
    if(x1>x0)
    {
        //entering
        if(t[3]>te)
            te=t[3];
    }
    else
    {
        //leaving
        if(t[3]<tl)
            tl=t[3];

    }

    printf("Top T : %lf Bottom T : %lf\n \tRight T : %lf Left T : %lf\n",t[0],t[1],t[2],t[3]);
    printf("Entering (T): %lf \n \tLeaving (T): %lf\n",te,tl);

    if(te==0.0 && tl==1.0)
    {
        printf("Completely Accepted\n");
        return;
    }
    if(te<tl )
    {

        int nx0,nx1,ny0,ny1;
        nx0=(x0+te*(x1-x0));
        ny0=(y0+te*(y1-y0));

        nx1=(x0+tl*(x1-x0));
        ny1=(y0+tl*(y1-y0));

        glColor3ub(255.0,0.0,255.0);
        //glColor3ub(0.0,0.0,1.0);

        drawing(x0,y0,nx0,ny0);


        glColor3ub(0.0,255.0,230.0);
        //glColor3ub(0.0,1.0,0.0);

        drawing(nx0,ny0,nx1,ny1);

        //glColor3ub(0.0,0.0,255.0);
        glColor3ub(0.0,0.0,1.0);

        drawing(x1,y1,nx1,ny1);
    }
}


void my_display(void)
{


    frame();

    glBegin(GL_POINTS);
    int n=0;
    while(n<N)
    {
        n++;
        printf("Line %d : ",n);
        rand_and_cyrus();
    }
    glEnd();
	glFlush();
}

void rand_and_cyrus()
{
    int x0,y0,x1,y1;
    x0=rand()%X - (X/2);
    x1=rand()%X - (X/2);
    y0=rand()%Y - (Y/2);
    y1=rand()%Y - (Y/2);
    //cyrus_beck_main(x0,y0,x1,y1);
    cyrus_beck_main(-150,-200,150,200);

}

void drawing(int x0,int y0,int x1,int y1)
{
    int m=-1;
    int x,y;


    m= zoneSelection(x0,y0,x1,y1);
    if(m==0)
    {
        //glColor3ub(255.0,255.0,0.0); //Yellow
		drawLine(x0,y0,x1,y1,m);
    }

    else if(m==1)
    {
        //glColor3ub(0.0,255.0,0.0);   //green
		drawLine(y0,x0,y1,x1,m);
    }

    else if(m==2)
    {
        //glColor3ub(255.0,65.0,0);    //Orange
		drawLine(y0,(-1)*x0,y1,(-1)*x1,m);
    }

    else if(m==3)
    {
        //glColor3ub(255.0,250.0,240.0); //Floral White
		drawLine((-1)*x0,y0,(-1)*x1,y1,m);
    }

    else if(m==4)
    {
        //glColor3b(0.0,153.0,51.0);  //paste green
		drawLine((-1)*x0,(-1)*y0,(-1)*x1,(-1)*y1,m);
    }

    else if(m==5)
    {
        //glColor3ub(0.0,0.0,255.0);   //Blue
		drawLine((-1)*y0,(-1)*x0,(-1)*y1,(-1)*x1,m);
    }

    else if(m==6)
    {
        //glColor3ub(128.0,128.0,128.0); //Gray
		drawLine((-1)*y0,x0,(-1)*y1,x1,m);
    }

    else if(m==7)
    {
        //glColor3ub(255.0,0.0,0.0);   //red
		drawLine(x0,(-1)*y0,x1,(-1)*y1,m);
    }
}

int zoneSelection(int x0,int y0,int x1,int y1)
{
        int slope;
        int dx,dy,m,x,y;
        x=x1-x0;
        y=y1-y0;
        dx=fabs(x);
        dy=fabs(y);
        if(dx>=dy)
        {
            if(x>=0 && y>=0 )
            {
                slope=0;
            }
            else if(x<0 && y>=0 )
            {
                slope=3;
            }
            else if(x<0 && y<0)
            {
                slope=4;
            }
            else if (x>=0 && y<0)
            {
                slope=7;
            }
        }

        else
        {
            if(x>=0 && y>=0 )
            {
                slope=1;
            }
            else if(x<0 && y>=0 )
            {
                slope=2;
            }
            else if(x<0 && y<0)
            {
                slope=5;
            }
            else if (x>=0 && y<0)
            {
                slope=6;
            }
        }
        return slope;
}

void drawLine(int x0,int y0,int x1,int y1, int m)
{
    int dx=fabs(x1-x0);
    int dy=fabs(y1-y0);
    int dinit=2*dy-dx;
    int dE=2*dy;
    int dNE=2*(dy-dx);

    int x=x0,y=y0;

	while(x<=x1)
	{
        if(dinit<0)
        {
            x++;
            dinit+=dE;

        }

        else
        {
            x++;
            y++;
            dinit+=dNE;
        }
        drawPixels(x,y,m);
	}

}

void drawPixels(int x, int y,int m)
{
    if(m==0)
    {
		glVertex2i(x,y);
    }

    else if(m==1)
    {
		glVertex2i(y,x);
    }

    else if(m==2)
    {
		glVertex2i((-1)*y,x);
    }

    else if(m==3)
    {

		glVertex2i((-1)*x,y);
    }

    else if(m==4)
    {
		glVertex2i((-1)*x,(-1)*y);
    }

    else if(m==5)
    {
		glVertex2i((-1)*y,(-1)*x);
    }

    else if(m==6)
    {
		glVertex2i(y,(-1)*x);
    }

    else if(m==7)
    {
		glVertex2i(x,(-1)*y);
    }
}

void frame()
{


    glBegin(GL_LINES);

		glColor3f(1.0,1.0,1.0);
		glVertex2i(-320,0);
		glVertex2i(319,0);
		glVertex2i(0,239);
		glVertex2i(0,-240);

		glVertex2i(xmin, ymax);
		glVertex2i(xmax, ymax);

		glVertex2i(xmax, ymax);
		glVertex2i(xmax, ymin);

		glVertex2i(xmax, ymin);
		glVertex2i(xmin, ymin);

		glVertex2i(xmin, ymin);
		glVertex2i(xmin, ymax);

	glEnd();
}

int main(int argc, char *argv[])
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(X, Y);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Lab4 cyrus beck try akash");

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho (-320,319,-240,239,-1,1);
	glutDisplayFunc(my_display);
	glutMainLoop();
	return 0;
}
