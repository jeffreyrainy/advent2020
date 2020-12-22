#include <iostream>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'(', " "}, {')', " "}, {',', " "}};
    return ret;
}

std::map<std::string, std::set<std::string>> couldBe;
std::map<std::string, std::string> is;
std::map<std::string, uint64_t> counts;

void process(Data& data)
{
    uint64_t total = 0;

    for(auto l: data.lines)
    {
        bool allergens = false;
        std::set<std::string> possibilities;

        for(auto w:l.words)
        {
            if (w == "contains")
            {
                allergens = true;
            }
            else
            {
                if (!allergens)
                {
                    total++;
                    counts[w]++;
                    possibilities.insert(w);
                }
                else
                {
                    if (couldBe.find(w) == couldBe.end())
                    {
                        couldBe[w] = possibilities;
                        std::cout << "initial " << w << std::endl;
                        std::cout << couldBe[w] << std::endl;
                    }
                    else
                    {
                        std::cout << "updating " << w << std::endl;
                        std::set<std::string> newCouldBe;
                        for(auto w2:possibilities)
                        {
                            if (couldBe[w].find(w2) != couldBe[w].end())
                            {
                                newCouldBe.insert(w2);
                            }
                        }

                        int oldSize = couldBe[w].size();
                        couldBe[w] = newCouldBe;

                        std::cout<< w << " went from " << oldSize << " to " << couldBe[w].size() << std::endl;
                    }
                }
            }
        }
    }

    bool added = false;
    do
    {
        added = false;
        std::string known = "";

        for(auto p:couldBe)
        {
            auto w = p.first;
            if (p.second.size() == 1 && is.find(p.first) == is.end())
            {
                is[p.first] = *p.second.begin();
                std::cout << p.first << " is " << is[p.first] << std::endl;
                known = p.first;
                added = true;
                break;
            };
        }

        if (known != "")
        {
            for(auto& p:couldBe)
            {
                if (p.first != known)
                {
                    std::string other = *couldBe[known].begin();
                    if (p.second.find(other) != p.second.end())
                    {
                        std::cout << p.first << " cannot be " << other << std::endl;
                        p.second.erase(other);
                        added = true;
                    }
                };
            }
        }

        for(auto& p:couldBe)
        {
            std::cout << p.first << ":" << std::endl;
            std::cout << p.second << std::endl;
        }
        std::cout << std::endl;

    }
    while(added);

    std::set<std::string> badIng;
    for(auto p:is)
    {
        badIng.insert(p.second);
    }

    std::set<std::string> badList;
    for(auto b:badIng)
    {
        total -= counts[b];
        badList.insert(b);
    }

    std::cout << total << std::endl;

    for(auto s:is)
    {
        std::cout << s.second << ",";
    }
    std::cout << std::endl;

}
