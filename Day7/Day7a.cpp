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
    vector<char> Step;
    vector<char> Require;
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

    //sort(InputInst.begin(),InputInst.end());
    for(auto line : InputInst)
    {
        char step = *line.substr(line.find("step")+5,1).c_str();
        Step.push_back(step);
        char req = *line.substr(line.find("Step")+5,1).c_str();
        Require.push_back(req);
        //cout << "Step: " << step  << " Require " << req << '\n';
    }

    //cout << "Steps: " << Step << "\nRequires: " << Require <<'\n';
    vector<char> stepsList = Step;
    string answer;
    //string::iterator req_iter = Require.begin();
    //string::iterator step_iter = Step.begin();
    bool first = false;
    size_t PosA,PosB,ErasePos;
    vector<char> PossibleInstructions;
    while (!Require.empty())
    {
        vector<char>::iterator step_iter;
        vector<char>::iterator req_iter;
        
        for(auto start = 0U; start!=Require.size(); start++)
        {
            req_iter = Require.begin()+start;
            PosA=start;
            PosB=0;
            ErasePos=0;
            first = false;
            while(!first)
            {
                step_iter = find(Step.begin(),Step.end(),Require[PosA]);
                //PosB = PosA;
                if(step_iter != Step.end())
                {
                    PosA = distance(Step.begin(),step_iter);
                    req_iter = (Require.begin()+PosA);
                }
                else
                {
                    //cout<<"Found first\n"; 
                    first = true;
                }
            }
            
            PossibleInstructions.push_back(*req_iter);
            //cout<< "Get Value? : "<< *req_iter <<'\n';
        }

        sort( PossibleInstructions.begin(), PossibleInstructions.end() );
        PossibleInstructions.erase( unique( PossibleInstructions.begin(), PossibleInstructions.end() ), PossibleInstructions.end() );

/*
        cout << "Possible instructions: ";
        for(auto instructions : PossibleInstructions)
        {
            cout<<instructions<< " ";
        }
        cout << '\n';
        */
        req_iter = Require.begin();
        while(req_iter != Require.end())
        {
            req_iter = find(Require.begin(),Require.end(),PossibleInstructions[0]);
            
            if(req_iter != Require.end())
            {
                //cout<<"Removal of char: "<< *req_iter << " Eh: " << PossibleInstructions[0]<<'\n';
                Require.erase(req_iter);
                step_iter = (Step.begin()+ distance(Require.begin(),req_iter));
                Step.erase(step_iter);
            }
        }
        answer.append(string(1,PossibleInstructions[0]));
        PossibleInstructions.clear();
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