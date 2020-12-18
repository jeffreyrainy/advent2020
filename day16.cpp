#include <iostream>
#include <map>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}, {'-', " -1 "}};
    return ret;
}

std::vector<int64_t> gRules;
int64_t rate = 0;

std::map<int64_t,std::set<int64_t>> forbidField;
std::map<int64_t,std::set<int64_t>> forbidRule;

void impossible(int64_t i, int64_t r)
{
    if (forbidField[i].find(r) == forbidField[i].end())
    {
        forbidField[i].insert(r);
        forbidRule[r].insert(i);
    }
}

bool check(std::vector<int64_t>& other, bool addRule = false)
{
    bool rejected = false;
    for(int64_t i=0; i < other.size(); i++)
    {
        bool valid = false;
        for(int r=0; r < gRules.size(); r+=4)
        {
            if ((other[i] >= gRules[r] && other[i] <= gRules[r+1]) ||
                (other[i] >= gRules[r+2] && other[i] <= gRules[r+3]))
            {
                valid = true;
            }
            else
            {
                if (addRule)
                {
                    impossible(i, r / 4);
                }
            }
        }

        if (!valid)
        {
            rate += other[i];
            rejected = true;
        }
    }

    if (!rejected && !addRule)
    {
        check(other, true);
    }

    return rejected;
}

void parseRule(std::vector<int64_t>& line)
{
    for(int64_t i = 0; i < line.size(); i++)
    {
        if (line[i] == -1)
        {
            gRules.push_back(line[i-1]);
            gRules.push_back(line[i+1]);
        }
    }
}

void process(Data& data)
{
    bool started = false;
    bool ticket = false;
    std::vector<int64_t> tick;
    std::vector<int64_t> other;
    std::vector<std::vector<int64_t>> tickets;

    for(int i = 0; i < data.lines.size(); i++)
    {
        parseRule(data.lines[i].numbers);

        if (ticket)
        {
            tick = data.lines[i].numbers;
            ticket = false;
        }

        if (started)
        {
            other = data.lines[i].numbers;
            if (check(other))
            {
                tickets.push_back(other);
            }
        }

        if (data.lines[i].words.size() && data.lines[i].words[0] == "nearby")
        {
            started = true;
        }
        if (data.lines[i].words.size() && data.lines[i].words[0] == "your")
        {
            ticket = true;
        }
    }
    std::cout << rate << std::endl;

    int64_t size = gRules.size() / 4;

    std::map<int64_t, int64_t> field;

    bool changed = true;
    int64_t prod = 1;
    while(changed)
    {
        changed = false;
        for(int i=0; i < size; i++)
        {
            if (field.find(i) == field.end() && forbidField[i].size() == (size - 1))
            {
                int r,i2;
                for(r=0; r < size; r++)
                {
                    if (forbidField[i].find(r) == forbidField[i].end())
                    {
                        break;
                    }
                }

                field[i] = r;

                if (r < 6)
                {
                    prod *= tick[i];
                }

                for(i2=0; i2 < size; i2++)
                {
                    if (i2 != i)
                    {
                        impossible(i2, r);
                    }
                }
                changed = true;
            }
        }
    }
    std::cout << prod;
    std::cout << std::endl;
}
