//
//  main.cpp
//  OpenGL
//
//  Created by Irina on 24/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <math.h>
#include "free_camera.h"
#include "models.h"

using namespace std;

void display(void);
void reshape(int, int);

bool good(int i, int siz)
{
    return (i < siz)&&(i >= 0);
}

GLfloat rtri;
float vel = 0.0f;

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    /* set the window size to 512 x 512 */
    glutInitWindowSize(1024, 630);
    
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
    if (deltaMove || deltaMove_Sides || deltaMove_Y)
        computePos(deltaMove, deltaMove_Sides, deltaMove_Y);
    
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
    
    ifstream in;
    in.open("/Users/irina/VMMORPG/chunck.txt");

    string is;
    in >> is;
  //  std::cout << is;
    in.close();

    int wid = 16;
    int hei = 256;
    int dee = 16;

    glPushMatrix();
    glRotatef(rtri, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < wid; i++)
        for (int j = 0; j < hei; j++)
            for (int k = 0; k < dee; k++)
                if (is[i*hei*dee + j*dee + k] == '1')
                {
                    if (!(good((i-1)*hei*dee + j*dee + z, is.size())) || is[(i-1)*hei*dee + j*dee + z] == '0')
                        drawModel::plain_side(j, k, j+1, k+1, i);
                    if (!(good((i+1)*hei*dee + j*dee + z, is.size())) || is[(i+1)*hei*dee + j*dee + z] == '0')
                        drawModel::plain_side_reversed(j, k, j+1, k+1, i+1);
                    if (!(good(i*hei*dee + (j-1)*dee + z, is.size())) || is[i*hei*dee + (j-1)*dee + z] == '0')
                        drawModel::plain_top(i, k, i+1, k+1, j);
                    if (!(good(i*hei*dee + (j+1)*dee + z, is.size())) || is[i*hei*dee + (j+1)*dee + z] == '0')
                        drawModel::plain_top_reversed(i, k, i+1, k+1, j+1);
                    if (!(good(i*hei*dee + j*dee + (z-1), is.size())) || is[i*hei*dee + j*dee + (z-1)] == '0')
                        drawModel::plain_front(i, j, i+1, j+1, k);
                    if (!(good(i*hei*dee + j*dee + (z+1), is.size())) || is[i*hei*dee + j*dee + (z+1)] == '0')
                        drawModel::plain_front_reversed(i, j, i+1, j+1, k+1);
                }

    drawModel::plain_side(0, 0, 1, 1, 0);
    
    glEnd();
    
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
