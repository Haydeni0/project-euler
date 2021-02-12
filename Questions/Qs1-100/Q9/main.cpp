/* 
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // Test all pythagorean triples with b^2 less than 1 million by brute force
    for (int b{2}; b < 1'000'000; ++b)
    {
        for (int a{1}; a < b; ++a)
        {
            long long c_squ{a*a + b*b};
            if ((a + b + sqrt(c_squ)) == 1000)
            {
                std::cout << "a:" << a << ", b:" << b << ", c:" << sqrt(c_squ) << "\n";
                std::cout << "abc: " << (a*b*static_cast<int>(sqrt(c_squ)));
                return 0;
            }
        }
    }
    return 0;
}