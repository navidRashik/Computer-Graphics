
#include<windows.h>
//#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>

#include <math.h>


//using namespace std;

int centerx;
int centery;
int n;
bool rendered=false;
int *arrx;
int *arry;
float angle= 1;


void drawPixel(int x, int y)
{

	glBegin(GL_POINTS);
    glVertex2i(x,y);
	glEnd();
}
static void drawLine(int x1, int y1, int x2, int y2)
{


    int x,y;


    if(x1>x2){
        x=x2;
        y=y2;

        x2=x1; y2=y1;
    }else{
        x=x1;
        y=y1;
    }



    float dx=x2-x;
    float dy=y2-y;
    float slope = dy/dx;

    if(slope== 0)
    {
        drawPixel(x,y);
        while(x<=x2)
        {
            drawPixel(x,y);
            x++;
            //Y++
        }
    }
    else if(slope== +1)
    {
        //drawPixel(x,y);
        while(x<=x2)
        {
            drawPixel(x,y);
            x++;
            y++;
        }
    }

    else if(slope==INFINITY)
        {
            while(y<=y2)
            {
                drawPixel(x,y);
                y++;
            }
        }
    else if(slope==-INFINITY)
        {
            while(y>=y2)
            {
                drawPixel(x,y);
                y--;
            }
        }
    else if(slope== -1)
    {
        drawPixel(x,y);
        while(x<=x2)
        {
            drawPixel(x,y);
            x++;
            y--;
        }
    }
    else if(1>slope && slope>0) //0-45
    {
        int d=2*dy-dx;
        int increE=2*dy;
        int incrNE=2*(dy-dx);
        drawPixel(x,y);

            while (x <= x2 )
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
    else if( slope>1) //45-90
    {

            int d=dy-2*dx;
            int increN=2*(-dx);
            int incrNE=2*(dy-dx);
            drawPixel(x,y);

                while (x <= x2)
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


        }
    else if(-1<slope && slope<0) //315-360
    {

            int d=2*dy+dx;
            int increE=2*dy;
            int incrSE=2*(dy+dx);
            drawPixel(x,y);

                while (x <= x2 )
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


        }


    else  if( slope<-1)   //270-315 //no equal
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

static void polygon_navid()
{


    int firstx,firsty;
    int x1tem,y1tem,xtem,ytem;


    if(!rendered){

        for(int i=0;i<n;i++){
            cin>>xtem;
            cin>>ytem;
            arrx[i]=xtem;
            arry[i]=ytem;
            if(i==0){
                firstx=xtem;
                firsty=ytem;

                x1tem=xtem;
                y1tem=ytem;
            }else{
                drawLine(x1tem,y1tem,xtem,ytem);
                x1tem=xtem;
                y1tem=ytem;
            }
        }
        drawLine(x1tem,y1tem,firstx,firsty);
        rendered=true;
    }else if(rendered){
         angle= angle + 1.14/180 ;
        for(int i=0;i<n;i++){
            //xtem=arrx[i];
            //ytem=arry[i];
            //xtem=arrx[i]*cos(angle)-arry[i]*sin(angle);
            //ytem=arry[i]*cos(angle)-arrx[i]*sin(angle);
            xtem=arrx[i]*cos(angle)-arry[i]*sin(angle);
            ytem=arrx[i]*sin(angle)+arry[i]*cos(angle);
            if(i==0){
                firstx=xtem;
                firsty=ytem;

                x1tem=xtem;
                y1tem=ytem;
            }else{
                drawLine(x1tem,y1tem,xtem,ytem);
                x1tem=xtem;
                y1tem=ytem;
            }
        }
        drawLine(x1tem,y1tem,firstx,firsty);
        //drawLine(x1tem,y1tem,firstx,firsty);

    }
}


static void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,0,0);

    glPushMatrix();
    for(i=-5000; i<5000; i++){  drawPixel(i,0);}
    for(i=-5000; i<5000; i++){   drawPixel(0,i);}
//what i do

    polygon_navid();        //  4 -55 0 55 0 0 -55 0 55


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
    cin>>n;
    arrx=new int[n];
    arry=new int[n];
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
