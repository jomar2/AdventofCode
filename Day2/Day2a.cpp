#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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


    cout<<"Lines: " <<DataLines.size()<<'\n';

    int NumberOfPairs = 0;
    int NumberOfThrice = 0;
    for(auto line : DataLines)
    {
        bool foundDouble = false;
        bool foundTriple = false;
        //cout <<"Newline!\n";
        while(!line.empty())
        {
            auto c = line.at(0);
            int num_c = std::count(line.begin(), line.end(), c);
            //cout <<"char: "<<c<<"! before: "<< line << '\n';
            line.erase( std::remove( line.begin(), line.end(), c ), line.end() );
            //cout <<"after: "<< line << '\n';
            if (num_c == 2)
            {
                //cout <<"Double!\n";
                foundDouble = true;
            }
            else if (num_c == 3)
            {
                //cout <<"Triple!\n";
                foundTriple = true;
            }
        }
        if(foundDouble)
        {
            NumberOfPairs++;
        }
        
        if(foundTriple)
        {
            NumberOfThrice++;
        }
    }
    cout << "Number of Pairs: "<< NumberOfPairs << " and triplets: "<< NumberOfThrice << " makes checksum: " << NumberOfPairs*NumberOfThrice <<'\n';
}