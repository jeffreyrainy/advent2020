#include <iostream>
#include <algorithm>

#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process2(Data& data)
{
    uint64_t x = 0;
    uint64_t y = 0;
    uint64_t sum = 0;
    uint64_t target = 2089807806;

    while(true)
    {
        //std::cout << "sum " << x << " to " << y << " is " << sum << std::endl;
        if (sum < target)
        {
            sum = sum + data.lines[y].numbers[0];
            y++;
        }
        else if (sum > target)
        {
            sum = sum - data.lines[x].numbers[0];
            x++;
        }
        else
        {
            uint64_t l1 = data.lines[x].numbers[0];
            uint64_t l2 = data.lines[x].numbers[0];

            for(int i = x; i < y; i++)
            {
                if (data.lines[i].numbers[0] < l1)
                {
                    l1 = data.lines[i].numbers[0];
                }
                if (data.lines[i].numbers[0] > l2)
                {
                    l2 = data.lines[i].numbers[0];
                }
            }
            std::cout << l1 + l2 << std::endl;

            return;
        }
    }
}
// 251228247 too high

void process(Data& data)
{

    uint64_t i, x, y;
    const uint64_t SIZE = 25;
    uint64_t ring[SIZE];
    uint64_t pos = 0;
    uint64_t mod = (uint64_t)1 << 30;

    for(i = 0 ; i < data.lines.size(); i++)
    {
        uint64_t value = data.lines[i].numbers[0] % mod;

        bool good = false;
        for(x = 0; x < SIZE; x++)
        for(y = 0; y < SIZE; y++)
        {
            if ((x!=y) && ((ring[x] + ring[y]) % mod == value))
            {
                good = true;
                break;
            }
        }

        if (i > SIZE && !good)
        {
            std::cout << data.lines[i].words[0] << std::endl;
        }

        ring[pos] = value;
        pos = (pos + 1) % SIZE;
    }

    process2(data);

}
