/* 
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/

#include "UsefulFunctions.h"
#include "VectorFloat.h"

class VectorFloatOpen : public VectorFloat
{
public:
    VectorFloatOpen &trimFront(int num_trim)
    { // Function to trim the front of the VF. Consider adding this to VectorFloat.h .
        // Eg. for num_trim = 3, the VF 12345678 turns into 678.

        uf::assertMsg(num_trim > 0, "num_trim must be greater than 0");

        // Convert all VFs to 'integer VFs' (VFs that dont have any decimal component)
        if (m_exponent < 0)
        {
            set_zero();
            return *this;
        }
        if (m_mantissa.size() > m_exponent + 1)
            m_mantissa = std::vector<short>(m_mantissa.begin(), m_mantissa.begin() + m_exponent + 1);

        // Trim the front if necessary
        if (m_exponent + 1 > num_trim)
        {
            int num_remove{m_exponent - num_trim + 1};
            m_exponent -= num_remove;
            if (num_remove > m_mantissa.size())
            {
                set_zero();
                return *this;
            }
            else
            {
                m_mantissa = std::vector<short>(m_mantissa.begin() + num_remove, m_mantissa.end());
            }
        }

        return *this;
    }
};

int main()
{
    VectorFloatOpen VF{0};

    for (int n{1}; n <= 1000; ++n)
    {
        VectorFloatOpen nn{n};
        for (int j{2}; j <= n; ++j)
        {
            nn *= n;
            nn.trimFront(10);
        }
        VF += nn;
        VF.trimFront(10);
    }

    std::cout << VF;
    return 0;
}