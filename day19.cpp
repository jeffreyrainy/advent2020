#include <iostream>
#include <stdlib.h>

#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{':', ""}};
    return ret;
}

std::vector<Line> lines;
std::map<int, std::string> cache;
int gDepth = 0;

std::string getRep(int index)
{
    bool count = false;
    if (index == 11 || index == 8)
    {
        count = true;
    }

    if (count)
    {
        gDepth ++;
    }

    if (gDepth > 6)
    {
        gDepth --;
        return "x";
    }


    int i=0;
    for(i=0;lines[i].words.size() != 0; i++)
    {
        if (lines[i].numbers[0] == index)
        {
            break;
        }
    }

    std::string ret;
    ret = "(";
    for(int j=1; j < lines[i].words.size(); j++)
    {
        if (lines[i].words[j] == "|")
        {
            ret += "|";
        }
        else if (lines[i].words[j][0] =='"')
        {
            ret += lines[i].words[j][1];
        }
        else
        {
            ret += getRep(lines[i].numbers[j]);
        }
    }
    ret += ")";

    if (count)
    {
        gDepth--;
    }

    return ret;

}

void process(Data& data)
{
    lines=data.lines;
    std::string cmd = "grep -v : 19.txt | egrep \"^" + getRep(0) + "$\" | wc -l\n";
    std::cout << cmd.size() << " " << cmd << std::endl;
    system(cmd.c_str());
}
