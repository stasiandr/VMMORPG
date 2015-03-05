//raycast.h

using namespace std;

bool IsFull(int, int, int);

block raycast(float x, float y, float z, float an, float yan)
{
    block result;
    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int z0 = static_cast<int>(z);
    for (int i = 0; i < 25; ++i)
    {
        cout << i << endl;
        int xc = x0 + 1;
        int yc = y0 + 1;
        int zc = z0 + 1;
        int r1, r2, r3;
        r1 = xc / cos(an) / cos(yan);
        r2 = zc / sin(an) / cos(yan);
        r3 = yc / sin(yan);
        /*cout << an << " " << yan << endl;
        cout << sin(an) << " " << cos(an) << " " << sin(yan) << " " << cos(yan) << endl;
        cout << xc / cos(an) / cos(yan) << ' ' << zc / sin(an) / cos(yan) << ' ' << yc / sin(yan) << endl;
        cout << r1 << ' ' << r2 << ' ' << r3 << endl;
        cout << i << " start" << endl;*/
        if (r1 < r2 && r1 < r3)
        {
            int y1, z1;
            z1 = xc / cos(an) * sin (an);
            y1 = xc / cos(an) / cos(yan) * sin(yan);
            if (IsFull(xc, y1, z1))
            {
                cout << xc << " " << y1 << " " << z1 << " In 1 if has gone" << endl;
                result.x = xc;
                result.y = y1;
                result.z = z1;
                break;
            }
        }
        else if (r2 < r3)
        {
            int x1, y1;
            x1 = zc / sin(an) * cos(an);
            y1 = zc / sin(an) / cos(yan) * sin(yan);
            if (IsFull(x1, y1, zc))
            {
                cout << x1 << " " << y1 << " " << zc << " In 2 if has gone" << endl;
                result.x = x1;
                result.y = y1;
                result.z = zc;
                break;
            }
            cout << " 2 if finished" << endl;
        }
        else
        {
            int x1, z1;
            x1 = yc / sin(yan) * cos(yan) * cos(an);
            z1 = yc / sin(yan) * cos(yan) * sin(an);
            if (IsFull(x1, yc, z1))
            {
                cout << x1 << " " << yc << " " << z1 << " In 3 if has gone" << endl;
                result.x = x1;
                result.y = yc;
                result.z = z1;
                break;
            }
            cout << " 3 if finished" << endl;
        }
        x0 = xc;
        y0 = yc;
        z0 = zc;
        cout << i << " suceed\n";
    }
    int tex, tey, tez;
    tex = result.x % 6;
    tey = result.y % 6;
    tez = result.z % 6;
    int ch = (int)(result.x / 6)*4 + (int)(result.y / 6);
    cout << ch << " " << tex << " " << tey << " " << tez << " before replacing\n";
    iss[ch][tex*hei*dee + tey*dee + tez] = '0';
    cout << "replace sucessfull\n";
    //Update();
    return result;
}
