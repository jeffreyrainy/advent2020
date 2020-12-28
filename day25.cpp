#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    int64_t a = data.lines[0].numbers[0];
    int64_t b = data.lines[1].numbers[0];

    int64_t subject = 1;
    int64_t count1 = 0;
    int64_t count2 = 0;
    int64_t value = 1;

    subject = 7;
    while(value != a)
    {
        value = (value * subject) % 20201227;
        count1++;
    }
    value = 1;
    subject = 7;
    while(value != b)
    {
        value = (value * subject) % 20201227;
        count2++;
    }

    std::cout << count1 << " " << count2 << std::endl;
    std::cout << "pub key 1" << " " << a << std::endl;
    std::cout << "pub key 2" << " " << b << std::endl;

    value = 1;
    subject = a;
    for(int64_t i = 0; i < count2; i++)
    {
        value = (value * subject) % 20201227;
    }

    std::cout << value << std::endl;

    value = 1;
    subject = b;
    for(int64_t i = 0; i < count1; i++)
    {
        value = (value * subject) % 20201227;
    }

    std::cout << value << std::endl;


}
