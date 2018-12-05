#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <array>

using namespace std;
class timeTableClass
{
    public:
    timeTableClass(){};
    int totalTime = {0};
    array<int,60> timeTable = {0};// = vector<int>(60);
};

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("myFile.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            DataLines.push_back(_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    
    
    cout<<"Number of lines: "<< DataLines.size() << '\n';

    /* Date is in the beginning of each line so a regular sort after numbers is working just fine. */
    sort(DataLines.begin(),DataLines.end());

    /* Variables used during parsing of each line. */    
    int idDelim;
    int timeDelim;
    int CurrentGuardID,start,timeAsleep,awake;


    vector<pair<int,timeTableClass*>> GuardDatabase; // the entries in the database is the pair (<ID>,<Amount of time sleeping in minutes>)
    vector<pair<int,timeTableClass*>>::iterator it;


    /* Go through the file and for each line do *one* action. */
    for (string line : DataLines)
    {
        idDelim = line.find("#");
        timeDelim = line.find(":");
        
        /* Check if the row contains a guard ID.*/
        if(idDelim != std::string::npos)
        {
            CurrentGuardID = stoi(line.substr(idDelim+1,4));
            /* Search the database for the ID and return the iterator to that object. */
            it = find_if(GuardDatabase.begin(),GuardDatabase.end(),[&](const std::pair<int, timeTableClass*>& element){return element.first == CurrentGuardID;} );
            if (it == GuardDatabase.end())
            {
                /* If new Guard: add the guard to the database and set the iterator to that object.*/
                GuardDatabase.emplace_back(make_pair(CurrentGuardID , new timeTableClass));
                it = GuardDatabase.end()-1;
            }

        }
        else if (line.find("asleep") != std::string::npos)
        {
            /* The guard fell asleep, log the time! */
            start = stoi(line.substr(timeDelim+1,2));
            //cout << "Asleep Time: " << start << "\n";
        }
        else if (line.find("wakes up") != std::string::npos)
        {
            /* The guard woke up, count the time spent asleep and add it to the iterator pair*/
            awake = stoi(line.substr(timeDelim+1,2));
            timeAsleep = stoi(line.substr(timeDelim+1,2)) - start;
            for(int i = start;i<awake;i++)
            {
                it->second->timeTable[i]++;
            }

            it->second->totalTime += timeAsleep;            
            //cout << "Time awoken: "<< awake << " Slept: " << timeAsleep << " ID: "<< it->first<< " Total: " << it->second << "\n";
        }
    }
    
    
    /* Sort the database according to the second element in the pair; minutes spent asleep */
    std::sort(GuardDatabase.begin(), GuardDatabase.end(), [](auto &left, auto &right) { return left.second->totalTime > right.second->totalTime;});
    
    /* Printouts for all of the guards */
    /*
    for(auto Guard : GuardDatabase)
    {
        //cout << "GuardID: " << Guard.first << " slept " << floor(Guard.second/60) << " Hours and "<< (Guard.second % 60) <<" Minutes\n";
        cout << "GuardID: " << Guard.first << " slept " <<Guard.second->totalTime <<" Minutes\n";
    }*/
    
    int maxTime =0;
    int maxID = 0;
    int maxOccurences =0;
    for(auto Guard : GuardDatabase)
    {
        auto maxIt = max_element(Guard.second->timeTable.begin(), Guard.second->timeTable.end());
        int maxOccurencesTmp = *maxIt;
        if(maxOccurencesTmp>maxOccurences)
        {
            maxID = Guard.first;
            maxOccurences = maxOccurencesTmp;
            maxTime = distance(Guard.second->timeTable.begin(),maxIt);
        }
    }
    //cout << "Winner! GuardID: " << GuardDatabase[0].first << " slept " << floor(GuardDatabase[0].second/60) << " Hours and "<< (GuardDatabase[0].second % 60) <<" Minutes\n";
    
    int time = distance(GuardDatabase[0].second->timeTable.begin(), max_element(GuardDatabase[0].second->timeTable.begin(), GuardDatabase[0].second->timeTable.end()));
    int Answer1 = GuardDatabase[0].first*time;
    int Answer2 = maxTime*maxID;
    cout << "First! GuardID: " << GuardDatabase[0].first << " slept " <<GuardDatabase[0].second->totalTime <<" Minutes and slept most at 00:"<<time <<", Answer 1: "<< Answer1 <<"\n";
    cout << "Second! GuardID: "<<maxID << " Time: 00:"<<maxTime<<", Answer 2: "<<Answer2 <<'\n';

    return 0;
}
