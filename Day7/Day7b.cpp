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
    workItem(int workitem, int require): workinstruction(workitem), requires(vector<int>(require)), timeLeft(60+workinstruction) {};
    workItem(int workitem): workinstruction(workitem), timeLeft(60+workinstruction) {};
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
        //cout<<"task: " <<item.workinstruction<<" Req: "<<requirement<<'\n';
        if(find(workDoneList.begin(),workDoneList.end(),requirement) == workDoneList.end())
        {
            return false;
        }
    }
    if (item.isDone() || item.Taken)
    {
        return false;
    }
    cout<<"TASK: "<< item.workinstruction<<" AVAILABLE"<<'\n';
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

    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    vector<char> Step;
    vector<char> RequiresList;
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
        RequiresList.push_back(req);
        Step.push_back(step);
        vector<workItem>::iterator iter = find_if(work.begin(), work.end(), [&] (const workItem & item) 
        { 
            cout << "item instruction: "<< item.workinstruction << " and charMap " << charMap[step]<< " Letter: "<< step<<'\n';
            return item.workinstruction == charMap[step]; 
        } );
        
        
        if(iter == work.end())
        {
        //cout<<"Add New! "<<charMap[step]<<'\n';
            cout<<"Add New! "<<step<<'\n';
            work.push_back(workItem(charMap[step]));
            iter = work.end()-1;
        }
        
        vector<int>::iterator req_iter = find((*iter).requires.begin(),(*iter).requires.end(),charMap[req]);
        if(req_iter==(*iter).requires.end())
        {
            (*iter).addRequirement(charMap[req]);
            //cout<<"Add existing! "<<charMap[req]<< '\n';
            cout<<"Add New requirement "<<req<< " on "<< (*iter).workinstruction <<'\n';
        }
        else
        {
            //cout<<charMap[req]<< " already there.. on " << (*iter).workinstruction<<"\n";
            cout<<req<< " already there.. on " << (*iter).workinstruction<<"\n";
        }

    }
    cout<<"The size! : "<< work.size()<<"\n";
    sort(RequiresList.begin(),RequiresList.end());
    sort(Step.begin(),Step.end());
    RequiresList.erase( unique(RequiresList.begin(), RequiresList.end()), RequiresList.end() );
    Step.erase( unique(Step.begin(), Step.end()), Step.end() );

    cout<<"printing lists!\n";
    cout << "Req: size=" << RequiresList.size()<<": ";
    for(auto rq :  RequiresList)
    {
        cout << rq << " ";
    }
    cout << "\nSteps: size="<<Step.size()<<": ";
    for (auto st : Step)
    {
        cout << st << " ";
    }
    cout << '\n';
    for(auto requirements : RequiresList)
    {
        if(find(Step.begin(),Step.end(),requirements)==Step.end())
        {
            cout<<"Final Add! : "<< charMap[requirements]<<"\n";
            work.push_back(workItem(charMap[requirements]));
        }
    }

    if (work.size() != 26)
    {   
        cout<<"The size! : "<< work.size()<<"\nNot correct size.\n";
        return 1;
    }

    sort(work.begin(),work.end(),[](auto &left, auto &right){return left.workinstruction<right.workinstruction;});
    for(auto workitem : work)
    {
        cout<<"WorkItem: "<< workitem.workinstruction <<"\nRequires: ";
        for(auto req : workitem.requires)
        {
            cout<< req << " ";
        }
        cout<<'\n';
    }


    bool allDone = false;
    int time = 0;
    int next_event = 0;
    int availableWorkers = 5;

    while(!allDone)
    {
        time +=next_event;
        cout<<"Timestamp: "<<time<<'\n';
        // Update of times
        for(auto &item : work)
        {
            if(item.Taken && !item.isDone())
            {
                item.reduceTime(next_event);
                cout<<"Reducing Time!, TimeLeft: "<<item.timeLeft<<'\n';   
                if(item.isDone())
                {
                    workDone.push_back(item.workinstruction);
                    availableWorkers++;
                    item.Taken = false;
                    cout<<"Task Done!\n";
                }
            }
            //cout<<"Current Time, Task: "<< item.workinstruction<< " and status: " <<item.isDone()<< " and Taken:"<< item.Taken<<'\n';
            cout<<"TimeLeft: "<<item.timeLeft<<'\n';    
        }

        allDone = true;
        next_event = 255;
        // Check of status
        for(auto &item : work)
        {
            if(!item.isDone())
            {
                allDone = false;
            }
            
            if((available(item,workDone) || (item.requires.empty() && !item.isDone() && !item.Taken)))
            {
                if(availableWorkers>0)
                {
                    cout<<"Taking new Task! << task: "<< item.workinstruction << " and free?: " << item.requires.empty()<< "\n";
                    item.Taken = true;
                    availableWorkers--;
                }
            }
        }

        for(auto &item : work)
        {
            //cout<<"Item: " << item.workinstruction << " timeLeft: " << item.timeLeft << " taken? " << item.Taken << " next event: "<< next_event <<"\n";
            if(item.timeLeft < next_event && item.Taken)
            {
                next_event = item.timeLeft;
                cout<<"set next event: " << next_event << "\n";
            }
        }
        if(next_event == 255)
        {
            next_event = 0;
        }
    }

    cout<<"TotalTime: "<<time<< " seconds\n";
    return 0;
} // CABDF