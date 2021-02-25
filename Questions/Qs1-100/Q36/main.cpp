/* 
The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)
*/

#include "UsefulFunctions.h"
#include <bitset>

template <class T>
bool isPalindrome(const std::vector<T> &vec)
{ // Returns true if vec in reverse order is the same as vec
    std::vector<T> vec_reverse{vec};
    std::reverse(vec_reverse.begin(), vec_reverse.end());
    return vec == vec_reverse;
}

std::vector<bool> int2binaryVec(int n)
{ // converts an int into a 32 bit binary number, represented as a bool vector.
    std::bitset<32> n_bin(n);
    int num_bits{32};
    while (n_bin[num_bits - 1] != 1 && num_bits > 0)
        num_bits--;

    std::vector<bool> vec_binary(num_bits);
    for (int j{0}; j < num_bits; ++j)
        vec_binary[j] = (n_bin[j] == 1);
    std::reverse(vec_binary.begin(), vec_binary.end());
    return vec_binary;
}

int main()
{

    int max_num{1'000'000};
    int total_sum{0};

    for (int n{1}; n < max_num; ++n)
    {
        if (isPalindrome(uf::int2digits(n)) && isPalindrome(int2binaryVec(n)))
            total_sum += n;
    }

    std::cout << total_sum;

    return 0;
}