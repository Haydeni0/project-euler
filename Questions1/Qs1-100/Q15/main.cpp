/* 
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.


How many such routes are there through a 20×20 grid?
*/

#include "UsefulFunctions.h"

long long sum(int N)
{
    // Sums numbers 1 to N
    long long SUM{0};
    for (int j{1}; j <= N; ++j)
    {
        SUM += j;
    }
    return SUM;
}

long long recursiveSum(int N, int num_recur)
{
    long long total_sum{0};
    for (int j{1}; j <= N; ++j)
    {
        if (num_recur > 0)
        {
            total_sum += recursiveSum(j, num_recur - 1);
        }
        else
        {
            total_sum += j;
        }
    }

    return total_sum;
}

int main()
{
    /* 
    Let sum[4,k](k) be the notation for a sum of k = 1 to 4, i.e 1+2+3+4. 
    Further, sum[N,k](k^2) = 1+2^2+3^2+...+(N-1)^2+N^2,
    and sum[3,a1](a1+1) = (1+1) + (2+1) + (3+1).

    On paper, the formula for routes through an NxN grid is:
    sum[N+1,k1]( sum[k1,k2]( sum[k2,k3]( ... ( sum[k{N-2},k{N-1}](k{N-1}) )))

    This is true for N > 1.
    */

    int N{20}; // Takes a while

    // sum of 1 to (N+1), with (N-2) recursions
    std::cout << recursiveSum(N+1, N-2);
    return 0;
}