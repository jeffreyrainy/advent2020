#include <iostream>
#include <map>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'['," "}, {']'," "}, {'='," "}};
    return ret;
}

void readMask(std::string v, uint64_t& z, uint64_t& o)
{
    uint64_t bit = 1;
    z = 0;
    o = 0;
    for(int i = 0; i < 36; i++)
    {
        if (v[35-i] == '0')
        {
            z |= bit;
        }
        if (v[35-i] == '1')
        {
            o |= bit;
        }

        bit = bit * 2;
    }

}

void readMask2(std::string v, uint64_t& z, uint64_t& o, uint64_t& x)
{
    uint64_t bit = 1;
    z = 0;
    o = 0;
    x = 0;
    for(int i = 0; i < 36; i++)
    {
        if (v[35-i] == '0')
        {
            z |= bit;
        }
        if (v[35-i] == '1')
        {
            o |= bit;
        }
        if (v[35-i] == 'X')
        {
            x |= bit;
        }

        bit = bit * 2;
    }

}


void process0(Data& data)
{
    uint64_t mask0;
    uint64_t mask1;

    std::map<uint64_t, uint64_t> memory;

    for(int i=0;i<data.lines.size(); ++i)
    {
        if (data.lines[i].words[0] == "mask")
        {
            readMask(data.lines[i].words[1], mask0, mask1);
        }
        else if (data.lines[i].words[0] == "mem")
        {
            uint64_t addr = data.lines[i].numbers[1];
            uint64_t op = data.lines[i].numbers[2];

            op = op | mask1;
            op = ~(~op | mask0);

            memory[addr] = op;
        }
    }

    uint64_t total = 0;
    for(auto p: memory)
    {
        total = total + p.second;
    }

    std::cout << total << std::endl;


}

bool f(uint64_t& addr2, uint64_t maskX, uint64_t it)
{
    uint64_t b = 1;

    do
    {
        if (maskX & b)
        {
            uint64_t v = it % 2;
            it /= 2;

            addr2 = (addr2 & ~b) + v * b;
        }

        b = b * 2;
    }
    while(b && it);

    if (!maskX) return false;
    if (it && !addr2) return false;

    return true;
}

void process(Data& data)
{
    process0(data);

    uint64_t mask0;
    uint64_t mask1;
    uint64_t maskX;

    std::map<uint64_t, uint64_t> memory;

    for(int i=0;i<data.lines.size(); ++i)
    {
        if (data.lines[i].words[0] == "mask")
        {
            readMask2(data.lines[i].words[1], mask0, mask1, maskX);
        }
        else if (data.lines[i].words[0] == "mem")
        {
            uint64_t addr = data.lines[i].numbers[1];
            uint64_t op = data.lines[i].numbers[2];

            addr = addr | mask1;
            addr = addr & ~maskX;

            uint64_t addr2 = 0;
            uint64_t it = 0;
            while(true)
            {
                bool b = f(addr2, maskX, it);

                memory[addr | addr2] = op;

                if (!b)
                {
                    break;
                }
                it++;
            }
        }
    }

    uint64_t total = 0;
    for(auto p: memory)
    {
        total = total + p.second;
    }

    std::cout << total << std::endl;


}