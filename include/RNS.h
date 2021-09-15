#ifndef RNS_H
#define RNS_H

#include "Base.h"

#include <iostream>
using namespace std;

/// RNS - residue numbers system
class RNS
{
    public:
        /// initialization of "blank" RNS object
        RNS();

        /// initialization of number in RNS
            /// _base - pointer to Base object which contains the modules of the creating number
            /// decimal_number - value of creating number in decimal system
        /// decimal_number be must between: -m and m:
            /// m = (M-1)/2 if M%2 == 1
            /// m = M/2 - 1 if M%2 == 0
                /// M - product of the numbers that make up the base
        RNS(Base *_base, int decimal_number);

        /// initialization of number in RNS
            /// _base - pointer to Base object which contains the modules of the creating number
            /// _representation - pointer to array with numbers which define number in RNS:
                /// length of _representation and length of base numbers must equal
        /// representation must be representation number between: -m and m:
            /// m = (M-1)/2 if M%2 == 1
            /// m = M/2 - 1 if M%2 == 0
                /// M - product of the numbers that make up the base
        RNS(Base *_base, int *_representation);

        /// destructor od RNS object
        virtual ~RNS();

        /// it returns value of number in decimal system
        int to_decimal();


                            /// OPERATOR OVERLOADING ///

        friend ostream &operator << (ostream &exit, RNS &x);
        //friend istream &operator >> (istream &wejscie, RNS &x);

        RNS& operator =(const RNS& x);

        bool operator ==(RNS &x);
        bool operator !=(RNS &x);

        bool operator >(RNS &x);
        bool operator <(RNS &x);

        bool operator >=(RNS &x);
        bool operator <=(RNS &x);

        RNS operator +(RNS &x);
        RNS operator -(RNS &x);
        RNS operator *(RNS &x);
        RNS operator /(RNS &x);

        RNS& operator +=(RNS &x);
        RNS& operator -=(RNS &x);
        RNS& operator *=(RNS &x);
        RNS& operator /=(RNS &x);

        Base *base;
        int *representation;
        int n;
};

#endif // RNS_H
