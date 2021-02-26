/* 
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
*/

#include "UsefulFunctions.h"

int main()
{   
    int product{1};
    int n{1};
    for (int j{2}; n < 1'000'000; ++j)
    {
        for (int k{1}; k <= uf::numDigits(j); ++k)
        {
            ++n;
            if (n == 1 || n == 10 || n == 100 || n == 1000 || n == 10000 || n == 100000 || n == 1000000 )
            {
                product *= uf::int2digits(j)[k-1];
            }
        }
    }

    std::cout << product;

    return 0;
}