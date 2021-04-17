/* 
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

#include "UsefulFunctions.h"

int main()
{
    int n{1};

    while (true)
    {
        bool all_true{true};
        uf::UnorderedDigitID N{n};
        for(int mult{2}; mult <= 6; mult ++)
        {
            uf::UnorderedDigitID N_mult{n*mult};
            if (!(N == N_mult))
                all_true = false;
        }
        if (all_true)
        {
            std::cout << n;
            break;
        }
        ++n;
    }

    return 0;
}