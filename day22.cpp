#include <iostream>
#include <deque>
#include <sstream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

class Result
{

};

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

std::string display(std::deque<int64_t> a)
{
    std::ostringstream out;
    while(a.size())
    {
        out << a.front() << " ";
        a.pop_front();
    }

    return out.str();
}

bool game(std::deque<int64_t> v1, std::deque<int64_t> v2)
{
    std::set<std::deque<int64_t>> seen;

    bool ret;


    int round = 1;
    while(v1.size() && v2.size())
    {
        if (seen.find(v1) != seen.end() || seen.find(v2) != seen.end())
        {
            return true;
        }
        seen.insert(v1);
        seen.insert(v2);

//        std::cout << "round " << round << std::endl;
//        std::cout << "player 1's deck: " << display(v1) << std::endl;
//        std::cout << "player 2's deck: " << display(v2) << std::endl;

        int64_t a1 = v1.front();
        int64_t a2 = v2.front();
        v1.pop_front();
        v2.pop_front();

        bool subWin;

        if (v1.size() >= a1 && v2.size() >= a2)
        {
            auto c1 = v1;
            auto c2 = v2;
            std::deque<int64_t> n1;
            std::deque<int64_t> n2;

            for(int i=0;i < a1; i++)
            {
                n1.push_back(c1.front());
                c1.pop_front();
            }
            for(int i=0;i < a2; i++)
            {
                n2.push_back(c2.front());
                c2.pop_front();
            }

            subWin = game(n1, n2);

            if (subWin)
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
        }
        else if (a1 > a2)
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

//    std::cout << "player " << (ret?1:2) << " wins" << std::endl;
    return ret;
}
