/* 
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
*/

#include "UsefulFunctions.h"

int main()
{
    std::vector<int> four_ints(4,-1);
    int vec_idx{0};

    for (int n{647}; four_ints[3] == -1; n++)
    {
        auto [prime_list, prime_count]{uf::findPrimeFactors(n)};
        if (prime_list.size() == 4)
        {
            four_ints[vec_idx++] = n;
        }
        else
        {
            four_ints = std::vector<int>(4,-1);
            vec_idx = 0;
        }
    }
    std::cout << four_ints[0];

    return 0;
}