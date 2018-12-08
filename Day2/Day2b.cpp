#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


bool difference(string & input1, string & input2)
{
    int diff = 0;
    string::iterator it = input2.begin();
    string::iterator badChar_it;
    //cout <<"Newline!\n";
    for( auto ch : input1)
    {
        if(ch != *it)
        {
            badChar_it = it;
            diff++;
        }
        ++it;
    }

    if(diff==1)
    {
        cout<<"BadMF: "<<*badChar_it<<'\n';
        cout<<"line1: "<<input1<<'\n';
        cout<<"line2: "<<input2<<'\n';
        input2.erase(badChar_it);
        return true;
    }
    return false;
}

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


    cout<<"Lines: " <<DataLines.size()<<'\n';

    int NumberOfPairs = 0;
    int NumberOfThrice = 0;
    string BoxID;
    char badCharacter;
    string::iterator it;
    vector<string>::iterator vec_it = DataLines.begin();
    vector<string>::iterator vec_it_2;
    for(auto line : DataLines)
    {
        vec_it_2 = vec_it;
        while(vec_it_2 != DataLines.end())
        {
            if(difference(line,*vec_it_2) == true)
            {
                BoxID = line;
                cout << "BoxID: "<< *vec_it_2 << '\n';
                return 0;
            }
            ++vec_it_2;
        }
        vec_it++;
    }
    cout << "No box for you!\n";
    return 0;
}