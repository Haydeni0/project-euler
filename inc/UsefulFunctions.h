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
#include <bitset>
#include <Eigen/Dense>

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

    int nextPrime(int n);

    // CLASSES
    class UnorderedDigitID
    {
    public:
        // Stores the number of each digit in this ordered list:
        // Eg. for an integer 14522999, m_digit_count = {0,1,2,0,1,1,0,0,0,3}
        std::vector<size_t> m_digit_count{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        UnorderedDigitID(int n)
        {
            std::vector<int> digit_list{int2digits(n)};
            for (auto elem : digit_list)
            {
                m_digit_count[elem]++;
            }
        }
        bool operator==(const UnorderedDigitID &UD) const
        {
            return m_digit_count == UD.m_digit_count;
        }
    };

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
    template <class T>
    std::vector<size_t> sortPermutation(const std::vector<T> &vec, bool ascending = true)
    { // Creates a permutation p that sorts vec into ascending or descending order
        std::vector<std::size_t> p(vec.size());
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(),
                  [&ascending, &vec](std::size_t i, std::size_t j) {
                      if (ascending)
                          return vec[i] < vec[j];
                      else
                          return vec[i] > vec[j];
                  });
        return p;
    }
    template <class T>
    void applySortPermutation(std::vector<T> &vec, const std::vector<size_t> &p)
    { // Code from https://stackoverflow.com/questions/17074324/how-can-i-sort-two-vectors-in-the-same-way-with-criteria-that-uses-only-one-of
        // Applies the sort permutation p to vec
        assertMsg(vectorMax(p) < vec.size(), "Sort permutation is out of index of the vector");
        assertMsg(p.size() == vec.size(), "Sort permutation is not the same size as the vector");
        std::vector<bool> done(vec.size());
        for (std::size_t i = 0; i < vec.size(); ++i)
        {
            if (done[i])
            {
                continue;
            }
            done[i] = true;
            std::size_t prev_j = i;
            std::size_t j = p[i];
            while (i != j)
            {
                std::swap(vec[prev_j], vec[j]);
                done[j] = true;
                prev_j = j;
                j = p[j];
            }
        }
    }
    template <class T>
    bool isEven(T n, typename std::enable_if<std::is_integral_v<T>>::type * = 0)
    {
        return (n % 2 == 0);
    }
    template <class T>
    bool isOdd(T n, typename std::enable_if<std::is_integral_v<T>>::type * = 0)
    {
        return (n % 2 != 0);
    }

} // namespace UsefulFunctions

namespace uf = UsefulFunctions;

#endif