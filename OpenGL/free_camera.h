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

float Moveconst = 0.5f;
float MoveconstY = 0.2f;

float angle = 0.0f;
float Yangle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=1.0f, ly=0.0f;

// XZ position of the camera
float x=20.0f, z=20.0f, y=10.0f;

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
		MoveconstY = 2.5f;
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

void processNormalKeys(unsigned char key, int xx, int yy) {

    if (key == 27)
        exit(0);

    switch (key) {
        case 'g' : grswt(); deltaMove_Y = 0; break;
        case 'i' : cout << "an: " << angle << " Yan: " << Yangle << " x: " << x << " y: " << y << " z: " << z << endl; break;
        case 'f' : Update(); break;
        case 'q' : for (int i = 0; i < 1; ++i)
                    {
                        mouseButton(GLUT_LEFT_BUTTON, GLUT_UP, -1, -1);
                        raycast(x, y, z, angle, Yangle);
                    }
                    break;
        case 'w' : deltaMove += Moveconst * lx; deltaMove_Sides += Moveconst * lz; break;
        case 's' : deltaMove += -Moveconst * lx; deltaMove_Sides += -Moveconst * lz; break;
        case 'd' : deltaMove_Sides += Moveconst * Slz; deltaMove += Moveconst * Slx; break;
        case 'a' : deltaMove_Sides += -Moveconst * Slz; deltaMove += -Moveconst * Slx; break;
        case ' ' : deltaMove_Y += MoveconstY; break;
    }
    if (!(gravity))
        if (key == 'z')
            deltaMove_Y -= MoveconstY;
}

void processNormalKeysRelease(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w' :
        case 's' :
        case 'd' :
        case 'a' : deltaMove = 0; deltaMove_Sides = 0; break;
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
