/* 
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/

#include "UsefulFunctions.h"

int main()
{
    int max_num{1'000'000};
    // Make list of primes under 1 million
    std::vector<int> prime_list;
    int n{uf::nextPrime(1)};
    while (n < max_num)
    {
        prime_list.push_back(n);
        n = uf::nextPrime(n);
    }

    int max_sum_length{21}; // Start at 21, because we already know there is a 21
    int target_prime;
    for (int prime_idx{0}; prime_idx < prime_list.size(); prime_idx++)
    {
        int sum_length{max_sum_length}; // Don't bother summing below the max sum length, as we are looking for larger ones
        // First, do a check to see if we have finished the search by seeing if any sum of the current max length is greater than max_num
        long long sum{uf::vectorSum(std::vector(prime_list.begin() + prime_idx, prime_list.begin() + prime_idx + sum_length))};
        if (sum > max_num & sum_length == max_sum_length)
        {
            std::cout << "Prime " << target_prime << " is a sum of " << max_sum_length << " consecutive primes.";
            return 0;
        }
        while (true)
        {
            sum_length++;
            sum = uf::vectorSum(std::vector<int> (prime_list.begin() + prime_idx, prime_list.begin() + prime_idx + sum_length));
            if (sum > max_num)
            {
                // Only break if the sum is larger than the limit
                break;
            }
            else if (uf::isPrime(sum))
            {
                // If we have found a prime, record it but don't stop searching until we reach the sum limit
                target_prime = sum;
                max_sum_length = sum_length;
            }
        }
    }

    return 0;
}