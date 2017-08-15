#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

float red[]={1.0, 0.0 ,0.0};
float green[]={0.0, 1.0 ,0.0};
float blue[]={0.0, 0.0 ,1.0};

const int TOP =  8;
const int BOTTOM =4;
const int LEFT =1;
const int RIGHT = 2;

void drawLine(int x0,int y0,int x1,int y1,int color,int zone);
int ymin = -200, ymax = 200, xmin = -200, xmax = 200;

void swap(int *a , int *b){
    *a ^= (*b);
    *b ^= (*a);
    *a ^= (*b);
}

int make_code(int x ,int y){
    int ret = 0;
    if (x > xmax) ret += RIGHT;
    else if(x < xmin) ret += LEFT;
    if (y > ymax) ret += TOP;
    else if(y < ymin) ret += BOTTOM;
    return ret;
}

void Line_clip(int x0 , int y0 , int x1 , int y1,int zone)
{

    int code , code0, code1;
    int x , y;
    code0 = make_code(x0,y0);
    code1 = make_code(x1,y1);
    if((code0 | code1) == 0){
        //accepted
        drawLine(x0,y0,x1,y1,1,zone);
        return;
    }
    else if(code0 & code1){
        //rejected
        drawLine(x0,y0,x1,y1,0,zone);
        return;
    }
    else{
        //partially reject
        drawLine(x0,y0,x1,y1,2,zone);
        return;
    }

}

void doColor(int x , int y , int color){
    switch(color){
        case 0: glColor3f(1.0, 1.0 ,0.0);break;
        case 1: glColor3f(0, 1, 1);break;
        case 2: glColor3f(1, 0, 1);break;
    }

    glVertex2i(x,y);
}

void zoneSetup(int *x , int *y , int zone){
    switch(zone){
    case 0:
        break;
    case 1:
        swap(x,y);
        break;
    case 2:
        swap(x,y);
        *y *= -1;
        break;
    case 3:
        *x *= -1;
        break;
    case 4:
        *x *= -1;
        *y *= -1;
        break;
    case 5:
        swap(x,y);
        *x *=-1;
        *y *=-1;
        break;
    case 6:
        swap(x,y);
        *x *= -1;
        break;
    case 7:
        *y *=-1;
        break;
    }
}
void colorsetUp(int color){
    //glClearColor(0,0,0,0);
    switch(color){
        case 0: glColor3f(1.0, 1.0 ,0.0);break;
        case 1: glColor3f(0, 0, 1);break;
        case 2: glColor3f(1, 0, 1);break;
    }
}
void zoneReset(int a , int b , int zone,int color){
    int x = a;
    int y = b;

    switch(zone){
        case 0: break;
        case 1: swap(&x,&y);break;
        case 2: y *= -1;swap(&x,&y); break;
        case 3: x *= -1; break;
        case 4: x *= -1; y *= -1; break;
        case 5: swap(&x,&y); x *=-1; y *= -1; break;
        case 6: x *=-1;swap(&x,&y); break;
        case 7: y *= -1;break;
    }
    colorsetUp(color);
    //glColor3f(zone*105.1,zone*50.25,zone*2.5);
    glVertex2i(x,y);

}
void drawLine(int x0,int y0,int x1,int y1 , int color ,int zone)
{
    printf("color %d\n",color);
    zoneSetup(&x0,&y0,zone);
    zoneSetup(&x1,&y1,zone);

    int dx=fabs(x1-x0);
    int dy=fabs(y1-y0);
    int dinit=2*dy-dx;
    int dE=2*dy;
    int dNE=2*(dy-dx);

    int x=x0,y=y0;

    zoneReset(x,y,zone,color);

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

		zoneReset(x,y,zone,color);
	}

}
void working(){

    int n;
    for(n = 0 ; n<20 ; n++)
    {
        int x0=rand()%640 - 320;
        int x1=rand()%640 - 320;
        int y0=rand()%480 - 240;
        int y1=rand()%480 - 240;
        //int x0 = 0;
        //int y0 = 0;
        int x=x1-x0;
        int y=y1-y0;
        int dx=fabs(x);
        int dy=fabs(y);
        int zone = 0;

        if(x>=0 && y>=0 && dx>=dy)zone=0;
        else if(x>=0 && y>=0 && dy > dx)zone = 1;
        else if(x<0 && y>=0 && dy>dx)zone=2;
        else if(x<0 && y>=0 && dx>=dy)zone=3;
        else if(x<0 && y<0 && dx>=dy)zone=4;
        else if(x<0 && y<0 && dy>dx)zone=5;
        else if(x>=0 && y<0 && dy>dx)zone=6;
        else if(x>=0 && y<0 && dx>=dy)zone=7;
        printf("Line %d :  %d %d %d %d %d %d zone =%d\n",n,x0,x1,y0,y1,x,y,zone);
        //drawLine(x0,y0,x1,y1,zone);
        Line_clip(x0,y0,x1,y1,zone);
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

void my_display(void){

    frame();
    
    glBegin(GL_POINTS);

    working();
    glEnd();
    glFlush();
}

int main(int argc , char **argv){

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Line clipping test1");

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0,0,0,0.0);
	glOrtho (-320,319,-240,239,-1,1);

	glutDisplayFunc(my_display);
	glutMainLoop();

	return 0;
}
