#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>

#include "../Include/dataCreator.hpp"


using std::vector;
using std::string;
using std::fstream;

int GetNumberFromString(const string &str)
{
    string tmp {};

    tmp = std::regex_replace(str,
        std::regex("[^0-9]*([0-9]+).*"),
        std::string("$1")
        );

    return std::stoi(tmp);
}

void DataCreator::ReadVertFromFile(const string &filePath)
{
    fstream file;
    string line;
    int tMaxVal { 0 };

    file.open(filePath, std::ios::in);

    if(file.good())
    {
        while (getline(file, line))
        {
            int index {0}, vert1 {0}, vert2 {0};
            string sub_left {""}, sub_right {""};

            if (line.find("@start") != std::string::npos)
                continue;

            if (line.find("@end") != std::string::npos)
                continue;

            index = line.find(" - ");
            sub_left = line.substr(1, index - 2);
            sub_right = line.substr(index + 4, line.size());

            vert1 = GetNumberFromString(sub_left);
            vert2 = GetNumberFromString(sub_right);

            if(tMaxVal < vert1 || tMaxVal < vert2)
            {
                tMaxVal = (vert1 >= vert2) ? vert1 : vert2;
                fVert.resize(tMaxVal + 1);
                for(auto &row : fVert)
                    row.resize(tMaxVal + 1);
            }

            fVert[vert1][vert2] = 1;
            fVert[vert2][vert1] = 1;
        }

        file.close();
    }

}





