/* 
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: 
    (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?
*/

#include "UsefulFunctions.h"

int next_prime(int n)
{
    if (n < 2)
    {
        return 2;
    }
    if (uf::isEven(n))
    {
        ++n;
        if (uf::isPrime(n))
            return n;
    }
    n += 2;
    while (!uf::isPrime(n))
    {
        n += 2;
    }
    return n;
}

int main()
{

    int n{next_prime(1000)};

    while (n < 10000)
    {
        for (int diff{1}; diff <= ((10000 - n) / 2 + 1); ++diff)
        {
            int n2{n + diff};
            int n3{n + diff + diff};
            uf::UnorderedDigitID n_ID{n};
            uf::UnorderedDigitID n2_ID{n2};
            uf::UnorderedDigitID n3_ID{n3};

            if (n_ID == n2_ID && n2_ID == n3_ID)
            {
                if (uf::isPrime(n2) && uf::isPrime(n3))
                {
                    std::cout << n << ", " << n2 << ", " << n3 << "\n";
                }
            }
        }
        n = next_prime(n);
    }

    return 0;
}