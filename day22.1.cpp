#include <iostream>
#include <deque>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

class Result
{

};

std::set<std::deque<int64_t>> seen;

bool game(std::deque<int64_t> v1, std::deque<int64_t> v2);

void process(Data& data)
{
    std::deque<int64_t> v1;
    std::deque<int64_t> v2;
    std::deque<int64_t>* v= &v1;

    for(auto l:data.lines)
    {
        if (l.words.size())
        {
            if (l.words[0] != "Player")
            {
                (*v).push_back(l.numbers[0]);
            }
        }
        else
        {
            v = &v2;
        }
    }
    std::cout << v1.size() << " " << v2.size() << std::endl;

    game(v1, v2);
}

bool game(std::deque<int64_t> v1, std::deque<int64_t> v2)
{
    bool ret;
    if (seen.find(v1) != seen.end() || seen.find(v2) != seen.end())
    {
        return true;
    }

    int round = 1;
    while(v1.size() && v2.size())
    {
        int64_t a1 = v1.front();
        int64_t a2 = v2.front();
        v1.pop_front();
        v2.pop_front();

        std::cout << "round " << round << " " << a1 << " " << a2 << std::endl;

        if (a1 > a2)
        {
            ret = true;
            v1.push_back(a1);
            v1.push_back(a2);
        }
        else
        {
            ret = false;
            v2.push_back(a2);
            v2.push_back(a1);
        }
        round++;
    }

    int64_t score = 0;
    int64_t mult =1;
    while(v1.size())
    {
        score += mult * v1.back();
        v1.pop_back();
        mult++;
    }
    mult = 1;
    while(v2.size())
    {
        score += mult * v2.back();
        v2.pop_back();
        mult++;
    }
    std::cout << score << std::endl;

    seen.insert(v1);
    seen.insert(v2);

    return ret;
}
