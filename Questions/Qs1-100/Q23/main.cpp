/* 
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. 
By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. 
However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the 
sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include "UsefulFunctions.h"

int main()
{

    // First step: Find all abundant numbers under 28123

    std::vector<int> abundant_numbers;
    int max_num{28123}; // 28123
    for (int j{1}; j <= max_num; ++j)
    {
        long long sum{uf::vectorSum(uf::findFactors(j, 1))};
        if (j < sum)
            abundant_numbers.push_back(j);
    }

    // Second step: list every number under 28124 that can be can be written as a sum of two abundant numbers

    std::vector<int> sum_2abundant;

    for (int j{0}; j < abundant_numbers.size(); ++j)
    {
        for (int k{j}; k < abundant_numbers.size(); ++k)
        {
            int ab_sum{abundant_numbers[j] + abundant_numbers[k]};
            if ((ab_sum <= max_num) && (std::find(sum_2abundant.begin(),sum_2abundant.end(), ab_sum) == sum_2abundant.end()))
            {
                sum_2abundant.push_back(ab_sum);
            }
        }
    }

    long long total_sum{0};
    for (int j{1}; j <= max_num; ++j)
    {
        if ((std::find(sum_2abundant.begin(),sum_2abundant.end(), j) == sum_2abundant.end()))
        {
            total_sum += j;
        }
    }

    // uf::printVector(abundant_numbers);
    // uf::printVector(sum_2abundant);

    std::cout << total_sum;

    return 0;
}