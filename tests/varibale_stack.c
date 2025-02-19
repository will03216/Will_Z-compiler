int f()
{
    int x = 0;
    int y = 1;
    {
        int x = 2;
        int z = 3;
        y = x + z;
    }
    return x + y;
}
