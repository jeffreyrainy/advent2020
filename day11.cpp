#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process1(Data& data)
{
    int X = data.raw[0].size();
    int Y = data.raw.size();

    std::vector<std::vector<int>> counts;

    for(int y = 0; y < Y; y++)
    {
        counts.push_back(std::vector<int>(X));
    }

    bool changed = true;
    auto check = data.raw;
    auto becomes = data.raw;

    while(changed)
    {
        changed = false;

        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
        {
            counts[y][x] = 0;
            for(int dy = -1; dy <= 1; dy++)
            for(int dx = -1; dx <= 1; dx++)
            {
                if (dx || dy)
                if (x + dx >= 0 && y + dy >= 0 && x + dx < X && y + dy < Y)
                {
                    if (check[y + dy][x + dx] == '#')
                    {
                        counts[y][x]++;
                    }
                }
            }
        }
        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
        {
            if (check[y][x] == 'L' && counts[y][x] == 0)
            {
                becomes[y][x] = '#';
                changed = true;
            }
            else if (check[y][x] == '#' && counts[y][x] >= 4)
            {
                becomes[y][x] = 'L';
                changed = true;
            }
            else
            {
                becomes[y][x] = check[y][x];
            }
        }

        check = becomes;
    }

    int count = 0;
    for(int y = 0; y < Y; y++)
    for(int x = 0; x < X; x++)
    {
        if(check[y][x] == '#')
        {
            count++;
        }
    }
    std::cout << count << std::endl;
}

void process2(Data& data)
{
    int X = data.raw[0].size();
    int Y = data.raw.size();

    std::vector<std::vector<int>> counts;

    for(int y = 0; y < Y; y++)
    {
        counts.push_back(std::vector<int>(X));
    }

    bool changed = true;
    auto check = data.raw;
    auto becomes = data.raw;

    while(changed)
    {
        changed = false;

        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
        {
            counts[y][x] = 0;
            for(int dy = -1; dy <= 1; dy++)
            for(int dx = -1; dx <= 1; dx++)
            {
                if (dx || dy)
                {
                    int scale = 1;
                    while(true)
                    {
                        if (x + scale*dx >= 0 && y + scale*dy >= 0 && x + scale*dx < X && y + scale*dy < Y)
                        {
                            if (check[y + scale*dy][x + scale*dx] == '#')
                            {
                                counts[y][x]++;
                                break;
                            }
                            if (check[y + scale*dy][x + scale*dx] == 'L')
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }

                        scale++;
                    }
                }
            }
        }
        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
        {
            if (check[y][x] == 'L' && counts[y][x] == 0)
            {
                becomes[y][x] = '#';
                changed = true;
            }
            else if (check[y][x] == '#' && counts[y][x] >= 5)
            {
                becomes[y][x] = 'L';
                changed = true;
            }
            else
            {
                becomes[y][x] = check[y][x];
            }
        }

        check = becomes;
    }

    int count = 0;
    for(int y = 0; y < Y; y++)
    for(int x = 0; x < X; x++)
    {
        if(check[y][x] == '#')
        {
            count++;
        }
    }
    std::cout << count << std::endl;
}

void process(Data& data)
{
    process1(data);
    process2(data);
}

