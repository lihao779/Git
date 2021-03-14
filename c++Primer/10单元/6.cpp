#include <iostream>

using namespace std;

struct Test
{
    Test(/*Test* const this*/)
    {
        auto f1 = [this]{};
        auto f2 = [&this]{};
    }
};

