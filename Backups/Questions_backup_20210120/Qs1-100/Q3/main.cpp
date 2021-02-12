/* 
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    long long input_num{600851475143};//600851475143 //13195
    long long biggest_prime;

    long long n{input_num};
    
    while (n % 2 == 0)
    {
        biggest_prime = 2;
        n >>= 1; // Divide n by 2
    }


    for (int j{3}; (j <= input_num) && (j <= n); j += 2)
    {
        while (n % j == 0)
        {
            biggest_prime = j;
            n = n/j;
        }
    }

    
    std::cout << biggest_prime;
    
    return 0;
}