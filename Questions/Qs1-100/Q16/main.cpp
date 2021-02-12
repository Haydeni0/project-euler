/* 
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

#include "UsefulFunctions.h"

int main()
{
    int power{1000};
    // Vector to store the digits to sum: {8,6,7,2,3} for the example given above. Starts at 2
    std::vector<int> digits{2};

    // Store the number as
    for (int p{2}; p <= power; ++p)
    {
        for (long j{0}; j < digits.size(); ++j)
        {
            digits[j] *= 2; // Operation (multiply by 2 in this case)
        }
        for (long j{0}; j < digits.size(); ++j)
        {
            if (digits[j] > 9)
            {
                int tens{digits[j] / 10}; // Integer division
                int unit{digits[j] - 10 * tens};
                if ((j + 1) >= digits.size())
                    digits.push_back(tens);
                else
                    digits[j + 1] += tens;
                digits[j] = unit;
            }
        }
    }

    // Print the number
    for (int j{digits.size() - 1}; j >= 0; --j)
    {
        std::cout << digits[j];
    }

    long digit_sum{0};
    for (int elem : digits)
    {
        digit_sum += elem;
    }

    std::cout << "\n";
    std::cout << "Sum of digits: " << digit_sum;

    return 0;
}