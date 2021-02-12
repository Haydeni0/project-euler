/* 
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

#include "UsefulFunctions.h"

bool isAmicable(long long a)
{
    auto factor_list1{uf::findFactors(a)};
    factor_list1.erase(factor_list1.begin() + 1);

    auto b{uf::sumVector(factor_list1)};
    if (a == b)
        return false;

    auto factor_list2{uf::findFactors(b)};
    factor_list2.erase(factor_list2.begin() + 1);
    if (a == uf::sumVector(factor_list2))
        return true;
    else
        return false;
}

int main()
{

    long long total_amicable{0};
    int num_limit{10000};
    for (int n{1}; n < num_limit; ++n)
    {
        if (isAmicable(n))
        {
            total_amicable += n;
            // std::cout << n << "\n";
        }
    }

    std::cout << total_amicable;

    return 0;
}