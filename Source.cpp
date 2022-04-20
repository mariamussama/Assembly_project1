#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include <cstdlib>
#include <cstdint>
#include<iomanip>
#include<bitset>
#include<vector>
#include<array>
using namespace std;
//determine the operation 
void det_op(string& operation, string line) //extract label and operation
{
	string Temp = "";
	int i = 0;
	while (line[i] != ' ')
	{
		if (line[i] == ':')
		{
			Temp = "";
			i++;
		}
		else
			Temp = Temp + line[i];
		i++;
	}
	operation = Temp;
}
//determine the label if any
void det_label(string& label, string line)
{
	string temp = "";
	int i = 0;
	label = temp;
	if ((line != "fence") && (line != "ecall") && (line != "ebreak"))
	while (line[i] != ' ')
	{
		if (line[i] == ':')
		{
			label = temp;
		}
		else
			temp = temp + line[i];
		i++;
	}
}

//read instructions and save them in the corresponding unordered map(lines) and labels
void read_instruction(ifstream& file, unordered_map<int, string>& lines, unordered_map<string, int>& label)
{
	string inst, lab = "";
	if (!file.is_open())
		cout << "Can't open file" << endl;
	else
	{
		int i = 0;
		while (getline(file, inst))
		{
			lines[i] = inst;
			det_label(lab, inst);
			if (lab != "")
				label[lab] = i;//save labels and their corresponding instruction no.
			i = i + 4;
		}

	}
	//for (auto x : lines)
		//cout << x.first << " " << x.second << endl;

}
//read the initial values of some reg and memory locations
void read_initial(ifstream& reg, ifstream& memory, unordered_map<string, int>& R, unordered_map<int, int>& M)
{
	string inst;
	if (!reg.is_open() || !memory.is_open())
		cout << "Can't open file" << endl;
	else
	{
		while (reg)
		{
			string r; int value;
			reg >> r >> value;
			if (r != "")
				R[r] = value;
		}
		while (memory)
		{
			int addr, value;
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

//instruction divider to get the registers/ offsets/ labels....
void three_reg(string& rd, string& rs1, string& rs2, string Inst, string op, unordered_map<string, int>& R) //all instructions that deal with three registers
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
	rs2 = reg[2];
	if (R.find(rd) == R.end())
		R[rd] = 0;
	if (R.find(rs1) == R.end())
		R[rs1] = 0;
	if (R.find(rs2) == R.end())
		R[rs2] = 0;
}

void imm_op(string& rd, string& rs1, int& val, string Inst, string op, unordered_map<string, int>& R) //immediate instructions
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
	if (R.find(rd) == R.end())
		R[rd] = 0;
	if (R.find(rs1) == R.end())
		R[rs1] = 0;
	val = stoi(reg[2]);
}

void load_op(string& rd, string& rs1, int& offset, string Inst, string op, unordered_map<string, int>& R) //load instructions 
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
	if (R.find(rd) == R.end())
		R[rd] = 0;
	if (R.find(rs1) == R.end())
		R[rs1] = 0;

}

void store_op(string& rs1, string& rs2, int& offset, string Inst, string op, unordered_map<string, int>& R) //store instructions
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
	if (R.find(rs1) == R.end())
		R[rs1] = 0;
	if (R.find(rs2) == R.end())
		R[rs2] = 0;

}

void branch_op(string& rs1, string& rs2, string& label, string Inst, string op, unordered_map<string, int>& R) //branching instructions
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
	if (R.find(rs1) == R.end())
		R[rs1] = 0;
	rs2 = reg[1];
	if (R.find(rs2) == R.end())
		R[rs2] = 0;
	label = reg[2];
}

void Jal_op(string& rd, string& label, string Inst, string op, unordered_map<string, int>& R) //jump and link instruction
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
	if (R.find(rd) == R.end())
		R[rd] = 0;
	label = reg[1];
}

void LUI_AUIPC(string& rd, int& val, string Inst, string op, unordered_map<string, int>& R) //LUI and AUIPC instructions
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
	if (R.find(rd) == R.end())
		R[rd] = 0;
	val = stoi(reg[1]);
}

//the operations fuunctions
void add_inst(string inst, unordered_map<string, int>& reg) // addition instruction 
{
	//cout << "add" << endl;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "add",reg);
	reg[rd] = reg.at(rs1) + reg.at(rs2);
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sub_inst(string inst, unordered_map<string, int>& reg)  // subtraction instruction
{
	//cout << "sub" << endl;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sub",reg);
	reg[rd] = reg.at(rs1) - reg.at(rs2);
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sll_inst(string inst, unordered_map<string, int>& reg) // shift left logical instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sll",reg);
	reg[rd] = reg.at(rs1) * pow(2, reg.at(rs2));
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void slt_inst(string inst, unordered_map<string, int>& reg) // set less than instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "slt",reg);
	if (reg.at(rs1) < reg.at(rs2))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sltu_inst(string inst, unordered_map<string, int>& reg) // set less than unsigned instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sltu",reg);
	if (abs(reg.at(rs1)) < abs(reg.at(rs2)))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void xor_inst(string inst, unordered_map<string, int>& reg) // exclusive or instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "xor", reg);
	reg[rd] = reg.at(rs1) ^ reg.at(rs2);
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void srl_inst(string inst, unordered_map<string, int>& reg) // shift right logical instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "srl", reg);
	reg[rd] = reg.at(rs1) / (pow(2, reg.at(rs2)));
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sra_inst(string inst, unordered_map<string, int>& reg) // shift right arithmetic instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sra", reg);
	reg[rd] = reg.at(rs1) / pow(2, reg.at(rs2));
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void or_inst(string inst, unordered_map<string, int>& reg) // or instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "or", reg);
	if (reg.at(rs1) || reg.at(rs2))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
void and_inst(string inst, unordered_map<string, int>& reg) // and instruction 
{
	//cout << "and" << endl;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "and", reg);
	if (reg.at(rs1) && reg.at(rs2))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << rs2 << endl;
}
/////////////////////////////////
void slli_inst(string inst, unordered_map<string, int>& reg) // shift left logical immediate instruction  
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slli",reg);
	reg[rd] = reg.at(rs1) * pow(2, val);
	//cout << rd << " " << rs1 << " " << val << endl;
}
void srli_inst(string inst, unordered_map<string, int>& reg) // shift right logical immediate instrucrtion 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srli",reg);
	reg[rd] = reg.at(rs1) / (pow(2, val));
	//cout << rd << " " << rs1 << " " << val << endl;
}
void srai_inst(string inst, unordered_map<string, int>& reg) // shift right arethmetic immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srai",reg);
	reg[rd] = reg.at(rs1) / pow(2, val);
	//cout << rd << " " << rs1 << " " << val << endl;
}
/////////////////////////////////
void addi_inst(string inst, unordered_map<string, int>& reg) // add immediate instruction 
{
	//cout << "addi" << endl;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "addi", reg);
	reg[rd] = reg.at(rs1) + val;
	//cout << rd << " " << rs1 << " " << val << endl;
}
void slti_inst(string inst, unordered_map<string, int>& reg) // set if less than immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slti", reg);
	if (reg.at(rs1) < val)
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << val << endl;
}
void sltiu_inst(string inst, unordered_map<string, int>& reg) // set if less than unsigned immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "sltiu", reg);
	if (abs(reg.at(rs1)) < abs(val))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << val << endl;
}
void xori_inst(string inst, unordered_map<string, int>& reg) // exclusive or immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "xori", reg);
	reg[rd] = reg.at(rs1) ^ val;
	//cout << rd << " " << rs1 << " " << val << endl;
}
void ori_inst(string inst, unordered_map<string, int>& reg) // or immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "ori", reg);
	if (reg.at(rs1) || val)
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << val << endl;
}
void andi_inst(string inst, unordered_map<string, int>& reg) // and immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "andi", reg);
	if (reg.at(rs1) && val)
		reg[rd] = 1;
	else
		reg[rd] = 0;
	//cout << rd << " " << rs1 << " " << val << endl;
}
/////////////////////////////////
void sb_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // store byte instruction 
{
	string rs1, rs2; int offset;
	store_op(rs1, rs2, offset, inst, "sb",reg);
	int8_t temp = reg.at(rs1);
	int addr = reg.at(rs2) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	memory[addr] = temp;
	//cout << rs1 << " " << rs2 << " " << offset << endl;
}
void sh_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // store halfword instruction 
{
	string rs1, rs2; int offset;
	store_op(rs1, rs2, offset, inst, "sh",reg);
	int16_t temp = reg.at(rs1);
	int addr = reg.at(rs2) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	memory[addr] = temp;
	//cout << rs1 << " " << rs2 << " " << offset << endl;
}
void sw_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // store word instruction 
{
	string rs1, rs2; int offset;
	store_op(rs1, rs2, offset, inst, "sw",reg);
	int32_t temp = reg.at(rs1);
	int addr = reg.at(rs2) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	memory[addr] = temp;
	//cout << rs1 << " " << rs2 << " " << offset << endl;
}
/////////////////////////////////
void lb_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) //  load byte instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lb",reg);
	int addr = reg.at(rs1) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	int8_t temp = memory.at(addr);
	reg[rd] = temp;
	//cout << rd << " " << rs1 << " " << offset << endl;
}
void lh_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) //  load halfword instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lh",reg);
	int addr = reg.at(rs1) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	int16_t temp = memory.at(addr);
	reg[rd] = temp;
	//cout << rd << " " << rs1 << " " << offset << endl;
}
void lw_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // load word instruction 
{
	//cout << "lw" << endl;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lw",reg);
	int addr = reg.at(rs1) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	int32_t temp = memory.at(addr);
	reg[rd] = temp;
	//cout << rd << " " << rs1 << " " << offset << endl;
}
void lbu_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // load byte unsigned instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lbu",reg);
	int addr = reg.at(rs1) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	int8_t temp = abs(memory.at(addr));
	reg[rd] = temp;
	//cout << rd << " " << rs1 << " " << offset << endl;
}
void lhu_inst(string inst, unordered_map<string, int>& reg, unordered_map<int, int>& memory) // load halfword unsigne instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lhu",reg);
	int addr = reg.at(rs1) + offset;
	if (memory.find(addr) == memory.end())
		memory[addr] = 0;
	int16_t temp = abs(memory.at(addr));
	reg[rd] = temp;
	//cout << rd << " " << rs1 << " " << offset << endl;
}
/////////////////////////////////
void beq_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // branch if equal instruction (==)
{
	//cout << "beq" << endl;
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "beq", reg);
	if (reg.at(rs1) == reg.at(rs2))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
void bne_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // branch if not equal instruction (!=)
{
	//cout << "bne" << endl;
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "bne", reg);
	if (reg.at(rs1) != reg.at(rs2))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
void blt_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // branch if less than instruction(<)
{
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "blt", reg);
	if (reg.at(rs1) < reg.at(rs2))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
void bge_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // branch if greater than or equal instruction (>=)
{
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "bge", reg);
	if (reg.at(rs1) >= reg.at(rs2))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
void bltu_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // branch if less than using unsigned numbers instruction
{
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "bltu", reg);
	if (abs(reg.at(rs1)) < abs(reg.at(rs2)))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
void bgeu_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) //branch if greater than or equal using unsigned numbers instruction
{
	string rs1, rs2, lab;
	branch_op(rs1, rs2, lab, inst, "bgeu", reg);
	if (abs(reg.at(rs1)) >= abs(reg.at(rs2)))
	{
		jump = label.at(lab);
	}
	//cout << rs1 << " " << rs2 << " " << lab << endl;
}
/////////////////////////////////
void jalr_inst(string inst, unordered_map<string, int>& reg, int& jump) // jump and link register instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "jalr", reg);
	reg[rd] = jump + 4;
	jump = reg.at(rs1) + offset;

	//cout << rd << " " << rs1 << " " << offset << endl;
}
/////////////////////////////////
void jal_inst(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, int& jump) // jump and link instruction 
{
	string rd, lab;
	Jal_op(rd, lab, inst, "jal", reg);
	reg[rd] = jump + 4;
	jump = label.at(lab);
	//cout << "jump" << endl << endl;
	//cout << rd << " " << lab << endl;
}
/////////////////////////////////
void lui_inst(string inst, unordered_map<string, int>& reg) // load upper immediate instruction 
{
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "lui", reg);
	int temp1 = val;
	reg[rd] = temp1 * pow(2, 12);
	/*
	reg[rd] = pow(2,12)*val;
	*/
	//cout << rd << " " << val << endl;
}
void auipc_inst(string inst, unordered_map<string, int>& reg, int& jump) // add upper immediate to PC instruction 
{
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "auipc", reg);
	reg[rd] = jump + (pow(2,12)*val);
	//cout << rd << " " << val << endl;
}
/////////////////////////////////
//divider function that call the operation function based on the operation
void operation_divider(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, unordered_map<int, int>& memory, int& jump, unordered_map<int, string> lines) // string of the instruction type will be the input of this function that automaticlly calles the specific function for that operation 
{
	int output;
	string op;
	if ((inst == "fence") || (inst == "ecall") || (inst == "ebreak"))
		jump = (lines.size() * 4);
	else 
	{
		det_op(op, inst);
		//cout << op << endl;
		if (op == "add")
			add_inst(inst, reg);
		if (op == "sub")
			sub_inst(inst, reg);
		if (op == "sll")
			sll_inst(inst, reg);
		if (op == "slt")
			slt_inst(inst, reg);
		if (op == "sltu")
			sltu_inst(inst, reg);
		if (op == "xor")
			xor_inst(inst, reg);
		if (op == "srl")
			srl_inst(inst, reg);
		if (op == "sra")
			sra_inst(inst, reg);
		if (op == "or")
			or_inst(inst, reg);
		if (op == "and")
			and_inst(inst, reg);
		if (op == "slli")
			slli_inst(inst, reg);
		if (op == "srli")
			srli_inst(inst, reg);
		if (op == "srai")
			srai_inst(inst, reg);
		if (op == "addi")
			addi_inst(inst, reg);
		if (op == "slti")
			slti_inst(inst, reg);
		if (op == "sltiu")
			sltiu_inst(inst, reg);
		if (op == "xori")
			xori_inst(inst, reg);
		if (op == "ori")
			ori_inst(inst, reg);
		if (op == "andi")
			andi_inst(inst, reg);
		if (op == "sb")
			sb_inst(inst, reg, memory);
		if (op == "sh")
			sh_inst(inst, reg, memory);
		if (op == "sw")
			sw_inst(inst, reg, memory);
		if (op == "lb")
			lb_inst(inst, reg, memory);
		if (op == "lh")
			lh_inst(inst, reg, memory);
		if (op == "lw")
			lw_inst(inst, reg, memory);
		if (op == "lbu")
			lbu_inst(inst, reg, memory);
		if (op == "lhu")
			lhu_inst(inst, reg, memory);
		if (op == "beq")
			beq_inst(inst, reg, label, jump);
		if (op == "bne")
			bne_inst(inst, reg, label, jump);
		if (op == "blt")
			blt_inst(inst, reg, label, jump);
		if (op == "bge")
			bge_inst(inst, reg, label, jump);
		if (op == "bltu")
			bltu_inst(inst, reg, label, jump);
		if (op == "bgeu")
			bgeu_inst(inst, reg, label, jump);
		if (op == "jalr")
			jalr_inst(inst, reg, jump);
		if (op == "jal")
			jal_inst(inst, reg, label, jump);
		if (op == "lui")
			lui_inst(inst, reg);
		if (op == "auipc")
			auipc_inst(inst, reg, jump);
	}
	
}

void disp_init(unordered_map<int, int> memory, unordered_map<string, int> reg)
{
	
	std::array<string, 4> head = {
		"Memory:",
		"Decimal",
		"Hexadecimal",
		"Binary",
	};

	int space[] = {
		head[0].size() + 2,
		head[1].size() + 2,
		10 + 2,
		30 + 2 };

	/*for (int i = 0; i < head.size(); i++)
	{
		cout << setw(space[i]) << head[i];
	}*/
	cout << "Memory:" << "  " << "Decimal" << "  " << "Hexadecimal" << " " << "Binary";
	cout << endl;
	
	for (auto i : memory)
	{
		cout << left << setw(space[0]) << i.first << setw(space[1]) << dec << i.second << setw(space[2]) << hex << i.second << setw(space[3]) << bitset<32>(i.second);
		cout << endl;
		
	}
	cout << endl;
	
	std::array<string, 4> headers = {
		"Registers",
		"Decimal",
		"Hexadecimal",
		"Binary",
	};

	int spaces[] = {
		headers[0].size() + 2,
		headers[1].size() + 2,
		10 + 2,
		32 + 2 };

	for (int i = 0; i < headers.size(); i++)
	{
		cout << setw(spaces[i]) << headers[i];
	}
	cout << endl;
	for (auto x : reg)
	{
		
		cout << left << setw(spaces[0]) << x.first << setw(spaces[1]) << dec << x.second << setw(spaces[2]) << hex << x.second << setw(spaces[3]) << bitset<32>(x.second);
		cout << endl;
		
	}
	cout << endl;
	
}

int main()
{
	char hor = '-';           // Change to other characters if available
	int tab = 80;

	ifstream inst("instructions.txt");
	ifstream reg_init("initialReg.txt");
	ifstream memory_init("initialMem.txt");
	unordered_map<int, string> lines;
	unordered_map<string, int> label;
	unordered_map<string, int> reg;
	unordered_map<int, int> memory;
	read_instruction(inst, lines, label);
	read_initial(reg_init, memory_init, reg, memory);
	int pc = 0;
	//cout << string(tab, hor)<<endl;
	cout << "PC = " << dec << pc << " = ";
	cout << hex << pc <<" = " << bitset<32>(pc)<<endl;
	disp_init(memory, reg);
	cout << string(tab, hor);
	while (pc != (lines.size() * 4))
	{
		//cout<<lines.at(j)<<endl;
		int jump = pc;
		operation_divider(lines.at(pc), reg, label, memory, jump,lines);
		cout << endl;
		cout << "PC = " << dec << pc << " = ";
		cout << hex << pc << " = " << bitset<32>(pc) << endl;
		cout << lines.at(pc) << endl;
		disp_init(memory, reg);
		cout << string(tab, hor);
		if (jump == pc)
			pc = pc + 4;
		else
			pc = jump;
		
	}
	//cout << pc << endl;

	/*for (auto x : lines)
	{
		//string op, label;
		//cout << x.first << " " << x.second << endl;
		//det_op(op, x.second);
		//operation_divider(x.second,reg,label,memory);
		//cout << op << endl;
	}
	//cout << lines.size();
	for (auto x : label)
	{
		//cout << x.first << " " << x.second << endl;
	}
	for (auto x : reg)
	{
		//cout << x.first << " " << x.second << endl;
	}*/

	return 0;
}