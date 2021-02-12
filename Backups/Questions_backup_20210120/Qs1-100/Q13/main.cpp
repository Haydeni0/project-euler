/* 

*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

int main()
{
    std::string filepath{"numbers.txt"};
    std::ifstream infile{filepath};

    if (!infile)
    {
        std::cerr << "File " + filepath + " could not be opened" << std::endl;
        throw;
    }

    std::string line;
    std::getline(infile,line,'\n');
    std::cout << line;


    return 0;
}