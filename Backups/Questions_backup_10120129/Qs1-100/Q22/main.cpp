/* 
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

#include "UsefulFunctions.h"

int nameValue(std::string name)
{
    // Makes a value for a name made of capital letters
    // Eg. COLIN is worth 3 + 15 + 12 + 9 + 14 = 53
    int value{0};
    for (int j{0}; j < name.size(); ++j)
    {
        value += static_cast<int>(name[j]) - 64;
    }
    return value;
}

int main()
{
    auto infile{uf::loadFile("names.txt")};

    std::vector<std::string> name_list;
    std::string line;
    while (std::getline(infile, line, ','))
    {
        line = line.substr(1, line.size() - 2); // Remove quotes
        name_list.push_back(line);
    }

    std::sort(name_list.begin(), name_list.end());

    // uf::printVector(name_list);

    long long total_score{0};
    for (long j{0}; j < name_list.size(); ++j)
    {
        total_score += nameValue(name_list[j])*(j+1);
    }

    std::cout << total_score;

    return 0;
}