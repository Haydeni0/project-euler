#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H

#include <tuple>
#include <math.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <Eigen/Dense>
#include "VectorFloat.h"

namespace UsefulFunctions
{

    template <typename T>
    std::vector<T> findFactors(T n, bool find_proper = 0);

    std::tuple<std::vector<int>, std::vector<int>> findPrimeFactors(long long n);

    std::ifstream loadFile(std::string filepath);

    void veryLongMultiply(std::vector<short> &digits_out, long long multiplier);

    void veryLongAdd(std::vector<short> &digits_out, const std::vector<short> &num_add);

    template <typename T>
    void printBackwardsDigits(const std::vector<T> &digits);

    void assertMsg(bool condition, std::string errMsg);

    void printVector(const std::vector<int> &vec);

    std::string boldText(std::string str);

    template <typename T>
    long long sumVector(const std::vector<T> &vec);

    std::string short2string(const short sh);
} // namespace UsefulFunctions

namespace uf = UsefulFunctions;

#endif