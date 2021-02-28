/* 
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, 
but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.
*/

#include "UsefulFunctions.h"
#include "VectorFloat.h"

int main()
{

    VectorFloat total_sum{0};

    // Generate combinations of 0 to 9: all 0-9 pandigital numbers.
    std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int j{1}; j <= uf::factorial(10); ++j)
    {
        std::next_permutation(vec.begin(), vec.end());

        if (((uf::digits2int(std::vector<int>(vec.begin() + 1, vec.begin() + 4)) % 2) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 2, vec.begin() + 5)) % 3) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 3, vec.begin() + 6)) % 5) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 4, vec.begin() + 7)) % 7) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 5, vec.begin() + 8)) % 11) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 6, vec.begin() + 9)) % 13) == 0) &&
            ((uf::digits2int(std::vector<int>(vec.begin() + 7, vec.begin() + 10)) % 17) == 0))
        {
            uf::printVector(vec);
            VectorFloat vec_VF(std::vector<short>(vec.begin(),vec.end()),9,true);
            total_sum += vec_VF;
        }
    }

    std::cout << total_sum;


    return 0;
}