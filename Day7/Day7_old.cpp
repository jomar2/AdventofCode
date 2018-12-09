#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_set>
using namespace std;

// Ska börja på H
int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    string Step, Require= "";
    vector<pair<string,string>> Instructions;
    vector<string> InputInst;

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            InputInst.push_back(_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    sort(InputInst.begin(),InputInst.end());
    for(auto line : InputInst)
    {
        Step.append(line.substr(line.find("step")+5,1));
        Require.append(line.substr(line.find("Step")+5,1));
        //cout << "Step: " << Step  << " Require " << Require << '\n';
    }

    cout << "Steps: " << Step << "\nRequires: " << Require <<'\n';
    string stepsList = Step;
    string answer;
    //string::iterator req_iter = Require.begin();
    //string::iterator step_iter = Step.begin();
    bool first = false;
    size_t PosA,PosB,ErasePos;
    while (!Require.empty())
    {
        PosA=0;
        PosB=0;
        ErasePos=0;
        first = false;
        while(!first)
        {
            PosA = Step.find(Require[PosA]);
            //cout<<"ehh: " << PosA <<'\n';
            cout<<"Strings Req: "<< Require[PosA]<<'\n';
            cout<<"Strings Step: "<< Step[PosA]<<'\n';
            if(PosA != string::npos)
            {
                PosB = PosA;
            }
            else
            {
                first = true;
            }
        }
        //cout<< "Get Value? : "<< Require[PosB] <<'\n';
        ErasePos= PosB;
        answer.append(string(1,Require[PosB]));
        string Instr = string(1,Require[PosB]);

        while(ErasePos != string::npos)
        {
            ErasePos = Require.find(Instr);
            if(ErasePos != string::npos)
            {
                cout<<"Removal of char: "<< *(Require.begin()+ErasePos) << '\n';
                cout<<"Before: "<<  Require <<'\n';
                Require.erase(Require.begin()+ErasePos);
                cout<<"After: "<<  Require <<'\n';
                Step.erase(Step.begin()+ErasePos);
            }
        }
    }

    for(auto instr : stepsList)
    {
        if(answer.find(instr) == string::npos)
        {  
            answer.append(string(1,instr));
        }
    }

    cout <<"Answer: "<< answer<< '\n';

    return 0;
} // CABDF