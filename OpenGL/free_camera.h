//
//  free_camera.h
//  OpenGL
//
//  Created by Irina on 29/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//

#ifndef OpenGL_free_camera_h
#define OpenGL_free_camera_h


#endif

// Camer Stuff --------

float Moveconst = 2.5f;
float MoveconstY = 3.5f;

short Movingw = 0;
short Movinga = 0;

float angle = 0.0f;
float Yangle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=1.0f, ly=0.0f;

// XZ position of the camera
float x=4.0f, z=4.0f, y=200.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

float YdeltaAngle = 0.0f;
int yOrigin = -1;
// --------------------


float deltaMove_Sides = 0;
float Slx = 0, Slz = 0;

float deltaMove_Y = 0;

float Movew = 0;
float Movea = 0;

void processNormalKeys(unsigned char, int, int);
void processNormalKeysRelease(unsigned char, int, int);
void pressKey(int, int, int);
void releaseKey(int, int, int);

void mouseMove(int, int);
void mouseButton(int, int, int, int);

void grswt()
{
    if(gravity)
	{
        gravity = false;
		MoveconstY = 1.0f;
	}
    else
	{
        gravity = true;
		MoveconstY = 0.7f;
	}
}

float m[3];
float * computePos(float deltaMove, float deltaMove_Sides, float deltaMove_Y)
{
    x += deltaMove * 0.1f;
    z += deltaMove_Sides * 0.1f;

    y += deltaMove_Y * 0.1f;

    m[0] = x; // Just to return data
    m[1] = y;
    m[2] = z;
    return m;
}

void Moving()
{
    deltaMove = 0; deltaMove_Sides = 0;
    if (Movingw != 0)
    {
        deltaMove += Moveconst * Movingw * lx;
        deltaMove_Sides += Moveconst * Movingw * lz;
    }
    if (Movinga != 0)
    {
        deltaMove_Sides += Moveconst * Movinga * Slz;
        deltaMove += Moveconst * Movinga * Slx;
    }
}

void processNormalKeys(unsigned char key, int xx, int yy) {

    if (key == 27)
        exit(0);

    float lc = 1.0f;
    switch (key) {
        case '1' : dist += 1; break;
        case '2' : dist -= 1; break;
        case '=' : gfe += 100.0f; break;
        case '-' : gfe -= 100.0f; break;
        case '+' : gfs += 100.0f; break;
        case '_' : gfs -= 100.0f; break;
        case 'i' : lpy += lc; break;
        case 'j' : lpx += lc; break;
        case 'k' : lpy -= lc; break;
        case 'l' : lpx -= lc; break;
        case 'u' : lpz += lc; break;
        case 'o' : lpz -= lc; break;
        case 't' : circle = !circle; break;
        case 'r' : FOG_is = !FOG_is; break;
        case 'e' : blend = !blend; break;
        case 'c' : light = !light; break;
        case 'x' : color = !color; glColor3f(1.0f, 1.0f, 1.0f); break;
        case 'g' : grswt(); deltaMove_Y = 0; break;
        case 'y' : cout << "an: " << angle << " Yan: " << Yangle << " x: " << x << " y: " << y << " z: " << z << endl; break;
        case 'f' : Update(); break;
        case 'w' : Movingw = 1; Moving(); break;
        case 's' : Movingw = -1;  Moving(); break;
        case 'd' : Movinga = 1; Moving(); break;
        case 'a' : Movinga = -1;  Moving(); break;
        case ' ' : deltaMove_Y += MoveconstY; break;
    }
    if (!(gravity))
        if (key == 'z')
            deltaMove_Y -= MoveconstY;
}

void processNormalKeysRelease(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w' : if (Movingw == 1) Movingw = 0; Moving(); break;
        case 's' : if (Movingw == -1) Movingw = 0; Moving(); break;
        case 'd' : if (Movinga == 1) Movinga = 0; Moving(); break;
        case 'a' : if (Movinga == -1) Movinga = 0; Moving(); break;
        case ' ' : break;
    }
    if (!(gravity))
        switch (key) {
            case 'z':
            case ' ' : deltaMove_Y = 0; break;
        }
}

void pressKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_UP : deltaMove = Moveconst; break;
        case GLUT_KEY_DOWN : deltaMove = -Moveconst; break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP : deltaMove = 0; break;
        case GLUT_KEY_DOWN : deltaMove = 0; break;
    }
}


void mouseMove(int x, int y) {

    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        Moving();

        YdeltaAngle = (y - yOrigin) * -0.01f;

        if (sin(Yangle + YdeltaAngle) > -0.6f && sin(Yangle + YdeltaAngle) < 0.6f)
        {
            ly = sin(Yangle + YdeltaAngle);
        }


        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.01f;

        Slx = cos(angle + deltaAngle);
        Slz = sin(angle + deltaAngle);

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y) {

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            Yangle += YdeltaAngle;

            xOrigin = -1;
            yOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}
