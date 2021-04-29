

int Istrue = false;


bool equal(double num1, double num2)
{
    double result = num1 - num2;
    if(result > -0.00001 && result < 0.00001)
        return true;
    return false;
}

double Power(double base, int exponent)
{
    if(equal(base, 0.0) && exponent < 0)
    {
        Istrue = true;
        return 0.0;
    }
    
    if(equal(base, 0.0))
    {
        Istrue = true;
        return 0.0;
    }



    int absexponent = (exponent > 0 ? exponent : -exponent);
    double result = 1.0;

    for(int i = 0; i < absexponent; i++)
    {
        result *= base;
    }

    if(exponent > 0)
        return result;
    else
        return 1.0/result;
}

#include <stdio.h>
int main()
{
    printf("%lf\n", Power(3.3, 2));
 
    return 0;
}
