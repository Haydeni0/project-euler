/* 
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
*/

#include "UsefulFunctions.h"

int main()
{
    int largest_pan_prime{0};

    for (int n{1}; n <= 9; n++)
    {
        std::vector<int> vec(n);
        std::iota(vec.begin(), vec.end(), 1);
        for (int j{1}; j < uf::factorial(n); ++j)
        {
            if (uf::isPrime(uf::digits2int(vec)))
                largest_pan_prime = uf::digits2int(vec);
            std::next_permutation(vec.begin(), vec.end());
        }
    }

    std::cout << largest_pan_prime;

    return 0;
}