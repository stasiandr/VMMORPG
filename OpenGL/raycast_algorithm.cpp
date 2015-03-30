//raycast_algorithm.cpp

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

void print(double a, double b, double c)
{
    cout << a << " " << b << " " << c << endl;
}

double abs(double etwas)
{
    if (etwas < 0)
        etwas = -etwas;
    return etwas;
}

int main()
{
    const int ach = 6;
    const int bch = 6;
    const int cch = 6;
    //cout << "Number of chunks: ";
    //cin >> ach >> bch >> cch;

    int a = 10;
    int b = 10;
    int c = 10;
    //cout << "Sizes of chunks: ";
    //cin >> a >> b >> c;

    string iss[ach][bch][cch];
    char ids[ach][bch][cch][13];

    for (int i = 0; i < ach; ++i)
        for (int j = 0; j < bch; ++j)
            for (int k = 0; k < cch; ++k)
            {
                char name[15];
                string path;
                path = (char)(i + '0');
                path += (char)(j + '0');
                path += (char)(k + '0');
                string path2 = ".VMC";
                string fullpath = path;
				fullpath += path2;
                for (int e = 0; e < 14; ++e)
                    name[e] = fullpath[e];
                name[14] = 0;

                ifstream in;  // Поток in будем использовать для чтения
                in.open(name);
                for (int d = 0; d < 12; ++d)
                    in >> ids[i][j][k][d];
                in >> iss[i][j][k];
                in.close();
            }
    bool field[a*ach][b*bch][c*cch];
    cout << "FIRST PART\n";
    for (int chunk_x = 0; chunk_x < ach; ++chunk_x)
        for (int chunk_y = 0; chunk_y < bch; ++chunk_y)
            for (int chunk_z = 0; chunk_z < cch; ++chunk_z)
            {
                for (int i = 0; i < a*b*c; ++i)
                {
                    int x, y, z;
                    x = i / (b*c);
                    y = (i-x*b*c) / c;
                    z = (i-x*b*c - y*c) % c;
                    char t = iss[chunk_x][chunk_y][chunk_z][x*b*c + y*c + z];
                    if (t == 0)
                        field[x][y][z] = false;
                    else
                        field[x][y][z] = true;
                }
            }
    cout << "SECOND PART\n";
    float an, yan;
    cout << "Angles: ";
    cin >> an >> yan;
    float radian = 57.295779513;
    an /= radian;
    yan /= radian;
    float resx, resy, resz;
    float x, y, z;
    cout << "Position: ";
    cin >> resx >> resy >> resz;
    x = resx;
    y = resy;
    z = resz;
    //cout << "Angles " << an << " " << yan << endl;
    cout << "THIRD PART\n";
    for (int i = 0; i < 8; ++i)
    {
        int x0, y0, z0;
        if (an >= 0/radian && an < 90/radian) /// FIRST IF
        {
            x0 = x + 1;
            z0 = z + 1;
        }
        if (an >= 90/radian && an < 180/radian) /// FIRST IF
        {
            x0 = x - 1;
            z0 = z + 1;
        }
        else if (an >= 180/radian && an < 270/radian) /// FIRST IF
        {
            x0 = x - 1;
            z0 = z - 1;
        }
        else if (an >= 270/radian && an < 360/radian) /// FIRST IF
        {
            x0 = x + 1;
            z0 = z - 1;
        }
        if (yan >= -90/radian && yan < 0/radian)
            y0 = y - 1;
        else if (yan >= 0/radian && yan <= 90/radian)
            y0 = y + 1;

        double r1, r2, r3;
        r1 = abs(x0 / cos(an) / cos(yan));
        r2 = abs(y0 / sin(yan));
        r3 = abs(z0 / sin(an) / cos(yan));
        cout << i << " " << x << " " << y << " " << z << endl;
        if (r1 < r2 && r1 < r3)
        {
                y0 = r1 * sin(yan);
                z0 = r1 * cos(yan) * cos(an);
                print(x0, y0, z0);
                int xb, yb, zb;
                xb = x0;
                yb = y0;
                zb = z0;
                print(xb, yb, zb);
                if (xb < a*ach && yb < b*bch && zb < c*cch)
                {
                    if (field[xb][yb][zb] == true)
                    {
                        cout << "answer ";
                        print(xb, yb, zb);
                        cout << field[xb][yb][zb] << endl;
                        field[xb][yb][zb] = 0;
                        break;
                    }
                else if (xb >= a*ach && yb >= b*bch && zb >= c*cch)
                    break;
                }
        }
        else if (r2 < r3)
        {
            x0 = r2 * cos(yan) * cos(an);
            z0 = r2 * cos(yan) * sin(an);
            print(x0, y0, z0);
            int xb, yb, zb;
            xb = x0;
            yb = y0;
            zb = z0;
            print(xb, yb, zb);
            if (xb < a*ach && yb < b*bch && zb < c*cch)
            {
                if (field[xb][yb][zb] == true)
                {
                    cout << "answer ";
                    print(xb, yb, zb);
                    cout << field[xb][yb][zb] << endl;
                    field[xb][yb][zb] = 0;
                    break;
                }
            else if (xb >= a*ach && yb >= b*bch && zb >= c*cch)
                break;
            }
        }
        else
        {
            x0 = r3 * cos(yan) * cos(an);
            y0 = r3 * sin(yan);
            print(x0, y0, z0);
            int xb, yb, zb;
            xb = x0;
            yb = y0;
            zb = z0;
            print(xb, yb, zb);
            if (xb < a*ach && yb < b*bch && zb < c*cch)
            {
                    if (field[xb][yb][zb] == true)
                    {
                        cout << "answer ";
                        print(xb, yb, zb);
                        cout << field[xb][yb][zb] << endl;
                        field[xb][yb][zb] = 0;
                        break;
                    }
            else if (xb >= a*ach && yb >= b*bch && zb >= c*cch)
                break;
            }
        }
        x = x0;
        y = y0;
        z = z0;
    }
    return 0;
}
