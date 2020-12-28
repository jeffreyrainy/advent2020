#include <iostream>
#include <map>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

std::map<std::pair<int,int>,int> color;

std::map<std::pair<int,int>,int> flip(std::map<std::pair<int,int>,int> before)
{
    std::map<std::pair<int,int>,int> after;

    int x0=0,x1=0;
    int y0=0,y1=0;

    for(auto p:color)
    {
        x0 = std::min(x0, p.first.first);
        x1 = std::max(x1, p.first.first);

        y0 = std::min(y0, p.first.second);
        y1 = std::max(y1, p.first.second);
    }

    for(int x = x0 - 2; x <= x1 + 2; x++)
    for(int y = y0 - 2; y <= y1 + 2; y++)
    {
        int count = 0;
        if (before[std::make_pair(x,y+1)]) count++;
        if (before[std::make_pair(x+1,y+1)]) count++;
        if (before[std::make_pair(x+1,y)]) count++;
        if (before[std::make_pair(x,y-1)]) count++;
        if (before[std::make_pair(x-1,y-1)]) count++;
        if (before[std::make_pair(x-1,y)]) count++;

        if (before[std::make_pair(x,y)] && (count == 0 || count > 2))
        {
            after[std::make_pair(x,y)] = 0;
        }
        else if (!before[std::make_pair(x,y)] && (count == 2))
        {
            after[std::make_pair(x,y)] = 1;
        }
        else
        {
            if (before.find(std::make_pair(x,y)) != before.end())
            after[std::make_pair(x,y)] = before[std::make_pair(x,y)];
        }
    }

    return after;
}


void process(Data& data)
{
    for(auto s:data.raw)
    {
        int x = 0;
        int y = 0;
        int p=0;
        while(p < s.size())
        {
            if (s[p] == 's')
            {
                if (s[p+1] == 'e')
                {
                    y--;
                    p+=2;
                }
                else
                {
                    y--;
                    x--;
                    p+=2;
                }
            }
            else if(s[p] == 'n')
            {
                if (s[p+1] == 'e')
                {
                    x++;
                    y++;
                    p+=2;
                }
                else
                {
                    y++;
                    p+=2;
                }
            }
            else if(s[p] == 'e')
            {
                x++;
                p+=1;
            }
            else if(s[p] == 'w')
            {
                x--;
                p+=1;
            }
            else
            {
                std::cout << "wtf" << std::endl;
                std::cout << s.c_str() + p << " " << p << std::endl;
            }
        }

        color[std::make_pair(x,y)] = 1 - color[std::make_pair(x,y)];
    }

    int total = 0;
    for(auto p:color)
    {
        total += p.second;
    }
    std::cout << total << std::endl;

    for(int i = 1; i < 101; i++)
    {
        color = flip(color);

        total = 0;
        for(auto p:color)
        {
            total += p.second;
        }
        std::cout << i << " " << total << std::endl;

    }



}
