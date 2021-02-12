// Test program

#include "UsefulFunctions.h"
/* 
Things to do:
* Be able to add/mult/div/sub doubles to it
* Find a way to implicitly convert a double to VectorFloat when using a function
*   with VectorFloat input
* Make a double2VF(double dbl) function to convert dbl to VF
* Be able to round to decimal places as well as sig figs
* Optimise operators so they return somehow by reference? without breaking things
* Make more overloads of + - * / that take in a VF and a double and implicitly convert
* Overload operators << and >> as 'bitshift' which increases or decreases the exponent
* Make a constructor for int with a template or something?
* Make quick versions of + - * / using long long variables if the VF is small enough
* Instead of using the + operator inside +=, redo operator+= such that it does the same
*       as + but returns by reference rather than copying.
* Make unary operators like +=, -, member functions
* Overload ++ and -- operators
* 
*/

int main()
{
    double num1{1};
    double num2{3};
    VectorFloat VF1(num1, 10);
    VectorFloat VF2(num2, 10);

    std::cout << VF1.get_str() << "\n";
    std::cout << VF2.get_str() << "\n";

    VectorFloat::s_div_sigfigs = 20;

    std::cout << (VF1 / VF2) << "\n";

    return 0;
}
int main1()
{

    double num1{131};
    double num2{830};
    VectorFloat VF1(num1, 10);
    VectorFloat VF2(num2, 10);
    std::cout << (VF1 > VF2) << "\n";

    return 0;
}