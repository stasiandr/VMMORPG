//raycast.h

struct block
{
    int x, y, z;
    int xid, yid, zid;
};

block raycast(float x0, float y0, float z0, float an, float yan)
{
    for (int i = 0; i < 25; ++i)
    {
        int r1, r2, r3;
        r1 = x0 / cos(an) / cos(yan);
        r2 = z0 / sin(an) / cos(yan);
        r3 = y0 / sin(yan);
        if (r1 < r2 && r1 < r3)
        {
            int y1, z1;
            z1 = x0 / cos(an) * sin (an);
            y1 = x0 / cos(an) / cos(yan) * sin(yan);
            IsFull(x0, y1, z1);
        }
        else if (r2 < r3)
        {
            int x1, y1;
            x1 = z0 / sin(an) * cos(an);
            y1 = z0 / sin(an) / cos(yan) * sin(yan);
            IsFull(x0, y1, z1);
        }
        else
        {
            int x1, z1;
            x1 = y0 / sin(yan) * cos(yan) * cos(an);
            z1 = y0 / sin(yan) * cos(yan) * sin(an);
        }
    }
}
