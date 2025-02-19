int f()
{
    int x = 4;
    int y = 3;
    {
        int x = 2;
        int z = 3;
        z = x + y;
        return z;
    }
}
