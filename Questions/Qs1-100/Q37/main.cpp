/* 
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

#include "UsefulFunctions.h"

bool isLeftRightTruncatable(int n)
{
    if (!uf::isPrime(n))
        return false;
    std::vector<int> digits{uf::int2digits(n)};

    // Check right truncation
    while (digits.size() > 1)
    {
        digits.pop_back();
        if (!uf::isPrime(uf::digits2int(digits)))
            return false;
    }
    // Remake digits
    digits = uf::int2digits(n);
    // Check left truncation
    while (digits.size() > 1)
    {
        digits.erase(digits.begin());
        if (!uf::isPrime(uf::digits2int(digits)))
            return false;
    }

    return true;
}

int main()
{
    int total_sum{0};
    int num_found{0};
    int n{9};
    while (num_found < 11)
    {
        if (isLeftRightTruncatable(n))
        {
            total_sum += n;
            num_found++;
        }
        n += 2;
    }

    std::cout << total_sum;

    return 0;
}