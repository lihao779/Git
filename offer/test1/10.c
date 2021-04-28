#include <stdio.h>


bool equal(double num1, double num2)
{
    double precision = num1 - num2;
    if(precision > -0.000001 && precision < 0.000001)
        return true;
    else
        return false;
}

double Power(double base, int exponent)
{
    if(equal(base, 0.0))
        return 0.0;
    int absexponent = (exponent >= 0 ? exponent : -exponent);
    
    double result = 1.0;
    for(int i = 0;i < absexponent; i++)
        result *= base;

    if(exponent > 0)
        return result;
    else
        return 1.0/result;
}

int main()
{
    double i = 2.0;
    scanf("%lf", &i);
    printf("%lf\n", Power(i, 2147483647));
    return 0;
}
