#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    std::cout << __FILE__ << std::endl;

    int x = 0;
    int y = 0;
    long count[5] = {0,0,0,0,0};
    int dx[5] = {1,3,5,7,1};
    int dy[5] = {1,1,1,1,2};


    for(int it = 0; it < 5; it++)
    {
        y = 0;
        x = 0;

        while(y < data.lines.size())
        {
            char c = data.lines[y].words[0][ dx[it]*(y/dy[it]) % data.lines[y].words[0].size() ];

            if (c == '#')
            {
                count[it]++;
            }
            y+=dy[it];
        }
    }

    long p = 1;
    for(int it=0;it<5;it++)
    {
        p = p * count[it];

        std::cout << count[it] << std::endl;
    }
    std::cout << p << std::endl;

}
