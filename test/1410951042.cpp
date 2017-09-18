
#include<windows.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include<iostream>
using namespace std;
//using namespace std;

int centerx;
int centery;
int n;
bool rendered=false;
int *arrx;
int *arry;
float angle= 1;
int LOD=90000;
int g[4][4]={
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

	}
	return Matrix;
}








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


void drawPixel(int x, int y,int z)
{

	glBegin(GL_POINTS);
    glVertex3d(x,y,z);
	glEnd();
}


/* GLUT callback Handlers */


static void hermite()
{
    int **G;
    G=new int*[4];

    for(int i=0;i<4;i++)
	{
		G[i]=new int[4];//the ith array is initialized
		for(int j=0;j<3;j++)		//the i,jth element is defined
		{
			//cout<<"Enter element in row "<<(i+1)<<" and column "<<(j+1)<<": ";
			cin>>G[i][j];
		}
	}
	for(int i=0;i<4;i++)
	{
		G[i]=new int[4];//the ith array is initialized
		for(int j=0;j<3;j++)		//the i,jth element is defined
		{
			//cout<<"Enter element in row "<<(i+1)<<" and column "<<(j+1)<<": ";
			cin>>G[i][j];
		}
	}
    G[0][3]=1;G[1][3]=1;G[2][3]=0;G[3][3]=0;


    for(int i=0;i<=LOD;++i) {
 angle= angle + 1.14/180 ;
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

        //code for rotation about z axis will start here
        //x=x*cos(angle)-y*sin(angle);
        //y=x*sin(angle)+y*cos(angle);
        //drawPixel(x,y);



		// projection is getting started :p
		int **mat3d=createMatrix(4,1);
		mat3d[0][0]=x;mat3d[1][0]=y;mat3d[2][0]=z;mat3d[3][0]=1;

		int zp=10;
		float q=((x-0)*(x-0)+(y-0)*(y-0)+(z-zp)*(z-zp));
		float dx=(x-0)/q;
		float dy=(y-0)/q;
		float dz=(z-zp)/q;
		int **mGeneral=createMatrix(4,4);       //creating mgeneral
		mGeneral[0][0]=1;   mGeneral[0][1]=0;   mGeneral[0][2]=-dx/dz;      mGeneral[0][3]=zp*(dx/dz);
		mGeneral[1][0]=0;   mGeneral[1][1]=1;   mGeneral[1][2]=-dx/dz;      mGeneral[1][3]=zp*(dx/dz);
		mGeneral[2][0]=0;   mGeneral[2][1]=0;   mGeneral[2][2]=-zp/(q*dz);  mGeneral[2][3]=((zp*zp)/(q*dz))+zp;
		mGeneral[3][0]=0;   mGeneral[3][1]=0;   mGeneral[3][2]=-1/(q*dz);   mGeneral[3][3]=((zp)/(q*dz))+1;
		int **homogen=createMatrix(4,1);
		homogen=multiMatrix(mGeneral,mat3d,4,4,4,1);

		//now i am going to homogenizing the resultant matrix and all the z will be same which in this case is zp=1
		if(homogen[3][0]!=0 && homogen[3][0]!=1){
            for(int jo=0;jo<4;jo++)
            {

                homogen[jo][0]=homogen[jo][0]/homogen[3][0];
            }
		}
        //done homogenizing
        x=homogen[0][0];
        y=homogen[1][0];
        x=x*cos(angle)-y*sin(angle);
        y=x*sin(angle)+y*cos(angle);
		//drawPixel(x,y);
		//cout<<homogen[1][0];

	}

}

namespace Cube {


    GLint vertice[8][3] = {
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
      {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

    GLint surface[6][4] = {
      {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
      {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

    GLfloat vertexColors[8][3] = {
      {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
      {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

    void draw() {
      glBegin(GL_QUADS);
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
          glColor3fv((GLfloat*)&vertexColors[surface[i][j]]);
          glVertex3iv((GLint*)&vertice[surface[i][j]]);
        }
      }
      glEnd();
    }
}
float vim;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  Cube::draw();
  glFlush();
  glutSwapBuffers();
}



void timer(int v) {
  static GLfloat u = 0.0;
  u += 0.01;
  vim=u;
  glLoadIdentity();
  gluLookAt(2u,2u,2u,.5,.5,.5,cos(u-35)*9-sin(u*u), cos(u/16), -8*cos(u+23));
  glutPostRedisplay();
  //glutMouseFunc()
  if(MOUSE_MOVED)
    glutTimerFunc(1000/60.0, timer, v);
}



static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    //glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
    gluPerspective(60.0, GLfloat(width) / GLfloat(height), 0.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity() ;
}


void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
    cout<<"give me all the 8 points"<<endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutCreateWindow("test");
  glutReshapeFunc(resize);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  init();
  hermite();
  glutMainLoop();
}
