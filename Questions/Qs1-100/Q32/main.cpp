/* 

*/

#include "UsefulFunctions.h"

bool isPandigital(int a, int b, int c)
{ // Do the digits of a, b and c make up only the numbers 1 to 9 once?
    int num_digits_a{static_cast<int>(log10(a)) + 1};
    int num_digits_b{static_cast<int>(log10(b)) + 1};
    int num_digits_c{static_cast<int>(log10(c)) + 1};
    if (num_digits_a + num_digits_b + num_digits_c != 9)
        return false;

    std::vector<int> digits_a{uf::int2digits(a)};
    std::vector<int> digits_b{uf::int2digits(b)};
    std::vector<int> digits_c{uf::int2digits(c)};

    // If any numbers have a zero digits, return false
    if (uf::inVector(0, digits_a) || uf::inVector(0, digits_b) || uf::inVector(0, digits_c))
        return false;

    std::vector<int> total_digit_list(9);
    int k{0};
    for (int j{0}; j < num_digits_a; ++j)
    {
        if (!uf::inVector(digits_a[j], total_digit_list))
            total_digit_list[k++] = digits_a[j];
        else
            return false;
    }
    for (int j{0}; j < num_digits_b; ++j)
    {
        if (!uf::inVector(digits_b[j], total_digit_list))
            total_digit_list[k++] = digits_b[j];
        else
            return false;
    }
    for (int j{0}; j < num_digits_c; ++j)
    {
        if (!uf::inVector(digits_c[j], total_digit_list))
            total_digit_list[k++] = digits_c[j];
        else
            return false;
    }
    return true;
}

int main()
{
    std::vector<int> product_list;

    for (int a{1}; a <= 9999; ++a)
    {
        for (int b{1}; b <= 10000 - a; ++b)
        {
            int product{a * b};
            if (isPandigital(a, b, product) && !uf::inVector(product, product_list))
                product_list.push_back(product);
        }
    }

    uf::printVector(product_list);
    std::cout << uf::vectorSum(product_list);
    return 0;
}