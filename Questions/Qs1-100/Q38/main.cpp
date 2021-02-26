/* 
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

#include "UsefulFunctions.h"

bool isPandigital(std::vector<int> vec)
{ // Do the digits of the elements of vec make up only the numbers 1 to 9 once?
    std::vector<int> num_digits(vec.size());
    for (int j{0}; j < vec.size(); ++j)
    {
        num_digits[j] = static_cast<int>(log10(vec[j])) + 1;
    }

    if (uf::vectorSum(num_digits) != 9)
        return false;

    // If any numbers have a zero digits, return false
    for (int j{0}; j < vec.size(); ++j)
    {
        if (uf::inVector(0, uf::int2digits(vec[j])))
            return false;
    }

    // Check that each digits occurs only once
    std::vector<int> total_digit_list(9);
    int k{0};
    for (int j{0}; j < vec.size(); ++j)
    {
        for (auto elem : uf::int2digits(vec[j]))
        {
            if (!uf::inVector(elem, total_digit_list))
                total_digit_list[k++] = elem;
            else
                return false;
        }
    }

    // If all the above goes through, the numbers are pandigital.
    return true;
}

int main()
{
    int largest_pandigital{0};

    for (int j{1}; j < 100'000; ++j)
    {
        int num_digits{static_cast<int>(log10(j) + 1)};
        std::vector<int> num_list{j};
        for (int n{2}; num_digits < 9; ++n)
        {
            num_list.push_back(j * n);
            num_digits += static_cast<int>(log10(num_list[n-1]) + 1);
        }
        if (isPandigital(num_list))
        {
            std::vector<int> pandigits;
            for (auto elem : num_list)
            {
                std::vector<int> elem_digits{uf::int2digits(elem)};
                pandigits.insert(pandigits.end(), elem_digits.begin(), elem_digits.end());
            }
            int pandigital_num{uf::digits2int(pandigits)};
            if (pandigital_num > largest_pandigital)
                largest_pandigital = pandigital_num;
        }
    }

    std::cout << largest_pandigital;

    return 0;
}