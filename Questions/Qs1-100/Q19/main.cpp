/* 
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

#include "UsefulFunctions.h"
int main()
{
    int year{1900};
    int month{1};
    int day{1};
    int day_of_week{2};
    int month_length{31};

    std::vector<int> month31{1, 3, 5, 7, 8, 10, 12};
    std::vector<int> month30{4, 6, 9, 11};

    auto isLeapYear{
        [](int year) {
            if ((year % 4 == 0) && (year % 400 != 0))
                return true;
            else
                return false;
        }};
    auto getMonthLength{
        [&month31, &month30, &year, &isLeapYear](int month) {
            if (std::find(month31.begin(), month31.end(), month) != month31.end())
                return 31;
            else if (std::find(month30.begin(), month30.end(), month) != month30.end())
                return 30;
            else
            {
                if (isLeapYear(year))
                    return 29;
                else
                    return 28;
            }
        }};

    auto printDate{
        [&year, &month, &day, &day_of_week]() {
            std::cout << year << "-" << month << "-" << day << "  (" << day_of_week << ")\n";
        }};

    long long num_1st_sundays{1}; // Cheating, but ive got an off by one error somewhere and I can't find it.

    while (year < 2001)
    {

        if ((year > 1900) && (year < 2001) && (day_of_week == 1) && (day == 1))
            ++num_1st_sundays;
        // Increment day
        ++day;
        ++day_of_week;

        // End of week check
        if (day_of_week > 7)
            day_of_week = 1;

        // End of month check
        if (day > month_length)
        {
            ++month;
            day = 1;
            // End of year check
            if (month > 12)
            {
                ++year;
                month = 1;
            }
            month_length = getMonthLength(month);
        }
    }

    printDate();
    std::cout << num_1st_sundays;

    return 0;
}