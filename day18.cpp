#include <iostream>
#include "data.h"
#include <sstream>

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

bool part2 = false;


int64_t eval(std::string l, bool override = false)
{
    int64_t v;
    int64_t last;

    std::cout << "evaluating " << l << std::endl;

    for(int64_t i = 0; i < l.size(); i++)
    {
        if (l[i] =='(')
        {
            last = i;
        }
        if (l[i] ==')')
        {
            std::string sub = l.substr(last + 1, i - (last + 1));

            v = eval(sub);
            sub = l.substr(0, last) + std::to_string(v) + l.substr(i + 1, l.size() - i - 1);

            return eval(sub);
        }
    }

    if(!part2 || override || l.find('+') == std::string::npos || l.find('*') == std::string::npos)
    {
        int op = 0;
        int64_t acc = 0;
        int64_t acc0 = 0;
        for(int i=0; i<l.size(); i++)
        {
            if (l[i] >= '0' && l[i] <= '9')
            {
                acc *= 10;
                acc += (l[i] - '0');
            }
            if (!op && l[i] == '+')
            {
                op = 1;
                acc0 = acc;
                acc = 0;
            }
            else if (!op && l[i] == '*')
            {
                op = 2;
                acc0 = acc;
                acc = 0;
            }
            else if (op && (l[i] == '*' || l[i] == '+'))
            {
                //std::cout << "acc " << acc << " acc0 " << acc0 << std::endl;
                if (op == 1) acc0 = acc + acc0;
                if (op == 2) acc0 = acc * acc0;
                //std::cout << "partial " << acc0 << std::endl;
                acc = 0;
                op = (l[i] == '*' ? 2 : 1);
            }
        }
        //std::cout << "acc " << acc << " acc0 " << acc0 << std::endl;
        if (op == 1) acc0 = acc + acc0;
        if (op == 2) acc0 = acc * acc0;
        //std::cout << "partial " << acc0 << std::endl;

        return acc0;
    }

    std::string was = l;
    int lasts = -1;
    for(int i=0; i<l.size(); i++)
    {
        if (l[i] == '*') lasts = i;
        if (l[i] == '+')
        {
            if (lasts != -1)
            {
                l[lasts + 1] = '(';
                int j;
                bool done = false;
                for(j=i;j<l.size();j++)
                {
                    if (l[j] == '*')
                    {
                        l[j-1] = ')';
                        done = true;
                        i = j-1;
                        break;
                    }
                }
                if (!done)
                {
                    l = l + ")";
                    i = l.size();
                }
            }
        }
    }
    return eval(l, true);


}

void process(Data& data)
{
    part2 = true;
    uint64_t sum = 0;
    for(auto l:data.raw)
    {
        sum += eval(l);

        std::cout << l << std::endl;
        std::cout << sum << std::endl << std::endl;;
    }
    std::cout << sum << std::endl;


}
