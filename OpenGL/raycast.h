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
        cout << an << " " << yan << endl;
        cout << sin(an) << " " << cos(an) << " " << sin(yan) << " " << cos(yan) << endl;
        cout << xc / cos(an) / cos(yan) << ' ' << zc / sin(an) / cos(yan) << ' ' << yc / sin(yan) << endl;
        cout << r1 << ' ' << r2 << ' ' << r3 << endl;
        cout << i << " start" << endl;
        if (r1 < r2 && r1 < r3)
        {
            cout << i << " first if started" << endl;
            int y1, z1;
            z1 = xc / cos(an) * sin (an);
            cout << i << " first if started 2" << endl;
            y1 = xc / cos(an) / cos(yan) * sin(yan);
            cout << i << " first if started 3" << endl;
            if (IsFull(xc, y1, z1))
            {
                result.x = xc;
                result.y = y1;
                result.z = z1;
                break;
            }
            cout << i << " first if finished" << endl;
        }
        else if (r2 < r3)
        {
            int x1, y1;
            x1 = zc / sin(an) * cos(an);
            y1 = zc / sin(an) / cos(yan) * sin(yan);
            if (IsFull(x1, y1, zc))
            {
                result.x = x1;
                result.y = y1;
                result.z = zc;
                break;
            }
        }
        else
        {
            int x1, z1;
            x1 = yc / sin(yan) * cos(yan) * cos(an);
            z1 = yc / sin(yan) * cos(yan) * sin(an);
            if (IsFull(x1, yc, z1))
            {
                result.x = x1;
                result.y = yc;
                result.z = z1;
                break;
            }
        }
        x0 = xc;
        y0 = yc;
        z0 = zc;
        cout << i << " suceed\n";
    }
    iss[result.x*hei*dee + result.y*dee + result.z] = '0';
    cout << "replace sucessfull\n";
    Update();
    return result;
}
