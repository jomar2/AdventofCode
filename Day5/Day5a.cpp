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
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        getline (myfile,_line);
        myfile.close();
    }
    else cout << "Unable to open file"; 
    cout<<"Start! Size of the string: " << _line.size() <<'\n';

    bool clean = false;
    string::iterator it;
    while (!clean)
    {
        clean = true;
        it = _line.begin();
        while(it !=_line.end())
        {
            if(   (tolower(*it) == tolower(*(it+1)))
               && (*it != *(it+1)))
            {
                clean = false;
                cout<<"Cut! : " << *it << " and "<< *(it+1) << '\n';
                _line.erase(it,it+2);
            }
            else
            {
                ++it;
            }
        }
    }
    
    cout<<"End! Size of the string: " << _line.size() <<'\n';
    return 0;
}