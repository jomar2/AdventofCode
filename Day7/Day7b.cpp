#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

class workItem
{
    public:
    int workinstruction;
    vector<int> requires;
    workItem(int workitem, int require): workinstruction(workitem), requires(vector<int>(1,require)), timeLeft(60+workinstruction) {}
    int timeLeft;
    bool isDone(){return timeLeft==0;};
    void addRequirement(int requirement){requires.push_back(requirement);};
    void reduceTime(int elapsedTime){timeLeft -= elapsedTime;};
    bool Taken = false;
};

bool available(workItem item,vector<int> workDoneList)
{
    for(auto requirement : item.requires)
    {
        cout<<"task: " <<item.workinstruction<<" Req: "<<requirement<<'\n';
        if(find(workDoneList.begin(),workDoneList.end(),requirement) == workDoneList.end())
        {

            return false;
        }
    } 
    cout<<"TASK: AVAILABLE"<<'\n';
    return true;
}


int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    map<char,int> charMap;

    string alphabeth = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    for (uint32_t index = 1; index<=alphabeth.size();index++)
    {
        charMap[alphabeth[index-1]] = index;
        //cout<<alphabeth[index-1]<<" = "<<index<<'\n';
    }

    //ifstream myfile ("input.txt");
    ifstream myfile ("test1.txt");
    vector<char> Step;
    vector<char> Require;
    vector<workItem> work;
    vector<string> InputInst;
    vector<int> workDone(0);

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            InputInst.push_back(_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    for(auto line : InputInst)
    {
        char step = line[36];
        char req = line[5];
        vector<workItem>::iterator iter = find_if(work.begin(), work.end(), [&] (const workItem & item) 
        { 
            //cout << "item instruction: "<< item.workinstruction << " and charMap " << charMap[step]<< " Letter: "<< step<<'\n';
            return item.workinstruction == charMap[step]; 
        } );
        
        
        if(iter != work.end())
        {
            //(*iter).addRequirement(charMap[req]);
            cout<<"Add existing!\n";
        }
        else
        {
            //cout<<"Add New!\n";
            work.push_back(workItem(charMap[step],charMap[req]));
        }
    }

    bool allDone = false;
    int time = 0;
    int next_event = 0;
    int availableWorkers = 5;
    while(!allDone)
    {
        allDone = true;
        time +=next_event;
        //cout<<"Timestamp: "<<time<<'\n';
        // Update of times
        for(auto item: work)
        {
            if(!item.isDone() && item.Taken)
            {
                item.reduceTime(next_event);
            }
        }
        // Check of status
        for(auto item: work)
        {
            if(item.isDone() && item.Taken)
            {
                workDone.push_back(item.workinstruction);
                availableWorkers++;
                item.Taken = false;
                cout<<"Task Done!\n";
            }
            else
            {
                allDone = false;
                if(available(item,workDone))
                {
                    if(availableWorkers>0)
                    {
                        cout<<"Taking new Task!\n";
                        item.Taken = true;
                        availableWorkers--;
                    }
                }
            }

            if(item.timeLeft<next_event && (item.Taken != 0))
            {
                next_event = item.timeLeft;
            }
        }
    }

    cout<<"TotalTime: "<<time<< " seconds\n";
    return 0;
} // CABDF