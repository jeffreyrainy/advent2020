#include <iostream>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}, {'.', " "}};
    return ret;
}

long content(std::string target, std::multimap<std::string, std::string>& contains, std::map<std::string, long>& factors)
{
    long ret = 0;
    for(auto p:contains)
    {
        if (p.first == target)
        {
            long f = factors[p.first + p.second];
            long c = content(p.second, contains, factors);

            ret += f * c;
        }
    }
    return ret + 1; // this bag lao counts
}

void process(Data& data)
{
    std::multimap<std::string, std::string> contains;
    std::map<std::string, long> factors;
    std::set<std::string> valid;

    for(auto j = 0; j < data.lines.size(); j++)
    for(auto i = 5; i < data.lines[j].words.size(); i+= 4)
    {
        std::string a = data.lines[j].words[0] + data.lines[j].words[1];
        std::string b = data.lines[j].words[i] + data.lines[j].words[i + 1];

        if (b != "otherbags")
        {
            contains.insert(std::make_pair(a,b) );
            long f = std::stol(data.lines[j].words[i - 1]);
            factors[a + b] = f;
        }
    }

    valid.insert("shinygold");

    bool changed = false;
    do
    {
        changed = false;
        for(auto p:contains)
        {
            if (valid.find(p.second) != valid.end() && valid.find(p.first) == valid.end())
            {
                valid.insert(p.first);
                changed = true;
            }
        }
    }
    while(changed);

    // -1 because we don't count the shiny gold bag itself
    std::cout << valid.size() - 1 << std::endl;
    std::cout << content("shinygold", contains, factors) - 1 << std::endl;

}
