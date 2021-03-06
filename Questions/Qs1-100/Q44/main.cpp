/* 
Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal and D = |Pk − Pj| is minimised; what is the value of D?
*/

#include "UsefulFunctions.h"

size_t pentagonal(size_t n)
{
    return n * (3 * n - 1) / 2;
}

bool isPentagonal(size_t Pn)
{
    double n{(1 + sqrt(24 * Pn + 1)) / 6};
    // If n is an integer return true
    double intpart;
    return modf(n, &intpart) == 0.0;
}

int main()
{
    // Pentagonal numbers Pn = n(3n-1)/2
    // 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
    // Their consecutive differences = 3n+1
    //  4, 7,  10, 13, 16, 19, 22, 25,  28, 31, 34

    // To minimise D, I should check the pairs in order: smallest D, ascending
    // so D = 4, 7, 10, (4+7), 13, 16, (7+10), 19, (4+7+10), 22, (10+13), 25, 28, (13+16), (7+10+13), 31, 34, (4+7+10+13), (16+19)
    // for P2-P1, P3-P2, P4-P3, P3-P1, ...

    // std::cout << isPentagonal(92);
    // std::cout << isPentagonal(1103080226);
    // return 0;

    size_t D;
    std::vector<size_t> n_list{1, 1};
    std::vector<size_t> n_diff_list{1, 2};
    std::vector<size_t> D_list{4, 11}; // P_{n+n_diff} - P_{n}
    std::vector<size_t> sort_permutation{0, 1};

    bool apply_sort{true};

    bool found{false};
    while (!found)
    {
        if (apply_sort)
        {
            sort_permutation = uf::sortPermutation(D_list);
            uf::applySortPermutation(n_diff_list, sort_permutation);
            uf::applySortPermutation(n_list, sort_permutation);
            uf::applySortPermutation(D_list, sort_permutation);
        }

        size_t n{n_list[0]};
        size_t n_diff{n_diff_list[0]};
        ++n_list[0];
        D_list[0] += 3*n_diff; // Formula for D if n_diff remains constant and n increases by 1
        if (D_list[0] > D_list[1])
            apply_sort = true;
        else
            apply_sort = false;

        if (n_list[n_list.size()-1] > 1)
        {
            n_list.push_back(1);
            n_diff_list.push_back(n_list.size());
            D_list.push_back(pentagonal(n_list.size()) - 1);
            apply_sort = true;
            std::cout << D_list[0] << "\n";
        }

        size_t Pa{pentagonal(n)};
        size_t Pb{pentagonal(n + n_diff)};

        D = Pb - Pa;

        // std::cout << D << "\n";
        if (isPentagonal(D) && isPentagonal(Pb + Pa))
        {
            std::cout << "a: " << n << ", b:" << n + n_diff << "\n";
            std::cout << "Pa: " << Pa << ", Pb: " << Pb << "\n";
            std::cout << D << "\n";
            found = true;
        }
    }

    return 0;
}