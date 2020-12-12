#include <vector>
#include <string>
#include <map>

class Line
{
public:
    std::vector<std::string> words;
    std::vector<int64_t> numbers;
};

class Data
{
public:
    std::vector<Line> lines;
    std::vector<std::string> raw;
};

void process(Data& data);
std::map<char, std::string> getReplacements();
