#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <math.h>
using namespace std;


int main()
{
    /* Open File and add it to vector. */
    string _line;
    int input = 505961;
    int Limit = 505961;

    vector <int> scoreBoard = {3,7};
    auto elf1_pos = 0U;
    auto elf2_pos = 1U;


    int iterations = 2;
    while(iterations<Limit+10)
    {
        int score1 = scoreBoard.at(elf1_pos);
        int score2 = scoreBoard.at(elf2_pos);
        int sum = score1 + score2;
        //cout<<"sum: "<<sum<<'\n';
        int step1 = score1+1;
        int step2 = score2+1;
        if(sum>=10)
        {
            scoreBoard.push_back(floor(sum/10));
        }
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
        iterations++;
    }
    cout<< "Answer: ";
    for(auto pos = 0;pos<10;pos++)
    {
        auto val = scoreBoard.begin()+Limit+pos;
        cout<< *val;
    }
    return 0;
}