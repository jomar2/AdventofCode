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
    }
    cout << "The final frequency was "<< value<<'\n';
    return 0;
}