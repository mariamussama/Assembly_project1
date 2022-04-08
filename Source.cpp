#include<iostream>
#include <unordered_map>
#include<string>
#include<fstream>
using namespace std;
void det_op(string& operation, string line) //extract label and operation
{
	string Temp = "";
	int i = 0;
	while (line[i] != ' ')
	{
		if (line[i] == ':')
		{
			Temp = ""; i++;
		}
		else
			Temp = Temp + line[i];
		i++;
	}
	operation = Temp;
}
void det_label(string& label, string line)
{
	string temp = "";
	int i = 0;
	label = temp;
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

void read_instruction(ifstream& file, unordered_map<int, string>& lines, unordered_map<string, int>& label)
{
	string inst,lab="";
	if (!file.is_open())
		cout << "Can't open file" << endl;
	else
	{
		int i = 0;
		while (getline(file, inst))
		{
			lines[i] = inst;
			det_label(lab, inst);
			if (lab!="")
				label[lab] = i;
			i = i + 4;
		}
		
	}
	//for (auto x : lines)
		//cout << x.first << " " << x.second << endl;

}
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


void three_reg(string& rd, string& rs1, string& rs2, string Inst, string op) //all instructions that deal with three registers
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


int add_inst(string inst) // addition instruction 
{
	cout << "add" << endl;
	int output = 0; string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "add");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int sub_inst(string inst)  // subtraction instruction
{
	cout << "sub" << endl;
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sub");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int sll_inst(string inst) // shift left logical instruction 
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sll");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int slt_inst(string inst) // set less than instruction
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "slt");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int sltu_inst(string inst) // set less than unsigned instruction
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sltu");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int xor_inst(string inst) // exclusive or instruction 
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "xor");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int srl_inst(string inst) // shift right logical instruction
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "srl");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int sra_inst(string inst) // shift right arithmetic instruction 
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sra");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int or_inst(string inst) // or instruction
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "or");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
int and_inst(string inst) // and instruction 
{
	int output=0;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "and");
	cout << rd << " " << rs1 << " " << rs2 << endl;
	return output;
}
/////////////////////////////////
int slli_inst(string inst) // shift left logical immediate instruction  
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slli");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int srli_inst(string inst) // shift right logical immediate instrucrtion 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srli");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int srai_inst(string inst) // shfit right arethmetic instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srai");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
/////////////////////////////////
int addi_inst(string inst) // add immediate instruction 
{
	cout << "addi" << endl;
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "addi");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int slti_inst(string inst) // set if less than immediate instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slti");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int sltiu_inst(string inst) // set if less than unsigned immediate instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "sltiu");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int xori_inst(string inst) // exclusive or immediate instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "xori");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int ori_inst(string inst) // or immediate instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "ori");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
int andi_inst(string inst) // and immediate instruction 
{
	int output=0;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "andi");
	cout << rd << " " << rs1 << " " << val << endl;
	return output;
}
/////////////////////////////////
int sb_inst(string inst) // store byte instruction 
{
	int output=0;
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst,"sb");
	cout << rs1 << " " << rs2 << " " << offset << endl;
	return output;
}
int sh_inst(string inst) // store halfword instruction 
{
	int output=0;
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst, "sh");
	cout << rs1 << " " << rs2 << " " << offset << endl;
	return output;
}
int sw_inst(string inst) // store word instruction 
{
	int output=0;
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst, "sw");
	cout << rs1 << " " << rs2 << " " << offset << endl;
	return output;
}
/////////////////////////////////
int lb_inst(string inst) //  load byte instruction 
{
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lb");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
int lh_inst(string inst) //  load halfword instruction 
{
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lh");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
int lw_inst(string inst) // load word instruction 
{
	cout << "lw" << endl;
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lw");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
int lbu_inst(string inst) // load byte unsigned instruction 
{
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lbu");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
int lhu_inst(string inst) // load halfword unsigne instruction 
{
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lhu");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
/////////////////////////////////
int beq_inst(string inst) // branch if equal instruction (==)
{
	cout << "beq" << endl;
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "beq");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
int bne_inst(string inst) // branch if not equal instruction (!=)
{
	cout << "bne" << endl;
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bne");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
int blt_inst(string inst) // branch if less than instruction(<)
{
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "blt");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
int bge_inst(string inst) // branch if greater than or equal instruction (>=)
{
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bge");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
int bltu_inst(string inst) // branch if less than using unsigned numbers instruction
{
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bltu");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
int bgeu_inst(string inst) //branch if greater than or equal using unsigned numbers instruction
{
	int output=0;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bgeu");
	cout << rs1 << " " << rs2 << " " << label << endl;
	return output;
}
/////////////////////////////////
int jalr_inst(string inst) // jump and link register instruction 
{
	int output=0;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "jalr");
	cout << rd << " " << rs1 << " " << offset << endl;
	return output;
}
/////////////////////////////////
int jal_inst(string inst) // jump and link instruction 
{
	int output=0;
	string rd, label;
	Jal_op(rd, label, inst, "jal");
	cout << rd << " " << label << endl;
	return output;
}
/////////////////////////////////
int lui_inst(string inst) // load upper immediate instruction 
{
	int output = 0;
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "lui");
	cout << rd << " " << val << endl;
	return output;
}
int auipc_inst(string inst) // add upper immediate to PC instruction 
{
	int output=0;
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "auipc");
	cout << rd << " " << val << endl;
	return output;
}
/////////////////////////////////
void operation_divider(string inst) // string of the instruction type will be the input of this function that automaticlly calles the specofoc function for that operation 
{
	int output;
	string op;
	det_op(op, inst);
	//cout << op << endl;
	if (op == "add")
		output = add_inst(inst);
	if (op == "sub")
		output = sub_inst(inst);
	if (op == "sll")
		output = sll_inst(inst);
	if (op == "slt")
		output = slt_inst(inst);
	if (op == "sltu")
		output = sltu_inst(inst);
	if (op == "xor")
		output = xor_inst(inst);
	if (op == "srl")
		output = srl_inst(inst);
	if (op == "sra")
		output = sra_inst(inst);
	if (op == "or")
		output = or_inst(inst);
	if (op == "and")
		output = and_inst(inst);
	if (op == "slli")
		output = slli_inst(inst);
	if (op == "srli")
		output = srli_inst(inst);
	if (op == "srai")
		output = srai_inst(inst);
	if (op == "addi")
		output = addi_inst(inst);
	if (op == "slti")
		output = slti_inst(inst);
	if (op == "sltiu")
		output = sltiu_inst(inst);
	if (op == "xori")
		output = xori_inst(inst);
	if (op == "ori")
		output = ori_inst(inst);
	if (op == "andi")
		output = andi_inst(inst);
	if (op == "sb")
		output = sb_inst(inst);
	if (op == "sh")
		output = sh_inst(inst);
	if (op == "sw")
		output = sw_inst(inst);
	if (op == "lb")
		output = lb_inst(inst);
	if (op == "lh")
		output = lh_inst(inst);
	if (op == "lw")
		output = lw_inst(inst);
	if (op == "lbu")
		output = lbu_inst(inst);
	if (op == "lhu")
		output = lhu_inst(inst);
	if (op == "beq")
		output = beq_inst(inst);
	if (op == "bne")
		output = bne_inst(inst);
	if (op == "blt")
		output = blt_inst(inst);
	if (op == "bge")
		output = bge_inst(inst);
	if (op == "bltu")
		output = bltu_inst(inst);
	if (op == "bgeu")
		output = bgeu_inst(inst);
	if (op == "jalr")
		output = jalr_inst(inst);
	if (op == "jal")
		output = jal_inst(inst);
	if (op == "lui")
		output = lui_inst(inst);
	if (op == "auipc")
		output = auipc_inst(inst);
}


int main()
{
	ifstream inst("instructions.txt");
	ifstream reg_init("initialReg.txt");
	ifstream memory_init("initialMem.txt");
	unordered_map<int, string> lines;
	unordered_map<string, int> label;
	unordered_map<string, int> reg;
	unordered_map<int, int> memory;
	read_instruction(inst, lines, label);
	read_initial(reg_init, memory_init, reg, memory);
	for (auto x : lines)
	{
		string op, label;
		cout << x.first << " " << x.second << endl;
		//det_op(op, x.second);
		operation_divider(x.second);
		//cout << op << endl;
	}
	for (auto x : label)
	{
		cout << x.first << " " << x.second << endl;
	}

	return 0;
}