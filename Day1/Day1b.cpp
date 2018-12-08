#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {

            DataLines.push_back(_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    
    int value = 0; 
    int TwiceFrequency = 0;
    bool TwiceFrequencyFound = false;
    vector<int> OldValues;
    while(!TwiceFrequencyFound)
    {
        for(auto line : DataLines)
        {
            char op = line[0];
            line.erase(line.begin());

            switch(op)
            {
                case '+':
                    value += stoi(line);
                    break;
                case '-':
                    value -= stoi(line);
                    break;
            }
            if(OldValues.empty())
            {
                OldValues.push_back(stoi(line));
            }
            else if ( find( OldValues.begin(), OldValues.end(), value) != OldValues.end())
            {
                TwiceFrequency = value;
                TwiceFrequencyFound = true;
                break;
            }
            else
            {
                OldValues.push_back(value);
            }
        }
    }
    cout << "The first double frequency was "<< value<<'\n';
    return 0;
}