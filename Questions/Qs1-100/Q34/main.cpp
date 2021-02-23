/* 
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: As 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include "UsefulFunctions.h"

int main()
{
    int max_num{uf::factorial(9)};
    int num_digits{1};
    while (pow(10, num_digits) < max_num)
    {
        num_digits++;
        max_num += uf::factorial(9);
    }

    int total_sum{0};

    for (int j{3}; j < max_num; ++j)
    {
        std::vector<int> digits{uf::int2digits(j)};
        int digit_factorial{0};
        for (auto elem : digits)
        {
            digit_factorial += uf::factorial(elem);
        }
        if (digit_factorial == j)
        {
            total_sum += j;
            std::cout << j << "\n";
        }
    }

    std::cout << total_sum;

    return 0;
}