#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int ReduceFunction(string line)
{
    bool clean = false;
    string::iterator it;
    while (!clean)
    {
        clean = true;
        it = line.begin();
        while(it !=line.end())
        {
            if(   (tolower(*it) == tolower(*(it+1)))
               && (*it != *(it+1)))
            {
                clean = false;
                line.erase(it,it+2);
            }
            else
            {
                ++it;
            }
        }
    }
    
    return line.size();
}

int main()
{
    /* Open File and add it to vector. */
    string _line;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        getline (myfile,_line);
        myfile.close();
    }
    else cout << "Unable to open file"; 
    cout<<"Start! Size of the string: " << _line.size() <<'\n';
    int minSize = _line.size();
    string alphabeth = {"abcdefghijklmnopqrstuvwxyz"};
    for(auto ch : alphabeth)
    {
        string tmpstring = _line;
        tmpstring.erase( std::remove( tmpstring.begin(), tmpstring.end(), ch ), tmpstring.end() );
        tmpstring.erase( std::remove( tmpstring.begin(), tmpstring.end(), toupper(ch) ), tmpstring.end() );
        int minSizeTmp = ReduceFunction(tmpstring);
        if(minSize>minSizeTmp)
        {
            minSize = minSizeTmp;
        }
    }
    cout<<"End! Size of the string: " << minSize <<'\n';
}

