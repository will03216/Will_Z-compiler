int f () {
    int x[4];
    int *y = &x;
    x[1] = 5;
    int *z = y + 1;
    return *z;
}
