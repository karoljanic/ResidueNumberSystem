#ifndef BASE_H
#define BASE_H

/// Base is using in creating RNS - number in residue number system
class Base
{
    public:
        /// initialization of blank base
        Base();

        /// initialization of base:
            /// _base - pointer to an array of length _length with the numbers that make up the base
            /// _length - length of array with numbers, number of numbers
        /// it does not validate numbers: each two numbers must be relatively prime
        Base(int *_base, int _length);

        /// destructor of Base object
        virtual ~Base();

        /// initialization of numbers in base:
            /// _base - pointer to an array of length _length with the numbers that make up the base
            /// _length - length of array with numbers, number of numbers
        /// it validate numbers: each two numbers must be relatively prime
            /// if it returns 1 - is OK
            /// if it returns -1 - is not OK - it does not save numbers to base
        int base_init(int *_base, int _length);


        int n; /// length of base
        int M; /// product of the numbers that make up the base
        int m; /// half of the product of the numbers that make up the base, m = M // 2
        int *base_numbers; /// numbers that make up the base
};

#endif // BASE_H
