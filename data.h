#include <vector>
#include <string>
#include <map>
#include <set>

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

template<typename T> std::ostream& operator<<(std::ostream& out, std::vector<T>& t)
{
    for(auto x: t)
    {
        out << x << " ";
    }
    return out;
}

template<typename T> std::ostream& operator<<(std::ostream& out, std::set<T>& t)
{
    for(auto x: t)
    {
        out << x << " ";
    }
    return out;
}


