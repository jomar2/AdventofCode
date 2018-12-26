
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

using namespace std;

enum inst
{
    addr = 0,
    addi,
    mulr,
    muli,
    banr,
    bani,
    borr,
    bori,
    setr,
    seti,
    gtir,
    gtri,
    gtrr,
    eqir,
    eqri,
    eqrr
};

void runInstr (vector<int> &registers,vector<int> programInstructions,map<int,int> ConfirmedFunc)
{
    int instruction = programInstructions[0];
    int ValA = programInstructions[1];
    int ValB = programInstructions[2];
    int ValC = programInstructions[3];
    switch (ConfirmedFunc[instruction])
    {
        case inst::addr:
            registers[ValC] = registers[ValA] + registers[ValB];
            break;
        case inst::addi:
            registers[ValC] = registers[ValA] + ValB;
            break;
        case inst::mulr:
            registers[ValC] = registers[ValA] * registers[ValB];
            break;
        case inst::muli:
            registers[ValC] = registers[ValA] * ValB;
            break;
        case inst::banr:
            registers[ValC] = registers[ValA] & registers[ValB];
            break;
        case inst::bani:
            registers[ValC] = registers[ValA] & ValB;
            break;
        case inst::borr:
            registers[ValC] = registers[ValA] | registers[ValB];
            break;
        case inst::bori:
            registers[ValC] = registers[ValA] | ValB;
            break;
        case inst::setr:
            registers[ValC] = registers[ValA];
            break;
        case inst::seti:
            registers[ValC] = ValA;
            break;
        case inst::gtir:
            registers[ValC] =  ValA > registers[ValB];
            break;
        case inst::gtri:
            registers[ValC] = registers[ValA] > ValB;
            break;
        case inst::gtrr:
            registers[ValC] = (registers[ValA] > registers[ValB]);
            break;
        case inst::eqir:
            registers[ValC] = (ValA == registers[ValB]);
            break;
        case inst::eqri:
            registers[ValC] = (registers[ValA] == ValB);
            break;
        case inst::eqrr:
            registers[ValC] = registers[ValA] == registers[ValB];
            break;
    }
}


    
int FunctionTester(vector<int> BeforeRegs, vector<int> AfterRegs, vector<int> Inst, map<int, int> &ConfirmedInstructions)
{
    int instruction = Inst[0];
    vector<int> tmpInstructions;

    set<int> confirmedFuncs;

    for (auto funcs : ConfirmedInstructions)
    {
        confirmedFuncs.emplace(funcs.second);
    }

    /*cout << "confirmed functions: ";
    for (auto func : confirmedFuncs)
    {
        cout << func << " ";
    }
    cout << '\n';*/

    int ValA = Inst[1];
    int ValB = Inst[2];
    int ValC = Inst[3];
    int matches = 0;
    // Addr
    int Addr = BeforeRegs[ValA] + BeforeRegs[ValB];
    if(Addr == AfterRegs[ValC])
    {
        if(confirmedFuncs.find(inst::addr)==confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::addr);
        }
    }   
    // Addi
    int Addi = BeforeRegs[ValA] + ValB;
    if(Addi == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::addi) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::addi);
        }
    }
    // Mulr
    int Mulr = BeforeRegs[ValA] * BeforeRegs[ValB];
    if(Mulr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::mulr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::mulr);
        }    
    }
    // Muli
    int Muli = BeforeRegs[ValA] * ValB;
    if(Muli == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::muli) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::muli);
        }
    }
    // Banr
    int Banr = BeforeRegs[ValA] & BeforeRegs[ValB];
    if(Banr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::banr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::banr);
        }
    }
    // Bani
    int Bani = BeforeRegs[ValA] & ValB;
    if(Bani == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::bani) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::bani);
        }
    }
    // Borr
    int Borr = BeforeRegs[ValA] | BeforeRegs[ValB];
    if(Borr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::borr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::borr);
        }
    }
    // Bori
    int Bori = BeforeRegs[ValA] | ValB;
    if(Bori == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::bori) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::bori);
        }
    }
    // Setr
    int Setr = BeforeRegs[ValA];
    if(Setr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::setr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::setr);
        }
    }
    // Seti
    int Seti = ValA;
    if(Seti == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::seti) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::seti);
        }
    }
    // Gtir
    int Gtir = (int) ValA > BeforeRegs[ValB];
    if(Gtir == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::gtir) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::gtir);
        }
    }
    // Gtri
    int Gtri = (int) BeforeRegs[ValA] > ValB;
    if(Gtri == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::gtri) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::gtri);
        }
    }
    // Gtrr
    int Gtrr = (int) BeforeRegs[ValA] > BeforeRegs[ValB];
    if(Gtrr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::gtrr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::gtrr);
        }
    }
    // Eqir
    int Eqir = ValA == BeforeRegs[ValB];
    if(Eqir == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::eqir) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::eqir);
        }
    }
    // Eqri
    int Eqri = BeforeRegs[ValA] == ValB;
    if(Eqri == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::eqri) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::eqri);
        }
    }
    // Eqrr
    int Eqrr = BeforeRegs[ValA] == BeforeRegs[ValB];
    if(Eqrr == AfterRegs[ValC])
    {
        if (confirmedFuncs.find(inst::eqrr) == confirmedFuncs.end())
        {
            tmpInstructions.push_back(inst::eqrr);
        }
    }

    if (tmpInstructions.size() == 1)
    {
        //Verified instruction:
        ConfirmedInstructions[instruction] = tmpInstructions[0];
    }
    

    //cout << "Instruction: " << instruction << " validOps: " << matches << '\n';


    return matches;
}

int main()
{
    /* Open File and add it to vector. */
    /* Too low: 393, 618 correct. */
    /* 1 0 4 1 : 1 NOC, 0 NOC*/
    string _line;
    vector<string> DataLines;
    vector<vector<int>> registersBefore;
    vector<vector<int>> registersAfter;
    vector<vector<int>> instructions;
    vector<vector<int>> program;

    ifstream myfile ("input.txt");
    ifstream myProgram ("input2.txt");
    //ifstream myfile ("test1.txt");
    //ifstream myfile("test2.txt");
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

    if(myProgram.is_open())
    {
        while (getline(myProgram, _line))
        {
            if (!_line.empty())
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

                program.emplace_back(instruct);
            }
        }
        myProgram.close();
    }



    else cout << "Unable to open file"; 

    cout << "We have "<<registersBefore.size() << ", "<<registersAfter.size()<<", "<<instructions.size()<<'\n';
    map<int,int> ConfirmedFunctions;

    for (auto entry = 0U;ConfirmedFunctions.size() != 16;entry++)
    {
        if(entry == registersBefore.size())
        {
            entry = 0U;
        }
        FunctionTester(registersBefore[entry], registersAfter[entry], instructions[entry], ConfirmedFunctions);
    }

    cout << "Instruction Pairs:\n";
    for (auto instPairs : ConfirmedFunctions)
    {
        cout << "opCode: "<<instPairs.first<< " = "<<instPairs.second<<'\n';
    }

    vector<int> registers{0,0,0,0};
    for(auto programInstr : program)
    {
        runInstr(registers, programInstr,ConfirmedFunctions);
    }


    cout << "Ans: "<<registers[0] << '\n';

    for(auto reg : registers)
    {
        cout<<reg<< " ";
    }
    cout<<'\n';
}