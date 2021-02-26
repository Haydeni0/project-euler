/* 
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?
*/

#include "UsefulFunctions.h"

class RightAngledTriangle
{
private:
    std::vector<int> m_sides;
    bool m_isValidTriangle;

public:
    RightAngledTriangle(int a, int b, int c) : m_sides{a, b, c}, m_isValidTriangle{m_sides[0] * m_sides[0] + m_sides[1] * m_sides[1] == m_sides[2] * m_sides[2]}
    { // Given 3 sides
        // Always store the side lengths in order
        std::sort(m_sides.begin(), m_sides.end());
    }

    RightAngledTriangle(int a, int b) : RightAngledTriangle(a, b, std::lround(sqrt(a * a + b * b)))
    { // Given two sides (but not the hypotenuse)
    }

    std::string getSides()
    {
        return "{" + std::to_string(m_sides[0]) + ", " +
               std::to_string(m_sides[1]) + ", " + std::to_string(m_sides[2]) + "}";
    }

    bool isValid()
    {
        return m_isValidTriangle;
    }

    bool operator==(RightAngledTriangle rat) const
    {
        return (m_sides == rat.m_sides);
    }

    int perimeter()
    {
        return uf::vectorSum(m_sides);
    }
};

int main()
{

    int max_perimeter{500};

    int best_p{0};
    int max_solutions{0};
    for (int p{1}; p <= max_perimeter; p++)
    {
        std::vector<RightAngledTriangle> solution_list;
        for (int b{1}; b < p; ++b)
        {
            for (int a{1}; a <= b; ++a)
            {
                // std::cout << sqrt(p * p - 2 * a * a);
                RightAngledTriangle rat(a, b);
                if (rat.isValid())
                {
                    if ((rat.perimeter() == p) && !uf::inVector(rat, solution_list))
                        solution_list.push_back(rat);
                }
            }
        }
        if (solution_list.size() > max_solutions)
        {
            best_p = p;
            max_solutions = solution_list.size();
        }
    }

    std::cout << best_p;

    return 0;
}