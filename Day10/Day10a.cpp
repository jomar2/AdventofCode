
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

template < class T1, class T2 >

inline std::vector < T1, T2 > operator+ ( const std::pair < T1, T2 > & a, const std::pair < T1, T2 > & b )
{
    return std::make_pair < T1, T2 > ( a.first + b.first, a.second + b.second );
};


void operator+=(std::vector<pair<int,int>> &v1, const std::vector<pair<int,int>> &v2) {
    vector<pair<int,int>>::iterator v1_iter = v1.begin();
    for(auto val : v2)
    {
        (*v1_iter).first += val.first;
        (*v1_iter).second += val.second;
        ++v1_iter;
    }
};


uint64_t area(vector<pair<int,int>>  & DrawVector)
{
    
    //cout << "start Maxelement:\n";
    uint64_t max_x = (*max_element(DrawVector.begin(),DrawVector.end() ,[](auto & left, auto & right){return left.first < right.first;})).first;
    uint64_t min_x = (*max_element(DrawVector.begin(),DrawVector.end() ,[](auto & left, auto & right){return left.first > right.first;})).first;

    uint64_t max_y = (*max_element(DrawVector.begin(),DrawVector.end() ,[](auto & left, auto & right){return left.second < right.second;})).second;
    uint64_t min_y = (*max_element(DrawVector.begin(),DrawVector.end() ,[](auto & left, auto & right){return left.second > right.second;})).second;
    uint64_t sizex = (max_x - min_x)+3;
    uint64_t sizey = (max_y - min_y)+3;
    //cout << "end Maxelement:\n";
    uint64_t area = sizex*sizey;
    return area;
}

int getDistance(const pair<int,int> & Coordinate ,const pair<int,int> & Target)
{
    
    int xdist = abs(Coordinate.first - Target.first);
    int ydist = abs(Coordinate.second - Target.second);   
    int res = xdist+ydist;
    return (res == 0 ? 1 : res);
};


auto accumMinDistance(vector<pair<int,int>>  & InputVector)
{
    //int dist = __INT32_MAX__;
    vector<int> sum(0);
    
    //int minDist = __INT32_MAX__;
    for(auto inp = InputVector.begin(); inp != InputVector.end(); ++inp)
    {
        for(auto target = InputVector.begin(); target != InputVector.end(); ++target)
        {
            if(inp!=target)
            {
                //dist = Distance(*inp,*target);
                //cout<<"Check of coordinates: pos 1: "<< (*inp).first <<"x"<<(*inp).second <<" pos 2: "<< (*target).first <<"x"<<(*target).second<< "\nGives Distance: "<<dist<<'\n';
                sum.push_back(getDistance(*inp,*target)); 
            }
        }
        //cout<<"MinDist during count: "<< minDist<<'\n';
    }
    int total = accumulate(sum.begin(),sum.end(),0); 
    cout<<"Total size during count: "<< sum.size()<<'\n';
    return total/sum.size();   
}

void clear(vector<vector<char>> & fieldIn,int sizex,int sizey)
{
    for(int y=0;y<sizey;y++)
    {
        for(int x=0;x<sizex;x++)
        {
            fieldIn[x][y] = '.';
        }
    }
}
void drawMessage(vector<pair<int,int>> input)
{  
    auto max_x = (*max_element(input.begin(),input.end() ,[](auto & left, auto & right){return left.first <= right.first;})).first;
    auto min_x = (*max_element(input.begin(),input.end() ,[](auto & left, auto & right){return left.first > right.first;})).first;

    auto max_y = (*max_element(input.begin(),input.end() ,[](auto & left, auto & right){return left.second <= right.second;})).second;
    auto min_y = (*max_element(input.begin(),input.end() ,[](auto & left, auto & right){return left.second > right.second;})).second;
    auto sizex = (max_x - min_x)+3;
    auto sizey = (max_y - min_y)+3;
    auto Area = sizex*sizey;
     cout << "Drawing Area: "<<Area<<'\n';
    ofstream myfile;
    myfile.open ("res.txt");
    //myfile << "Writing this to a file.\n";
 
    // Best Matrix setup!!
    cout << "Max x: "<< max_x <<" Min x: "<< min_x<<  " Max y: "<< max_y << " Min y: "<< min_y<< "\nGives total area of: "<<sizex<<"x"<<sizey<<'\n';
    vector<vector<char>> field(sizex,vector<char>(sizey,'.'));
    vector<pair<int,int>> drawingVector;
    drawingVector.reserve(input.size());
    drawingVector = input;
    //pair<int,int> bias((min_x < 0 ? -min_x : 0),(min_y < 0 ? -min_y : 0));
    pair<int,int> bias(-min_x,-min_y);
    vector<pair<int,int>> biasVect(input.size(),bias);
    cout << "pos x: "<< drawingVector[0].first <<" pos y: "<< drawingVector[0].second<<'\n';
    drawingVector+= biasVect;
    cout << "pos x: "<< drawingVector[0].first <<" pos y: "<< drawingVector[0].second<<'\n';
    //clear(field,sizex,sizey);
    for(auto drawpos : drawingVector)
    {
        if((drawpos.first<sizex) && (drawpos.first>=0) && (drawpos.second<sizey) && (drawpos.second>=0))
        {
            //cout << "pos x: "<< drawpos.first <<" pos y: "<<drawpos.second<< " Limits: " << sizex<<"x"<<sizey<<'\n';
            field[drawpos.first][drawpos.second] = '#';
        }
    }


    for(int y = 0;y<sizey;y++)
    {
        for(int x = 0;x<sizex;x++)
        {   
            //cout<<((field[x][y] != '\0') ?  '#' : '.');
            myfile<<field[x][y];
        }
        myfile<<'\n';
    }
 myfile.close();
}


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    vector<pair<int,int>> positions;
    vector<pair<int,int>> velocities;
    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            //position=<-31667, -52902> velocity=< 3,  5>
            int tmp1 = _line.find("<");
            int tmp2 = _line.find(",");
            int tmp3 = _line.find(">");
            pair<int,int> pos = pair<int,int>(stoi(_line.substr(tmp1+1,tmp2-tmp1)),stoi(_line.substr(tmp2+1,tmp3-tmp2)));
            _line = _line.substr(tmp3);
            tmp1 = _line.find("<");
            tmp2 = _line.find(",");
            tmp3 = _line.find(">");
            pair<int,int> vel = pair<int,int>(stoi(_line.substr(tmp1+1,tmp2-tmp1)),stoi(_line.substr(tmp2+1,tmp3-tmp2)));
            //cout<<"Pos x: " << pos.first << " y: " << pos.second << " Velocity: vx: "<< vel.first << " vy: "<< vel.second << '\n';
            positions.push_back(pos);
            velocities.push_back(vel);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout<<"Pos x: " << positions.size() << " y: " << positions[4].second << " Velocity: vx: "<< velocities[4].first << " vy: "<< velocities[4].second << '\n';

    int maxTime = 50000;
    int time = 0;
    int foundTime;
    uint64_t CurrentDist = 0;
    uint64_t MinDistance = __UINT64_MAX__;
    uint64_t CurrentArea = 0;
    uint64_t MinArea = __UINT64_MAX__;
    vector<pair<int,int>> answer;
    while(time <= maxTime)
    {
        CurrentArea = area(positions);
        cout<< " Current area: " << CurrentArea<<'\n';
        if(CurrentArea>MinArea)
        {
            //break;
        }
        else
        {
            MinArea = CurrentArea;
            answer = positions;
            foundTime = time;
        } 
        positions+=velocities;
        time++;
    }

    cout<<"MinArea: "<<MinArea<<'\n'<<"Time Found: "<<foundTime<<'\n';
    drawMessage(answer);
    
    return 0;
}