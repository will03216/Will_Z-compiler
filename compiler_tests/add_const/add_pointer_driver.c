#include <stdio.h>

int f();

void test(double a)
{
    printf("Test function produced value: %f\n", (float)a + 3.2f);
}

int main()
{

    test(1.5);
    printf("int_variable function returned: %d\n", f());

    return !(f() == 5);
}
