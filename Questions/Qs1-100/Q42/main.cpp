/* 
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle 
numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position 
and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. 
If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly 
two-thousand common English words, how many are triangle words?
*/

#include "UsefulFunctions.h"

int main()
{
    // Make list of all relevant triangle numbers
    std::vector<int> triangle_numbers;
    for (int n{1}; n < 100; ++n)
    {
        triangle_numbers.push_back((n * (n + 1)) / 2);
    }

    int num_triangle_words{0};

    auto words_file{uf::loadFile("p042_words.txt")};
    std::string num_string;
    while (std::getline(words_file, num_string, ','))
    {
        int word_value{0};
        // Remove quotations "..."
        num_string = num_string.substr(1, num_string.size() - 2);

        for (auto elem : num_string)
        {                                              // Calculate word value
            word_value += static_cast<int>(elem) - 64; // Convert capital letter to position in alphabet
        }
        if (uf::inVector(word_value, triangle_numbers))
            num_triangle_words++;
    }

    std::cout << num_triangle_words;

    return 0;
}