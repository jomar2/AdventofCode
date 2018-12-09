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

int DistanceLowerThan(const pair<int,int> & Coordinate ,const vector<TargetCoordinate> & InputCoordinates,const int Limit)
{
    int accDistance = 0;
    
    for(auto input : InputCoordinates)
    {
        int distanceTmp = Distance(Coordinate,input.Pos);
        accDistance += distanceTmp;
        if(accDistance>=Limit)
        {
            return 0;
        }
    }
 
    return 1;
};

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<TargetCoordinate> Data;
    ifstream myfile ("input.txt");
    string pos_x,pos_y;
    int distanceLimit = 10000;
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

    auto size_max_y = max_element(Data.begin(), Data.end(),
            [&](const TargetCoordinate& left, const TargetCoordinate& right){
            return left.Pos.second <  right.Pos.second;});
    


    int size_x = size_max_x->Pos.first+2;
    int size_y = size_max_y->Pos.second+2;
    
    cout << "X: "<<size_x<<" Y: "<<size_y<<'\n';
    static vector<vector<int>> field(size_x,vector<int>(size_y));
  
    for(auto coordx = 0;coordx<size_x; coordx++)
    {
        for(auto coordy = 0;coordy<size_y; coordy++)
        {
            pair<int,int> CurrentCoordinate = pair<int,int>(coordx,coordy);
            
            field[coordx][coordy] = DistanceLowerThan(CurrentCoordinate,Data,distanceLimit);
        }
    }

    int area = 0;
    int num_elements = 0;
    vector< vector<int> >::iterator row;
    vector<int>::iterator col;
    for (row = field.begin(); row != field.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            area += *col;
            num_elements++;
        }
    }
    cout<<"Max Valid Area: "<< area<<'\n';
    cout<<"Elements checked: "<< num_elements<<'\n';

    return 0;
}
