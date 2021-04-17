/* 
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the 
family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
*/

#include "UsefulFunctions.h"

std::vector<int> swapElements(std::vector<int> vec, const std::vector<bool> &mask, const int &value)
{
    // Sets values of vec (defined by the mask) to a certain value
    uf::assertMsg(vec.size() == mask.size(), "AAAA");
    for (int j{0}; j < mask.size(); j++)
    {
        if (mask[j])
            vec[j] = value;
    }

    return vec;
}

int main()
{
    int n{11};
    int target_family_length{8};
    while (true)
    {
        std::vector<int> n_digits{uf::int2digits(n)};
        for (int mask_length{1}; mask_length < n_digits.size(); mask_length++)
        {
            std::vector<bool> mask(n_digits.size()); // Using vector<bool> for convenience
            std::fill_n(mask.begin(), mask_length, true);
            std::sort(mask.begin(), mask.end());

            do
            {
                int prime_family_length{0};
                // Make sure we dont swap the first digit with a zero
                int start_digit;
                if (mask[0] == false)
                    start_digit = 0;
                else
                    start_digit = 1;

                for (int digit_val{start_digit}; digit_val <= 9; digit_val++)
                {
                    int n_swapped{uf::digits2int(swapElements(n_digits, mask, digit_val))};
                    if (uf::isPrime(n_swapped))
                        prime_family_length++;
                }
                if (prime_family_length == target_family_length)
                {
                    if (mask[0] == false)
                        std::cout << uf::digits2int(swapElements(n_digits, mask, 0));
                    else
                        std::cout << uf::digits2int(swapElements(n_digits, mask, 1));
                    return 0;
                }
            } while (std::next_permutation(mask.begin(), mask.end()));
        }

        n = uf::nextPrime(n);
    }

    return 0;
}