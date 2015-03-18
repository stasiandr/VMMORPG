//
//  main.cpp
//  OpenGL
//
//  Created by Irina on 24/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//
//#pragma comment(lib,"glaux.lib")

#ifdef _WIN32
    #include <windows.h>
    #include "Headers\glut.h"
    #include "Headers\glu.h"
    #include "Headers\glaux.h"
#elif TARGET_OS_MAC
    #include <GL/glut.h>
    #include <GL/glu.h>
    #include <GL/glaux.h>
#endif


#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

static HGLRC hRC;		// Постоянный контекст рендеринга
static HDC hDC;			// Приватный контекст устройства GDI

GLuint textures[6];
unsigned char * datas[6];
unsigned int widths[6];
unsigned int heights[6];

void loadBMP_custom(const char * imagepath, int ind)
{
    // Данные, прочитанные из заголовка BMP-файла
    unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
    unsigned int dataPos;     // Смещение данных в файле (позиция данных)
    unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3
    // RGB-данные, полученные из файла
    FILE * file = fopen(imagepath,"rb");
    if (!file) {
      cout << "1Изображение не может быть открыто\n";
      return;
    }
    if ( fread(header, 1, 54, file) != 54 ) { // Если мы прочитали меньше 54 байт, значит возникла проблема
        cout << "2Некорректный BMP-файл\n";
        return;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        cout << "3Некорректный BMP-файл\n";
        return;
    }
    // Читаем необходимые данные
    dataPos      = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
    imageSize    = *(int*)&(header[0x22]); // Размер изображения в байтах
    widths[ind]  = *(int*)&(header[0x12]); // Ширина
    heights[ind] = *(int*)&(header[0x16]); // Высота
    // Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
    if (imageSize==0)    imageSize=widths[ind]*heights[ind]*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
    if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком
    // Создаем буфер
    datas[ind] = new unsigned char [imageSize];

    // Считываем данные из файла в буфер
    fread(datas[ind],1,imageSize,file);

    // Закрываем файл, так как больше он нам не нужен
    fclose(file);

    glGenTextures(1, &textures[ind]);

    // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
    glBindTexture(GL_TEXTURE_2D, textures[ind]);
    // Передадим изображение OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, datas[ind]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Update();

void display(void);
void reshape(int, int);
/* Drawing one chunk function*/
void chunks(string);
/*Getting one chunk-string function*/
string getchunk(const char *);

int wid = 6;
int hei = 6;
int dee = 6;

float * posses;
float st[3];
bool blocker [10];

GLfloat rtri;
float vel = 0.0f;

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

const int n_c = 64;
char fns[n_c][15];
string iss[n_c];

struct block
{
    int x, y, z;
    int side;
};

bool IsFull(int x, int y, int z);
block raycast(float x, float y, float z, float an, float yan);

bool gravity = false;

#include "raycast.h"
#include "free_camera.h"
#include "models.h"

bool IsFull(int x, int y, int z)
{
    int tex, tey, tez;
    tex = x % 6;
    tey = y % 6;
    tez = z % 6;
    int ch = (int)(x / 6)*4 + (int)(y / 6);
    if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '1')
        return true;
    else if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '0')
        return false;
}
float absm(float etwas)
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
void Update()
{
    if (!(color))
    {
        loadBMP_custom("textures/0.BMP", 0);
        loadBMP_custom("textures/1.BMP", 1);
        loadBMP_custom("textures/2.BMP", 2);
        loadBMP_custom("textures/3.BMP", 3);
        loadBMP_custom("textures/4.BMP", 4);
        loadBMP_custom("textures/5.BMP", 5);
    }
    for(int i = 0; i < n_c; ++i)
        iss[i] = getchunk(fns[i]);
}
int main(int argc, char** argv)
{
    string path1 = "chunks/";
    string path2 = ".VMC";
    st[0] = 20.0f;
    st[1] = 10.0f;
    st[2] = 20.0f;
    posses = st;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
            {
                string path;
                path = (char)(i + '0');
                path += (char)(j + '0');
                path += (char)(k + '0');
                string fullpath = path1;
				fullpath += path;
				fullpath += path2;
                for (int e = 0; e < 14; ++e)
                    fns[i*4*4 + j*4 + k][e] = fullpath[e];
                fns[i*4*4 + j*4 + k][14] = 0;
            }

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

    Update();

    glEnable(GL_TEXTURE_2D);

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
    // clear the color buffer (resets everything to black)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glTranslatef(0.0f, 0.0f,0.0f);

    gluLookAt(	x, y, z,
              x+lx, y+ly,  z+lz,
              0.0f, 1.0f,  0.0f);

    //---

    for(int i = 0; i < n_c; ++i)
        chunks(iss[i]);

    if (gravity)
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


    // swap the back and front buffers so we can see what we just drew
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
    //cout << x << y << z << endl;
    glPushMatrix();
    glRotatef(rtri, 1.0f, 1.0f, 1.0f);
    if (color)
        glBegin(GL_QUADS);
    float tx = posses[0] - 0.5f;
    float ty = posses[1] - 1.5f;
	float ty2 = posses[1] - 2.5f;
    float tz = posses[2] - 0.5f;

    for (int i = 0; i < wid; i++)
        for (int j = 0; j < hei; j++)
            for (int k = 0; k < dee; k++)
                if (is[i*hei*dee + j*dee + k + de] == '1')
                {
                    float xbc = i+x*wid;
                    float ybc = j+y*hei;
                    float zbc = k+z*dee;
                    if ((ty > ybc && ty - ybc < 1.0f) && (absm(xbc - tx) <= 0.5f) && (absm(zbc - tz) <= 0.5f)) // not to fall through blocks
                        blocker[0] = true;
                    if ((ty + 1.0f < ybc && ybc - (ty + 1.0f) < 1.0f) && (absm(xbc - tx) <= 0.5f) && (absm(zbc - tz) <= 0.5f)) // not to jump into the upper block
                        blocker[1] = true;

                    if (((tx + 1.0f) > xbc && (tx + 1.0f) - xbc < 1.0f) && (absm(ybc - ty - 1) < 1.0f) && (absm(tz - zbc) < 0.55f))
                        blocker[2] = true;
                    if ((tx > xbc && tx - xbc < 1.0f) && (absm(ybc - ty - 1) < 1.0f) && (absm(tz - zbc) < 0.55f))
                        blocker[3] = true;
                    if (((tz + 1.0f) > zbc && (tz + 1.0f) - zbc < 1.0f) && (absm(ybc - ty - 1) < 1.0f) && (absm(tx - xbc) < 0.55f))
                        blocker[4] = true;
                    if ((tz > zbc && tz - zbc < 1.0f) && (absm(ybc - ty - 1) < 1.0f) && (absm(tx - xbc) < 0.55f))
                        blocker[5] = true;

                    if (((tx + 1.0f) > xbc && (tx + 1.0f) - xbc < 1.0f) && (absm(ybc - ty2 - 1) < 1.0f) && (absm(tz - zbc) < 0.55f))
                        blocker[6] = true;
                    if ((tx > xbc && tx - xbc < 1.0f) && (absm(ybc - ty2 - 1) < 1.0f) && (absm(tz - zbc) < 0.55f))
                        blocker[7] = true;
                    if (((tz + 1.0f) > zbc && (tz + 1.0f) - zbc < 1.0f) && (absm(ybc - ty - 1) < 1.0f) && (absm(tx - xbc) < 0.55f))
                        blocker[8] = true;
                    if ((tz > zbc && tz - zbc < 1.0f) && (absm(ybc - ty2 - 1) < 1.0f) && (absm(tx - xbc) < 0.55f))
                        blocker[9] = true;
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
    if (color)
        glEnd();
}
string getchunk(const char *fn)
{
	#include <fstream>
    ifstream in;  // Поток in будем использовать для чтения
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
