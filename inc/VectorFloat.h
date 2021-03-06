#ifndef VECTORFLOAT_H
#define VECTORFLOAT_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

// Do something more standard than this maybe?
#define DEFAULT_SIG_FIGS 17
#define DEFAULT_DIV_SIGFIGS 20;

// A decimal floating point number.
class VectorFloat
{
private:
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

    VectorFloat(double input_num, int sig_figs = DEFAULT_SIG_FIGS)
    {
        set(input_num, sig_figs);
    }
    VectorFloat(std::vector<short> input_mantissa, int input_exponent = 0, bool input_sign = true)
    {
        set(input_mantissa, input_exponent, input_sign);
    }
    // Find a better way to repeat this for int, template maybe#?
    VectorFloat(int input_num)
    {
        set(input_num);
    }
    VectorFloat()
        : m_mantissa{0}, m_exponent{0}, m_sign{true}
    {
    }

    VectorFloat &set(double input_num, int sig_figs = DEFAULT_SIG_FIGS);
    VectorFloat &set(int input_num);
    VectorFloat &set(std::vector<short> input_mantissa, int input_exponent = 0, bool input_sign = true);
    VectorFloat &round(int sig_figs);

    // Const access functions
    int size() const;
    double get_dbl() const;
    std::string get_str() const;
    bool get_sign() const;
    int get_exponent() const;
    std::vector<short> get_mantissa() const;

    // Member operator functions
    VectorFloat& operator<<(int shift_amount);
    VectorFloat& operator>>(int shift_amount);

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