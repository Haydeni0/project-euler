#ifndef VECTORFLOAT_H
#define VECTORFLOAT_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

// Do something more standard than this maybe?
#define DEFAULT_FLOAT_SIGFIGS 17;
#define DEFAULT_DIV_SIGFIGS 20;

// A decimal floating point number.
class VectorFloat
{
protected:
    // Make private, so there aren't any formatting issues with m_mantissa
    //      such as adding zeros to the end which can break things if not caught.
    std::vector<short> m_mantissa;
    int m_exponent;
    bool m_sign; // True:positive, False:negative.

    void checkDigitLimits();
    void trimZeros();
    void set_zero();
    VectorFloat &add_VF(const VectorFloat &add_num);
    VectorFloat &subtract_VF(const VectorFloat &add_num, bool flip_signs = false);

public:
    // Static class parameter for the number of sigfigs when dividing
    static int s_div_sigfigs;
    static int s_float_sigfigs;
    template <class T>
    VectorFloat(T input_num)
    {
        set(input_num);
    }
    VectorFloat(std::vector<short> input_mantissa, int input_exponent = 0, bool input_sign = true)
    {
        set(input_mantissa, input_exponent, input_sign);
    }
    VectorFloat()
        : m_mantissa{0}, m_exponent{0}, m_sign{true}
    {
    }

    VectorFloat &set(std::vector<short> input_mantissa, int input_exponent = 0, bool input_sign = true);
    VectorFloat &round(int sig_figs);

    template <class T = double>
    VectorFloat &set(T input_num, typename std::enable_if<std::is_floating_point_v<T>>::type * = 0)
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
        for (int j{0}; j < VectorFloat::s_float_sigfigs + 1; ++j)
        {
            m_mantissa.push_back(static_cast<short>(input_num));
            input_num -= m_mantissa[j];
            input_num *= 10;
        }
        round(VectorFloat::s_float_sigfigs);
        return *this;
    }

    template <class T = int>
    VectorFloat &set(T input_num, typename std::enable_if<std::is_integral_v<T>>::type * = 0)
    {
        if (input_num < 0)
        {
            m_sign = false;
            input_num *= -1;
        }
        else
            m_sign = true;

        if (input_num == 0)
            set_zero();
        else if (input_num >= 1) // Find exponent by logging and dropping the fractional part
            m_exponent = static_cast<int>(log10(input_num));
        else
            m_exponent = static_cast<int>(log10(input_num) - 1);

        // input_num *= pow(10, -m_exponent);

        for (int j{0}; j < m_exponent + 1; ++j)
        {
            int highest_exp{static_cast<int>(input_num * pow(10, -m_exponent + j))};
            m_mantissa.push_back(static_cast<short>(highest_exp));
            input_num -= static_cast<int>(highest_exp * pow(10, m_exponent - j));
        }
        return *this;
    }

    // Const access functions
    int size() const;
    double get_dbl() const;
    std::string get_str() const;
    bool get_sign() const;
    int get_exponent() const;
    std::vector<short> get_mantissa() const;

    // Member operator functions
    VectorFloat &operator<<(int shift_amount);
    VectorFloat &operator>>(int shift_amount);

    // Friend functions
    friend VectorFloat operator+(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat operator-(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat operator-(const VectorFloat &VF);
    friend VectorFloat operator*(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat operator/(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat &operator+=(VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat &operator-=(VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat &operator*=(VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat &operator/=(VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator==(const VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator!=(const VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator>(const VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator<(const VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator>=(const VectorFloat &VF1, const VectorFloat &VF2);
    friend bool operator<=(const VectorFloat &VF1, const VectorFloat &VF2);
    friend std::ostream &operator<<(std::ostream &out, const VectorFloat &VF);

    // operator assist functions
    friend VectorFloat add_same_sign(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat add_diff_sign(const VectorFloat &VF1, const VectorFloat &VF2);
    friend VectorFloat mult_num(const VectorFloat &VF, const short num, const int exponent);
    friend VectorFloat abs(const VectorFloat &VF);
};

#endif