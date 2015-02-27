//
//  models.h
//  OpenGL
//
//  Created by Irina on 29/11/14.
//  Copyright (c) 2014 Argon Team. All rights reserved.
//

#ifndef OpenGL_models_h
#define OpenGL_models_h


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

#endif

class drawModel {
public:
    static void cube(float, float, float);
    static void plain_top (float, float, float, float, float, float, float, float);
    static void plain_side (float, float, float, float, float, float, float, float);
    static void plain_front (float, float, float, float, float, float, float, float);
    static void plain_top_reversed (float, float, float, float, float, float, float, float);
    static void plain_side_reversed (float, float, float, float, float, float, float, float);
    static void plain_front_reversed (float, float, float, float, float, float, float, float);

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


void drawModel::plain_top (float x1, float z1, float x2, float z2, float y, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f)
{
    GLuint Texture = loadBMP_custom("uvtemplate.bmp");

    //glTexCoord3f(0.0f, 0.0f, 0.0f);

    glColor3f(c1, c2, c3);
    glVertex3f(x1, y, z1);
    glVertex3f(x1, y, z2);
    glVertex3f(x2, y, z2);
    glVertex3f(x2, y, z1);
}

 void drawModel::plain_side (float y1, float z1, float y2, float z2, float x, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f)
{
    glColor3f(c1, c2, c3);
    glVertex3f(x, y1, z1);
    glVertex3f(x, y1, z2);
    glVertex3f(x, y2, z2);
    glVertex3f(x, y2, z1);
}
void drawModel::plain_front (float x1, float y1, float x2, float y2, float z, float c1 = 1.0f, float c2 =1.0f, float c3 = 1.0f)
{
    glColor3f(c1, c2, c3);
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x2, y1, z);
}


void drawModel::plain_top_reversed (float x1, float z1, float x2, float z2, float y, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f)
{
    glColor3f(c1, c2, c3);
    glVertex3f(x2, y, z1);
    glVertex3f(x2, y, z2);
    glVertex3f(x1, y, z2);
    glVertex3f(x1, y, z1);
}

void drawModel::plain_side_reversed (float y1, float z1, float y2, float z2, float x, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f)
{
    glColor3f(c1, c2, c3);
    glVertex3f(x, y2, z1);
    glVertex3f(x, y2, z2);
    glVertex3f(x, y1, z2);
    glVertex3f(x, y1, z1);
}
void drawModel::plain_front_reversed (float x1, float y1, float x2, float y2, float z, float c1 = 1.0f, float c2 = 1.0f, float c3 = 1.0f)
{
    glColor3f(c1, c2, c3);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x1, y1, z);
}
