/* 
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include "UsefulFunctions.h"

int main()
{
    long long biggest_chain{0};
    long long biggest_chain_num{0};

    for (long long start_num{1}; start_num < 1e6; ++start_num)
    {
        long long chain_length{1};
        long long n{start_num};
        while (n > 1)
        {
            if (n % 2 == 0)
                n /= 2;
            else
                n = 3 * n + 1;
            ++chain_length;
        }
        if (chain_length > biggest_chain)
        {
            biggest_chain = chain_length;
            biggest_chain_num = start_num;
        }
    }
    std::cout << "Start number: " << biggest_chain_num << "\n"
              << "Chain length: " << biggest_chain;

    return 0;
}