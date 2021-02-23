#include "UsefulFunctions.h"

std::vector<int> uf::findFactors(int n, bool find_proper)
{
    // Lists all the factors of n.
    // Eg. for n = 8, outputs: {1,8,2,4}
    std::vector<int> factor_list;
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

std::string uf::boldText(std::string str)
{
    // Returns a formatted string
    return "\033[1;31m" + str + "\033[0m";
}

std::string uf::short2string(const short sh)
{
    return std::to_string(static_cast<int>(sh));
}

std::vector<int> uf::int2digits(int x)
{
    x = abs(x);
    int num_digits{static_cast<int>(log10(x) + 1)};
    std::vector<int> digit_list(num_digits);
    for (int j{0}; j < num_digits; ++j)
    {
        digit_list[j] = static_cast<int>(x / pow(10, num_digits - j - 1));
        x -= digit_list[j] * pow(10, num_digits - j - 1);
    }
    return digit_list;
}

int uf::digits2int(const std::vector<int> &vec)
{
    int num{0};
    for (int j{(int)vec.size() - 1}; j >= 0; --j)
    {
        uf::assertMsg(vec[j] >= 0, "Digits must be positive");
        num += vec[j] * pow(10, vec.size() - 1 - j);
    }
    return num;
}

size_t uf::factorial(int n)
{ // Factorial, returns n!. Can overflow if n is larger than 20.
    uf::assertMsg(n >= 0, "n must be greater than or equal to zero.");
    uf::assertMsg(n <= 20, "n is too large (> 20)");

    if (n == 0)
        return 1;

    size_t n_factorial{1};
    while (n > 1)
    {
        n_factorial *= n;
        --n;
    }
    return n_factorial;
}
