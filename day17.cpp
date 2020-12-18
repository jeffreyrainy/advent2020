#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void prop(std::vector<std::vector<std::vector<std::string>>> from, std::vector<std::vector<std::vector<std::string>>>& to)
{
    for(auto w = 0; w < from.size(); w++)
    for(auto z = 0; z < from[0].size(); z++)
    for(auto y = 0; y < from[0][0].size(); y++)
    for(auto x = 0; x < from[0][0][0].size(); x++)
    {
        int count = 0;
        for(auto dw = -1; dw < 2; dw++)
        for(auto dz = -1; dz < 2; dz++)
        for(auto dy = -1; dy < 2; dy++)
        for(auto dx = -1; dx < 2; dx++)
        {
            if (dx||dy||dz||dw)
            if (x + dx >= 0 && y + dy >= 0 && z + dz >= 0 && w + dw >=0)
            if (x + dx < from[0][0][0].size() && y + dy < from[0][0].size() && z + dz < from[0].size() && w + dw < from.size())
            if (from[w+dw][z+dz][y+dy][x+dx] == '#')
                count++;
        }
        if (from[w][z][y][x] == '#')
        {
            if (count >=2 && count <=3)
            {

            }
            else
            {
                to[w][z][y][x] = '.';
            }
        }
        else
        {
            if (count == 3)
            {
                to[w][z][y][x] = '#';
            }
        }
    }
}


void grow(std::vector<std::vector<std::vector<std::string>>>& hp)
{

    for(auto& planes:hp)
    {
        for(auto& plane:planes)
        {
            for(auto& row:plane)
            {
                row = (std::string)"?" + row + "?";
            }
        }

        for(auto& plane:planes)
        {
            plane.insert(plane.begin(), plane[0]);
            plane.push_back(plane[0]);
        }

        planes.insert(planes.begin(), planes[0]);
        planes.push_back(planes[0]);
    }
    hp.insert(hp.begin(), hp[0]);
    hp.push_back(hp[0]);

    {
        for(auto w = 0; w < hp.size(); w++)
        for(auto z = 0; z < hp[0].size(); z++)
        for(auto y = 0; y < hp[0][0].size(); y++)
        for(auto x = 0; x < hp[0][0][0].size(); x++)
        {
            if (!x || !y || !z || !w || (x == hp[0][0][0].size() - 1) || (y == hp[0][0].size() - 1) || (z == hp[0].size() - 1) || (w == hp.size() - 1))
            {
                hp[w][z][y][x] = '.';
            }
        }
    }
}

void display(std::vector<std::vector<std::string>> planes)
{
    for(auto&p:planes)
    {
        for(auto&l:p)
        {
            std::cout << l << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void process(Data& data)
{
    std::vector<std::vector<std::vector<std::string>>> planes;

    planes.resize(1);
    planes[0].resize(1);

    planes[0][0] = data.raw;

    for(int i=0; i < 6; i++)
    {
        auto planes2 = planes;

        grow(planes);
        grow(planes2);
        prop(planes, planes2);

        //display(planes2);
        planes = planes2;

        std::cout << std::endl;
    }

    int count =0;
    for(auto& hp:planes)
    for(auto& p:hp)
    for(auto& l:p)
    for(auto& c:l)
    {
        if (c == '#') count++;
    }

    std::cout << count << std::endl;




}
