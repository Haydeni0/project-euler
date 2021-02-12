/* 
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
The use of "and" when writing out numbers is in compliance with British usage.
*/

#include "UsefulFunctions.h"

std::string getUnitString(int n)
{
    // Prints numbers from 1 to 10. Eg. 4 outputs four.
    UsefulFunctions::assertMsg((n >= 0) && n <= 10, "Expected number between 0 and 10");
    std::vector<std::string> units{"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"}; // Ten is not a unit but eee.;..
    return units[n];
}
std::string getTenString(int n)
{
    // Prints numbers from 11 to 99. Eg. 21 outputs twentyone.
    UsefulFunctions::assertMsg((n >= 11) && n <= 99, "Expected number between 11 and 99");
    std::vector<std::string> tens{"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    std::vector<std::string> teens{"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

    std::string total_string;
    if (n < 20)
    {
        total_string += teens[n - 11];
        return total_string;
    }
    else
    {
        total_string += tens[n / 10 - 2];
        total_string += getUnitString(n - 10 * (n / 10));
        return total_string;
    }
}

std::string getHundredString(int n)
{
    // Prints numbers from 100 to 999. Eg. 432 outputs fourhundredandthirtytwo.
    UsefulFunctions::assertMsg((n >= 100) && n <= 999, "Expected number between 100 and 999");
    std::string hundred{"hundred"};
    std::string and_{"and"}; // and is a keyword, so use and_

    std::string total_string;

    if (n % 100 != 0)
        total_string += getUnitString(n / 100) + hundred + and_;
    else
        total_string += getUnitString(n / 100) + hundred;

    int tens{n - 100 * (n / 100)};
    if (tens < 11)
        total_string += getUnitString(tens);
    else
        total_string += getTenString(tens);

    return total_string;
}

std::string getNumberString(int n)
{
    // Prints numbers from 1 to 1000. Eg. 432 outputs fourhundredandthirtytwo.
    UsefulFunctions::assertMsg((n >= 1) && n <= 1000, "Expected number between 1 and 1000");

    if (n == 1000)
    {
        return "onethousand";
    }
    else if ((n >= 100) && n <= 999)
    {
        return getHundredString(n);
    }
    else if ((n >= 11) && n <= 99)
    {
        return getTenString(n);
    }
    else if ((n >= 1) && n <= 10)
    {
        return getUnitString(n);
    }
    else
        throw;
}

int main()
{
    long total_letters{0};

    for (int n{1}; n <= 1000; ++n)
    {
        std::string num{getNumberString(n)};
        total_letters += num.size();
        // std::cout << num <<"\n";
        // std::cin.get();
    }

    std::cout << total_letters;

    return 0;
}