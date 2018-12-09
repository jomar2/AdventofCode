#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> getMetaData(vector<int>::iterator & input)
{
    vector<int> MetaData;
    vector<int> MetaDataRes;
    int numChildren = *input;
    int numMetaData = *(input+1);
    cout<<"Children: "<< numChildren <<" and MetaData: "<<numMetaData<<'\n';
    
    input += 2;
    for(int i = 0; i<numChildren;i++)
    {
        MetaDataRes = getMetaData(input);
        MetaData.insert(std::end(MetaData), std::begin(MetaDataRes), std::end(MetaDataRes));;
    }
    MetaData.insert(end(MetaData),input,input+numMetaData);
    input+=numMetaData;
    for(auto data: MetaData)
    {
        cout<< "Data: "<<data<<" ";

    }
    cout<<'\n';
    return MetaData;

};

int main()
{
    /* Open File and add it to vector. */
    vector<string> DataLines;
    vector<int> input;
    string _line;
    //ifstream myfile ("test.txt");
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        getline (myfile,_line);
        myfile.close();
    }
    else cout << "Unable to open file"; 
    
    stringstream lineStream(_line);
    int entry;
    while(!lineStream.eof())
    {
        lineStream>>entry;
        input.push_back(entry);
    }

    vector<int>::iterator input_iter = input.begin();
    vector<int> result = getMetaData(input_iter);
    int total = 0;
    for(auto inp : input)
    {
        cout<<inp<<" ";
    }
    cout<<"Results: ";
    for(auto res : result)
    {
        total+=res;
        cout<<res<<" ";
    }
    cout << '\n';

    cout<<"Total: "<<total<<'\n';
    return 0;
}