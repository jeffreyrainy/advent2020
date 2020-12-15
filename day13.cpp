#include <iostream>
#include <numeric>

#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}};
    return ret;
}

void process1(Data& data)
{
    uint64_t t0 = data.lines[0].numbers[0];
    uint64_t best = 0;
    uint64_t bestID = 0;

    for(int i=0; i < data.lines[1].numbers.size(); i++)
    {
        uint64_t p = data.lines[1].numbers[i];
        if (p)
        {
            uint64_t next = ((t0 + p - 1) / p) * p;
            if (next < best || best == 0)
            {
                best = next;
                bestID = p;
            }
        }
    }
    std::cout << best - t0 << " " << bestID << std::endl;
    std::cout << (best - t0) * (bestID) << std::endl;
}

class State
{
public:
    uint64_t step = 1;
    uint64_t start = 0;

    void combine(uint64_t period, uint64_t mod)
    {
        if (mod == 0)
        {
            start = 0;
            step = period;
        }
        else
        while(true)
        {
            if ((start + mod) % period == 0)
            {
                step = std::lcm(step, period);
                break;
            }
            start += step;
        }
    }
};

void process2(Data& data)
{
    uint64_t t0 = data.lines[0].numbers[0];
    uint64_t best = 0;
    uint64_t bestID = 0;
    State d;

    for(int i=0; i < data.lines[1].numbers.size(); i++)
    {
        uint64_t p = data.lines[1].numbers[i];
        if (p)
        {
            d.combine(p, i);
        }
    }
    std::cout << d.start << " " << d.step << std::endl;
}

void process(Data& data)
{
    process1(data);
    process2(data);

    //     2   3
    //
    // 0   D   D
    // 1
    // 2   D
    // 3       D
    // 4   D
    // 5
    // 6   D   D
    // 7
    // 8   D


}
