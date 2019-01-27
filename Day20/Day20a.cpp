#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

vector<string> subPath(string::iterator Directions,string CurrentPath)
{
    vector<string> retVal;

} 


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("test1.txt");
    if (myfile.is_open())
    {
        getline (myfile,_line);
        myfile.close();
    }
    else cout << "Unable to open file"; 
    vector<vector<string>> paths;
    int level = 0;
    istringstream lineStream(_line);
    string CurrentPath = "";
    string::iterator direction = _line.begin();
    while(direction != _line.end())
    {
        if(*direction == '(')
        {
            vector<string> res = subPath(direction,CurrentPath);
        }
        CurrentPath+=*direction;
    }
    /*for (auto dir : _line)
    {
        if(dir == '(')
        {
            paths.push_back(start);
            level++;
        }


    }*/
    return 0;
}