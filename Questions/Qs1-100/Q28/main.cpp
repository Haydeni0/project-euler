/* 
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

#include "UsefulFunctions.h"

int main()
{
    /* 
    The formula is 1+ sum_{n=2}^{501}(4k^2 - 6(k-1)), where k = 2n-1.
    */

    int result{1};

    for (int n{2}; n <= 501; ++n)
    {
        int k{2 * n - 1};
        result += 4*k*k - 6*(k-1);
    }

    std::cout << result;

    return 0;
}