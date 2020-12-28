#include <iostream>
#include <queue>
#include "data.h"


std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void display(std::deque<int> ring)
{
    while(ring.size())
    {
        std::cout << ring.front() << " ";
        ring.pop_front();
    }
    std::cout << std::endl;
}

void moveTo(std::deque<int>& ring, int position)
{
    std::cout << "before move to " << position << std::endl;
    display(ring);

    int curr;
    do
    {
        curr = ring.front();
        ring.pop_front();

        if (curr == position)
        {
            break;
        }
        ring.push_back(curr);
    }
    while(true);
    ring.push_back(curr);

    std::cout << "after move to " << position << std::endl;
    display(ring);
}

void run(std::deque<int>& ring)
{

    std::cout << "-----" << std::endl;
    display(ring);


    int curr = ring.front();

    ring.pop_front();
    ring.push_back(curr);

    int x = ring.front();
    ring.pop_front();

    int y = ring.front();
    ring.pop_front();

    int z = ring.front();
    ring.pop_front();

    int position = curr;

    bool again;
    do
    {
        position--;
        again = false;
        if (position == 0)
        {
            position = 9;
        }
        if (position == x || position == y || position == z)
        {
            again = true;
        }
    }
    while(again);

    moveTo(ring, position);

    ring.push_front(z);
    ring.push_front(y);
    ring.push_front(x);

    moveTo(ring, curr);

    display(ring);

}

void slow(std::deque<int> ring)
{
    for(int i = 0; i < 100; i++)
    {
        std::cout << i + 1 <<std::endl;
        run(ring);
    }
}

void fillTo(int after[], int target, int first, int prev)
{
    after[first] = 10;
    for(int i = 10; i < target; i++)
    {
        after[i] = i+1;
    }

    if (target > 9)
    {
        after[target] = prev;
    }
    else
    {
        after[first] = prev;
    }

}

void process(Data& data)
{
    int after[1000001];
    int64_t value = data.lines[0].numbers[0];
    std::deque<int> ring;

    int first = value % 10;
    int prev;
    while(value)
    {
        prev = value % 10;
        ring.push_front(value % 10);
        value /= 10;

        if (value)
        {

            after[value % 10] = prev;
            prev = value % 10;
        }
    }

//    display(ring);
//    slow(ring);
//    std::cout << first << " " << prev << std::endl;

    int x,y,z,dest, curr;
    int limit = 1000000;

    fillTo(after, limit, first, prev);
    curr = prev;


    for(int it = 0; it < 10000000; it++)
    {
        dest = curr;
        x = after[curr];
        y = after[x];
        z = after[y];

        dest--;
        dest = dest ? dest : limit;
        while (dest == x || dest == y || dest == z)
        {
            dest--;
        }
        dest = dest ? dest : limit;

        int next = after[z];

        after[curr] = after[z];
        after[z] = after[dest];
        after[dest] = x;
        curr = next;
    }

    std::cout << (uint64_t)after[1] * after[after[1]] << std::endl;
}
