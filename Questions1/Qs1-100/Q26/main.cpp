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




void veryLongDivide(std::vector<short> &digits_out, long long divisor)
    {
        // A function that takes in an int vector representing the digits of a number in backwards order.
        // Eg. 3489 is represented as {9,8,4,3}.
        // Divides this number by the divisor.
        // Directly changes the vector 'digits_out' by reference.

        // Temporarily reverse the digits so we can push_back the 
        std::reverse(digits_out.begin(),digits_out.end());

        for (long j{0}; j < digits_out.size(); ++j)
        {
            digits_out[j] *= multiplier; // Multiply by the given multiplier
        }
        for (long j{0}; j < digits_out.size(); ++j)
        {
            if (digits_out[j] > 9)
            {
                int tens{digits_out[j] / 10}; // Integer division
                int unit{digits_out[j] - 10 * tens};
                if ((j + 1) >= digits_out.size())
                    digits_out.push_back(tens);
                else
                    digits_out[j + 1] += tens;
                digits_out[j] = unit;
            }
        }
    }

int main()
{
    


    return 0;
}