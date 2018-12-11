#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int powa(int x,int y,int puzzleID)
{
    string lvl;
    int rackID = (x+10);
    int digit =  ((rackID*y+puzzleID)*rackID%1000)/100;
    //lvl = string(to_string(int (rackID*y+puzzleID)*rackID));
    //
    int answer = digit-5;
    //cout<< "digit: "<< digit << " level!: " << lvl << " RackID: "<<rackID<<" Answer: "<< answer<<'\n';

    return answer;
    //return stoi(string(1,*((string(to_string(int ((x+10)*y+puzzleID)*(x+10)))).end()-3)))-5;
}

int powerCell(int x,int y,int puzzleID,int size)
{
    int total = 0;
    for(int sub_x= 0;sub_x<size;sub_x++)
    {
        for(int sub_y= 0;sub_y<size;sub_y++)
        {
            total += powa(x+sub_x,y+sub_y,puzzleID);
            //cout << "Current Total: "<<total<<'\n';
        }
    }
    //cout << "Final ans: "<<total<<'\n';
    return total;
}

int main()
{
    int puzzleinput = 3628; //  Mine
    //int puzzleinput = 5153; // Not Mine
    int gridsize= 301;
    cout <<"More POWA!!: "<<  powa(3,5,8)<<'\n';

/*Fuel cell at  122,79, grid serial number 57: power level -5.
  Fuel cell at 217,196, grid serial number 39: power level  0.
  Fuel cell at 101,153, grid serial number 71: power level  4.*/

  if(   (powa(122,79,57)  !=-5)
     || (powa(217,196,39) !=0)   
     || (powa(101,153,71) !=4))
    {
        cout << "Fail!" <<'\n';
    }
    else
    {
       cout << "Sucksess!!" <<'\n';
    }

    vector<vector<int>> grid(gridsize,vector<int>(gridsize));
    int maxPowa = 0;
    pair<int,int> maxPos;
    int CurrPowa = 0;
    int maxSize = 0;
    for(int grid_size=1;grid_size<=300;grid_size++)
    {
        for(int grid_x = 1;grid_x <= gridsize-grid_size;grid_x++)
        {
            for(int grid_y = 1;grid_y <= gridsize-grid_size;grid_y++)
            {
                CurrPowa = powerCell(grid_x,grid_y,puzzleinput,grid_size);
                if (CurrPowa>maxPowa)
                {
                    maxPowa = CurrPowa;
                    maxPos = pair<int,int>(grid_x,grid_y);
                    maxSize = grid_size;
                }
            }
        }
        cout<<"CurrentGrid: " << grid_size<<'\n';
    }

    cout << "Final Answer, MaxPowa!: "<< maxPowa<< " at: " << maxPos.first<<"x"<<maxPos.second<< " using the size: "<< maxSize<<'\n'; 


    return 0;   
}