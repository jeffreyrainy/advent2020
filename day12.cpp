#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process1(Data& data)
{
    int64_t x = 0;
    int64_t y = 0;
    int64_t dx = 1;
    int64_t dy = 0;

    for(int i = 0; i < data.lines.size(); i++)
    {
        char c = data.lines[i].words[0][0];
        auto v = atol(data.lines[i].words[0].c_str() + 1);
        int64_t dx2,dy2;

        switch(c)
        {
            case 'N':
                y -= v;
            break;
            case 'S':
                y += v;
            break;
            case 'E':
                x += v;
            break;
            case 'W':
                x -= v;
            break;
            case 'L':
                while(v)
                {
                    dx2 = dy;
                    dy2 = -dx;
                    dx = dx2;
                    dy = dy2;
                    v -= 90;
                }
            break;
            case 'R':
                while(v)
                {
                    dx2 = -dy;
                    dy2 = dx;
                    dx = dx2;
                    dy = dy2;
                    v -= 90;
                }
            break;
            case 'F':
                x += dx * v;
                y += dy * v;
            break;
        }
    }
    std::cout << std::abs(x) +std::abs(y) << std::endl;
}

void process2(Data& data)
{
    int64_t x = 0;
    int64_t y = 0;
    int64_t dx = 10;
    int64_t dy = -1;


    for(int i = 0; i < data.lines.size(); i++)
    {
        char c = data.lines[i].words[0][0];
        auto v = atol(data.lines[i].words[0].c_str() + 1);
        int64_t dx2, dy2;

        switch(c)
        {
            case 'N':
                dy -= v;
            break;
            case 'S':
                dy += v;
            break;
            case 'E':
                dx += v;
            break;
            case 'W':
                dx -= v;
            break;
            case 'L':
                while(v)
                {
                    dx2 = dy;
                    dy2 = -dx;
                    dx = dx2;
                    dy = dy2;
                    v -= 90;
                }
            break;
            case 'R':
                while(v)
                {
                    dx2 = -dy;
                    dy2 = dx;
                    dx = dx2;
                    dy = dy2;
                    v -= 90;
                }
            break;
            case 'F':
                x += dx * v;
                y += dy * v;
            break;
        }
        //std::cout << x << " " << y << " " << dx << " " << dy << std::endl;
    }
    std::cout << std::abs(x) +std::abs(y) << std::endl;
}


void process(Data& data)
{
    process1(data);
    process2(data);


}
