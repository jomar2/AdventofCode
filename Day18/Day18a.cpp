#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<pair<int,int>> getAdjecent(int xcoord,int ycoord,int maxSize)
{
    vector<int> removeIndex;
    vector<pair<int,int>> adjecent;
    if(xcoord==0)
    {
        removeIndex.insert(removeIndex.end(),{0,3,5});
    }
    else if (xcoord==static_cast<int>(maxSize-1))
    {
        removeIndex.insert(removeIndex.end(),{2,4,7});
    }

    if(ycoord==0)
    {
        removeIndex.insert(removeIndex.end(),{0,1,2});
    }
    else if (ycoord==static_cast<int>(maxSize-1))
    {
        removeIndex.insert(removeIndex.end(),{5,6,7});
    }

    for(int coordIndex = 0;coordIndex<8;coordIndex++)
    {
        if(find(removeIndex.begin(),removeIndex.end(),coordIndex) == removeIndex.end())
        {
            switch(coordIndex)
            {
                case 0:
                    adjecent.push_back(pair<int,int>(xcoord-1,ycoord-1));
                    break;
                case 1:
                    adjecent.push_back(pair<int,int>(xcoord,ycoord-1));
                    break;
                case 2:
                    adjecent.push_back(pair<int,int>(xcoord+1,ycoord-1));
                    break;
                case 3:
                    adjecent.push_back(pair<int,int>(xcoord-1,ycoord));
                    break;
                case 4:
                    adjecent.push_back(pair<int,int>(xcoord+1,ycoord));
                    break;
                case 5:
                    adjecent.push_back(pair<int,int>(xcoord-1,ycoord+1));
                    break;
                case 6:
                    adjecent.push_back(pair<int,int>(xcoord,ycoord+1));
                    break;
                case 7:
                    adjecent.push_back(pair<int,int>(xcoord+1,ycoord+1));
                    break;
                default:
                    break;
            }
        }
    }
    return adjecent;
}

char updateCoordinate(vector<vector<char>> CurrentMap, int xcoord,int ycoord)
{
    vector<pair<int,int>> adjecent = getAdjecent(xcoord,ycoord,CurrentMap.size());

    /*cout<< "Coordinates: "<< xcoord << "x"<<ycoord<<"\nAdjecent: ";
    for ( auto adj : adjecent)
    {
        cout<< adj.first << "x" << adj.second<<" , ";
    }
    cout<<'\n';
*/
    int woods;
    int luberyards;
    //cout<<"currentChar: "<< CurrentMap[xcoord][ycoord]<<'\n';

    woods = 0;
    luberyards = 0;

    if(CurrentMap[xcoord][ycoord] == '.')
    {
        // cout<<"empty square: \n";
        for(auto adjCoords : adjecent)
        {
            // cout<< adjCoords.first << "x" << adjCoords.second<<" : ";
            if(CurrentMap[adjCoords.first][adjCoords.second] == '|')
            {
                // cout<<" Tree++";
                woods++;
            }
            // cout<<"\n";
        }

        if (woods>2)
        {
            return '|';
        }
    }
    else if(CurrentMap[xcoord][ycoord] == '|')
    {

        // cout<<"Tree square: \n";
        for(auto adjCoords : adjecent)
        {
            // cout<< adjCoords.first << "x" << adjCoords.second<<" : ";
            if(CurrentMap[adjCoords.first][adjCoords.second] == '#')
            {
                // cout<<" Lumberyard++";
                luberyards++;
            }
            // cout<<'\n';
        }
        if (luberyards>2)
        {
            return '#';
        }
    }
    else if(CurrentMap[xcoord][ycoord] == '#')
    {
        // cout<<"LumberYard square: \n";
        for(auto adjCoords : adjecent)
        {
            if(CurrentMap[adjCoords.first][adjCoords.second] == '#')
            {
                // cout<<" Lumberyard++";
                luberyards++;
            }
            if(CurrentMap[adjCoords.first][adjCoords.second] == '|')
            {
                // cout<<" Tree++";
                woods++;
            } 
            // cout<<"\n";
        }
        if (luberyards<1 || woods <1)
        {
            return '.';
        }
    }
    return CurrentMap[xcoord][ycoord];
    
}

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    int sizex = 50;
    int sizey = 50;
    //ifstream myfile ("test1.txt");
    //int sizex = 10;
    //int sizey = 10;
    int x=0;
    int y=0;
    vector<vector<char>> forrestMapGround(sizex,vector<char>(sizey,'#'));

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            x=0;
            for(auto coord : _line)
            {
                forrestMapGround[x][y] = coord;
                x++;
            }
            y++;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    //auto limit = 1000000000;

    auto limit = 1000;
    

    int tree = 0;
    int lumberyards = 0;
    /*for(auto limit = 0;limit <=3000;limit+=1000)
    {  
    auto forrestMap = forrestMapGround;*/

    for(auto minutes = 1;minutes <=limit;minutes++)
    {
        auto NewMap = forrestMap;
        /*cout << "\nRound "<<minutes<<"!\n";
        for(auto y = 0; y<sizey;y++)
        {
            for(auto x = 0; x<sizex;x++)
            {
                cout << forrestMap[x][y];
            }
            cout<<'\n';
        }*/
        
        for(auto y = 0; y<sizey;y++)
        {
            for(auto x = 0; x<sizex;x++)
            { 
                //cout<<"current: "<<x<<"x"<<y<<'\n';
                NewMap[x][y] = updateCoordinate(forrestMap,x,y);
            }
        }
        forrestMap = NewMap;

        tree = 0;
        lumberyards = 0;
        //cout << "\nFinal Round!\n";
        for(auto y = 0; y<sizey;y++)
        {
            for(auto x = 0; x<sizex;x++)
            {
                auto coordinate = forrestMap[x][y];
                if(coordinate == '|')
                {
                    tree++;
                }
                else if (coordinate == '#')
                {
                    lumberyards++;
                }
                
                //cout << coordinate;
            }
            //cout<<'\n';
        }
        cout<< minutes << " : "<< tree*lumberyards<<'\n';
    }
//}

   cout << "total resource value: "<< tree*lumberyards<<'\n';

    cout << "The question requires index: "<< (1000000000-407)%28<<'\n';

/*
    for(auto y = 0; y<sizey;y++)
    {
        for(auto x = 0; x<sizex;x++)
        {
            cout << Map[x][y];
        }
        cout<<'\n';
    }
*/
return 0;
}