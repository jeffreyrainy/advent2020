#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;

}

void process(Data& data)
{
    for(int i = 0; i < data.lines.size(); i++)
    for(int j = i + 1; j < data.lines.size(); j++)
    for(int k = j + 1; k < data.lines.size(); k++)
    {
        long& x = data.lines[i].numbers[0];
        long& y = data.lines[j].numbers[0];
        long& z = data.lines[k].numbers[0];

        if (x + y == 2020)
        {
            std::cout << x * y << std::endl;
        }

        if (x + y + z == 2020)
        {
            std::cout << x * y * z << std::endl;
        }
    }
}
