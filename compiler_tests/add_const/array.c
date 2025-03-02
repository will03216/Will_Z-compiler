int f()
{
    int i;
    int x[8];
    int acc;
    acc=0;
    for(i=8; i<10; i++){
        x[i-8]=i;
        acc = acc + x[i-8];
    }
    return acc;
}
