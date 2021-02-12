/* 
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

bool isPrime(const long long &n)
{
    // Returns true if n is prime, false if not
    
    if (n % 2 == 0)
    {
        return false;
    }

    long long j{3};
    while (j < (n / 2 + 1))
    {
        if (n % j == 0)
        {
            return false;
        }
        j += 2;
    }

    return true;
}

int main()
{

    long long sum_primes{2}; // Starts having found prime 2
    long long current_num{3};
    long long max_num{2'000'000}; // 2'000'000
    while (current_num < max_num) // Takes a while, less than a minute
    {
        if (isPrime(current_num))
        {
            sum_primes += current_num;
        }

        current_num += 2;
    }

    std::cout << sum_primes;

    return 0;
}