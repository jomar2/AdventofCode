#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;


int Addition (vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Addr
    int Addr = BeforeRegs[ValA] + BeforeRegs[ValB];
    matches += ((Addr == AfterRegs[ValC]) ? 1:0);
    // Addi
    int Addi = BeforeRegs[ValA] + ValB;
    matches += ((Addi == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int Multiplication(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Mulr
    int Mulr = BeforeRegs[ValA] * BeforeRegs[ValB];
    matches += ((Mulr == AfterRegs[ValC]) ? 1 : 0);
    // Muli
    int Muli = BeforeRegs[ValA] * ValB;
    matches += ((Muli == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int BWAnd(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Banr
    int Banr = BeforeRegs[ValA] & BeforeRegs[ValB];
    matches += ((Banr == AfterRegs[ValC]) ? 1:0);
    // Bani
    int Bani = BeforeRegs[ValA] & ValB;
    matches += ((Bani == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int BWOr(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst) 
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Borr
    int Borr = BeforeRegs[ValA] | BeforeRegs[ValB];
    matches += ((Borr == AfterRegs[ValC]) ? 1:0);
    // Bori
    int Bori = BeforeRegs[ValA] | ValB;
    matches += ((Bori == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int Assignment(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    // int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Setr
    int Setr = BeforeRegs[ValA];
    matches += ((Setr == AfterRegs[ValC]) ? 1:0);
    // Seti
    int Seti = ValA;
    matches += ((Seti == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int GreaterThan(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Gtir
    int Gtir = (int) ValA > BeforeRegs[ValB];
    matches += ((Gtir == AfterRegs[ValC]) ? 1:0);
    // Gtri
    int Gtri = (int) BeforeRegs[ValA] > ValB;
    matches += ((Gtri == AfterRegs[ValC]) ? 1 : 0);
    // Gtrr
    int Gtrr = (int) BeforeRegs[ValA] > BeforeRegs[ValB];
    matches += ((Gtrr == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

int Equality(vector<int>  BeforeRegs, vector<int> AfterRegs,  vector<int> Inst)
{
    
    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Eqir
    int Eqir = ValA == BeforeRegs[ValB];
    matches += ((Eqir == AfterRegs[ValC]) ? 1 : 0);
    // Eqri
    int Eqri = BeforeRegs[ValA] == ValB;
    matches += ((Eqri == AfterRegs[ValC]) ? 1 : 0);
    // Eqrr
    int Eqrr = BeforeRegs[ValA] == BeforeRegs[ValB];
    matches += ((Eqrr == AfterRegs[ValC]) ? 1 : 0);
    return matches;
}

bool testFunc(vector<int> BeforeRegs, vector<int> AfterRegs, vector<int> Inst)
{
    int instruction = Inst[0];

    int numberOfValidOps = 0;

    numberOfValidOps += Multiplication(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += BWOr(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += BWAnd(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += Addition(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += Equality(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += Assignment(BeforeRegs, AfterRegs, Inst);
    numberOfValidOps += GreaterThan(BeforeRegs, AfterRegs, Inst);
    cout << "Instruction: " << instruction << " validOps: " << numberOfValidOps << '\n';
    return (numberOfValidOps >= 3);
}

int main()
{
    /* Open File and add it to vector. */
    /* Too low: 393 */
    string _line;
    vector<string> DataLines;
    vector<vector<int>> registersBefore;
    vector<vector<int>> registersAfter;
    vector<vector<int>> instructions;
    ifstream myfile ("input.txt");
    //ifstream myfile ("test1.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            string reg0,reg1,reg2,reg3;
            if (int pos1 = _line.find("Before:") != string::npos)
            {
                istringstream lineStream(_line.substr(pos1+8));
                // cout <<"Before line: "<< _line.substr(pos1 + 8)<<'\n';
                getline(lineStream, reg0, ',');
                getline(lineStream, reg1, ',');
                getline(lineStream, reg2, ',');
                getline(lineStream, reg3, ']');
                vector<int> vect{stoi(reg0),stoi(reg1),stoi(reg2),stoi(reg3)};
                registersBefore.emplace_back(vect);
                // cout << "before vect: " << reg0 << " " << reg1 << " " << reg2 << " " << reg3 << " " << '\n';
            }
            else if (int pos1 = _line.find("After:") != string::npos)
            {
                // cout << "After line: " << _line.substr(pos1 + 8)<<'\n';
                istringstream lineStream(_line.substr(pos1 + 8));
                getline(lineStream, reg0, ',');
                getline(lineStream, reg1, ',');
                getline(lineStream, reg2, ',');
                getline(lineStream, reg3, ']');

                vector<int> vect{stoi(reg0), stoi(reg1), stoi(reg2), stoi(reg3)};
                registersAfter.emplace_back(vect);

                // cout << "After vect: " << reg0 << " " << reg1 << " " << reg2 << " " << reg3 << " " << '\n';
            }
            
            else if ( !_line.empty() )
            {
                // cout << "inst line:" << _line<<'\n';
                istringstream lineStream(_line);
                vector<int> instruct;
                string instr_part;
                while (getline(lineStream, instr_part, ' '))
                {
                    instruct.emplace_back(stoi(instr_part));
                }
                /* cout << "Instructions: ";
                for(int inst : instruct)
                {
                    cout << inst <<" ";
                }
                cout << '\n';*/

                instructions.emplace_back(instruct);
            }

            //Data.push_back(TargetCoordinate(pair<int, int>(stoi(pos_x), stoi(pos_y))));
            //DataLines.push_back(_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "We have "<<registersBefore.size() << ", "<<registersAfter.size()<<", "<<instructions.size()<<'\n';

    int numOpsOver3 = 0;
    for (auto entry = 0U;entry<instructions.size();entry++)
    {
        numOpsOver3 += (testFunc(registersBefore[entry], registersAfter[entry], instructions[entry])) ? 1:0;
    }
    cout << "ans: "<<numOpsOver3<<'\n';

}