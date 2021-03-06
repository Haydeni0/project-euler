/* 
Consider all integer combinations of ab for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

2^2=4, 2^3=8, 2^4=16, 2^5=32
3^2=9, 3^3=27, 3^4=81, 3^5=243
4^2=16, 4^3=64, 4^4=256, 4^5=1024
5^2=25, 5^3=125, 5^4=625, 5^5=3125
If they are then placed in numerical order, with any repeats removed, we get the following sequence of 15 distinct terms:

4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

How many distinct terms are in the sequence generated by ab for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?
*/

#include "UsefulFunctions.h"

class PrimeFactorisation
{
public:
    std::vector<int> m_prime_list;
    std::vector<int> m_prime_count;

    PrimeFactorisation(int num)
    {
        auto [prime_list, prime_count] = uf::findPrimeFactors(num);
        m_prime_list = prime_list;
        m_prime_count = prime_count;
    }

    PrimeFactorisation(std::vector<int> prime_list, std::vector<int> prime_count)
        : m_prime_list{prime_list}, m_prime_count{prime_count}
    {
    }

    PrimeFactorisation operator^(const int exponent)
    {
        PrimeFactorisation temp_PF{*this};
        for (int j{0}; j < temp_PF.m_prime_count.size(); ++j)
        {
            temp_PF.m_prime_count[j] *= exponent;
        }
        return temp_PF;
    }
    bool operator==(const PrimeFactorisation PF) const
    {
        if ((PF.m_prime_count == (this->m_prime_count)) && (PF.m_prime_list == (this->m_prime_list)))
            return true;
        else
            return false;
    }
};

std::vector<PrimeFactorisation> unique(std::vector<PrimeFactorisation> PF_list)
{
    std::vector<PrimeFactorisation> tempPF_list;
    for (int j{0}; j < PF_list.size(); ++j)
    {
        if (!uf::inVector(PF_list[j], tempPF_list))
            tempPF_list.push_back(PF_list[j]);
    }
    return tempPF_list;
}

int main()
{
    // Brute force: make a vector of all the prime factorisations of a^b, then remove duplicates

    int max_num{100};

    std::vector<PrimeFactorisation> PF_list;
    for (int a{2}; a <= max_num; ++a)
    {
        PrimeFactorisation a_PF{a};
        for (int b{2}; b <= max_num; ++b)
        {
            PF_list.push_back(a_PF ^ b);
        }
    }

    std::vector<PrimeFactorisation> newPF_list{unique(PF_list)};

    std::cout << newPF_list.size();

    // PrimeFactorisation a{37};
    // PrimeFactorisation b{37};

    // std::cout << (a == b);

    return 0;
}