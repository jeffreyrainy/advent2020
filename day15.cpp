#include <iostream>
#include <map>
#include <unordered_map>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}};
    return ret;
}

void process(Data& data)
{
    std::unordered_map<uint64_t, uint64_t> when;
    std::unordered_map<uint64_t, uint64_t> before;

    uint64_t now = 0;
    uint64_t spoken = 0;
    uint64_t last;

    for(now = 0; now < data.lines[0].numbers.size(); ++now)
    {
        when[data.lines[0].numbers[now]] = now;
        last = data.lines[0].numbers[now];
    }

    do
    {
        if (before.find(last) == before.end())
        {
            spoken = 0;
        }
        else
        {
            spoken = when[last] - before[last];
        }

        if (when.find(spoken) != when.end())
        {
            before[spoken] = when[spoken];
        }
        when[spoken] = now;

        if (now == 2019)
        {
            std::cout << now << " " <<  spoken << std::endl;
        }
        else if (now == 29999999)
        {
            std::cout << now << " " <<  spoken << std::endl;
            return;
        }
        last = spoken;
        now++;
    }
    while(true);




}
