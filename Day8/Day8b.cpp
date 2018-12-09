#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;

void getMetaData(vector<int>::iterator & input,vector<uint32_t> & result)
{
    vector<int> MetaData(0);
    vector<uint32_t> MetaDataRes,MetaDataTmp;
    vector<int> whichMetaData,countVector;

    int numChildren = *input;
    int numMetaData = *(input+1);
    cout<<"Children: "<< numChildren <<" and MetaData: "<<numMetaData<<'\n';
    
    if(numChildren == 0)
    {
        input += 2;
        for(int val = 0; val<numMetaData;val++)
        {
            MetaDataRes.push_back(*input);
            input++;
        }
        
        int sum = accumulate(MetaDataRes.begin(), MetaDataRes.end(), 0);
        result.push_back(sum);
        cout<<"Direct return with value: "<<sum<<'\n';
        return;
    }

    input += 2;
    
    for(int i = 0; i<numChildren;i++)
    {
        getMetaData(input,MetaDataTmp);
        cout<<i<<": Child Return with value: "<<MetaDataTmp.at(i)<<'\n';
        
        MetaDataRes.push_back(MetaDataTmp[i]);
        cout<<"Pushed Data: "<<MetaDataTmp[i]<<'\n';        

    }
    cout<<"Size of MetaDataRes: "<<MetaDataRes.size()<<'\n';

    for(int inst = 0; inst<numMetaData;inst++)
    {
        int data = *input;
        input++;
        cout<< "Lets Add : "<<data<< " ";
        int value = 0;
        if(data<=numChildren)
        {
            value = MetaDataRes[data-1];
            cout<< "Data: "<<value<<" ";
        }
        cout<< "\n";
        countVector.push_back(value);
    }

    result.push_back(accumulate(countVector.begin(), countVector.end(), 0));
    cout<<"Return!\n ";
    return;
};

int main()
{
    /* Open File and add it to vector. */
    vector<string> DataLines;
    vector<int> input;
    string _line;
    //ifstream myfile ("test2.txt");
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
    vector<uint32_t> result;
    getMetaData(input_iter,result);
    uint32_t total = 0;
   /* for(auto inp : input)
    {
        cout<<inp<<" ";
    }*/
    cout<<"\nResults: ";
    for(auto res : result)
    {
        total+=res;
        cout<<res<<" ";
    }
    cout << '\n';

    cout<<"Total: "<<total<<'\n';
    return 0;
}