/* 

*/

#include "UsefulFunctions.h"

int main()
{
    auto quadraticPrime = [](int n, int a, int b) {
        return n * n + a * n + b;
    };

    int max_consecutive{0};
    int best_a;
    int best_b;

    for (int a{-999}; a < 1000; ++a)
    {
        for (int b(-1000); b <= 1000; ++b)
        {
            int n{0};
            while (uf::isPrime(quadraticPrime(n, a, b)))
            {
                if (n > max_consecutive)
                {
                    max_consecutive = n;
                    best_a = a;
                    best_b = b;
                }
                ++n;
            }
        }
    }

    std::cout << "(n,a,b) : (" << max_consecutive << "," << best_a << "," << best_b << ")" << "\n";
    std::cout << "a*b = " << best_a*best_b;

    return 0;
}