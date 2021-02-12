/* 
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

/*
Beyond terrible implementation where we find all the prime factors and multiply them together, like doing it by hand.
A better implementation would use a recursive gcd function to find the lcm of two numbers. 
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <numeric>
#include <algorithm>

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

int findIndex(const std::vector<int> vec, int x)
{
    int idx{0};
    for (int elem : vec)
    {
        if (elem == x)
        {
            return (idx);
        }
        else ++idx;
    }
    return -1;
}

int main()
{

    // auto [p_list, p_count]{findPrimeFactors(2)};
    // return 0;

    // List of numbers to find the Lowest common multiple of
    std::vector<int> num_list(20);
    std::iota(num_list.begin(),num_list.end(),1);
    num_list.erase(std::remove(num_list.begin(), num_list.end(), 1), num_list.end()); // Remove ones from list

    // Iterate through the list first to find all the primes
    std::vector<int> prime_list;
    for (int num : num_list)
    {
        auto [p_list, p_count]{findPrimeFactors(num)};
        for (int elem : p_list)
        {
            if (findIndex(prime_list, elem) == -1)
            {
                prime_list.push_back(elem);
            }
        }
    }
    // Iterate through again to find the number of each prime
    std::vector<int> prime_count(prime_list.size(), 0);
    for (int num : num_list)
    {
        auto [p_list, p_count]{findPrimeFactors(num)};
        for (int j{0}; j < p_list.size(); ++j)
        {
            int prime_idx{findIndex(prime_list, p_list[j])};
            if (prime_count[prime_idx] < p_count[j])
            {
                prime_count[prime_idx] = p_count[j];
            }

        }
    }

    for (int elem : prime_list)
    {
        std::cout << elem << ", ";
    }

    std::cout << "\n";

    long long LCM{1};
    for (int j{0}; j <= prime_list.size(); ++j)
    {
        LCM *= pow(prime_list[j],prime_count[j]);
    }

    std::cout << LCM;

    return 0;
}