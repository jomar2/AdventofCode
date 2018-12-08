#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <array>
using namespace std;

class TargetCoordinate
{
    public:
    pair<int,int> Pos;
    bool valid = true;
    TargetCoordinate(pair<int,int> inPos): Pos(inPos) {}
};


int Distance(const pair<int,int> & Coordinate ,const pair<int,int> & Target)
{
    int xdist = abs(Coordinate.first - Target.first);
    int ydist = abs(Coordinate.second - Target.second);   
    return xdist+ydist;
};

pair<int,int> shortestDistance(const pair<int,int> & Coordinate ,const vector<TargetCoordinate> & InputCoordinates)
{
    int shortestDistance = __INT32_MAX__;
    int ID = 0;
    int counter = 0;
    bool collision =false;
    
    for(auto input : InputCoordinates)
    {
        int distanceTmp = Distance(Coordinate,input.Pos);
        if(distanceTmp<shortestDistance)
        {
            ID = counter;
            shortestDistance = distanceTmp;
            collision = false;
        }
        else if (distanceTmp==shortestDistance)
        {
            collision = true;
        }
        
        if (distanceTmp==0)
        {
            collision = false;
            return pair<int,int>(ID,shortestDistance);
        }
        counter++;
    }

    if(collision) 
    {
        return pair<int,int>(-1,shortestDistance);
    }
 
    return pair<int,int>(ID,shortestDistance);
};

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<TargetCoordinate> Data;
    ifstream myfile ("input.txt");
    string pos_x,pos_y;
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            istringstream lineStream(_line);
            getline(lineStream, pos_x , ',');
            getline(lineStream, pos_y , '\n');
            Data.push_back(TargetCoordinate(pair<int,int>(stoi(pos_x),stoi(pos_y))));
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "Size of Data: "<< Data.size() << '\n';
    auto size_max_x = max_element(Data.begin(), Data.end(),
            [&](const TargetCoordinate& left, const TargetCoordinate& right){
            return left.Pos.first <  right.Pos.first;});
/*
    auto size_min_x = max_element(Data.begin(), Data.end(),
            [&](const TargetCoordinate& left, const TargetCoordinate& right){
            return left.Pos.first >  right.Pos.first;});
    auto size_min_y = max_element(Data.begin(), Data.end(),
            [&](const TargetCoordinate& left, const TargetCoordinate& right){
            return left.Pos.second >  right.Pos.second;});
*/
    auto size_max_y = max_element(Data.begin(), Data.end(),
            [&](const TargetCoordinate& left, const TargetCoordinate& right){
            return left.Pos.second <  right.Pos.second;});
    

    //int size_x = (size_max_x->Pos.first) - (size_min_x->Pos.first);
    //int size_y = (size_max_y->Pos.second) - (size_min_y->Pos.second);
    int size_x = size_max_x->Pos.first+2;
    int size_y = size_max_y->Pos.second+2;
    
    //const int size_x = {400};
    //const int size_y = {400};
    cout << "X: "<<size_x<<" Y: "<<size_y<<'\n';
    static vector<vector<int>> field(size_x,vector<int>(size_y));
  
    //cout << "Ehh: Size X : "<<field.size()<<" Size Y : "<<field[0].size() << '\n';
    for(auto coord = 0;coord<size_x; coord++)
    {
        pair<int,int> Candidate;
        pair<int,int> topBorder = pair<int,int>(coord,0);
        pair<int,int> bottomBorder = pair<int,int>(coord,size_y);   
        
        Candidate = shortestDistance(topBorder,Data);
        //cout<<"top: " << coord<< " Invalid: "<<Candidate.first<<'\n';
        Data[Candidate.first].valid = false;
        Candidate = shortestDistance(bottomBorder,Data);
        Data[Candidate.first].valid = false;
        //cout<<"bottom: " << coord<< " Invalid: "<<Candidate.first<<'\n';
    }

    for(auto coord = 0;coord<size_y; coord++)
    {
        pair<int,int> Candidate;
        pair<int,int> leftBorder = pair<int,int>(0,coord);
        pair<int,int> rightBorder = pair<int,int>(size_x,coord);
        Candidate = shortestDistance(leftBorder,Data);
        //cout<<"left: " << coord<< " Invalid: "<<Candidate.first<<'\n';
        Data[Candidate.first].valid = false;
        Candidate = shortestDistance(rightBorder,Data);
      //  cout<<"right: " << coord<< " Invalid: "<<Candidate.first<<'\n';
        Data[Candidate.first].valid = false;
    }
    int num = 0;
    for(auto cand : Data)
    {
        if(cand.valid)
        {
            cout<<"Pos : "<< cand.Pos.first << ","<< cand.Pos.second << " is still valid"<<'\n'; 
            num++;
        }
    }
    cout<<"valid points: "<<num<<'\n'; 
    for(auto coordx = 0;coordx<size_x; coordx++)
    {
        for(auto coordy = 0;coordy<size_y; coordy++)
        {
            pair<int,int> Candidate = {-1,50000};
            pair<int,int> CurrentCoordinate = pair<int,int>(coordx,coordy);
            
            Candidate = shortestDistance(CurrentCoordinate,Data);
            field[coordx][coordy] = Candidate.first;
        }
    }

    int MaxArea = 0;
    int area = 0;
    int num_elements = 0;
    for(auto candId = 0U; candId < Data.size();candId++)
    {
        if(Data[candId].valid)
        {
            area = 0;
            vector< vector<int> >::iterator row;
            vector<int>::iterator col;
            for (row = field.begin(); row != field.end(); row++) {
                for (col = row->begin(); col != row->end(); col++) {
                    area += (*col == static_cast<int>(candId) ? 1 : 0);
                    num_elements++;
                }
            }

            if(MaxArea < area)
            {
                MaxArea = area;
            }

            /*
            for (row = field.begin(); row != field.end(); row++) 
            {
                for (col = row->begin(); col != row->end(); col++) 
                {
                    cout << *col <<" "; 
                }
                cout << '\n';
            }*/
        }
    }
    cout<<"Max Valid Area: "<< MaxArea<<'\n';
    cout<<"Elements checked: "<< num_elements<<'\n';

    return 0;
}
