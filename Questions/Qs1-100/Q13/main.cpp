/* 
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
Store in numbers.txt
*/

#include "UsefulFunctions.h"

int main()
{
    long long big_sum{0};

    std::string filepath{"numbers.txt"};
    auto infile{UsefulFunctions::loadFile(filepath)};

    std::string line;
    std::getline(infile, line);
    int num_length{static_cast<int>(line.size())};

    /*
    I want to add these numbers just like doing it by hand, but not storing the last digits.
    Eg. if adding 123, 345 and 567:
    Add 3+5+7 = 15, store remainder 1 and throw away the 5.
    Then (along with the remainder 1) 
    Add (1+)2+4+6 = 13, store remainder 1 and throw away the 3,
    etc...
    */

    std::string result{""};
    int num_sigfig{10};
    long long remainder{0};
    for (int j{num_length - 1}; j >= 0; --j)
    {
        long long col_sum{remainder};
        infile.clear();
        infile.seekg(0); // Go back to beginning of the file
        while (infile >> line)
        {
            col_sum += static_cast<int>(line.at(j)) - 48;
            // std::cout << j << "\n";
        }
        remainder = col_sum / 10; // Integer divide by 10 (drop decimal part)
        if (j < num_sigfig)
        {
            result = std::to_string(col_sum - remainder * 10) + result;
        }
    }
    result = std::to_string(remainder) + result;
    // Remove the extra digits added by the remainder
    result = result.substr(0, num_sigfig);
    std::cout << result;

    return 0;
}