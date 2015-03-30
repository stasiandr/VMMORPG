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
    static void plain_top (float, float, float, float, float, char, float, float, float, int);
    static void plain_side (float, float, float, float, float, char, float, float, float, int);
    static void plain_front (float, float, float, float, float, char, float, float, float, int);
    static void plain_top_reversed (float, float, float, float, float, char, float, float, float, int);
    static void plain_side_reversed (float, float, float, float, float, char, float, float, float, int);
    static void plain_front_reversed (float, float, float, float, float, char, float, float, float, int);

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

void drawModel::plain_top (float x1, float z1, float x2, float z2, float y, char tem, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 0)
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
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            blend_plain temp;
            temp.tex[0][0] = x1; temp.tex[0][1] = z1;
            temp.tex[0][0] = x1; temp.tex[0][1] = z2;
            temp.tex[0][0] = x2; temp.tex[0][1] = z2;
            temp.tex[0][0] = x2; temp.tex[0][1] = z1;
            temp.ver[0][0] = x1; temp.ver[0][0] = y; temp.ver[0][0] = z1;
            temp.ver[0][0] = x1; temp.ver[0][0] = y; temp.ver[0][0] = z1;
            temp.ver[0][0] = x2; temp.ver[0][0] = y; temp.ver[0][0] = z2;
            temp.ver[0][0] = x2; temp.ver[0][0] = y; temp.ver[0][0] = z1;
            temp.tex_ind = ind;
            temp.tex_t = t;
            GL_BLEND_BUFFER_BIT.push_back(temp);
            return;
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

        glBegin(GL_QUADS);
		glTexCoord2f(x1, z1); glVertex3f(x1, y, z1);
	    glTexCoord2f(x1, z2); glVertex3f(x1, y, z2);
		glTexCoord2f(x2, z2); glVertex3f(x2, y, z2);
	    glTexCoord2f(x2, z1); glVertex3f(x2, y, z1);
        glEnd();

        if (t == 9 && blend)
        {
            glDepthMask(true);
            glDisable(GL_BLEND);        // Выключаем смешивание
            glEnable(GL_DEPTH_TEST);
        }
	}
}
 void drawModel::plain_side (float y1, float z1, float y2, float z2, float x, char tem, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 2)
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
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            glEnable(GL_BLEND);        // Включаем смешивание
            glDisable(GL_DEPTH_TEST);  // Выключаем тест глубины
            glDepthMask(false);
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

        glBegin(GL_QUADS);
		glTexCoord2f(y2, z2); glVertex3f(x, y2, z2);
	    glTexCoord2f(y1, z2); glVertex3f(x, y2, z1);
		glTexCoord2f(y1, z1); glVertex3f(x, y1, z1);
	    glTexCoord2f(y2, z1); glVertex3f(x, y1, z2);
        glEnd();

        if (t == 9 && blend)
        {
            glDepthMask(true);
            glDisable(GL_BLEND);        // Выключаем смешивание
            glEnable(GL_DEPTH_TEST);
        }
	}
}
void drawModel::plain_front (float x1, float y1, float x2, float y2, float z, char tem, float c1 = 1.0f, float c2 =1.0f, float c3 = 1.0f, int ind = 4)
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
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            glEnable(GL_BLEND);        // Включаем смешивание
            glDisable(GL_DEPTH_TEST);  // Выключаем тест глубины
            glDepthMask(false);
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

		/*// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, datas[ind]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/

        glBegin(GL_QUADS);
		glTexCoord2f(x2, y1); glVertex3f(x1, y1, z);
	    glTexCoord2f(x2, y2); glVertex3f(x1, y2, z);
		glTexCoord2f(x1, y2); glVertex3f(x2, y2, z);
	    glTexCoord2f(x1, y1); glVertex3f(x2, y1, z);
        glEnd();

        if (t == 9 && blend)
        {
            glDepthMask(true);
            glDisable(GL_BLEND);        // Выключаем смешивание
            glEnable(GL_DEPTH_TEST);
        }
	}
}
void drawModel::plain_top_reversed (float x1, float z1, float x2, float z2, float y, char tem, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 1)
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
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            glEnable(GL_BLEND);        // Включаем смешивание
            glDisable(GL_DEPTH_TEST);  // Выключаем тест глубины
            glDepthMask(false);
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

		/*// Передадим изображение OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, widths[ind], heights[ind], 0, GL_RGB, GL_UNSIGNED_BYTE, datas[ind]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/

        glBegin(GL_QUADS);
		glTexCoord2f(x2, z2); glVertex3f(x2, y, z1);
	    glTexCoord2f(x2, z1); glVertex3f(x2, y, z2);
		glTexCoord2f(x1, z1); glVertex3f(x1, y, z2);
	    glTexCoord2f(x1, z2); glVertex3f(x1, y, z1);
        glEnd();

        if (t == 9 && blend)
        {
            glDepthMask(true);
            glDisable(GL_BLEND);        // Выключаем смешивание
            glEnable(GL_DEPTH_TEST);
        }
	}
}
void drawModel::plain_side_reversed (float y1, float z1, float y2, float z2, float x, char tem, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 5)
{
	if (color)
	{
        glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(x, y2, z1);
		glVertex3f(x, y2, z2);
	    glVertex3f(x, y1, z2);
		glVertex3f(x, y1, z1);
	}
	else
	{
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            blend_plain temp;
            temp.tex[0][0] = y2; temp.tex[0][1] = z2;
            temp.tex[0][0] = y1; temp.tex[0][1] = z2;
            temp.tex[0][0] = y2; temp.tex[0][1] = z1;
            temp.tex[0][0] = y2; temp.tex[0][1] = z1;
            temp.ver[0][0] = x; temp.ver[0][0] = y2; temp.ver[0][0] = z1;
            temp.ver[0][0] = x; temp.ver[0][0] = y2; temp.ver[0][0] = z2;
            temp.ver[0][0] = x; temp.ver[0][0] = y1; temp.ver[0][0] = z2;
            temp.ver[0][0] = x; temp.ver[0][0] = y1; temp.ver[0][0] = z1;
            temp.tex_ind = ind;
            temp.tex_t = t;
            GL_BLEND_BUFFER_BIT.push_back(temp);
            return;
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

        glBegin(GL_QUADS);
		glTexCoord2f(y2, z2); glVertex3f(x, y2, z1);
	    glTexCoord2f(y1, z2); glVertex3f(x, y2, z2);
		glTexCoord2f(y1, z1); glVertex3f(x, y1, z2);
	    glTexCoord2f(y2, z1); glVertex3f(x, y1, z1);
        glEnd();
	}
}
void drawModel::plain_front_reversed (float x1, float y1, float x2, float y2, float z, char tem, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f, int ind = 3)
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
	    int t = (int)tem - 49;
	    if (t == 9 && blend)
        {
            blend_plain temp;
            temp.tex[0][0] = x2; temp.tex[0][1] = y1;
            temp.tex[0][0] = x2; temp.tex[0][1] = y2;
            temp.tex[0][0] = x1; temp.tex[0][1] = y2;
            temp.tex[0][0] = x1; temp.tex[0][1] = y1;
            temp.ver[0][0] = x2; temp.ver[0][0] = y1; temp.ver[0][0] = z;
            temp.ver[0][0] = x2; temp.ver[0][0] = y2; temp.ver[0][0] = z;
            temp.ver[0][0] = x1; temp.ver[0][0] = y2; temp.ver[0][0] = z;
            temp.ver[0][0] = x1; temp.ver[0][0] = y1; temp.ver[0][0] = z;
            temp.tex_ind = ind;
            temp.tex_t = t;
            GL_BLEND_BUFFER_BIT.push_back(temp);
            return;
        }
        // Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
        glBindTexture(GL_TEXTURE_2D, textures[t][ind]);

        glBegin(GL_QUADS);
		glTexCoord2f(x2, y1); glVertex3f(x2, y1, z);
	    glTexCoord2f(x2, y2); glVertex3f(x2, y2, z);
		glTexCoord2f(x1, y2); glVertex3f(x1, y2, z);
	    glTexCoord2f(x1, y1); glVertex3f(x1, y1, z);
        glEnd();
	}
}
