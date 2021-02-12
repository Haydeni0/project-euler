/* 
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/

#include "UsefulFunctions.h"

int main()
{
    std::vector<short> digits{1};
    for (int n{1}; n <= 100; ++n)
    {
        UsefulFunctions::veryLongMultiply(digits,n);
    }


    std::reverse(digits.begin(),digits.end());
    UsefulFunctions::printVector(digits);

    long long digit_sum{0};
    for (auto elem : digits)
    {
        digit_sum += elem;
    }

    std::cout << digit_sum;

    return 0;
}