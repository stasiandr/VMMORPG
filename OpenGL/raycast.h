//raycast.h

using namespace std;

double pi = 3.141592653589793238462643383279502884197f;

bool IsFull(int, int, int);

block raycast(float x, float y, float z, float an, float yan)
{
    while (an < 0)
        an += 2 * pi;
    while (yan < 0)
        yan += 2 * pi;
    while (an >= 2 * pi)
        an -= 2 * pi;
    while (yan >= 2 * pi)
        yan -= 2 * pi;

    block result;
    bool nfound = true;
    cout << an << " " << cos(an) << " " << sin(an) << "\n"
    << yan << " " << cos(yan) << " " << sin(yan) << endl;
    for (int i = 0; i < 25; ++i)
    {
        float x0;
        float y0;
        float z0;
        if (an <= pi && yan <= pi)
        {
            x0 = static_cast<int>(x + 1);
            y0 = static_cast<int>(y + 1);
            z0 = static_cast<int>(z + 1);
        }
        else if (an > pi && yan <= pi)
        {
            x0 = static_cast<int>(x - 1);
            y0 = static_cast<int>(y + 1);
            z0 = static_cast<int>(z + 1);
        }
        else if (an <= pi && yan > pi)
        {
            x0 = static_cast<int>(x - 1);
            y0 = static_cast<int>(y + 1);
            z0 = static_cast<int>(z - 1);
        }
        else if (an > pi && yan > pi)
        {
            x0 = static_cast<int>(x + 1);
            y0 = static_cast<int>(y + 1);
            z0 = static_cast<int>(z - 1);
        }
        float r1 = abs(x0 / cos(an) / cos(yan));
        float r2 = abs(y0 / sin(yan));
        float r3 = abs(z0 / sin(an) / cos(yan));
        //cout << "i: " << i << " xyz: " << x << " " << y << " " << z << endl;;
        if (r1 < r2 && r1 < r3)
        {
            y0 = r1 * sin(yan);
            z0 = r1 * cos(yan) * cos(an);
            int xb = x0;
            int yb = y0;
            int zb = z0;

            int tex, tey, tez;
            tex = xb % 6;
            tey = yb % 6;
            tez = zb % 6;
            int ch = (int)(xb / 6)*4 + (int)(yb / 6);
            if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '1')
            {
                result.x = xb + int(x);
                result.y = yb + int(y);
                result.z = zb + int(z);
                nfound = false;
                break;
            }
        }
        else if (r2 < r3)
        {
            x0 = r2 * cos(yan) * cos(an);
            z0 = r2 * cos(yan) * sin(an);
            int xb = x0;
            int yb = y0;
            int zb = z0;

            int tex, tey, tez;
            tex = xb % 6;
            tey = yb % 6;
            tez = zb % 6;
            int ch = (int)(xb / 6)*4 + (int)(yb / 6);
            if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '1')
            {
                result.x = xb + int(x);
                result.y = yb + int(y);
                result.z = zb + int(z);
                nfound = false;
                break;
            }
        }
        else
        {
            x0 = r3 * cos(yan) * cos(an);
            y0 = r3 * sin(yan);
            int xb = x0;
            int yb = y0;
            int zb = z0;

            int tex, tey, tez;
            tex = xb % 6;
            tey = yb % 6;
            tez = zb % 6;
            int ch = (int)(xb / 6)*4 + (int)(yb / 6);
            if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '1')
            {
                result.x = xb + int(x);
                result.y = yb + int(y);
                result.z = zb + int(z);
                nfound = false;
                break;
            }
        }
        x = x0;
        y = y0;
        z = z0;
    }
    //cout << "for ended\n";
    if (nfound)
        return result;
    int tex, tey, tez;
    tex = result.x % 6;
    tey = result.y % 6;
    tez = result.z % 6;
    int ch = (int)(result.x / 6)*4 + (int)(result.y / 6);
    if (ch >= 0 and ch < n_c and tex >= 0 and tey >= 0 and tez >= 0)
    {
        if (iss[ch][tex*hei*dee + tey*dee + tez + 12] == '1')
            cout << "YYYYYYYYYYYYYYYYYYPPPPPPPPPPPPPPPPPPPPAAAAAAAAAAAAAAAAAAAAA!!!";
        iss[ch][tex*hei*dee + tey*dee + tez+ 12] = '0';
        cout << ch << " " << tex << " " << tey << " " << tez << " replace successful\n";
    }
    else
    {
        cout << ch << " " << tex << " " << tey << " " << tez << " replace aborted\n";
    }
    return result;
}
