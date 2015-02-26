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

float abs(float etwas)
{
    if (etwas < 0)
        etwas = -etwas;
    return etwas;
}

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

GLuint Texture;

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

GLuint loadBMP_custom(const char * imagepath)
{
    // Данные, прочитанные из заголовка BMP-файла
    unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
    unsigned int dataPos;     // Смещение данных в файле (позиция данных)
    unsigned int width, height;
    unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3
    // RGB-данные, полученные из файла
    unsigned char * data;
    FILE * file = fopen(imagepath,"rb");
    if (!file) {
      printf("Изображение не может быть открыто\n");
      return 0;
    }
    if ( fread(header, 1, 54, file) != 54 ) { // Если мы прочитали меньше 54 байт, значит возникла проблема
        printf("Некорректный BMP-файл\n");
        return false;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Некорректный BMP-файл\n");
        return 0;
    }
    // Читаем необходимые данные
    dataPos    = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
    imageSize  = *(int*)&(header[0x22]); // Размер изображения в байтах
    width      = *(int*)&(header[0x12]); // Ширина
    height     = *(int*)&(header[0x16]); // Высота
    // Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
    if (imageSize==0)    imageSize=width*height*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
    if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком
    // Создаем буфер
    data = new unsigned char [imageSize];

    // Считываем данные из файла в буфер
    fread(data,1,imageSize,file);

    // Закрываем файл, так как больше он нам не нужен
    fclose(file);

    // Создадим одну текстуру OpenGL
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Передадим изображение OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

void Update()
{
    for(int i = 0; i < 16; ++i)
        iss[i] = getchunk(fns[i]);
}
int main(int argc, char** argv)
{
    st[0] = 10.0f;
    st[1] = 10.0f;
    st[2] = 10.0f;
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

    GLuint Texture = loadBMP_custom("uvtemplate.bmp");

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

    for(int i = 0; i < 16; ++i)
        chunks(iss[i]);

    deltaMove_Y -= 0.017f;

    float reserveDeltaMove = deltaMove;
    float reserveDeltaMove_Sides = deltaMove_Sides;

    if (blocker[0])
        if (deltaMove_Y < 0)
            deltaMove_Y = 0;
    if (blocker[1])
        if (deltaMove_Y > 0)
            deltaMove_Y = 0;
    if (blocker[2])
        if (deltaMove > 0)
            deltaMove = 0;
    if (blocker[3])
        if (deltaMove < 0)
            deltaMove = 0;
    if (blocker[4])
        if (deltaMove_Sides > 0)
            deltaMove_Sides = 0;
    if (blocker[5])
        if (deltaMove_Sides < 0)
            deltaMove_Sides = 0;

    if (deltaMove || deltaMove_Sides || deltaMove_Y)
        posses = computePos(deltaMove, deltaMove_Sides, deltaMove_Y);

    deltaMove = reserveDeltaMove;
    deltaMove_Sides = reserveDeltaMove_Sides;

    for(int b = 0; b < 6; ++b)
       blocker[b] = false;

    glPopMatrix();

    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

    glVertex3f(-1000, 0, 0);
    glVertex3f(1000, 0, 0);

    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);

    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, 20);

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
    glPushMatrix();
    glRotatef(rtri, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    float tx = posses[0] - 0.5f;
    float ty = posses[1] - 1.5f;
    float tz = posses[2] - 0.5f;

    for (int i = 0; i < wid; i++)
        for (int j = 0; j < hei; j++)
            for (int k = 0; k < dee; k++)
                if (is[i*hei*dee + j*dee + k + de] == '1')
                {
                    float xbc = i+x*wid;
                    float ybc = j+y*hei;
                    float zbc = k+z*dee;
                    if ((ty > ybc && ty - ybc < 1.0f) && (abs(xbc - tx) <= 0.5f) && (abs(zbc - tz) <= 0.5f)) // not to fall through blocks
                        blocker[0] = true;
                    if ((ty + 1.0f < ybc && ybc - (ty + 1.0f) < 1.0f) && (abs(xbc - tx) <= 0.5f) && (abs(zbc - tz) <= 0.5f)) // not to jump into the upper block
                        blocker[1] = true;

                    if (((tx + 1.0f) > xbc && (tx + 1.0f) - xbc < 1.0f) && (abs(ybc - ty - 1) < 1.0f) && (abs(tz - zbc) < 0.55f))
                        blocker[2] = true;
                    if ((tx > xbc && tx - xbc < 1.0f) && (abs(ybc - ty - 1) < 1.0f) && (abs(tz - zbc) < 0.55f))
                        blocker[3] = true;

                    if (((tz + 1.0f) > zbc && (tz + 1.0f) - zbc < 1.0f) && (abs(ybc - ty - 1) < 1.0f) && (abs(tx - xbc) < 0.55f))
                        blocker[4] = true;
                    if ((tz > zbc && tz - zbc < 1.0f) && (abs(ybc - ty - 1) < 1.0f) && (abs(tx - xbc) < 0.55f))
                        blocker[5] = true;
                    //chunk's borders drawing - BEGIN
                    //drawModel::cube(xbc, ybc, zbc);
                    if (bad(i-1, j, k))
                        drawModel::plain_side(ybc, zbc, ybc+1, zbc+1, xbc, 1.0f, 0.0f, 0.0f);
                    if (bad(i+1, j, k))
                        drawModel::plain_side_reversed(ybc, zbc, ybc+1, zbc+1, xbc+1, 1.0f, 0.0f, 1.0f);
                    if (bad(i, j-1, k))
                        drawModel::plain_top_reversed(xbc, zbc, xbc+1, zbc+1, ybc, 1.0f, 1.0f, 0.0f);
                    if (bad(i, j+1, k))
                        drawModel::plain_top(xbc, zbc, xbc+1, zbc+1, ybc+1, 0.0f, 1.0f, 0.0f);
                    if (bad(i, j, k-1))
                        drawModel::plain_front(xbc, ybc, xbc+1, ybc+1, zbc, 0.0f, 1.0f, 1.0f);
                    if (bad(i, j, k+1))
                        drawModel::plain_front_reversed(xbc, ybc, xbc+1, ybc+1, zbc+1, 0.0f, 0.0f, 1.0f);
                    // chunk's borders drawing - END
                    if (is[(i-1)*wid*dee + j*dee + k + de] == '0')
                        drawModel::plain_side(ybc, zbc, ybc+1, zbc+1, xbc, 1.0f, 0.0f, 0.0f);
                    if (is[(i+1)*wid*dee + j*dee + k + de] == '0')
                        drawModel::plain_side_reversed(ybc, zbc, ybc+1, zbc+1, xbc+1, 1.0f, 0.0f, 1.0f);
                    if (is[i*wid*dee + (j-1)*dee + k + de] == '0')
                        drawModel::plain_top_reversed(xbc, zbc, xbc+1, zbc+1, ybc, 1.0f, 1.0f, 0.0f);
                    if (is[i*wid*dee + (j+1)*dee + k + de] == '0')
                        drawModel::plain_top(xbc, zbc, xbc+1, zbc+1, ybc+1, 0.0f, 1.0f, 0.0f);
                    if (is[i*wid*dee + j*dee + k-1 + de] == '0')
                        drawModel::plain_front(xbc, ybc, xbc+1, ybc+1, zbc, 0.0f, 1.0f, 1.0f);
                    if (is[i*wid*dee + j*dee + k+1 + de] == '0')
                        drawModel::plain_front_reversed(xbc, ybc, xbc+1, ybc+1, zbc+1, 0.0f, 0.0f, 1.0f);
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
