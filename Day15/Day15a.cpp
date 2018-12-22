#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Character
{
    public:
    pair<int,int> Pos;
    bool alive = true;
    int AttackPower;
    Character(pair<int,int> inPos): Pos(inPos) {}
};


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    //ifstream myfile ("input.txt");
    ifstream myfile ("test1.txt");
    int x=0;
    int y=0;
    int sizex = 7;
    int sizey = 7;
    vector<vector<char>> caveMap(sizex,vector<char>(sizey,'#'));

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            x=0;
            for(auto coord : _line)
            {
                switch (coord)
                {
                    case '.':
                    case 'G':
                    case 'E':
                        caveMap[x][y] = coord;
                        break;
                    default:
                        break;
                }
                x++;
            }
            y++;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    for(auto y = 0; y<sizey;y++)
    {
        for(auto x = 0; x<sizex;x++)
        {
            cout << caveMap[x][y];
        }
        cout<<'\n';
    }

}