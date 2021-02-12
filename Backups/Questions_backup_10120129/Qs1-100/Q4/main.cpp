/* 
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>

int main()
{
    int biggest_pal{0};
    for (int j{999}; j >= 100; --j)
    {
        for (int k{999}; k >= 100; --k)
        {
            int multiple{j*k};
            std::string str_multiple{std::to_string(multiple)};
            std::reverse(str_multiple.begin(),str_multiple.end());

            if (multiple == std::stoi(str_multiple))
            {
                if (multiple > biggest_pal)
                {
                    biggest_pal = multiple;
                    std::cout << multiple << "\n";
                    std::cout << j << ", " << k << "\n";
                }
            }
        }
    }
    
    
    return 0;
}