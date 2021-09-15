#include <iostream>

#include "RNS.h"

using namespace std;

int modular_multiplicative_inverse(int a, int b)
{
    int q, u = 1, x = 0, w = a, z = b;

    while(w)
    {
        if( w < z )
        {
            q = u;
            u = x;
            x = q;
            q = w;
            w = z;
            z = q;
        }
        q = w / z;
        u -= q * x;
        w -= q * z;
    }

    if(x<0)
        return x+b;
    else
        return x;
}

int neg(int a, int m)
{
    int b = m, x = 1, y = 0, n = 0;
    int t;
    while(a != 0)
    {
        n = (int)b/a;
        t = a;
        a = b - n * a;
        b = t;
        t = x;
        x = y - n * x;
        y = t;
    }
    while(y<0)
        y+=m;
    return y%m;
}

void to_mixed_radix_system(int *_representation, Base *_base, int len, int it, int *_result)
{

    if(len-1 == it)
    {
        _result[it] = _representation[it];
        for(int i = 0; i<len/2; i++)
            swap(_result[i], _result[len-1-i]);

        for(int i = 0; i<len; i++)
        {
            while(_result[i] < 0)
                _result[i] += _base->base_numbers[i];
        }
        return;
    }
    else
    {
        int x = _representation[it];
        _result[it] = x;
        int new_rep[len], new_bas[len], new_data[len];
        for(int i = it+1; i<len; i++)
        {
            new_rep[i] = _representation[i]-x;
            new_bas[i] = neg(_base->base_numbers[it], _base->base_numbers[i]);
            new_data[i] = new_rep[i] * new_bas[i];
            new_data[i] %= _base->base_numbers[i];
            while(new_data[i]<0)
                new_data[i]+=_base->base_numbers[i];
        }
        to_mixed_radix_system(new_data, _base, len, it+1, _result);
    }
}

RNS::RNS()
{

}

RNS::~RNS()
{
    delete [] representation;
}

RNS::RNS(Base *_base, int _decimal_number)
{
    n = _base->n;
    base = _base;
    representation = new int[n];
    for(int i = 0; i<n; i++)
    {
        representation[i] = (_decimal_number+_base->m)%(_base->base_numbers[i]);
        representation[i] %= base->base_numbers[i];
        while(representation[i]<0)
            representation[i] += _base->base_numbers[i];
    }

}

RNS::RNS(Base *_base, int *_representation)
{
    n = _base->n;
    base = _base;
    representation = new int[n];

    for(int i = 0; i<n; i++)
    {
        representation[i] = _representation[i];
        while(representation[i]<0)
            representation[i] += base->base_numbers[i];
    }
}

int RNS::to_decimal()
{
    int m_prim, result = 0;
    for(int i = 0; i<n; i++)
    {
        m_prim = base->M / base->base_numbers[i];
        result += m_prim * modular_multiplicative_inverse(m_prim, base->base_numbers[i])*representation[i];
    }

    return result%(base->M)-(base->m);
}

ostream &operator <<(ostream &wyjscie, RNS &x)
{
    wyjscie << "< ";
    for(int i = 0; i<x.n; i++)
        wyjscie << x.representation[i] << " ";
    wyjscie << ">";
    return wyjscie;
}

istream &operator >>(istream &exit, RNS& x)
{
    exit >> x.n;
    for(int i = 0; i<x.n; i++)
        exit >> x.representation[i];

    return exit;
}

RNS& RNS::operator =(const RNS& x)
{
    for(int i = 0; i<n; i++)
    representation[i] = x.representation[i];

    return *this;
}

bool RNS::operator ==(RNS &x)
{
    for(int i = 0; i<n; i++)
    {
        if(base->base_numbers[i] != x.base->base_numbers[i])
            return false;

    }

    for(int i = 0; i<n; i++)
    {
        if(representation[i] != x.representation[i])
            return false;

    }
    return true;
}

bool RNS::operator !=(RNS &x)
{
    for(int i = 0; i<n; i++)
    {
        if(base->base_numbers[i] != x.base->base_numbers[i])
            return true;

    }

    for(int i = 0; i<n; i++)
    {
        if(representation[i] != x.representation[i])
            return true;

    }
    return false;
}

bool RNS::operator >(RNS &x)
{
    int result_a[n];
    int result_b[n];

    to_mixed_radix_system(representation, base, n, 0, result_a);
    to_mixed_radix_system(x.representation, base, n, 0, result_b);

    for(int i = 0; i<n; i++)
    {
        if(result_a[i]>result_b[i])
            return true;
        else if(result_b[i]>result_a[i])
            return false;
    }

    return false;
}

bool RNS::operator <(RNS &x)
{
    int result_a[n];
    int result_b[n];
    to_mixed_radix_system(representation, base, n, 0, result_a);
    to_mixed_radix_system(x.representation, base, n, 0, result_b);

    for(int i = 0; i<n; i++)
    {
        if(result_a[i]<result_b[i])
            return true;
        else if(result_b[i]<result_a[i])
            return false;
    }

    return false;
}

bool RNS::operator >=(RNS &x)
{
    if(*this == x)
        return true;

    int result_a[n];
    int result_b[n];
    to_mixed_radix_system(representation, base, n, 0, result_a);
    to_mixed_radix_system(x.representation, base, n, 0, result_b);

    for(int i = 0; i<n; i++)
    {
        if(result_a[i]>result_b[i])
            return true;
        else if(result_b[i]>result_a[i])
            return false;
    }

    return false;
}

bool RNS::operator <=(RNS &x)
{
    if(*this == x)
        return true;
    int result_a[n];
    int result_b[n];
    to_mixed_radix_system(representation, base, n, 0, result_a);
    to_mixed_radix_system(x.representation, base, n, 0, result_b);

    for(int i = 0; i<n; i++)
    {
        if(result_a[i]<result_b[i])
            return true;
        else if(result_b[i]<result_a[i])
            return false;
    }

    return false;
}

RNS RNS::operator +(RNS &x)
{
    RNS m = RNS(base, 0);
    int *nums = new int[n];
    for(int i = 0; i<n; i++)
    {
        nums[i] = representation[i]+x.representation[i]-m.representation[i];
        nums[i] %= base->base_numbers[i];
        while(nums[i]<0)
            nums[i] += base->base_numbers[i];
    }

    return RNS(base, nums);
}

RNS RNS::operator -(RNS &x)
{
    RNS m = RNS(base, 0);
    int *nums = new int[n];
    for(int i = 0; i<n; i++)
    {
        nums[i] = (representation[i]-x.representation[i]+m.representation[i]);
        nums[i] %= base->base_numbers[i];
        while(nums[i]<0)
            nums[i] += base->base_numbers[i];
    }

    return RNS(base, nums);
}

RNS RNS::operator *(RNS &x)
{
    RNS m = RNS(base, 0);
    int *nums = new int[n];
    for(int i = 0; i<n; i++)
    {
        nums[i] = ((representation[i]-m.representation[i]) * (x.representation[i]-m.representation[i])) % base->base_numbers[i];
        nums[i] += m.representation[i];
        nums[i] %= base->base_numbers[i];
        while(nums[i]<0)
            nums[i] += base->base_numbers[i];
    }

    return RNS(base, nums);
}

RNS RNS::operator /(RNS &x)
{
    if(*this == x)
        return RNS(base, 1);

    RNS k = RNS(base, -1);
    k *= x;
    if(*this == k)
        return RNS(base, -1);

    RNS m = RNS(base, 0);
    RNS two = RNS(base, 2);
    RNS zero = RNS(base, 0);
    RNS minus_one = RNS(base, -1);
    RNS previus_k = RNS(base, 0);
    RNS D = *this+m;
    RNS p = RNS(base, 0);
    RNS result = RNS(base, 0);
    RNS X =  x+m;
    int type = 0;

    if(*this < zero && X < zero)
    {
        D *= minus_one;
        X *= minus_one;

    }
    else if(*this < zero)
    {
        D *= minus_one;
        type = 1;
    }
    else if(X < zero)
    {
        X *= minus_one;
        type = 1;
    }

    while(true)
    {
        previus_k = RNS(base, 0);
        k = RNS(base, 1);

        while(k*X<=D)
        {
            previus_k = k;
            k *= two;
        }
        p = previus_k*X;
        D-=p;
        result += previus_k;
        if(previus_k == zero)
            break;
    }

    if(type == 0)
        return result+m;
    else
        return (result+m)*minus_one;
}

RNS& RNS:: operator +=(RNS &x)
{
    RNS m = RNS(base, 0);
    for(int i = 0; i<n; i++)
    {
        representation[i] = representation[i] + x.representation[i] - m.representation[i];
        representation[i] %= base->base_numbers[i];
        while(representation[i]<0)
            representation[i] += base->base_numbers[i];
    }
    return * this;
}

RNS& RNS:: operator -=(RNS &x)
{
   RNS m = RNS(base, 0);
    for(int i = 0; i<n; i++)
    {
        representation[i] = representation[i] - x.representation[i] + m.representation[i];
        representation[i] %= base->base_numbers[i];
        while(representation[i]<0)
            representation[i] += base->base_numbers[i];
    }
    return * this;
}

RNS& RNS:: operator *=(RNS &x)
{
    RNS m = RNS(base, 0);
    for(int i = 0; i<n; i++)
    {
        representation[i] = ((representation[i]-m.representation[i]) * (x.representation[i]-m.representation[i])) % base->base_numbers[i];
        representation[i] += m.representation[i];
        representation[i] %= base->base_numbers[i];
        while(representation[i]<0)
            representation[i] += base->base_numbers[i];
    }
    return * this;
}

RNS& RNS:: operator /=(RNS &x)
{
    *this = *this/x;
    return * this;
}

