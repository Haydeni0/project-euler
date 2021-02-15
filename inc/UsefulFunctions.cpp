#include "UsefulFunctions.h"

template <class T>
std::vector<T> uf::findFactors(T n, bool find_proper)
{
    // Lists all the factors of n.
    // Eg. for n = 8, outputs: {1,8,2,4}
    std::vector<T> factor_list;
    if (n == 1)
    { // Exception for when n == 1
        factor_list = {1};
        return factor_list;
    }

    for (int j{1}; j <= sqrt(n); ++j)
    {
        if (n % j == 0)
        {
            factor_list.push_back(j);
            if ((n % (n / j) == 0) && (n / j != j))
            {
                factor_list.push_back(n / j);
            }
        }
    }

    if (find_proper) // If we want to find proper factors, remove n from the list.
        factor_list.erase(factor_list.begin() + 1);

    return factor_list;
}

std::tuple<std::vector<int>, std::vector<int>> uf::findPrimeFactors(long long n)
{
    // Returns a list of the prime factors of n and a list of the number of times they occur, stored together in a tuple.
    // Eg. for n = 140, outputs { {2,5,7}, {2,1,1} }, because 140 = 2^2 * 5^1 * 7^1.
    std::vector<int> prime_list;
    std::vector<int> prime_count;

    int n_primes{0};
    while (n % 2 == 0)
    {
        if (n_primes == 0)
        {
            prime_list.push_back(2);
            prime_count.push_back(0);
            ++n_primes;
        }
        ++prime_count[0];
        n >>= 1; // Divide n by 2
    }

    for (int j{3}; n > 1; j += 2)
    {
        bool new_prime{true};
        while (n % j == 0)
        {
            if (new_prime)
            {
                prime_list.push_back(j);
                prime_count.push_back(1);
                ++n_primes;
                new_prime = false;
            }
            else
            {
                ++prime_count[n_primes - 1];
            }

            n = n / j;
        }
    }

    return {prime_list, prime_count};
}

bool uf::isPrime(int n)
{
    if (n <= 3)
        return n > 1;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    int i{5};
    while (i * i <= n)
    {
        if (n % i == 0 or n % (i + 2) == 0)
            return false;
        i += 6;
    }
    return true;
}

template <class T>
bool uf::inVector(const T find_var, const std::vector<T> &vec)
{ // If find_var is an element of vec, return true.
    for (auto elem : vec)
    {
        if (find_var == elem)
            return true;
    }
    return false;
}

std::ifstream uf::loadFile(std::string filepath)
{
    // Outputs an std::ifstream variable for the chosen file, after verifying the file has been loaded successfully.
    std::ifstream infile{filepath};

    if (!infile)
    {
        std::cerr << "File " + filepath + " could not be opened" << std::endl;
        throw;
    }
    return infile;
}

void uf::veryLongMultiply(std::vector<short> &digits_out, long long multiplier)
{
    // A function that takes in an int vector representing the digits of a number in backwards order.
    // Eg. 3489 is represented as {9,8,4,3}.
    // Directly changes the vector digits by reference.

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

void uf::veryLongAdd(std::vector<short> &digits_out, const std::vector<short> &num_add)
{
    // A function that takes in two int vectors representing the digits of their numbers in backwards order.
    // Adds the second vector to the first, modifying the first.
    // Eg. 3489 is represented as {9,8,4,3}.
    // Directly changes the vector 'digits_out' by reference.

    if (digits_out.size() < num_add.size()) // Resize
    {
        digits_out.resize(num_add.size(), 0);
    }

    for (int j{0}; j < digits_out.size(); ++j)
    {
        digits_out[j] += num_add[j]; // Add each respective digit together.
    }
    for (int j{0}; j < digits_out.size(); ++j)
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

template <class T>
void uf::printBackwardsDigits(const std::vector<T> &digits)
{
    for (int j{static_cast<int>(digits.size()) - 1}; j >= 0; --j)
        std::cout << digits.at(j);
    std::cout << "\n";
}

void uf::assertMsg(bool condition, std::string errMsg)
{
    // An easy version of assert() that provides a message.
    if (condition)
        return;
    else
    {
        std::cout << errMsg << "\n";
        throw;
    }
}

template <class T>
void uf::printVector(const std::vector<T> &vec)
{
    // Prints a vector. Eg. {1,2,3,4} prints: 1, 2, 3, 4, \n
    for (int j{0}; j < vec.size(); ++j)
        std::cout << vec.at(j) << ", ";
    std::cout << "\n";
}

std::string uf::boldText(std::string str)
{
    // Returns a formatted string
    return "\033[1;31m" + str + "\033[0m";
}

template <class T>
long long uf::sumVector(const std::vector<T> &vec)
{
    // Sums a vector. Make sure the input is some sort of number.
    long long total{0};
    for (int j{0}; j < vec.size(); ++j)
        total += vec.at(j);
    return total;
}

std::string uf::short2string(const short sh)
{
    return std::to_string(static_cast<int>(sh));
}

// Instantiate templates
template bool uf::inVector<int>(const int find_var, const std::vector<int> &vec);
template void uf::printVector<int>(const std::vector<int> &vec);