#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

char getInstruction(string & chunk, vector<pair<string,string>> & instructionList)
{   
    for(auto instr : instructionList)
    {
        //cout<<"Check of :" << chunk << " against " << instr.first<<'\n';
        if(chunk == instr.first)
        {
            //cout<<"Found instruction: "<< instr.second[0]<<'\n';
            return instr.second[0];
        }
    }

    return '.';
}


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {

            DataLines.push_back(_line);

        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    int pos1 = DataLines[0].find(":");
    string state = DataLines[0].substr(pos1+2,98);
    state.reserve(1400);
    cout<< "initState: " << state <<'\n';
    //string::iterator Position0 = state.begin();
    cout<<"Size 1: "<<state.size()<<'\n'; 

    vector<pair<string,string>> instructions;

    for(auto str_iter = (DataLines.begin()+2);str_iter!=DataLines.end();++str_iter)
    {
        auto parse_p1 = (*str_iter).find(" => ");
        auto inst = (*str_iter).substr(0,parse_p1);
        auto result = (*str_iter).substr(parse_p1+4);
        cout<< "instruction: " << inst <<" and result: "<<result<<'\n';
        instructions.push_back(pair<string,string>(inst,result));
    }
    cout<<"in the vector:\n";
    for(auto inst : instructions)
    {
        //cout<< "instruction: " << inst.first <<" and result: "<<inst.second<<'\n';
    }

    auto valueOfFirst = 0;
    for(long long generation = 1;generation<=10000; generation++)
    {
        auto first = state.find("#");
        //cout<<"state: "<< state<<'\n';
        while (first<4)
        {
            state.insert(state.begin(),'.');
            first = state.find("#");
            valueOfFirst--;
            //cout<<"first value: "<<valueOfFirst<<'\n';  
        }
        //cout<<"state: "<< state<<'\n';
        auto last = state.find_last_of("#");

        while((state.size()-last)<5)
        {
            //cout<<"Adding!:"<<last<<" size: " << state.size()<<endl;
            state.insert(state.end(),'.');
            last = state.find_last_of("#");
        }
        //cout<<"state: "<< state<<'\n';
        /*cout<<"Content: \n";    
        for(auto i : state)
        {
            cout<<i;
        }
        cout<<"\nNewState: \n"<<state<<'\n';
        */

        string newString = string(state.size(),'.');
        auto newString_iter = newString.begin();
        for(auto state_iter = state.begin();state_iter != state.end()-5;++state_iter)
        {
            string chunk = string(state_iter,state_iter+5);
            *(newString_iter+2) = getInstruction(chunk,instructions);
            newString_iter++;
        }
        state = newString;
        //cout<<"Gen: "<< generation << " " <<state<<'\n';
        //cout<<"Gen: "<< generation;
    }
    long long totalSum = 0;
    for(auto chr : state)
    {
        if(chr == '#')
        {
            totalSum +=valueOfFirst;
        }
        valueOfFirst++;
    }

    cout << "total: "<<totalSum<< '\n';
    return 0;
}