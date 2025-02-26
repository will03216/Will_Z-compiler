int f(int x, int y)
{
    int acc=0;
    while(x > 0){
        acc += 1;
        x--;
    }
    return acc + y ;
}
