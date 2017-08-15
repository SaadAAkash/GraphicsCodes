#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

void drawLineSym(int x0, int y0, int x1, int y1);
int Xmax = 200, Xmin = -200, Ymax = 200, Ymin = -200;
int top = 8, bottom = 4, right = 2, left = 1;
double a, zp, ZP;
double lx, ly, lz;
double N[10];

struct Point{
    double x,y,z;
};

struct Point cop;
struct Point obj[8];
struct Point proj[8];
struct Point rotObj[8];

void drawPixel(int x, int y, int slopeZONE){
    glBegin(GL_POINTS);
    if(slopeZONE == 0)glVertex2i(x,y);
    else if(slopeZONE == 1)glVertex2i(y,x);
    else if(slopeZONE == 2)glVertex2i((-1)*y,x);
    else if(slopeZONE == 3)glVertex2i((-1)*x,y);
    else if(slopeZONE == 4)glVertex2i((-1)*x,(-1)*y);
    else if(slopeZONE == 5)glVertex2i((-1)*y,(-1)*x);
    else if(slopeZONE == 6)glVertex2i(y,(-1)*x);
    else if(slopeZONE == 7)glVertex2i(x,(-1)*y);
    glEnd();
}



void drawLine(int x0,int y0,int x1,int y1, int slopeZONE){
    int dx=x1-x0;
    int dy=y1-y0;
    int dinit=2*dy-dx;
    int de=2*dy;
    int dne=2*(dy-dx);
    int x=x0;
    int y=y0;
    while(x<=x1){
        if(dinit<0)
        {
            x++;
            dinit+=de;
        }
        else{
            x++;
            y++;
            dinit+=dne;
        }
        drawPixel(x,y,slopeZONE);
    }
}

void drawLineSym(int x0, int y0, int x1, int y1){
        int dx=x1-x0;
        int dy=y1-y0;
        int modX = dx, modY = dy;
        if(dx < 0) modX = -modX;
        if(dy < 0) modY = -modY;

        if(modX >= modY){ //0, 3, 4, 7
            if(dx >= 0 && dy >= 0){
                //0
                drawLine(x0,y0,x1,y1,0);
            }
            else if(dx < 0 && dy >= 0){
                //3
                drawLine((-1)*x0, y0, (-1)*x1, y1, 3);
            }
            else if(dx < 0 && dy < 0 ){
                //4
                drawLine((-1)*x0, (-1)*y0, (-1)*x1, (-1)*y1, 4);
            }
            else if(dx >= 0 && dy < 0 ){
                //7
                drawLine(x0, (-1)*y0, x1, (-1)*y1, 7);
            }

        }
        else if(modX < modY ){ //1,2,5,6
            if(dx >= 0 && dy >= 0){
                //1
                drawLine(y0, x0, y1, x1, 1);
            }
            else if(dx < 0 && dy >= 0){
                //2
                drawLine(y0, (-1)*x0, y1, (-1)*x1, 2);
            }
            else if(dx < 0 && dy < 0 ){
                //5
                drawLine((-1)*y0, (-1)*x0, (-1)*y1, (-1)*x1, 5);
            }
            else if(dx >= 0 && dy < 0 ){
                //6
                drawLine((-1)*y0, x0, (-1)*y1, x1, 6);
            }
        }
        glFlush();
}


void drawLine3d(Point a, Point b){
    drawLineSym(a.x, a.y, b.x, b.y);
}

void draw3(int a, int b){
    drawLine3d(proj[a], proj[b]);
    //drawLine3d(rot[a],rot[b]);
}

void fillGround(){
    for(int x=0; x<=a; x++){
        drawLineSym(0,x,a,x);
    }
}


void drawQuad(Point a, Point b, Point c, Point d, double col){


    printf("Calculated Intensity = %f\n", col);


    glColor3f(col, col, col);
    glBegin(GL_QUADS);

    glVertex2i(a.x,a.y);
    glVertex2i(b.x,b.y);
    glVertex2i(c.x,c.y);
    glVertex2i(d.x,d.y);
    glEnd();


}

void cal(int x, int y, int z, int w, Point *p)
{
    Point a, b;


    a.x = p[y].x - p[x].x;
    a.y = p[y].y - p[x].y;
    a.z = p[y].z - p[x].z;
    b.x = p[y].x - p[z].x;
    b.y = p[y].y - p[z].y;
    b.z = p[y].z - p[z].z;
    Point n;

    //cross prod:

    n.x = a.y*b.z - b.y*a.z;
    n.y = -(a.z*b.x - a.x*b.z);
    n.z = a.x*b.y - a.y*b.x;

    //normalization:
    double norm = n.x*n.x+n.y*n.y+n.z*n.z;
    norm = sqrt(norm);
    n.x/=norm; n.y/=norm; n.z/=norm;


    //dot prod
    double ret = lx*n.x + ly*n.y + lz*n.z;  //intensity
    printf("Intensity: %lf\n", ret);


      //  drawQuad(p[x], p[y], p[z], p[w], ret);

   if(ret>=0)
   {
        //intesity
        drawQuad(p[x], p[y], p[z], p[w], ret);
    }
}

void mainDrawCube()
{
    cal(3,2,1,0,proj);
    cal(5,1,2,6,proj);
    cal(7,6,2,3,proj);

    cal(7,3,0,4,proj);
    cal(0,1,5,4,proj);
    cal(4,5,6,7,proj);
/*
 cal(3,2,1,0,rotObj);
    cal(5,1,2,6,rotObj);
    cal(7,6,2,3,rotObj);

    cal(7,3,0,4,rotObj);
    cal(0,1,5,4,rotObj);
    cal(4,5,6,7,rotObj);
*/
    return;

    glColor3f(0.0,1.0,0.0);

    //left
    for(int k=0; k<=2; k++)
        draw3(k,k+1);
    draw3(0,3);
    //right
    for(int k=4; k<=6; k++)
        draw3(k,k+1);
    draw3(4,7);

    //corner
    for(int k=0; k<=3; k++)
        draw3(k,k+4);
    //fillGround();

    glColor3f(0.0,1.0,1.0);
    draw3(1,2);
    draw3(5,6);
    draw3(4,7);
    draw3(0,3);
}


double dx, dy, dz;
double xp(Point p){return  p.x + -dx/dz*p.z + zp * dx/dz;}
double yp(Point p){return p.y + -dy/dz*p.z + zp * dy/dz;}
double zpp(Point p){return zp * (-p.z/dz + 1.0 + zp/dz );}
double div(Point p){return -1/dz*p.z + 1.0 + zp/dz;}

void projection(Point *obj)
{
    for(int j=0; j<8; j++)
    {
        proj[j]=obj[j];
    }

    for(int j = 0; j < 8; j++){

        //baireer tol ar bhitorer tol zP not eq tai
        if(j==0||j==1||j==4||j==5)
            zp = ZP;
        else zp = ZP-a;

        dx = cop.x;
        dy = cop.y;
        dz = cop.z - zp;

        proj[j].x = xp(obj[j])/div(obj[j]);
        proj[j].y = yp(obj[j])/div(obj[j]);
        proj[j].z = zpp(obj[j])/div(obj[j]);


        printf("The projectd points: %d,  %lf %lf %lf\n",j, proj[j].x, proj[j].y, proj[j].z);
    }

}

double xr(double deg, Point p){
    return p.x*cos(deg) - p.y*sin(deg);
    }
double yr(double deg, Point p){
    return p.x*sin(deg) + p.y*cos(deg);
    }

double zr(double deg, Point p){
    return p.z;
}

void rotation(Point *proj, double deg)
{
    deg = deg * (3.141596 / 180);
    for(int j = 0; j< 8; j++)
    {
        rotObj[j].x = xr(deg, proj[j]);
        rotObj[j].y = yr(deg, proj[j]);
        rotObj[j].z = zr(deg, proj[j]);
        /*proj[j].x = xr(deg, proj[j]);
        proj[j].y = yr(deg, proj[j]);
        proj[j].z = zr(deg, proj[j]);*/

    }
}


void cube_params(){
    a = 50;

    cop.x = 100;
    cop.y = 200;
    cop.z = 800;

    //cop.x = 0;
    //cop.y = 0;
    //cop.z = 0;
    lx = -50;
    ly = -100;
    lz = -400;

    double norm = lx*lx+ly*ly+lz*lz;

    norm = sqrt(norm);

    lx/=norm; ly/=norm; lz/=norm;

    ZP = 200;


    obj[0].x = -a;
    obj[0].y = -a;
    obj[0].z = -a;

    obj[1].x = +a;
    obj[1].y = -a;
    obj[1].z = -a;

    obj[2].x = +a;
    obj[2].y = +a;
    obj[2].z = -a;

    obj[3].x = -a;
    obj[3].y = +a;
    obj[3].z = -a;

    obj[4].x = -a;
    obj[4].y = -a;
    obj[4].z = a;

    obj[5].x = +a;
    obj[5].y = -a;
    obj[5].z = +a;

    obj[6].x = +a;
    obj[6].y = +a;
    obj[6].z = +a;

    obj[7].x = -a;
    obj[7].y = +a;
    obj[7].z = +a;



}

void frame()
{

	glBegin(GL_LINES);
		glColor3f(1.0,1.0,0.0);
		glVertex2i(-320,0);
		glVertex2i(319,0);
		glVertex2i(0,219);
		glVertex2i(0,-220);

	glEnd();


}
void display(void)
{
	//glClearColor(0,0,0,0.0);
	glOrtho (-320,319,-240,239,-1,1);

    //frame();

	//glFlush();

    while(1)
    {
        cube_params();
        printf("loop going...\n ");
        for(int deg=0; deg<=0; deg+=10)
        {

            rotation(obj,deg);

            projection(rotObj);

            mainDrawCube();

            glEnd();
            glFlush();
            glClear(GL_COLOR_BUFFER_BIT);

        }
        //glFlush();
		getchar();
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);
    }
}


int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Lab8try2");
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

