#include <vector>
#include <string>
#include <map>

class Line
{
public:
    std::vector<std::string> words;
    std::vector<long> numbers;
};

class Data
{
public:
    std::vector<Line> lines;
};

void process(Data& data);
std::map<char, std::string> getReplacements();
