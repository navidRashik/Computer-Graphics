
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
int G[4][4]={
	{ 110,110,0,1 },	//	Point1
	{-100,115,-312,1 },	//	Point2
	{ 5,-50,0 ,0 },	//	Tangent1
	{ 5,100,0 ,0 }		//	Tangent2
};
int **createMatrix(int rows,int columns)
{
    int **Matrix;
    Matrix=new int*[rows];
    for(int i=0;i<rows;i++)
	{
		Matrix[i]=new int[columns];//the ith array is initialized


		for(int j=0;j<columns;j++)		//the i,jth element is defined
		{
			//cout<<"Enter element in row "<<(i+1)<<" and column "<<(j+1)<<": ";
			cin>>Matrix[i][j];
		}
	}
	return Matrix;
}

int **multiMatrix(int **matrix1,int **matrix2,int r1,int c1,int r2,int c2)
{
    int **mult;
    mult=new int*[r1];
    for(int i = 0; i < r1; ++i)
	{
        mult[i]=new int[c2];//the ith array is initialized
        for(int j = 0; j < c2; ++j)
        {
            mult[i][j]=0;
            for(int k = 0; k < c1; ++k)
            {
                mult[i][j]+= matrix1[i][k] * matrix2[k][j];
            }
        }
	}
	return mult;
}
void matdel(int **matrix, int rows)
{
    for(int i=0;i<rows;i++)
		delete[] matrix[i];
	delete[] matrix;
    //c++ can delete up to 1 dimensional vectors
}

void drawPixel(int x, int y)
{

	glBegin(GL_POINTS);
    glVertex2i(x,y);
	glEnd();
}
void drawPixel(int x, int y,int z)
{

	glBegin(GL_POINTS);
    glVertex3d(x,y,z);
	glEnd();
}
int LOD=90000;

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


static void hermite()
{
    for(int i=0;i<=LOD;++i) {

		float t = (float)i/(LOD);

		// calculate blending functions
		float a =  2*t*t*t - 3*t*t + 1;
		float b = -2*t*t*t + 3*t*t;
		float c = t*t*t - 2*t*t + t;
		float d = t*t*t - t*t;

		// calculate the x,y and z of the curve point
		float x = a*G[0][0] +
				  b*G[1][0] +
				  c*G[2][0] +
				  d*G[3][0] ;

		float y = a*G[0][1] +
				  b*G[1][1] +
				  c*G[2][1] +
				  d*G[3][1] ;

		float z = a*G[0][2] +
				  b*G[1][2] +
				  c*G[2][2] +
				  d*G[3][2] ;

		// specify the point
		drawPixel(x,y,z);
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

    //polygon_navid();        //  4 -55 0 55 0 0 -55 0 55
    hermite();

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
    cout<<"give P1x,P1y,P1z,P4x,P4y,P4z,R1x,R1y,R1z,R4x,R4y,R4z "<<endl;
    /*for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>G[i][j];
        }
    }
    */
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






