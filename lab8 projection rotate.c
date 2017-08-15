#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

#define X 640
#define Y 480
#define N 200

#define left   -320
#define right   319
#define top     239
#define bottom -240
#define area_x_max 200
#define area_y_max 200
#define area_x_min -200
#define area_y_min -200
#define up 8
#define down 4
#define dan 2
#define bam 1
#define alpha 120


void display();//the calling one
void init();//the loop controller
void draw(int x0,int y0,int x1,int y1);//the one which calls the drawline
int selectzone(int x0,int y0,int x1, int y1);//the one which select where to draw
void drawLine(int x0,int y0,int x1, int y1, int m);//the one which draws lines
void drawPixels(int x, int y, int m);//draw individual pixels
struct vertex project(struct vertex);//projrction
struct vertex set_points (struct vertex ,float x0,float y0,float z0);//set values in structure
struct vertex rotate(struct vertex vert,float deg);


struct vertex{
	float x0,y0,z0;
	int xp,yp,zp;
}projp,cop,points[8],Q;

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(X,Y);
    glutInitWindowPosition(200,200);

    glutCreateWindow("Line clipping algorithm using 8-Way Symmetry Algorithm");

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(left,right,bottom,top,-1,1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

struct vertex set_points(struct vertex vert ,float x,float y,float z)
{
	vert.x0 = x;
	vert.y0 = y;
	vert.z0 = z;
	return vert;
}


void display()
{

    init();


}


void init()
{
    int n = 8;
    projp = set_points(projp, 0 ,0,200);
    cop = set_points(cop, 0, 0,400);

    Q.x0 = cop.x0 - projp.x0;
    Q.y0 = cop.y0 - projp.y0;
    Q.z0 = cop.z0 - projp.z0;

    points[0] = set_points(points[0], 00, 00, 00);
    points[1] = set_points(points[1], 00, 00, alpha);
    points[2] = set_points(points[2], 00, alpha, 00);
    points[3] = set_points(points[3], 00, alpha, alpha);
    points[4] = set_points(points[4], alpha, 00, 00);
    points[5] = set_points(points[5], alpha, 00, alpha);
    points[6] = set_points(points[6], alpha, alpha, 00);
    points[7] = set_points(points[7], alpha, alpha, alpha);


    //points[0] = set_points(points[0], 0 ,0, 0);

	while(1)
	{
		glBegin(GL_POINTS);


        int i;
		for(i = 0 ; i < n ; i++)
		{
			points[i] = rotate(points[i],10);
			printf("%lf %lf %lf %d %d\n",points[i].x0,points[i].y0,points[i].z0,points[i].xp , points[i].yp);
		}

		for( i = 0 ; i < n ; i++)
		{
			points[i] = project(points[i]);
			printf("%lf %lf %lf %d %d\n",points[i].x0,points[i].y0,points[i].z0,points[i].xp , points[i].yp);
		}
		draw(points[0].xp , points[0].yp , points[1].xp , points[1].yp);
		draw(points[0].xp , points[0].yp , points[2].xp , points[2].yp);
		draw(points[0].xp , points[0].yp , points[4].xp , points[4].yp);
		draw(points[1].xp , points[1].yp , points[3].xp , points[3].yp);
		draw(points[1].xp , points[1].yp , points[5].xp , points[5].yp);
		draw(points[2].xp , points[2].yp , points[3].xp , points[3].yp);
		draw(points[2].xp , points[2].yp , points[6].xp , points[6].yp);
		draw(points[4].xp , points[4].yp , points[5].xp , points[5].yp);
		draw(points[4].xp , points[4].yp , points[6].xp , points[6].yp);
		draw(points[7].xp , points[7].yp , points[3].xp , points[3].yp);
		draw(points[7].xp , points[7].yp , points[5].xp , points[5].yp);
		draw(points[7].xp , points[7].yp , points[6].xp , points[6].yp);

		glEnd();
		glFlush();
		getchar();
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);
    }

}


struct vertex rotate(struct vertex vert,float deg)
{
	float tempz = vert.z0 * cos((3.1416 /180 )* deg) - vert.x0 * sin((3.1416 /180 ) * deg);
	float tempx = vert.z0 * sin((3.1416 /180 )* deg) + vert.x0 * cos((3.1416 /180 ) * deg);
	vert.y0 = vert.y0;

	vert.z0 = tempz;
	vert.x0 = tempx;

	return vert;

}

struct vertex project(struct vertex vert)
{
	float denom = (-vert.z0 / Q.z0 + 1 + projp.z0 / Q.z0);

	int tempx = vert.x0 - (Q.x0 / Q.z0) * vert.z0 + projp.z0 * (Q.x0 / Q.z0);
	//printf("%d\n",tempx);
	vert.xp = tempx / denom;
	//printf("%d\n",vert.xp);

	int tempy = vert.y0 - (Q.y0 / Q.z0) * vert.z0 + projp.z0 * (Q.y0 / Q.z0);
	vert.yp = tempy / denom;

	return vert;

}


void draw(x0,y0,x1,y1)
{
    //int m;
    //int x0,y0,x1,y1,x,y;

	int m = selectzone(x0,y0,x1,y1);

    if(m == 0)
    {
        drawLine(x0,y0,x1,y1,m);
    }


    if(m == 1)
    {
        drawLine(y0,x0,y1,x1,m);
    }



    if(m == 2)
    {
        drawLine(y0,(-1)*x0,y1,(-1)*x1,m);
    }


    if(m == 3)
    {
        drawLine((-1)*x0,y0,(-1)*x1,y1,m);
    }

    if(m == 4)
    {
        drawLine((-1)*x0,(-1)*y0,(-1)*x1,(-1)*y1,m);
    }


    if(m == 5)
    {
        drawLine((-1)*y0,(-1)*x0,(-1)*y1,(-1)*x1,m);
    }


    if(m == 6)
    {
        drawLine((-1)*y0,x0,(-1)*y1,x1,m);
    }


    if(m == 7)
    {
        drawLine(x0,(-1)*y0,x1,(-1)*y1,m);
    }

}



int selectzone(int x0,int y0,int x1, int y1)
{
    int slope,x,y,m,dx,dy;
    x = x1 - x0;
    y = y1 - y0;
    dx = fabs(x);
    dy = fabs(y);

    if(dx >= dy)
    {
        if(x >= 0 && y >= 0)
            slope = 0;
        if(x < 0 && y >= 0)
            slope = 3;
        if(x < 0 && y < 0)
            slope = 4;
        if(x >= 0 && y < 0)
            slope = 7;
    }


    else
    {
        if(x >= 0 && y >= 0)
            slope = 1;
        if(x < 0 && y >= 0)
            slope = 2;
        if(x < 0 && y < 0)
            slope = 5;
        if(x >= 0 && y < 0)
            slope = 6;

    }


    return slope;

}


void drawLine(int x0,int y0,int x1, int y1, int m)
{
    printf("  Slope %d , %d %d %d %d\n",m,x0,y0,x1,y1);

    int dx=fabs(x1-x0);
    int dy=fabs(y1-y0);
    int dinit=2*dy-dx;

    int dE=2*dy;
    int dNE=2*(dy-dx);

    int x=x0,y=y0;

    while(x<= x1)
    {
        if(dinit >= 0)
        {
            x++;
            y++;
            dinit += dNE;
        }

        else
        {
            x++;
            dinit += dE;
        }
        drawPixels(x,y,m);

    }

}


void drawPixels(int x, int y, int m)
{
    if(m == 0)
    {
        glVertex2i(x,y);
    }

    if(m == 1)
    {
        glVertex2i(y,x);
    }

    if(m == 2)
    {
        glVertex2i((-1)*y,x);
    }

    if(m == 3)
    {
        glVertex2i((-1)*x,y);
    }

    if(m == 4)
    {
        glVertex2i((-1)*x,(-1)*y);
    }

    if(m == 5)
    {
        glVertex2i((-1)*y,(-1)*x);
    }

    if(m == 6)
    {
        glVertex2i(y,(-1)*x);
    }

    if(m == 7)
    {
        glVertex2i(x,(-1)*y);
    }
}



