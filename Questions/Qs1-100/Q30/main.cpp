/* 
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 14 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

#include "UsefulFunctions.h"

bool isDigitFifthPower(std::vector<int> digits)
{
    int num;
    int exp{0};
    for (int j{(int)digits.size() - 1}; j >= 0; --j)
    {
        num += digits[j] * (pow(10, exp++));
    }

    int digit_power_sum{0};
    for (auto elem : digits)
    {
        digit_power_sum += elem * elem * elem * elem * elem;
    }

    return (digit_power_sum == num);
}
bool isDigitFifthPower(VectorFloat VF_digits)
{
    int digit_power_sum{0};
    for (auto elem : VF_digits.get_mantissa())
    {
        digit_power_sum += elem * elem * elem * elem * elem;
    }

    return (digit_power_sum == static_cast<int>(VF_digits.get_dbl()));
}

int main()
{
    // std::vector<int> digits{8, 2, 0, 8};
    // VectorFloat digits{8208,4};
    // std::cout << isDigitFifthPower(digits);

    // Make a list of 0:9 to the power of 5
    std::vector<int> digit_pow_list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int j{0}; j < digit_pow_list.size(); ++j)
        digit_pow_list[j] = pow(digit_pow_list[j], 5);

    uf::printVector(digit_pow_list);

    VectorFloat VF_total;
    for (VectorFloat VF_count{2, 1}; VF_count <= 1e6; VF_count += 1)
    {
        if (isDigitFifthPower(VF_count))
        {
            std::cout << VF_count << "\n";
            VF_total += VF_count;
        }
    }

    std::cout << VF_total;

    return 0;
}