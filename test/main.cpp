
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include<math.h>
using namespace std;
#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

//int i1,j1a,i2,j2,i3,j3;
//int xc,yc;
//int radius;
/* GLUT callback Handlers */
void drawPixel(float x, float y, float z)
{
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
}






static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);

   // glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    int i;

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    glPushMatrix();

    //for(i=-1000; i<1000; i++)   drawPixel(i,0,0);
    //for(i=-1000; i<1000; i++)   drawPixel(0,i,0);

    glBegin(GL_QUADS);
    glColor3f(0.0f,1.0f,0.0f);    // blue
    drawPixel( 1.0f, 1.0f,-1.0f);
    drawPixel(-1.0f, 1.0f,-1.0f);
    drawPixel(-1.0f, 1.0f, 1.0f);
    drawPixel( 1.0f, 1.0f, 1.0f);

    glColor3f(1.0f,0.5f,0.0f);    // orange
    drawPixel( 1.0f,-1.0f, 1.0f);
    drawPixel(-1.0f,-1.0f, 1.0f);
    drawPixel(-1.0f,-1.0f,-1.0f);
    drawPixel( 1.0f,-1.0f,-1.0f);

    glColor3f(1.0f,0.0f,0.0f); //red
    drawPixel( 1.0f, 1.0f, 1.0f);
    drawPixel(-1.0f, 1.0f, 1.0f);
    drawPixel(-1.0f,-1.0f, 1.0f);
    drawPixel( 1.0f,-1.0f, 1.0f);

    glColor3f(1.0f,1.0f,0.0f);    // yellow
    drawPixel( 1.0f,-1.0f,-1.0f);
    drawPixel(-1.0f,-1.0f,-1.0f);
    drawPixel(-1.0f, 1.0f,-1.0f);
    drawPixel( 1.0f, 1.0f,-1.0f);

    glColor3f(0.0f,0.0f,1.0f);    // blue
    drawPixel(-1.0f, 1.0f, 1.0f);
    drawPixel(-1.0f, 1.0f,-1.0f);
    drawPixel(-1.0f,-1.0f,-1.0f);
    drawPixel(-1.0f,-1.0f, 1.0f);

    glColor3f(1.0f,0.0f,1.0f);    // magenta
    drawPixel( 1.0f, 1.0f,-1.0f);
    drawPixel( 1.0f, 1.0f, 1.0f);
    drawPixel( 1.0f,-1.0f, 1.0f);
    drawPixel( 1.0f,-1.0f,-1.0f);

    glEnd();
    glFlush();


    glPopMatrix();

    glutSwapBuffers();
}

static void onMouseClick()
{

}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);



    glutMainLoop();

    return EXIT_SUCCESS;
}
