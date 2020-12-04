#include <iostream>
#include <algorithm>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{':', " "}};
    return ret;
}

std::multimap<std::string, std::string> passed;

bool check(std::string field, std::string value)
{
    int v = 0;
    try
    {
        v = std::stoi(value);
    }
    catch(...)
    {

    }

    if (field == "byr")
    {
        if (value.size() != 4) return false;
        if (v < 1920 || v > 2002) return false;
    }
    if (field == "iyr")
    {
        if (value.size() != 4) return false;
        if (v < 2010 || v > 2020) return false;
    }
    if (field == "eyr")
    {
        if (value.size() != 4) return false;
        if (v < 2020 || v > 2030) return false;
    }

    if (field == "hgt")
    {
        if (value.find("cm") != std::string::npos)
        {
            if (v < 150 || v > 193) return false;
        }
        else if (value.find("in") != std::string::npos)
        {
            if (v < 59 || v > 76) return false;
        }
        else
        {
            return false;
        }
    }
    if (field == "hcl")
    {
        if (value.size() != 7) return false;
        if (value[0] != '#') return false;
        for(int i = 0; i < 6; i++)
        {
            if ((value[i + 1] < '0' || value[i + 1] > '9') &&
                (value[i + 1] < 'a' || value[i + 1] > 'f')) return false;
        }
    }
    if (field == "ecl")
    {
        if (value != "amb" &&
            value != "blu" &&
            value != "brn" &&
            value != "gry" &&
            value != "grn" &&
            value != "hzl" &&
            value != "oth" ) return false;
    }

    if (field == "pid")
    {
        if (value.size() != 9) return false;
        for(int i = 0; i < 9; i++)
        {
            if (value[i] < '0' || value[i] > '9') return false;
        }
    }
    passed.insert(std::make_pair(field, value));

    return true;
}

void process(Data& data)
{
    std::vector<std::string> codes = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    std::map<std::string, int> counts;
    int count = 0;
    int count2 = 0;
    bool invalid = false;

    for(int i = 0; i < data.lines.size(); i++)
    {
        std::string field = "";
        for(auto w:data.lines[i].words)
        {
            if (std::find(codes.begin(), codes.end(), w) != codes.end())
            {
                counts[w]++;
                field = w;
            }
            else if (field != "")
            {
                if (!check(field, w))
                {
                    invalid = true;
                }

                field = "";
            }
        }
        if(data.lines[i].words.size() == 0 || i == data.lines.size() - 1)
        {
            if (counts.size() == 7)
            {
                count++;
                if (!invalid)
                {
                    count2++;
                }
            }
            invalid = false;
            counts.clear();
        }
    }

    std::cout << count << " " << count2 << std::endl;

}
