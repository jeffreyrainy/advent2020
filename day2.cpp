#include <iostream>
#include <string>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{':', " "}, {'-', " "}};
    return ret;

}

void process(Data& data)
{
    int good1 = 0;
    int good2 = 0;

    for(auto l: data.lines)
    {
        std::string& pass = l.words[3];
        std::string& c = l.words[2];
        long x = l.numbers[0];
        long y = l.numbers[1];

        int count = 0;
        for(auto it:pass)
        {
            if (it == c[0])
            {
                count++;
            }
        }
        if (count >= x && count <= y)
        {
            good1++;
        }

        if ((pass[x - 1] == c[0]) ^ (pass[y - 1] == c[0]))
        {
            good2++;
        }
    }

    std::cout << good1 << std::endl;
    std::cout << good2 << std::endl;
}
