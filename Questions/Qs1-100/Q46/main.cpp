/* 
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×12
15 = 7 + 2×22
21 = 3 + 2×32
25 = 7 + 2×32
27 = 19 + 2×22
33 = 31 + 2×12

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/

#include "UsefulFunctions.h"

int &nextOddComposite(int &n)
{
    uf::assertMsg(n != (n / 2) * 2, "n must be odd");
    while (true)
    {
        n += 2;
        if (!uf::isPrime(n))
            break;
    }
    return n;
}

int main()
{
    int n{3};
    while (true)
    {
        nextOddComposite(n);
        bool found_counterexample{true};
        int j{1};
        int square_part{2};
        while (square_part < n)
        {
            if (uf::isPrime(n - square_part))
            {
                found_counterexample = false;
                break;
            }
            ++j;
            square_part = 2 * j * j;
        }
        if (found_counterexample)
        {
            std::cout << n;
            break;
        }
    }
    return 0;
}