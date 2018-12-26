#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

set<pair<int,int>> fillDown(vector<vector<char>> & groundMap,pair<int,int> waterstart,int edge)
{
    pair<int,int> water = waterstart;
    set<pair<int,int>> result;
    int xcoord_start = water.first;
    bool done = false;
    while(water.second<edge && !done)
    {

        if(groundMap[water.first][water.second+1] != '#')
        {
            groundMap[water.first][water.second] = '|';
            water.second++;
            
            // cout<<"down, row: " <<water.second<< "!\n";
        }
        else
        {
            while(result.empty())
            {
                //groundMap[water.first][water.second] = '~';
                // Fill left
                do
                {
                    // cout<<"left!\n";
                    groundMap[water.first][water.second] = '|';
                    water.first--;
                    
                    if (    (groundMap[water.first][water.second+1] == '.')
                        ||  (   (groundMap[water.first][water.second+1] != '#')
                             && (groundMap[water.first+1][water.second+1] == '#')
                             && (groundMap[water.first-1][water.second+1] == '.')))
                    {
                        result.insert(pair<int,int>(water.first,water.second));
                        // cout<<"found left edge!\n";
                        break;
                    }

                } while(groundMap[water.first][water.second] != '#');

                water.first=xcoord_start;
                do
                {
                    // cout<<"right!\n";
                    groundMap[water.first][water.second] = '|';
                    water.first++;
                    if (    (groundMap[water.first][water.second+1] == '.')
                        ||  (   (groundMap[water.first][water.second+1] != '#')
                             && (groundMap[water.first-1][water.second+1] == '#')
                             && (groundMap[water.first+1][water.second+1] == '.')))
                    {
                        result.insert(pair<int,int>(water.first,water.second));
                        // cout<<"found right edge!\n";
                        break;
                    }

                } while(groundMap[water.first][water.second] != '#');
                // cout<<"upwards one row: " <<water.second<< "!\n";
                if(result.size() == 0U)
                {
                    water.first--;
                    while(groundMap[water.first][water.second] == '|')
                    {
                        groundMap[water.first][water.second] = '~';
                        water.first--;
                    }
                    water.second--;
                }
                water.first = xcoord_start;
            }
            done = true;
        }
    }

    //vector<pair<int,int>> output(result.begin(),result.end());
    return result;
}

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    
    vector<int> xvector;
    vector<int> yvector;

    vector<pair<vector<int>,vector<int>>> indata;

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            int pos1 = _line.find(",");
            string tmp1 = _line.substr(0,pos1);
            string tmp2 = _line.substr(pos1+1);
            
            vector<int> xvec,yvec;
            int dots = tmp2.find("..");
            int pos2 = tmp2.find("=");

            if (int pos1 = tmp1.find("x") != string::npos)
            {
                xvec.push_back(stoi(tmp1.substr(pos1+1)));
                int start = stoi(tmp2.substr(pos2+1,dots));
                int end = stoi(tmp2.substr(dots+2));
                for (int y = start ; y<=end ; y++)
                {
                    yvec.push_back(y);
                }
            }  
            else
            {
                yvec.push_back(stoi(tmp1.substr(2)));
                int start = stoi(tmp2.substr(pos2+1,dots));
                int end = stoi(tmp2.substr(dots+2));
                for (int x = start ; x<=end ; x++)
                {
                    xvec.push_back(x);
                }
            }
            indata.emplace_back(pair<vector<int>,vector<int>>(xvec,yvec));
        }
        myfile.close();
    }
    else 
    {
        cout << "Unable to open file"; 
    }

    int glob_xmax = 0;
    int glob_xmin = __INT32_MAX__;
    int glob_ymax = 0;
    int glob_ymin = __INT32_MAX__;

    for(auto input: indata)
    {
        int xmax_tmp = *(max_element((input.first).begin(),(input.first).end()));
        int xmin_tmp = *(min_element((input.first).begin(),(input.first).end()));
        
        int ymax_tmp = *(max_element((input.second).begin(),(input.second).end()));
        int ymin_tmp = *(min_element((input.second).begin(),(input.second).end()));

        if (xmax_tmp>glob_xmax)
        {
            glob_xmax = xmax_tmp;   
        }
        if (ymax_tmp>glob_ymax)
        {
            glob_ymax = ymax_tmp;   
        }
        if (xmin_tmp<glob_xmin)
        {
            glob_xmin = xmin_tmp;   
        }
        if (ymin_tmp<glob_ymin)
        {
            glob_ymin = ymin_tmp;   
        }
    }
    cout << "Xmax: "<< glob_xmax << " Xmin: "<<glob_xmin << " Ymax: "<<glob_ymax<< " Ymin: "<< glob_ymin<<'\n';

    int sizex = glob_xmax-glob_xmin+4;
    int sizey = glob_ymax-glob_ymin+1;


    int waterstart = 500-(glob_xmin-2);

    vector<vector<char>> groundMap(sizex,vector<char>(sizey,'.'));
    
    for(auto & input: indata)
    {    
        for(auto & x:input.first)
        {
            x-=(glob_xmin-2);
        }
        for(auto & y : input.second)
        {
            y-=glob_ymin;
        }
    }
    for(auto input: indata)
    {
        if ((input.first).size() > 1)
        {
            for (auto x : input.first)
            {
                groundMap[x][(input.second)[0]] = '#';
            }            
        }
        else
        {
            for (auto y : input.second)
            {
                groundMap[(input.first)[0]][y] = '#';
            } 
        }
        
    }

    int waterstreamDepth = 0;
    pair<int,int> water = {waterstart,0};
    int rounds = 0;
    groundMap[waterstart][0] = '~';

    set<pair<int,int>> points;
    points = fillDown(groundMap,water,sizey);
    int validPoints = 1;
    //points = fillDown(groundMap,points[0],sizey);
    // while(points.size()>0 && rounds<30)
    while((points.size() != 0U) && rounds<30)
    {
        //rounds++;
        validPoints = 0;
        set<pair<int,int>> tmp_points;
        set<pair<int,int>> tmp;
        cout<< "Size of Points " << points.size() << "\n";
        for(auto start : points)
        {
            //cout<< start.first << "x" << start.second << " ymaxSize:"<< sizey<<'\n';
            tmp = fillDown(groundMap,start,sizey);
            tmp_points.insert(tmp.begin(),tmp.end());

        }
        points.clear();
        points = tmp_points;
        tmp_points.clear();
        tmp.clear();
    
    }
    
    if(!points.empty())
    {
        //cout << points[0].first << "x" << points[0].second<<'\n';
    }
    
    int total = 0;
    int still = 0;
    for(auto y = 0; y<sizey;y++)
    {
        for(auto x = 0; x<sizex;x++)
        {
            auto ground = groundMap[x][y];
            if(ground == '|' || ground == '~' )
            {
                total++;
            }
            if(ground == '~')
            {
                still++;
            }
            cout << ground;
        }
        cout<<'\n';
    }

    cout << "Total: " << total<<"\n"<<"Still Water: "<<still<<'\n';
/*
    cout << "ParsedData: \n";
    for(auto data : indata)
    {
        cout << "Xvec Size: "<< data.first.size() << " Yvec Size: " << data.second.size() << '\n';
        // cout<< "x: ";
        for(auto xvec : data.first)
        {
            // cout<<xvec<<" ";
        }

        // cout<< "y: ";
        for(auto yvec : data.second)
        {
            // cout<<yvec<<" ";
        }
        // cout<<'\n';
    }
*/
    return 0;
}