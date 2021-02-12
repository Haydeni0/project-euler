/* 
Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int> num_list(100);
    std::iota(num_list.begin(),num_list.end(),1);

    long long sum_squ{0};
    for (int j : num_list)
    {
        sum_squ += j*j;
    }

    long long squ_sum{0};
    for (int j :num_list)
    {
        squ_sum += j;
    }
    squ_sum *= squ_sum;

    std::cout << -(sum_squ - squ_sum);
}