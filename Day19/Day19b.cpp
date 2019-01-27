
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

class instruction
{
    public:
    instruction(string NameIn,int RegA,int RegB,int RegC): name(NameIn), registerA(RegA),registerB(RegB),registerC(RegC){}
    string name;
    int registerA;
    int registerB;
    int registerC;
};

void runInstr (vector<long> &registers,instruction Instruction,int ipRegister,int & ip)
{
    string instruction = Instruction.name;
    int ValA = Instruction.registerA;
    int ValB = Instruction.registerB;
    int ValC = Instruction.registerC;
    
    if (instruction == "addr") 
    {
        registers[ValC] = registers[ValA] + registers[ValB];
    }
    else if (instruction == "addi") 
    {
        registers[ValC] = registers[ValA] + ValB;
    }
    else if (instruction == "mulr") 
    {
        registers[ValC] = registers[ValA] * registers[ValB];
    }
    else if (instruction == "muli") 
    {
        registers[ValC] = registers[ValA] * ValB;
    }
    else if (instruction == "banr")
    {
        registers[ValC] = registers[ValA] & registers[ValB];
    }
    else if (instruction == "bani")
    {
        registers[ValC] = registers[ValA] & ValB;

    }
    else if (instruction == "borr")
    {
        registers[ValC] = registers[ValA] | registers[ValB];

    }
    else if (instruction == "bori")
    {
        registers[ValC] = registers[ValA] | ValB;

    }
    else if (instruction == "setr")
    {
        registers[ValC] = registers[ValA];
    }
    else if (instruction == "seti")
    {
        registers[ValC] = ValA;

    }
    else if (instruction == "gtir")
    {
        registers[ValC] =  ValA > registers[ValB];

    }
    else if (instruction == "gtri")
    {
        registers[ValC] = registers[ValA] > ValB;

    }
    else if (instruction == "gtrr")
    {
        registers[ValC] = (registers[ValA] > registers[ValB]);

    }
    else if (instruction == "eqir")
    {
        registers[ValC] = (ValA == registers[ValB]);

    }
    else if (instruction == "eqri")
    {
        registers[ValC] = (registers[ValA] == ValB);

    }
    else if (instruction == "eqrr")
    {
        registers[ValC] = registers[ValA] == registers[ValB];

    }
    ip = registers[ipRegister];
    ip++;
}

int main()
{
    string _line;
    vector<string> DataLines;
    vector<vector<int>> registersBefore;
    vector<vector<int>> registersAfter;
    vector<vector<int>> instructions;
    vector<instruction> program;
    int ip_register;

    //ifstream myfile ("input.txt");
    //ifstream myProgram ("test1.txt");
     ifstream myProgram ("input.txt");

    
    if(myProgram.is_open())
    {
        while (getline(myProgram, _line))
        {
            if (!_line.empty())
            {
                // cout << "inst line:" << _line<<'\n';
                istringstream lineStream(_line);
                vector<string> instruct;
                string instr_part;
                if(auto pos = _line.find("#ip") != string::npos)
                {
                    ip_register = stoi(_line.substr(pos+3));
                    cout<<"IP Register" << ip_register<<"\n";
                }
                else
                {
                    while(getline(lineStream, instr_part, ' '))
                    {
                        instruct.emplace_back(instr_part);
                    }
                    program.emplace_back(instruction(instruct[0],stoi(instruct[1]),stoi(instruct[2]),stoi(instruct[3])));
                    
                    /* cout << "Instructions: ";
                    for(int inst : instruct)
                    {
                        cout << inst <<" ";
                    }
                    cout << '\n';*/
                }
            }
        }
        myProgram.close();
    }
    else cout << "Unable to open file"; 

    for (auto inst : program)
    {
        cout << inst.name << " "<< inst.registerA << " " << inst.registerB << " " << inst.registerC<< "\n"; 
    }
    
    vector<long> registers{1,0,0,0,0,0};
    int ip = 0;
    while(ip < static_cast<int>(program.size()))
    {   
        registers[ip_register]=ip;
        cout<<"ip: "<<ip<< " [ ";
        for (auto regs: registers)
        {
            cout<<regs<< " ";
        }
        cout<<"] ";
        
        cout << program[ip].name << " "<< program[ip].registerA << " " << program[ip].registerB << " " << program[ip].registerC<< " [ ";

        runInstr(registers, program[ip],ip_register,ip);
        for (auto regs: registers)
        {
            cout<<regs<< " ";
        }
        cout<<"]\n";

    }


    cout << "Ans: "<<registers[0] << '\n';

    for(auto reg : registers)
    {
        cout<<reg<< " ";
    }
    cout<<'\n';
}