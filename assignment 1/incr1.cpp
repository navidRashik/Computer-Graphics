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












void drawPixel(int x, int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

static void drawLine(int x1, int y1, int x2, int y2)
{
    int x,y;

    if(x1>x2)
    {
        x=x2;
        y=y2;

        x2=x1;
        y2=y1;
    }
    else
    {
        x=x1;
        y=y1;
    }
        float dy=y2-y;
        //cout<<dy;
        float dx=x2-x;

        float slope = dy/dx;
        //cout<<slope;
        if(slope==0)
        {
            while(x<=x2)
            {
                drawPixel(x,y);
                x++;
            }
        }
        else if(slope==+1)
            {
                while(x<=x2)
                {
                    drawPixel(x,y);
                    x++;
                    y++;
                }
            }
        else if(slope==-1)
            {
                while(x<=x2)
                {
                    drawPixel(x,y);
                    x++;
                    y--;
                }
            }
       else if(slope>0 && slope <1)
        {

            int d=2*dy-dx;
            int increE=2*dy;
            int incrNE=2*(dy-dx);
            drawPixel(x,y);
            while (x <= x2)
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
        }
        else if(slope>1)
        {

            int d=dy-2*dx;
            int increN=2*(-dx);
            int incrNE=2*(dy-dx);
            drawPixel(x,y);
            while (x <= x2)
            {
            if (d <= 0) {
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
        else if(slope>-1 && slope<0)
        {

            int d=2*dy+dx;
            int increE=2*dy;
            int incrSE=2*(dy+dx);
            drawPixel(x,y);
            while (x <= x2)
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
        else if(slope<-1)
            {

                int d=2*dx+dy;
                int increS=2*dx;
                int incrSE=2*(dx+dy);
                drawPixel(x,y);

                while (x <= x2)
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
static void centerFromTangents(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int x,y;
    float mx=(x1+x2)/2;
    float my=(y1+y2)/2;
    if(x1>x2)
    {
        x=x2;
        y=y2;

        x2=x1;
        y2=y1;
    }
    else
    {
        x=x1;
        y=y1;
    }
    float dy=y2-y;
    float dx=x2-x;
    float slope = dy/dx;
    float mslope = (-1/slope);

    int x_a,y_a;
    float mx1=(x1+x3)/2;
    float my1=(x1+x3)/2;
    if(x1>x3)
    {
        x_a=x3;
        y_a=y3;

        x3=x1;
        y3=y1;
    }
    else
    {
        x_a=x1;
        y_a=y1;
    }
    float dy_a=y3-y_a;
    float dx_a=x3-x_a;
    float slope_a = dy_a/dx_a;
    float mslope_a = (-1/slope_a);

    int xn,yn;

    int c1=my-(mslope*mx);
    int c2=my1-(mslope_a*mx1);

     xn=(c2-c1)/(mslope-mslope_a);
     yn= (xn*mslope)+c1;
        drawPixel(xn,yn);
    //cout<<xn;
    //cout<<yn;

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
    for(i=-500; i<500; i++)   drawPixel(i,0);
    for(i=-500; i<500; i++)   drawPixel(0,i);
//what i do
    int x11=50,y11=20,x12=10,y12=20;
    int x1=(x11+x12)/2, y1=(y11+y12)/2;
    drawLine(50,20,10,20);
    int x21=10,y21=20,x22=40,y22=30;
    int x2=(x21+x22)/2, y2=(y21+y22)/2;
    drawLine(10,20,40,30);
    int x31=40,y31=30,x32=50,y32=20;
    int x3=(x31+x32)/2, y3=(y31+y32)/2;
    drawLine(40,30,50,20);
    centerFromTangents(x1, y1,  x2,  y2,  x3,  y3);

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
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
