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
    static void plain_top (float, float, float, float, float, float, float, float, int);
    static void plain_side (float, float, float, float, float, float, float, float, int);
    static void plain_front (float, float, float, float, float, float, float, float, int);
    static void plain_top_reversed (float, float, float, float, float, float, float, float, int);
    static void plain_side_reversed (float, float, float, float, float, float, float, float, int);
    static void plain_front_reversed (float, float, float, float, float, float, float, float, int);

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

bool color = false;

void drawModel::plain_top (float x1, float z1, float x2, float z2, float y, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x1, y, z1);
		glVertex3f(x1, y, z2);
	    glVertex3f(x2, y, z2);
		glVertex3f(x2, y, z1);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexCoord2f(x1, z1); glVertex3f(x1, y, z1);
	    glTexCoord2f(x1, z2); glVertex3f(x1, y, z2);
		glTexCoord2f(x2, z2); glVertex3f(x2, y, z2);
	    glTexCoord2f(x2, z1); glVertex3f(x2, y, z1);
	}
}

 void drawModel::plain_side (float y1, float z1, float y2, float z2, float x, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x, y1, z1);
		glVertex3f(x, y1, z2);
	    glVertex3f(x, y2, z2);
		glVertex3f(x, y2, z1);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(y1, z1); glVertex3f(x, y1, z1);
	    glTexCoord2f(y1, z2); glVertex3f(x, y1, z2);
		glTexCoord2f(y2, z2); glVertex3f(x, y2, z2);
	    glTexCoord2f(y2, z1); glVertex3f(x, y2, z1);
	}
}
void drawModel::plain_front (float x1, float y1, float x2, float y2, float z, float c1 = 1.0f, float c2 =1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x1, y1, z);
		glVertex3f(x1, y2, z);
	    glVertex3f(x2, y2, z);
		glVertex3f(x2, y1, z);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(x1, y1); glVertex3f(x1, y1, z);
	    glTexCoord2f(x1, y2); glVertex3f(x1, y2, z);
		glTexCoord2f(x2, y2); glVertex3f(x2, y2, z);
	    glTexCoord2f(x2, y1); glVertex3f(x2, y1, z);
	}
}


void drawModel::plain_top_reversed (float x1, float z1, float x2, float z2, float y, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x2, y, z1);
		glVertex3f(x2, y, z2);
	    glVertex3f(x1, y, z2);
		glVertex3f(x1, y, z1);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(x2, z1); glVertex3f(x2, y, z1);
	    glTexCoord2f(x2, z2); glVertex3f(x2, y, z2);
		glTexCoord2f(x1, z2); glVertex3f(x1, y, z2);
	    glTexCoord2f(x1, z1); glVertex3f(x1, y, z1);
	}
}

void drawModel::plain_side_reversed (float y1, float z1, float y2, float z2, float x, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x, y2, z1);
		glVertex3f(x, y2, z2);
	    glVertex3f(x, y1, z2);
		glVertex3f(x, y1, z1);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(y2, z1); glVertex3f(x, y2, z1);
	    glTexCoord2f(y2, z2); glVertex3f(x, y2, z2);
		glTexCoord2f(y1, z2); glVertex3f(x, y1, z2);
	    glTexCoord2f(y1, z1); glVertex3f(x, y1, z1);
	}
}
void drawModel::plain_front_reversed (float x1, float y1, float x2, float y2, float z, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
{
	if (color)
	{
		glColor3f(c1, c2, c3);
		glVertex3f(x2, y1, z);
		glVertex3f(x2, y2, z);
	    glVertex3f(x1, y2, z);
		glVertex3f(x1, y1, z);
	}
	else
	{
		// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
		glBindTexture(GL_TEXTURE_2D, textures[ind]);

		// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexCoord2f(x2, y1); glVertex3f(x2, y1, z);
	    glTexCoord2f(x2, y2); glVertex3f(x2, y2, z);
		glTexCoord2f(x1, y2); glVertex3f(x1, y2, z);
	    glTexCoord2f(x1, y1); glVertex3f(x1, y1, z);
	}
}
