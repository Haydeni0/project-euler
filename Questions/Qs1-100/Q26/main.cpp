/* 
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

#include "UsefulFunctions.h"

int cycleLength(const VectorFloat VF)
{ // Returns the cycle length of a recurring number. Doesn't really work for values such as 0.2, thinks its a cycle length of 1.
    std::vector<short> mantissa{VF.get_mantissa()};
    for (int start_idx{0}; start_idx < VF.size(); ++start_idx)
    {
        for (int end_idx{start_idx}; end_idx < VF.size(); ++end_idx)
        {
            std::vector<short> cycle{mantissa.begin() + start_idx, mantissa.begin() + end_idx + 1};
            int mantissa_idx{0};
            while (mantissa_idx < VF.size() && mantissa[mantissa_idx] != cycle[0])
                mantissa_idx++;
            int cycle_idx{0};
            bool is_recursive{true};
            while (mantissa_idx < VF.size() - 1)
            {
                if (mantissa[mantissa_idx] == cycle[cycle_idx])
                {
                    cycle_idx++;
                    mantissa_idx++;
                    if (cycle_idx == cycle.size())
                        cycle_idx = 0;
                }
                else
                {
                    is_recursive = false;
                    break;
                }
            }
            // If it makes it this far, then cycle is a recursive cycle
            if (is_recursive && (end_idx < (VF.size() - 2)))
                return cycle.size();
        }
    }
    // If it makes it this far, then there is no recursive cycle
    return 0;
}

int main()
{
    int num_sigfigs = 1000;
    VectorFloat::s_div_sigfigs = num_sigfigs;
    int biggest_cycle{0};
    for (VectorFloat d{3}; d < 1000; d += 2)
    {
        VectorFloat result{1/d};
        int cycle_length{cycleLength(result)};

        if (cycle_length > biggest_cycle)
        {
            biggest_cycle = cycle_length;
            std::cout << "1/"<< d << " has cycle Length: " << cycle_length << "\n";
        }
    }

    std::cout << cycleLength(1 / VectorFloat(75)) << "\n";

    return 0;
}