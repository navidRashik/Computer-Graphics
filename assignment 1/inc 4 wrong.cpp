/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include<windows.h>
//#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

//using namespace std;

int centerx;
int centery;






void drawPixel(int x, int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
static void drawLine(int x1, int y1, int x2, int y2)
{

    float dx=x2-x1;
    float dy=y2-y1;
    float slope = dy/dx;
    int x,y;
    if(x1<x2){
         x=x1;  y=y1;
    }else{
        x=x2; y=y2;
        x2=x1; y2=y1;
    }

    //cout<<slope;
    if(y2 == y || x2 == x){
        while (y2 == y && x<x2)
        {
            x++;
            drawPixel(x,y);
        }
        while (x2 == x && y<y2)
        {
            y++;
            drawPixel(x,y);
        }
        while (y2 == y && x>x2)
        {
            x--;
            drawPixel(x,y);
        }
        while (x2 == x && y>y2)
        {
            y--;
            drawPixel(x,y);
        }



        }else if(1>slope && slope>=0) //0-45
        {
            int d=2*dy-dx;
            int increE=2*dy;
            int incrNE=2*(dy-dx);
            drawPixel(x,y);
            if(x>=0)
            {
                while (x < x2 )
                {

                    if (d <= 0) {
                        d+=increE;
                        x++;
                    }
                    else {
                        d+=incrNE;
                        x++;
                        y++;
                    }
                    drawPixel(x,y);
                }
            }else if(x<0)
            {

                while (x < x2 )
                {
                    if (d > 0) {
                        d+=increE;
                        x++;
                    }
                    else {
                        d+=incrNE;
                        x++;
                        y++;
                    }
                    drawPixel(x,y);
                }


            }

        }
        else if(-1<=slope && slope<0) //315-360
        {

            int d=2*dy+dx;
            int increE=2*dy;
            int incrSE=2*(dy+dx);while (x < x2 )

            if(x>=0){
                while (x < x2 )
                {
                    if (d >= 0) {
                        d+=increE;
                        x++;
                    }
                    else {
                        d+=incrSE;
                        x++;
                        y--;
                    }
                    drawPixel(x,y);
                }
            }else if(x<0)
            {
                while (x <= x2 )
                {
                    if (d < 0) {
                        d+=increE;
                        x++;
                    }
                    else {
                        d+=incrSE;
                        x++;
                        y--;
                    }
                    drawPixel(x,y);
                }
            }

        }


       else if(slope>=1) //45-90
        {

            int d=dy-2*dx;
            int increN=2*(-dx);
            int incrNE=2*(dy-dx);
            drawPixel(x,y);
            if(y>=0){
                while (y < y2)
                {

                    if (d >= 0) {
                        d+=increN;
                        y++;
                    }
                    else {
                        d+=incrNE;
                        x++;
                        y++;
                    }
                    drawPixel(x,y);
                }
            }else if(y<0){
                while (y < y2)
                {
                    if (d < 0) {
                        d+=increN;
                        y++;
                    }
                    else {
                        d+=incrNE;
                        x++;
                        y++;
                    }
                    drawPixel(x,y);
                }
            }

        }

      else  if(slope<-1)   //270-315 //no equal
        {

            int d=2*dx+dy;
            int increS=2*dx;
            int incrSE=2*(dx+dy);
            drawPixel(x,y);
            if(y2>=0){
                while (y > y2)
                {
                    if(y2>=0){
                        if (d >= 0) {
                        d+=increS;
                        y--;
                        }
                        else {
                            d+=incrSE;
                            x++;
                            y--;
                        }
                    }
                    drawPixel(x,y);
                }
            }else if(y2<0){
                while (y > y2)
                {
                    if (d <= 0) {
                        d+=increS;
                        y--;
                    }
                    else {
                        d+=incrSE;
                        x++;
                        y--;
                    }
                    drawPixel(x,y);
                }
                }

            }




}

static void drawCircle(int a, int b, int rds)
{
    int x =0;
    int y=rds;
    int h= 1-rds;
    //drawPixel(x,y);
    while(y>x){
        if(h<0)
        {
            h+=2*x+3;
            x++;
        }else{
            h+=2*(x-y) +5;
            x++;
            y--;
        }
        drawPixel(x+a,y+b);
        drawPixel(x+a,-y+b);
        drawPixel(-x+a,y+b);
        drawPixel(-x+a,-y+b);
        drawPixel(y+a,x+b);
        drawPixel(y+a,-x+b);
        drawPixel(-y+a,x+b);
        drawPixel(-y+a,-x+b);

    }
}
static void centerFind(int x1, int y1, int x2, int y2, int x3, int y3)
{
    float xm=(x1+x2)/2;
    float ym=(y1+y2)/2;
    float xmp=(x2+x3)/2;
    float ymp=(y2+y3)/2;
    float a=ym-y3;
    float b=ymp-y1;
    float c=xmp;
    float d=xm-x3;
    float e=xmp-x1;
    float y=(1/((d*a*e/b)-1))*((d*a*e*ymp/b)-(c*a/d));
    float x=(((y-ymp)*e)/b)+xmp;
    centerx=(int)x;
    centery=(int)y;
    drawPixel(centerx,centery);
}


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,0,0);

    glPushMatrix();
    for(i=-5000; i<5000; i++)   drawPixel(i,0);
    for(i=-5000; i<5000; i++)   drawPixel(0,i);
//what i do
    int x11=0,y11=0,x12=320,y12=80;
    drawLine(x11,y11,x12,y12);
    int x21=0,y21=0,x22=40,y22=30;
    drawLine(x21,y21,x22,y22);
    int x31=40,y31=30,x32=320,y32=80;
    drawLine(x31,y31,x32,y32);

    centerFind(x11, y11,  x21,  y21,  x31,  y31);
    drawCircle(centerx,centery,8);

    glPopMatrix();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    //cout<<"ljl";
    glutMainLoop();

    return EXIT_SUCCESS;
}
