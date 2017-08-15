#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawPixel(int posX,int posY, int x,int y)
{
    glVertex2i(posX+x, posY+y);
    glVertex2i(posX-x, posY+y);
    glVertex2i(posX-x, posY-y);
    glVertex2i(posX+x, posY-y);

}

void drawElipse(int xs1,int ys1,int rx, int ry)
{
    if (ry<0)
        return;
    int x,y;
    float d1,d2,dx,dy;
    x = 0;
    y = ry;
    d1 = 4*pow(ry,2) - 4*(pow(rx,2) * ry) +  pow(rx,2);
    //d1 = pow(ry,2) - (pow(rx,2) * ry) + (0.25 * pow(rx,2));
    dx = 8 * pow(ry,2) * x;
    dy = 8 * pow(rx,2) * y;
    do                         // region one
    {
        drawPixel(xs1,ys1,x,y);
        if(d1<0)
        {
            x++;
            dx = dx + (8 * (pow(ry,2)));
            d1 = d1 + dx +(pow(ry,2));
        }
        else
        {
            x++;
            y--;
            dx = dx + (8 * (pow(ry,2)));
            dy = dy - (8 * (pow(rx,2)));
            d1 = d1 + dx - dy + (pow(ry,2));
        }
    }while(dx<dy);

    do
    {
        drawPixel(xs1,ys1,x,y);
        if(d2>0)
        {
            x = x;
            y--;
            dy = dy - (8 * (pow(rx,2)));
            d2 = d2 - dy + pow(rx,2);
        }
        else
        {
            x++;
            y--;
            dy = dy - (8 * (pow(rx,2)));
            dx = dx + (8 * (pow(ry,2)));
            d2 = d2 +dx - dy + pow(rx,2);

        }
    }while(y>0);

    drawElipse(xs1,ys1,rx,ry-1);
}


void doLine()
{

    glBegin(GL_LINES);

		glColor3f(1.0,1.0,1.0);
		glVertex2i(-320,0);
		glVertex2i(319,0);
		glVertex2i(0,239);
		glVertex2i(0,-240);


	glEnd();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255.0,255.0,255.0);   //white
    doLine();
    glBegin(GL_POINTS);
    drawElipse(0,0,100,30);  //x, y, a ,b
    glEnd();
    glutSwapBuffers();
}


    int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);

	glutCreateWindow("Ellipse/circle Algorithm");

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho (-320,319,-240,239,-1,1);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}


