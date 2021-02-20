/* 
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

#include "UsefulFunctions.h"

/*
Cheating i guess https://www.quora.com/How-would-you-explain-an-algorithm-that-generates-permutations-using-lexicographic-ordering
1. Find the largest x such that P[x]<P[x+1].
(If there is no such x, P is the last permutation.)
2. Find the largest y such that P[x]<P[y].
3. Swap P[x] and P[y].
4. Reverse P[x+1 .. n].
*/

int main()
{
    int max_num{9};
    uf::assertMsg(max_num >= 0, "Bigger than 0 please");
    // Make a vector from 0 to max_num
    std::vector<int> v(max_num + 1);
    std::iota(std::begin(v), std::end(v), 0);

    int max_perm{1'000'000};

    for (int j{2}; j <= max_perm; j++)
    {
        // Step 1
        int x{-1};
        int y{0};
        for (int k{0}; k < max_num; ++k)
        {

            if (v[k] < v[k + 1])
            {
                x = k;
            }
        }
        if (x == -1)
        { // Lexicographic permutations have finished
            std::cout << "ENDED\n";
            uf::printVector(v);
            return 0;
        }

        // Step 2
        for (int k{0}; k <= max_num; ++k)
        {

            if (v[x] < v[k])
            {
                y = k;
            }
        }

        // Step 3
        std::iter_swap(v.begin() + x, v.begin() + y);

        // Step 4
        for (int k{0}; k <= (max_num - x-1) / 2; ++k) // Note integer division with max_num
        {
            std::iter_swap(v.begin() + x + 1 + k, v.begin() + max_num - k);
        }
    }

    uf::printVector(v);
    for (auto elem : v)
    {
        std::cout << elem;
    }
    return 0;
}