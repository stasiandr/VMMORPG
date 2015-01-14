//
//  models.h
//  OpenGL
//
//  Created by Irina on 29/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//

#ifndef OpenGL_models_h
#define OpenGL_models_h


#endif

class drawModel {
public:
    static void cube(float, float, float);
    static void plain_top (float, float, float, float, float);
    static void plain_side (float, float, float, float, float);
    static void plain_front (float, float, float, float, float);

};


void drawModel::cube(float pos_x, float pos_y, float pos_z)
{
    glColor3f(0.0f,1.0f,0.0f);              // Зеленый
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Право верх квадрата (Верх)
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Лево верх
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Лево низ
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Право низ
    
    glColor3f(1.0f,0.5f,0.0f);              // Оранжевый
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Верх право квадрата (Низ)
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Верх лево
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Низ лево
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Низ право
    
    glColor3f(1.0f,0.0f,0.0f);              // Красный
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Верх право квадрата (Перед)
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Верх лево
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Низ лево
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Низ право
    
    glColor3f(1.0f,0.7f,0.3f);              // Желтый
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Верх право квадрата (Зад)
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Верх лево
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Низ лево
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Низ право
    
    glColor3f(0.0f,0.0f,1.0f);              // Синий
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Верх право квадрата (Лево)
    glVertex3f(-1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Верх лево
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Низ лево
    glVertex3f(-1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Низ право
    
    glColor3f(1.0f,0.0f,1.0f);              // Фиолетовый
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y,-1.0f + pos_z);          // Верх право квадрата (Право)
    glVertex3f( 1.0f + pos_x, 1.0f + pos_y, 1.0f + pos_z);          // Верх лево
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y, 1.0f + pos_z);          // Низ лево
    glVertex3f( 1.0f + pos_x,-1.0f + pos_y,-1.0f + pos_z);          // Низ право
    
}


void drawModel::plain_top (float x1, float z1, float x2, float z2, float y)
{
    glVertex3f(x1, y, z1);
    glVertex3f(x1, y, z2);
    glVertex3f(x2, y, z1);
    glVertex3f(x2, y, z2);
}

 void drawModel::plain_side (float y1, float z1, float y2, float z2, float x)
{
    glVertex3f(x, y1, z1);
    glVertex3f(x, y1, z2);
    glVertex3f(x, y2, z1);
    glVertex3f(x, y2, z2);
}
void drawModel::plain_front (float x1, float y1, float x2, float y2, float z)
{
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
}




