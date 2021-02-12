/* 
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

#include <iostream>
#include <cmath>
int main()
{
    double three{3};
    double five{5};
    int max_num{1000};
    int sum_total{0};

    for (int j{1}; j < 1000; ++j)
    {
        double div_three{j/three};
        double div_five{j/five};
        if (((div_three - static_cast<int>(div_three)) == 0)  || ((div_five - static_cast<int>(div_five)) == 0))
        {
            sum_total += j;
        }
    }

    std::cout << sum_total;
}