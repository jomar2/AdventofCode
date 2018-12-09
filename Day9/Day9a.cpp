#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<pair<int,int>> Data;
    ifstream myfile ("input.txt");
    //ifstream myfile ("Examples.txt");
    int players,finalMarble;
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            players = stoi(_line.substr(0,3));
            int tmp2 = _line.find("worth");
            int tmp1 = _line.find("points")-(tmp2+5);

            finalMarble = stoi(_line.substr(tmp2+5,tmp1));
            Data.push_back(pair<int,int>(players,finalMarble));
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    // 10 players; last marble is worth 1618 points: high score is 8317
    //players = 13;
    //finalMarble = 7999;
    cout<<"Players: "<<players << " and final value: "<< finalMarble<<'\n'; 

    vector<int> circle(1);
    circle.reserve(finalMarble);
    vector<uint64_t> score(players);
    vector<uint64_t>::iterator score_iter = score.begin();
    vector<int>::iterator circ_iter = circle.begin();
    int currentMarble = 1;
    int RoundCount = 1;
    while(currentMarble!=finalMarble+1)
    {
        if(currentMarble%23==0)
        {
            //cout<<"Modulus 23!\n";
            *score_iter+=currentMarble;
            int dist = distance(circle.begin(),circ_iter);
            if(dist>=7)
            {
                circ_iter -= 7;
            }
            else
            {
                circ_iter = circle.end()-(7-dist);
            }
            *score_iter += *circ_iter;
            //++circ_iter;
            circle.erase(circ_iter);
        }
        else
        {
            ++circ_iter;
            if(circ_iter == circle.end())
            {
                circ_iter = circle.begin();
            }
            ++circ_iter;
            circle.insert(circ_iter,currentMarble);
        }
        


        
        ++score_iter;
        if (score_iter == score.end())
        {
            score_iter = score.begin();
        }
        // Visualization
    /*   cout<<"Round "<<RoundCount<<": ";
        for(int circ : circle)
        {   
            if(circ == currentMarble)
            {
                cout<<"("<<circ<<") ";
            }
            else
            {
                cout<<circ<<" ";    
            }
        }
        cout<<'\n';
        */
        currentMarble++;
        RoundCount++;
    }


    //int count = 1;
    /*for(auto points : score )
    {
        cout<<"Player "<<count<< ": " <<points<<"\n";
        count++;
    }*/
    cout<<"Winrar: "<<*max_element(score.begin(),score.end())<<'\n';
    return 0;
}