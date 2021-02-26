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

    std::vector<int> int2digits(int x);

    int digits2int(const std::vector<int> &vec);

    int numDigits(int n);

    int factorial(int n);

    bool isPandigital(const std::vector<int> &vec, int max_digit = 9);

    // TEMPLATES
    // It's a lot easier to include function templates directly in this header file, as they can be initialised by the compiler for whichever variable type needed.
    // If included in a separate cpp file, then they would need to be manually initialised at the bottom for each necessary datatype and function.
    template <class T>
    void printVector(const std::vector<T> &vec)
    {
        // Prints a vector. Eg. {1,2,3,4} prints: {1, 2, 3, 4} \n
        if (vec.size() == 0)
        {
            std::cout << "{}";
            return;
        }
        std::cout << "{";
        for (int j{0}; j < vec.size() - 1; ++j)
            std::cout << vec[j] << ", ";
        std::cout << vec[vec.size() - 1] << "}\n";
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
    std::vector<int> findInVector(const T find_var, const std::vector<T> &vec)
    { // Return indices of the elements of vec that are equal to find_var
        std::vector<int> idx_list;
        for (int j{0}; j < vec.size(); j++)
        {
            if (find_var == vec[j])
                idx_list.push_back(j);
        }
        return idx_list;
    }
    template <class T>
    long long vectorSum(const std::vector<T> &vec)
    {
        // Sums a vector. Make sure the input is some sort of number.
        long long total{0};
        for (int j{0}; j < vec.size(); ++j)
            total += vec[j];
        return total;
    }
    template <class T>
    long long vectorProd(const std::vector<T> &vec)
    {
        // Product of elements in the vector. Make sure the input is some sort of number.
        long long total{1};
        for (int j{0}; j < vec.size(); ++j)
            total *= vec[j];
        return total;
    }
    template <class T>
    long long vectorMean(const std::vector<T> &vec)
    {
        // Mean of elements in a vector. Make sure the input is some sort of number.

        return vectorSum(vec) / vec.size();
    }
    template <class T>
    int vectorMinIndex(const std::vector<T> &vec)
    {
        // Return the index of the minimum value in the vector
        // If the minimum is not unique, return the first of those.
        T min{vec[0]};
        int min_idx{0};
        for (int j{1}; j < vec.size(); ++j)
        {
            if (vec[j] < min)
            {
                min = vec[j];
                min_idx = j;
            }
        }
        return min_idx;
    }
    template <class T>
    T vectorMin(const std::vector<T> &vec)
    {
        return vec[vectorMinIndex(vec)];
    }
    template <class T>
    int vectorMaxIndex(const std::vector<T> &vec)
    {
        // Return the index of the maximum value in the vector
        // If the maximum is not unique, return the first of those.
        T max{vec[0]};
        int max_idx{0};
        for (int j{1}; j < vec.size(); ++j)
        {
            if (vec[j] > max)
            {
                max = vec[j];
                max_idx = j;
            }
        }
        return max_idx;
    }
    template <class T>
    T vectorMax(const std::vector<T> &vec)
    {
        return vec[vectorMaxIndex(vec)];
    }
} // namespace UsefulFunctions

namespace uf = UsefulFunctions;

#endif