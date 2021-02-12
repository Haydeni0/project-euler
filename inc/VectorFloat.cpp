#include "VectorFloat.h"
#include "UsefulFunctions.h"

int VectorFloat::s_div_sigfigs = DEFAULT_DIV_SIGFIGS;

// ###PRIVATE:###
void VectorFloat::checkDigitLimits()
{
    for (int j{static_cast<int>(m_mantissa.size()) - 1}; j >= 0; --j)
    {
        if (m_mantissa[j] > 9)
        {
            int tens{m_mantissa[j] / 10}; // Integer division
            int unit{m_mantissa[j] - 10 * tens};
            if ((j - 1) < 0)
            {
                m_mantissa.insert(m_mantissa.begin(), 0);
                m_exponent += 1;
                j += 1;
            }
            m_mantissa[j - 1] += tens;
            m_mantissa[j] = unit;
        }
        // Pretty sure doesnt work atm for negative values
        if (m_mantissa[j] < 0)
        {
            std::cout << "SHOULDNT BE ABLE TO PRODUCE NEGATIVE VALUES"
                      << "\n";
        }
    }
    trimZeros();
}

void VectorFloat::trimZeros()
{
    // Trim end zeros
    int end_zeros{0};
    for (int j{size() - 1}; j >= 0; --j)
    {
        if (m_mantissa[j] == 0)
            end_zeros += 1;
        else
            break;
    }
    if (end_zeros == size())
    { // If there are only zeros, set to the zero VF and return
        set_zero();
        return;
    }
    else if (end_zeros > 0)
        m_mantissa.resize(m_mantissa.size() - end_zeros);

    // Trim start zeros
    int start_zeros{0};
    while (m_mantissa[start_zeros] == 0)
        ++start_zeros;
    if (start_zeros > 0)
    {
        m_mantissa.erase(m_mantissa.begin(), m_mantissa.begin() + start_zeros);
        m_exponent -= start_zeros;
    }
}

void VectorFloat::set_zero()
{ // Set this VF to the zero VF
    m_mantissa = {0};
    m_sign = true;
    m_exponent = 0;
}

// ###PUBLIC:###

VectorFloat &VectorFloat::set(double input_num, int sig_figs)
{
    // Convert a double to vector float form
    if (input_num < 0)
    {
        m_sign = false;
        input_num *= -1;
    }
    else
        m_sign = true;

    if (input_num >= 1) // Find exponent by logging and dropping the fractional part
        m_exponent = static_cast<int>(log10(input_num));
    else if (input_num == 0)
    {
        m_exponent = 0;
        m_mantissa = {0};
    }
    else
        m_exponent = static_cast<int>(log10(input_num) - 1);

    input_num *= pow(10, -m_exponent);
    for (int j{0}; j < sig_figs + 1; ++j)
    {
        m_mantissa.push_back(static_cast<short>(input_num));
        input_num -= m_mantissa[j];
        input_num *= 10;
    }
    round(sig_figs);
    return *this;
}

VectorFloat &VectorFloat::set(std::vector<short> input_mantissa, int input_exponent, bool input_sign)
{
    // Set explicitly the mantissa exponent and sign of this number

    // Verify that all elements in m_mantissa are positive
    for (short elem : input_mantissa)
    {
        if (elem < 0)
        {
            std::cout << "Expected input to have positive vector elements"
                      << "\n";
            throw;
        }
    }
    m_mantissa = input_mantissa;
    m_exponent = input_exponent;
    m_sign = input_sign;
    checkDigitLimits();
    return *this;
}

VectorFloat &VectorFloat::round(int sig_figs)
{
    uf::assertMsg(sig_figs > 0, "Expected significant figures greater than 0");

    // Rounds this number to [sig_figs] significant figures
    if (m_mantissa.size() < sig_figs)
        return *this;
    else
    {
        if (m_mantissa[sig_figs] >= 5)
            m_mantissa[sig_figs - 1] += 1;
        m_mantissa.resize(sig_figs);
        checkDigitLimits();
        return *this;
    }
}

// Const access functions
int VectorFloat::size() const
{
    // Returns the number of significant digits for this VF.
    // Eg. the size of 1'402'000 in VF form is 4.
    return static_cast<int>(m_mantissa.size());
}

double VectorFloat::get_dbl() const
{
    // Returns a double (can result in loss of precision when converting to double)
    double out_dbl{0};
    for (int j{0}; j < m_mantissa.size(); ++j)
    {
        out_dbl += m_mantissa[j] * pow(10, m_exponent - j);
    }
    if (!m_sign)
        out_dbl *= -1;

    return out_dbl;
}

std::string VectorFloat::get_str() const
{
    std::string str;
    if (!m_sign)
        str += '-';
    if (m_exponent >= 0)
    {
        int j{0};
        while (j < m_mantissa.size())
        {
            // Append the number to the string from left to right
            str += uf::short2string(m_mantissa[j]);
            // Add a decimal point if we go into the negative exponents
            if ((j == m_exponent) && (j + 1 != m_mantissa.size()))
                str += ".";
            ++j;
        }
        while (j <= m_exponent)
        { // Add trailing zeros for numbers like 2300 which have size 2.
            str += "0";
            ++j;
        }
    }
    else
    {
        str += "0.";
        int j{0};
        while (j > m_exponent + 1)
        {
            str += "0";
            --j;
        }
        j = 0;
        while (j < m_mantissa.size())
        {
            str += uf::short2string(m_mantissa[j]);
            ++j;
        }
    }
    return str;
}

// ###FRIEND FUNCTIONS:### (not inside the class)
// Overloaded operators
VectorFloat operator+(const VectorFloat &VF1, const VectorFloat &VF2)
{
    if (VF1.m_sign == VF2.m_sign)
        return add_same_sign(VF1, VF2);
    else
        return add_diff_sign(VF1, VF2);
}
VectorFloat operator-(const VectorFloat &VF1, const VectorFloat &VF2)
{
    return (VF1 + (-VF2));
}
VectorFloat operator-(const VectorFloat &VF)
{
    VectorFloat returnVF{VF};
    returnVF.m_sign = !returnVF.m_sign;
    return returnVF;
}
VectorFloat operator*(const VectorFloat &VF1, const VectorFloat &VF2)
{
    VectorFloat VF_temp{0};

    for (int j{VF2.size() - 1}; j >= 0; --j)
    {
        int current_exponent{VF2.m_exponent - j};
        VF_temp += mult_num(VF1, VF2.m_mantissa[j], current_exponent);
    }
    VF_temp.m_sign = (VF1.m_sign == VF2.m_sign);
    return VF_temp;
}
VectorFloat operator/(const VectorFloat &dividend, const VectorFloat &divisor)
{ // Division function
    uf::assertMsg(divisor != VectorFloat(0), "Divide by zero error");
    // Quick version using long long

    // slower version using rem/mod for VF
    VectorFloat quotient{0};
    quotient.m_mantissa.resize(VectorFloat::s_div_sigfigs + 1);
    quotient.m_exponent = dividend.m_exponent - divisor.m_exponent;

    VectorFloat temp_dividend{dividend.m_mantissa, divisor.m_exponent};
    VectorFloat temp_divisor{abs(divisor)};
    int quotient_idx{0};
    while (quotient_idx < quotient.size())
    {
        while (temp_divisor > temp_dividend)
        {
            ++temp_dividend.m_exponent;
            quotient.m_mantissa[quotient_idx] = 0;
            ++quotient_idx;
        }

        do
        {
            temp_divisor += abs(divisor);
            ++quotient.m_mantissa[quotient_idx];
        } while ((temp_divisor) < temp_dividend);
        temp_divisor -= abs(divisor);

        temp_dividend -= temp_divisor;
        temp_dividend.m_exponent += 1;
        // temp_dividend.trimZeros();
        temp_divisor = abs(divisor);

        // If there is no remainder, stop.
        if (temp_dividend.m_mantissa[0] == 0)
            break;

        ++quotient_idx;
    }
    quotient.trimZeros();
    quotient.round(VectorFloat::s_div_sigfigs);

    return quotient;
}
VectorFloat &operator+=(VectorFloat &VF1, const VectorFloat &VF2)
{
    VF1 = VF1 + VF2;
    return VF1;
}
VectorFloat &operator-=(VectorFloat &VF1, const VectorFloat &VF2)
{
    VF1 = VF1 - VF2;
    return VF1;
}
VectorFloat &operator*=(VectorFloat &VF1, const VectorFloat &VF2)
{
    VF1 = VF1 * VF2;
    return VF1;
}
VectorFloat &operator/=(VectorFloat &VF1, const VectorFloat &VF2)
{
    VF1 = VF1 / VF2;
    return VF1;
}
bool operator==(const VectorFloat &VF1, const VectorFloat &VF2)
{
    if ((VF1.m_sign == VF2.m_sign) &&
        (VF1.m_exponent == VF2.m_exponent) &&
        (VF1.m_mantissa == VF2.m_mantissa))
        return true;
    else
        return false;
}
bool operator!=(const VectorFloat &VF1, const VectorFloat &VF2)
{
    return !(VF1 == VF2);
}
bool operator>(const VectorFloat &VF1, const VectorFloat &VF2)
{
    if ((VF1.m_sign && VF2.m_sign))
    {
        if (VF1.m_exponent > VF2.m_exponent)
            return true;
        else if (VF1.m_exponent < VF2.m_exponent)
            return false;
        else
        {
            int min_size{std::min(VF1.size(), VF2.size())};
            for (int j{0}; j < min_size; ++j)
            { // If digits are different then the larger one will be obvious
                if (VF1.m_mantissa[j] > VF2.m_mantissa[j])
                    return true;
                else if (VF1.m_mantissa[j] < VF2.m_mantissa[j])
                    return false;
            }
            // If all the digits so far are equal, then assuming that there are no
            // end zeros (which there shouldn't be) then the more sizeable one
            // is greater.
            if (VF1.size() > VF2.size())
                return true;
            else
                return false;
        }
    }
    else if (VF1.m_sign != VF2.m_sign)
    {
        if (VF1.m_sign)
            return true;
        else
            return false;
    }
    else
    {
        if (VF1.m_exponent < VF2.m_exponent)
            return true;
        else if (VF1.m_exponent > VF2.m_exponent)
            return false;
        else
        {
            int min_size{std::min(VF1.size(), VF2.size())};
            for (int j{0}; j < min_size; ++j)
            {
                if (VF1.m_mantissa[j] < VF2.m_mantissa[j])
                    return true;
                else if (VF1.m_mantissa[j] > VF2.m_mantissa[j])
                    return false;
            }
            // If all the digits so far are equal, then assuming that there are no
            // end zeros (which there shouldn't be) then the more sizeable one
            // is greater.
            if (VF1.size() < VF2.size())
                return true;
            else
                return false;
        }
    }
}
bool operator<(const VectorFloat &VF1, const VectorFloat &VF2)
{
    return !(VF1 >= VF2);
}
bool operator>=(const VectorFloat &VF1, const VectorFloat &VF2)
{
    return ((VF1 == VF2) || (VF1 > VF2));
}
bool operator<=(const VectorFloat &VF1, const VectorFloat &VF2)
{
    return ((VF1 == VF2) || (VF1 < VF2));
}
std::ostream &operator<<(std::ostream &out, const VectorFloat &VF)
{ // Overload the << operator so we can easily do - std::cout << VF;
    out << VF.get_str();
    return out;
}

// Operator assist functions
VectorFloat add_same_sign(const VectorFloat &VF1, const VectorFloat &VF2)
{
    VectorFloat VF_temp{VF1};
    // Function to add two VFs of the same sign
    uf::assertMsg(VF_temp.m_sign == VF2.m_sign, "Expected numbers of the same sign.");
    if (VF2.m_exponent > VF_temp.m_exponent)
    { // When VF2 has higher exponent than VF1
        // VF2 : {12321.456001}
        // VF1     : {00221.566000}
        while (VF_temp.m_exponent < VF2.m_exponent)
        {
            VF_temp.m_mantissa.insert(VF_temp.m_mantissa.begin(), 0);
            ++VF_temp.m_exponent;
        }
        if (VF_temp.size() < VF2.size())
            VF_temp.m_mantissa.resize(VF2.size());
        for (int j{0}; j < VF2.m_mantissa.size(); ++j)
        {
            VF_temp.m_mantissa[j] += VF2.m_mantissa[j];
        }
    }
    else
    { // When VF2 has an equal or lower exponent than VF1
        // VF2 : {1.456001}
        // VF1     : {221.566000}
        int exp_diff{VF_temp.m_exponent - VF2.m_exponent};
        if ((VF2.size() + exp_diff) > VF_temp.size())
            VF_temp.m_mantissa.resize(VF2.size() + exp_diff);
        for (int j{0}; j < VF2.m_mantissa.size(); ++j)
        {
            VF_temp.m_mantissa[j + exp_diff] += VF2.m_mantissa[j];
        }
    }
    VF_temp.checkDigitLimits();

    return VF_temp;
}
VectorFloat add_diff_sign(const VectorFloat &VF1, const VectorFloat &VF2)
{
    // Function to add VF1 to VF2 when they have different sign
    uf::assertMsg(VF1.m_sign != VF2.m_sign, "Expected numbers with different sign");

    // Make sure that VF1 is positive, so we can do VF1 - VF2
    if (VF1.m_sign == false)
        return add_diff_sign(VF2, VF1);
    // Make sure that |VF1| > |VF2| so that subtraction is easy
    if (VF1 < (-VF2))
        return -add_diff_sign(-VF2, -VF1);

    // Proceed now that we know VF1 > 0, VF2 < 0, and VF1 + VF2 > 0
    VectorFloat VF_temp{VF1};

    // Find the number of decimal places each VF has.
    // Eg. 43.2 has 1 dp, 5 has 0 dp, 2300 has -2 dp.
    int dec_places_1{VF_temp.size() - VF_temp.m_exponent - 1};
    int dec_places_2{VF2.size() - VF2.m_exponent - 1};
    // If necessary resize VF_temp so that the decimal places can be indexed
    if (dec_places_2 > dec_places_1)
        VF_temp.m_mantissa.resize(VF_temp.size() + (dec_places_2 - dec_places_1));
    for (int VF2_idx{VF2.size() - 1}; VF2_idx >= 0; --VF2_idx)
    {
        int current_exponent{VF2.m_exponent - VF2_idx};
        int VF_temp_idx{VF_temp.m_exponent - current_exponent};
        if (VF_temp.m_mantissa[VF_temp_idx] >= VF2.m_mantissa[VF2_idx])
            VF_temp.m_mantissa[VF_temp_idx] -= VF2.m_mantissa[VF2_idx];
        else
        { // If subtracting the current digits will result in a negative value,
            //      borrow a ten from the next higher digit. This will always work as |VF1| > |VF2|
            VF_temp.m_mantissa[VF_temp_idx - 1] -= 1;
            VF_temp.m_mantissa[VF_temp_idx] += 10;
            VF_temp.m_mantissa[VF_temp_idx] -= VF2.m_mantissa[VF2_idx];
        }
    }

    VF_temp.trimZeros();
    return VF_temp;
}
VectorFloat mult_num(const VectorFloat &VF, const short num, const int exponent)
{
    // Function that multiplies the input VF by num (num > 0).
    // Modifies VF_out directly.
    uf::assertMsg(num > 0, "Expected num > 0");

    VectorFloat VF_temp{VF};
    VF_temp.m_exponent += exponent;
    for (int j{VF_temp.size() - 1}; j >= 0; --j)
    {
        VF_temp.m_mantissa[j] *= num;
    }
    VF_temp.checkDigitLimits();

    return VF_temp;
}
// std::vector<short> div_subtract(const std::vector<short> divisor,
//  const std::vector<short> dividend)
// {

// }
// Additional
VectorFloat abs(const VectorFloat &VF)
{ // Return the absolute value
    if (VF.m_sign == true)
        return VF;
    else
        return -VF;
}
