#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

char names[6][8];

int main()
{
    char inp;
    cin >> inp;
    string path1;
    path1 = inp;
    path1 += "/";
    string path2 = ".bmp";
    for (int i = 0; i < 6; ++i)
    {
        string path;
        path = path1;
        path += (char)(i + '0');
        string fullpath = path;
        fullpath += path2;
        for (int e = 0; e < 7; ++e)
            names[i][e] = fullpath[e];
        names[i][7] = 0;
    }
    for (int n = 0; n < 6; ++n)
    {
        char * imagepath = names[n];
        cout << imagepath << endl;
        // Данные, прочитанные из заголовка BMP-файла
        unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
        unsigned int dataPos;     // Смещение данных в файле (позиция данных)
        unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3

        // RGB-данные, полученные из файла
        FILE * file = fopen(imagepath,"rb");
        if (!file) {
          cout << "The image can't be opened\n";
          return -1;
        }
        if ( fread(header, 1, 54, file) != 54 ) { // Если мы прочитали меньше 54 байт, значит возникла проблема
            cout << "Incorrect BMP-file\n";
            return -1;
        }
        if ( header[0]!='B' || header[1]!='M' ){
            cout << "Incorrect BMP-file\n";
            return -1;
        }
        int width, height;
        unsigned char * data;

        // Читаем необходимые данные
        dataPos      = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
        imageSize    = *(int*)&(header[0x22]); // Размер изображения в байтах
        width  = *(int*)&(header[0x12]); // Ширина
        height = *(int*)&(header[0x16]); // Высота
        // Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
        if (imageSize==0)    imageSize=width*height*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
        if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком
        // Создаем буфер
        data = new unsigned char [imageSize];

        // Считываем данные из файла в буфер
        fread(data,1,imageSize,file);

        // Закрываем файл, так как больше он нам не нужен
        fclose(file);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                char r, g, b;
                r = data[i*width*3 + j*3 + 0];
                g = data[i*width*3 + j*3 + 1];
                b = data[i*width*3 + j*3 + 2];

                data[i*width*3 + j*3 + 0] = b;
                data[i*width*3 + j*3 + 1] = g;
                data[i*width*3 + j*3 + 2] = r;
            }
        }

        FILE * fout = fopen(imagepath, "wb");
        fwrite(header, sizeof(char), 54, fout);
        fwrite(data, sizeof(char), imageSize, fout);
        fclose(fout);
    }
    return 0;
}
