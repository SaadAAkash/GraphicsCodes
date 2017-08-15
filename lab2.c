#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<GL/glut.h>

int NumOfLines = 399, high = 239, low = -240, l = -320, r = 319;

void my_display()
{
    glBegin(GL_POINTS);

        int i =1;
        for(;i <= NumOfLines;i++)
        {
            printf("Line no. %d : ",i);
            draw();
        }

    glEnd();
    //using glFlush after glEnd()
    glFlush();
}
///////////////////////////////////////
void draw()
{

    int slope;
    int x0,y0,x1,y1,x,y;

    //rand points
    x1 = rand()%640 - (640/2);
    y1 = rand()%480 - (480/2);

    //main point
    x0 = 0;
    y0 = 0;

    slope = zone(x0,y0,x1,y1);  //detect slope/zone

    if(slope == 0)
    {
        glColor3ub(255.0,0.0,0.0);//red
        draw_line(x0,y0,x1,y1,slope);
    }
    else if(slope == 1)
    {
        glColor3ub(128.0,128.0,128.0);//gray
        draw_line(y0,x0,y1,x1,slope);
    }
    else if(slope == 2)
    {
        glColor3ub(0.0,0.0,255.0);//blue
        draw_line(y0,(-1)*x0,y1,(-1)*x1,slope);
    }
    else if(slope == 3)
    {
        glColor3ub(0.0,153.0,51.0);//paste green
        draw_line((-1)*x0,y0,(-1)*x1,y1,slope);
    }
    else if(slope == 4)
    {
        glColor3ub(255.0,255.0,240.0);//floral white
        draw_line((-1)*x0,(-1)*y0,(-1)*x1,(-1)*y1,slope);
    }
    else if(slope == 5)
    {
        glColor3ub(255.0,65.0,0.0);//orange
        draw_line((-1)*y0,(-1)*x0,(-1)*y1,(-1)*x1,slope);
    }
    else if(slope == 6)
    {
        glColor3ub(255.0,255.0,0.0);//yellow
        draw_line((-1)*y0,x0,(-1)*y1,x1,slope);

    }
    else if(slope == 7)
    {
        glColor3ub(0.0,255.0,0.0);//green
        draw_line(x0,(-1)*y0,x1,(-1)*y1,slope);
    }

}
////////////////////////////////////////////////////
int zone(int x0,int y0,int x1, int y1)
{
    int retslope,x,y;
    x = x1 - x0;
    y = y1 - y0;

    if(fabs(x) >= fabs(y))
    {
        if(x >= 0 && y >= 0)
            retslope = 0;
        else if(x < 0 && y >= 0)
            retslope = 3;
        else if(x < 0 && y < 0)
            retslope = 4;
        else if(x >= 0 && y < 0)
            retslope = 7;
    }
    else
    {
        if(x >= 0 && y >= 0)
            retslope = 1;
        else if(x < 0 && y >= 0)
            retslope = 2;
        else if(x < 0 && y < 0)
            retslope = 5;
        else if(x >= 0 && y < 0)
            retslope = 6;

    }
    return retslope;

}
////////////////////////////////////////////////
void draw_line(int x0,int y0,int x1, int y1, int m)
{
    printf(" --> Points: %d,%d,%d,%d & slope:%d\n",x0,y0,x1,y1,m);

    int dx=fabs(x1-x0);
    int dy=fabs(y1-y0);
    int dinit=2*dy-dx;

    int dE=2*dy;
    int dNE=2*(dy-dx);

    int x=x0,y=y0;

    while(x<=x1)
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
        draw_pixel(x,y,m);

    }

}
//changes acc to slopes
void draw_pixel(int x, int y, int m)
{
    switch(m)
    {

        case 0:
        {
            glVertex2i(x,y);
            break;
        }

        case 1:
        {
            glVertex2i(y,x);
            break;
        }

        case 2:
        {
            glVertex2i((-1)*y,x);
            break;
        }

        case 3:
        {
            glVertex2i((-1)*x,y);
            break;
        }

        case 4:
        {
            glVertex2i((-1)*x,(-1)*y);
            break;
        }

        case 5:
        {
            glVertex2i((-1)*y,(-1)*x);
            break;
        }

        case 6:
        {
            glVertex2i(y,(-1)*x);
            break;
        }

        case 7:
        {
            glVertex2i(x,(-1)*y);
            break;
        }

    }

}


int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize( 640 , 480) ;  //main win
    glutInitWindowPosition(200,200);
    glutCreateWindow("Assignmnt01Test4");
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glOrtho(l,r,low,high,-1,1);
    glutDisplayFunc(my_display);  //calling my_display

    glutMainLoop();
    return 0;
}
