
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
using namespace std;

class rectangle
{
    public:
    int ID;
    pair<int,int> Pos;
    pair<int,int> Size;
    rectangle(int rect_id, int x,int y,int l_x,int l_y):ID(rect_id), Pos(x,y), Size(l_x,l_y) {}
};

void CountRect(vector<rectangle> & input_vector)
{
    static array<array<int,1000>,1000> fabric = {0};
    int l_x,l_y,p_x,p_y;
    bool collision;
    vector<int> Candidates;
    for(auto rect : input_vector)
    {
        l_x = rect.Size.first;
        l_y = rect.Size.second;
        p_x = rect.Pos.first;
        p_y = rect.Pos.second;
        for(int x = 0;x<l_x;++x)
        {
            for(int y = 0;y<l_y;++y)
            {
                fabric[p_x+x][p_y+y]++;
            }   
        }
    }
    int num_items = 0;
    
    for(auto row : fabric)
    {
        for(auto column : row)
        {
            if(column >= 2)
            {
                num_items++;
            }
        }
    }
    
    int num_items2 = 0;
    for(auto rect : input_vector)
    {
        collision = false;
        l_x = rect.Size.first;
        l_y = rect.Size.second;
        p_x = rect.Pos.first;
        p_y = rect.Pos.second;
        for(int x = 0;x<l_x;++x)
        {
            for(int y = 0;y<l_y;++y)
            {
                if(fabric[p_x+x][p_y+y]>1)
                {
                    collision = true;
                }
            }   
        }
        if(!collision)
        {
            Candidates.push_back(rect.ID);
        }
    }

    cout <<" Number above 2: " << num_items << " or " << num_items2<< '\n';
    cout << "Candidates: ";
    for(auto ID : Candidates)
    {
        cout << "ID: " <<ID <<", ";
    }
    cout<<'\n';
    //count_if(fabric)
};

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    string p_x,p_y,l_x,l_y,id,tmp;
    vector<rectangle> Data;

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            //DataLines.push_back(_line);
            istringstream lineStream(_line);
            getline(lineStream, tmp, '#');
            getline(lineStream, id, '@');
            getline(lineStream, p_x, ',');
            getline(lineStream, p_y, ':');
            getline(lineStream, l_x, 'x');
            getline(lineStream, l_y, ' ');
            //cout<<"ID: "<< id << "x,y:" << stoi(p_x) <<"," << stoi(p_y) << " Len: " << stoi(l_x) << "," << stoi(l_y) << '\n';
            Data.push_back(rectangle(stoi(id),stoi(p_x),stoi(p_y),stoi(l_x),stoi(l_y)));
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    CountRect(Data);
    return 0;
}