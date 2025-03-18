
#include <stdio.h>

float f();

void test(double a)
{
    printf("Test function produced value: %f\n", (float)a + 3.2f);
}

int main()
{

    test(5.5);
    printf("float function returned: %f\n", f());

    return !(f() == 3.0000001);
}
