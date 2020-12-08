#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    std::map<char, int> counts;
    int total = 0;
    int total2 = 0;
    int people = 0;

    for(int i = 0; i < data.lines.size(); i++)
    {
        if (data.lines[i].words.size())
        {
            for(auto c: data.lines[i].words[0])
            {
                counts[c]++;
            }
            people++;
        }

        if(data.lines[i].words.size() == 0 || i == data.lines.size() - 1)
        {
            for(auto p: counts)
            {
                total++;

                if (p.second == people)
                {
                    total2++;
                }
            }

            counts.clear();
            people = 0;
        }
    }
    std::cout << total << " " << total2 << std::endl;
}
