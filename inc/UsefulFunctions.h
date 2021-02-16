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
    std::vector<int> findFactors(int n, bool find_proper = 0);

    std::tuple<std::vector<int>, std::vector<int>> findPrimeFactors(long long n);

    bool isPrime(int n);

    std::ifstream loadFile(std::string filepath);

    void veryLongMultiply(std::vector<short> &digits_out, long long multiplier);

    void veryLongAdd(std::vector<short> &digits_out, const std::vector<short> &num_add);

    void assertMsg(bool condition, std::string errMsg);

    std::string boldText(std::string str);

    std::string short2string(const short sh);

    // TEMPLATES
    template <class T>
    void printVector(const std::vector<T> &vec)
    {
        // Prints a vector. Eg. {1,2,3,4} prints: 1, 2, 3, 4, \n
        for (int j{0}; j < vec.size(); ++j)
            std::cout << vec.at(j) << ", ";
        std::cout << "\n";
    }
    template <class T>
    bool inVector(const T find_var, const std::vector<T> &vec)
    { // If find_var is an element of vec, return true.
        for (auto elem : vec)
        {
            if (find_var == elem)
                return true;
        }
        return false;
    }
    template <class T>
    long long sumVector(const std::vector<T> &vec)
    {
        // Sums a vector. Make sure the input is some sort of number.
        long long total{0};
        for (int j{0}; j < vec.size(); ++j)
            total += vec[j];
        return total;
    }
    template <class T>
    long long multVector(const std::vector<T> &vec)
    {
        // Sums a vector. Make sure the input is some sort of number.
        long long total{0};
        for (int j{0}; j < vec.size(); ++j)
            total *= vec[j];
        return total;
    }
    
} // namespace UsefulFunctions

namespace uf = UsefulFunctions;

#endif