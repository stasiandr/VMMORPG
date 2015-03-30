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
#include <vector>

using namespace std;

static HGLRC hRC;		// Постоянный контекст рендеринга
static HDC hDC;			// Приватный контекст устройства GDI

bool FOG_is = false;

float gfs = 1.0f;
float gfe = 5.0f;

bool blend = true;
bool light = true;
bool circle = false;

struct blend_plain
{
    float tex[4][2];
    float ver[4][3];
    int tex_t;
    int tex_ind;
};

vector<blend_plain> GL_BLEND_BUFFER_BIT;

// Задаем параметры освещения
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]={ 0.0f, 0.0f, 2.0f, 1.0f };

float lpx = 200.0f;
float lpy = 0.0f;
float lpz = 200.0f;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);    // Декларация WndProc

const int num_tex = 10;
GLuint textures[num_tex][6];
unsigned char * datas[num_tex][6];
unsigned int widths[num_tex][6];
unsigned int heights[num_tex][6];

void loadBMP_custom(const char * imagepath, int ind, int t)
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
    widths[t][ind]  = *(int*)&(header[0x12]); // Ширина
    heights[t][ind] = *(int*)&(header[0x16]); // Высота
    // Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
    if (imageSize==0)    imageSize=widths[t][ind]*heights[t][ind]*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
    if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком
    // Создаем буфер
    datas[t][ind] = new unsigned char [imageSize];

    // Считываем данные из файла в буфер
    fread(datas[t][ind],1,imageSize,file);

    // Закрываем файл, так как больше он нам не нужен
    fclose(file);

    glGenTextures(1, &textures[t][ind]);

    // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
    glBindTexture(GL_TEXTURE_2D, textures[t][ind]);
    // Передадим изображение OpenGL
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[t][ind], heights[t][ind], 0, GL_RGB, GL_UNSIGNED_BYTE, datas[t][ind]);
}

void Update();

void display(void);
void reshape(int, int);
/* Drawing one chunk function*/
void chunks(string);
/*Getting one chunk-string function*/
string getchunk(const char *);

int wid = 16;
int hei = 16;
int dee = 16;

float * posses;

int dist = 2;

float st[3];
bool blocker [10];

GLfloat rtri;
float vel = 0.0f;

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

float tx , ty, ty2, tz;

struct block
{
    int x, y, z;
    int side;
};

bool IsFull(int x, int y, int z);
//block raycast(float x, float y, float z, float an, float yan);

bool gravity = false;

bool color = false;

//#include "raycast.h"
#include "free_camera.h"
#include "models.h"

char name[15];

void getname(int i, int j, int k)
{
    string path;
    string path1 = "chunks/";
    string path2 = ".VMC";
    path = (char)(i + '0');
    path += (char)(j + '0');
    path += (char)(k + '0');
    string fullpath = path1;
    fullpath += path;
    fullpath += path2;
    for (int e = 0; e < 14; ++e)
        name[e] = fullpath[e];
    name[14] = 0;
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
        string path1 = "textures/";
        string pathend = ".bmp";
        for (int i = 0; i < num_tex; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                string path;
                path = (char)(i + '0');
                path += "/";
                path += (char)(j + '0');
                string fullpath = path1;
                fullpath += path;
                fullpath += pathend;
                char name[17];
                for (int e = 0; e < 16; ++e)
                    name[e] = fullpath[e];
                name[16] = 0;
                cout << name << endl;
                loadBMP_custom(name, j, i);
            }
        }
    }
}
int main(int argc, char** argv)
{
    st[0] = 4.0f;
    st[1] = 200.0f;
    st[2] = 4.0f;
    posses = st;

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
    glShadeModel(GL_SMOOTH);      // Разрешение сглаженного закрашивания
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Черный фон
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшенные вычисления перспективы

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // Позиция света
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1); // Разрешение источника света номер один

    glEnable(GL_DEPTH_TEST);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);   // Полная яркость, 50% альфа (НОВОЕ)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Функция смешивания для непрозрачности,
                                  // базирующаяся на значении альфы(НОВОЕ)

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
    LightPosition[0] = lpx;
    LightPosition[1] = lpy;
    LightPosition[2] = lpz;

    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // Позиция света

    if (!light)               // Если не свет
    {
        glDisable(GL_LIGHTING);  // Запрет освещения
    }
    else                      // В противном случае
    {
        glEnable(GL_LIGHTING);   // Разрешить освещение
    }
    if (FOG_is)
    {
        GLfloat fogColor[4] = {0.8f, 0.8f, 0.8f, 1.0f}; // Цвет тумана
        glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);      // Будем очищать экран, заполняя его цветом тумана. ( Изменено
        glEnable(GL_FOG);                       // Включает туман (GL_FOG)
        glFogi(GL_FOG_MODE, GL_EXP2);// Выбираем тип тумана
        glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
        glFogf(GL_FOG_DENSITY, 0.15f);          // Насколько густым будет туман
        glHint(GL_FOG_HINT, GL_FASTEST);      // Вспомогательная установка тумана GL_NICEST or GL_DONT_CARE or GL_FASTEST
        glFogf(GL_FOG_START, gfs);             // Глубина, с которой начинается туман
        glFogf(GL_FOG_END, gfe);               // Глубина, где туман заканчивается.
    }
    else
    {
        glClearColor(0.4f, 0.8f, 0.8f, 1.0f);
        glDisable(GL_FOG);
    }
    // clear the color buffer (resets everything to black)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f,0.0f);

    gluLookAt(	x, y, z,
              x+lx, y+ly,  z+lz,
              0.0f, 1.0f,  0.0f);

    //---

    tx = x - 0.5f;
    ty = y - 1.5f;
	ty2 = y - 2.5f;
    tz = z - 0.5f;

    int ch_min_x = (tx - dist)/wid;
    int ch_max_x = (tx + dist)/wid + 1;

    int ch_min_y = (ty - dist)/hei;
    int ch_max_y = (ty + dist)/hei + 1;

    int ch_min_z = (tz - dist)/dee;
    int ch_max_z = (tz+ dist)/dee + 1;

    if (ch_min_x < 0) ch_min_x = 0;
    if (ch_min_y < 0) ch_min_y = 0;
    if (ch_min_z < 0) ch_min_z = 0;

    for (int i = ch_min_x; i < ch_max_x; ++i)
        for (int j = ch_min_y; j < ch_max_y; ++j)
            for (int k = ch_min_z; k < ch_max_z; ++k)
            {
                getname(i, j, k);
                string cancer = getchunk(name);
                if (cancer != "IDITE NAFIG!")
                    chunks(cancer);
            }

    if (gravity)
        deltaMove_Y -= 0.027f;

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

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);

    //glColor3f(1, 1, 1);

    glVertex3f(-1000, 0, 0);
    glVertex3f(1000, 0, 0);

    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);

    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, 20);

    glEnd();
    glEnable(GL_TEXTURE_2D);

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

    for (int i = 0; i < wid; i++)
        for (int j = 0; j < hei; j++)
            for (int k = 0; k < dee; k++)
                if (is[i*hei*dee + j*dee + k + de] != '0')
                {
                    char tem = is[i*hei*dee + j*dee + k + de];
                    float xbc = i+x*wid;
                    float ybc = j+y*hei;
                    float zbc = k+z*dee;

                    if (circle)
                        if ((xbc-tx)*(xbc-tx) + (ybc-ty)*(ybc-ty) + (zbc-tz)*(zbc-tz) > (dist+2)*(dist+2))
                            continue;

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
                        drawModel::plain_side(ybc, zbc, ybc+1, zbc+1, xbc, tem, 1.0f, 0.0f, 0.0f);
                    else if (is[(i-1)*wid*dee + j*dee + k + de] == '0' or is[(i-1)*wid*dee + j*dee + k + de] == ':')
                        drawModel::plain_side(ybc, zbc, ybc+1, zbc+1, xbc, tem, 1.0f, 0.0f, 0.0f);
                    if (bad(i+1, j, k))
                        drawModel::plain_side_reversed(ybc, zbc, ybc+1, zbc+1, xbc+1, tem, 1.0f, 0.0f, 1.0f);
                    else if (is[(i+1)*wid*dee + j*dee + k + de] == '0' or is[(i+1)*wid*dee + j*dee + k + de] == ':')
                        drawModel::plain_side_reversed(ybc, zbc, ybc+1, zbc+1, xbc+1, tem, 1.0f, 0.0f, 1.0f);
                    if (bad(i, j-1, k))
                        drawModel::plain_top_reversed(xbc, zbc, xbc+1, zbc+1, ybc, tem, 1.0f, 1.0f, 0.0f);
                    else if (is[i*wid*dee + (j-1)*dee + k + de] == '0' or is[i*wid*dee + (j-1)*dee + k + de] == ':')
                        drawModel::plain_top_reversed(xbc, zbc, xbc+1, zbc+1, ybc, tem, 1.0f, 1.0f, 0.0f);
                    if (bad(i, j+1, k))
                        drawModel::plain_top(xbc, zbc, xbc+1, zbc+1, ybc+1, tem, 0.0f, 1.0f, 0.0f);
                    else if (is[i*wid*dee + (j+1)*dee + k + de] == '0' or is[i*wid*dee + (j+1)*dee + k + de] == ':')
                        drawModel::plain_top(xbc, zbc, xbc+1, zbc+1, ybc+1, tem, 0.0f, 1.0f, 0.0f);
                    if (bad(i, j, k-1))
                        drawModel::plain_front(xbc, ybc, xbc+1, ybc+1, zbc, tem, 0.0f, 1.0f, 1.0f);
                    else if (is[i*wid*dee + j*dee + k-1 + de] == '0' or is[i*wid*dee + j*dee + k-1 + de] == ':')
                        drawModel::plain_front(xbc, ybc, xbc+1, ybc+1, zbc, tem, 0.0f, 1.0f, 1.0f);
                    if (bad(i, j, k+1))
                        drawModel::plain_front_reversed(xbc, ybc, xbc+1, ybc+1, zbc+1, tem, 0.0f, 0.0f, 1.0f);
                    else if (is[i*wid*dee + j*dee + k+1 + de] == '0' or is[i*wid*dee + j*dee + k+1 + de] == ':')
                        drawModel::plain_front_reversed(xbc, ybc, xbc+1, ybc+1, zbc+1, tem, 0.0f, 0.0f, 1.0f);
                    // chunk's borders drawing - END
                    /*int inde = (i-1)*wid*dee + j*dee + k + de;
                    cout << i << " " << j << " " << k << " " << de << endl;
                    cout << inde << endl;
                    cout << is.size() << endl;
                    cout << is[inde] << endl;*/
                }
    if (GL_BLEND_BUFFER_BIT.size() < 1)
    {
        if(color)
            glEnd();
        return;
    }
    //cout << GL_BLEND_BUFFER_BIT.size() << endl;
    for (int i = 0; i < 108; ++i)
    {
        //glEnable(GL_BLEND);        // Включаем смешивание
        //glDisable(GL_DEPTH_TEST);  // Выключаем тест глубины
        //glDepthMask(false);
        blend_plain temp = GL_BLEND_BUFFER_BIT[i];
        glBindTexture(GL_TEXTURE_2D, textures[temp.tex_t][temp.tex_ind]);

        glBegin(GL_QUADS);
        for (int n = 0; n < 4; ++n)
        {
            glTexCoord2f(temp.tex[n][0], temp.tex[n][1]);
            glVertex3f(temp.ver[n][0], temp.ver[n][1], temp.ver[n][2]);
        }
        glEnd();
        //glDepthMask(true);
        //glDisable(GL_BLEND);        // Выключаем смешивание
        //glEnable(GL_DEPTH_TEST);
    }
    GL_BLEND_BUFFER_BIT.clear();


    if (color)
        glEnd();
}
string getchunk(const char *fn)
{
    ifstream in;  // Поток in будем использовать для чтения
    in.open(fn);
    if (in == 0)
        return "IDITE NAFIG!";
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
