/* 
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

#include "UsefulFunctions.h"

class Fraction
{
public:
    int m_numerator;
    int m_denominator;
    Fraction(int numerator = 1, int denominator = 1) : m_numerator{numerator}, m_denominator{denominator}
    {
        uf::assertMsg(denominator != 0, "Denominator must be non zero");
        cancelFrac();
    }

    double getDbl() const
    {
        return static_cast<double>(m_numerator) / m_denominator;
    }
    std::string getStr() const
    {
        return (std::to_string(m_numerator) + "/" + std::to_string(m_denominator));
    }
    void cancelFrac()
    {
        int gcd{std::gcd(m_numerator, m_denominator)};
        while (gcd != 1)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
            gcd = std::gcd(m_numerator, m_denominator);
        }
    }
    bool operator==(Fraction frac) const
    {
        return ((m_numerator == frac.m_numerator) && (m_denominator == frac.m_denominator));
    }
    void operator*=(const Fraction &frac)
    {
        m_numerator *= frac.m_numerator;
        m_denominator *= frac.m_denominator;
        cancelFrac();
    }
    Fraction operator*(const Fraction &frac)
    {
        Fraction temp_frac{*this};
        temp_frac *= frac;
        return temp_frac;
    }

};

int main()
{

    // Fraction frac{-2, -6};
    // std::cout << frac.getDbl() << "\n";
    // std::cout << frac.getStr() << "\n";

    std::vector<Fraction> curious_frac_list;
    for (int denominator{11}; denominator <= 99; denominator++)
    {
        for (int numerator{10}; numerator < denominator; numerator++)
        {
            // Skip trivial cases where zeros can be 'cancelled'
            if (numerator % 10 == 0 || denominator % 10 == 0)
                continue;
            Fraction frac{numerator, denominator};
            // Check if there are any repeated digits
            std::vector<int> numerator_digits{uf::int2digits(numerator)};
            std::vector<int> denominator_digits{uf::int2digits(denominator)};
            for (int j{0}; j < numerator_digits.size(); ++j)
            {
                std::vector<int> idx_list{uf::findInVector(numerator_digits[j], denominator_digits)};
                if (idx_list.size() != 0)
                {
                    std::vector<int> new_numerator_digits{numerator_digits};
                    std::vector<int> new_denominator_digits{denominator_digits};
                    new_numerator_digits.erase(new_numerator_digits.begin() + j);
                    new_denominator_digits.erase(new_denominator_digits.begin() + idx_list[0]); // Only takes into account the first digit
                    Fraction frac_cancelled{uf::digits2int(new_numerator_digits), uf::digits2int(new_denominator_digits)};
                    if (frac == frac_cancelled)
                        curious_frac_list.push_back(frac);
                }
            }
        }
    }

    Fraction frac_product{1,1};
    for (auto elem : curious_frac_list)
    {
        frac_product *= elem;
    }

    return 0;
}