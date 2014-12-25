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

float angle = 0.0f;
float Yangle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=1.0f, ly=0.0f;

// XZ position of the camera
float x=1.0f, z=10.0f, y=0.0f;

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


void processNormalKeys(unsigned char, int, int);
void processNormalKeysRelease(unsigned char, int, int);
void pressKey(int, int, int);
void releaseKey(int, int, int);

void mouseMove(int, int);
void mouseButton(int, int, int, int);


void computePos(float deltaMove, float deltaMove_Sides, float deltaMove_Y) {
    x += deltaMove_Sides * Slx * 0.1f;
    z += deltaMove_Sides * Slz * 0.1f;
    
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
    y += deltaMove * ly * 0.1f;
    
    y += deltaMove_Y * 0.1f;
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    
    if (key == 27)
        exit(0);
    
    switch (key) {
        case 'w' : deltaMove = 5.0f; break;
        case 's' : deltaMove = -5.0f; break;
        case 'd' : deltaMove_Sides = 5.0f; break;
        case 'a' : deltaMove_Sides = -5.0f; break;
        case ' ' : deltaMove_Y = 5.0f;break;
        case 'z' : deltaMove_Y = -5.0f;break;
    }
    
}

void processNormalKeysRelease(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w' :
        case 's' : deltaMove = 0; break;
        case 'd' :
        case 'a' : deltaMove_Sides = 0; break;
        case ' ' :
        case 'z' : deltaMove_Y = 0; break;
    }
    
}

void pressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_UP : deltaMove = 5.0f; break;
        case GLUT_KEY_DOWN : deltaMove = -5.0f; break;
    }
}

void releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
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
