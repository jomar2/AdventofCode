#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <math.h>
#include <sstream>
#include <iterator>
using namespace std;


int main()
{
    // Wrong ans: 270157146 Too High
    /* Open File and add it to vector. */
    string _line;
    int input = 505961;
    string inputStr = "505961";
    //string inputStr = "51589";
    //string inputStr = "01245";
    //string inputStr = "92510";
    //string inputStr = "59414";
    int Limit = 10;

    vector <int> scoreBoard = {3,7};
    scoreBoard.reserve(5000);
    string scoreBoardString = "37";
    auto elf1_pos = 0U;
    auto elf2_pos = 1U;



    int recepie = 2;
    bool found = false;
    auto strAdj = inputStr.size();
    while(!found)
    {
        int extras = 0;
        int score1 = scoreBoard.at(elf1_pos);
        int score2 = scoreBoard.at(elf2_pos);
        int sum = score1 + score2;
        //cout<<"sum: "<<sum<<'\n';
        int step1 = score1+1;
        int step2 = score2+1;
        if(sum>=10)
        {
            scoreBoard.push_back(floor(sum/10));
            extras++;
            //scoreBoardString.append(to_string(int(floor(sum/10))));
        }
        //scoreBoardString.append(to_string(sum % 10));
        scoreBoard.push_back(sum % 10);

        //cout<<"steps: "<<step1<<" "<<step2<<'\n';
        for(int steps = 0; steps<step1;steps++)
        {
            ++elf1_pos;
            if (elf1_pos == scoreBoard.size())
            {
                //cout<<"loop! 1\n";
                elf1_pos = 0;
            }
        }

        for(int steps = 0; steps<step2;steps++)
        {
            ++elf2_pos;
            if (elf2_pos == scoreBoard.size())
            {
                //cout<<"loop! 2\n";
                elf2_pos = 0;
            }
        }
        //cout<<scoreBoardString<<'\n';
/*
        for(auto pos = 0U;pos<scoreBoard.size();pos++)
        {
            int score = scoreBoard.at(pos);
            if (pos == elf1_pos)
            {
                cout<< "(" << score << ")";
            }
            else if (pos == elf2_pos)
            {
                cout<< "[" << score << "]";
            }
            else
            {
                cout<<" " << score << " ";
            }
        }
        cout<<'\n';
                */
        if(scoreBoard.size()>(strAdj+extras))
        {
            std::stringstream result;
            recepie = scoreBoard.size();
            std::copy(scoreBoard.end()-(strAdj+extras), scoreBoard.end(), std::ostream_iterator<int>(result, ""));
            string scoreBoardString = result.str();
            //cout<< scoreBoardString <<'\n';
            if(scoreBoardString.find(inputStr) != string::npos)
            {
                found = true;
                cout<<"found after recepie: " << recepie-(strAdj+extras) <<'\n';     
            };
        }
    }
    /*cout<< "Answer: ";
    for(auto pos = 0;pos<10;pos++)
    {
        auto val = scoreBoard.begin()+Limit+pos;
        cout<< *val;
    }*/
    return 0;
}