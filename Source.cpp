#include<iostream>
#include <unordered_map>
#include<string>
#include<fstream>
using namespace std;
void read_instruction(ifstream& file, unordered_map<int,string> & lines)
{
	string inst;
	if (!file.is_open())
		cout << "Can't open file" << endl;
	else
	{
		int i = 0;
		while (getline(file, inst)) 
		{
			lines[i] = inst;
			i = i + 4;
		}
	}
	//for (auto x : lines)
		//cout << x.first << " " << x.second << endl;

}
void read_initial(ifstream& reg, ifstream& memory, unordered_map<string, int>& R, unordered_map<int, int>& M)
{
	string inst;
	if (!reg.is_open()||!memory.is_open())
		cout << "Can't open file" << endl;
	else
	{
		while (reg)
		{
			string r; int value;
			reg >> r >> value;
			if(r!="")
			R[r] = value;
		}
		while (memory)
		{
			int addr,value;
			memory >> addr >> value;
			M[addr] = value;
		}
	}
/*	for (auto x : R)
		cout << x.first << " " << x.second << endl;
	for (auto x : M)
		cout << x.first << " " << x.second << endl;
		*/
}

int add_fun(int input1, int input2)
{
	int output = input1 + input2;
	return ouput;
}
void operations(string op, int input1, int input2)
{
	if (op == "add")
		output = add_fun(input1, input2)
}

int main()
{
	ifstream inst("instructions.txt");
	ifstream reg_init("initialReg.txt");
	ifstream memory_init("initialMem.txt");
	unordered_map<int, string> lines;
	unordered_map<string, int> reg;
	unordered_map<int, int> memory;
	read_instruction(inst, lines);
	read_initial(reg_init, memory_init, reg, memory);

	return 0;
}