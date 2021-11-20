#include <cstdlib>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>

int main()
{
    mkdir("./Questions");
    for (int hundred{0}; hundred <= 7; ++hundred)
    {
        std::string dirname{"./Questions/Qs"};
        dirname += std::to_string(hundred * 100 + 1) + "-" + std::to_string((hundred + 1) * 100);
        mkdir(dirname.c_str());
        for (int j{1}; j <= 100; ++j)
        {
            std::string Qdirname{dirname + "/Q" + std::to_string(hundred*100 + j)};
            mkdir(Qdirname.c_str());
            std::string filepath{Qdirname + "/" + "main.cpp"};
            // Copy the template main.cpp file to the rest of the directories
            std::ifstream src("main.cpp", std::ios::binary);
            std::ofstream dst(filepath, std::ios::binary);

            dst << src.rdbuf();
        }
    }
}
