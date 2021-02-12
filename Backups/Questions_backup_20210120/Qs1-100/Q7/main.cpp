/* 
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

std::tuple<std::vector<int>, std::vector<int>> findPrimeFactors(long long n)
{
    std::vector<int> prime_list;
    std::vector<int> prime_count;

    int n_primes{0};
    while (n % 2 == 0)
    {
        if (n_primes == 0)
        {
            prime_list.push_back(2);
            prime_count.push_back(0);
            ++n_primes;
        }
        ++prime_count[0];
        n >>= 1; // Divide n by 2
    }

    for (int j{3}; n > 1; j += 2)
    {
        bool new_prime{true};
        while (n % j == 0)
        {
            if (new_prime)
            {
                prime_list.push_back(j);
                prime_count.push_back(1);
                ++n_primes;
                new_prime = false;
            }
            else
            {
                ++prime_count[n_primes - 1];
            }

            n = n / j;
        }
    }

    return {prime_list, prime_count};
}

int main()
{
    int num_prime{1}; // Starts having found prime 2
    int current_num{3};
    int nth_prime{10001};
    while (num_prime < nth_prime)
    {
        auto [p_list, p_count]{findPrimeFactors(current_num)};
        if ((p_list.size() == 1) && (p_count[0] == 1))
        {
            ++num_prime;
            // std::cout << current_num << ", ";
        }

        current_num += 2;
    }

    std::cout << current_num - 2;

    return 0;
}