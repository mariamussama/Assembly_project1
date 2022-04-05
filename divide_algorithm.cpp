#include<iostream>
#include <unordered_map>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

void det_op(string &operation, string &label, string line) //extract label and operation
{
	string Temp = "";
	bool space = false;
	bool lab = false;
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != ':') && (!space))
			Temp.push_back(line[i]);

		if ((line[i] == ':') && (!lab))
		{
			lab = true;
			continue;
		}
		else if ((line[i] == ' ') && (line[i - 1] != ':') && (!space))
		{
			space = true;
			continue;
		}
		if (lab)
		{
			if ((line[i] == ' ') && (line[i - 1] == ':'))
			{
				label = Temp;
				Temp = "";
			}
		}
	}
	operation = Temp;
}

void three_reg(string& rd, string& rs1, string& rs2, string Inst, string op) //all instructions that deal with three registers
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op)+L+1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index+1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];
	rs2 = reg[2];
}

void imm_op(string& rd, string& rs1, int& val, string Inst, string op) //immediate instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];
	val = stoi(reg[2]);
}

void load_op(string& rd, string& rs1, int& offset, string Inst, string op) //load instructions 
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		if (line[i] == '(')
		{
			offset = stoi(temp);
			temp = "";
		}
		if (line[i] == ')')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];
	
}

void store_op(string& rs1, string& rs2, int& offset, string Inst, string op) //store instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		if (line[i] == '(')
		{
			offset = stoi(temp);
			temp = "";
		}
		if (line[i] == ')')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rs1 = reg[0];
	rs2 = reg[1];

}

void branch_op(string& rs1, string& rs2, string& label, string Inst, string op) //branching instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rs1 = reg[0];
	rs2 = reg[1];
	label = reg[2];
}

void Jal_op(string& rd, string& label, string Inst, string op) //jump and link instruction
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	label = reg[1];
}

void LUI_AUIPC(string& rd, int& val, string Inst, string op) //LUI and AUIPC instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	val = stoi(reg[1]);
}

int main()
{
	string instruction = "sw s0, 4(sp)";
	string operation = "";
	string label = "";
	string rd = "", rs1 = "", rs2 = "";
	int offset = 0;
	det_op(operation, label, instruction);
	//cout << operation << " " << label << " " ;

	int L = operation.length();
	string line = instruction.substr(instruction.find(operation) + L+1, instruction.length() - 1);
	//cout << endl << line << endl;
	store_op(rs1, rs2, offset, instruction, operation);
	cout <<rs1<<" "<<rs2<<" "<<offset << endl;
	return 0;
}