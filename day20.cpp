#include <iostream>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

int parse(std::string s)
{
    int v1 = 0;
    int v2 = 0;

    int f = 1;
    for(int i=0;i<10;i++)
    {
        if (s[i] == '#')
        {
            v1 += f;
        }
        f *= 2;
    }

    f = 1;
    for(int i=0;i<10;i++)
    {
        if (s[9 - i] == '#')
        {
            v2 += f;
        }
        f *= 2;
    }

    return std::min(v1,v2);
}

class Tile
{
    public:
    std::vector<int> sides;
    std::set<int> inSides;
    int code;
    std::vector<std::string> content;

    int sideOut = 0;
    int placed = false;
    int r = 0 ;
};

std::map<int,Tile> tiles;
std::vector<Tile> vTiles;

std::map<int, int> codes;
std::vector<std::string> theMap;

void draw()
{
    for(auto l:theMap)
    {
        std::cout << "|" << l << "|" << std::endl;
    }

}

bool addPiece(int tileOrient, int position)
{
    Tile& tile = vTiles[tileOrient/8];
    int orient = tileOrient%8;

    int ox = (position % 12) * 10;
    int oy = (position / 12) * 10;

    for(int i=0;i < 10; i++)
    for(int j=0;j < 10; j++)
    {
        int x;
        int y;

        switch(orient)
        {
            case 0:
                x = i; y = j; break;
            case 1:
                x = j; y = i; break;
            case 2:
                x = 9-i; y = j; break;
            case 3:
                x = j; y = 9-i; break;
            case 4:
                x = i; y = 9-j; break;
            case 5:
                x = 9-j; y = i; break;
            case 6:
                x = 9-i; y = 9-j; break;
            case 7:
                x = 9-j; y = 9-i; break;
        }

        theMap[oy + i][ox + j] = tile.content[x][y];
    }

    for(int i=0;i<10;i++)
    {
        if (oy != 0)
        {
            if (theMap[oy][ox + i] != theMap[oy - 1][ox + i])
            {
                return false;
            }
        }
        if (ox != 0)
        {
            if (theMap[oy + i][ox] != theMap[oy + i][ox - 1])
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<int> taken;
std::vector<std::string> monster = {
"                  # ",
"#    ##    ##    ###",
" #  #  #  #  #  #   "};

void countDragons()
{
    int count = 0;
    int j = 0;
    for(int i = 0; i < 12*10; i++)
    {
        if ((i % 10 != 0) && (i % 10 != 9))
        {
            int l = 0;
            for(int k = 0; k < 12*10; k++)
            {
                if ((k % 10 != 0) && (k % 10 != 9))
                {
                    theMap[j][l] = theMap[i][k];
                    theMap[j].resize(12*8);
                    l++;
                }
            }
            j++;
        }
    }
    theMap.resize(12*8);
    draw();
    std::cout << std::endl;


    for(int x = 0; x < 8 * 12; x++)
    for(int y = 0; y < 8 * 12; y++)
    {
        for(int o=0; o < 8; o++)
        {
            bool nope = false;

            for(int i = 0; i < 20; i++)
            for(int j = 0; j < 3; j++)
            {
                int dx;
                int dy;

                switch(o)
                {
                    case 0:
                        dx = i; dy = j; break;
                    case 1:
                        dx = j; dy = i; break;
                    case 2:
                        dx = -i; dy = j; break;
                    case 3:
                        dx = j; dy = -i; break;
                    case 4:
                        dx = i; dy = -j; break;
                    case 5:
                        dx = -j; dy = i; break;
                    case 6:
                        dx = -i; dy = -j; break;
                    case 7:
                        dx = -j; dy = -i; break;
                }

                if (x + dx >= 0 && y + dy >= 0 &&
                    x + dx < 12*8 && y + dy < 12*8)
                {
                    if (theMap[y + dy][x + dx] == '.' && monster[j][i] == '#')
                    {
                        nope = true;
                    }
                }
                else
                {
                    nope = true;
                }
            }

            if (!nope)
            {
                for(int i = 0; i < 20; i++)
                for(int j = 0; j < 3; j++)
                {
                    int dx;
                    int dy;

                    switch(o)
                    {
                        case 0:
                            dx = i; dy = j; break;
                        case 1:
                            dx = j; dy = i; break;
                        case 2:
                            dx = -i; dy = j; break;
                        case 3:
                            dx = j; dy = -i; break;
                        case 4:
                            dx = i; dy = -j; break;
                        case 5:
                            dx = -j; dy = i; break;
                        case 6:
                            dx = -i; dy = -j; break;
                        case 7:
                            dx = -j; dy = -i; break;
                    }

                    if (monster[j][i] == '#')
                    {
                        theMap[y + dy][x + dx] = 'O';
                    }
                }
                draw();
                std::cout << std::endl;
            }
        }
    }
    draw();

    for(auto l:theMap)
    {
        for(char c:l)
        {
            if (c == '#') count++;
        }
    }
    std::cout << count << std::endl;
}


void placeRec(int index)
{
    if (index == tiles.size())
    {
        std::cout << "solved" << std::endl;
        draw();
        std::cout << std::endl;
        countDragons();
        exit(0);
    }

    for(int i = 0; i < tiles.size() * 8; i++)
    {
        if (!taken[i/8])
        {
            taken[i/8] = 1;
            if (addPiece(i, index))
            {
                placeRec(index + 1);
            }
            taken[i/8] = 0;
        }
    }
}

void place()
{
    taken.clear();
    taken.resize(tiles.size());

    vTiles.clear();

    for(auto& t:tiles)
    {
        vTiles.push_back(t.second);
    }

    placeRec(0);

}

void add(int l,int r, int t, int b, int code, std::vector<std::string> content)
{
    if (tiles.find(code) != tiles.end())
    {
        return;
    }

    Tile& tile = tiles[code];
    tile.sides.push_back(l);
    tile.sides.push_back(r);
    tile.sides.push_back(t);
    tile.sides.push_back(b);
    tile.code = code;
    tile.content = content;

    for(auto s:tile.sides)
    {
        codes[s]++;
    }
}

void compute()
{
    std::cout << tiles.size() << std::endl;
    int64_t product = 1;

    for(auto t:tiles)
    {
        std::vector<int> sidesOut;
        for(int i = 0; i < t.second.sides.size(); i++)
        {
            if (codes[t.second.sides[i]] < 2)
            {
                t.second.sideOut++;
                sidesOut.push_back(i);
            }
        }

        if (t.second.sideOut == 2)
        {
            std::cout << "tile " << t.second.code << " is a corner" << std::endl;
            product *= t.second.code;

            for(auto p: t.second.content)
            {
                std::cout << p << std::endl;
            }
        }
        if (t.second.sideOut == 1)
        {
            std::cout << "tile " << t.second.code << " is a side" << std::endl;
        }
    }

    std::cout << product << std::endl;
}

void process(Data& data)
{
    bool first = false;
    int v;
    int top, bottom,left,right,code;
    std::string side1, side2;
    std::vector<std::string> content;

    for(int i=0; i < data.raw.size(); i++)
    {
        if (data.raw[i].substr(0, 4) == "Tile")
        {
            code = std::atoi(data.raw[i].c_str() + 4);
            side1 = "";
            side2 = "";
            first = true;
            content.clear();
        }
        else if (data.raw[i] == "")
        {
            bottom = v;
            left = parse(side1);
            right = parse(side2);

            add(left,right,top,bottom,code, content);

        }
        else
        {
            content.push_back(data.raw[i]);

            v = parse(data.raw[i]);
            if (first)
            {
                top = v;
                first = false;
            }
            side1 += data.raw[i][0];
            side2 += data.raw[i][9];
        }
    }
    bottom = v;
    left = parse(side1);
    right = parse(side2);

    theMap.resize(12*10);

    for(auto& l:theMap)
    {
        l.resize(12*10, ' ');
    }

    add(left,right,top,bottom,code, content);
    compute();
    draw();
    place();
}
