#include <iostream>
#include <algorithm>
#include <map>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    std::sort(data.lines.begin(), data.lines.end(), [](auto& x, auto& y){return x.numbers[0] < y.numbers[0];});
    std::map<int64_t, int64_t> counts;

    int64_t ones = 0;
    int64_t threes = 0;
    counts[0] = 1;

    for(int64_t i=0; i < data.lines.size(); ++i)
    {
        int64_t prev = 0;
        if (i != 0)
        {
            prev = data.lines[i - 1].numbers[0];
        }
        if (data.lines[i].numbers[0] - prev == 3)
        {
            threes++;
        }
        if (data.lines[i].numbers[0] - prev == 1)
        {
            ones++;
        }
    }
    threes++;

    for(int64_t i=0; i < data.lines.size(); i++)
    {
        int64_t target = data.lines[i].numbers[0];
        counts[target] = counts[target - 1] + counts[target - 2] + counts[target - 3];
    }

    std::cout << ones * threes << std::endl;
    std::cout << counts[data.lines[data.lines.size() - 1].numbers[0]] << std::endl;
}
