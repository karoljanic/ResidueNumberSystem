#include "Base.h"

int gcd(int a, int b)
{
    int t;
    while(b)
    {
        t = b;
        b = a%b;
        a = t;
    }
    return a;
}

Base::Base()
{

}

Base::~Base()
{
    delete [] base_numbers;
}

Base::Base(int *_base, int _length)
{
    n = _length;
    base_numbers = _base;

    M = 1;
    for(int i = 0; i<n; i++)
        M*= base_numbers[i];

    if(M%2 == 1)
        m = (M-1)/2;
    else
        m = M/2-1;
}

int Base::base_init(int *_base, int _length)
{
    for(int i = 0; i<_length-1; i++)
    {
        for(int j = i+1; j<_length; j++)
        {
            if(gcd(_base[i], _base[j]) != 1)
                return -1;
        }
    }

    n = _length;
    base_numbers = _base;

    M = 1;
    for(int i = 0; i<n; i++)
        M*= base_numbers[i];

    if(M%2 == 1)
        m = (M-1)/2;
    else
        m = M/2-1;

    return 1;
}
