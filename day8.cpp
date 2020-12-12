#include <iostream>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'+', " "}};
    return ret;
}

long run(Data& data, bool& status)
{
    long ip = 0;
    long acc = 0;
    std::set<long> ips;

    do
    {
        if (ip == data.lines.size())
        {
            status = true;
            return acc;
        }
        ips.insert(ip);

        if (data.lines[ip].words[0] == "nop")
        {
            ip++;
        }
        else if (data.lines[ip].words[0] == "acc")
        {
            acc += data.lines[ip].numbers[1];
            ip++;
        }
        else if (data.lines[ip].words[0] == "jmp")
        {
            ip += data.lines[ip].numbers[1];
        }

        if (ips.find(ip) != ips.end())
        {
            status = false;
            return acc;
        }
    }
    while(true);
}

void process(Data& data)
{
    bool status = true;
    std::cout << run(data, status) << std::endl;
    auto lines0 = data.lines;

    for(int i=0; i < data.lines.size(); i++)
    {
        data.lines = lines0;
        if (data.lines[i].words[0] == "nop")
        {
            data.lines[i].words[0] = "jmp";
        }
        else if (data.lines[i].words[0] == "jmp")
        {
            data.lines[i].words[0] = "nop";
        }
        long acc = run(data, status);
        if (status)
        {
            std::cout << acc << std::endl;
        }
    }
}
