/* 
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?
*/

#include "UsefulFunctions.h"

int intCircShift(int n)
{
    int n_exponent{static_cast<int>(log10(n))};
    int n_unit{n - (n / 10)*10}; // Integer division
    return (n/10) + n_unit*pow(10,n_exponent);
}

int main()
{
    int max_num{1'000'000};

    int num_circular_primes{1}; // Start at 1 because we assume 2 is already found
    for (int n{3}; n < max_num; n += 2)
    {
        int temp_n{n};
        bool is_circular{true};
        int num_digits{static_cast<int>(log10(n))+1};
        for (int j{1}; j <= num_digits && is_circular; j++)
        {
            is_circular = uf::isPrime(temp_n);
            temp_n = intCircShift(temp_n);
        }
        if (is_circular)
        {
            num_circular_primes++;
            std::cout << n << "\n";
        }
    }

    std::cout << num_circular_primes;

    return 0;
}