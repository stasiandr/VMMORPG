//
//  main.cpp
//  OpenGL
//
//  Created by Irina on 24/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include "glut.h"
#include "glu.h"
#include <math.h>
#include "free_camera.h"
#include "models.h"

using namespace std;

void display(void);
void reshape(int, int);
/* Drawing one chunk function*/
void chunks(string);
/*Getting one chunk-string function*/
string getchunk(const char *);

int wid = 16;
int hei = 16;
int dee = 16;

bool bad(int i, int j, int k)
{
    if (i >= 0 && j >= 0 && k >= 0)
        if (i < wid && j < hei && k < dee)
        {
            return false;
        }
    return true;
}
int okr(float n)
{
    int s = (int)n;
    if (n >= s and n < s+1)
        return s;
    else if (n >= s+1 and n < s+2)
        return s;
}

float * posses;
float st[3];
bool blocker [6];

GLfloat rtri;
float vel = 0.0f;

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

const char * fns[16];
string iss[16];

void Update()
{
    for(int i = 0; i < 16; ++i)
        iss[i] = getchunk(fns[i]);
}
int main(int argc, char** argv)
{
    st[0] = 0.0f;
    st[1] = 10.0f;
    st[2] = 0.0f;
    posses = st;

    fns[0] = "00.VMC";
    fns[1] = "01.VMC";
    fns[2] = "02.VMC";
    fns[3] = "03.VMC";

    fns[4] = "10.VMC";
    fns[5] = "11.VMC";
    fns[6] = "12.VMC";
    fns[7] = "13.VMC";

    fns[8] = "20.VMC";
    fns[9] = "21.VMC";
    fns[10] = "22.VMC";
    fns[11] = "23.VMC";

    fns[12] = "30.VMC";
    fns[13] = "31.VMC";
    fns[14] = "32.VMC";
    fns[15] = "33.VMC";

    Update();

    glutInit(&argc, argv);

    /* set the window size to 512 x 512 */
    glutInitWindowSize(1300, 690);

    /* set the display mode to Red, Green, Blue and Alpha
     allocate a depth buffer
     enable double buffering
     */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* create the window (and call it Lab 1) */
    glutCreateWindow("Lab 1");

    /* set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);

    /* set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is
     first created
     */
    glutReshapeFunc(reshape);

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(processNormalKeysRelease);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glEnable(GL_CULL_FACE);

    /* set the default background color to black */
    glClearColor(0,0,0,1);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);



    /* enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();

    return 0;
}






/*! glut display callback function.  Every time the window needs to be drawn,
 glut will call this function.  This includes when the window size
 changes, or when another window covering part of this window is
 moved so this window is uncovered.
 */
void display(void)
{

    /* clear the color buffer (resets everything to black) */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* set the current drawing color to red */


    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glTranslatef(0.0f, 0.0f,0.0f);

    gluLookAt(	x, y, z,
              x+lx, y+ly,  z+lz,
              0.0f, 1.0f,  0.0f);

    //---
    if (deltaMove || deltaMove_Sides || deltaMove_Y)
        posses = computePos(deltaMove, deltaMove_Sides, deltaMove_Y);

    for(int i = 0; i < 16; ++i)
        chunks(iss[i]);

    deltaMove_Y -= 0.01f;
    if (blocker[0])
        if (deltaMove_Y < 0)
            deltaMove_Y = 0;
    if (blocker[1])
        if (deltaMove_Y > 0)
            deltaMove_Y = 0;

    for(int b = 0; b < 6; ++b)
       blocker[b] = false;

    glPopMatrix();

    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

    glVertex3f(-1000, 0, 0);
    glVertex3f(1000, 0, 0);

    glVertex3f(0, -1000, 0);
    glVertex3f(0, 1000, 0);

    glVertex3f(0, 0, -1000);
    glVertex3f(0, 0, 1000);

    glEnd();

    glPopMatrix();


        /* swap the back and front buffers so we can see what we just drew */
    glutSwapBuffers();

//    float acc = 0.01f;
//    vel += acc;

    glutPostRedisplay();
}

int powm(int n, int m)
{
    int r = 1;
    for (int i = 0; i < m; ++i)
        r *= n;
    return r;
}

void chunks(string is)
{
    int x = 0;
    int y = 0;
    int z = 0;
    int de = 12;

    for (int i = 0; i < 12; ++i)
    {
        if (i < 4)
            x += (((int)is[i] - 48) * powm(10, 3-(i%4)));
        else if (i < 8)
            y += (((int)is[i] - 48) * powm(10, 3-(i%4)));
        else if (i < 12)
            z += (((int)is[i] - 48) * powm(10, 3-(i%4)));
    }
    //cout << x << ' ' << y << ' ' << z << endl;
    glPushMatrix();
    glRotatef(rtri, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    int tx = (int)posses[0];
    int ty = (int)posses[1]-1;
    int tz = (int)posses[2];
    for (int i = 0; i < wid; i++)
        for (int j = 0; j < hei; j++)
            for (int k = 0; k < dee; k++)
                if (is[i*hei*dee + j*dee + k + de] == '1')
                {
                    if (j+y*hei == ty && (i+x*wid == tx || i+x*wid == tx+1) && (k+z*dee == tz || k+z*dee == tz+1))
                        blocker[0] = true;
                    if (j+y*hei == ty+1 && (i+x*wid == tx || i+x*wid == tx+1) && (k+z*dee == tz || k+z*dee == tz+1))
                        blocker[1] = true;
                    //chunk's borders drawing - BEGIN
                    //drawModel::cube(i+x*wid, j+y*hei, k+z*dee);
                    if (bad(i-1, j, k))
                    {
                        drawModel::plain_side(j+y*hei, k+z*dee, j+y*hei+1, k+z*dee+1, i+x*wid, 1.0f, 0.0f, 0.0f);
                    }
                    if (bad(i+1, j, k))
                        drawModel::plain_side_reversed(j+y*hei, k+z*dee, j+y*hei+1, k+z*dee+1, i+x*wid+1, 1.0f, 0.0f, 1.0f);
                    if (bad(i, j-1, k))
                        drawModel::plain_top_reversed(i+x*wid, k+z*dee, i+x*wid+1, k+z*dee+1, j+y*hei, 1.0f, 1.0f, 0.0f);
                    if (bad(i, j+1, k))
                        drawModel::plain_top(i+x*wid, k+z*dee, i+x*wid+1, k+z*dee+1, j+y*hei+1, 0.0f, 1.0f, 0.0f);
                    if (bad(i, j, k-1))
                        drawModel::plain_front(i+x*wid, j+y*hei, i+x*wid+1, j+y*hei+1, k+z*dee, 0.0f, 1.0f, 1.0f);
                    if (bad(i, j, k+1))
                        drawModel::plain_front_reversed(i+x*wid, j+y*hei, i+x*wid+1, j+y*hei+1, k+z*dee+1, 0.0f, 0.0f, 1.0f);
                    // chunk's borders drawing - END
                    if (is[(i-1)*wid*dee + j*dee + k + de] == '0')
                        drawModel::plain_side(j+y*hei, k+z*dee, j+y*hei+1, k+z*dee+1, i+x*wid, 1.0f, 0.0f, 0.0f);
                    if (is[(i+1)*wid*dee + j*dee + k + de] == '0')
                        drawModel::plain_side_reversed(j+y*hei, k+z*dee, j+y*hei+1, k+z*dee+1, i+x*wid+1, 1.0f, 0.0f, 1.0f);
                    if (is[i*wid*dee + (j-1)*dee + k + de] == '0')
                        drawModel::plain_top_reversed(i+x*wid, k+z*dee, i+x*wid+1, k+z*dee+1, j+y*hei, 1.0f, 1.0f, 0.0f);
                    if (is[i*wid*dee + (j+1)*dee + k + de] == '0')
                        drawModel::plain_top(i+x*wid, k+z*dee, i+x*wid+1, k+z*dee+1, j+y*hei+1, 0.0f, 1.0f, 0.0f);
                    if (is[i*wid*dee + j*dee + k-1 + de] == '0')
                        drawModel::plain_front(i+x*wid, j+y*hei, i+x*wid+1, j+y*hei+1, k+z*dee, 0.0f, 1.0f, 1.0f);
                    if (is[i*wid*dee + j*dee + k+1 + de] == '0')
                        drawModel::plain_front_reversed(i+x*wid, j+y*hei, i+x*wid+1, j+y*hei+1, k+z*dee+1, 0.0f, 0.0f, 1.0f);
                }

    glEnd();
}
string getchunk(const char *fn)
{
    ifstream in;
    in.open(fn);

    string is;
    in >> is;
    in.close();
    return is;
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
    /* tell OpenGL we want to display in a recangle that is the
     same size as the window
     */
    glViewport(0,0,width,height);

    /* switch to the projection matrix */
    glMatrixMode(GL_PROJECTION);

    /* clear the projection matrix */
    glLoadIdentity();

    /* set the camera view, orthographic projection in 2D */
    gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 400.0f );

    /* switch back to the model view matrix */
    glMatrixMode(GL_MODELVIEW);
}
